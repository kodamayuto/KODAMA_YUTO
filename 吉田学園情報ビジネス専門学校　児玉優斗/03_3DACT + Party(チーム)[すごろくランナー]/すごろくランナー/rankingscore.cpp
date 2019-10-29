//=============================================================================
//
// �����L���O�X�R�A���� [rankingscore.cpp]
// Author : �������D
// Editor : Yuto Kodama
//
//=============================================================================
#include "rankingscore.h"
#include "score.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RANKINGSCORE	"data/TEXTURE/score.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_RANKINGSCORE		(8)							// ���̍ő吔
#define MIN_RANKINGSCORE		(6)
#define MAX_LENGTH				(5)							// �c�ɏo����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRankingscore(LPDIRECT3DDEVICE9 pDevice);		// ���_���̍쐬

															//*****************************************************************************
															// �O���[�o���ϐ�
															//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRankingscore = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingscore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int	g_nRankingscore;										// ����ւ��p(�\�[�g)
int	g_nRankingscore2;										// ����ւ��p(�\�[�g)
Ranking g_Ranking[MAX_LENGTH][MAX_RANKINGSCORE];
int g_aHighscore[MAX_LENGTH];								// 5�ϐ����i�[�ł���
bool bRanking = true;										// �����L���O�L��

int g_nDrawRanking = 4;
//=============================================================================
// ����������
//=============================================================================
void InitRankingscore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNum = 100000000;
	int nNum1 = 10000000;
	int nCnt;
	int nCntLength;

	// ������
	g_nRankingscore = 0;
	g_nRankingscore2 = 0;

	// �c�ɉ��o������for���̏�����
	for (nCntLength = 0; nCntLength < MAX_LENGTH; nCntLength++)
	{// �����ɂ��邩��for���̏�����
		for (nCnt = 0; nCnt < MAX_RANKINGSCORE; nCnt++)
		{// ���̍��W�̌v�Z 
			g_Ranking[nCntLength][nCnt].g_aRankingscore = 0;
		}
	}

	// �����̃X�R�A�̏�����
	if (bRanking == true)
	{
		g_aHighscore[0] = 10;
		g_aHighscore[1] = 20;
		g_aHighscore[2] = 30;
		g_aHighscore[3] = 40;
		g_aHighscore[4] = 50;

		bRanking = false;
	}
	// �X�R�A�̏���������
	InitScore();

	// �X�R�A�̌Ăяo��
	SetHighScore(GetScore());


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKINGSCORE,		// �t�@�C���̖��O
		&g_pTextureRankingscore);	// �e�N�X�`���ւ̃|�C���^

									// ���_���̍쐬
	MakeVertexRankingscore(pDevice);
	//// �X�R�A�Ŕ�
	//g_RankingModel[5].pos = D3DXVECTOR3(40.0f, 0.0f, 0.0f);
	//g_RankingModel[6].pos = D3DXVECTOR3(80.0f, 0.0f, 100.0f);
	//g_RankingModel[7].pos = D3DXVECTOR3(40.0f, 0.0f, 200.0f);
	//g_RankingModel[8].pos = D3DXVECTOR3(80.0f, 0.0f, 300.0f);
	//g_RankingModel[9].pos = D3DXVECTOR3(40.0f, 0.0f, 400.0f);

	//g_camera.SelectModelpos[4] = D3DXVECTOR3(20.0f, 20.0f, -80.0f);
	//g_camera.SelectModelpos[3] = D3DXVECTOR3(60.0f, 20.0f, 20.0f);
	//g_camera.SelectModelpos[2] = D3DXVECTOR3(20.0f, 20.0f, 120.0f);
	//g_camera.SelectModelpos[1] = D3DXVECTOR3(60.0f, 20.0f, 220.0f);
	//g_camera.SelectModelpos[0] = D3DXVECTOR3(20.0f, 20.0f, 320.0f);

	for (int nCntRankingscore = MIN_RANKINGSCORE; nCntRankingscore < MAX_RANKINGSCORE; nCntRankingscore++)
	{
		g_Ranking[0][nCntRankingscore].pos = D3DXVECTOR3(20.0f + (3.0f * nCntRankingscore), 15.0f, -5.0f);
		g_Ranking[1][nCntRankingscore].pos = D3DXVECTOR3(60.0f + (3.0f * nCntRankingscore), 15.0f, 95.0f);
		g_Ranking[2][nCntRankingscore].pos = D3DXVECTOR3(20.0f + (3.0f * nCntRankingscore), 15.0f, 195.0f);
		g_Ranking[3][nCntRankingscore].pos = D3DXVECTOR3(60.0f + (3.0f * nCntRankingscore), 15.0f, 295.0f);
		g_Ranking[4][nCntRankingscore].pos = D3DXVECTOR3(20.0f + (3.0f * nCntRankingscore), 15.0f, 395.0f);

		g_Ranking[0][nCntRankingscore].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ranking[1][nCntRankingscore].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ranking[2][nCntRankingscore].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ranking[3][nCntRankingscore].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ranking[4][nCntRankingscore].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}

}

