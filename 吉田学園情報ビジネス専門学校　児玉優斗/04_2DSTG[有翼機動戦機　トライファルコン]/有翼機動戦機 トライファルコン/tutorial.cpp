//=============================================================================
//
// ゲーム画面管理クラス処理 [tutorial.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "tutorial.h"
#include "fade.h"
#include "sound.h"

//==================================================================
// 静的メンバ変数
//==================================================================
CPlayer* CTutorial::m_pPlayer = NULL;
CPlayerUI* CTutorial::m_pPlayerUI = NULL;
int CTutorial::m_nRespawnTimer = -1;

LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CTutorial::CTutorial()
{
	m_nRespawnTimer = -1;
}
CTutorial::~CTutorial()
{

}

//==================================================================
// 共有テクスチャの読み込み&解放
//==================================================================
HRESULT CTutorial::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial.jpg", &m_pTexture);
	return S_OK;
}
void CTutorial::Unload(void)
{
	//テクスチャ破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//==================================================================
// 生成処理
//==================================================================
CTutorial* CTutorial::Create(void)
{
	CTutorial* pTutorial = NULL;

	pTutorial = new CTutorial;

	if (pTutorial != NULL)
	{
		pTutorial->Init();
	}
	return pTutorial;
}
//==================================================================
// 初期化処理
//==================================================================
HRESULT CTutorial::Init(void)
{
	//オブジェクトの生成

	m_pPlayerUI = CPlayerUI::Create();
	CPlayer::SetStock();
	m_pPlayer = CPlayer::Create();

	CBg::Create();

	//チュートリアルの生成
	m_pTutorial = CScene2D::Create(5);
	if (m_pTutorial != NULL)
	{
		m_pTutorial->SetPosition(D3DXVECTOR3(SCREEN_WIDTH - 330.0f,0.0f,0.0f),
									D3DXVECTOR3(0.0f,0.0f,0.0f),
									D3DXVECTOR3(330.0f,SCREEN_HEIGHT,0.0f));
		m_pTutorial->BindTexture(m_pTexture);
	}
	//BGM鳴らす
	CSound* pSound = CManager::GetSound();
	pSound->StopAll();
	if (pSound != NULL)
	{
		pSound->Play(CSound::SOUND_LABEL_BGM_002);
	}

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CTutorial::Uninit(void)
{
	CSound* pSound = CManager::GetSound();

	//オブジェクト全破棄
	if (m_pTutorial != NULL)
	{
		m_pTutorial->Uninit();
		m_pTutorial = NULL;
	}
	CScene::ReleaseAll();

	m_pPlayer = NULL;
	m_pPlayerUI = NULL;

	if (pSound != NULL)
	{
		pSound->StopAll();
	}
}

//==================================================================
// 更新処理
//==================================================================
void CTutorial::Update(void)
{
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CDInputController* pController = CManager::GetController();
	CFade*			pFade = CManager::GetFade();

	if (pInput->GetTrigger(DIK_P) == true || pController != NULL && pController->GetTrigger(CDInputController::DIJS_BUTTON_9) == true)
	{
		CManager::PauseModeChange();
	}

	//プレイヤーの再出現
	if (m_nRespawnTimer >= -1)
	{
		m_nRespawnTimer--;

		if (m_nRespawnTimer == 0)
		{
			if (CPlayer::GetStock() >= 0)
			{
				m_pPlayer = NULL;
				m_pPlayer = CPlayer::Create();

				m_nRespawnTimer = -1;
			}
		}
	}


}

//==================================================================
// 描画処理
//==================================================================
void CTutorial::Draw(void)
{

}

