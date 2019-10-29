//=============================================================================
//
// ゲーム画面管理クラス処理 [game.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "game.h"
#include "fade.h"
#include "Scene3D.h"

#include "ranking.h"
//==================================================================
// 静的メンバ変数
//==================================================================
CSound *CGame::m_pSound = NULL;
CScore* CGame::m_pScore = NULL;
CLife* CGame::m_pLife = NULL;

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CGame::CGame()
{
	m_pBaggage = NULL;
	m_nCntClearTimer = 0;
}
CGame::~CGame()
{

}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CGame::Init(void)
{
	if (SceneCreate(m_pGameUI, CScene::PRIORITY_1))
	{
		m_pGameUI->Set();
	}
	//	作業員
	if (SceneCreate(m_pWoker[0], CScene::PRIORITY_1))
	{
		m_pWoker[0]->Set(D3DXVECTOR3(500.0f, 1800.0f, 0.0f), D3DXVECTOR2(80.0f, 60.0f), 0);

	}
	if (SceneCreate(m_pWoker[1], CScene::PRIORITY_1))
	{
		m_pWoker[1]->Set(D3DXVECTOR3(920.0f, -200.0f, 0.0f), D3DXVECTOR2(80.0f, 60.0f), 1);
	}
	if (SceneCreate(m_pWoker[2], CScene::PRIORITY_1))
	{
		m_pWoker[2]->Set(D3DXVECTOR3(920.0f, 1100.0f, 0.0f), D3DXVECTOR2(80.0f, 60.0f), 2);
	}
	if (SceneCreate(m_pLife, CScene::PRIORITY_1))
	{
		m_pLife->Set(D3DXVECTOR3(SCREEN_WIDTH - 200, 80.0f, 0.0f), D3DXVECTOR2(80.0f, 50.0f));
	}
	if (SceneCreate(m_pControlUI, CScene::PRIORITY_1))
	{
		m_pControlUI->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 + 90, 0.0f), D3DXVECTOR2(60.0f, 60.0f));
	}

	CJudgeBaggage* pJB = NULL;
	if (SceneCreate(pJB, CScene::PRIORITY_2))
	{
		pJB->Set(D3DXVECTOR3(250.0f, SCREEN_HEIGHT * 0.425f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), CBaggage::TYPE_CARDBOARD_BOX);
	}
	if (SceneCreate(pJB, CScene::PRIORITY_2))
	{
		pJB->Set(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 570.0f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), CBaggage::TYPE_LETTER);
	}
	if (SceneCreate(pJB, CScene::PRIORITY_2))
	{
		pJB->Set(D3DXVECTOR3(1030.0f, SCREEN_HEIGHT * 0.425f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), CBaggage::TYPE_ENVELOVE);
	}
	if (SceneCreate(pJB, CScene::PRIORITY_2))
	{
		pJB->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 175, SCREEN_HEIGHT / 2 - 175, 0.0f), D3DXVECTOR2(70.0f, 70.0f), CBaggage::TYPE_TRASH);
	}

	CTruck* pT = NULL;
	if (SceneCreate(pT, CScene::PRIORITY_4))
	{
		pT->Set(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 30.0f, 0.0f));
	}

	CScene2D* p2D = NULL;
	if (SceneCreate(p2D, CScene::PRIORITY_3))
	{
		p2D->Set(D3DXVECTOR3(300.0f, 650.0f, 0.0f),"UI_スコア");
		p2D->SetPosition(D3DXVECTOR3(280.0f, 610.0f, 0.0f), D3DXVECTOR2(125.0f,65.0f));
	}
	if (SceneCreate(m_pScore, CScene::PRIORITY_4))
	{
		m_pScore->Set(D3DXVECTOR3(305.0f, 580.0f, 0.0f),
			D3DXVECTOR2(55.0f, 65.0f), 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);
	}
	//	スタートコール
	if (SceneCreate(m_pStateCall, CScene::PRIORITY_6))
	{
		m_pStateCall->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	}
	//	---<<追加>>---
	m_pSound = CManager::GetSound();
	if (m_pSound != NULL)
	{
		m_pSound->Play(CSound::BGM_GAME);
		m_pSound->Play(CSound::BGM_GAME02);

	}

	m_pScene2D = NULL;
	m_bCntFlag = false;
	m_nCnt = 0;
	if (SceneCreate(m_pScene2D, CScene::PRIORITY_6))
	{
		m_pScene2D->Set(D3DXVECTOR3(890.0f, 100.0f, 0.0f), "GAME_COUNT");
		m_pScene2D->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / 5.0f, 1.0f));

	}
	//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★

	if (SceneCreate(m_pEndCall, CScene::PRIORITY_6))
	{
		m_pEndCall->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	}


	CCommand::RegistCommand("SPACE", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_SPACE);

	CCommand::RegistCommand("CREATE", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_C);

	CCommand::RegistCommand("UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_W);
	CCommand::RegistCommand("RIGHT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_D);
	CCommand::RegistCommand("LEFT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_A);
	CCommand::RegistCommand("DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_S);

	m_nCntClearTimer = 0;

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CGame::Uninit(void)
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
void CGame::Update(void)
{
	CFade* pFade = CManager::GetFade();

	//if (CCommand::GetCommand("CREATE"))
	//{
	//	if (SceneCreate(m_pBaggage, CScene::PRIORITY_1))
	//	{
	//		int nRand = (rand() % 4) + 1;
	//		m_pBaggage->Set(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), (CBaggage::BAGGAGE_TYPE)nRand);
	//	}
	//}
	if (CCommand::GetCommand("PAUSE"))
	{
		CManager::ChangePauseFlag();
	}


	//	---<<追加>>---
	if (CManager::GetPauseFlag() == false)
	{
		TimeCount(5);	//	カウントダウン
	}

	//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★



	//if (CCommand::GetCommand("ENTER"))
	//{
	//	if (pFade != NULL)
	//	{
	//		if (*pFade->GetFade() != CFade::FADE_OUT)
	//		{
	//			CRanking::SetRankScore(m_pScore->GetScore());
	//		}
	//		pFade->SetFade(CManager::MODE_RESULT, CFade::COLOR_BLACK);
	//	}
	//}

	if (m_bClear == true)
	{
		m_nCntClearTimer++;
		if (m_nCntClearTimer >= 60)
		{
				if (pFade != NULL)
				{
					if (*pFade->GetFade() != CFade::FADE_OUT)
					{
						CRanking::SetRankScore(m_pScore->GetScore());
					}
					pFade->SetFade(CManager::MODE_RANKING, CFade::COLOR_BLACK);
				}
		}

	}
}

//==================================================================
// 描画処理
//==================================================================
void CGame::Draw(void)
{

}

void CGame::SetCountFlag(bool bFlag)
{
	m_bCntFlag = bFlag;
	m_nCnt = 0;
	m_pScene2D->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / (float)5, 1.0f));

}
//	---<<追加>>---
void CGame::TimeCount(int nNumSplit)
{
	if (CCommand::GetCommand("SPACE"))
	{
		m_bCntFlag = true;

	}
	CLife* pLife = CGame::GetLife();

	if (m_bCntFlag == true)
	{
		m_nCnt++;

		if ((m_nCnt % 30) == 0)
		{
			if (m_nCnt == 30)
			{
				if (m_pSound != NULL)
				{
					//m_pSound->Play(CSound::SE_COUNT01);
				}
			}
			if (m_nCnt == 60)
			{
				if (m_pSound != NULL)
				{
					//m_pSound->Play(CSound::SE_COUNT02);
				}
			}
			if (m_nCnt == 90)
			{
				if (m_pSound != NULL)
				{
					//m_pSound->Play(CSound::SE_COUNT03);
				}
			}
			m_pScene2D->SetUV(D3DXVECTOR2(0.0f + (1.0f / (float)nNumSplit) * ((float)m_nCnt / 30.0f), 0.0f), D3DXVECTOR2((1.0f / (float)nNumSplit) + (1.0f / (float)nNumSplit) * ((float)m_nCnt / 30.0f), 1.0f));
		}
		if (m_nCnt >= 112)
		{
			m_nCnt = 0;
			m_bCntFlag = false;
			m_pScene2D->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / (float)nNumSplit, 1.0f));
			pLife->AddLife(1);

		}
	}
}
//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★
