//=============================================================================
//
// プレイヤー処理 [titleLogo.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "titleLogo.h"
#include "game.h"
#include "input.h"

//==================================================================
// マクロ定義
//==================================================================

//==================================================================
// 静的メンバ変数宣言
//==================================================================
LPDIRECT3DTEXTURE9 CTitleLogo::m_pTexture;				//共有テクスチャへのポインタ

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CTitleLogo::CTitleLogo() : CScene(5)
{
	m_pLogo = NULL;
}
CTitleLogo::~CTitleLogo()
{

}

//==================================================================
// 共有テクスチャの読み込み&解放
//==================================================================
HRESULT CTitleLogo::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TitleLogo000.png", &m_pTexture);

	return S_OK;
}

void CTitleLogo::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==================================================================
// 生成処理
//==================================================================
CTitleLogo* CTitleLogo::Create()
{
	CTitleLogo* pLogo = NULL;
	pLogo = new CTitleLogo;

	if (pLogo != NULL)
	{
		pLogo->Init();
	}

	return pLogo;
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CTitleLogo::Init(void)
{
	m_pLogo = CScene2D::Create(5);
	m_pLogo->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2,250.0f,0.0f),
		D3DXVECTOR3(-400.0f,-150.0f,0.0f),
		D3DXVECTOR3(400.0f, 150.0f, 0.0f));
	m_pLogo->BindTexture(m_pTexture);
	m_nCount = 0;
	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CTitleLogo::Uninit(void)
{
		if (m_pLogo != NULL)
		{
			m_pLogo->Uninit();
			m_pLogo = NULL;
		}

	Release();
}

//==================================================================
// 更新処理
//==================================================================
void CTitleLogo::Update(void)
{

}

//==================================================================
// 描画処理
//==================================================================
void CTitleLogo::Draw(void)
{

}
