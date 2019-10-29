//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : �������D
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE	"data/TEXTURE/score.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_SCORE	(8)								// ���̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int	g_nScore;										// �X�R�A
int g_aScore[8];

//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNum = 100000000;
	int nNum1 = 10000000;
	int nCnt;

	// �X�R�A�̏�����
	g_nScore = 1000;

	for (nCnt = 0; nCnt < 8; nCnt++)
	{
		g_aScore[nCnt] = g_nScore% nNum / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
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
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^
	int nCntScore;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aScore[nCntScore] * 0.1f), 0.0f); 
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aScore[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aScore[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aScore[nCntScore] * 0.1f), 1.0f);

		pVtx += 4;		// ���_�f�[�^�̃|�C���^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
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

	// �|���S���̕`��
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntScore,
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntScore;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_���̍쐬
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(940.0f + (40.0f * nCntScore), 23.0f, 0.0f);	// �傫���c�A��
		pVtx[1].pos = D3DXVECTOR3(980.0f + (40.0f * nCntScore), 23.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(940.0f + (40.0f * nCntScore), 73.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(980.0f + (40.0f * nCntScore), 73.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �ԁA�΁A�A�����x
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddScore(int nValue)
{
	int nNum = 100000000;
	int nNum1 = 10000000;
	int nCnt;

	g_nScore += nValue;

	for (nCnt = 0; nCnt < 8; nCnt++)
	{
		g_aScore[nCnt] = g_nScore% nNum / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
int GetScore(void)
{
	return g_nScore;
	//return 25;

}