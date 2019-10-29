//*****************************************************************************
//
//					DirectX �w�i���� [bg.cpp]
//					Author Kodama Yuto
//
//*****************************************************************************
//�C���N���[�h�t�@�C��
#include "main.h"
#include "bg.h"

//=============================================================================
//							�O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBG[3] = {};	                //�e�N�X�`���ւ̃|�C���^

int g_nCounterBG = 0;

D3DXVECTOR3 g_aBG_pos[3];

//-----------------------------------------------------------------------------
//						   �w�i�̏���������
//-----------------------------------------------------------------------------
void InitBG(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾
	
	pDevice = GetDevice();
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	for (int nCntData = 0; nCntData < 3; nCntData++)
	{
		g_aBG_pos[nCntData] = D3DXVECTOR3(BG_POS_X,BG_POS_Y,0.0f);
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_100,&g_pTextureBG[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_101, &g_pTextureBG[1]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_102, &g_pTextureBG[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	for (int nCntData = 0; nCntData < 3; nCntData++)
	{

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntData;

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aBG_pos[nCntData].x - BG_POS_X, g_aBG_pos[nCntData].y - BG_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBG_pos[nCntData].x + BG_POS_X, g_aBG_pos[nCntData].y - BG_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBG_pos[nCntData].x - BG_POS_X, g_aBG_pos[nCntData].y + BG_POS_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBG_pos[nCntData].x + BG_POS_X, g_aBG_pos[nCntData].y + BG_POS_Y, 0.0f);

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

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBG->Unlock();

	}
}

//-----------------------------------------------------------------------------
//						   �w�i�̏I������
//-----------------------------------------------------------------------------
void UninitBG(void)
{
	//�e�N�X�`���̔j��
	for (int nCntData = 0; nCntData < 3; nCntData++)
	{
		if (g_pTextureBG[nCntData] != NULL)
		{
			g_pTextureBG[nCntData]-> Release();
			g_pTextureBG[nCntData] =  NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//-----------------------------------------------------------------------------
//							�w�i�̍X�V����
//-----------------------------------------------------------------------------
//�܂����������Ȃ�
void UpdateBG(void)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	Player *pPlayer;

	pPlayer = GetPlayer();

	g_nCounterBG++;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);


	//�e�N�X�`�����W
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00025f + 0.0f, 0.0025f * -g_nCounterBG + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00025f + 1.0f, 0.0025f * -g_nCounterBG + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00025f + 0.0f, 0.0025f * -g_nCounterBG + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00025f + 1.0f, 0.0025f * -g_nCounterBG + 1.0f);

	pVtx += 4;
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.55f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.55f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.55f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.55f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(pPlayer->pos.x * 0.0004f, 0.005f * -g_nCounterBG + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(pPlayer->pos.x * 0.0004f + 1.0f, 0.005f * -g_nCounterBG + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(pPlayer->pos.x * 0.0004f, 0.005f * -g_nCounterBG + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(pPlayer->pos.x * 0.0004f + 1.0f, 0.005f * -g_nCounterBG + 1.0f);

	pVtx += 4;
	pVtx[0].col = D3DXCOLOR(1.0f, 0.59f, 0.54f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.59f, 0.54f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.59f, 0.54f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.59f, 0.54f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00065f, 0.008f * -g_nCounterBG + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00065f + 1.0f, 0.008f * -g_nCounterBG + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00065f, 0.008f * -g_nCounterBG + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00065f + 1.0f, 0.008f * -g_nCounterBG + 1.0f);

	g_pVtxBuffBG->Unlock();

}

//-----------------------------------------------------------------------------
//							�w�i�̕`�揈��
//-----------------------------------------------------------------------------
void DrawBG(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�`��
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�


	for (int nCntData = 0; nCntData < 3; nCntData++)
	{
		pDevice->SetTexture(0, g_pTextureBG[nCntData]);//�e�N�X�`���̐ݒ�

												//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			4 * nCntData,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   	       //�v���~�e�B�u�̐�
	}
}

