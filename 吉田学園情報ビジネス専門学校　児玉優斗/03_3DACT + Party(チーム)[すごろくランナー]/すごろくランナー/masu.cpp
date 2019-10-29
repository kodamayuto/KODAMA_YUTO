//=============================================================================
//
// ���f������ [model.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "masu.h"
#include "input.h"
#include "camera.h"
#include "game.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MASU_NAME0	"data\\MODEL\\trout\\jumpUP.x"      // �}�X�̃��f����(�W�����v�͏㏸�}�X)
#define MASU_NAME1	"data\\MODEL\\trout\\jumpDOWN.x"    // �}�X�̃��f����(�W�����v�͌����}�X)
#define MASU_NAME2	"data\\MODEL\\trout\\speedUP.x"     // �}�X�̃��f����(�ړ��͏㏸�}�X)
#define MASU_NAME3	"data\\MODEL\\trout\\speedDOWN.x"     // �}�X�̃��f����(�ړ��͌����}�X)
#define MASU_NAME4	"data\\MODEL\\trout\\saikoroUP.x"   // �}�X�̃��f����(�T�C�R���Q�{�}�X)
#define MASU_NAME5	"data\\MODEL\\trout\\trampoline.x"  // �}�X�̃��f����(�W�����v��}�X)
#define MASU_NAME6	"data\\MODEL\\trout\\masu.x"  // �}�X�̃��f����(�ʏ�}�X)
#define MASU_NAME7	"data\\MODEL\\trout\\3d_001_Goal000.x"  // �}�X�̃��f����(�S�[���}�X)
#define MASU_NAME8	"data\\MODEL\\trout\\start.x"  // �}�X�̃��f����(�X�^�[�g�}�X)
#define MAX_MASU		(50)
#define MAX_MASU_TYPE		(MASUTYPE_MAX)

// ���a147

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH		g_pMeshMasu[MASUTYPE_MAX];		  // ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER	g_pBuffMatMasu[MASUTYPE_MAX];	  // �}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9* g_pTextureMasu[MASUTYPE_MAX]; // �e�N�X�`�����ւ̃|�C���^
DWORD			g_nNumMatMasu[MASUTYPE_MAX];      // �}�e���A�����̐�
MASU			g_Masu[MASUTYPE_MAX][MAX_MASU];   // �}�X�̏��

												  //=============================================================================
												  // ����������
												  //=============================================================================
