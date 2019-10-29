//=============================================================================
//
// �^�C�}�[���� [timer.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "timer.h"
#include "dice.h"
#include "game.h"
#include "meter.h"

//=============================================================================
//	�v���g�^�C�v�錾
//=============================================================================
void MakeTimerFont(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;						//�e�N�X�`���ւ̃|�C���^

LPD3DXFONT	pTimerFont = NULL;	// �t�H���g�I�u�W�F�N�g
D3DXCOLOR g_TimerFontColor;		//�t�H���g�̐F
char g_TimerText[256];	//�t�H���g�̕���[256�ŌŒ�]

RECT g_TimerRect = {	//�t�H���g��u���͈�
	1030,		// �����x���W
	0,			// �����y���W
	1300,		// �E����x���W
	100			// �E����y���W
};

int g_nCountTimer;		//�^�C�}�[�J�E���g�p
int g_nDiceTime;		//�T�C�R���̃^�C�}�[

bool g_bSetTimerFlag;		//�^�C�}�[�̃J�E���g����

							//=============================================================================
							//	����������
							//=============================================================================
void InitTimer(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�ϐ��̏�����
	g_nCountTimer = 0;
	g_nDiceTime = -1;
	g_TimerFontColor = D3DXCOLOR(0.3f, 1.0f, 1.0f, 1.0f);
	g_bSetTimerFlag = true;
	//�t�H���g�̍쐬
	MakeTimerFont(pDevice);

}

//=============================================================================
//	�I������
//=============================================================================
void UninitTimer(void)
{
	//�t�H���g�̉��
	if (pTimerFont != NULL)
	{
		pTimerFont->Release();
		pTimerFont = NULL;
	}

}

//=============================================================================
//	�X�V����
//=============================================================================
void UpdateTimer(void)
{
	TURNSTATE pTurnState;
	pTurnState = GetTurnState();

	if (g_bSetTimerFlag == true && g_nDiceTime != -1 && pTurnState == TURNSTATE_MOVEandATTACK)
	{
		g_nCountTimer++;
		if (g_nCountTimer == 60)
		{
			DeleteDice(2);
		}
		//�^�C�}�[�̃J�E���g�_�E��
		if (g_nCountTimer % TIMER_INTERVAL == 0)
		{
			g_nDiceTime--;

		}

		//�t�H���g�̐F�̒���
		if (g_nDiceTime > 4)
		{
			g_TimerFontColor = D3DXCOLOR(0.3f, 1.0f, 1.0f, 1.0f);

		}
		else
		{
			g_TimerFontColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		}
		if (GetMeterSize() <= 0)
		{
			g_bSetTimerFlag = false;
			g_nDiceTime = -1;
			SetGameState(GAMESTATE_OVER);
		}

		//if (GetKeyboardTrigger(DIK_L) == true)		//DEBUG
		//{
		//	g_nDiceTime = -1;
		//	SetDice(2);

		//}
		if (g_nDiceTime == 0 && g_nCountTimer % TIMER_INTERVAL == 59)
		{
			g_nDiceTime = -1;
			//SetDice(2);
			SetTurnState(TURNSTATE_END);
			g_TimerFontColor = D3DXCOLOR(0.4f, 1.0f, 1.0f, 1.0f);
		}

		//�o�͂��镶�����ݒ�
		wsprintf(g_TimerText, "%d.%d", g_nDiceTime, 60 - (g_nCountTimer % TIMER_INTERVAL));
	}

}

//=============================================================================
//	�`�揈��
//=============================================================================
void DrawTimer(void)
{
	if (g_nDiceTime != -1)
	{//�v���C���͕\��
	 //�t�H���g�̕`��
		pTimerFont->DrawText(
			NULL,								// NULL
			g_TimerText,						// �`�悷��e�L�X�g
			-1,									// �`�悷�镶����(-1�ŏ�̃e�L�X�g�̕��������擾���Ă����)
			&g_TimerRect,						// �`��͈�(��Œ�`����RECT�^�̕ϐ��̃|�C���^������)
			DT_VCENTER | DT_LEFT,				// �`��I�v�V����
			g_TimerFontColor					// �F�w��
		);
	}

}

//=============================================================================
//	�^�C�}�[�Z�b�g
//=============================================================================
void SetTimer(int nTime)
{
	//�擾�����o�ڂɉ����Ď��Ԃ����߁A�J�E���g���J�n����
	g_nDiceTime = nTime * TIMER_COUNT_COEFFICIENT - 1;
	g_nCountTimer = 0;

	//�o�͂��镶�����ݒ�
	wsprintf(g_TimerText, "%d.%d", g_nDiceTime, 60 - (g_nCountTimer % TIMER_INTERVAL));

}

//=============================================================================
//	�t�H���g�̍쐬
//=============================================================================
void MakeTimerFont(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXCreateFont(
		pDevice,					// �f�o�C�X�̃|�C���^
		80,							// ����
		40,							// ��
		FW_BLACK,					// �t�H���g�̑���
		NULL,						// ����
		FALSE,						// �Α�(TRUE��on,FALSE��off)
		SHIFTJIS_CHARSET,			// �����Z�b�g
		OUT_DEFAULT_PRECIS,			// �o�͐��x(OUT_DEFAULT_PRECIS�ŌŒ�)
		PROOF_QUALITY,				// �����̕i��
		FIXED_PITCH | FF_SCRIPT,	// �s�b�`�ƃt�@�~���̃C���f�b�N�X
		TEXT("Meiryo UI"),			// �t�H���g��(�󔒁A�啶�����܂߂Đ��m�ɓ��͂��邱��)
		&pTimerFont);				// �t�H���g�̃|�C���^

}

//=============================================================================
//	�^�C�}�[�̎擾
//=============================================================================
int GetTimer(void)
{
	return g_nDiceTime;
}

//=============================================================================
//	�^�C�}�[�̃J�E���g�t���O�̏�Ԃ��擾
//=============================================================================
bool GetSetTimerFlag(void)
{
	return g_bSetTimerFlag;
}
