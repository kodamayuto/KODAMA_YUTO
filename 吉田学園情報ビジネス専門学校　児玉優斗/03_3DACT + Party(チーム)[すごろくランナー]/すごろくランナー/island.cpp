//=============================================================================
//
// ���f������ [island.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "island.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ISLAND_FILENAME "data/MODEL/island/3d_001_Land000.x"
#define ISLAND_MOVE_SPEED (1.0f)
#define ISLAND_ROTMOVE_COEFFICIENT (0.11f)
#define MAX_NUM_ISLAND (4)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshISLAND[MAX_NUM_ISLAND] = {};		//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatISLAND[MAX_NUM_ISLAND] = {};	//�}�e���A�����ւ̃|�C���^

ISLAND g_ISLAND[MAX_NUM_ISLAND];
//=============================================================================
// ����������
//=============================================================================
void InitIsland(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�t�@�C��������
	g_ISLAND[0].filename = "data/MODEL/island/3d_001_Land000.x";
	g_ISLAND[1].filename = "data/MODEL/island/3d_001_Land001.x";
	g_ISLAND[2].filename = "data/MODEL/island/3d_001_Land002.x";
	g_ISLAND[3].filename = "data/MODEL/island/3d_001_Land003.x";

	for (int nCntNpc = 0; nCntNpc < MAX_NUM_ISLAND; nCntNpc++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(g_ISLAND[nCntNpc].filename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatISLAND[nCntNpc],
			NULL,
			&g_ISLAND[nCntNpc].nNumMatISLAND,
			&g_pMeshISLAND[nCntNpc]);

		// �����̏����ݒ�
		g_ISLAND[nCntNpc].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�ړ��ʁE��]�ʂ̏�����
		g_ISLAND[nCntNpc].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ISLAND[nCntNpc].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	g_ISLAND[0].pos = D3DXVECTOR3(-200.0f, 0.0f, 200.0f);
	g_ISLAND[1].pos = D3DXVECTOR3(200.0f, 0.0f, 200.0f);
	g_ISLAND[2].pos = D3DXVECTOR3(-200.0f, 0.0f, -200.0f);
	g_ISLAND[3].pos = D3DXVECTOR3(200.0f, 0.0f, -200.0f);

	g_ISLAND[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_ISLAND[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_ISLAND[2].rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);
	g_ISLAND[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//=============================================================================
// �I������
//=============================================================================
void UninitIsland(void)
{
	// ���b�V���̉��
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_ISLAND; nCntMesh++)
	{
		if (g_pMeshISLAND[nCntMesh] != NULL)
		{
			g_pMeshISLAND[nCntMesh]->Release();
			g_pMeshISLAND[nCntMesh] = NULL;
		}
		/*�e�N�X�`���̉��*/
		//�}�e���A���̉��
		if (g_pBuffMatISLAND[nCntMesh] != NULL)
		{
			g_pBuffMatISLAND[nCntMesh]->Release();
			g_pBuffMatISLAND[nCntMesh] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateIsland(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawIsland(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^

	for (int nCntNpc = 0; nCntNpc < MAX_NUM_ISLAND; nCntNpc++)
	{
		//if (g_ISLAND[nCntNpc].bUse == true)
		//{

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_ISLAND[nCntNpc].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_ISLAND[nCntNpc].rot.y,
				g_ISLAND[nCntNpc].rot.x,
				g_ISLAND[nCntNpc].rot.z);

			D3DXMatrixMultiply(&g_ISLAND[nCntNpc].mtxWorld,
				&g_ISLAND[nCntNpc].mtxWorld,
				&mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_ISLAND[nCntNpc].pos.x,
				g_ISLAND[nCntNpc].pos.y,
				g_ISLAND[nCntNpc].pos.z);

			D3DXMatrixMultiply(&g_ISLAND[nCntNpc].mtxWorld,
				&g_ISLAND[nCntNpc].mtxWorld,
				&mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_ISLAND[nCntNpc].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatISLAND[nCntNpc]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ISLAND[nCntNpc].nNumMatISLAND; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				/*�e�N�X�`���̐ݒ�*/
				pDevice->SetTexture(0, NULL);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

				// ���f��(�p�[�c)�̕`��
				g_pMeshISLAND[nCntNpc]->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		//}
	}
}
