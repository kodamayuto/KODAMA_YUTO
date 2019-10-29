//=============================================================================
//
// シーン2D処理 [scene2D.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "scene2D.h"
#include "renderer.h"
#include "Manager.h"

//==================================================================
// 静的メンバ変数
//==================================================================
static bool g_DeleteFlag = true;		//ブロック消すフラグ(テスト)

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
}

CScene2D::~CScene2D()
{

}

//==================================================================
// テクスチャの適用
//==================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//==================================================================
// 生成
//==================================================================
CScene2D* CScene2D::Create(int nPriority = 3)
{
	int nAll = m_nNumAll;

	CScene2D* pScene2D = NULL;

	pScene2D = new CScene2D(nPriority);

	if(pScene2D != NULL)
	{
		pScene2D->Init();
	}

	return pScene2D;
}


//==================================================================
// ポリゴンの初期化処理
//==================================================================
HRESULT CScene2D::Init()
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//pDevice = GetRenderer()->GetDevice();	//これでも呼べるが、レンダラにポインタが入っていないと止まる

	// テクスチャの生成

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	// 頂点情報を設定
	float fSize = 10.0f;
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-fSize, -fSize, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fSize, -fSize, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fSize, fSize, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fSize, fSize, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}

//==================================================================
// ポリゴンの終了処理
//==================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}

	Release();
}

//==================================================================
// ポリゴンの更新処理
//==================================================================
void CScene2D::Update(void)
{
	//// 変数宣言
	//VERTEX_2D* pVtx;

	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fSize, -m_fSize, 0.0f);
	//pVtx[1].pos = m_pos + D3DXVECTOR3(m_fSize, -m_fSize, 0.0f);
	//pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fSize, m_fSize, 0.0f);
	//pVtx[3].pos = m_pos + D3DXVECTOR3(m_fSize, m_fSize, 0.0f);

	//m_pVtxBuff->Unlock();
}

//==================================================================
// ポリゴンの描画処理
//==================================================================
void CScene2D::Draw(void)
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
// 各種設定処理
//==================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// 変数宣言
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_fSize, -m_fSize, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_fSize, -m_fSize, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_fSize, m_fSize, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_fSize, m_fSize, 0.0f);

	m_pVtxBuff->Unlock();

}

void CScene2D::SetPosition(D3DXVECTOR3 pos, float fSize)
{
	m_fSize = fSize;

	SetPosition(pos);
}

void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 MinOffset,D3DXVECTOR3 MaxOffset)
{
	m_pos = pos;

	// 変数宣言
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(MinOffset.x, MinOffset.y, 0.0f) + pos;
	pVtx[1].pos = D3DXVECTOR3(MaxOffset.x, MinOffset.y, 0.0f) + pos;
	pVtx[2].pos = D3DXVECTOR3(MinOffset.x, MaxOffset.y, 0.0f) + pos;
	pVtx[3].pos = D3DXVECTOR3(MaxOffset.x, MaxOffset.y, 0.0f) + pos;

	m_pVtxBuff->Unlock();

}

void CScene2D::SetColor(D3DXCOLOR col)
{
	// 変数宣言
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();

}

void CScene2D::SetUV(D3DXVECTOR2 MinRect, D3DXVECTOR2 MaxRect)
{
	// 変数宣言
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = MinRect;
	pVtx[1].tex = D3DXVECTOR2(MaxRect.x, MinRect.y);
	pVtx[2].tex = D3DXVECTOR2(MinRect.x, MaxRect.y);
	pVtx[3].tex = MaxRect;

	m_pVtxBuff->Unlock();

}
