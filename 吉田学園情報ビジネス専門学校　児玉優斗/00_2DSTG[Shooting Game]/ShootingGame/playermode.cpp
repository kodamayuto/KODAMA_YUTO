//=============================================================================
//
// ���@�^�C�v�\������ [playermode.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "playermode.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PLAYERMODE_01		"data/TEXTURE/PlayerMode_1.png"		//�ǂݍ��ރe�N�X�`���t�@�C����1
#define	TEXTURE_PLAYERMODE_02		"data/TEXTURE/PlayerMode_2.png"		//�ǂݍ��ރe�N�X�`���t�@�C����2
#define	TEXTURE_PLAYERMODE_03		"data/TEXTURE/PlayerMode_3.png"		//�ǂݍ��ރe�N�X�`���t�@�C����3

#define PLAYERMODE_SIZE  (35.0f)									//��ԕ\���̑傫��

#define PLAYERMODE_POS_X (1220)										//��ԕ\����X��
#define PLAYERMODE_POS_Y (590)										//��ԕ\����Y��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePlayerMode[3] = {};			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerMode = NULL;			// ���_�o�b�t�@�ւ̃|�C���^

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPlayerMode(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// ����������
//=============================================================================
void InitPlayerMode(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PLAYERMODE_01,		// �t�@�C���̖��O
								&g_pTexturePlayerMode[0]);	// �e�N�X�`���ւ̃|�C���^

	D3DXCreateTextureFromFile(pDevice,
								TEXTURE_PLAYERMODE_02,
								&g_pTexturePlayerMode[1]);

	D3DXCreateTextureFromFile(pDevice,
								TEXTURE_PLAYERMODE_03,
								&g_pTexturePlayerMode[2]);
	// ���_���̍쐬
	MakeVertexPlayerMode(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerMode(void)
{
	// �e�N�X�`���̊J��
	for (int nCntData = 0; nCntData < 3; nCntData++)
	{
	if (g_pTexturePlayerMode[nCntData] != NULL)
	{
		g_pTexturePlayerMode[nCntData]->Release();
		g_pTexturePlayerMode[nCntData] = NULL;
	}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayerMode != NULL)
	{
		g_pVtxBuffPlayerMode->Release();
		g_pVtxBuffPlayerMode = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerMode(void)
{//�܂������Ȃ�

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerMode(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	Player *pPlayer = GetPlayer();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffPlayerMode, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	if (pPlayer->nBulletPattern % 3 == 0)
	{
		pDevice->SetTexture(0, g_pTexturePlayerMode[0]);
	}
	else if (pPlayer->nBulletPattern % 3 == 1)
	{
		pDevice->SetTexture(0, g_pTexturePlayerMode[1]);
	}
	else if (pPlayer->nBulletPattern % 3 == 2)
	{
		pDevice->SetTexture(0, g_pTexturePlayerMode[2]);
	}

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
			0,							   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   										   //�v���~�e�B�u�̐�
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPlayerMode(LPDIRECT3DDEVICE9 pDevice)
{

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerMode,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	// ���_����ݒ�
	g_pVtxBuffPlayerMode->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(PLAYERMODE_POS_X - PLAYERMODE_SIZE, PLAYERMODE_POS_Y - PLAYERMODE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PLAYERMODE_POS_X + PLAYERMODE_SIZE, PLAYERMODE_POS_Y - PLAYERMODE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PLAYERMODE_POS_X - PLAYERMODE_SIZE, PLAYERMODE_POS_Y + PLAYERMODE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PLAYERMODE_POS_X + PLAYERMODE_SIZE, PLAYERMODE_POS_Y + PLAYERMODE_SIZE, 0.0f);

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


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayerMode->Unlock();
}

