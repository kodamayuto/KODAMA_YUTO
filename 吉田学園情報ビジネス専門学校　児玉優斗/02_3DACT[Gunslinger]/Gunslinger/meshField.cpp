//=============================================================================
//
// �|���S������ [MeshField.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "meshField.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_FILENAME0 "data/TEXTURE/field000.jpg"
#define MAX_MESHFIELD (1)

#define MESH_BLOCK_WIDTH (4)
#define MESH_BLOCK_DEPTH (4)

#define MESH_WIDTH (1000.0f)
#define MESH_DEPTH (1000.0f)

//****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshField= NULL;	    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;

MESHFIELD g_MeshField[2];

//=============================================================================
// ����������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_FILENAME0, &g_pTextureMeshField);

	MakeVertexMeshField(pDevice);

	//�\���̂̏�����
	for (int nCntMesh = 0; nCntMesh < MAX_MESHFIELD; nCntMesh++)
	{
		g_MeshField[nCntMesh].pos = D3DXVECTOR3(0.0f + (100.0f * nCntMesh), 0.0f, 0.0f);
		g_MeshField[nCntMesh].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshField[nCntMesh].bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
		if (g_pTextureMeshField != NULL)
		{
			g_pTextureMeshField->Release();
			g_pTextureMeshField = NULL;
		}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	for (int nCntMesh = 0; nCntMesh < MAX_MESHFIELD; nCntMesh++)
	{

		g_MeshField[nCntMesh].nNumPolygon = (MESH_BLOCK_WIDTH * MESH_BLOCK_DEPTH * 2) + (4 * (MESH_BLOCK_DEPTH - 1));
		// ���[���h�}�g���b�N�X�̏�����
		// �|���S���̕`��
		D3DXMatrixIdentity(&g_MeshField[nCntMesh].g_mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_MeshField[nCntMesh].rot.y,
			g_MeshField[nCntMesh].rot.x,
			g_MeshField[nCntMesh].rot.z);

		D3DXMatrixMultiply(&g_MeshField[nCntMesh].g_mtxWorld,
			&g_MeshField[nCntMesh].g_mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_MeshField[nCntMesh].pos.x,
			g_MeshField[nCntMesh].pos.y,
			g_MeshField[nCntMesh].pos.z);

		D3DXMatrixMultiply(&g_MeshField[nCntMesh].g_mtxWorld,
			&g_MeshField[nCntMesh].g_mtxWorld,
			&mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshField[nCntMesh].g_mtxWorld);

		pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffMeshField);

		pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

			// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshField);//�e�N�X�`���̐ݒ�

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			g_MeshField[nCntMesh].nNumVertex,
			0,
			g_MeshField[nCntMesh].nNumPolygon);
	}
}


//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntMesh = 0; nCntMesh < MAX_MESHFIELD; nCntMesh++)
	{

		g_MeshField[nCntMesh].nNumVertex = (MESH_BLOCK_DEPTH + 1) * (MESH_BLOCK_WIDTH + 1);
		g_MeshField[nCntMesh].nNumIndex = (MESH_BLOCK_WIDTH * MESH_BLOCK_DEPTH * 2) + (4 * (MESH_BLOCK_DEPTH - 1)) + 2;

		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_MeshField[nCntMesh].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMeshField,
			NULL);

		//�C���f�b�N�X�o�b�t�@�̐���
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_MeshField[nCntMesh].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIdxBuffMeshField,
			NULL);

		//�ϐ��錾
		VERTEX_3D *pVtx;	//���_���ւ̃|�C���^


		for (int nCntDepth = 0; nCntDepth < MESH_BLOCK_DEPTH + 1; nCntDepth++)
		{
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (MESH_BLOCK_WIDTH + 1) * nCntDepth;
			for (int nCntWidth = 0; nCntWidth < MESH_BLOCK_WIDTH + 1; nCntWidth++)
			{
				pVtx[nCntWidth].pos = D3DXVECTOR3(-MESH_WIDTH + ((MESH_WIDTH / (MESH_BLOCK_WIDTH / 2.0f)) * nCntWidth),
					0.0f,
					MESH_DEPTH - ((MESH_DEPTH / (MESH_BLOCK_DEPTH / 2.0f))* nCntDepth));

				pVtx[nCntWidth].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[nCntWidth].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntWidth].tex = D3DXVECTOR2(nCntWidth * 1.0f,nCntDepth * 1.0f);
				//pVtx[nCntWidth].tex = D3DXVECTOR2(((1.0f / MESH_BLOCK_WIDTH) * nCntWidth), ((1.0f / MESH_BLOCK_DEPTH) * nCntDepth));
			}
			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffMeshField->Unlock();
		}


		//�C���f�b�N�X�f�[�^�̐ݒ�
		WORD *Idx;			//�C���f�b�N�X�f�[�^�ւ̃|�C���^
		bool flag = false;
		//�C���f�b�N�X�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pIdxBuffMeshField->Lock(0, 0, (void**)&Idx, 0);
		for (int nCntIdxDepth = 0; nCntIdxDepth < MESH_BLOCK_DEPTH; nCntIdxDepth++)
		{
			for (int nCntIdxWidth = 0; nCntIdxWidth < MESH_BLOCK_WIDTH + 1; nCntIdxWidth++)
			{
				Idx[0] = nCntIdxWidth + ((MESH_BLOCK_WIDTH + 1) * (nCntIdxDepth + 1));

				if (flag == true)
				{//�k�ރ|���S���̏����i���j
					Idx[1] = Idx[0];
					Idx[2] = nCntIdxWidth + ((MESH_BLOCK_WIDTH + 1) * (nCntIdxDepth));
					Idx += 3;
					flag = false;
				}
				else
				{//�k�ރ|���S���łȂ����

					Idx[1] = nCntIdxWidth + ((MESH_BLOCK_WIDTH + 1) * (nCntIdxDepth));
					Idx += 2;
				}

				if (Idx[-1] % (MESH_BLOCK_WIDTH + 1) == MESH_BLOCK_WIDTH && flag == false)
				{//�k�ރ|���S���̏����i��j
					Idx[0] = Idx[-1];
					Idx += 1;
					flag = true;
				}
			}
		}
		//�C���f�b�N�X�o�b�t�@���A�����b�N����
		g_pIdxBuffMeshField->Unlock();
	}


}


