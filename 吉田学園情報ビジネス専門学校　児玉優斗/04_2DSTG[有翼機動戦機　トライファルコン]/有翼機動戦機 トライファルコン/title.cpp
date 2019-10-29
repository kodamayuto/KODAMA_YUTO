//=============================================================================
//
// ゲーム画面管理クラス処理 [title.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "title.h"
#include "Manager.h"
#include "fade.h"
//
//
//
CTitleLogo* CTitle::m_pTitleLogo = NULL;
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[MAX_TITLE_TEX] = {};

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CTitle::CTitle()
{
	for (int nCntBG = 0; nCntBG < MAX_TITLE_TEX; nCntBG++)
	{
		m_pBG[nCntBG] = NULL;
	}
	m_pPressEnter = NULL;
	m_nCount = 0;
}
CTitle::~CTitle()
{

}

CTitle* CTitle::Create(void)
{
	CTitle* pTitle = NULL;

	pTitle = new CTitle;

	if (pTitle != NULL)
	{
		pTitle->Init();
	}
	return pTitle;
}

HRESULT CTitle::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/tex_press.png", &m_apTexture[3]);

	return S_OK;
}
void CTitle::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TITLE_TEX; nCntTex++)
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
HRESULT CTitle::Init(void)
{
	for (int nCntBG = 0; nCntBG < 3; nCntBG++)
	{
		m_pBG[nCntBG] = CScene2D::Create(4);
		m_pBG[nCntBG]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		m_pBG[nCntBG]->BindTexture(m_apTexture[nCntBG]);
	}

	//ロゴ作成
	m_pTitleLogo = CTitleLogo::Create();

	m_pPressEnter = CScene2D::Create(5);
	m_pPressEnter->SetPosition(D3DXVECTOR3(700.0f,500.0f,0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(500.0f, 125.0f, 0.0f));
	m_pPressEnter->BindTexture(m_apTexture[3]);

	//BGM鳴らす
	CSound* pSound = CManager::GetSound();
	pSound->StopAll();
	if (pSound != NULL)
	{
		pSound->Play(CSound::SOUND_LABEL_BGM_003);
	}

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CTitle::Uninit(void)
{
	CSound* pSound = CManager::GetSound();

	for (int nCntData = 0; nCntData < MAX_TITLE_TEX; nCntData++)
	{
		if (m_pBG[nCntData] != NULL)
		{
			m_pBG[nCntData]->Uninit();
			m_pBG[nCntData] = NULL;
		}
	}

	CScene::ReleaseAll();

	if (pSound != NULL)
	{
		pSound->StopAll();
	}

}

//==================================================================
// 更新処理
//==================================================================
void CTitle::Update(void)
{
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CDInputController* pController = CManager::GetController();
	CFade*			pFade = CManager::GetFade();
	CSound* pSound = CManager::GetSound();

	//テクスチャのUVアニメーション
	m_nCount++;
	m_pBG[0]->SetUV(D3DXVECTOR2(0.0f, 0.001f * -m_nCount + 0.0f),
		D3DXVECTOR2(1.0f, 0.001f * -m_nCount + 1.0f));

	m_pBG[1]->SetUV(D3DXVECTOR2(0.0002f * -m_nCount + 0.0f, 0.0016f * -m_nCount + 0.0f),
		D3DXVECTOR2(0.0002f * -m_nCount + 1.0f, 0.0016f * -m_nCount + 1.0f));

	m_pBG[2]->SetUV(D3DXVECTOR2(0.0001f * m_nCount + 0.0f, 0.002f * -m_nCount + 0.0f),
		D3DXVECTOR2(0.0001f * m_nCount + 1.0f, 0.002f * -m_nCount + 1.0f));

	m_pPressEnter->SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,((m_nCount / 30) % 2) * 1.0f));
	//終了
	if (pInput != NULL && pFade != NULL)
	{
		if (*pFade->GetFade() != CFade::FADE_OUT)
		{
			if (pInput->GetTrigger(DIK_RETURN) == true ||
				pController != NULL && pController->GetTrigger(CDInputController::DIJS_BUTTON_9) == true)
			{
				pFade->SetFade(CManager::MODE_SELECT, CFade::COLOR_BLACK);
				pSound->Play(CSound::SOUND_LABEL_SE_003);

			}

		}
	}
}

//==================================================================
// 描画処理
//==================================================================
void CTitle::Draw(void)
{

}

