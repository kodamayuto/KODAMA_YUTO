//=============================================================================
//
// ゲーム画面管理クラス処理 [title.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "title.h"
#include "Manager.h"
#include "fade.h"
#include "sound.h"

#include "sceneBillboard.h"

//==================================================================
// 静的メンバ変数
//==================================================================
CSound *CTitle::m_pSound = NULL;
//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CTitle::CTitle()
{
	m_pTitleLogo = NULL;
	m_pPressEnter = NULL;
}
CTitle::~CTitle()
{

}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CTitle::Init(void)
{
	m_nCount = 0;


	//	---<<追加>>---
	m_pSound = CManager::GetSound();
	if (m_pSound != NULL)
	{
		m_pSound->Play(CSound::BGM_TITLE);
	}

	m_nStopTime = 0;
	m_bEnterStop = false;
	m_nCnt = 0;

	for (int nCnt = 0; nCnt < MAX_TITLE_TEX; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	if (SceneCreate(m_pScene2D[0], CScene::PRIORITY_1))
	{
		m_pScene2D[0]->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "TITLE_BG");
		m_pScene2D[0]->SetPosition(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR2(640.0f, 360.0f));

	}
	if (SceneCreate(m_pScene2D[1], CScene::PRIORITY_1))
	{
		m_pScene2D[1]->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "TITLE_SCROLL");
		m_pScene2D[1]->SetPosition(D3DXVECTOR3(1280.0f, 360.0f, 0.0f), D3DXVECTOR2(1280.0f, 120.0f));

	}
	if (SceneCreate(m_pScene2D[2], CScene::PRIORITY_1))
	{
		m_pScene2D[2]->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "PRESS");
		m_pScene2D[2]->SetPosition(D3DXVECTOR3(640.0f, 630.0f, 0.0f), D3DXVECTOR2(200.0f, 80.0f));
		m_pScene2D[2]->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f / 2.0f));

	}

	//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★
	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CTitle::Uninit(void)
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
void CTitle::Update(void)
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
		m_bEnterStop = true;
		m_pScene2D[1]->Uninit();
		m_pScene2D[1] = NULL;
		if (SceneCreate(m_pScene2D[1], CScene::PRIORITY_1))
		{
			m_pScene2D[1]->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "TITLE_SCROLL");
			m_pScene2D[1]->SetPosition(D3DXVECTOR3(0.0f, 360.0f, 0.0f), D3DXVECTOR2(1280.0f, 120.0f));
		}
		//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★

		if (pFade != NULL)
		{

			pFade->SetFade(CManager::MODE_TUTORIAL,CFade::COLOR_WHITE);
		}
	}

	//	---<<追加>>---
	m_nStopTime++;
	if (m_bEnterStop == false)
	{
		if (m_nStopTime <= 250)
		{
			if (m_pScene2D[1] != NULL)
			{
				m_pScene2D[1]->SetScroll(-0.2f, 0);	//	スクロール(速度と向き , 縦or横)
			}
		}
	}

	m_nCnt++;
	if ((m_nCnt % 30) == 0)
	{

		m_pScene2D[2]->SetUV(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 2.0f) * ((float)m_nCnt / 30.0f)), D3DXVECTOR2(1.0f, (1.0f / 2.0f) + (1.0f / 2.0f) * ((float)m_nCnt / 30.0f)));
	}
	if (m_nCnt >= 60)
	{
		m_nCnt = 0;

		m_pScene2D[2]->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f / 2.0f));

	}
	//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★

}

//==================================================================
// 描画処理
//==================================================================
void CTitle::Draw(void)
{

}

