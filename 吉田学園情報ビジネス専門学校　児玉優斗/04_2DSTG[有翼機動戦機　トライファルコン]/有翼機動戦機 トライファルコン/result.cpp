//=============================================================================
//
// ゲーム画面管理クラス処理 [title.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "result.h"
#include "Manager.h"
#include "game.h"
#include "fade.h"
#include "number.h"
#include "ranking.h"
//
//
//
CScore* CResult::m_pScore = NULL;
LPDIRECT3DTEXTURE9 CResult::m_apTexture[4] = {};
//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CResult::CResult()
{
	m_pScore = NULL;
	for (int nCntBG = 0; nCntBG < 3; nCntBG++)
	{
		m_apBG[nCntBG] = NULL;
	}
	m_nCount = 0;
}
CResult::~CResult()
{

}

CResult* CResult::Create(void)
{
	CResult* pResult = NULL;

	pResult = new CResult;

	if (pResult != NULL)
	{
		pResult->Init();
	}
	return pResult;
}

//==================================================================
// テクスチャ読み込み＆解放
//==================================================================
HRESULT CResult::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/result000.png", &m_apTexture[3]);

	return S_OK;
}
void CResult::Unload(void)
{
	for (int nCntTex = 0; nCntTex < 4; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}

	}
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CResult::Init(void)
{
	CSound* pSound = CManager::GetSound();

	for (int nCntBG = 0; nCntBG < 3; nCntBG++)
	{
		m_apBG[nCntBG] = CScene2D::Create(4);
		m_apBG[nCntBG]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		m_apBG[nCntBG]->BindTexture(m_apTexture[nCntBG]);
	}

	CScene2D *pResult = CScene2D::Create(4);
	pResult->SetPosition(D3DXVECTOR3(100.0f,100.0f,0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(400.0f, 100.0f, 0.0f));
	pResult->BindTexture(m_apTexture[3]);


	m_pScore = CScore::Create(D3DXVECTOR3(640.0f, 200.0f, 0.0f));
	if (m_pScore != NULL)
	{
		int nScore = CGame::GetOldScore();

		m_pScore->SetScore(nScore);
	}

	pSound->Play(CSound::SOUND_LABEL_BGM_005);
	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CResult::Uninit(void)
{

	CScene::ReleaseAll();
}

//==================================================================
// 更新処理
//==================================================================
void CResult::Update(void)
{
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CDInputController* pController = CManager::GetController();
	CSound* pSound = CManager::GetSound();
	CFade*			pFade = CManager::GetFade();

	m_nCount++;
	m_apBG[0]->SetUV(D3DXVECTOR2(0.0f, 0.001f * -m_nCount + 0.0f),
		D3DXVECTOR2(1.0f, 0.001f * -m_nCount + 1.0f));

	m_apBG[1]->SetUV(D3DXVECTOR2(0.0002f * -m_nCount + 0.0f, 0.0016f * -m_nCount + 0.0f),
		D3DXVECTOR2(0.0002f * -m_nCount + 1.0f, 0.0016f * -m_nCount + 1.0f));

	m_apBG[2]->SetUV(D3DXVECTOR2(0.0001f * m_nCount + 0.0f, 0.002f * -m_nCount + 0.0f),
		D3DXVECTOR2(0.0001f * m_nCount + 1.0f, 0.002f * -m_nCount + 1.0f));

	if (pInput != NULL && pFade != NULL)
	{
		if (*pFade->GetFade() != CFade::FADE_OUT)
		{
			if (pInput->GetTrigger(DIK_RETURN) == true ||
				pController != NULL && pController->GetTrigger(CDInputController::DIJS_BUTTON_1) == true)
			{
				int nScore = CGame::GetOldScore();
				CRanking::SetRankScore(nScore);
				pFade->SetFade(CManager::MODE_RANKING, CFade::COLOR_WHITE);
				pSound->Play(CSound::SOUND_LABEL_SE_003);
			}
		}
	}
}

//==================================================================
// 描画処理
//==================================================================
void CResult::Draw(void)
{

}

