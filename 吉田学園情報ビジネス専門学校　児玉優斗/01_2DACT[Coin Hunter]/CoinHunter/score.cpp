//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore[2] = {};			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
int						g_nScore;						// �X�R�A
int						g_aScoreDigit[MAX_SCORE_DIGIT]; // �X�R�A�̃f�[�^

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
	for (nCntScore = 0; nCntScore < MAX_SCORE_DIGIT; nCntScore++)
	{
		g_aScoreDigit[nCntScore] = 0;
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FRAME,			// �t�@�C���̖��O
								&g_pTextureScore[0]);	// �e�N�X�`���ւ̃|�C���^

	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,			// �t�@�C���̖��O
								&g_pTextureScore[1]);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexScore(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��
	for (int nCntData = 0; nCntData < 2; nCntData++)
	{
		if (g_pTextureScore[nCntData] != NULL)
		{
			g_pTextureScore[nCntData]->Release();
			g_pTextureScore[nCntData] = NULL;
		}
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
{//�܂������Ȃ�

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
	pDevice->SetTexture(0, g_pTextureScore[0]);
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
		0,							   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
		2);		   										   //�v���~�e�B�u�̐�

	for (nCntScore = 1; nCntScore < MAX_SCORE_DIGIT + 1; nCntScore++)
	{
		pDevice->SetTexture(0, g_pTextureScore[1]);
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
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_SCORE_DIGIT + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

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
	pVtx[0].pos = D3DXVECTOR3(FRAME_INTERVAL, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH- FRAME_INTERVAL, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(FRAME_INTERVAL, 100, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH- FRAME_INTERVAL, 100, 0.0f);

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

	for (nCntData = 0; nCntData < MAX_SCORE_DIGIT; nCntData++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3((SCORE_POS_X + ((SCORE_SIZE * 1.75f) * nCntData)) - SCORE_SIZE, SCORE_POS_Y - SCORE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((SCORE_POS_X + ((SCORE_SIZE * 1.75f) * nCntData)) + SCORE_SIZE, SCORE_POS_Y - SCORE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((SCORE_POS_X + ((SCORE_SIZE * 1.75f) * nCntData)) - SCORE_SIZE, SCORE_POS_Y + SCORE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((SCORE_POS_X + ((SCORE_SIZE * 1.75f) * nCntData)) + SCORE_SIZE, SCORE_POS_Y + SCORE_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

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
	else if (g_nScore > ((int)powf(10.0f, MAX_SCORE_DIGIT + 1.0f) - 1))//�J���X�g������
	{
		g_nScore = (int)powf(10.0f, MAX_SCORE_DIGIT + 1.0f) - 1;
	}

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
	pVtx += 4;
	for (nCntData = 0; nCntData < MAX_SCORE_DIGIT; nCntData++)
	{
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
//=============================================================================
// �X�R�A�̃��Z�b�g
//=============================================================================
void ResetScore(void)
{
	g_nScore = 0;
}

//=============================================================================
// �X�R�A�̈����p��
//=============================================================================
void OverStageScore(int nScore)
{
	g_nScore = nScore;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
int GetScore(void)
{
	return g_nScore;
}
