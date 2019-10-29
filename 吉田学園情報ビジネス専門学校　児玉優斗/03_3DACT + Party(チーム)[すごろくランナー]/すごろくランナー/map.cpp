//=============================================================================
//
// ミニマップ処理 [map.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "map.h"
#include "mapPlayer.h"
//#include "mapEnemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAP_TEXTURENAME	"data\\TEXTURE\\map.png"	// テクスチャ名
#define	MAP_SIZE_X		(100)						// ミニマップの大きさ
#define	MAP_SIZE_Y		(100)						// ミニマップの大きさ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMap = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMap = NULL;	// 頂点バッファへのポインタ
D3DXVECTOR3 g_MapPos;

//=============================================================================
// タイマーのフレーム初期化処理
//=============================================================================
void InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	// 位置を設定
	D3DXVECTOR3 g_MapPos(120, 120, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MAP_TEXTURENAME, &g_pTextureMap);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffMap,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

						// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffMap->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_MapPos.x - MAP_SIZE_X, g_MapPos.y - MAP_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_MapPos.x + MAP_SIZE_X, g_MapPos.y - MAP_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_MapPos.x - MAP_SIZE_X, g_MapPos.y + MAP_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_MapPos.x + MAP_SIZE_X, g_MapPos.y + MAP_SIZE_Y, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffMap->Unlock();

	// マッププレイヤー初期化処理
	InitMapPlayer();

	//// マップエネミー初期化処理
	//InitMapEnemy();
}

//=============================================================================
// タイマーのフレーム終了処理
//=============================================================================
void UninitMap(void)
{
	// テクスチャの破棄
	if (g_pTextureMap != NULL)
	{
		g_pTextureMap->Release();
		g_pTextureMap = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffMap != NULL)
	{
		g_pVtxBuffMap->Release();
		g_pVtxBuffMap = NULL;
	}

	// マッププレイヤー終了処理
	UninitMapPlayer();

	//// マップエネミー終了処理
	//UninitMapEnemy();
}

//=============================================================================
// タイマーのフレーム更新処理
//=============================================================================
void UpdateMap(void)
{
	// マッププレイヤー更新処理
	UpdateMapPlayer();

	//// マップエネミー更新処理
	//UpdateMapEnemy();
}

//=============================================================================
// タイマーのフレーム描画処理
//=============================================================================
void DrawMap(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// デバイスへのポインタ

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMap, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMap);

	// タイトルの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// マッププレイヤー描画処理
	DrawMapPlayer();

	//// マップエネミー描画処理
	//DrawMapEnemy();
}