//=============================================================================
//
// プレイヤー処理 [BG.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "BG.h"
#include "game.h"
#include "input.h"

//==================================================================
// マクロ定義
//==================================================================

//==================================================================
// 静的メンバ変数宣言
//==================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[CBg::TYPE_MAX];				//共有テクスチャへのポインタ

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CBg::CBg() : CScene(1)
{
	for (int nCntData = 0; nCntData < MAIN_BG_NUM; nCntData++)
	{
		m_apMainBG[nCntData] = NULL;
	}
	for (int nCntData = 0; nCntData < SIDE_BG_NUM; nCntData++)
	{
		m_apSideBG[nCntData] = NULL;
	}

}
CBg::~CBg()
{

}

//==================================================================
// 共有テクスチャの読み込み&解放
//==================================================================
HRESULT CBg::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Bg0004.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipo-fog012.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SideBG002.png", &m_apTexture[2]);

	return S_OK;
}

void CBg::Unload(void)
{
	for (int nCntTex = 0; nCntTex < CBg::TYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//==================================================================
// 生成処理
//==================================================================
CBg* CBg::Create()
{
	CBg* pBg = NULL;
	pBg = new CBg;

	if (pBg != NULL)
	{
		pBg->Init();
	}

	return pBg;
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CBg::Init(void)
{
	//プレイ領域のBGの生成
	for (int nCntData = 0; nCntData < MAIN_BG_NUM; nCntData++)
	{
		m_apMainBG[nCntData] = CScene2D::Create(1);
		m_apMainBG[nCntData]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f),
			D3DXVECTOR3((-SCREEN_WIDTH / 2) + MOVESTOP_RANGE, -SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3((SCREEN_WIDTH / 2) - MOVESTOP_RANGE, SCREEN_HEIGHT / 2, 0.0f));
		m_apMainBG[nCntData]->BindTexture(m_apTexture[nCntData]);
	}

	m_apMainBG[0]->SetColor(D3DXCOLOR(0.45f, 0.45f, 0.45f, 1.0f));
	m_apMainBG[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));

	//左右のBG生成
		m_apSideBG[0] = CScene2D::Create(4);
		m_apSideBG[0]->SetPosition(D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(MOVESTOP_RANGE,SCREEN_HEIGHT,0.0f));
		m_apSideBG[0]->BindTexture(m_apTexture[2]);

		m_apSideBG[1] = CScene2D::Create(4);
		m_apSideBG[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH - MOVESTOP_RANGE, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(MOVESTOP_RANGE, SCREEN_HEIGHT, 0.0f));
		m_apSideBG[1]->BindTexture(m_apTexture[2]);

	m_nCount = 0;
	SetObjType(CScene::OBJTYPE_BG);
	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CBg::Uninit(void)
{
	for (int nCntData = 0; nCntData < MAIN_BG_NUM; nCntData++)
	{
		if (m_apMainBG[nCntData] != NULL)
		{
			m_apMainBG[nCntData]->Uninit();
			m_apMainBG[nCntData] = NULL;
		}
	}
	for (int nCntData = 0; nCntData < SIDE_BG_NUM; nCntData++)
	{
		if (m_apSideBG[nCntData] != NULL)
		{
			m_apSideBG[nCntData]->Uninit();
			m_apSideBG[nCntData] = NULL;
		}
	}

	Release();
}

//==================================================================
// 更新処理
//==================================================================
void CBg::Update(void)
{

	m_nCount++;
	m_apMainBG[0]->SetUV(D3DXVECTOR2(0.0f, 0.0006f * -m_nCount + 0.0f),
		D3DXVECTOR2(1.0f, 0.0006f * -m_nCount + 0.25f));



	m_apMainBG[1]->SetUV(D3DXVECTOR2(0.0f, 0.005f * -m_nCount + 0.0f),
		D3DXVECTOR2(1.0f, 0.005f * -m_nCount + 1.0f));


}

//==================================================================
// 描画処理
//==================================================================
void CBg::Draw(void)
{

}
