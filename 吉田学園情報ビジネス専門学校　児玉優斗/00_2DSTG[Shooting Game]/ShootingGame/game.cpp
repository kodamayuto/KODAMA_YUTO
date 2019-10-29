//*****************************************************************************
//
// �Q�[���̏���[game.cpp]
// Author : kodama Yuto
//
//*****************************************************************************
//�C���N���[�h�t�@�C��
#include "game.h"
#include "fade.h"
#include "pause.h"
#include"ranking.h"
//=============================================================================
//	�O���[�o���ϐ��錾
//=============================================================================
GAMESTATE g_gamestate		  = GAMESTATE_NONE;		//�Q�[���̏���
int g_nCounterGameState;    						//�J�E���^�[

bool g_bPause;				//�|�[�Y�����p  true = �|�[�Y��

//=============================================================================
//	����������
//=============================================================================
void InitGame(void)
{
	InitPause();		//�|�[�Y
	InitBG();			//�w�i
	InitPlayer();		//�v���C���[�̃|���S��
	InitBullet();		//�e
	InitExplosion();	//����
	InitScore();		//�X�R�A
	InitLife();			//���C�t
	InitPlayerMode();	//���@�̏�ԕω�
	InitEffect();		//�G�t�F�N�g
	InitEnemy();		//�G�̃|���S��
	InitBoss();			//�{�X
	InitBossOption();	//�{�X�̃I�v�V����

	 //==============//
	 //  �G���Z�b�g  //
	 //==============//

	// nCntData == �s�@nCntSetEnemy == ��
	for (int nCntData = 0; nCntData < MAX_TYPE_ENEMY / 2; nCntData++)
	{
		for (int nCntSetEnemy = 0; nCntSetEnemy < 13; nCntSetEnemy++)
		{
			SetEnemy(D3DXVECTOR3(50.0f + (100 * nCntSetEnemy), 200.0f + (-50 * nCntData), 0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f),(nCntData) % 4);
		}

	}


	//�O���[�o���ϐ��̏�����
	g_gamestate = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPause = false;

	PlaySound(SOUND_LABEL_BGM001);//��

}

//=============================================================================
//	�I������
//=============================================================================
void UninitGame(void)
{
	UninitPause();		//�|�[�Y
	UninitBG();			//�w�i
	UninitPlayer();		//�|���S��
	UninitBullet();		//�e
	UninitExplosion();	//����
	UninitScore();		//�X�R�A
	UninitLife();		//���C�t
	UninitPlayerMode();	//���@�̏�ԕω�
	UninitEffect();		//�G�t�F�N�g
	UninitEnemy();		//�G
	UninitBoss();		//�{�X
	UninitBossOption();
}

//=============================================================================
//	�X�V����
//=============================================================================
void UpdateGame(void)
{

	//�|�[�Y�@ON/OFF
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		PauseModeChange();
		SerectReset();
		DispReset();
		if (g_gamestate == GAMESTATE_NORMAL)
		{

		PlaySound(SOUND_LABEL_SE_PAUSE);//��
		}

	}

	if (g_bPause == false || g_gamestate == GAMESTATE_END || g_gamestate == GAMESTATE_NONE)
	{
		UpdateBG();			//�w�i
		UpdatePlayer();		//�|���S��
		UpdateBullet();		//�e
		UpdateExplosion();	//����
		UpdateScore();		//�X�R�A
		UpdateLife();		//���C�t
		UpdatePlayerMode();	//���@�̏�ԕω�
		UpdateEffect();		//�G�t�F�N�g
		UpdateEnemy();		//�G
		UpdateBoss();		//�{�X
		UpdateBossOption();

	}
	else if(g_bPause == true && g_gamestate != GAMESTATE_END || g_gamestate != GAMESTATE_NONE)
	{
		UpdatePause();//�|�[�Y����
	}

	switch (g_gamestate)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_END:
		BulletErese();
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			SetRankScore(GetScore());
			SetFade(MODE_RESULT);
			g_gamestate = GAMESTATE_NONE;			//���[�h�ݒ�
		}
		break;
	}
}

//=============================================================================
//	�`�揈��
//=============================================================================
void DrawGame(void)
{
	//***�e��I�u�W�F�N�g�̕`�揈��***
	DrawBG();			//�w�i
	DrawBullet();		//�e
	DrawExplosion();	//����
	DrawEffect();		//�G�t�F�N�g
	DrawEnemy();		//�G
	DrawLife();			//���C�t
	DrawPlayerMode();	//���@�̏�ԕω�
	DrawScore();		//�X�R�A
	DrawPlayer();		//���@
	DrawBoss();			//�{�X
	DrawBossOption();	//�{�X�̃I�v�V����

	if (g_bPause == true && g_gamestate == GAMESTATE_NORMAL)
	{
		DrawPause();	//�|�[�Y���
	}
}

//=============================================================================
//	�Q�[���̏�Ԃ̐ݒ�
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
	g_nCounterGameState = 0;
}

//=============================================================================
//	�Q�[���̏�Ԃ̎擾
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gamestate;
}
//=============================================================================
//	�|�[�Y��Ԃ̐؂�ւ�
//=============================================================================
void PauseModeChange(void)
{
	g_bPause = g_bPause ? false : true;
}
