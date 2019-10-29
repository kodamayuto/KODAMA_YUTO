//=============================================================================
//
// 番号クラス処理 [number.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "number.h"
#include "Manager.h"

//==================================================================
// 静的メンバ変数宣言
//==================================================================
LPDIRECT3DTEXTURE9	CNumber::m_pTexture;			// テクスチャへのポインタ

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
}
CNumber::~CNumber()
{

}

//==================================================================
// テクスチャ読み込み&削除処理
//==================================================================
HRESULT CNumber::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Number001.png", &m_pTexture);

	return S_OK;
}
void CNumber::Unload(void)
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
CNumber* CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect, int nNum)
{
	CNumber* pNumber = NULL;

	pNumber = new CNumber;

	if (pNumber != NULL)
	{
		pNumber->Init(pos, polygonRect, nNum);
	}
	return pNumber;
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect, int nNum)
{
	m_pos = pos;
	m_polygonRect = polygonRect;
	m_nNumber = nNum;

	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	// 頂点情報を設定
	VERTEX_2D* pVtx;
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_polygonRect.x, 0.0f, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, m_polygonRect.y, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_polygonRect.x, m_polygonRect.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2((m_nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((m_nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CNumber::Uninit(void)
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
void CNumber::Update(void)
{

}

//==================================================================
// 描画処理
//==================================================================
void CNumber::Draw(void)
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

//==================================================================
// 番号設定処理
//==================================================================
void CNumber::SetNumber(int nNum)
{
	m_nNumber = nNum;

	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((m_nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((m_nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();


}

//==================================================================
// 各種設定処理
//==================================================================
void CNumber::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_polygonRect.x, 0.0f, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, m_polygonRect.y, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_polygonRect.x, m_polygonRect.y, 0.0f);

	m_pVtxBuff->Unlock();

}
void CNumber::SetColor(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	m_pVtxBuff->Unlock();

}
