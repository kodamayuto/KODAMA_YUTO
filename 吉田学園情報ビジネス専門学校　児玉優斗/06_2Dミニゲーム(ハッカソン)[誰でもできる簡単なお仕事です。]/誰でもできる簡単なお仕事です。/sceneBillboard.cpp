//=============================================================================
//
// ビルボード処理 [sceneBillboard.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "sceneBillboard.h"
#include "Manager.h"

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CSceneBillboard::CSceneBillboard(CScene::PRIORITY pri = CScene::PRIORITY_3) : CScene(pri,OBJTYPE_BILLBOARD)
{
}
CSceneBillboard::~CSceneBillboard()
{

}

//==================================================================
// テクスチャの適用
//==================================================================
void CSceneBillboard::BindTexture(LPCSTR TexTag)
{
	m_pTexture = CTexture::GetTexture(TexTag);
}

//==================================================================
// 生成処理
//==================================================================
void CSceneBillboard::Set(D3DXVECTOR3 pos, LPCSTR TexTag, D3DXVECTOR2 Size)
{
	m_pos = pos;
	m_Size = Size;
	BindTexture(TexTag);

	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(-m_Size.x, m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x, m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x, -m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x, -m_Size.y, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();


}
//==================================================================
// 初期化処理
//==================================================================
HRESULT CSceneBillboard::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f,0.0f);
	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CSceneBillboard::Uninit(void)
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
// 更新処理
//==================================================================
void CSceneBillboard::Update(void)
{

}

//==================================================================
// 描画処理
//==================================================================
void CSceneBillboard::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;				// 計算用マトリックス

														//αテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ライティングモードを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//マトリックスの計算
	CUtilityMath::CalWorldMatrix(&m_mtxWorld, m_pos, m_rot,NULL,D3DXVECTOR3(1.0f,1.0f,1.0f), &mtxView);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

	pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

								   // テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);//テクスチャの設定

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
		0,					   //開始する頂点のインデックス(基本０)
		2);		   	       //プリミティブの数


	// ライティングモードを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//==================================================================
// 各種設定処理
//==================================================================
void CSceneBillboard::SetPosition(D3DXVECTOR3 pos)
{//座標のみ設定
	m_pos = pos;
}
void CSceneBillboard::SetSize(D3DXVECTOR2 Size)
{
	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ
	m_Size = Size;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_Size.x, m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x, m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x, -m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x, -m_Size.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
