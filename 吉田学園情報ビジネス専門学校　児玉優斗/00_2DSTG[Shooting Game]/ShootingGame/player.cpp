//*****************************************************************************
//
//					DirectX �v���C���[�̏��� [player.cpp]
//						Author Kodama Yuto
//
//*****************************************************************************
//�C���N���[�h�t�@�C��
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
//=============================================================================
//							�O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;	                    //�e�N�X�`���ւ̃|�C���^

int g_nCounterAnim;				//�A�j���[�V�����J�E���^�[
int g_nPattrenAnim;				//�A�j���[�V�����p�^�[��No.
int g_Score;
Player g_Player;

//-----------------------------------------------------------------------------
//						   �|���S���̏���������
//-----------------------------------------------------------------------------
void InitPlayer(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3(SENT_POS_X, SENT_POS_Y, 0.0f);
	g_Player.bDisp = true;
	g_Player.nLife = PLAYER_LIFE;
	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.move = D3DXVECTOR3(0, 0, 0.0f);
	g_Player.nBulletPattern = 0;
	g_Player.nCntBullet = 0;
	g_Player.bMove = false;
	g_Player.nCountState = 50;

	g_nCounterAnim = 0;		//�J�E���^�[�̏�����
	g_nPattrenAnim = 0;		//�p�^�[��No.�̏�����


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE,&g_pTexturePolygon);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);


	//���_���W
	pVtx[0].pos = D3DXVECTOR3(0 - PLAYER_SIZE, 0 - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0 + PLAYER_SIZE, 0 - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0 - PLAYER_SIZE, 0 + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0 + PLAYER_SIZE, 0 + PLAYER_SIZE, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();
}

//-----------------------------------------------------------------------------
//						   �|���S���̏I������
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon -> Release();
		g_pTexturePolygon =  NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//-----------------------------------------------------------------------------
