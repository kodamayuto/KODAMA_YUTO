//*****************************************************************************
//
// �����L���O���� [ranking.cpp]
// Author : Kodama Yuto
//
//*****************************************************************************
//�C���N���[�h�t�@�C��
#include"ranking.h"
#include"score.h"
#include"fade.h"
#include"sound.h"

//=============================================================================
//	�O���[�o���ϐ��錾
//=============================================================================
int g_nRankScore = 0;
int g_aRankingDigit[MAX_RANKING_DIGIT] = {0,0,0,0,0,0,0,0,0,0};

int g_nCntTimer = 0;

bool g_bRankingEnter = true;	//	PRESS ENTER �̓_��
bool g_bHighScore = false;		//	�n�C�X�R�A�̍X�V
bool g_bScoreDisp = true;		//	�n�C�X�R�A���̃X�R�A�̓_��

LPDIRECT3DTEXTURE9		g_pTextureRanking[MAX_RANKING_TEXTURE] = {};			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;			// ���_�o�b�t�@�ւ̃|�C���^

//=============================================================================
//	���C���֐�
//=============================================================================
void InitRanking(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCntTimer = 0;
	g_bScoreDisp = true;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKING_00,		// �t�@�C���̖��O
		&g_pTextureRanking[0]);	// �e�N�X�`���ւ̃|�C���^

	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKING_01,		// �t�@�C���̖��O
		&g_pTextureRanking[1]);	// �e�N�X�`���ւ̃|�C���^

	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKING_02,		// �t�@�C���̖��O
		&g_pTextureRanking[2]);	// �e�N�X�`���ւ̃|�C���^

	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKING_03,		// �t�@�C���̖��O
		&g_pTextureRanking[3]);	// �e�N�X�`���ւ̃|�C���^

	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKING_04,		// �t�@�C���̖��O
		&g_pTextureRanking[4]);	// �e�N�X�`���ւ̃|�C���^

	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKING_05,		// �t�@�C���̖��O
		&g_pTextureRanking[5]);	// �e�N�X�`���ւ̃|�C���^
								// ���_���̍쐬
	MakeVertexRanking(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
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

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRanking(void)
{
	FADE *pFade;
	pFade = GetFade();

	g_nCntTimer++;
 //ENTER�L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true || g_nCntTimer % 1000 == 0)
	{
		if (*pFade != FADE_OUT)
		{
			StopSound();

			PlaySound(SOUND_LABEL_SE_DECIDE);//��

			SetFade(MODE_TITLE);
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


	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.002f * -g_nCntTimer + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.002f * -g_nCntTimer + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.002f * -g_nCntTimer + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.002f * -g_nCntTimer + 1.0f);

	pVtx += 4;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.004f * -g_nCntTimer + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.004f * -g_nCntTimer + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.004f * -g_nCntTimer + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.004f * -g_nCntTimer + 1.0f);

	pVtx += 4;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.007f * -g_nCntTimer + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.007f * -g_nCntTimer + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.007f * -g_nCntTimer + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.007f * -g_nCntTimer + 1.0f);

	g_pVtxBuffRanking->Unlock();

	// ���_����ݒ�
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 16;

	for (int nCntData = 0; nCntData < MAX_RANKING_DIGIT; nCntData++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(g_aRankingDigit[nCntData] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aRankingDigit[nCntData] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aRankingDigit[nCntData] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((g_aRankingDigit[nCntData] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();




}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntTex;
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		pDevice->SetTexture(0, g_pTextureRanking[nCntTex]);//�e�N�X�`���̐ݒ�

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			4 * nCntTex,					   //�J�n���钸�_�̃C���f�b�N�X 0 4 8
			2);		   	       //�v���~�e�B�u�̐�
	}

	pDevice->SetTexture(0, g_pTextureRanking[3]);//�e�N�X�`���̐ݒ�

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
		4 * nCntTex,					   //�J�n���钸�_�̃C���f�b�N�X 12
		2);		   	       //�v���~�e�B�u�̐�

	pDevice->SetTexture(0, g_pTextureRanking[4]);//�e�N�X�`���̐ݒ�
	for (nCntTex = 4; nCntTex < MAX_RANKING_DIGIT + 4; nCntTex++)
	{
		if(g_bScoreDisp == true)
		{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			4 * nCntTex,					   //�J�n���钸�_�̃C���f�b�N�X 16 �`�@52
			2);		   	       //�v���~�e�B�u�̐�
		}
	}

	pDevice->SetTexture(0, g_pTextureRanking[5]);//�e�N�X�`���̐ݒ�

	if (g_bRankingEnter == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			4 * nCntTex,					   //�J�n���钸�_�̃C���f�b�N�X 56
			2);		   	       //�v���~�e�B�u�̐�
	}
}


//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntData;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_RANKING_DIGIT + 5),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						// ���_����ݒ�
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < 3; nCntData++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		pVtx += 4;
	}

	pVtx[0].pos = D3DXVECTOR3(350, 100, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(900, 100, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(350, 200, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(900, 200, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	pVtx += 4;

	for (nCntData = 0; nCntData < MAX_RANKING_DIGIT; nCntData++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3((RANKING_POS_X + (50 * nCntData)) - RANKING_SIZE, RANKING_POS_Y - RANKING_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((RANKING_POS_X + (50 * nCntData)) + RANKING_SIZE, RANKING_POS_Y - RANKING_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((RANKING_POS_X + (50 * nCntData)) - RANKING_SIZE, RANKING_POS_Y + RANKING_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((RANKING_POS_X + (50 * nCntData)) + RANKING_SIZE, RANKING_POS_Y + RANKING_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(g_aRankingDigit[nCntData] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aRankingDigit[nCntData] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aRankingDigit[nCntData] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((g_aRankingDigit[nCntData] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	pVtx[0].pos = D3DXVECTOR3(800, 600, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1100, 600, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(800, 650, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1100, 650, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();


}

//=============================================================================
//	�X�R�A�̃Z�b�g
//=============================================================================
void SetRankScore(int nScore)
{

	if (nScore > g_nRankScore)
	{
		g_nRankScore = nScore;//�n�C�X�R�A�X�V
		g_bHighScore = true;
	}
	else
	{
		g_bHighScore = false;
	}

	g_aRankingDigit[0] = g_nRankScore % 10000000000 / 1000000000;
	g_aRankingDigit[1] = g_nRankScore % 1000000000 / 100000000;
	g_aRankingDigit[2] = g_nRankScore % 100000000 / 10000000;
	g_aRankingDigit[3] = g_nRankScore % 10000000 / 1000000;
	g_aRankingDigit[4] = g_nRankScore % 1000000 / 100000;
	g_aRankingDigit[5] = g_nRankScore % 100000 / 10000;
	g_aRankingDigit[6] = g_nRankScore % 10000 / 1000;
	g_aRankingDigit[7] = g_nRankScore % 1000 / 100;
	g_aRankingDigit[8] = g_nRankScore % 100 / 10;
	g_aRankingDigit[9] = g_nRankScore % 10 / 1;

}