//=============================================================================
//
// 番号クラス処理 [Gauge.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "Gauge.h"
#include "Manager.h"

//==================================================================
// 静的メンバ変数宣言
//==================================================================
LPDIRECT3DTEXTURE9	CGauge::m_pTexture;			// テクスチャへのポインタ

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CGauge::CGauge()
{
	m_pVtxBuff = NULL;
}
CGauge::~CGauge()
{

}

//==================================================================
// テクスチャ読み込み&削除処理
//==================================================================
HRESULT CGauge::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Gauge000.png", &m_pTexture);

	return S_OK;
}
void CGauge::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==================================================================
// 生成処理
//==================================================================
CGauge* CGauge::Create(D3DXVECTOR3 pos, float fSizeY, float fLength, CScene::ELEMENT elem)
{
	CGauge* pGauge = NULL;

	pGauge = new CGauge;

	if (pGauge != NULL)
	{
		pGauge->Init(pos, fSizeY, fLength,elem);
	}
	return pGauge;

}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CGauge::Init(D3DXVECTOR3 pos, float fSizeY, float fLength, CScene::ELEMENT elem)
{
	m_pos = pos;
	m_fSizeY = fSizeY;
	m_fElementGauge = fLength;
	m_Element = elem;

	m_nCntTime = 0;

	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	D3DXCOLOR col;
	switch (elem)
	{
	case CScene::ELEMENT_RED:
		col = D3DXCOLOR(1.0f, 0.2f, 0.1f, 1.0f);
		break;
	case CScene::ELEMENT_GREEN:
		col = D3DXCOLOR(0.2f, 0.8f, 0.2f, 1.0f);
		break;
	case CScene::ELEMENT_BLUE:
		col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
		break;
	case CScene::ELEMENT_SUPER:
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	}
	m_OrgColor = col;

	// 頂点情報を設定
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f,-fSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(fLength* 2.0f, -fSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, fSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(fLength* 2.0f, fSizeY, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;

}
//==================================================================
// 終了処理
//==================================================================
void CGauge::Uninit(void)
{

	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

//==================================================================
// 更新処理
//==================================================================
void CGauge::Update(void)
{
	//m_nCntTime = ((m_nCntTime + 1) % 100)/* + 1*/;
	m_nCntTime++;
	float fColorFade;
	fColorFade = sinf((float)m_nCntTime / 10) * 0.5f + 1.5f;
	//D3DXCOLOR col = D3DXCOLOR(m_OrgColor.r + fColorFade, m_OrgColor.b + fColorFade, m_OrgColor.g + fColorFade,1.0f);
	D3DXCOLOR col = m_OrgColor * fColorFade;
	col.a = 1.0f;

	if (m_fElementGauge >= 100.0f)
	{
		// 頂点情報を設定
		VERTEX_2D* pVtx;
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;
		m_pVtxBuff->Unlock();
	}
}

//==================================================================
// 描画処理
//==================================================================
void CGauge::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	if (m_pTexture != NULL)
	{
		pDevice->SetTexture(0, m_pTexture);
	}
	else
	{
		pDevice->SetTexture(0, NULL);
	}

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


}

void CGauge::SetGauge(float fElementGauge)
{
	m_fElementGauge = fElementGauge;

	// 頂点情報を設定
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, -m_fSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(fElementGauge * 2.0f, -m_fSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, m_fSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(fElementGauge* 2.0f, m_fSizeY, 0.0f);

	m_pVtxBuff->Unlock();

}
