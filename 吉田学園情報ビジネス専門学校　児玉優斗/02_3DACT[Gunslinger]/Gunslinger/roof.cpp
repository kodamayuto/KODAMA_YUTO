//=============================================================================
//
// �Ǐ���[roof.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "roof.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ROOF_FILENAME0 "data/TEXTURE/wall000.jpg"
#define ROOF_FILENAME1 "data/TEXTURE/wall000.jpg"
#define MAX_ROOF (256)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRoof(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRoof = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRoof[2] = {};	    //�e�N�X�`���ւ̃|�C���^

ROOF g_Roof[MAX_ROOF];
//=============================================================================
// ����������
//=============================================================================
void InitRoof(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, ROOF_FILENAME0, &g_pTextureRoof[0]);
	D3DXCreateTextureFromFile(pDevice, ROOF_FILENAME1, &g_pTextureRoof[1]);

	MakeVertexRoof(pDevice);

	//�\���̂̏�����
	for (int nCntRoof = 0; nCntRoof < MAX_ROOF; nCntRoof++)
	{
		g_Roof[nCntRoof].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Roof[nCntRoof].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Roof[nCntRoof].bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitRoof(void)
{
	// ���_�o�b�t�@�̊J��
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureRoof[nCntTex] != NULL)
		{
			g_pTextureRoof[nCntTex]->Release();
			g_pTextureRoof[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRoof != NULL)
	{
		g_pVtxBuffRoof->Release();
		g_pVtxBuffRoof = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRoof(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRoof(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	// ���[���h�}�g���b�N�X�̏�����
	// �|���S���̕`��
	//pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	for (int nCntRoof = 0; nCntRoof < MAX_ROOF; nCntRoof++)
	{
		if (g_Roof[nCntRoof].bUse == true)
		{
			D3DXMatrixIdentity(&g_Roof[nCntRoof].g_mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Roof[nCntRoof].rot.y,
				g_Roof[nCntRoof].rot.x,
				g_Roof[nCntRoof].rot.z);

			D3DXMatrixMultiply(&g_Roof[nCntRoof].g_mtxWorld,
				&g_Roof[nCntRoof].g_mtxWorld,
				&mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Roof[nCntRoof].pos.x,
				g_Roof[nCntRoof].pos.y,
				g_Roof[nCntRoof].pos.z);

			D3DXMatrixMultiply(&g_Roof[nCntRoof].g_mtxWorld,
				&g_Roof[nCntRoof].g_mtxWorld,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Roof[nCntRoof].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffRoof, 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

				// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRoof[0]);//�e�N�X�`���̐ݒ�

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
				4 * nCntRoof,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�
		}
	}
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// �|���S���̐ݒ�
//=============================================================================
void SetRoof(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ROOFTYPE type, float fWidth ,float fHaight)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntRoof = 0; nCntRoof < MAX_ROOF; nCntRoof++)
	{
		if (g_Roof[nCntRoof].bUse == false)
		{
			g_Roof[nCntRoof].pos = pos;
			g_Roof[nCntRoof].rot = rot;
			g_Roof[nCntRoof].fWidth = fWidth;
			g_Roof[nCntRoof].Haight = fHaight;
			g_Roof[nCntRoof].type = type;
			

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffRoof->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntRoof;
			switch (g_Roof[nCntRoof].type)
			{
			case ROOFTYPE_1:

				pVtx[0].pos = D3DXVECTOR3(-g_Roof[nCntRoof].fWidth, g_Roof[nCntRoof].Haight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Roof[nCntRoof].fWidth, g_Roof[nCntRoof].Haight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_Roof[nCntRoof].fWidth,0.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Roof[nCntRoof].fWidth, 0.0f, 0.0f);

				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_Roof[nCntRoof].fWidth / 100.0f) + 1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, (g_Roof[nCntRoof].Haight / 100.0f) + 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_Roof[nCntRoof].fWidth / 100.0f) + 1.0f, (g_Roof[nCntRoof].Haight / 100.0f) + 1.0f);
				break;
			}
			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffRoof->Unlock();
			g_Roof[nCntRoof].bUse = true;
			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRoof(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ROOF,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRoof,
		NULL);

	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntRoof = 0; nCntRoof < MAX_ROOF; nCntRoof++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffRoof->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntRoof;

		pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRoof->Unlock();
	}
}

