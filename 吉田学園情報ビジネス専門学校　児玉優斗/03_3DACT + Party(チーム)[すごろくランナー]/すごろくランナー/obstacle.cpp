//=============================================================================
//
// ��Q���̏������� [obstacle.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "obstacle.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OBSTACLE_NAME0	"data\\MODEL\\obstacle\\logS.x"			// ��(��)�̃��f����
#define OBSTACLE_NAME1	"data\\MODEL\\obstacle\\logM.x"			// ��(��)�̃��f����
#define OBSTACLE_NAME2	"data\\MODEL\\obstacle\\logL.x"			// ��(��)�̃��f����
#define OBSTACLE_NAME3	"data\\MODEL\\obstacle\\move.x"			// �|�؂̃��f����
#define OBSTACLE_NAME4	"data\\MODEL\\obstacle\\move.x"			// �|�؂̃��f����
#define OBSTACLE_NAME5	"data\\MODEL\\obstacle\\logL.x"			// �|�؂̃��f����
#define OBSTACLE_NAME6	"data\\MODEL\\obstacle\\logBase.x"			// �|�؂̃��f����
#define OBSTACLE_NAME7	"data\\MODEL\\obstacle\\logM.x"	    // �ړ��ۑ��̃��f����
#define OBSTACLE_NAME8	"data\\MODEL\\obstacle\\logFat.x"	    // �����ۑ��̃��f����
#define OBSTACLE_NAME9	"data\\MODEL\\obstacle\\logL.x"			// ��(����])�̃��f����
#define OBSTACLE_NAME10	"data\\MODEL\\obstacle\\logL.x"			// ��(�E��])�̃��f����
#define OBSTACLE_NAME11	"data\\MODEL\\obstacle\\logStairs_S.x"	// �؁i�K�i�jS
#define OBSTACLE_NAME12	"data\\MODEL\\obstacle\\logStairs_M.x"	// �؁i�K�i�jM
#define OBSTACLE_NAME13	"data\\MODEL\\obstacle\\logStairs_L.x"	// �؁i�K�i�jL
#define OBSTACLE_NAME14	"data\\MODEL\\obstacle\\halflogStairs_S.x"	// �؁i�K�i�����jS
#define OBSTACLE_NAME15	"data\\MODEL\\obstacle\\halflogStairs_M.x"	// �؁i�K�i�����jM
#define OBSTACLE_NAME16	"data\\MODEL\\obstacle\\halflogStairs_L.x"	// �؁i�K�i�����jL
#define FIELD_SIZE		    (300.0f)							// �t�B�[���h�̑傫��
#define OBSTACLE_SIZE		(5.0f)								// ���f���̑傫��
#define MAX_OBSTACLE		(200)
#define MAX_OBSTACLE_TYPE   (OBSTACLE_TYPE_MAX)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH		    g_pMeshObstacle[MAX_OBSTACLE_TYPE];	              // ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER	    g_pBuffMatObstacle[MAX_OBSTACLE_TYPE];	          // �}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9* g_pTextureObstacle[MAX_OBSTACLE_TYPE];            // �e�N�X�`�����ւ̃|�C���^
DWORD			    g_nNumMatObstacle[MAX_OBSTACLE_TYPE] = { 0,0,0,0 }; // �}�e���A�����̐�
OBSTACLE	        g_aObstacle[MAX_OBSTACLE_TYPE][MAX_OBSTACLE];     // ��Q���̏��
int g_nMoveTimer;
//=============================================================================
// ����������
//=============================================================================
void InitObstacle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_nMoveTimer = 0;
	char aXFileName[MAX_OBSTACLE_TYPE][64] = { OBSTACLE_NAME0,
		OBSTACLE_NAME1	,
		OBSTACLE_NAME2,
		OBSTACLE_NAME3,
		OBSTACLE_NAME4,
		OBSTACLE_NAME5,
		OBSTACLE_NAME6,
		OBSTACLE_NAME7,
		OBSTACLE_NAME8,
		OBSTACLE_NAME9,
		OBSTACLE_NAME10,
		OBSTACLE_NAME11,
		OBSTACLE_NAME12,
		OBSTACLE_NAME13,
		OBSTACLE_NAME14,
		OBSTACLE_NAME15,
		OBSTACLE_NAME16,
	};

	for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
	{// ��Q���̎�ނ����J��Ԃ�
	 // X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(aXFileName[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObstacle[nCntType],
			NULL,
			&g_nNumMatObstacle[nCntType],
			&g_pMeshObstacle[nCntType]);

		// �}�e���A����񂩂�e�N�X�`���������o��
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatObstacle[nCntType]->GetBufferPointer();
		D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_nNumMatObstacle[nCntType]];
		g_pTextureObstacle[nCntType] = new LPDIRECT3DTEXTURE9[g_nNumMatObstacle[nCntType]];

		for (DWORD nCntMat = 0; nCntMat < g_nNumMatObstacle[nCntType]; nCntMat++)
		{// ���_���̐������J��Ԃ� 
		 // �}�e���A������ǂݍ���
			pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

			// ����������������
			pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

			// �e�N�X�`������������
			g_pTextureObstacle[nCntType][nCntMat] = NULL;

			// �e�N�X�`���̏���ǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL &&
				lstrlen(pMat[nCntMat].pTextureFilename) > 0)
			{// �e�N�X�`���̃t�@�C����������
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureObstacle[nCntType][nCntMat]);
			}
		}

		for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
		{// ��Q���̐������J��Ԃ�
		 // ��Q�����̏�����
			g_aObstacle[nCntType][nCntObstacle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ���W��������
			g_aObstacle[nCntType][nCntObstacle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ��������������
			g_aObstacle[nCntType][nCntObstacle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ړ��ʂ���������
			g_aObstacle[nCntType][nCntObstacle].nType = (OBSTACLE_TYPE)nCntType;         // ��ނ���������
			g_aObstacle[nCntType][nCntObstacle].bUse = false;                            // �g�p���Ă��Ȃ���Ԃɂ���
			for (int nCntVer = 0; nCntVer < 4; nCntVer++)
			{// ���_���̐������J��Ԃ�
				g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}

			if (nCntObstacle == 0)
			{// 1��ڂ�������
				int nNumVtx;	 // ���_��
				DWORD sizeFVF;	 // ���_�t�H�[�}�b�g�̃T�C�Y
				BYTE *pVtxBuff;  // ���_�o�b�t�@�ւ̃|�C���^

								 // �ŏ��l�̐ݒ�
				g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
				g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

				// ���_�����擾
				nNumVtx = g_pMeshObstacle[nCntType]->GetNumVertices();

				// ���_�t�H�[�}�b�g�̃T�C�Y���擾
				sizeFVF = D3DXGetFVFVertexSize(g_pMeshObstacle[nCntType]->GetFVF());

				// ���_�o�b�t�@�����b�N
				g_pMeshObstacle[nCntType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{// ���f���̒��_�������J��Ԃ�
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

					if (vtx.x < g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x)
					{// X���W����菬����
						g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x = vtx.x;
					}
					if (vtx.y < g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y)
					{// Y���W����菬����
						g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y = vtx.y;
					}
					if (vtx.z < g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z)
					{// Z���W����菬����
						g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z = vtx.z;
					}

					if (vtx.x > g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x)
					{// X���W�����傫��
						g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x = vtx.x;
					}
					if (vtx.y > g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y)
					{// Y���W�����傫��
						g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y = vtx.y;
					}
					if (vtx.z > g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z)
					{// Z���W�����傫��
						g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z = vtx.z;
					}

					pVtxBuff += sizeFVF;	// �T�C�Y���|�C���^��i�߂�
				}

				// ���_�o�b�t�@���A�����b�N
				g_pMeshObstacle[nCntType]->UnlockVertexBuffer();
			}
			else
			{// ����ȍ~
				g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle = g_aObstacle[nCntType][nCntObstacle - 1].vtxMaxObstacle;
				g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle = g_aObstacle[nCntType][nCntObstacle - 1].vtxMinObstacle;
			}
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitObstacle(void)
{
	for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
	{
		// ���b�V���̊J��
		if (g_pMeshObstacle[nCntType] != NULL)
		{
			g_pMeshObstacle[nCntType]->Release();
			g_pMeshObstacle[nCntType] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatObstacle[nCntType] != NULL)
		{
			g_pBuffMatObstacle[nCntType]->Release();
			g_pBuffMatObstacle[nCntType] = NULL;
		}
		// �e�N�X�`���̊J��
		for (DWORD nCntMat = 0; nCntMat < g_nNumMatObstacle[nCntType]; nCntMat++)
		{
			if (g_pTextureObstacle[nCntType][nCntMat] != NULL)
			{
				g_pTextureObstacle[nCntType][nCntMat]->Release();
				g_pTextureObstacle[nCntType][nCntMat] = NULL;
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObstacle(void)
{
	g_nMoveTimer++;
	for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
	{// ��Q���̎�ނ̐������J��Ԃ�
		for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
		{// ��Q���̒u���鐔�����J��Ԃ�
			if (g_aObstacle[nCntType][nCntObstacle].bUse == true)
			{// ��Q�����g�p����Ă���
			 // �O��̈ʒu�X�V
				g_aObstacle[nCntType][nCntObstacle].posold = g_aObstacle[nCntType][nCntObstacle].pos;

				// �ړ�������
				g_aObstacle[nCntType][nCntObstacle].pos += g_aObstacle[nCntType][nCntObstacle].move;

				switch (g_aObstacle[nCntType][nCntObstacle].nType)
				{// ��Q���̎�ނ��Ƃɏ����킯
				case OBSTACLE_TYPE_LOG_S:	//���T�C�Y�ۑ�
					break;
				case OBSTACLE_TYPE_LOG_M:	//���T�C�Y�ۑ�
					break;
				case OBSTACLE_TYPE_LOG_L:	//���T�C�Y�ۑ�203268535
					break;

				case OBSTACLE_TYPE_MOVE:	//�ړ���
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{// �v���C���[�̐������J��Ԃ�
						CollisionMoveOb(g_aObstacle[nCntType][nCntObstacle].pos, g_aObstacle[nCntType][nCntObstacle].posold, g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle, g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle, nCntPlayer);
					}
					break;
				case OBSTACLE_TYPE_HALFMOVE://�ړ�������
					if (g_nMoveTimer % 92 == 0)
					{
						g_aObstacle[nCntType][nCntObstacle].move.x *= -1;
						g_aObstacle[nCntType][nCntObstacle].move.z *= -1;
					}
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{// �v���C���[�̐������J��Ԃ�
						CollisionMoveOb(g_aObstacle[nCntType][nCntObstacle].pos, g_aObstacle[nCntType][nCntObstacle].posold, g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle, g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle, nCntPlayer);
					}
					break;
				case OBSTACLE_TYPE_UPDOWNLOG://�㉺�ړ��ۑ�
					if (g_nMoveTimer % 50 == 0)
					{
						g_aObstacle[nCntType][nCntObstacle].move.y *= -1;
					}
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{// �v���C���[�̐������J��Ԃ�
						CollisionMoveOb(g_aObstacle[nCntType][nCntObstacle].pos, g_aObstacle[nCntType][nCntObstacle].posold, g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle, g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle, nCntPlayer);
					}
					break;
				case OBSTACLE_TYPE_LOGMOVE://�ړ��ۑ�
					if (g_nMoveTimer % 92 == 0)
					{
						g_aObstacle[nCntType][nCntObstacle].move.x *= -1;
						g_aObstacle[nCntType][nCntObstacle].move.z *= -1;
					}
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{// �v���C���[�̐������J��Ԃ�
						CollisionMoveOb(g_aObstacle[nCntType][nCntObstacle].pos, g_aObstacle[nCntType][nCntObstacle].posold, g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle, g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle, nCntPlayer);
					}
					break;
				case OBSTACLE_TYPE_ROLL_LEFT:// ����]�ۑ�
					g_aObstacle[nCntType][nCntObstacle].rot.y -= D3DX_PI / 120;
					if (g_aObstacle[nCntType][nCntObstacle].rot.y <= -D3DX_PI)
					{
						g_aObstacle[nCntType][nCntObstacle].rot.y = D3DX_PI;
					}
					g_aObstacle[nCntType][nCntObstacle].pos.x = g_aObstacle[nCntType][nCntObstacle].pos.x - sinf(g_aObstacle[nCntType][nCntObstacle].rot.y) * 1.5f;
					g_aObstacle[nCntType][nCntObstacle].pos.z = g_aObstacle[nCntType][nCntObstacle].pos.z - cosf(g_aObstacle[nCntType][nCntObstacle].rot.y) * 1.5f;
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{// �v���C���[�̐������J��Ԃ�
						CollisionMoveOb(g_aObstacle[nCntType][nCntObstacle].pos, g_aObstacle[nCntType][nCntObstacle].posold, g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle, g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle, nCntPlayer);
					}
					break;

				case OBSTACLE_TYPE_ROLL_RIGHT:// ����]�ۑ�
					g_aObstacle[nCntType][nCntObstacle].rot.y += D3DX_PI / 120;
					if (g_aObstacle[nCntType][nCntObstacle].rot.y >= D3DX_PI)
					{
						g_aObstacle[nCntType][nCntObstacle].rot.y = -D3DX_PI;
					}
					g_aObstacle[nCntType][nCntObstacle].pos.x = g_aObstacle[nCntType][nCntObstacle].pos.x - sinf(g_aObstacle[nCntType][nCntObstacle].rot.y) * 1.5f;
					g_aObstacle[nCntType][nCntObstacle].pos.z = g_aObstacle[nCntType][nCntObstacle].pos.z - cosf(g_aObstacle[nCntType][nCntObstacle].rot.y) * 1.5f;
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{// �v���C���[�̐������J��Ԃ�
						CollisionMoveOb(g_aObstacle[nCntType][nCntObstacle].pos, g_aObstacle[nCntType][nCntObstacle].posold, g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle, g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle, nCntPlayer);
					}
					break;

				case OBSTACLE_TYPE_STAIRS_S:
					if (GetKeyboardPress(DIK_9) == true)
					{
						g_aObstacle[nCntType][nCntObstacle].rot.y += 0.04f;
					}
					break;
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObstacle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntType = 0; nCntType< MAX_OBSTACLE_TYPE; nCntType++)
	{// ��Q���̎�ނ̐������J��Ԃ�
		for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
		{// ��Q���̐������J��Ԃ�
			if (g_aObstacle[nCntType][nCntObstacle].bUse == true)
			{// ��Q�����g�p����Ă���
			 // ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aObstacle[nCntType][nCntObstacle].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObstacle[nCntType][nCntObstacle].rot.y, g_aObstacle[nCntType][nCntObstacle].rot.x, g_aObstacle[nCntType][nCntObstacle].rot.z);
				D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].mtxWorld, &mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aObstacle[nCntType][nCntObstacle].pos.x, g_aObstacle[nCntType][nCntObstacle].pos.y, g_aObstacle[nCntType][nCntObstacle].pos.z);
				D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].mtxWorld, &mtxTrans);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aObstacle[nCntType][nCntObstacle].mtxWorld);

				for (int nCntVer = 0; nCntVer < 4; nCntVer++)
				{// ���_���̐������J��Ԃ�
				 // ���[���h�}�g���b�N�X�̏�����
					D3DXMatrixIdentity(&g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld);

					// ��]�𔽉f
					D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].rot.y, g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].rot.x, g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].rot.z);
					D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld, &mtxRot);

					// �ʒu�𔽉f
					D3DXMatrixTranslation(&mtxTrans, g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].pos.x, g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].pos.y, g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].pos.z);
					D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld, &mtxTrans);

					// �e�̃}�g���b�N�X���|�����킹��
					D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].mtxWorld);
				}

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatObstacle[nCntType]->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_nNumMatObstacle[nCntType]; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureObstacle[nCntType][nCntMat]);

					// ���f��(�p�[�c)�̕`��
					g_pMeshObstacle[nCntType]->DrawSubset(nCntMat);
				}
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}
//=============================================================================
// ��Q���̐ݒ菈��
//=============================================================================
void SetObstacle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, OBSTACLE_TYPE nType)
{
	for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
	{// ��Q���̐������J��Ԃ�
		if (g_aObstacle[nType][nCntObstacle].bUse == false)
		{// ��Q�����g�p����Ă��Ȃ�
		 // �ʒu�E�����̏����ݒ�
			g_aObstacle[nType][nCntObstacle].pos = pos;
			g_aObstacle[nType][nCntObstacle].rot = rot;
			g_aObstacle[nType][nCntObstacle].move = move;
			//�@�e�̃Z�b�g
			//g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0), 20.0f);

			g_aObstacle[nType][nCntObstacle].Vertex[0].pos = D3DXVECTOR3(g_aObstacle[nType][nCntObstacle].vtxMinObstacle.x - 8.0f, 0.0f, g_aObstacle[nType][nCntObstacle].vtxMaxObstacle.z + 8.0f);
			g_aObstacle[nType][nCntObstacle].Vertex[1].pos = D3DXVECTOR3(g_aObstacle[nType][nCntObstacle].vtxMaxObstacle.x + 8.0f, 0.0f, g_aObstacle[nType][nCntObstacle].vtxMaxObstacle.z + 8.0f);
			g_aObstacle[nType][nCntObstacle].Vertex[2].pos = D3DXVECTOR3(g_aObstacle[nType][nCntObstacle].vtxMaxObstacle.x + 8.0f, 0.0f, g_aObstacle[nType][nCntObstacle].vtxMinObstacle.z - 8.0f);
			g_aObstacle[nType][nCntObstacle].Vertex[3].pos = D3DXVECTOR3(g_aObstacle[nType][nCntObstacle].vtxMinObstacle.x - 8.0f, 0.0f, g_aObstacle[nType][nCntObstacle].vtxMinObstacle.z - 8.0f);

			g_aObstacle[nType][nCntObstacle].bUse = true;
			break;
		}
	}

}

