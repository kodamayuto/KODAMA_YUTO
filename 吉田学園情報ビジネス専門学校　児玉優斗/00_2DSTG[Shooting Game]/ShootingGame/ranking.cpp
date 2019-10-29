//*****************************************************************************
//
// ランキング処理 [ranking.cpp]
// Author : Kodama Yuto
//
//*****************************************************************************
//インクルードファイル
#include"ranking.h"
#include"score.h"
#include"fade.h"
#include"sound.h"

//=============================================================================
//	グローバル変数宣言
//=============================================================================
int g_nRankScore = 0;
int g_aRankingDigit[MAX_RANKING_DIGIT] = {0,0,0,0,0,0,0,0,0,0};

int g_nCntTimer = 0;

bool g_bRankingEnter = true;	//	PRESS ENTER の点滅
bool g_bHighScore = false;		//	ハイスコアの更新
bool g_bScoreDisp = true;		//	ハイスコア時のスコアの点滅

LPDIRECT3DTEXTURE9		g_pTextureRanking[MAX_RANKING_TEXTURE] = {};			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;			// 頂点バッファへのポインタ

//=============================================================================
//	メイン関数
//=============================================================================
void InitRanking(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCntTimer = 0;
	g_bScoreDisp = true;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RANKING_00,		// ファイルの名前
		&g_pTextureRanking[0]);	// テクスチャへのポインタ

	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RANKING_01,		// ファイルの名前
		&g_pTextureRanking[1]);	// テクスチャへのポインタ

	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RANKING_02,		// ファイルの名前
		&g_pTextureRanking[2]);	// テクスチャへのポインタ

	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RANKING_03,		// ファイルの名前
		&g_pTextureRanking[3]);	// テクスチャへのポインタ

	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RANKING_04,		// ファイルの名前
		&g_pTextureRanking[4]);	// テクスチャへのポインタ

	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RANKING_05,		// ファイルの名前
		&g_pTextureRanking[5]);	// テクスチャへのポインタ
								// 頂点情報の作成
	MakeVertexRanking(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRanking(void)
{
	// テクスチャの開放
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING_TEXTURE; nCntRanking++)
	{

		if (g_pTextureRanking[nCntRanking] != NULL)
		{
			g_pTextureRanking[nCntRanking]->Release();
			g_pTextureRanking[nCntRanking] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRanking(void)
{
	FADE *pFade;
	pFade = GetFade();

	g_nCntTimer++;
 //ENTERキーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true || g_nCntTimer % 1000 == 0)
	{
		if (*pFade != FADE_OUT)
		{
			StopSound();

			PlaySound(SOUND_LABEL_SE_DECIDE);//音

			SetFade(MODE_TITLE);
		}
	}

	if (g_nCntTimer % 40 == 0 || *pFade == FADE_OUT && g_nCntTimer % 3 == 0)
	{
		g_bRankingEnter = g_bRankingEnter ? false : true;
	}

	if (g_bHighScore == true && g_nCntTimer % 10 == 0)
	{
		g_bScoreDisp = g_bScoreDisp ? false : true;
	}


	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.002f * -g_nCntTimer + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.002f * -g_nCntTimer + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.002f * -g_nCntTimer + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.002f * -g_nCntTimer + 1.0f);

	pVtx += 4;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.004f * -g_nCntTimer + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.004f * -g_nCntTimer + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.004f * -g_nCntTimer + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.004f * -g_nCntTimer + 1.0f);

	pVtx += 4;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.007f * -g_nCntTimer + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.007f * -g_nCntTimer + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.007f * -g_nCntTimer + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.007f * -g_nCntTimer + 1.0f);

	g_pVtxBuffRanking->Unlock();

	// 頂点情報を設定
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 16;

	for (int nCntData = 0; nCntData < MAX_RANKING_DIGIT; nCntData++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(g_aRankingDigit[nCntData] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aRankingDigit[nCntData] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aRankingDigit[nCntData] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((g_aRankingDigit[nCntData] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRanking->Unlock();




}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntTex;
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		pDevice->SetTexture(0, g_pTextureRanking[nCntTex]);//テクスチャの設定

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
			4 * nCntTex,					   //開始する頂点のインデックス 0 4 8
			2);		   	       //プリミティブの数
	}

	pDevice->SetTexture(0, g_pTextureRanking[3]);//テクスチャの設定

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
		4 * nCntTex,					   //開始する頂点のインデックス 12
		2);		   	       //プリミティブの数

	pDevice->SetTexture(0, g_pTextureRanking[4]);//テクスチャの設定
	for (nCntTex = 4; nCntTex < MAX_RANKING_DIGIT + 4; nCntTex++)
	{
		if(g_bScoreDisp == true)
		{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
			4 * nCntTex,					   //開始する頂点のインデックス 16 ～　52
			2);		   	       //プリミティブの数
		}
	}

	pDevice->SetTexture(0, g_pTextureRanking[5]);//テクスチャの設定

	if (g_bRankingEnter == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
			4 * nCntTex,					   //開始する頂点のインデックス 56
			2);		   	       //プリミティブの数
	}
}


//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntData;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_RANKING_DIGIT + 5),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						// 頂点情報を設定
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < 3; nCntData++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


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

	pVtx[0].pos = D3DXVECTOR3(350, 100, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(900, 100, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(350, 200, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(900, 200, 0.0f);

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

	for (nCntData = 0; nCntData < MAX_RANKING_DIGIT; nCntData++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3((RANKING_POS_X + (50 * nCntData)) - RANKING_SIZE, RANKING_POS_Y - RANKING_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((RANKING_POS_X + (50 * nCntData)) + RANKING_SIZE, RANKING_POS_Y - RANKING_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((RANKING_POS_X + (50 * nCntData)) - RANKING_SIZE, RANKING_POS_Y + RANKING_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((RANKING_POS_X + (50 * nCntData)) + RANKING_SIZE, RANKING_POS_Y + RANKING_SIZE, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(g_aRankingDigit[nCntData] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aRankingDigit[nCntData] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aRankingDigit[nCntData] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((g_aRankingDigit[nCntData] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	pVtx[0].pos = D3DXVECTOR3(800, 600, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1100, 600, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(800, 650, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1100, 650, 0.0f);

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
	g_pVtxBuffRanking->Unlock();


}

//=============================================================================
//	スコアのセット
//=============================================================================
void SetRankScore(int nScore)
{

	if (nScore > g_nRankScore)
	{
		g_nRankScore = nScore;//ハイスコア更新
		g_bHighScore = true;
	}
	else
	{
		g_bHighScore = false;
	}

	g_aRankingDigit[0] = g_nRankScore % 10000000000 / 1000000000;
	g_aRankingDigit[1] = g_nRankScore % 1000000000 / 100000000;
	g_aRankingDigit[2] = g_nRankScore % 100000000 / 10000000;
	g_aRankingDigit[3] = g_nRankScore % 10000000 / 1000000;
	g_aRankingDigit[4] = g_nRankScore % 1000000 / 100000;
	g_aRankingDigit[5] = g_nRankScore % 100000 / 10000;
	g_aRankingDigit[6] = g_nRankScore % 10000 / 1000;
	g_aRankingDigit[7] = g_nRankScore % 1000 / 100;
	g_aRankingDigit[8] = g_nRankScore % 100 / 10;
	g_aRankingDigit[9] = g_nRankScore % 10 / 1;

}