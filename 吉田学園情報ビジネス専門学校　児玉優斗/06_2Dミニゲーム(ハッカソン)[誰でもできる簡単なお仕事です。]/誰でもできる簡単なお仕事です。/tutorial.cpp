//=============================================================================
//
// ゲーム画面管理クラス処理 [tutorial.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "tutorial.h"
#include "Scene2D.h"
#include "fade.h"
#include "sound.h"

//==================================================================
// 静的メンバ変数
//==================================================================
CSound *CTutorial::m_pSound = NULL;

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CTutorial::CTutorial()
{
}
CTutorial::~CTutorial()
{

}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CTutorial::Init(void)
{
	//	---<<追加>>---
	m_pSound = CManager::GetSound();
	if (m_pSound != NULL)
	{
		m_pSound->Play(CSound::BGM_TITLE);
	}

	m_nCnt = 0;

	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	if (SceneCreate(m_pScene2D[0], CScene::PRIORITY_1))
	{
		m_pScene2D[0]->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "TUTORIAL_BG");
		m_pScene2D[0]->SetPosition(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR2(640.0f, 360.0f));

	}
	if (SceneCreate(m_pScene2D[1], CScene::PRIORITY_1))
	{
		m_pScene2D[1]->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "PRESS");
		m_pScene2D[1]->SetPosition(D3DXVECTOR3(1160.0f, 680.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f));
		m_pScene2D[1]->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f / 2.0f));

	}

	//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CTutorial::Uninit(void)
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
void CTutorial::Update(void)
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
			pFade->SetFade(CManager::MODE_GAME, CFade::COLOR_WHITE);
		}
	}

	//	---<<追加>>---

	m_nCnt++;
	if ((m_nCnt % 30) == 0)
	{

		m_pScene2D[1]->SetUV(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 2.0f) * ((float)m_nCnt / 30.0f)), D3DXVECTOR2(1.0f, (1.0f / 2.0f) + (1.0f / 2.0f) * ((float)m_nCnt / 30.0f)));
	}
	if (m_nCnt >= 60)
	{
		m_nCnt = 0;

		m_pScene2D[1]->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f / 2.0f));

	}
	//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★


}

//==================================================================
// 描画処理
//==================================================================
void CTutorial::Draw(void)
{

}

