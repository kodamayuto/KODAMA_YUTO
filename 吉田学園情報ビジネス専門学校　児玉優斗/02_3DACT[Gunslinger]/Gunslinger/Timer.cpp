//=============================================================================
//
// �^�C�}�[���� [timer.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "Timer.h"
#include "fade.h"
//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_TIMER_POLYGON (2)

//=============================================================================
//	�v���g�^�C�v�錾
//=============================================================================
void MakeTimerFont(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTimer[MAX_TIMER_POLYGON] = {};						//�e�N�X�`���ւ̃|�C���^

LPD3DXFONT	pTimerFont = NULL;	// �t�H���g�I�u�W�F�N�g
D3DXCOLOR g_TimerFontColor;		//�t�H���g�̐F
char g_TimerText[256];	//�t�H���g�̕���[256�ŌŒ�]

RECT g_TimerRect = {	//�t�H���g��u���͈�
	990,		// �����x���W
	10,			// �����y���W
	1300,		// �E����x���W
	110			// �E����y���W
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

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/timer.png", &g_pTextureTimer[1]);

	//�ϐ��̏�����
	g_nCountTimer = 0;
	g_nDiceTime = 0;
	g_TimerFontColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_bSetTimerFlag = true;
	//�t�H���g�̍쐬
	MakeTimerFont(pDevice);
	MakeVertexTimer(pDevice);
}

//=============================================================================
//	�I������
//=============================================================================
void UninitTimer(void)
{
	//�e�N�X�`���̉��
	for (int nCntTex = 0; nCntTex < MAX_TIMER_POLYGON; nCntTex++)
	{
		if (g_pTextureTimer[nCntTex] != NULL)
		{
			g_pTextureTimer[nCntTex]->Release();
			g_pTextureTimer[nCntTex] = NULL;
		}

	}
	//�o�b�t�@�̉��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;

	}
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
	GAMESTATE pGamestate;
	pGamestate = GetGameState();
	FADE *pFade;
	pFade = GetFade();

		//�^�C�}�[�̃J�E���g�_�E��
		if (*pFade != FADE_OUT)
		{
		g_nCountTimer++;
			if (g_nCountTimer % TIMER_INTERVAL == 0 && pGamestate != GAMESTATE_END)
			{
				g_nDiceTime++;

			}
			//�o�͂��镶�����ݒ�
			wsprintf(g_TimerText, "%d.%d", g_nCountTimer / TIMER_INTERVAL, g_nCountTimer % TIMER_INTERVAL);

		}

}

//=============================================================================
//	�`�揈��
//=============================================================================
void DrawTimer(void)
{

	for (int nCntTimer = 0; nCntTimer < MAX_TIMER_POLYGON; nCntTimer++)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = GetDevice();

		pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

		pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

									   // �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTimer[nCntTimer]);//�e�N�X�`���̐ݒ�

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
			4 * nCntTimer,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   	       //�v���~�e�B�u�̐�
	}
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

//=============================================================================
//	�t�H���g�̍쐬
//=============================================================================
void MakeTimerFont(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXCreateFont(
		pDevice,					// �f�o�C�X�̃|�C���^
		60,							// ����
		30,							// ��
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

int GetTimer(void)
{
	return g_nCountTimer;
}

//=============================================================================
//	���_���̒ǉ�
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	for (int nCntTimer = 0; nCntTimer < MAX_TIMER_POLYGON; nCntTimer++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntTimer;
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(970.0f, 0.0f + ((MAX_TIMER_POLYGON-nCntTimer) * 10.0f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1200.0f, 0.0f + ((MAX_TIMER_POLYGON - nCntTimer) * 10.0f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(970.0f, 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1200.0f, 100.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[	��
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTimer->Unlock();

	}

}
