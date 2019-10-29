//=============================================================================
//
// �Q�[����ʊǗ��N���X���� [ranking.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "ranking.h"
#include "Scene2D.h"
#include "fade.h"
#include "Score.h"

//==================================================================
// �ÓI�����o�ϐ�
//==================================================================
int CRanking::m_aRankingScore[MAX_RANKING] = {};
CScore* CRanking::m_pRanking[MAX_RANKING] = {};
CSound *CRanking::m_pSound = NULL;

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CRanking::CRanking()
{
}
CRanking::~CRanking()
{

}

//==================================================================
// ����������
//==================================================================
HRESULT CRanking::Init(void)
{

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (SceneCreate(m_pRanking[nCntRanking], CScene::PRIORITY_2))
		{
			m_pRanking[nCntRanking]->Set(D3DXVECTOR3(760.0f, 70.0f + (120.0f * nCntRanking), 0.0f),
										D3DXVECTOR2(70.0f, 90.0f),m_aRankingScore[nCntRanking],D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),3);
		}
	}

	//	---<<�ǉ�>>---
	m_pSound = CManager::GetSound();
	if (m_pSound != NULL)
	{
		m_pSound->Play(CSound::BGM_RANKING);
	}

	for (int nCnt = 0; nCnt < MAX_RANKING_TEX; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	if (SceneCreate(m_pScene2D[0], CScene::PRIORITY_1))
	{
		m_pScene2D[0]->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "RANKING_BG");
		m_pScene2D[0]->SetPosition(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR2(640.0f, 360.0f));

	}
	if (SceneCreate(m_pScene2D[1], CScene::PRIORITY_2))
	{
		m_pScene2D[1]->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "RANKING_SCROLL");
		m_pScene2D[1]->SetPosition(D3DXVECTOR3(1210.0f, 360.0f, 0.0f), D3DXVECTOR2(70.0f, 640.0f));

	}
	if (SceneCreate(m_pScene2D[2], CScene::PRIORITY_2))
	{
		m_pScene2D[2]->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "RANKING_SCROLL");
		m_pScene2D[2]->SetPosition(D3DXVECTOR3(70.0f, 360.0f, 0.0f), D3DXVECTOR2(70.0f, 640.0f));

	}
	if (SceneCreate(m_pScene2D[3], CScene::PRIORITY_2))
	{
		m_pScene2D[3]->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "RANKING_RANK");
		m_pScene2D[3]->SetPosition(D3DXVECTOR3(330.0f, 350.0f, 0.0f), D3DXVECTOR2(130.0f, 290.0f));

	}
	if (SceneCreate(m_pScene2D[4], CScene::PRIORITY_2))
	{
		m_pScene2D[4]->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "PRESS");
		m_pScene2D[4]->SetPosition(D3DXVECTOR3(1160.0f, 680.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f));
		m_pScene2D[4]->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f / 2.0f));

	}


	//	���X�R�ACPP�Ő��l�Ԋu���L���Ă܂�!!
	//	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��

	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CRanking::Uninit(void)
{
	if (m_pSound != NULL)
	{
		m_pSound->StopAll();
	}
	CScene::ReleaseAll(false);
}

//==================================================================
// �X�V����
//==================================================================
void CRanking::Update(void)
{

	CFade* pFade = CManager::GetFade();
	if (CCommand::GetCommand("UP"))
	{
		//	---<<�ǉ�>>---
		if (*pFade->GetFade() == CFade::FADE_NONE)
		{
			if (m_pSound != NULL)
			{
				m_pSound->Play(CSound::SE_PUSH);
			}
		}
		//	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��

		if (pFade != NULL)
		{
			pFade->SetFade(CManager::MODE_TITLE, CFade::COLOR_WHITE);
		}
	}

	//	---<<�ǉ�>>---
	m_pScene2D[1]->SetScroll(-0.5f, 1);	//	�X�N���[��(���x�ƌ��� , �cor��)
	m_pScene2D[2]->SetScroll(0.5f, 1);	//	�X�N���[��(���x�ƌ��� , �cor��)

	m_nCnt++;
	if ((m_nCnt % 30) == 0)
	{

		m_pScene2D[4]->SetUV(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 2.0f) * ((float)m_nCnt / 30.0f)), D3DXVECTOR2(1.0f, (1.0f / 2.0f) + (1.0f / 2.0f) * ((float)m_nCnt / 30.0f)));
	}
	if (m_nCnt >= 60)
	{
		m_nCnt = 0;

		m_pScene2D[4]->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f / 2.0f));

	}
	//	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��
}

//==================================================================
// �`�揈��
//==================================================================
void CRanking::Draw(void)
{

}

//==================================================================
// �����L���O�ďW�v����
//==================================================================
void CRanking::SetRankScore(int nScore)
{
	int nRankScore = nScore;
	if (nRankScore < 0) { nRankScore = 0; }
	if (nRankScore > SCORECOUNT_MAX) { nRankScore = SCORECOUNT_MAX; }

	int nCntNum, nCntNum2;			//�X�R�A�̌����̃J�E���^�[

	for (int nCntLength = 0; nCntLength < MAX_RANKING; nCntLength++)
	{// ���ʕύX
		if (m_aRankingScore[nCntLength] < nRankScore)
		{// �㏑���j�~�̂��߂ɐ����𓦂���
			nCntNum = m_aRankingScore[nCntLength];
			m_aRankingScore[nCntLength] = nRankScore;

			// �֌W�Ȃ��Ƃ���͕��ׂȂ�for��
			for (int nCntLength2 = nCntLength + 1; nCntLength2 < MAX_RANKING; nCntLength2++)
			{// �����������Ƃ��̎��̐�������בւ�
				nCntNum2 = m_aRankingScore[nCntLength2];
				m_aRankingScore[nCntLength2] = nCntNum;
				nCntNum = nCntNum2;
			}
			break;
		}
	}


}