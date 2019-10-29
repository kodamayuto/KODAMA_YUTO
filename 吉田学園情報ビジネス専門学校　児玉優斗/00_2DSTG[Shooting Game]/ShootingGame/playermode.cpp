//=============================================================================
//
// 自機タイプ表示処理 [playermode.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "playermode.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_PLAYERMODE_01		"data/TEXTURE/PlayerMode_1.png"		//読み込むテクスチャファイル名1
#define	TEXTURE_PLAYERMODE_02		"data/TEXTURE/PlayerMode_2.png"		//読み込むテクスチャファイル名2
#define	TEXTURE_PLAYERMODE_03		"data/TEXTURE/PlayerMode_3.png"		//読み込むテクスチャファイル名3

#define PLAYERMODE_SIZE  (35.0f)									//状態表示の大きさ

#define PLAYERMODE_POS_X (1220)										//状態表示のX軸
#define PLAYERMODE_POS_Y (590)										//状態表示のY軸

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePlayerMode[3] = {};			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerMode = NULL;			// 頂点バッファへのポインタ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexPlayerMode(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayerMode(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_PLAYERMODE_01,		// ファイルの名前
								&g_pTexturePlayerMode[0]);	// テクスチャへのポインタ

	D3DXCreateTextureFromFile(pDevice,
								TEXTURE_PLAYERMODE_02,
								&g_pTexturePlayerMode[1]);

	D3DXCreateTextureFromFile(pDevice,
								TEXTURE_PLAYERMODE_03,
								&g_pTexturePlayerMode[2]);
	// 頂点情報の作成
	MakeVertexPlayerMode(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerMode(void)
{
	// テクスチャの開放
	for (int nCntData = 0; nCntData < 3; nCntData++)
	{
	if (g_pTexturePlayerMode[nCntData] != NULL)
	{
		g_pTexturePlayerMode[nCntData]->Release();
		g_pTexturePlayerMode[nCntData] = NULL;
	}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffPlayerMode != NULL)
	{
		g_pVtxBuffPlayerMode->Release();
		g_pVtxBuffPlayerMode = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerMode(void)
{//まだ書かない

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerMode(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	Player *pPlayer = GetPlayer();

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffPlayerMode, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	if (pPlayer->nBulletPattern % 3 == 0)
	{
		pDevice->SetTexture(0, g_pTexturePlayerMode[0]);
	}
	else if (pPlayer->nBulletPattern % 3 == 1)
	{
		pDevice->SetTexture(0, g_pTexturePlayerMode[1]);
	}
	else if (pPlayer->nBulletPattern % 3 == 2)
	{
		pDevice->SetTexture(0, g_pTexturePlayerMode[2]);
	}

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類		//プリミティブ == ポリゴン
			0,							   //開始する頂点のインデックス(基本０)
			2);		   										   //プリミティブの数
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexPlayerMode(LPDIRECT3DDEVICE9 pDevice)
{

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerMode,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	// 頂点情報を設定
	g_pVtxBuffPlayerMode->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(PLAYERMODE_POS_X - PLAYERMODE_SIZE, PLAYERMODE_POS_Y - PLAYERMODE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PLAYERMODE_POS_X + PLAYERMODE_SIZE, PLAYERMODE_POS_Y - PLAYERMODE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PLAYERMODE_POS_X - PLAYERMODE_SIZE, PLAYERMODE_POS_Y + PLAYERMODE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PLAYERMODE_POS_X + PLAYERMODE_SIZE, PLAYERMODE_POS_Y + PLAYERMODE_SIZE, 0.0f);

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


	//頂点バッファをアンロックする
	g_pVtxBuffPlayerMode->Unlock();
}

