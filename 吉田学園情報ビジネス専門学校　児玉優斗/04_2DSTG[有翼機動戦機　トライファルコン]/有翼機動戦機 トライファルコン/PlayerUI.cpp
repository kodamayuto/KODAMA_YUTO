//=============================================================================
//
// プレイヤーUIクラス処理 [PlayerUI.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "PlayerUI.h"
#include "Manager.h"
#include "Gauge.h"

//
//
//
LPDIRECT3DTEXTURE9 CPlayerUI::m_apTexture[UI_TEX_NUM] = {};

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CPlayerUI::CPlayerUI() : CScene(5)
{
	for (int nCntVIT = 0; nCntVIT < MAX_VITALITY; nCntVIT++)
	{
		m_apVitarity[nCntVIT] = NULL;
	}

	for (int nCntStock = 0; nCntStock < MAX_STOCK; nCntStock++)
	{
		m_apStock[nCntStock] = NULL;
	}

	for (int nCntGauge = 0; nCntGauge < 3; nCntGauge++)
	{
		m_apGauge[nCntGauge] = NULL;
	}
}
CPlayerUI::~CPlayerUI()
{

}
//==================================================================
// 生成処理
//==================================================================
CPlayerUI* CPlayerUI::Create(void)
{
	CPlayerUI* pPlayerUI = NULL;

	pPlayerUI = new CPlayerUI;

	if (pPlayerUI != NULL)
	{
		pPlayerUI->Init();
	}

	return pPlayerUI;
}
//==================================================================
// 共有テクスチャの読み込み&解放
//==================================================================
HRESULT CPlayerUI::Load(void)
{
	for (int nCntTex = 0; nCntTex < UI_TEX_NUM; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}

	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI000_Life.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI000_ENERGY.png", &m_apTexture[1]);

	return S_OK;

}
void CPlayerUI::Unload(void)
{
	for (int nCntTex = 0; nCntTex < UI_TEX_NUM; nCntTex++)
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
HRESULT CPlayerUI::Init(void)
{
	//体力
	for (int nCntVIT = 0; nCntVIT < MAX_VITALITY; nCntVIT++)
	{
		m_apVitarity[nCntVIT] = CScene2D::Create(6);
		m_apVitarity[nCntVIT]->SetPosition(D3DXVECTOR3(25.0f + (25.0f * nCntVIT), 100.0f, 0.0f), 12.5f);
		m_apVitarity[nCntVIT]->BindTexture(m_apTexture[0]);
	}

	m_nVITcount = MAX_VITALITY;

	//残機
	for (int nCntStock = 0; nCntStock < MAX_STOCK; nCntStock++)
	{
		m_apStock[nCntStock] = CScene2D::Create(6);
		m_apStock[nCntStock]->SetPosition(D3DXVECTOR3(25.0f + (25.0f * nCntStock), 140.0f, 0.0f), 12.5f);
		m_apStock[nCntStock]->BindTexture(m_apTexture[1]);
	}

	m_nStockCount = MAX_STOCK;

	//ゲージ
	for (int nCntGauge = 0; nCntGauge < 3; nCntGauge++)
	{
		m_apGauge[nCntGauge] = CGauge::Create(D3DXVECTOR3(50.0f,400.0f + (40.0f * nCntGauge),0.0f),
												15.0f,
												100.0f,
												(CScene::ELEMENT)nCntGauge);
	}

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CPlayerUI::Uninit(void)
{
	for (int nCntVIT = 0; nCntVIT < MAX_VITALITY; nCntVIT++)
	{
		if (m_apVitarity[nCntVIT] != NULL)
		{
			m_apVitarity[nCntVIT]->Uninit();
			m_apVitarity[nCntVIT] = NULL;
		}
	}
	for (int nCntStock = 0; nCntStock < MAX_STOCK; nCntStock++)
	{
		if (m_apStock[nCntStock] != NULL)
		{
			m_apStock[nCntStock]->Uninit();
			m_apStock[nCntStock] = NULL;
		}
	}

	for (int nCntGauge = 0; nCntGauge < 3; nCntGauge++)
	{
		if (m_apGauge[nCntGauge] != NULL)
		{
			m_apGauge[nCntGauge]->Uninit();

			delete m_apGauge[nCntGauge];
			m_apGauge[nCntGauge] = NULL;
		}

	}
	Release();

}

//==================================================================
// 更新処理
//==================================================================
void CPlayerUI::Update(void)
{
	for (int nCntGauge = 0; nCntGauge < 3; nCntGauge++)
	{
		if (m_apGauge[nCntGauge] != NULL)
		{
			m_apGauge[nCntGauge]->Update();
		}
	}

}

//==================================================================
// 描画処理
//==================================================================
void CPlayerUI::Draw(void)
{
	for (int nCntGauge = 0; nCntGauge < 3; nCntGauge++)
	{
		if (m_apGauge[nCntGauge] != NULL)
		{
			m_apGauge[nCntGauge]->Draw();
		}
	}

}

//==================================================================
// 各種設定処理
//==================================================================
void CPlayerUI::SetLife(int nLife)
{

	for (int nCntVIT = 0; nCntVIT < m_nVITcount; nCntVIT++)
	{
		m_apVitarity[nCntVIT]->Uninit();
		m_apVitarity[nCntVIT] = NULL;
	}

	for (int nCntVIT = 0; nCntVIT < nLife; nCntVIT++)
	{
		m_apVitarity[nCntVIT] = CScene2D::Create(6);
		m_apVitarity[nCntVIT]->SetPosition(D3DXVECTOR3(25.0f + (25.0f * nCntVIT), 100.0f, 0.0f), 12.5f);
		m_apVitarity[nCntVIT]->BindTexture(m_apTexture[0]);
	}
	m_nVITcount = nLife;

}
void CPlayerUI::SetStock(int nStock)
{

	for (int nCntStock = 0; nCntStock < m_nStockCount; nCntStock++)
	{
		m_apStock[nCntStock]->Uninit();
		m_apStock[nCntStock] = NULL;
	}

	int nStk = nStock;
	if (nStk < 0)
	{
		nStk = 0;
	}
	for (int nCntStock = 0; nCntStock < nStk; nCntStock++)
	{
		m_apStock[nCntStock] = CScene2D::Create(6);
		m_apStock[nCntStock]->SetPosition(D3DXVECTOR3(25.0f + (25.0f * nCntStock), 140.0f, 0.0f), 12.5f);
		m_apStock[nCntStock]->BindTexture(m_apTexture[1]);
	}

	m_nStockCount = nStk;
}

void CPlayerUI::SetGauge(CScene::ELEMENT elem, float fElementGauge)
{
	m_apGauge[elem]->SetGauge(fElementGauge);

}