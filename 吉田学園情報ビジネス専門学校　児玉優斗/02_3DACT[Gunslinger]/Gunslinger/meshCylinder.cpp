//=============================================================================
//
// �|���S������ [MeshCylinder.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "meshCylinder.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHCYLINDER_FILENAME0 "data/TEXTURE/thK0A5DS5J.jpg"
#define MAX_MESHCYLINDER (2)

#define MESH_BLOCK_WIDTH (100)
#define MESH_BLOCK_HAIGHT (1)

#define MESH_WIDTH (1500.0f)
#define MESH_HAIGHT (1000.0f)

//****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder= NULL;	    //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;

MESHCYLINDER g_MeshCylinder[MAX_MESHCYLINDER];

//=============================================================================
// ����������
//=============================================================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, MESHCYLINDER_FILENAME0, &g_pTextureMeshCylinder);

	MakeVertexMeshCylinder(pDevice);

	//�\���̂̏�����
	for (int nCntMesh = 0; nCntMesh < MAX_MESHCYLINDER; nCntMesh++)
	{
		g_MeshCylinder[nCntMesh].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshCylinder[nCntMesh].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshCylinder[nCntMesh].bUse = false;
	}

}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshCylinder(void)
{
		if (g_pTextureMeshCylinder != NULL)
		{
			g_pTextureMeshCylinder->Release();
			g_pTextureMeshCylinder = NULL;
		}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshCylinder(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_MESHCYLINDER; nCntMesh++)
	{
		g_MeshCylinder[nCntMesh].rot.y += 0.0005f;

		RotOverwhelming(g_MeshCylinder[nCntMesh].rot.y);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	for (int nCntMesh = 0; nCntMesh < MAX_MESHCYLINDER; nCntMesh++)
	{

		g_MeshCylinder[nCntMesh].nNumPolygon = (MESH_BLOCK_WIDTH * MESH_BLOCK_HAIGHT * 2) + (4 * (MESH_BLOCK_HAIGHT - 1));
		// ���[���h�}�g���b�N�X�̏�����
		// �|���S���̕`��
		D3DXMatrixIdentity(&g_MeshCylinder[nCntMesh].g_mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_MeshCylinder[nCntMesh].rot.y,
			g_MeshCylinder[nCntMesh].rot.x,
			g_MeshCylinder[nCntMesh].rot.z);

		D3DXMatrixMultiply(&g_MeshCylinder[nCntMesh].g_mtxWorld,
			&g_MeshCylinder[nCntMesh].g_mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_MeshCylinder[nCntMesh].pos.x,
			g_MeshCylinder[nCntMesh].pos.y,
			g_MeshCylinder[nCntMesh].pos.z);

		D3DXMatrixMultiply(&g_MeshCylinder[nCntMesh].g_mtxWorld,
			&g_MeshCylinder[nCntMesh].g_mtxWorld,
			&mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshCylinder[nCntMesh].g_mtxWorld);

		pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffMeshCylinder);

		pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

			// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshCylinder);//�e�N�X�`���̐ݒ�

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			g_MeshCylinder[nCntMesh].nNumVertex,
			0,
			g_MeshCylinder[nCntMesh].nNumPolygon);
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}


//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vecNor;		//�@���̐��K���p

	for (int nCntMesh = 0; nCntMesh < MAX_MESHCYLINDER; nCntMesh++)
	{

		g_MeshCylinder[nCntMesh].nNumVertex = (MESH_BLOCK_HAIGHT + 1) * (MESH_BLOCK_WIDTH + 1);
		g_MeshCylinder[nCntMesh].nNumIndex = (MESH_BLOCK_WIDTH * MESH_BLOCK_HAIGHT * 2) + (4 * (MESH_BLOCK_HAIGHT - 1)) + 2;

		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_MeshCylinder[nCntMesh].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMeshCylinder,
			NULL);

		pDevice->CreateIndexBuffer(sizeof(WORD) * g_MeshCylinder[nCntMesh].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIdxBuffMeshCylinder,
			NULL);

		//�ϐ��錾
		VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

		for (int nCntHaight = 0; nCntHaight < MESH_BLOCK_HAIGHT + 1; nCntHaight++)
		{
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (MESH_BLOCK_WIDTH + 1) * nCntHaight;
			for (int nCntWidth = 0; nCntWidth < MESH_BLOCK_WIDTH + 1; nCntWidth++)
			{
				pVtx[nCntWidth].pos = D3DXVECTOR3(sinf(((D3DX_PI * 2.0f)/ MESH_BLOCK_WIDTH) * nCntWidth) * MESH_WIDTH,
					MESH_HAIGHT - ((MESH_HAIGHT / MESH_BLOCK_HAIGHT) * nCntHaight),
					cosf(((D3DX_PI * 2.0f) / MESH_BLOCK_WIDTH) * nCntWidth) * MESH_WIDTH);

				D3DXVec3Normalize(&vecNor, &pVtx[nCntWidth].pos);

				pVtx[nCntWidth].nor.x = vecNor.x;
				pVtx[nCntWidth].nor.y = 0.0f;
				pVtx[nCntWidth].nor.z = vecNor.z;

				pVtx[nCntWidth].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntWidth].tex = D3DXVECTOR2((1.0f / MESH_BLOCK_WIDTH) * nCntWidth, (1.0f / MESH_BLOCK_HAIGHT) * nCntHaight);
			}
			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffMeshCylinder->Unlock();

		}

		//�C���f�b�N�X�o�b�t�@�̐���

		//�C���f�b�N�X�f�[�^�̐ݒ�
		WORD *Idx;			//�C���f�b�N�X�f�[�^�ւ̃|�C���^
		bool flag = false;
		//�C���f�b�N�X�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&Idx, 0);
		for (int nCntIdxHaight = 0; nCntIdxHaight < MESH_BLOCK_HAIGHT; nCntIdxHaight++)
		{
			for (int nCntIdxWidth = 0; nCntIdxWidth < MESH_BLOCK_WIDTH + 1; nCntIdxWidth++)
			{
				Idx[0] = nCntIdxWidth + ((MESH_BLOCK_WIDTH + 1) * (nCntIdxHaight + 1));

				if (flag == true)
				{//�k�ރ|���S���̏����i���j
					Idx[1] = Idx[0];
					Idx[2] = nCntIdxWidth + ((MESH_BLOCK_WIDTH + 1) * (nCntIdxHaight));
					Idx += 3;
					flag = false;
				}
				else
				{//�k�ރ|���S���łȂ����

					Idx[1] = nCntIdxWidth + ((MESH_BLOCK_WIDTH + 1) * (nCntIdxHaight));
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
		g_pIdxBuffMeshCylinder->Unlock();

	}


}


