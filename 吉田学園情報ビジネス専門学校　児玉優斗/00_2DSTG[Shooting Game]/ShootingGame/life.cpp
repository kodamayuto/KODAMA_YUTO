//=============================================================================
//
// ライフ表示処理 [life.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "life.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_LIFE		"data/TEXTURE/life000.png"	//読み込むテクスチャファイル名
#define MAX_LIFE (PLAYER_LIFE)								//桁数
#define LIFE_SIZE  (15.0f)									//ライフの大きさ

#define LIFE_POS_X (1000)									//ライフのX軸
#define LIFE_POS_Y (650)									//ライフのY軸

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;			// 頂点バッファへのポインタ
int						g_nLife;						// ライフ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// 初期化処理
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//値の初期化
	g_nLife = MAX_LIFE;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_LIFE,		// ファイルの名前
								&g_pTextureLife);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexLife(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLife(void)
{
	// テクスチャの開放
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLife(void)
{//まだ書かない

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntLife;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLife);

	for (nCntLife = 0; nCntLife < g_nLife; nCntLife++)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類		//プリミティブ == ポリゴン
			4 * nCntLife,							   //開始する頂点のインデックス(基本０)
			2);		   										   //プリミティブの数
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntData;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	// 頂点情報を設定
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < MAX_LIFE; nCntData++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) - LIFE_SIZE, LIFE_POS_Y - LIFE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) + LIFE_SIZE, LIFE_POS_Y - LIFE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) - LIFE_SIZE, LIFE_POS_Y + LIFE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) + LIFE_SIZE, LIFE_POS_Y + LIFE_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
//ライフの処理
//=============================================================================
void SetLife(int nLife)
{
	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ
	int nCntData;

	g_nLife = nLife;
	// 頂点情報を設定
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < g_nLife; nCntData++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) - LIFE_SIZE, LIFE_POS_Y - LIFE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) + LIFE_SIZE, LIFE_POS_Y - LIFE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) - LIFE_SIZE, LIFE_POS_Y + LIFE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((LIFE_POS_X + (30 * nCntData)) + LIFE_SIZE, LIFE_POS_Y + LIFE_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();

}
