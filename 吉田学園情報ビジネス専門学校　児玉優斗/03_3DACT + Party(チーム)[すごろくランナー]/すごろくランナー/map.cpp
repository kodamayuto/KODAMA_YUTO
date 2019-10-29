//=============================================================================
//
// �~�j�}�b�v���� [map.cpp]
// Author : ���R���
//
//=============================================================================
#include "map.h"
#include "mapPlayer.h"
//#include "mapEnemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_TEXTURENAME	"data\\TEXTURE\\map.png"	// �e�N�X�`����
#define	MAP_SIZE_X		(100)						// �~�j�}�b�v�̑傫��
#define	MAP_SIZE_Y		(100)						// �~�j�}�b�v�̑傫��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMap = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMap = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_MapPos;

//=============================================================================
// �^�C�}�[�̃t���[������������
//=============================================================================
void InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �ʒu��ݒ�
	D3DXVECTOR3 g_MapPos(120, 120, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MAP_TEXTURENAME, &g_pTextureMap);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffMap,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_MapPos.x - MAP_SIZE_X, g_MapPos.y - MAP_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_MapPos.x + MAP_SIZE_X, g_MapPos.y - MAP_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_MapPos.x - MAP_SIZE_X, g_MapPos.y + MAP_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_MapPos.x + MAP_SIZE_X, g_MapPos.y + MAP_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMap->Unlock();

	// �}�b�v�v���C���[����������
	InitMapPlayer();

	//// �}�b�v�G�l�~�[����������
	//InitMapEnemy();
}

//=============================================================================
// �^�C�}�[�̃t���[���I������
//=============================================================================
void UninitMap(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureMap != NULL)
	{
		g_pTextureMap->Release();
		g_pTextureMap = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMap != NULL)
	{
		g_pVtxBuffMap->Release();
		g_pVtxBuffMap = NULL;
	}

	// �}�b�v�v���C���[�I������
	UninitMapPlayer();

	//// �}�b�v�G�l�~�[�I������
	//UninitMapEnemy();
}

//=============================================================================
// �^�C�}�[�̃t���[���X�V����
//=============================================================================
void UpdateMap(void)
{
	// �}�b�v�v���C���[�X�V����
	UpdateMapPlayer();

	//// �}�b�v�G�l�~�[�X�V����
	//UpdateMapEnemy();
}

//=============================================================================
// �^�C�}�[�̃t���[���`�揈��
//=============================================================================
void DrawMap(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMap, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMap);

	// �^�C�g���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �}�b�v�v���C���[�`�揈��
	DrawMapPlayer();

	//// �}�b�v�G�l�~�[�`�揈��
	//DrawMapEnemy();
}