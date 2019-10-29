//=============================================================================
//
// �~�j�}�b�v�̒��̃v���C���[���� [mapPlayer.cpp]
// Author : ���R���
//
//=============================================================================
#include "mapPlayer.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAPPLAYER_TEXTURENAME	"data\\TEXTURE\\mapPlayer.png"	// �e�N�X�`����
#define	MAPPLAYER_SIZE_X		(10)							// �~�j�}�b�v�̑傫��
#define	MAPPLAYER_SIZE_Y		(10)							// �~�j�}�b�v�̑傫��
#define	MINIMAP_SIZE			(185)							// �~�j�}�b�v�̑傫��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMapPlayer = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMapPlayer = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_MapPosPlayer;

//=============================================================================
// �^�C�}�[�̃t���[������������
//=============================================================================
void InitMapPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �v���C���[���擾
	Player *pPlayer;
	pPlayer = GetPlayer();

	// �ʒu��ݒ�
	D3DXVECTOR3 g_MapPosPlayer = pPlayer->pos / 20;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MAPPLAYER_TEXTURENAME, &g_pTextureMapPlayer);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffMapPlayer,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMapPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_MapPosPlayer.x - MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z - MAPPLAYER_SIZE_Y + (120), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_MapPosPlayer.x + MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z - MAPPLAYER_SIZE_Y + (120), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_MapPosPlayer.x - MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z + MAPPLAYER_SIZE_Y + (120), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_MapPosPlayer.x + MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z + MAPPLAYER_SIZE_Y + (120), 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMapPlayer->Unlock();
}

//=============================================================================
// �^�C�}�[�̃t���[���I������
//=============================================================================
void UninitMapPlayer(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureMapPlayer != NULL)
	{
		g_pTextureMapPlayer->Release();
		g_pTextureMapPlayer = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMapPlayer != NULL)
	{
		g_pVtxBuffMapPlayer->Release();
		g_pVtxBuffMapPlayer = NULL;
	}
}

//=============================================================================
// �^�C�}�[�̃t���[���X�V����
//=============================================================================
void UpdateMapPlayer(void)
{
	// �v���C���[���擾
	Player *pPlayer;
	pPlayer = GetPlayer();

	g_MapPosPlayer = pPlayer->pos / 135;

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMapPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�t�B�[���h�̑傫���̔���
	if (MINIMAP_SIZE - MAPPLAYER_SIZE_X / 2 <= g_MapPosPlayer.x)
	{
		g_MapPosPlayer.x = MINIMAP_SIZE - MAPPLAYER_SIZE_X / 2;
	}
	if (-MINIMAP_SIZE + MAPPLAYER_SIZE_X / 2 >= g_MapPosPlayer.x)
	{
		g_MapPosPlayer.x = -MINIMAP_SIZE + MAPPLAYER_SIZE_X / 2;
	}
	if (-MINIMAP_SIZE + MAPPLAYER_SIZE_Y / 2 >= g_MapPosPlayer.z)
	{
		g_MapPosPlayer.z = -MINIMAP_SIZE + MAPPLAYER_SIZE_Y / 2;
	}
	if (MINIMAP_SIZE - MAPPLAYER_SIZE_Y / 2 <= g_MapPosPlayer.z)
	{
		g_MapPosPlayer.z = MINIMAP_SIZE - MAPPLAYER_SIZE_Y / 2;
	}

	pVtx[0].pos = D3DXVECTOR3(/*g_MapPosPlayer.x*/ - MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z - MAPPLAYER_SIZE_Y + (210), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(/*g_MapPosPlayer.x*/ + MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z - MAPPLAYER_SIZE_Y + (210), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(/*g_MapPosPlayer.x*/ - MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z + MAPPLAYER_SIZE_Y + (210), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(/*g_MapPosPlayer.x*/ + MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z + MAPPLAYER_SIZE_Y + (210), 0.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMapPlayer->Unlock();
}

//=============================================================================
// �^�C�}�[�̃t���[���`�揈��
//=============================================================================
void DrawMapPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMapPlayer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMapPlayer);

	// �^�C�g���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}