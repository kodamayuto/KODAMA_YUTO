//=============================================================================
//
// �{�X���� [boss.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "boss_option.h"
#include "Explosion.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OPTION_BULLET_ROTATION (3.3f)
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBossOption = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBossOption = NULL;					// ���_�o�b�t�@�ւ̃|�C���^

BOSS_OPTION g_BossOption;	//�G�̃f�[�^�i�[

int g_BulletRot;
//=============================================================================
// ����������
//=============================================================================
void InitBossOption(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	g_BossOption.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_BossOption.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BossOption.bUse = false;
	g_BossOption.nCounterBullet = 0;

	g_BulletRot = 1;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BOSS_OPTION_TEXTURE, &g_pTextureBossOption);

	// ���_���̍쐬
	VERTEX_2D *pVtx;
	

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBossOption,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBossOption->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(0 - BOSS_OPTION_POLYGON_SIZE, 0 - BOSS_OPTION_POLYGON_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0 + BOSS_OPTION_POLYGON_SIZE, 0 - BOSS_OPTION_POLYGON_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0 - BOSS_OPTION_POLYGON_SIZE, 0 + BOSS_OPTION_POLYGON_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0 + BOSS_OPTION_POLYGON_SIZE, 0 + BOSS_OPTION_POLYGON_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(BOSS_OPTION_COLOR_RED, BOSS_OPTION_COLOR_GREEN,  BOSS_OPTION_COLOR_BLUE, BOSS_OPTION_COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(BOSS_OPTION_COLOR_RED, BOSS_OPTION_COLOR_GREEN, BOSS_OPTION_COLOR_BLUE, BOSS_OPTION_COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(BOSS_OPTION_COLOR_RED, BOSS_OPTION_COLOR_GREEN, BOSS_OPTION_COLOR_BLUE, BOSS_OPTION_COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(BOSS_OPTION_COLOR_RED, BOSS_OPTION_COLOR_GREEN, BOSS_OPTION_COLOR_BLUE, BOSS_OPTION_COLOR_ALPHA);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBossOption->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBossOption(void)
{

		// �e�N�X�`���̊J��
		if (g_pTextureBossOption != NULL)
		{
			g_pTextureBossOption->Release();
			g_pTextureBossOption = NULL;
		}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBossOption != NULL)
	{
		g_pVtxBuffBossOption->Release();
		g_pVtxBuffBossOption = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBossOption(void)
{
	// ���_���̍쐬
	BOSS *pBoss = GetBoss();

	float fBulletRot;

	g_BossOption.nCounterBullet++;

	if (pBoss->bUse == false)
	{
		g_BossOption.bUse = false;
	}

	if (g_BossOption.bUse == true)
	{
		//�e�ł�
		if (pBoss->bUse == true)
		{
			fBulletRot = OPTION_BULLET_ROTATION * ((g_BossOption.nCounterBullet) % 3600);
			SetBullet(g_BossOption.pos, D3DXVECTOR3(sinf(fBulletRot * g_BulletRot) * 8.0f, cosf(fBulletRot * g_BulletRot) * 8.0f, 0.0f), BULLETTYPE_BOSS, D3DXCOLOR(0.7f, 0.4f, 0.95f, 1.0f), 0.0f);
		}
		g_BossOption.pos += g_BossOption.move;

		if (g_BossOption.pos.x <= pBoss->pos.x - 200 || g_BossOption.pos.x >= pBoss->pos.x + 200)
		{
			g_BossOption.move.x = g_BossOption.move.x * -1.0f;
			g_BulletRot = g_BulletRot * - 1;
		}

		VERTEX_2D *pVtx;
		g_pVtxBuffBossOption->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(g_BossOption.pos.x - BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y - BOSS_OPTION_POLYGON_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_BossOption.pos.x + BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y - BOSS_OPTION_POLYGON_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_BossOption.pos.x - BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y + BOSS_OPTION_POLYGON_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_BossOption.pos.x + BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y + BOSS_OPTION_POLYGON_SIZE, 0.0f);

		g_pVtxBuffBossOption->Unlock();




	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBossOption(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	BOSS *pBoss = GetBoss();

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBossOption, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	
		if (g_BossOption.bUse == true)
		{
			//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0,g_pTextureBossOption);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
				0,							   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   							       //�v���~�e�B�u�̐�
		}
	
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetBossOption(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

		if (g_BossOption.bUse == false)
		{
			g_pVtxBuffBossOption->Lock(0, 0, (void**)&pVtx, 0);

			g_BossOption.pos = pos;

			g_BossOption.move = move;

			pVtx[0].pos = D3DXVECTOR3(g_BossOption.pos.x - BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y - BOSS_OPTION_POLYGON_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_BossOption.pos.x + BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y - BOSS_OPTION_POLYGON_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_BossOption.pos.x - BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y + BOSS_OPTION_POLYGON_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_BossOption.pos.x + BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y + BOSS_OPTION_POLYGON_SIZE, 0.0f);

			g_BossOption.nCounterBullet = 0;
			g_BossOption.bUse = true;


			g_pVtxBuffBossOption->Unlock();
	}
}

