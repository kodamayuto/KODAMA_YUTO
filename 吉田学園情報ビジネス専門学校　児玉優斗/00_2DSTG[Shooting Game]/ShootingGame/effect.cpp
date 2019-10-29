//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EFFECT		"data/TEXTURE/effect000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MAX_EFFECT			(8192)							// �G�t�F�N�g�̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEffect = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
EFFECT					g_aEffect[MAX_EFFECT];		// �G�t�F�N�g�̏��

//=============================================================================
// ����������
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}

	// ���_���̍쐬
	MakeVertexEffect(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	// �e�N�X�`���̊J��
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
	int nCntData;
	for (nCntData = 0; nCntData < MAX_EFFECT; nCntData++)
	{
		//�ϐ��錾
		VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

		// ���_����ݒ�
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
		
		pVtx += 4 * nCntData;

		if (g_aEffect[nCntData].bUse == true)
		{
			g_aEffect[nCntData].nLife--;
			if (g_aEffect[nCntData].nLife <= 0)
			{
				g_aEffect[nCntData].bUse = false;
			}
			/*�T�C�Y������������(����͂�������̗p)*/
			g_aEffect[nCntData].fRadius -= (BULLET_SIZE * 0.1f);
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x - g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y - g_aEffect[nCntData].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x + g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y - g_aEffect[nCntData].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x - g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y + g_aEffect[nCntData].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x + g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y + g_aEffect[nCntData].fRadius, 0.0f);

			/*���l��������*/
			//g_aEffect[nCntData].col.a -= 0.1f;
			//pVtx[0].col = g_aEffect[nCntData].col;
			//pVtx[1].col = g_aEffect[nCntData].col;
			//pVtx[2].col = g_aEffect[nCntData].col;
			//pVtx[3].col = g_aEffect[nCntData].col;



		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEffect->Unlock();

	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEffect;
	
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEffect);

	//// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// �|���S���̕`��
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
				4 * nCntEffect,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   			   //�v���~�e�B�u�̐�
		}
	}
	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		
	

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntData;

	//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT, &g_pTextureEffect);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						// ���_����ݒ�
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < MAX_EFFECT; nCntData++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(10,10,0.0f);
		pVtx[1].pos = D3DXVECTOR3(20,10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(10 ,20, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(20, 20, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();


}


//=============================================================================
// �G�t�F�N�g�ݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	int nCntData;


	for (nCntData = 0; nCntData < MAX_EFFECT; nCntData++)
	{
		if (g_aEffect[nCntData].bUse == false)
		{
			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntData;

			g_aEffect[nCntData].pos = pos;
			g_aEffect[nCntData].col = col;

			pVtx[0].col = g_aEffect[nCntData].col;
			pVtx[1].col = g_aEffect[nCntData].col;
			pVtx[2].col = g_aEffect[nCntData].col;
			pVtx[3].col = g_aEffect[nCntData].col;

			g_aEffect[nCntData].fRadius = fRadius;

			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x - g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y - g_aEffect[nCntData].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x + g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y - g_aEffect[nCntData].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x - g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y + g_aEffect[nCntData].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x + g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y + g_aEffect[nCntData].fRadius, 0.0f);

			g_aEffect[nCntData].nLife = nLife;
			g_aEffect[nCntData].bUse = true;
			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEffect->Unlock();

			break;
		}
	}

}

//
//
//
EFFECT *GetEffect(void)
{
	return &g_aEffect[0];
}
