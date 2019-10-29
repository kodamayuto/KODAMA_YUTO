//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "polygon.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POLYGON_FILENAME0 "data/TEXTURE/field000.jpg"
#define POLYGON_FILENAME1 "data/TEXTURE/wall000.jpg"
#define MAX_POLYGON (1)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePolygon[2] = {};	    //�e�N�X�`���ւ̃|�C���^

POLYGON g_Polygon[MAX_POLYGON];

//=============================================================================
// ����������
//=============================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, POLYGON_FILENAME0, &g_pTexturePolygon[0]);
	D3DXCreateTextureFromFile(pDevice, POLYGON_FILENAME1, &g_pTexturePolygon[1]);

	MakeVertexPolygon(pDevice);

	//�\���̂̏�����
	for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
	{
		g_Polygon[nCntPolygon].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Polygon[nCntPolygon].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Polygon[nCntPolygon].bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{
	// ���_�o�b�t�@�̊J��
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTexturePolygon[nCntTex] != NULL)
		{
			g_pTexturePolygon[nCntTex]->Release();
			g_pTexturePolygon[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	// ���[���h�}�g���b�N�X�̏�����
	// �|���S���̕`��
	for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
	{
		if (g_Polygon[nCntPolygon].bUse == true)
		{
			D3DXMatrixIdentity(&g_Polygon[nCntPolygon].g_mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Polygon[nCntPolygon].rot.y,
				g_Polygon[nCntPolygon].rot.x,
				g_Polygon[nCntPolygon].rot.z);

			D3DXMatrixMultiply(&g_Polygon[nCntPolygon].g_mtxWorld,
				&g_Polygon[nCntPolygon].g_mtxWorld,
				&mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Polygon[nCntPolygon].pos.x,
				g_Polygon[nCntPolygon].pos.y,
				g_Polygon[nCntPolygon].pos.z);

			D3DXMatrixMultiply(&g_Polygon[nCntPolygon].g_mtxWorld,
				&g_Polygon[nCntPolygon].g_mtxWorld,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Polygon[nCntPolygon].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

				// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePolygon[g_Polygon[nCntPolygon].type]);//�e�N�X�`���̐ݒ�

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
				4 * nCntPolygon,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// �|���S���̐ݒ�
//=============================================================================
void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot,POLYGONTYPE type, float fWidth ,float fDepth)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
	{
		if (g_Polygon[nCntPolygon].bUse == false)
		{
			g_Polygon[nCntPolygon].pos = pos;
			g_Polygon[nCntPolygon].rot = rot;
			g_Polygon[nCntPolygon].fWidth = fWidth; 
			g_Polygon[nCntPolygon].fDepth = fDepth;
			g_Polygon[nCntPolygon].type = type;
			

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntPolygon;
			switch (g_Polygon[nCntPolygon].type)
			{
			case POLYGONTYPE_FIELD:
				pVtx[0].pos = D3DXVECTOR3(-g_Polygon[nCntPolygon].fWidth, 0.0f, g_Polygon[nCntPolygon].fDepth);
				pVtx[1].pos = D3DXVECTOR3(g_Polygon[nCntPolygon].fWidth, 0.0f, g_Polygon[nCntPolygon].fDepth);
				pVtx[2].pos = D3DXVECTOR3(-g_Polygon[nCntPolygon].fWidth, 0.0f, -g_Polygon[nCntPolygon].fDepth);
				pVtx[3].pos = D3DXVECTOR3(g_Polygon[nCntPolygon].fWidth, 0.0f, -g_Polygon[nCntPolygon].fDepth);

				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_Polygon[nCntPolygon].fWidth / 10.0f), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, (g_Polygon[nCntPolygon].fDepth / 10.0f));
				pVtx[3].tex = D3DXVECTOR2((g_Polygon[nCntPolygon].fWidth / 10.0f), (g_Polygon[nCntPolygon].fDepth /10.0f));
			}


			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPolygon->Unlock();
			g_Polygon[nCntPolygon].bUse = true;
			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntPolygon;

		pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPolygon->Unlock();
	}
}

