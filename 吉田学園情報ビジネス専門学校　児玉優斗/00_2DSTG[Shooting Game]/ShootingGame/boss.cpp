//=============================================================================
//
// �{�X���� [boss.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "boss.h"
#include "Explosion.h"
#include "game.h"
#include "boss_option.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BOSS_LIFE (300)
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBoss[2] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;					// ���_�o�b�t�@�ւ̃|�C���^

BOSS g_Boss;	//�G�̃f�[�^�i�[
//=============================================================================
// ����������
//=============================================================================
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
		g_Boss.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_Boss.bUse = false;
		g_Boss.state = BOSSSTATE_NORMAL;
		g_Boss.nCounterState = 0;
		g_Boss.nLife = 5;
		g_Boss.nCounterBullet = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BOSS_TEXTURE, &g_pTextureBoss[0]);
	D3DXCreateTextureFromFile(pDevice, BOSS_DAMAGE_TEXTURE, &g_pTextureBoss[1]);

	// ���_���̍쐬
	VERTEX_2D *pVtx;
	

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBoss,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(0 - BOSS_POLYGON_SIZE, 0 - BOSS_POLYGON_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0 + BOSS_POLYGON_SIZE, 0 - BOSS_POLYGON_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0 - BOSS_POLYGON_SIZE, 0 + BOSS_POLYGON_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0 + BOSS_POLYGON_SIZE, 0 + BOSS_POLYGON_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(BOSS_COLOR_RED, BOSS_COLOR_GREEN,  BOSS_COLOR_BLUE, BOSS_COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(BOSS_COLOR_RED, BOSS_COLOR_GREEN, BOSS_COLOR_BLUE, BOSS_COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(BOSS_COLOR_RED, BOSS_COLOR_GREEN, BOSS_COLOR_BLUE, BOSS_COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(BOSS_COLOR_RED, BOSS_COLOR_GREEN, BOSS_COLOR_BLUE, BOSS_COLOR_ALPHA);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBoss->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss(void)
{

	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureBoss[nCntTex] != NULL)
		{
			g_pTextureBoss[nCntTex]->Release();
			g_pTextureBoss[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss(void)
{
	// ���_���̍쐬
	Player *pPlayer;
	float fBulletAngle;

	pPlayer = GetPlayer();
	g_Boss.nCounterBullet++;

	if (g_Boss.bUse == true)
	{
		switch (g_Boss.state)
		{
		case BOSSSTATE_NORMAL:

			break;
		case BOSSSTATE_DAMAGE:
			g_Boss.nCounterState--;
			if (g_Boss.nCounterState <= 0)
			{
				g_Boss.state = BOSSSTATE_NORMAL;
			}
			break;
		}
		//�ړ�
		g_Boss.pos.y += g_Boss.move.y;
		if (g_Boss.pos.y >= 130)
		{
			g_Boss.move.y = 0;
		}
		VERTEX_2D *pVtx;

		g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].pos = D3DXVECTOR3(g_Boss.pos.x - BOSS_POLYGON_SIZE, g_Boss.pos.y - BOSS_POLYGON_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Boss.pos.x + BOSS_POLYGON_SIZE, g_Boss.pos.y - BOSS_POLYGON_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Boss.pos.x - BOSS_POLYGON_SIZE, g_Boss.pos.y + BOSS_POLYGON_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Boss.pos.x + BOSS_POLYGON_SIZE, g_Boss.pos.y + BOSS_POLYGON_SIZE, 0.0f);

		g_pVtxBuffBoss->Unlock();

		//�e�ł�
		if (pPlayer->bDisp == true)
		{
			fBulletAngle = atan2f(pPlayer->pos.x - g_Boss.pos.x, pPlayer->pos.y - g_Boss.pos.y);
			if (g_Boss.nLife <= MAX_BOSS_LIFE && g_Boss.nLife > 100)
			{
				if (g_Boss.nCounterBullet % 50 == 0)
				{
					SetBullet(g_Boss.pos, D3DXVECTOR3(sinf(fBulletAngle) * 10.0f, cosf(fBulletAngle) * 10.0f, 0.0f), BULLETTYPE_BOSS, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), fBulletAngle);
				}
			}
			if (g_Boss.nLife <= 250 && g_Boss.nLife > 200)//�ǉ��e
			{
				if (g_Boss.nCounterBullet % 50 == 25)
				{
					SetBullet(g_Boss.pos, D3DXVECTOR3(sinf(fBulletAngle - 0.5f) * 10.0f, cosf(fBulletAngle) * 10.0f, 0.0f), BULLETTYPE_BOSS, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 0.0f);
					SetBullet(g_Boss.pos, D3DXVECTOR3(sinf(fBulletAngle + 0.5f) * 10.0f, cosf(fBulletAngle) * 10.0f, 0.0f), BULLETTYPE_BOSS, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 0.0f);
				}
			}
			if (g_Boss.nLife <= 200 && g_Boss.nLife > 100 || g_Boss.nLife <= 50)
			{
				if (g_Boss.nCounterBullet % 2 == 0)
				{

					SetBullet(g_Boss.pos, D3DXVECTOR3(sinf(fBulletAngle - 0.4f) * 10.0f, cosf(fBulletAngle) * 10.0f, 0.0f), BULLETTYPE_BOSS, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 0.0f);
					SetBullet(g_Boss.pos, D3DXVECTOR3(sinf(fBulletAngle + 0.4f) * 10.0f, cosf(fBulletAngle) * 10.0f, 0.0f), BULLETTYPE_BOSS, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 0.0f);
				}
			}
			if (g_Boss.nLife == 100)
			{
				SetBossOption(D3DXVECTOR3(g_Boss.pos.x - 200, g_Boss.pos.y - BOSS_POLYGON_SIZE - 20, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f));
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	
		if (g_Boss.bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			if (g_Boss.state == BOSSSTATE_NORMAL)
			{
				pDevice->SetTexture(0,g_pTextureBoss[0]);
			}
			else if (g_Boss.state == BOSSSTATE_DAMAGE)
			{
				pDevice->SetTexture(0, g_pTextureBoss[1]);
			}

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
				0,							   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   							       //�v���~�e�B�u�̐�
		}
	
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

		if (g_Boss.bUse == false)
		{
			g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

			g_Boss.pos = pos;

			g_Boss.move = move;

			g_Boss.state = BOSSSTATE_NORMAL;

			g_Boss.nCounterState = 0;

			g_Boss.nLife = MAX_BOSS_LIFE;
			g_Boss.nCounterBullet = 0;
			g_Boss.bUse = true;

			pVtx[0].pos = D3DXVECTOR3(g_Boss.pos.x - BOSS_POLYGON_SIZE, g_Boss.pos.y - BOSS_POLYGON_SIZE,0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Boss.pos.x + BOSS_POLYGON_SIZE, g_Boss.pos.y - BOSS_POLYGON_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Boss.pos.x - BOSS_POLYGON_SIZE, g_Boss.pos.y + BOSS_POLYGON_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Boss.pos.x + BOSS_POLYGON_SIZE, g_Boss.pos.y + BOSS_POLYGON_SIZE, 0.0f);

			g_pVtxBuffBoss->Unlock();
	}
}

//=============================================================================
// �G�̎擾
//=============================================================================
BOSS *GetBoss(void)
{
	return &g_Boss;
}
//=============================================================================
//	�_���[�W����
//=============================================================================
void HitBoss(int nDamage)
{
	// ���_���̍쐬

	Player *pPlayer;

	int nValue = 0;			//�_��

	pPlayer = GetPlayer();
	g_Boss.nLife -= nDamage;
	PlaySound(SOUND_LABEL_SE_HIT000);//��

	if (g_Boss.nLife <= 0)
	{
		SetExplosion(g_Boss.pos, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		g_Boss.bUse = false;
		g_Boss.state = BOSSSTATE_DEATH;
		if (pPlayer->bDisp == true)
		{
		nValue = 10000000 * (pPlayer->nLife);
		AddScore(nValue);
		}
		PlaySound(SOUND_LABEL_SE_EXPLOSION);//��

			StopSound(SOUND_LABEL_BGM001);
			SetGameState(GAMESTATE_END);
	}
	else
	{
		g_Boss.state = BOSSSTATE_DAMAGE;
		g_Boss.nCounterState = 3;
		if (pPlayer->bDisp == true)
		{
			nValue = 1000 * ((MAX_BOSS_LIFE + 1)- g_Boss.nLife);
			AddScore(nValue);
		}

	}
}