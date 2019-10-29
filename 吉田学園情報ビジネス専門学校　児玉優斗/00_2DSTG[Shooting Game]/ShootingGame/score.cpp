//=============================================================================
//
// スコア処理 [score.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define MAX_SCORE_DIGIT (8)									//桁数
#define SCORE_SIZE      (20.0f)								//スコアの大きさ

#define SCORE_POS_X (1000)									//スコアのX軸
#define SCORE_POS_Y (700)									//スコアのY軸

#define COLOR_COUNT_NUM (20)								//スコアの色変更時間
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;			// 頂点バッファへのポインタ
int						g_nScore;						// スコア
int						g_aScoreDigit[MAX_SCORE_DIGIT]; // スコアのデータ
int						g_aScoreDigitOld[MAX_SCORE_DIGIT]; // スコアの一つ前のデータ
int						g_aScoreColorCounter[MAX_SCORE_DIGIT];//スコアの色変更カウンタ
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{
	int nCntScore;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_nScore = 00000000;		//八桁
	for (nCntScore = 0; nCntScore < MAX_SCORE_DIGIT; nCntScore++)
	{
		g_aScoreDigit[nCntScore] = 0;
		g_aScoreDigitOld[nCntScore] = 0;
		g_aScoreColorCounter[nCntScore] = 0;
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
	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ


	for (int nCntData = 0; nCntData < MAX_SCORE_DIGIT; nCntData++)
	{
		if (g_aScoreColorCounter[nCntData] > 0)
		{
			g_aScoreColorCounter[nCntData]--;

			if (g_aScoreColorCounter[nCntData] == 0)
			{
				// 頂点情報を設定
				g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += 4 * nCntData;

				//頂点カラー
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

				//頂点バッファをアンロックする
				g_pVtxBuffScore->Unlock();

				g_aScoreColorCounter[nCntData] = 0;
			}
		}
	}


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

	for (nCntScore = 0; nCntScore < MAX_SCORE_DIGIT; nCntScore++)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類		//プリミティブ == ポリゴン
			4 * nCntScore,							   //開始する頂点のインデックス(基本０)
			2);		   										   //プリミティブの数
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntData;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE_DIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	// 頂点情報を設定
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < MAX_SCORE_DIGIT; nCntData++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3((SCORE_POS_X + (32.0f * nCntData)) - SCORE_SIZE, SCORE_POS_Y - SCORE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((SCORE_POS_X + (32.0f * nCntData)) + SCORE_SIZE, SCORE_POS_Y - SCORE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((SCORE_POS_X + (32.0f * nCntData)) - SCORE_SIZE, SCORE_POS_Y + SCORE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((SCORE_POS_X + (32.0f * nCntData)) + SCORE_SIZE, SCORE_POS_Y + SCORE_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();


}

//=============================================================================
// スコアの加算
//=============================================================================
void AddScore(int nValue)
{
	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ
	int nCntData;

	g_nScore += nValue;
	if (g_nScore < 0)
	{
		g_nScore = 0;
	}

	//現在の桁番号を代入する
	for (nCntData = 0; nCntData < MAX_SCORE_DIGIT; nCntData++)
	{
		g_aScoreDigitOld[nCntData] = g_aScoreDigit[nCntData];
	}

	//g_aScoreDigit[0] = g_nScore % 10000000000 / 1000000000;
	//g_aScoreDigit[1] = g_nScore % 1000000000 / 100000000;
	g_aScoreDigit[0] = g_nScore % 100000000 / 10000000;
	g_aScoreDigit[1] = g_nScore % 10000000 / 1000000;
	g_aScoreDigit[2] = g_nScore % 1000000 / 100000;
	g_aScoreDigit[3] = g_nScore % 100000 / 10000;
	g_aScoreDigit[4] = g_nScore % 10000 / 1000;
	g_aScoreDigit[5] = g_nScore % 1000 / 100;
	g_aScoreDigit[6] = g_nScore % 100 / 10;
	g_aScoreDigit[7] = g_nScore % 10 / 1;


	// 頂点情報を設定
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < MAX_SCORE_DIGIT; nCntData++)
	{
		if (g_aScoreDigitOld[nCntData] != g_aScoreDigit[nCntData])
		{//前回の桁番号と今回の桁番号が違っていたら
			pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 255);

			g_aScoreColorCounter[nCntData] = COLOR_COUNT_NUM;
		}

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(g_aScoreDigit[nCntData] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aScoreDigit[nCntData] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aScoreDigit[nCntData] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((g_aScoreDigit[nCntData] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//
//
//
int GetScore(void)
{
	return g_nScore;
}