void InitMasu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// x�t�@�C���̃f�[�^��ǂݍ��ނ��߂Ɏg�p
	char aXFileName[MASUTYPE_MAX][64] = {
		MASU_NAME0,
		MASU_NAME1,
		MASU_NAME2,
		MASU_NAME3,
		MASU_NAME4,
		MASU_NAME5,
		MASU_NAME6,
		MASU_NAME7,
		MASU_NAME8,
	};

	for (int nCntType = 0; nCntType < MAX_MASU_TYPE; nCntType++)
	{// ��Q���̎�ނ����J��Ԃ�
	 // X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(aXFileName[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatMasu[nCntType],
			NULL,
			&g_nNumMatMasu[nCntType],
			&g_pMeshMasu[nCntType]);

		// �}�e���A����񂩂�e�N�X�`���������o��
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatMasu[nCntType]->GetBufferPointer();
		D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_nNumMatMasu[nCntType]];
		g_pTextureMasu[nCntType] = new LPDIRECT3DTEXTURE9[g_nNumMatMasu[nCntType]];

		for (DWORD nCntMat = 0; nCntMat < g_nNumMatMasu[nCntType]; nCntMat++)
		{// ���_���̐������J��Ԃ� 
		 // �}�e���A������ǂݍ���
			pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

			// ����������������
			pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

			// �e�N�X�`������������
			g_pTextureMasu[nCntType][nCntMat] = NULL;

			// �e�N�X�`���̏���ǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL &&
				lstrlen(pMat[nCntMat].pTextureFilename) > 0)
			{// �e�N�X�`���̃t�@�C����������
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureMasu[nCntType][nCntMat]);
			}
		}

		for (int nCntMasu = 0; nCntMasu < MAX_MASU; nCntMasu++)
		{// ��Q���̐������J��Ԃ�
		 // ��Q�����̏�����
			g_Masu[nCntType][nCntMasu].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ���W��������
			g_Masu[nCntType][nCntMasu].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ��������������
			g_Masu[nCntType][nCntMasu].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ړ��ʂ���������
			g_Masu[nCntType][nCntMasu].masuType = (MASUTYPE)nCntType;         // ��ނ���������
			g_Masu[nCntType][nCntMasu].bUse = false;                            // �g�p���Ă��Ȃ���Ԃɂ���

			if (nCntMasu == 0)
			{// 1��ڂ�������
				int nNumVtx;	 // ���_��
				DWORD sizeFVF;	 // ���_�t�H�[�}�b�g�̃T�C�Y
				BYTE *pVtxBuff;  // ���_�o�b�t�@�ւ̃|�C���^

								 // �ŏ��l�̐ݒ�
				g_Masu[nCntType][nCntMasu].vtxMinMasu = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
				g_Masu[nCntType][nCntMasu].vtxMaxMasu = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

				// ���_�����擾
				nNumVtx = g_pMeshMasu[nCntType]->GetNumVertices();

				// ���_�t�H�[�}�b�g�̃T�C�Y���擾
				sizeFVF = D3DXGetFVFVertexSize(g_pMeshMasu[nCntType]->GetFVF());

				// ���_�o�b�t�@�����b�N
				g_pMeshMasu[nCntType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{// ���f���̒��_�������J��Ԃ�
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

					if (vtx.x < g_Masu[nCntType][nCntMasu].vtxMinMasu.x)
					{// X���W����菬����
						g_Masu[nCntType][nCntMasu].vtxMinMasu.x = vtx.x;
					}
					if (vtx.y < g_Masu[nCntType][nCntMasu].vtxMinMasu.y)
					{// Y���W����菬����
						g_Masu[nCntType][nCntMasu].vtxMinMasu.y = vtx.y;
					}
					if (vtx.z < g_Masu[nCntType][nCntMasu].vtxMinMasu.z)
					{// Z���W����菬����
						g_Masu[nCntType][nCntMasu].vtxMinMasu.z = vtx.z;
					}

					if (vtx.x > g_Masu[nCntType][nCntMasu].vtxMaxMasu.x)
					{// X���W�����傫��
						g_Masu[nCntType][nCntMasu].vtxMaxMasu.x = vtx.x;
					}
					if (vtx.y > g_Masu[nCntType][nCntMasu].vtxMaxMasu.y)
					{// Y���W�����傫��
						g_Masu[nCntType][nCntMasu].vtxMaxMasu.y = vtx.y;
					}
					if (vtx.z > g_Masu[nCntType][nCntMasu].vtxMaxMasu.z)
					{// Z���W�����傫��
						g_Masu[nCntType][nCntMasu].vtxMaxMasu.z = vtx.z;
					}

					pVtxBuff += sizeFVF;	// �T�C�Y���|�C���^��i�߂�
				}

				// ���_�o�b�t�@���A�����b�N
				g_pMeshMasu[nCntType]->UnlockVertexBuffer();
			}
			else
			{// ����ȍ~
				g_Masu[nCntType][nCntMasu].vtxMaxMasu = g_Masu[nCntType][nCntMasu - 1].vtxMaxMasu;
				g_Masu[nCntType][nCntMasu].vtxMinMasu = g_Masu[nCntType][nCntMasu - 1].vtxMinMasu;
			}
		}
	}

}

