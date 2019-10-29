//*****************************************************************************
//
// �����L���O���� [ranking.cpp]
// Author : Kodama Yuto
//										(:3 )�O
//*****************************************************************************
//�C���N���[�h�t�@�C��
#include"ranking.h"
//#include"score.h"
#include"fade.h"
//=============================================================================
//	�v���g�^�C�v�錾
//=============================================================================
void MakeRankingFont(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	�O���[�o���ϐ��錾
//=============================================================================
int g_nRankScore = 5000;
int g_aRankingDigit[MAX_RANKING_DIGIT] = {0,0,0,0,0,0,0,0,0,0};

int g_nCntTimer = 0;

bool g_bRankingEnter = true;	//	PRESS ENTER �̓_��
bool g_bHighScore = false;		//	�n�C�X�R�A�̍X�V
bool g_bScoreDisp = true;		//	�n�C�X�R�A���̃X�R�A�̓_��

LPDIRECT3DTEXTURE9		g_pTextureRanking[MAX_RANKING_TEXTURE] = {};			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;			// ���_�o�b�t�@�ւ̃|�C���^

LPD3DXFONT	pRankingFont = NULL;	// �t�H���g�I�u�W�F�N�g

D3DXCOLOR g_RankingFontColor;		//�t�H���g�̐F
char g_RankingText[256];	//�t�H���g�̕���[256�ŌŒ�]

RECT g_RankingRect = {	//�t�H���g��u���͈�
	550,		// �����x���W
	300,		// �����y���W
	900,		// �E����x���W
	400			// �E����y���W
};
//=============================================================================
//	���C���֐�
//=============================================================================
void InitRanking(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCntTimer = 0;
	g_bScoreDisp = true;


	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKING_01,		// �t�@�C���̖��O
		&g_pTextureRanking[0]);	// �e�N�X�`���ւ̃|�C���^
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKING_02,		// �t�@�C���̖��O
		&g_pTextureRanking[1]);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexRanking(pDevice);

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	//���b�V���t�B�[���h�̏���������
	InitMeshField();

	//���b�V���E�H�[���̏���������
	InitMeshWall();

	MakeRankingFont(pDevice);
	g_RankingFontColor = D3DXCOLOR(1.0f,1.0f,0.0f,1.0f);		//�t�H���g�̐F

	wsprintf(g_RankingText, "%d.%d", g_nRankScore / TIMER_INTERVAL, g_nRankScore % TIMER_INTERVAL);

}

//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	//���b�V���t�B�[���h�̏I������
	UninitMeshField();

	//���b�V���E�H�[���̏I������
	UninitMeshWall();

	// �e�N�X�`���̊J��
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING_TEXTURE; nCntRanking++)
	{

		if (g_pTextureRanking[nCntRanking] != NULL)
		{
			g_pTextureRanking[nCntRanking]->Release();
			g_pTextureRanking[nCntRanking] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	if (pRankingFont != NULL)
	{
		pRankingFont->Release();
		pRankingFont = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRanking(void)
{

	// �J�����̍X�V����
	UpdateCamera();

	// ���C�g�̍X�V����
	UpdateLight();

	//���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();

	//���b�V���E�H�[���̍X�V����
	UpdateMeshWall();


	FADE *pFade;
	pFade = GetFade();

	g_nCntTimer++;

 //ENTER�L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true || g_nCntTimer % 500 == 0)
	{
		if (*pFade != FADE_OUT)
		{
			SetFade(MODE_TITLE);
			StopSound();
			PlaySound(SOUND_LABEL_SE001);
		}
	}

	if (g_nCntTimer % 40 == 0 || *pFade == FADE_OUT && g_nCntTimer % 3 == 0)
	{
		g_bRankingEnter = g_bRankingEnter ? false : true;
	}

	if (g_bHighScore == true && g_nCntTimer % 10 == 0)
	{
		g_bScoreDisp = g_bScoreDisp ? false : true;
	}



}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRanking(void)
{
	// �J�����̐ݒ�
	SetCamera();

	//���b�V���t�B�[���h�̕`�揈��
	DrawMeshField();

	//���b�V���E�H�[���̕`�揈��
	DrawMeshWall();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_pTextureRanking[0]);//�e�N�X�`���̐ݒ�

	if (g_bRankingEnter == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			0,					   //�J�n���钸�_�̃C���f�b�N�X 56
			2);		   	       //�v���~�e�B�u�̐�
	}

	pDevice->SetTexture(0, g_pTextureRanking[1]);//�e�N�X�`���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
		4,					   //�J�n���钸�_�̃C���f�b�N�X 56
		2);		   	       //�v���~�e�B�u�̐�

	if (g_bScoreDisp == true)
	{
		//�t�H���g
		pRankingFont->DrawText(
			NULL,								// NULL
			g_RankingText,						// �`�悷��e�L�X�g
			-1,									// �`�悷�镶����(-1�ŏ�̃e�L�X�g�̕��������擾���Ă����)
			&g_RankingRect,						// �`��͈�(��Œ�`����RECT�^�̕ϐ��̃|�C���^������)
			DT_VCENTER | DT_LEFT,				// �`��I�v�V����
			g_RankingFontColor					// �F�w��
		);

	}


}


//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	//int nCntData;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANKING_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						// ���_����ݒ�
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(0, 550, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(400, 550, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 600, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(400, 600, 0.0f);


	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(400, 50, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(900, 50, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(400, 200, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(900, 200, 0.0f);


	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffRanking->Unlock();

}

//=============================================================================
//	�t�H���g�̍쐬
//=============================================================================
void MakeRankingFont(LPDIRECT3DDEVICE9 pDevice)
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
		&pRankingFont);				// �t�H���g�̃|�C���^
}

//=============================================================================
//	�X�R�A�̃Z�b�g
//=============================================================================
void SetRankScore(int nScore)
{

	if (nScore < g_nRankScore)
	{
		g_nRankScore = nScore;//�n�C�X�R�A�X�V
		g_bHighScore = true;
	}
	else
	{
		g_bHighScore = false;
	}

}