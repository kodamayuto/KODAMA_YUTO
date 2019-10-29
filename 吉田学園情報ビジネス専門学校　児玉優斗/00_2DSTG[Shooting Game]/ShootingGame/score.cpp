//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_SCORE_DIGIT (8)									//����
#define SCORE_SIZE      (20.0f)								//�X�R�A�̑傫��

#define SCORE_POS_X (1000)									//�X�R�A��X��
#define SCORE_POS_Y (700)									//�X�R�A��Y��

#define COLOR_COUNT_NUM (20)								//�X�R�A�̐F�ύX����
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
int						g_nScore;						// �X�R�A
int						g_aScoreDigit[MAX_SCORE_DIGIT]; // �X�R�A�̃f�[�^
int						g_aScoreDigitOld[MAX_SCORE_DIGIT]; // �X�R�A�̈�O�̃f�[�^
int						g_aScoreColorCounter[MAX_SCORE_DIGIT];//�X�R�A�̐F�ύX�J�E���^
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{
	int nCntScore;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nScore = 00000000;		//����
	for (nCntScore = 0; nCntScore < MAX_SCORE_DIGIT; nCntScore++)
	{
		g_aScoreDigit[nCntScore] = 0;
		g_aScoreDigitOld[nCntScore] = 0;
		g_aScoreColorCounter[nCntScore] = 0;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
								&g_pTextureScore);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexScore(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^


	for (int nCntData = 0; nCntData < MAX_SCORE_DIGIT; nCntData++)
	{
		if (g_aScoreColorCounter[nCntData] > 0)
		{
			g_aScoreColorCounter[nCntData]--;

			if (g_aScoreColorCounter[nCntData] == 0)
			{
				// ���_����ݒ�
				g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += 4 * nCntData;

				//���_�J���[
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffScore->Unlock();

				g_aScoreColorCounter[nCntData] = 0;
			}
		}
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntScore;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < MAX_SCORE_DIGIT; nCntScore++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
			4 * nCntScore,							   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   										   //�v���~�e�B�u�̐�
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntData;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE_DIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	// ���_����ݒ�
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < MAX_SCORE_DIGIT; nCntData++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3((SCORE_POS_X + (32.0f * nCntData)) - SCORE_SIZE, SCORE_POS_Y - SCORE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((SCORE_POS_X + (32.0f * nCntData)) + SCORE_SIZE, SCORE_POS_Y - SCORE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((SCORE_POS_X + (32.0f * nCntData)) - SCORE_SIZE, SCORE_POS_Y + SCORE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((SCORE_POS_X + (32.0f * nCntData)) + SCORE_SIZE, SCORE_POS_Y + SCORE_SIZE, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();


}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddScore(int nValue)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	int nCntData;

	g_nScore += nValue;
	if (g_nScore < 0)
	{
		g_nScore = 0;
	}

	//���݂̌��ԍ���������
	for (nCntData = 0; nCntData < MAX_SCORE_DIGIT; nCntData++)
	{
		g_aScoreDigitOld[nCntData] = g_aScoreDigit[nCntData];
	}

	//g_aScoreDigit[0] = g_nScore % 10000000000 / 1000000000;
	//g_aScoreDigit[1] = g_nScore % 1000000000 / 100000000;
	g_aScoreDigit[0] = g_nScore % 100000000 / 10000000;
	g_aScoreDigit[1] = g_nScore % 10000000 / 1000000;
	g_aScoreDigit[2] = g_nScore % 1000000 / 100000;
	g_aScoreDigit[3] = g_nScore % 100000 / 10000;
	g_aScoreDigit[4] = g_nScore % 10000 / 1000;
	g_aScoreDigit[5] = g_nScore % 1000 / 100;
	g_aScoreDigit[6] = g_nScore % 100 / 10;
	g_aScoreDigit[7] = g_nScore % 10 / 1;


	// ���_����ݒ�
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < MAX_SCORE_DIGIT; nCntData++)
	{
		if (g_aScoreDigitOld[nCntData] != g_aScoreDigit[nCntData])
		{//�O��̌��ԍ��ƍ���̌��ԍ�������Ă�����
			pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 255);

			g_aScoreColorCounter[nCntData] = COLOR_COUNT_NUM;
		}

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(g_aScoreDigit[nCntData] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aScoreDigit[nCntData] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aScoreDigit[nCntData] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((g_aScoreDigit[nCntData] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//
//
//
int GetScore(void)
{
	return g_nScore;
}
