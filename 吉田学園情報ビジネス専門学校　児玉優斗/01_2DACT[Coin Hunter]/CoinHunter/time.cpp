//=============================================================================
//
// �^�C������ [time.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "time.h"
#include "fade.h"

//**************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime[2] = {};			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
Time					g_nTime;						// �^�C��
int						g_aTimeDigit[MAX_TIME_DIGIT];   // �^�C���̃f�[�^

int g_nCounterTime;		//�J�E���^�[
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// ����������
//=============================================================================
void InitTime(void)
{
	int nCntTime;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nCounterTime = TIME_INTERVAL;
	g_nTime.col = D3DXCOLOR(1.0f,0.5f,0.0f,1.0f);
	g_nTime.nTime = 100;
	g_nTime.bScoreFlag = true;


	for (nCntTime = 0; nCntTime < MAX_TIME_DIGIT; nCntTime++)
	{
		g_aTimeDigit[nCntTime] = 0;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TIME,		// �t�@�C���̖��O
								&g_pTextureTime[0]);	// �e�N�X�`���ւ̃|�C���^
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TIME_1,		// �t�@�C���̖��O
								&g_pTextureTime[1]);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexTime(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureTime[nCntTex] != NULL)
		{
			g_pTextureTime[nCntTex]->Release();
			g_pTextureTime[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTime(void)
{//�܂������Ȃ�
 //�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	FADE *pFade;
	pFade = GetFade();
	int nCntTime;
	if (GetNumCoin() != 0)//�R�C�����O�ɂȂ�܂ŃJ�E���^�[����
	{
		g_nCounterTime--;
	}
	else if(GetNumCoin() == 0 && g_nTime.bScoreFlag == true)
	{
		AddScore(((g_nTime.nTime * 100) + (TIME_INTERVAL - g_nCounterTime)) * 10);
		g_nTime.bScoreFlag = false;
		SetGameState(GAMESTATE_END);
	}
	if (g_nCounterTime  == 0 && g_nTime.nTime > 0)
	{
		g_nTime.nTime--;
		g_nCounterTime = TIME_INTERVAL;
	}
	else if (g_nCounterTime == 0 && g_nTime.nTime <= 0)
	{
		SetRankScore(GetScore());
		SetFade(MODE_RESULT);
		StopSound(SOUND_LABEL_BGM001);
	}

	if (g_nTime.nTime <= 50)
	{
		g_nTime.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}

	g_aTimeDigit[0] = g_nTime.nTime % 1000 / 100;
	g_aTimeDigit[1] = g_nTime.nTime % 100 /  10;
	g_aTimeDigit[2] = g_nTime.nTime % 10 /   1;

	// ���_����ݒ�
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_TIME_DIGIT; nCntTime++)
	{
		pVtx[0].col = g_nTime.col;
		pVtx[1].col = g_nTime.col;
		pVtx[2].col = g_nTime.col;
		pVtx[3].col = g_nTime.col;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(g_aTimeDigit[nCntTime] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aTimeDigit[nCntTime] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aTimeDigit[nCntTime] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((g_aTimeDigit[nCntTime] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntTime;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�

	for (nCntTime = 0; nCntTime < MAX_TIME_DIGIT; nCntTime++)
	{
	pDevice->SetTexture(0, g_pTextureTime[0]);
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
			4 * nCntTime,							   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   										   //�v���~�e�B�u�̐�
	}
	pDevice->SetTexture(0, g_pTextureTime[1]);
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
		4 * nCntTime,							   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
		2);		   										   //�v���~�e�B�u�̐�

}

//=============================================================================
// ���_���̍쐬
//==========================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntTime;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_TIME_DIGIT + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	// ���_����ݒ�
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_TIME_DIGIT; nCntTime++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3((TIME_POS_X + ((TIME_SIZE * 1.75f) * nCntTime)) - TIME_SIZE, TIME_POS_Y - TIME_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((TIME_POS_X + ((TIME_SIZE * 1.75f) * nCntTime)) + TIME_SIZE, TIME_POS_Y - TIME_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((TIME_POS_X + ((TIME_SIZE * 1.75f) * nCntTime)) - TIME_SIZE, TIME_POS_Y + TIME_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((TIME_POS_X + ((TIME_SIZE * 1.75f) * nCntTime)) + TIME_SIZE, TIME_POS_Y + TIME_SIZE, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	pVtx[0].pos = D3DXVECTOR3(580, 10, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(700, 10, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(580, 60, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(700, 60, 0.0f);

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


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();


}


//
//
//
int GetTime(void)
{
	return g_nTime.nTime;
}
