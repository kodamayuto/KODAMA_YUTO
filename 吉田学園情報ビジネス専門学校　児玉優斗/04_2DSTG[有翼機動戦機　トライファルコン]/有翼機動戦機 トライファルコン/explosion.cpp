//=============================================================================
//
// プレイヤー処理 [explosion.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "explosion.h"
#include "Manager.h"
#include "input.h"

//==================================================================
// マクロ定義
//==================================================================
#define ANIM_EXPLOSION (8)			//アニメーションの総数

#define ANIM_COUNT_INTERVAL (4)		//アニメーションの進行速度

//==================================================================
// 静的メンバ変数宣言
//==================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_apTexture[CExplosion::TYPE_MAX];				//共有テクスチャへのポインタ

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CExplosion::CExplosion() : CScene2D(3)
{

}
CExplosion::~CExplosion()
{
	CScene2D::~CScene2D();
}

//==================================================================
// 共有テクスチャの読み込み&解放
//==================================================================
HRESULT CExplosion::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Effect_p011.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Effect_p014s.png", &m_apTexture[1]);

	return S_OK;
}
void CExplosion::Unload(void)
{
	for (int nCntTex = 0; nCntTex < CExplosion::TYPE_MAX; nCntTex++)
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
CExplosion* CExplosion::Create(D3DXVECTOR3 pos,D3DXCOLOR col, float fSize, CExplosion::TYPE type)
{
	CExplosion* pExplosion = NULL;
	pExplosion = new CExplosion;

	pExplosion->Init(pos, col,fSize);
	pExplosion->BindTexture(m_apTexture[type]);

	return pExplosion;
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CExplosion::Init(void)
{
	CScene2D::Init();

	m_nCount = 0;
	m_nAnim = 0;
	m_nAnimInterval = ANIM_COUNT_INTERVAL;

	SetUV(D3DXVECTOR2((1.0f / ANIM_EXPLOSION) * (m_nAnim % ANIM_EXPLOSION), 0.0f),
		D3DXVECTOR2((1.0f / ANIM_EXPLOSION) * (m_nAnim % ANIM_EXPLOSION) + (1.0f / ANIM_EXPLOSION), 1.0f));

	SetObjType(OBJTYPE_EXPLOSION);
	return S_OK;
}
void CExplosion::Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fSize)
{
	Init();
	m_fSize = fSize;
	SetPosition(pos);
	SetColor(col);

}

//==================================================================
// 終了処理
//==================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//==================================================================
// 更新処理
//==================================================================
void CExplosion::Update(void)
{
	m_nCount++;
	if (m_nCount % m_nAnimInterval == 0)
	{
		m_nAnim++;

		SetUV(D3DXVECTOR2((1.0f / ANIM_EXPLOSION) * (m_nAnim % ANIM_EXPLOSION), 0.0f),
			D3DXVECTOR2((1.0f / ANIM_EXPLOSION) * (m_nAnim % ANIM_EXPLOSION) + (1.0f / ANIM_EXPLOSION), 1.0f));

		if (m_nAnim >= ANIM_EXPLOSION)
		{
			Uninit();
		}
	}

}

//==================================================================
// 描画処理
//==================================================================
void CExplosion::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CScene2D::Draw();

}

