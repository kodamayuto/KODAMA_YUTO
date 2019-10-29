//*****************************************************************************
//
// �Q�[���̏���[game.cpp]
// Author : kodama Yuto
//     (:3 )�O
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
int g_nStage;

//=============================================================================
//	����������
//=============================================================================
void InitGame(int nNumStage)
{
	InitPause();
	g_nStage = nNumStage;

	InitBG();					//�w�i�̏���
	InitEnemy();				//�G�L�����̏���
	InitBlock();				//�u���b�N�̏���
	InitPlayer();				//�v���C���[�̏���
	InitItem();					//�A�C�e���̏���
	InitScore();				//�X�R�A�̏���
	InitTime();					//�������Ԃ̏���

	MakeStageSet(g_nStage);

	//�O���[�o���ϐ��̏�����
	g_gamestate = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPause = false;
}

//=============================================================================
//	�I������
//=============================================================================
void UninitGame(void)
{
	UninitPause();

	UninitBG();				//�w�i�̏���
	UninitPlayer();			//�v���C���[�̏���
	UninitEnemy();			//�G�L�����̏���
	UninitBlock();			//�u���b�N�̏���
	UninitItem();			//�A�C�e���̏���
	UninitScore();			//�X�R�A�̏���
	UninitTime();			//�������Ԃ̏���

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
		PlaySound(SOUND_LABEL_SE_002);
		SerectReset();
		DispReset();
	}

	if (g_bPause == false || g_gamestate == GAMESTATE_END || g_gamestate == GAMESTATE_NONE)
	{
		UpdateBG();				//�w�i�̏���
		UpdateBlock();			//�u���b�N�̏���
		UpdatePlayer();			//�v���C���[�̏���
		UpdateEnemy();			//�G�L�����̏���
		UpdateItem();			//�A�C�e���̏���
		UpdateScore();			//�X�R�A�̏���
		UpdateTime();			//�������Ԃ̏���
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
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			if (g_nStage < MAX_STAGE)
			{
				SetFade(MODE_CHANGE);
				OverStageScore(GetScore());
				g_gamestate = GAMESTATE_NONE;			//���[�h�ݒ�
			}
			else
			{
				SetRankScore(GetScore());
				SetFade(MODE_RESULT);
				StopSound(SOUND_LABEL_BGM001);
				g_gamestate = GAMESTATE_NONE;			//���[�h�ݒ�
			}
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
	DrawBG();				//�w�i�̏���
	DrawPlayer();			//�v���C���[�̏���
	DrawEnemy();			//�G�L�����̏���
	DrawItem();				//�A�C�e���̏���
	DrawBlock();			//�u���b�N�̏���
	DrawScore();			//�X�R�A�̏���
	DrawTime();				//�������Ԃ̏���

	if (g_bPause == true && g_gamestate == GAMESTATE_NORMAL)
	{
		DrawPause();	//�|�[�Y���
	}
}

