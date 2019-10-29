//=============================================================================
//
// ターン数処理 [turnNum.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "turnNum.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_NAME_SCORE  "data/TEXTURE/score.png"      // 読み込むテクスチャファイル名
#define TEXTURE_SIZEX       (100)                         // テクスチャのサイズ
#define TEXTURE_SIZEY       (100)                         // テクスチャのサイズ
#define MAX_SCORENUMBER     (8)                           // ターン数の桁数の最大値
#define TURNNUM_POS_X       (200.0f)
#define TURNNUM_POS_Y       (100.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTurnNum(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTurnNum = NULL;   // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTurnNum = NULL;   // 頂点バッファへのポインタ
TurnNum                 g_TurnNum;                  // ターン数の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitTurnNum(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ターン数の情報を初期化
	g_TurnNum.pos = D3DXVECTOR3(TURNNUM_POS_X, TURNNUM_POS_Y, 0.0f);  // 座標を初期化
	g_TurnNum.TexturePos = 1;                                   // テクスチャ座標を初期化
	g_TurnNum.nScore = 1;                                       // 数を初期化
	g_TurnNum.NumScore = 1;                                     // スコアの桁数を初期化
	g_TurnNum.Width = TEXTURE_SIZEX;                            // 幅を初期化
	g_TurnNum.Height = TEXTURE_SIZEY;                           // 高さを初期化

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME_SCORE,
		&g_pTextureTurnNum);

	// 頂点情報の作成
	MakeVertexTurnNum(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTurnNum(void)
{
	// テクスチャの開放
	if (g_pTextureTurnNum != NULL)
	{
		g_pTextureTurnNum->Release();
		g_pTextureTurnNum = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffTurnNum != NULL)
	{
		g_pVtxBuffTurnNum->Release();
		g_pVtxBuffTurnNum = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTurnNum(void)
{

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTurnNum(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTurnNum, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTurnNum);

	// ポリゴンの描画
	for (int nCntScore = 0; nCntScore < g_TurnNum.NumScore; nCntScore++)
	{// 表示するスコアの桁数だけ繰り返し
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntScore * 4,
			2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTurnNum(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (4 * MAX_SCORENUMBER),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTurnNum,
		NULL);

	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffTurnNum->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	for (int nCntScore = 0; nCntScore < MAX_SCORENUMBER; nCntScore++)
	{// ターン数の桁数だけ繰り返し
	    // 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_TurnNum.pos.x + sinf(-D3DX_PI * 0.75f) * g_TurnNum.Width, g_TurnNum.pos.y + cosf(-D3DX_PI * 0.75f) * g_TurnNum.Height, g_TurnNum.pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_TurnNum.pos.x + sinf(D3DX_PI * 0.75f) * g_TurnNum.Width, g_TurnNum.pos.y + cosf(D3DX_PI * 0.75f) * g_TurnNum.Height, g_TurnNum.pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_TurnNum.pos.x + sinf(-D3DX_PI * 0.25f) * g_TurnNum.Width, g_TurnNum.pos.y + cosf(-D3DX_PI * 0.25f) * g_TurnNum.Height, g_TurnNum.pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_TurnNum.pos.x + sinf(D3DX_PI * 0.25f) * g_TurnNum.Width, g_TurnNum.pos.y + cosf(D3DX_PI * 0.25f) * g_TurnNum.Height, g_TurnNum.pos.z);

		// 頂点テクスチャ
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
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_TurnNum.TexturePos), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_TurnNum.TexturePos), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_TurnNum.TexturePos), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_TurnNum.TexturePos), 1.0f);

		pVtx += 4;
		g_TurnNum.pos.x -= TEXTURE_SIZEX + 5.0f;
	}
	g_TurnNum.pos.x = TURNNUM_POS_X;

	// 頂点バッファをアンロックする
	g_pVtxBuffTurnNum->Unlock();
}
//=============================================================================
// ターン数の加算
//=============================================================================
void AddTurnNum(int nValue)
{
	// 頂点バッファを生成
	VERTEX_2D *pVtx;
	g_TurnNum.nScore += nValue;

	if (g_TurnNum.nScore / (int)powf(10.0f, (float)g_TurnNum.NumScore) >= 1)
	{// 桁が上がった
		g_TurnNum.NumScore++;

	}

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffTurnNum->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < g_TurnNum.NumScore; nCntScore++)
	{// ターン数の桁数だけ繰り返し
		g_TurnNum.TexturePos = g_TurnNum.nScore % ((int)powf(10.0f, (float)nCntScore) * 10) / (int)powf(10.0f, (float)nCntScore);
		
		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_TurnNum.TexturePos), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_TurnNum.TexturePos), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_TurnNum.TexturePos), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_TurnNum.TexturePos), 1.0f);

		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffTurnNum->Unlock();
}
//=============================================================================
// ターン数の取得
//=============================================================================
int GetTurnNum(void)
{
	return g_TurnNum.nScore;
}