//=============================================================================
// ��Q���̎擾
//=============================================================================
OBSTACLE *GetObstacle(void)
{
	return &g_aObstacle[0][0];
}
//=============================================================================
// ��Q���̓����蔻��
//=============================================================================
bool CollisionObstacle(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius)
{
	bool bLand = false;  // ��������ǂ���

						 // �O�ς̓����蔻��p
	D3DXVECTOR3 vecA, vecC;
	D3DXVECTOR3 aVerPos[4];
	int nCntVec = 0;

	for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
	{// ��Q���̎�ނ����J��Ԃ�
		for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
		{// ��Q���̐������J��Ԃ�
			if (g_aObstacle[nCntType][nCntObstacle].bUse == true)
			{// ��Q�����g�p����Ă���
				nCntVec = 0;
				// ���̃R�[�X�̒��_���W���擾
				aVerPos[0] = D3DXVECTOR3(g_aObstacle[nCntType][nCntObstacle].Vertex[0].mtxWorld._41, g_aObstacle[nCntType][nCntObstacle].Vertex[0].mtxWorld._42, g_aObstacle[nCntType][nCntObstacle].Vertex[0].mtxWorld._43);
				aVerPos[1] = D3DXVECTOR3(g_aObstacle[nCntType][nCntObstacle].Vertex[1].mtxWorld._41, g_aObstacle[nCntType][nCntObstacle].Vertex[1].mtxWorld._42, g_aObstacle[nCntType][nCntObstacle].Vertex[1].mtxWorld._43);
				aVerPos[2] = D3DXVECTOR3(g_aObstacle[nCntType][nCntObstacle].Vertex[2].mtxWorld._41, g_aObstacle[nCntType][nCntObstacle].Vertex[2].mtxWorld._42, g_aObstacle[nCntType][nCntObstacle].Vertex[2].mtxWorld._43);
				aVerPos[3] = D3DXVECTOR3(g_aObstacle[nCntType][nCntObstacle].Vertex[3].mtxWorld._41, g_aObstacle[nCntType][nCntObstacle].Vertex[3].mtxWorld._42, g_aObstacle[nCntType][nCntObstacle].Vertex[3].mtxWorld._43);

				for (int nCntVer = 0; nCntVer < 4; nCntVer++)
				{// ���_���̐������J��Ԃ�
					vecC = *pPos - aVerPos[nCntVer];
					vecA = aVerPos[(nCntVer + 1) % 4] - aVerPos[nCntVer];

					if ((vecA.z * vecC.x) - (vecA.x * vecC.z) < 0)
					{// ���̃x�N�g���̊O���ɂ���
						nCntVec++;
					}
				}

				if (pPos->y <= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y - 5.0f && pPos->y + radius.y >= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y - 5.0f
					|| pPos->y + radius.y >= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y && pPos->y <= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y
					|| pPos->y + radius.y <= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y - 5.0f && pPos->y >= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y)
				{// ��Q����Y���W�̒��ɂ���
					if (nCntVec == 0)
					{// ��x���x�N�g���̊O���ɂ��Ȃ�����
						pPos->x = pPosOld->x;
						pPos->z = pPosOld->z;
						pPos->x -= pMove->x * 0.001f;
						pPos->z -= pMove->z * 0.001f;
						pPos->x += g_aObstacle[nCntType][nCntObstacle].move.x;
						pPos->z += g_aObstacle[nCntType][nCntObstacle].move.z;
					}
				}
				if (pPosOld->y >= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y && pPos->y < g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y
					|| pPos->y <= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y && pPosOld->y > g_aObstacle[nCntType][nCntObstacle].posold.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y
					/*					|| g_aObstacle[nCntType][nCntObstacle].posold.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y <= pPos->y && g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y >= pPos->y && pPos->y >= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y - 20.0f
					|| g_aObstacle[nCntType][nCntObstacle].posold.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y <= pPosOld->y && g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y >= pPosOld->y && pPos->y >= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y - 20.0f*/)
				{// ��Q���̓����ɏ����
					if (nCntVec == 0)
					{// ��x���x�N�g���̊O���ɂ��Ȃ�����
						bLand = true;     // ����������Ԃ�
						pPos->y = g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y + 0.1f;
						pMove->y = 0.0f;  // �ړ��ʂ��Ȃ���
						*pPos += g_aObstacle[nCntType][nCntObstacle].move;
						if (g_aObstacle[nCntType][nCntObstacle].nType == OBSTACLE_TYPE_ROLL_LEFT || g_aObstacle[nCntType][nCntObstacle].nType == OBSTACLE_TYPE_ROLL_RIGHT)
						{// �܂�铮���������Q���Ȃ��
							pPos->x = g_aObstacle[nCntType][nCntObstacle].pos.x - sinf(g_aObstacle[nCntType][nCntObstacle].rot.y) * 1.5f;
							pPos->z = g_aObstacle[nCntType][nCntObstacle].pos.z - cosf(g_aObstacle[nCntType][nCntObstacle].rot.y) * 1.5f;
						}
					}
				}
			}
		}
	}

	return bLand;   // ��������ǂ�����Ԃ�
}