//							�|���S���̍X�V����
//-----------------------------------------------------------------------------
void UpdatePlayer(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//�X�e�[�^�X
	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		if (g_Player.bMove == true)
		{
			SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 22, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), PLAYER_SIZE / 2.5f, 10);
		}
		else
		{
			SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 22, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f), PLAYER_SIZE / 2, 10);
		}
		break;
	case PLAYERSTATE_DAMAGE:
		SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 22, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), PLAYER_SIZE / 2, 10);

		g_Player.nCountState--;
		if (g_Player.nCountState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPolygon->Unlock();

		}
		break;
	case PLAYERSTATE_APPEAR:
		break;
	case PLAYERSTATE_DEATH:
		SetGameState(GAMESTATE_END);
		g_Player.state = PLAYERSTATE_END;
		StopSound(SOUND_LABEL_BGM001);
		PlaySound(SOUND_LABEL_SE_EXPLOSION);//��

		break;
	case PLAYERSTATE_END:
		break;
	}
	g_nCounterAnim++;

	if (g_Player.bDisp == true)
	{
		if (GetKeyboardPress(DIK_A) == true)//��
		{
			if (GetKeyboardPress(DIK_W) == true)//��
			{
				g_Player.move.x += sinf(D3DX_PI * -0.75f) * PLAYER_MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.75f) * PLAYER_MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)//��
			{
				g_Player.move.x += sinf(D3DX_PI * -0.25f) * PLAYER_MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.25f) * PLAYER_MOVE_SPEED;
			}
			else
			{
				g_Player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)//��
		{
			if (GetKeyboardPress(DIK_W) == true)//��
			{
				g_Player.move.x += sinf(D3DX_PI * 0.75f) * PLAYER_MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.75f) * PLAYER_MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)//��
			{
				g_Player.move.x += sinf(D3DX_PI * 0.25f) * PLAYER_MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.25f) * PLAYER_MOVE_SPEED;
			}
			else
			{
				g_Player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)//��
		{
			g_Player.move.x += sinf(D3DX_PI) * PLAYER_MOVE_SPEED;
			g_Player.move.y += cosf(D3DX_PI) * PLAYER_MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)//��
		{
			g_Player.move.x += sinf(0.0) * PLAYER_MOVE_SPEED;
			g_Player.move.y += cosf(0.0) * PLAYER_MOVE_SPEED;
		}

		//SPACE�L�[�Ō����؂�ւ�
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			g_Player.bMove = g_Player.bMove ? false : true;

		}

		if (g_Player.bMove == true)
		{
			g_Player.move.x += (0.0f - g_Player.move.x) * 0.55f;
			g_Player.move.y += (0.0f - g_Player.move.y) * 0.55f;
		}
		else
		{
			g_Player.move.x += (0.0f - g_Player.move.x) * PLAYER_MOVE_COEFFICIENT;
			g_Player.move.y += (0.0f - g_Player.move.y) * PLAYER_MOVE_COEFFICIENT;

		}

		//x���̕ǔ���
		if (g_Player.pos.x <= 0 + PLAYER_SIZE && GetKeyboardPress(DIK_A) == true || g_Player.pos.x >= SCREEN_WIDTH - PLAYER_SIZE && GetKeyboardPress(DIK_D) == true)
		{
			g_Player.move.x = 0;
		}
		//y���̕ǔ���
		if (g_Player.pos.y <= 0 + PLAYER_SIZE && GetKeyboardPress(DIK_W) == true || g_Player.pos.y >= SCREEN_HEIGHT - PLAYER_SIZE&& GetKeyboardPress(DIK_S) == true)
		{
			g_Player.move.y = 0;
		}

		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		//���G(�f�o�b�N�p)
		if (GetKeyboardTrigger(DIK_Q) == true&& GetKeyboardPress(DIK_LSHIFT) == true && GetKeyboardPress(DIK_RSHIFT) == true && GetKeyboardPress(DIK_0) == true)
		{
			g_Player.state = PLAYERSTATE_APPEAR;
			DebugEnemyLifeDown();
		}

		//�e�p�^�[���؂�ւ�
		if (GetKeyboardTrigger(DIK_K) == true)
		{
			g_Player.nBulletPattern++;
			g_Player.nCntBullet = 0;
		}

		if (GetKeyboardTrigger(DIK_M) == true && GetKeyboardPress(DIK_L) == false)
		{//�蓮�V���b�g
			if (g_Player.nBulletPattern % 3 == 0)
			{
				SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//����
				SetBullet(g_Player.pos, D3DXVECTOR3(-2.5f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//���㑤
				SetBullet(g_Player.pos, D3DXVECTOR3(2.5f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//�E�㑤
			}
			else if (g_Player.nBulletPattern % 3 == 1)
			{
				SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//����
				SetBullet(D3DXVECTOR3(g_Player.pos.x - 30, g_Player.pos.y + 20, 0.0f), D3DXVECTOR3(2.5f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//���㑤
				SetBullet(D3DXVECTOR3(g_Player.pos.x + 30, g_Player.pos.y + 20, 0.0f), D3DXVECTOR3(-2.5f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//�E�㑤
			}
			else
			{
				SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -7.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//����
				SetBullet(D3DXVECTOR3(g_Player.pos.x - 10, g_Player.pos.y + 15, 0.0f), D3DXVECTOR3(0.0f, -7.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//���㑤
				SetBullet(D3DXVECTOR3(g_Player.pos.x + 10, g_Player.pos.y + 15, 0.0f), D3DXVECTOR3(0.0f, -7.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//�E�㑤

			}

		}
		if (GetKeyboardPress(DIK_L) == true)
		{//�����V���b�g
			if (g_Player.nBulletPattern % 3 == 0)
			{
				if (g_nCounterAnim % 11 == 0)
				{
					SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);												 //����
					SetBullet(D3DXVECTOR3(g_Player.pos.x - 50, g_Player.pos.y + 20, 0.0f), D3DXVECTOR3(0.0f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f); //���㑤
					SetBullet(D3DXVECTOR3(g_Player.pos.x + 50, g_Player.pos.y + 20, 0.0f), D3DXVECTOR3(0.0f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);//�E�㑤
				}
			}
			else if (g_Player.nBulletPattern % 3 == 1)
			{
				if (g_nCounterAnim % 5 == 0)
				{
					SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -7.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f); //����
				}
			}
			else
			{
				if (g_nCounterAnim % 11 == 0)
				{
					SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);												 //����
					SetBullet(D3DXVECTOR3(g_Player.pos.x - (10), g_Player.pos.y + 20, 0.0f), D3DXVECTOR3(-1.0f * (1.5f + (g_Player.nCntBullet % 5)), -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f); //���㑤
					SetBullet(D3DXVECTOR3(g_Player.pos.x + (10), g_Player.pos.y + 20, 0.0f), D3DXVECTOR3(1.0f * (1.5f + (g_Player.nCntBullet % 5)), -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);//�E�㑤
					g_Player.nCntBullet++;
				}
			}
		}


		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_SIZE, g_Player.pos.y - PLAYER_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_SIZE, g_Player.pos.y - PLAYER_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_SIZE, g_Player.pos.y + PLAYER_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_SIZE, g_Player.pos.y + PLAYER_SIZE, 0.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPolygon->Unlock();
	}

}
//-----------------------------------------------------------------------------
//							�|���S���̕`�揈��
//-----------------------------------------------------------------------------
void DrawPlayer(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	if (g_Player.bDisp == true)
	{
		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//�`��
		pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

		pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

		pDevice->SetTexture(0, g_pTexturePolygon);//�e�N�X�`���̐ݒ�

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
			0,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   	       //�v���~�e�B�u�̐�
	}
}

//=============================================================================
//	�v���C���[�̎擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}

//=============================================================================
//	�_���[�W����
//=============================================================================
void HitPlayer(int nDamage)
{

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	g_Player.nLife -= nDamage;
	PlaySound(SOUND_LABEL_SE_HIT001);//��
	SetLife(g_Player.nLife);

	if (g_Player.nLife <= 0)
	{
		SetExplosion(g_Player.pos, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		g_Player.bDisp = false;
		g_Player.state = PLAYERSTATE_DEATH;
		g_Player.nCountState = 60;
		g_Score = -200000;
		AddScore(g_Score);
	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCountState = 5;
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, 0, 0, PLAYER_COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, 0, 0, PLAYER_COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, 0, 0, PLAYER_COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, 0, 0, PLAYER_COLOR_ALPHA);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPolygon->Unlock();
	}
}