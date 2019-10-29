//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 高橋美優
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE	"data/TEXTURE/score.png"	// 読み込むテクスチャファイル名
#define MAX_SCORE	(8)								// 桁の最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// 頂点バッファへのポインタ
int	g_nScore;										// スコア
int g_aScore[8];

//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNum = 100000000;
	int nNum1 = 10000000;
	int nCnt;

	// スコアの初期化
	g_nScore = 1000;

	for (nCnt = 0; nCnt < 8; nCnt++)
	{
		g_aScore[nCnt] = g_nScore% nNum / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_SCORE,		// ファイルの名前
								&g_pTextureScore);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexScore(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	// テクスチャの開放
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	VERTEX_2D*pVtx;		// 頂点情報へのポインタ
	int nCntScore;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aScore[nCntScore] * 0.1f), 0.0f); 
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aScore[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aScore[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aScore[nCntScore] * 0.1f), 1.0f);

		pVtx += 4;		// 頂点データのポインタを４つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntScore;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	// ポリゴンの描画
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntScore,
			2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntScore;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点情報の作成
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(940.0f + (40.0f * nCntScore), 23.0f, 0.0f);	// 大きさ縦、横
		pVtx[1].pos = D3DXVECTOR3(980.0f + (40.0f * nCntScore), 23.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(940.0f + (40.0f * nCntScore), 73.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(980.0f + (40.0f * nCntScore), 73.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 赤、緑、青、透明度
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;		//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
void AddScore(int nValue)
{
	int nNum = 100000000;
	int nNum1 = 10000000;
	int nCnt;

	g_nScore += nValue;

	for (nCnt = 0; nCnt < 8; nCnt++)
	{
		g_aScore[nCnt] = g_nScore% nNum / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}

//=============================================================================
// スコアの取得
//=============================================================================
int GetScore(void)
{
	return g_nScore;
	//return 25;

}