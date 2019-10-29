//=============================================================================
//
// プレイヤー処理 [effect.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "effect.h"
#include "Manager.h"
#include "input.h"

//==================================================================
// マクロ定義
//==================================================================
#define EFFECT_LIFE (30)

//==================================================================
// 静的メンバ変数宣言
//==================================================================
LPDIRECT3DTEXTURE9 CEffect::m_apTexture[2];				//共有テクスチャへのポインタ

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CEffect::CEffect() : CScene2D(2)
{

}
CEffect::~CEffect()
{
	CScene2D::~CScene2D();
}

//==================================================================
// 共有テクスチャの読み込み&解放
//==================================================================
HRESULT CEffect::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &m_apTexture[0]);

	return S_OK;
}
void CEffect::Unload(void)
{
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
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
CEffect* CEffect::Create(D3DXVECTOR3 pos, AUTHORITY author, float fSize, D3DXCOLOR col)
{
	CEffect* pEffect = NULL;
	pEffect = new CEffect;

	if (pEffect != NULL)
	{
		pEffect->Init(pos, col,fSize);				//オーバーロードしたInitで初期化
		pEffect->BindTexture(m_apTexture[0]);	//テクスチャ割り当て
		pEffect->m_Author = author;
	}

	return pEffect;
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CEffect::Init(void)
{
	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_EFFECT);//オブジェクトの種類設定

	return S_OK;
}
void CEffect::Init(D3DXVECTOR3 pos,D3DXCOLOR col, float fSize)
{
	Init();
	m_fSize = fSize;
	SetPosition(pos);
	m_Col = col;
	SetColor(col);
}

//==================================================================
// 終了処理
//==================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//==================================================================
// 更新処理
//==================================================================
void CEffect::Update(void)
{
	m_nCount++;

	SetColor(D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b,(EFFECT_LIFE - m_nCount) * (1.0f / EFFECT_LIFE)));
	if (m_nCount == EFFECT_LIFE)
	{
		Uninit();
	}
}

//==================================================================
// 描画処理
//==================================================================
void CEffect::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

