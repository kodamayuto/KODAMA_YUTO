//=============================================================================
//
// スコア処理 [score.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore[2] = {};			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;			// 頂点バッファへのポインタ
int						g_nScore;						// スコア
int						g_aScoreDigit[MAX_SCORE_DIGIT]; // スコアのデータ

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
	for (nCntScore = 0; nCntScore < MAX_SCORE_DIGIT; nCntScore++)
	{
		g_aScoreDigit[nCntScore] = 0;
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_FRAME,			// ファイルの名前
								&g_pTextureScore[0]);	// テクスチャへのポインタ

	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_SCORE,			// ファイルの名前
								&g_pTextureScore[1]);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexScore(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	// テクスチャの開放
	for (int nCntData = 0; nCntData < 2; nCntData++)
	{
		if (g_pTextureScore[nCntData] != NULL)
		{
			g_pTextureScore[nCntData]->Release();
			g_pTextureScore[nCntData] = NULL;
		}
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
{//まだ書かない

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
	pDevice->SetTexture(0, g_pTextureScore[0]);
	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類		//プリミティブ == ポリゴン
		0,							   //開始する頂点のインデックス(基本０)
		2);		   										   //プリミティブの数

	for (nCntScore = 1; nCntScore < MAX_SCORE_DIGIT + 1; nCntScore++)
	{
		pDevice->SetTexture(0, g_pTextureScore[1]);
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
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_SCORE_DIGIT + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

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
	pVtx[0].pos = D3DXVECTOR3(FRAME_INTERVAL, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH- FRAME_INTERVAL, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(FRAME_INTERVAL, 100, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH- FRAME_INTERVAL, 100, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	for (nCntData = 0; nCntData < MAX_SCORE_DIGIT; nCntData++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3((SCORE_POS_X + ((SCORE_SIZE * 1.75f) * nCntData)) - SCORE_SIZE, SCORE_POS_Y - SCORE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((SCORE_POS_X + ((SCORE_SIZE * 1.75f) * nCntData)) + SCORE_SIZE, SCORE_POS_Y - SCORE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((SCORE_POS_X + ((SCORE_SIZE * 1.75f) * nCntData)) - SCORE_SIZE, SCORE_POS_Y + SCORE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((SCORE_POS_X + ((SCORE_SIZE * 1.75f) * nCntData)) + SCORE_SIZE, SCORE_POS_Y + SCORE_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

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
	else if (g_nScore > ((int)powf(10.0f, MAX_SCORE_DIGIT + 1.0f) - 1))//カンストさせる
	{
		g_nScore = (int)powf(10.0f, MAX_SCORE_DIGIT + 1.0f) - 1;
	}

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
	pVtx += 4;
	for (nCntData = 0; nCntData < MAX_SCORE_DIGIT; nCntData++)
	{
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
//=============================================================================
// スコアのリセット
//=============================================================================
void ResetScore(void)
{
	g_nScore = 0;
}

//=============================================================================
// スコアの引き継ぎ
//=============================================================================
void OverStageScore(int nScore)
{
	g_nScore = nScore;
}

//=============================================================================
// スコアの取得
//=============================================================================
int GetScore(void)
{
	return g_nScore;
}
