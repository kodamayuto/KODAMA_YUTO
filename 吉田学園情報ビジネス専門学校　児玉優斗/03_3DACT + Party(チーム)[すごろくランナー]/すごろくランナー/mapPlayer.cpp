//=============================================================================
//
// ミニマップの中のプレイヤー処理 [mapPlayer.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "mapPlayer.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAPPLAYER_TEXTURENAME	"data\\TEXTURE\\mapPlayer.png"	// テクスチャ名
#define	MAPPLAYER_SIZE_X		(10)							// ミニマップの大きさ
#define	MAPPLAYER_SIZE_Y		(10)							// ミニマップの大きさ
#define	MINIMAP_SIZE			(185)							// ミニマップの大きさ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMapPlayer = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMapPlayer = NULL;	// 頂点バッファへのポインタ
D3DXVECTOR3 g_MapPosPlayer;

//=============================================================================
// タイマーのフレーム初期化処理
//=============================================================================
void InitMapPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	// プレイヤーを取得
	Player *pPlayer;
	pPlayer = GetPlayer();

	// 位置を設定
	D3DXVECTOR3 g_MapPosPlayer = pPlayer->pos / 20;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MAPPLAYER_TEXTURENAME, &g_pTextureMapPlayer);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffMapPlayer,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffMapPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_MapPosPlayer.x - MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z - MAPPLAYER_SIZE_Y + (120), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_MapPosPlayer.x + MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z - MAPPLAYER_SIZE_Y + (120), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_MapPosPlayer.x - MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z + MAPPLAYER_SIZE_Y + (120), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_MapPosPlayer.x + MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z + MAPPLAYER_SIZE_Y + (120), 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffMapPlayer->Unlock();
}

//=============================================================================
// タイマーのフレーム終了処理
//=============================================================================
void UninitMapPlayer(void)
{
	// テクスチャの破棄
	if (g_pTextureMapPlayer != NULL)
	{
		g_pTextureMapPlayer->Release();
		g_pTextureMapPlayer = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffMapPlayer != NULL)
	{
		g_pVtxBuffMapPlayer->Release();
		g_pVtxBuffMapPlayer = NULL;
	}
}

//=============================================================================
// タイマーのフレーム更新処理
//=============================================================================
void UpdateMapPlayer(void)
{
	// プレイヤーを取得
	Player *pPlayer;
	pPlayer = GetPlayer();

	g_MapPosPlayer = pPlayer->pos / 135;

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffMapPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//フィールドの大きさの判定
	if (MINIMAP_SIZE - MAPPLAYER_SIZE_X / 2 <= g_MapPosPlayer.x)
	{
		g_MapPosPlayer.x = MINIMAP_SIZE - MAPPLAYER_SIZE_X / 2;
	}
	if (-MINIMAP_SIZE + MAPPLAYER_SIZE_X / 2 >= g_MapPosPlayer.x)
	{
		g_MapPosPlayer.x = -MINIMAP_SIZE + MAPPLAYER_SIZE_X / 2;
	}
	if (-MINIMAP_SIZE + MAPPLAYER_SIZE_Y / 2 >= g_MapPosPlayer.z)
	{
		g_MapPosPlayer.z = -MINIMAP_SIZE + MAPPLAYER_SIZE_Y / 2;
	}
	if (MINIMAP_SIZE - MAPPLAYER_SIZE_Y / 2 <= g_MapPosPlayer.z)
	{
		g_MapPosPlayer.z = MINIMAP_SIZE - MAPPLAYER_SIZE_Y / 2;
	}

	pVtx[0].pos = D3DXVECTOR3(/*g_MapPosPlayer.x*/ - MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z - MAPPLAYER_SIZE_Y + (210), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(/*g_MapPosPlayer.x*/ + MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z - MAPPLAYER_SIZE_Y + (210), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(/*g_MapPosPlayer.x*/ - MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z + MAPPLAYER_SIZE_Y + (210), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(/*g_MapPosPlayer.x*/ + MAPPLAYER_SIZE_X + (120), -g_MapPosPlayer.z + MAPPLAYER_SIZE_Y + (210), 0.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffMapPlayer->Unlock();
}

//=============================================================================
// タイマーのフレーム描画処理
//=============================================================================
void DrawMapPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// デバイスへのポインタ

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMapPlayer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMapPlayer);

	// タイトルの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}