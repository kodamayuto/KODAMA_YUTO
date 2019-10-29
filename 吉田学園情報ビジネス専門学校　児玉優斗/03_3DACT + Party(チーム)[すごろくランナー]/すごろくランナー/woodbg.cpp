//=============================================================================
//
// �w�i�̖؏��� [woodbg.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "woodBG.h"
#include "input.h"
#include "camera.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WOODBG_NAME0	"data\\MODEL\\wood4.x"			// ��(��)�̃��f����
#define WOODBG_NAME1	"data\\MODEL\\lake.x"			// ��(��)�̃��f����

#define FIELD_SIZE		    (300.0f)							// �t�B�[���h�̑傫��
#define WOODBG_SIZE			(5.0f)								// ���f���̑傫��
#define MAX_WOODBG			(200)
#define MAX_WOODBG_TYPE		(WOODBG_TYPE_MAX)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH		    g_pMeshWoodBG[MAX_WOODBG_TYPE];	              // ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER	    g_pBuffMatWoodBG[MAX_WOODBG_TYPE];	          // �}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9* g_pTextureWoodBG[MAX_WOODBG_TYPE];            // �e�N�X�`�����ւ̃|�C���^
DWORD			    g_nNumMatWoodBG[MAX_WOODBG_TYPE] = { 0,0 }; // �}�e���A�����̐�
WOODBG	        g_aWoodBG[MAX_WOODBG_TYPE][MAX_WOODBG];     // ��Q���̏��
//=============================================================================
// ����������
//=============================================================================
void InitWoodBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	char aXFileName[MAX_WOODBG_TYPE][64] = { WOODBG_NAME0,
		WOODBG_NAME1	,
	};

	for (int nCntType = 0; nCntType < MAX_WOODBG_TYPE; nCntType++)
	{// ��Q���̎�ނ����J��Ԃ�
	 // X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(aXFileName[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatWoodBG[nCntType],
			NULL,
			&g_nNumMatWoodBG[nCntType],
			&g_pMeshWoodBG[nCntType]);

		// �}�e���A����񂩂�e�N�X�`���������o��
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatWoodBG[nCntType]->GetBufferPointer();
		D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_nNumMatWoodBG[nCntType]];
		g_pTextureWoodBG[nCntType] = new LPDIRECT3DTEXTURE9[g_nNumMatWoodBG[nCntType]];

		for (DWORD nCntMat = 0; nCntMat < g_nNumMatWoodBG[nCntType]; nCntMat++)
		{// ���_���̐������J��Ԃ� 
		 // �}�e���A������ǂݍ���
			pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

			// ����������������
			pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

			// �e�N�X�`������������
			g_pTextureWoodBG[nCntType][nCntMat] = NULL;

			// �e�N�X�`���̏���ǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL &&
				lstrlen(pMat[nCntMat].pTextureFilename) > 0)
			{// �e�N�X�`���̃t�@�C����������
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureWoodBG[nCntType][nCntMat]);
			}
		}

		for (int nCntWoodBG = 0; nCntWoodBG < MAX_WOODBG; nCntWoodBG++)
		{// ��Q���̐������J��Ԃ�
		 // ��Q�����̏�����
			g_aWoodBG[nCntType][nCntWoodBG].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ���W��������
			g_aWoodBG[nCntType][nCntWoodBG].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ��������������
			g_aWoodBG[nCntType][nCntWoodBG].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ړ��ʂ���������
			g_aWoodBG[nCntType][nCntWoodBG].nType = (WOODBG_TYPE)nCntType;         // ��ނ���������
			g_aWoodBG[nCntType][nCntWoodBG].bUse = false;                            // �g�p���Ă��Ȃ���Ԃɂ���

			if (nCntWoodBG == 0)
			{// 1��ڂ�������
				int nNumVtx;	 // ���_��
				DWORD sizeFVF;	 // ���_�t�H�[�}�b�g�̃T�C�Y
				BYTE *pVtxBuff;  // ���_�o�b�t�@�ւ̃|�C���^

								 // �ŏ��l�̐ݒ�
				g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
				g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

				// ���_�����擾
				nNumVtx = g_pMeshWoodBG[nCntType]->GetNumVertices();

				// ���_�t�H�[�}�b�g�̃T�C�Y���擾
				sizeFVF = D3DXGetFVFVertexSize(g_pMeshWoodBG[nCntType]->GetFVF());

				// ���_�o�b�t�@�����b�N
				g_pMeshWoodBG[nCntType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{// ���f���̒��_�������J��Ԃ�
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

					if (vtx.x < g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x)
					{// X���W����菬����
						g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x = vtx.x;
					}
					if (vtx.y < g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.y)
					{// Y���W����菬����
						g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.y = vtx.y;
					}
					if (vtx.z < g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z)
					{// Z���W����菬����
						g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z = vtx.z;
					}

					if (vtx.x > g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x)
					{// X���W�����傫��
						g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x = vtx.x;
					}
					if (vtx.y > g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.y)
					{// Y���W�����傫��
						g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.y = vtx.y;
					}
					if (vtx.z > g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z)
					{// Z���W�����傫��
						g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z = vtx.z;
					}

					pVtxBuff += sizeFVF;	// �T�C�Y���|�C���^��i�߂�
				}

				// ���_�o�b�t�@���A�����b�N
				g_pMeshWoodBG[nCntType]->UnlockVertexBuffer();
			}
			else
			{// ����ȍ~
				g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG = g_aWoodBG[nCntType][nCntWoodBG - 1].vtxMaxWoodBG;
				g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG = g_aWoodBG[nCntType][nCntWoodBG - 1].vtxMinWoodBG;
			}
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitWoodBG(void)
{
	for (int nCntType = 0; nCntType < MAX_WOODBG_TYPE; nCntType++)
	{
		// ���b�V���̊J��
		if (g_pMeshWoodBG[nCntType] != NULL)
		{
			g_pMeshWoodBG[nCntType]->Release();
			g_pMeshWoodBG[nCntType] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatWoodBG[nCntType] != NULL)
		{
			g_pBuffMatWoodBG[nCntType]->Release();
			g_pBuffMatWoodBG[nCntType] = NULL;
		}
		// �e�N�X�`���̊J��
		for (DWORD nCntMat = 0; nCntMat < g_nNumMatWoodBG[nCntType]; nCntMat++)
		{
			if (g_pTextureWoodBG[nCntType][nCntMat] != NULL)
			{
				g_pTextureWoodBG[nCntType][nCntMat]->Release();
				g_pTextureWoodBG[nCntType][nCntMat] = NULL;
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWoodBG(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWoodBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntType = 0; nCntType< MAX_WOODBG_TYPE; nCntType++)
	{// ��Q���̎�ނ̐������J��Ԃ�
		for (int nCntWoodBG = 0; nCntWoodBG < MAX_WOODBG; nCntWoodBG++)
		{// ��Q���̐������J��Ԃ�
			if (g_aWoodBG[nCntType][nCntWoodBG].bUse == true)
			{// ��Q�����g�p����Ă���
			 // ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aWoodBG[nCntType][nCntWoodBG].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWoodBG[nCntType][nCntWoodBG].rot.y, g_aWoodBG[nCntType][nCntWoodBG].rot.x, g_aWoodBG[nCntType][nCntWoodBG].rot.z);
				D3DXMatrixMultiply(&g_aWoodBG[nCntType][nCntWoodBG].mtxWorld, &g_aWoodBG[nCntType][nCntWoodBG].mtxWorld, &mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aWoodBG[nCntType][nCntWoodBG].pos.x, g_aWoodBG[nCntType][nCntWoodBG].pos.y, g_aWoodBG[nCntType][nCntWoodBG].pos.z);
				D3DXMatrixMultiply(&g_aWoodBG[nCntType][nCntWoodBG].mtxWorld, &g_aWoodBG[nCntType][nCntWoodBG].mtxWorld, &mtxTrans);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aWoodBG[nCntType][nCntWoodBG].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatWoodBG[nCntType]->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_nNumMatWoodBG[nCntType]; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureWoodBG[nCntType][nCntMat]);

					// ���f��(�p�[�c)�̕`��
					g_pMeshWoodBG[nCntType]->DrawSubset(nCntMat);
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
void SetWoodBG(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, WOODBG_TYPE nType)
{
	for (int nCntWoodBG = 0; nCntWoodBG < MAX_WOODBG; nCntWoodBG++)
	{// ��Q���̐������J��Ԃ�
		if (g_aWoodBG[nType][nCntWoodBG].bUse == false)
		{// ��Q�����g�p����Ă��Ȃ�
		 // �ʒu�E�����̏����ݒ�
			g_aWoodBG[nType][nCntWoodBG].pos = pos;
			g_aWoodBG[nType][nCntWoodBG].rot = rot;
			g_aWoodBG[nType][nCntWoodBG].move = move;
			//�@�e�̃Z�b�g
			//g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0), 20.0f);
			g_aWoodBG[nType][nCntWoodBG].bUse = true;
			break;
		}
	}

}

//=============================================================================
// ��Q���̎擾
//=============================================================================
WOODBG *GetWoodBG(void)
{
	return &g_aWoodBG[0][0];
}
//=============================================================================
// ��Q���̓����蔻��
//=============================================================================
//bool CollisionWoodBG(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius)
//{
//	bool bLand = false;  // ��������ǂ���
//
//	for (int nCntType = 0; nCntType < MAX_WOODBG_TYPE; nCntType++)
//	{// ��Q���̎�ނ����J��Ԃ�
//		for (int nCntWoodBG = 0; nCntWoodBG < MAX_WOODBG; nCntWoodBG++)
//		{// ��Q���̐������J��Ԃ�
//			if (g_aWoodBG[nCntType][nCntWoodBG].bUse == true)
//			{// ��Q�����g�p����Ă���
//				if (pPos->y <= g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.y && pPos->y + radius.y > g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.y
//					|| pPos->y + radius.y > g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.y && pPos->y < g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.y
//					|| pPos->y + radius.y > g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.y && pPos->y < g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.y)
//				{// ��Q����Y���W�̒��ɂ���
//					if (pPos->z - radius.z <= g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z && pPos->z + radius.z >= g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z)
//					{// ��Q����Z���W�̒��ɂ���
//						if (pPosOld->x + radius.x <= g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x
//							&& pPos->x + radius.x > g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x)
//						{// X���W�̒��ɍ����������
//							pPos->x = g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x - radius.x;
//							pMove->x = 0.0f;
//						}
//						else if (pPosOld->x - radius.x >= g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x
//							&& pPos->x - radius.x < g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x)
//						{// X���W�̒��ɉE���������
//							pPos->x = g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x + radius.x + 0.1f;
//							pMove->x = 0.0f;
//						}
//					}
//					if (pPos->x - radius.x <= g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x && pPos->x + radius.x >= g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x)
//					{// ��Q����X���W�̒��ɂ���
//						if (pPosOld->z + radius.z <= g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z
//							&& pPos->z + radius.z > g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z)
//						{// Z���W�̒��ɑO���������
//							pPos->z = g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z - radius.z;
//							pMove->z = 0.0f;
//						}
//						else if (pPosOld->z - radius.z >= g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z
//							&& pPos->z - radius.z < g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z)
//						{// Z���W�̒��Ɍ�납�������
//							pPos->z = g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z + radius.z + 0.1f;
//							pMove->z = 0.0f;
//						}
//					}
//
//					if (pPos->x - radius.x < g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x - 2.0f&& pPos->x + radius.x > g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x + 2.0f
//						&& pPos->z - radius.z <= g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z - 2.0f && pPos->z + radius.z >= g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z + 2.0f)
//					{// ��Q���̓����ɏ����
//						bLand = true;  // ����������Ԃ�
//						pPos->y = g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.y + 0.1f;
//						pMove->y = 0.0f;  // �ړ��ʂ��Ȃ���
//					}
//				}
//			}
//		}
//	}
//
//	return bLand;   // ��������ǂ�����Ԃ�
//}