//=============================================================================
// �I������
//=============================================================================
void UninitRankingscore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureRankingscore != NULL)
	{
		g_pTextureRankingscore->Release();
		g_pTextureRankingscore = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRankingscore != NULL)
	{
		g_pVtxBuffRankingscore->Release();
		g_pVtxBuffRankingscore = NULL;
	}

	// �X�R�A�̏I������
	UninitScore();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRankingscore(void)
{
	VERTEX_3D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankingscore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntLength = 0; nCntLength < MAX_LENGTH; nCntLength++)
	{

		for (int nCntRankingscore = MIN_RANKINGSCORE; nCntRankingscore < MAX_RANKINGSCORE; nCntRankingscore++)
		{
			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_Ranking[nCntLength][nCntRankingscore].g_aRankingscore * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (g_Ranking[nCntLength][nCntRankingscore].g_aRankingscore * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_Ranking[nCntLength][nCntRankingscore].g_aRankingscore * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (g_Ranking[nCntLength][nCntRankingscore].g_aRankingscore * 0.1f), 1.0f);

			pVtx += 4;		// ���_�f�[�^�̃|�C���^���S���i�߂�
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingscore->Unlock();

	// �X�R�A�̍X�V����
	UpdateScore();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRankingscore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntRankingscore;
	D3DXMATRIX mtxRot, mtxTrans, mtxView;               // �v�Z�p�}�g���b�N�X
	int nCntDraw = 0;

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//g_aRankingMatrix[nCntLength][nCntRankingscore]
	// �|���S���̕`��
	for (int nCntLength = 0; nCntLength < MAX_LENGTH; nCntLength++)
	{
		for (nCntRankingscore = MIN_RANKINGSCORE; nCntRankingscore < MAX_RANKINGSCORE; nCntRankingscore++)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix);
			//pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._11 = mtxView._11;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._12 = mtxView._21;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._13 = mtxView._31;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._21 = mtxView._12;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._22 = mtxView._22;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._23 = mtxView._32;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._31 = mtxView._13;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._32 = mtxView._23;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._33 = mtxView._33;

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Ranking[nCntLength][nCntRankingscore].rot.y,
				g_Ranking[nCntLength][nCntRankingscore].rot.x,
				g_Ranking[nCntLength][nCntRankingscore].rot.z);

			D3DXMatrixMultiply(&g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix,
				&g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix,
				&mtxRot);


			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Ranking[nCntLength][nCntRankingscore].pos.x,
				g_Ranking[nCntLength][nCntRankingscore].pos.y,
				g_Ranking[nCntLength][nCntRankingscore].pos.z);

			D3DXMatrixMultiply(&g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix,
				&g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffRankingscore, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRankingscore);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntDraw,
				2);
			nCntDraw++;
		}

	}


	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRankingscore(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntRankingscore;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_���̍쐬
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_RANKINGSCORE * MAX_LENGTH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingscore,
		NULL);

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankingscore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntLength = 0; nCntLength < MAX_LENGTH; nCntLength++)
	{
		for (nCntRankingscore = MIN_RANKINGSCORE; nCntRankingscore < MAX_RANKINGSCORE; nCntRankingscore++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-1.5f, 2.0f, 0.0f);	// ���A�c�A(��)
			pVtx[1].pos = D3DXVECTOR3(1.5f, 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-1.5f, -2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1.5f, -2.0f, 0.0f);

			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingscore->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void SetHighScore(int nScore)
{
	int nCntNum;			//�X�R�A�̌����̃J�E���^�[
	int nCntLength;
	int nCntLength2;
	int nNum = 100000000;
	int nNum2 = 10000000;

	for (nCntLength = 0; nCntLength < MAX_LENGTH; nCntLength++)
	{// ���ʕύX
		if (g_aHighscore[nCntLength] > nScore)
		{// �㏑���j�~�̂��߂ɐ����𓦂���
			g_nRankingscore = g_aHighscore[nCntLength];
			g_aHighscore[nCntLength] = nScore;

			// �֌W�Ȃ��Ƃ���͕��ׂȂ�for��
			for (nCntLength2 = nCntLength + 1; nCntLength2 < MAX_LENGTH; nCntLength2++)
			{// �����������Ƃ��̎��̐�������בւ�
				g_nRankingscore2 = g_aHighscore[nCntLength2];
				g_aHighscore[nCntLength2] = g_nRankingscore;
				g_nRankingscore = g_nRankingscore2;
			}

			break;
		}
	}

	for (nCntLength = 0; nCntLength < MAX_LENGTH; nCntLength++)
	{// �ς���������̌v�Z�̂�����
		for (nCntNum = 0; nCntNum < MAX_RANKINGSCORE; nCntNum++)
		{// ���̍��W�̌v�Z
			g_Ranking[nCntLength][nCntNum].g_aRankingscore = (g_aHighscore[nCntLength] % nNum) / nNum2;

			//�������P�����炷
			nNum = nNum / 10;
			nNum2 = nNum2 / 10;

			if (nCntNum == MAX_RANKINGSCORE - 1)
			{//����������
				nNum = 100000000;
				nNum2 = 10000000;
			}
		}
	}

	//// �X�R�A�̕`�揈��
	//DrawScore();
}
//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void SetDrawScore(int nNumScore)
{
	g_nDrawRanking = nNumScore;
}