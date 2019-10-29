//=============================================================================
//
// ��󏈗�[arrow.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "arrow.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ARROW_POLYGON_FILENAME "data/TEXTURE/Draw010_Icon000.png"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexArrow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArrow = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureArrow = NULL;	    //�e�N�X�`���ւ̃|�C���^

D3DXVECTOR3 g_posArrow;		//�ʒu
D3DXVECTOR3 g_rotArrow;		//����
D3DXMATRIX	g_mtxWorldArrow;	//���[���h�}�g���b�N�X

Arrow g_Arrow;

//=============================================================================
// ����������
//=============================================================================
void InitArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, ARROW_POLYGON_FILENAME, &g_pTextureArrow);

	MakeVertexArrow(pDevice);

	//�\���̂̏�����
		g_Arrow.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Arrow.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Arrow.bUse = false;
}

//=============================================================================
// �I������
//=============================================================================
void UninitArrow(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pTextureArrow != NULL)
	{
		g_pTextureArrow->Release();
		g_pTextureArrow = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffArrow != NULL)
	{
		g_pVtxBuffArrow->Release();
		g_pVtxBuffArrow = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateArrow(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
												// �|���S���̕`��

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Arrow.mtxWorldArrow);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Arrow.rot.y,
				g_Arrow.rot.x,
				g_Arrow.rot.z);

			D3DXMatrixMultiply(&g_Arrow.mtxWorldArrow,
				&g_Arrow.mtxWorldArrow,
				&mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Arrow.pos.x,
				g_Arrow.pos.y,
				g_Arrow.pos.z);

			D3DXMatrixMultiply(&g_Arrow.mtxWorldArrow,
				&g_Arrow.mtxWorldArrow,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Arrow.mtxWorldArrow);

			pDevice->SetStreamSource(0, g_pVtxBuffArrow, 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�


				// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureArrow);//�e�N�X�`���̐ݒ�

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
				0,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�
	

}
//=============================================================================
// ���̐ݒ�
//=============================================================================
void SetArrow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{

		if (g_Arrow.bUse == false)
		{
			g_Arrow.pos = pos;
			g_Arrow.rot = rot;
			g_Arrow.bUse = true;

		}

}
//=============================================================================
// ���̍X�V
//=============================================================================
void SetPositionArrow(D3DXVECTOR3 pos)
{
	MODEL *pModel;
	pModel = GetModel();
	g_Arrow.pos = pos;

	g_Arrow.rot.y = RotOverwhelming(atan2f(pModel->pos.x - g_Arrow.pos.x, pModel->pos.z - g_Arrow.pos.z));
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexArrow(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffArrow,
		NULL);

	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].pos = D3DXVECTOR3(-30.0f, 0.0f, 30.0f);
		pVtx[1].pos = D3DXVECTOR3(30.0f, 0.0f, 30.0f);
		pVtx[2].pos = D3DXVECTOR3(-30.0f, 0.0f, -30.0f);
		pVtx[3].pos = D3DXVECTOR3(30.0f, 0.0f, -30.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffArrow->Unlock();

}

