//=============================================================================
//
// �Ǐ���[effect.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "effect.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EFFECT_FILENAME0 "data/TEXTURE/shadow000.jpg"
#define MAX_EFFECT (4096)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;	    //�e�N�X�`���ւ̃|�C���^

EFFECT g_Effect[MAX_EFFECT];

//=============================================================================
// ����������
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, EFFECT_FILENAME0, &g_pTextureEffect);

	MakeVertexEffect(pDevice);

	//�\���̂̏�����
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_Effect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Effect[nCntEffect].fWidth = 0.0f;
		g_Effect[nCntEffect].Haight = 0.0f;
		g_Effect[nCntEffect].nLife = 0;
		g_Effect[nCntEffect].bUse = false;
	}

}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	// ���_�o�b�t�@�̊J��
		if (g_pTextureEffect != NULL)
		{
			g_pTextureEffect->Release();
			g_pTextureEffect = NULL;
		}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{
			g_Effect[nCntEffect].nLife--;

			if (g_Effect[nCntEffect].nLife <= 0)
			{
				g_Effect[nCntEffect].col.a -= 0.2f;
				g_Effect[nCntEffect].fWidth -= 0.5f;
				g_Effect[nCntEffect].Haight -= 0.5f;

				if (g_Effect[nCntEffect].col.a < 0.0f)
				{
					g_Effect[nCntEffect].col.a = 0.0f;
					g_Effect[nCntEffect].bUse = false;
				}
			}
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntEffect;

			pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fWidth, g_Effect[nCntEffect].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fWidth, g_Effect[nCntEffect].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fWidth, -g_Effect[nCntEffect].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fWidth, -g_Effect[nCntEffect].Haight, 0.0f);

			pVtx[0].col = g_Effect[nCntEffect].col;
			pVtx[1].col = g_Effect[nCntEffect].col;
			pVtx[2].col = g_Effect[nCntEffect].col;
			pVtx[3].col = g_Effect[nCntEffect].col;

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEffect->Unlock();

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans , mtxView;				// �v�Z�p�}�g���b�N�X

	// �|���S���̕`��
			//// ���u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			//���e�X�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 120);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// Z�o�b�t�@�𖳌���
			pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

			// ���C�e�B���O���[�h�𖳌���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);						

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{

			D3DXMatrixIdentity(&g_Effect[nCntEffect].g_mtxWorld);

			g_Effect[nCntEffect].g_mtxWorld._11 = mtxView._11;
			g_Effect[nCntEffect].g_mtxWorld._12 = mtxView._21;
			g_Effect[nCntEffect].g_mtxWorld._13 = mtxView._31;
			g_Effect[nCntEffect].g_mtxWorld._21 = mtxView._12;
			g_Effect[nCntEffect].g_mtxWorld._22 = mtxView._22;
			g_Effect[nCntEffect].g_mtxWorld._23 = mtxView._32;
			g_Effect[nCntEffect].g_mtxWorld._31 = mtxView._13;
			g_Effect[nCntEffect].g_mtxWorld._32 = mtxView._23;
			g_Effect[nCntEffect].g_mtxWorld._33 = mtxView._33;
			
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Effect[nCntEffect].pos.x,
				g_Effect[nCntEffect].pos.y,
				g_Effect[nCntEffect].pos.z);

			D3DXMatrixMultiply(&g_Effect[nCntEffect].g_mtxWorld,
				&g_Effect[nCntEffect].g_mtxWorld,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCntEffect].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

				// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);//�e�N�X�`���̐ݒ�

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
				4 * nCntEffect,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�
		}

	}
	// ���C�e�B���O���[�h��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�o�b�t�@�̗L����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		// ���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// �|���S���̐ݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fWidth, float haight)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == false)
		{
			g_Effect[nCntEffect].pos = pos;
			g_Effect[nCntEffect].rot = rot;
			g_Effect[nCntEffect].col = col;
			g_Effect[nCntEffect].fWidth = fWidth;
			g_Effect[nCntEffect].Haight = haight;
			g_Effect[nCntEffect].nLife = 10;


			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntEffect;
			pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fWidth, g_Effect[nCntEffect].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fWidth, g_Effect[nCntEffect].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fWidth, -g_Effect[nCntEffect].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fWidth, -g_Effect[nCntEffect].Haight, 0.0f);

			pVtx[0].col = g_Effect[nCntEffect].col;
			pVtx[1].col = g_Effect[nCntEffect].col;
			pVtx[2].col = g_Effect[nCntEffect].col;
			pVtx[3].col = g_Effect[nCntEffect].col;


			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEffect->Unlock();
			g_Effect[nCntEffect].bUse = true;

			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntEffect;

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
		g_pVtxBuffEffect->Unlock();
	}
}

