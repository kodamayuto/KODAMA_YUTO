//=============================================================================
//
// ���C�t�\������ [life.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "life.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_LIFE		"data/TEXTURE/life000.png"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_LIFE (PLAYER_LIFE)								//����
#define LIFE_SIZE  (15.0f)									//���C�t�̑傫��

#define LIFE_POS_X (1000)									//���C�t��X��
#define LIFE_POS_Y (650)									//���C�t��Y��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
int						g_nLife;						// ���C�t

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// ����������
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�l�̏�����
	g_nLife = MAX_LIFE;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_LIFE,		// �t�@�C���̖��O
								&g_pTextureLife);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexLife(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitLife(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLife(void)
{//�܂������Ȃ�

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntLife;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLife);

	for (nCntLife = 0; nCntLife < g_nLife; nCntLife++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
			4 * nCntLife,							   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   										   //�v���~�e�B�u�̐�
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntData;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	// ���_����ݒ�
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < MAX_LIFE; nCntData++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) - LIFE_SIZE, LIFE_POS_Y - LIFE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) + LIFE_SIZE, LIFE_POS_Y - LIFE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) - LIFE_SIZE, LIFE_POS_Y + LIFE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) + LIFE_SIZE, LIFE_POS_Y + LIFE_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
//���C�t�̏���
//=============================================================================
void SetLife(int nLife)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	int nCntData;

	g_nLife = nLife;
	// ���_����ݒ�
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < g_nLife; nCntData++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) - LIFE_SIZE, LIFE_POS_Y - LIFE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) + LIFE_SIZE, LIFE_POS_Y - LIFE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) - LIFE_SIZE, LIFE_POS_Y + LIFE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) + LIFE_SIZE, LIFE_POS_Y + LIFE_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();

}
