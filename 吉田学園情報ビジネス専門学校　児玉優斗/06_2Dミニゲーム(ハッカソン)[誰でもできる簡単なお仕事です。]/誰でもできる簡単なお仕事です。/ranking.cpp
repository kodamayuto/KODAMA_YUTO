//=============================================================================
//
// ゲーム画面管理クラス処理 [ranking.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "ranking.h"
#include "Scene2D.h"
#include "fade.h"
#include "Score.h"

//==================================================================
// 静的メンバ変数
//==================================================================
int CRanking::m_aRankingScore[MAX_RANKING] = {};
CScore* CRanking::m_pRanking[MAX_RANKING] = {};
CSound *CRanking::m_pSound = NULL;

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CRanking::CRanking()
{
}
CRanking::~CRanking()
{

}

//==================================================================
// 初期化処理
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

	//	---<<追加>>---
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


	//	＊スコアCPPで数値間隔を広げてます!!
	//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★

	return S_OK;
}

//==================================================================
// 終了処理
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
// 更新処理
//==================================================================
void CRanking::Update(void)
{

	CFade* pFade = CManager::GetFade();
	if (CCommand::GetCommand("UP"))
	{
		//	---<<追加>>---
		if (*pFade->GetFade() == CFade::FADE_NONE)
		{
			if (m_pSound != NULL)
			{
				m_pSound->Play(CSound::SE_PUSH);
			}
		}
		//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★

		if (pFade != NULL)
		{
			pFade->SetFade(CManager::MODE_TITLE, CFade::COLOR_WHITE);
		}
	}

	//	---<<追加>>---
	m_pScene2D[1]->SetScroll(-0.5f, 1);	//	スクロール(速度と向き , 縦or横)
	m_pScene2D[2]->SetScroll(0.5f, 1);	//	スクロール(速度と向き , 縦or横)

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
	//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★
}

//==================================================================
// 描画処理
//==================================================================
void CRanking::Draw(void)
{

}

//==================================================================
// ランキング再集計処理
//==================================================================
void CRanking::SetRankScore(int nScore)
{
	int nRankScore = nScore;
	if (nRankScore < 0) { nRankScore = 0; }
	if (nRankScore > SCORECOUNT_MAX) { nRankScore = SCORECOUNT_MAX; }

	int nCntNum, nCntNum2;			//スコアの桁数のカウンター

	for (int nCntLength = 0; nCntLength < MAX_RANKING; nCntLength++)
	{// 順位変更
		if (m_aRankingScore[nCntLength] < nRankScore)
		{// 上書き阻止のために数字を逃がす
			nCntNum = m_aRankingScore[nCntLength];
			m_aRankingScore[nCntLength] = nRankScore;

			// 関係ないところは並べないfor文
			for (int nCntLength2 = nCntLength + 1; nCntLength2 < MAX_RANKING; nCntLength2++)
			{// 書き換えたときの次の数字を並べ替え
				nCntNum2 = m_aRankingScore[nCntLength2];
				m_aRankingScore[nCntLength2] = nCntNum;
				nCntNum = nCntNum2;
			}
			break;
		}
	}


}