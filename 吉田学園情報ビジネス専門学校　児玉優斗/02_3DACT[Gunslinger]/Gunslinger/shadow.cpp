//=============================================================================
//
// �e����[shadow.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "shadow.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SHADOW_POLYGON_FILENAME "data/TEXTURE/shadow000.jpg"
#define MAX_SHADOW (1024)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;	    //�e�N�X�`���ւ̃|�C���^

D3DXVECTOR3 g_posShadow;		//�ʒu
D3DXVECTOR3 g_rotShadow;		//����
D3DXMATRIX	g_mtxWorldShadow;	//���[���h�}�g���b�N�X

Shadow g_Shadow[MAX_SHADOW];

//=============================================================================
// ����������
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, SHADOW_POLYGON_FILENAME, &g_pTextureShadow);

	MakeVertexShadow(pDevice);

	//�\���̂̏�����
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
												// �|���S���̕`��

	//���u�����f�B���O�����Z�����ɂ���
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//// Z�o�b�t�@�𖳌���
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Shadow[nCntShadow].mtxWorldShadow);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Shadow[nCntShadow].rot.y,
				g_Shadow[nCntShadow].rot.x,
				g_Shadow[nCntShadow].rot.z);

			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorldShadow,
				&g_Shadow[nCntShadow].mtxWorldShadow,
				&mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Shadow[nCntShadow].pos.x,
				g_Shadow[nCntShadow].pos.y,
				g_Shadow[nCntShadow].pos.z);

			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorldShadow,
				&g_Shadow[nCntShadow].mtxWorldShadow,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].mtxWorldShadow);

			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�


				// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);//�e�N�X�`���̐ݒ�

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
				4 * nCntShadow,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�
		}
	}
	////Z�o�b�t�@�̗L����
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			g_Shadow[nCntShadow].pos = pos;
			g_Shadow[nCntShadow].rot = rot;
			g_Shadow[nCntShadow].bUse = true;

		break;
		}
	}
	return nCntShadow;
}

//=============================================================================
// �e�̈ʒu�ݒ�
//=============================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_Shadow[nIdxShadow].pos = pos;
}

//=============================================================================
// �e�̃T�C�Y�ݒ�
//=============================================================================
void SetSizeShadow(int nIdxShadow, float posY, float Size)
{
	float fSize , fColA;
	//�T�C�Y
	fSize = (posY / 2.0f) + Size;

	//���l
	fColA = (posY * -0.005f) + 0.5f;
	
	if (fColA <= 0.0f)
	{
		fColA = 0.0f;
	}
	else if (fColA >= 1.0f)
	{
		fColA = 1.0f;
	}

	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * nIdxShadow;
	pVtx[0].pos = D3DXVECTOR3(-fSize, 0.0f, fSize);
	pVtx[1].pos = D3DXVECTOR3(fSize, 0.0f, fSize);
	pVtx[2].pos = D3DXVECTOR3(-fSize, 0.0f, -fSize);
	pVtx[3].pos = D3DXVECTOR3(fSize, 0.0f, -fSize);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fColA);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fColA);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fColA);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fColA);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//=============================================================================
// �e������
//=============================================================================
void DeleteShadow(int nIdxShadow)
{
	g_Shadow[nIdxShadow].bUse = false;
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

}