//=============================================================================
// �I������
//=============================================================================
void UninitMasu(void)
{
	for (int nCntType = 0; nCntType < MASUTYPE_MAX; nCntType++)
	{// �}�X�̎�ނ����J��Ԃ�
	 // ���b�V���̊J��
		if (g_pMeshMasu[nCntType] != NULL)
		{
			g_pMeshMasu[nCntType]->Release();
			g_pMeshMasu[nCntType] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatMasu[nCntType] != NULL)
		{
			g_pBuffMatMasu[nCntType]->Release();
			g_pBuffMatMasu[nCntType] = NULL;
		}
		//�e�N�X�`���̊J��
		for (DWORD nCntMat = 0; nCntMat < g_nNumMatMasu[nCntType]; nCntMat++)
		{
			if (g_pTextureMasu[nCntType][nCntMat] != NULL)
			{
				g_pTextureMasu[nCntType][nCntMat]->Release();
				g_pTextureMasu[nCntType][nCntMat] = NULL;
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMasu(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMasu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntType = 0; nCntType < MASUTYPE_MAX; nCntType++)
	{// �}�X�̎�ނ����J��Ԃ�
		for (int nCntMasu = 0; nCntMasu < MAX_MASU; nCntMasu++)
		{// �}�X�̐������J��Ԃ�
			if (g_Masu[nCntType][nCntMasu].bUse == true)
			{// �}�X���g�p����Ă���
			 // ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Masu[nCntType][nCntMasu].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Masu[nCntType][nCntMasu].rot.y, g_Masu[nCntType][nCntMasu].rot.x, g_Masu[nCntType][nCntMasu].rot.z);
				D3DXMatrixMultiply(&g_Masu[nCntType][nCntMasu].mtxWorld, &g_Masu[nCntType][nCntMasu].mtxWorld, &mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_Masu[nCntType][nCntMasu].pos.x, g_Masu[nCntType][nCntMasu].pos.y, g_Masu[nCntType][nCntMasu].pos.z);
				D3DXMatrixMultiply(&g_Masu[nCntType][nCntMasu].mtxWorld, &g_Masu[nCntType][nCntMasu].mtxWorld, &mtxTrans);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Masu[nCntType][nCntMasu].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatMasu[nCntType]->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_nNumMatMasu[nCntType]; nCntMat++)
				{// �}�e���A�����̐������J��Ԃ�
				 // �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureMasu[nCntType][nCntMat]);

					// ���f��(�p�[�c)�̕`��
					g_pMeshMasu[nCntType]->DrawSubset(nCntMat);

				}
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=============================================================================
// �}�X�̓����蔻��
//=============================================================================
bool CollisionMasu(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius, MASU **pMasu)
{
	bool bLand = false;  // ��������ǂ���

	D3DXVECTOR3 fData;
	D3DXVECTOR3 fData1(147.0f, 0.0f, 147.0f);
	float fLength;

	for (int nCntType = 0; nCntType < MAX_MASU_TYPE; nCntType++)
	{// ��Q���̎�ނ����J��Ԃ�
		for (int nCntMasu = 0; nCntMasu < MAX_MASU; nCntMasu++)
		{// ��Q���̐������J��Ԃ�
			if (g_Masu[nCntType][nCntMasu].bUse == true)
			{// ��Q�����g�p����Ă���
				fData = *pPos - g_Masu[nCntType][nCntMasu].pos;

				fLength = sqrtf((fData.x * fData.x) + (fData.z * fData.z));

				//// ���K��
				//D3DXVec3Normalize(&fData, &fData);

				//if (fData1.x * fData.x > fData2.x/* && fData1.z * fData.z > fData2.z*/)
				//{
				//	bLand = true;  // ����������Ԃ�
				//	pPos->y = g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y;
				//	pMove->y = 0.0f;  // �ړ��ʂ��Ȃ���
				//	*pMasu = &g_Masu[nCntType][nCntMasu];
				//}

				if (pPos->y <= g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y && pPos->y + radius.y > g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMinMasu.y
					|| pPos->y + radius.y > g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y && pPos->y < g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMinMasu.y
					|| pPos->y + radius.y > g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y && pPos->y < g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMinMasu.y)
				{// ��Q����Y���W�̒��ɂ���
				 //	if (pPos->z - radius.z <= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z && pPos->z + radius.z >= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z)
				 //	{// ��Q����Z���W�̒��ɂ���
				 //		if (pPosOld->x + radius.x <= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x
				 //			&& pPos->x + radius.x > g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x)
				 //		{// X���W�̒��ɍ����������
				 //			pPos->x = g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x - radius.x;
				 //			pMove->x = 0.0f;
				 //		}
				 //		else if (pPosOld->x - radius.x >= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x
				 //			&& pPos->x - radius.x < g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x)
				 //		{// X���W�̒��ɉE���������
				 //			pPos->x = g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x + radius.x + 0.1f;
				 //			pMove->x = 0.0f;
				 //		}
				 //	}
				 //	if (pPos->x - radius.x <= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x && pPos->x + radius.x >= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x)
				 //	{// ��Q����X���W�̒��ɂ���
				 //		if (pPosOld->z + radius.z <= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z
				 //			&& pPos->z + radius.z > g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z)
				 //		{// Z���W�̒��ɑO���������
				 //			pPos->z = g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z - radius.z;
				 //			pMove->z = 0.0f;
				 //		}
				 //		else if (pPosOld->z - radius.z >= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z
				 //			&& pPos->z - radius.z < g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z)
				 //		{// Z���W�̒��Ɍ�납�������
				 //			pPos->z = g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z + radius.z + 0.1f;
				 //			pMove->z = 0.0f;
				 //		}
				 //	}

				 //	if (pPos->x - radius.x < g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x - 2.0f&& pPos->x + radius.x > g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x + 2.0f
				 //		&& pPos->z - radius.z <= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z - 2.0f && pPos->z + radius.z >= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z + 2.0f)
				 //	{// ��Q���̓����ɏ����
				 //		bLand = true;  // ����������Ԃ�
				 //		pPos->y = g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y;
				 //		pMove->y = 0.0f;  // �ړ��ʂ��Ȃ���
				 //		*pMasu = &g_Masu[nCntType][nCntMasu];
				 //	}
				 //}

				 //if (pPos->y <= g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y && pPos->y + radius.y > g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMinMasu.y
				 //	|| pPos->y + radius.y > g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y && pPos->y < g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMinMasu.y
				 //	|| pPos->y + radius.y > g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y && pPos->y < g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMinMasu.y)
				 //{// ��Q����Y���W�̒��ɂ���
				 //	if (pPos->z - radius.z <= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z && pPos->z + radius.z >= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z)
				 //	{// ��Q����Z���W�̒��ɂ���
				 //		if (pPosOld->x + radius.x <= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x
				 //			&& pPos->x + radius.x > g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x)
				 //		{// X���W�̒��ɍ����������
				 //			pPos->x = g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x - radius.x;
				 //			pMove->x = 0.0f;
				 //		}
				 //		else if (pPosOld->x - radius.x >= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x
				 //			&& pPos->x - radius.x < g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x)
				 //		{// X���W�̒��ɉE���������
				 //			pPos->x = g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x + radius.x + 0.1f;
				 //			pMove->x = 0.0f;
				 //		}
				 //	}
				 //	if (pPos->x - radius.x <= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x && pPos->x + radius.x >= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x)
				 //	{// ��Q����X���W�̒��ɂ���
				 //		if (pPosOld->z + radius.z <= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z
				 //			&& pPos->z + radius.z > g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z)
				 //		{// Z���W�̒��ɑO���������
				 //			pPos->z = g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z - radius.z;
				 //			pMove->z = 0.0f;
				 //		}
				 //		else if (pPosOld->z - radius.z >= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z
				 //			&& pPos->z - radius.z < g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z)
				 //		{// Z���W�̒��Ɍ�납�������
				 //			pPos->z = g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z + radius.z + 0.1f;
				 //			pMove->z = 0.0f;
				 //		}
				 //	}

				 //if (pPos->x - radius.x < g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x - 2.0f&& pPos->x + radius.x > g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x + 2.0f
				 //	&& pPos->z - radius.z <= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z - 2.0f && pPos->z + radius.z >= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z + 2.0f)
				 //{// ��Q���̓����ɏ����
				 //	bLand = true;  // ����������Ԃ�
				 //	pPos->y = g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y;
				 //	pMove->y = 0.0f;  // �ړ��ʂ��Ȃ���
				 //	*pMasu = &g_Masu[nCntType][nCntMasu];
				 //}

					if (fLength < 134)
					{// ��Q���̓����ɏ����
						bLand = true;  // ����������Ԃ�
						pPos->y = g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y;
						pMove->y = 0.0f;  // �ړ��ʂ��Ȃ���
						*pMasu = &g_Masu[nCntType][nCntMasu];
					}
				}
			}
		}
	}

	return bLand;   // ��������ǂ�����Ԃ�
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetMasu(D3DXVECTOR3 pos, MASUTYPE Type)
{
	for (int nCntMasu = 0; nCntMasu < MAX_MASU; nCntMasu++)
	{// �}�X�̐������J��Ԃ�
		if (g_Masu[Type][nCntMasu].bUse == false)
		{// �}�X���g�p����Ă��Ȃ�
			g_Masu[Type][nCntMasu].pos = pos;    // ���W��ݒ�
			g_Masu[Type][nCntMasu].bUse = true;  // �g�p����Ă����Ԃɂ���
			break;
		}
	}
}

//=============================================================================
// ��ԋ߂��}�X�̎擾
//=============================================================================
D3DXVECTOR3 PlayerDistance(void)
{
	return g_Masu[MASUTYPE_GOAL][0].pos;
}

//=============================================================================
// �}�X�̎擾
//=============================================================================
MASU *GetMasu(void)
{
	return &g_Masu[0][0];
}