//=============================================================================
//	�X�e�[�W�Z�b�g
//=============================================================================
void MakeStageSet(int nNumStage)
{
	SetBlock(D3DXVECTOR3(-200, 700, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1500.0f, 40.0f, BLOCKTYPE_NORMAL);
	switch (nNumStage)
	{
	case 1:
		//�u���b�N�Z�b�g(��)
		/*��*/
		SetBlock(D3DXVECTOR3(-200, -40, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1500.0f, 50.0f, BLOCKTYPE_NORMAL);


		SetBlock(D3DXVECTOR3(-40, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 770.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(350, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 770.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(800, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 770.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1270, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 770.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(-50, 500, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 660.0f, 30.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(190, 350, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 660.0f, 30.0f, BLOCKTYPE_NORMAL);


		SetBlock(D3DXVECTOR3(850, 500, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 100.0f, 50.0f, BLOCKTYPE_MOVE);
		SetBlock(D3DXVECTOR3(1000, 450, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, 30.0f, BLOCKTYPE_INV);
		SetBlock(D3DXVECTOR3(1150, 450, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 30.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1150, 300, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 30.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1150, 150, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 30.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(200, 200, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, 30.0f, BLOCKTYPE_NORMAL);

		/*���[�v�u���b�N*/
		SetBlock(D3DXVECTOR3(300, 695, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_IN);
		SetBlock(D3DXVECTOR3(50, 495, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_OUT);

		SetBlock(D3DXVECTOR3(310, 195, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_IN);
		SetBlock(D3DXVECTOR3(400, 345, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_OUT);

		SetBlock(D3DXVECTOR3(550, 345, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_IN);
		SetBlock(D3DXVECTOR3(400, 495, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_OUT);

		SetBlock(D3DXVECTOR3(400, 695, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_IN);
		SetBlock(D3DXVECTOR3(750, 345, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_OUT);

		SetBlock(D3DXVECTOR3(630, 345, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_IN);
		SetBlock(D3DXVECTOR3(1200, 695, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_OUT);

		SetBlock(D3DXVECTOR3(1230, 445, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_IN);
		SetBlock(D3DXVECTOR3(100, 695, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_OUT);

		/*�R�C��*/
		SetItem(D3DXVECTOR3(265, 560, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(300, 400, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(265, 300, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(1250, 50, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(650, 500, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(650, 550, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(650, 600, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(900, 350, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(900, 450, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(900, 550, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5000, ITEM_SCOREUP_COIN);


		break;


	case 2:
		//�u���b�N�Z�b�g(��)
		/*��*/

		SetBlock(D3DXVECTOR3(240, 600, 0.0f), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 200.0f, 200.0f, BLOCKTYPE_MOVE);
		SetBlock(D3DXVECTOR3(0, 400, 0.0f), D3DXVECTOR3(0.0f, 1.5f, 0.0f), 100.0f, 50.0f, BLOCKTYPE_MOVE);

		SetBlock(D3DXVECTOR3(190, 300, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 300.0f, BLOCKTYPE_NORMAL);//�n�_

																											  /*���ꏰ*/

		SetBlock(D3DXVECTOR3(240, 300, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, BLOCKTYPE_FALL);
		SetBlock(D3DXVECTOR3(290, 300, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, BLOCKTYPE_FALL);
		SetBlock(D3DXVECTOR3(340, 300, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, BLOCKTYPE_FALL);
		SetBlock(D3DXVECTOR3(390, 300, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, BLOCKTYPE_FALL);
		SetBlock(D3DXVECTOR3(440, 300, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, BLOCKTYPE_FALL);
		SetBlock(D3DXVECTOR3(490, 300, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, BLOCKTYPE_FALL);
		SetBlock(D3DXVECTOR3(540, 300, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, BLOCKTYPE_FALL);
		SetBlock(D3DXVECTOR3(590, 300, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, BLOCKTYPE_FALL);
		SetBlock(D3DXVECTOR3(640, 300, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, BLOCKTYPE_FALL);

		SetBlock(D3DXVECTOR3(690, 320, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, BLOCKTYPE_NORMAL);//�I�_
		SetBlock(D3DXVECTOR3(790, 320, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, BLOCKTYPE_NORMAL);

		SetBlock(D3DXVECTOR3(670, 420, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(770, 420, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, BLOCKTYPE_NORMAL);

		/*�K�i*/
		//���
		SetBlock(D3DXVECTOR3(800, 680, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 20.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(820, 660, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 180.0f, 20.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(840, 640, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 20.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(860, 620, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 140.0f, 20.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(880, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f, 20.0f, BLOCKTYPE_NORMAL);

		//����
		SetBlock(D3DXVECTOR3(1000, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f, 20.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1000, 620, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 140.0f, 20.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1000, 640, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 20.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1000, 660, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 180.0f, 20.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1000, 680, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 20.0f, BLOCKTYPE_NORMAL);

		SetBlock(D3DXVECTOR3(980, 30, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 280.0f, 40.0f, BLOCKTYPE_NORMAL);

		//�A�C�e���Z�b�g(��)
		SetItem(D3DXVECTOR3(265, 260, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(315, 260, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(365, 260, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(415, 260, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(465, 260, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(515, 260, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(565, 260, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(615, 260, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(665, 260, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(540, 670, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(1000, 400, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(1000, 450, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(1000, 500, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(1000, 550, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(50, 400, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(50, 300, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(50, 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(750, 400, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(265, 360, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);

		break;


	case 3:
		//�u���b�N�Z�b�g(��)
		/*��*/
		SetBlock(D3DXVECTOR3(-40, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 770.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1270, 0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 770.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(400, 150, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 600.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(-50, 400, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 240.0f, 30.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1190, 150, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 40.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1190, 300, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 40.0f, BLOCKTYPE_NORMAL);

		SetBlock(D3DXVECTOR3(700, 500, 0.0f), D3DXVECTOR3(0.0f, 1.5f, 0.0f), 100.0f, 50.0f, BLOCKTYPE_MOVE);

		SetBlock(D3DXVECTOR3(320, 400, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 40.0f, BLOCKTYPE_ATTACK_MOVE);
		SetBlock(D3DXVECTOR3(320, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 40.0f, BLOCKTYPE_ATTACK_MOVE);
		SetBlock(D3DXVECTOR3(480, 600, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, BLOCKTYPE_ATTACK_MOVE);

		SetBlock(D3DXVECTOR3(1060, 550, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, BLOCKTYPE_ATTACK_MOVE);
		SetBlock(D3DXVECTOR3(1140, 550, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, BLOCKTYPE_ATTACK_MOVE);

		SetBlock(D3DXVECTOR3(50, 550, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, BLOCKTYPE_RESET);

		SetItem(D3DXVECTOR3(265, 560, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(30, 370, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(70, 370, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(110, 370, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(440, 120, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);

		SetItem(D3DXVECTOR3(500, 220, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(500, 320, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(500, 420, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(500, 520, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);

		SetItem(D3DXVECTOR3(750, 370, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(750, 420, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(750, 470, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(750, 520, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);

		SetItem(D3DXVECTOR3(1250, 120, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5000, ITEM_SCOREUP_COIN);

		break;
	case 4:
		SetBlock(D3DXVECTOR3(-200, -100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1500.0f, 50.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(-40, -100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 1000.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1270, -100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 1000.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(540, 440, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 160.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(720, 440, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 400.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(630, 170, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 400.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(0, 640, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f, 80.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(100, 100, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f, 20.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(910, 90, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f, 20.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1150, 520, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 40.0f, BLOCKTYPE_NORMAL);
		SetBlock(D3DXVECTOR3(1080, 660, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, BLOCKTYPE_NORMAL);

		SetBlock(D3DXVECTOR3(0, 300, 0.0f), D3DXVECTOR3(0.0f, 1.5f, 0.0f), 80.0f, 40.0f, BLOCKTYPE_MOVE);
		SetBlock(D3DXVECTOR3(850, 440, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 80.0f, 40.0f, BLOCKTYPE_MOVE);
		SetBlock(D3DXVECTOR3(350, 550, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 80.0f, 40.0f, BLOCKTYPE_MOVE);

		SetBlock(D3DXVECTOR3(460, 400, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 20.0f, BLOCKTYPE_FALL);

		SetBlock(D3DXVECTOR3(1150, 695, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_IN);
		SetBlock(D3DXVECTOR3(200, 695, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_OUT);

		SetBlock(D3DXVECTOR3(1080, 660, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 60.0f, BLOCKTYPE_INV);

		SetBlock(D3DXVECTOR3(650, 695, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_IN);
		SetBlock(D3DXVECTOR3(800, 695, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 30.0f, BLOCKTYPE_WARP_OUT);

		SetBlock(D3DXVECTOR3(550, 240, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 40.0f, BLOCKTYPE_ATTACK_MOVE);
		SetBlock(D3DXVECTOR3(650, 240, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 40.0f, BLOCKTYPE_ATTACK_MOVE);

		SetItem(D3DXVECTOR3(50, 170, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 6000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(50, 220, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 5000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(50, 270, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 4000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(50, 320, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 3000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(50, 370, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 2000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(50, 420, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(600, 370, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(600, 420, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(680, 370, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(680, 420, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(770, 570, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(770, 620, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(770, 670, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(900, 70, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(950, 70, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000, ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(1000, 70, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000,ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(1050, 70, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 1000,ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(1100, 70, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 10000,ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(1150, 70, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 10000,ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(1200, 70, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 10000,ITEM_SCOREUP_COIN);
		SetItem(D3DXVECTOR3(1250, 70, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 10000,ITEM_SCOREUP_COIN);

		break;
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

