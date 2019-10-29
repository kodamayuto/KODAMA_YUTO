//=============================================================================
//
// 画面遷移クラス処理 [fade.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "fade.h"
#include "Manager.h"

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CFade::CFade()
{
	m_pTexture = NULL;
	m_pFadePolygon = NULL;
}
CFade::~CFade()
{

}

CFade* CFade::Create(CManager::MODE modeNext)
{
	CFade* pFade = NULL;

	pFade = new CFade;

	if (pFade != NULL)
	{
		pFade->Init(modeNext);
	}
	return pFade;
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CFade::Init(CManager::MODE modeNext)
{
	// 値の初期化
	m_Fade = FADE_IN;
	m_modeNext = modeNext;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pFadePolygon = CScene2D::Create(7);
	m_pFadePolygon->SetPosition(D3DXVECTOR3(0.0f,0.0f,0.0f),
		D3DXVECTOR3(0.0f,0.0f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f));
	m_pFadePolygon->SetColor(m_colorFade);
	m_pFadePolygon->BindTexture(m_pTexture);
	m_pFadePolygon->SetObjType(CScene::OBJTYPE_FADE);
	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CFade::Uninit(void)
{
	if (m_pFadePolygon != NULL)
	{
		m_pFadePolygon->Uninit();
		m_pFadePolygon = NULL;
	}

	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}


}

//==================================================================
// 更新処理
//==================================================================
void CFade::Update(void)
{
	if (m_Fade != FADE_NONE)
	{
		m_pFadePolygon->SetColor(m_colorFade);
		if (m_Fade == FADE_IN)
		{
			m_colorFade.a -= 0.05f;//透明にしていく
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_Fade = FADE_NONE;
			}
		}
		else if (m_Fade == FADE_OUT)
		{

			m_colorFade.a += 0.03f;//不透明にしていく
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_Fade = FADE_IN;

				CManager::SetMode(m_modeNext);
			}

		}


	}
}

//==================================================================
// 描画処理
//==================================================================
void CFade::Draw(void)
{

}

//=============================================================================
// フェードの設定
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext, FADECOLOR fCol)
{
	m_Fade = FADE_OUT;
	m_modeNext = modeNext;
	switch (fCol)
	{
	case CFade::COLOR_BLACK:
		m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		break;
	case CFade::COLOR_WHITE:
		m_colorFade = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		break;
	}

	m_pFadePolygon->SetColor(m_colorFade);
}
