//*****************************************************************************
//
// ランキング処理 [ranking.cpp]
// Author : Kodama Yuto
//										(:3 )三
//*****************************************************************************
//インクルードファイル
#include"ranking.h"
//#include"score.h"
#include"fade.h"
//=============================================================================
//	プロトタイプ宣言
//=============================================================================
void MakeRankingFont(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	グローバル変数宣言
//=============================================================================
int g_nRankScore = 5000;
int g_aRankingDigit[MAX_RANKING_DIGIT] = {0,0,0,0,0,0,0,0,0,0};

int g_nCntTimer = 0;

bool g_bRankingEnter = true;	//	PRESS ENTER の点滅
bool g_bHighScore = false;		//	ハイスコアの更新
bool g_bScoreDisp = true;		//	ハイスコア時のスコアの点滅

LPDIRECT3DTEXTURE9		g_pTextureRanking[MAX_RANKING_TEXTURE] = {};			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;			// 頂点バッファへのポインタ

LPD3DXFONT	pRankingFont = NULL;	// フォントオブジェクト

D3DXCOLOR g_RankingFontColor;		//フォントの色
char g_RankingText[256];	//フォントの文字[256で固定]

RECT g_RankingRect = {	//フォントを置く範囲
	550,		// 左上のx座標
	300,		// 左上のy座標
	900,		// 右下のx座標
	400			// 右下のy座標
};
//=============================================================================
//	メイン関数
//=============================================================================
void InitRanking(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCntTimer = 0;
	g_bScoreDisp = true;


	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RANKING_01,		// ファイルの名前
		&g_pTextureRanking[0]);	// テクスチャへのポインタ
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RANKING_02,		// ファイルの名前
		&g_pTextureRanking[1]);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexRanking(pDevice);

	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	//メッシュフィールドの初期化処理
	InitMeshField();

	//メッシュウォールの初期化処理
	InitMeshWall();

	MakeRankingFont(pDevice);
	g_RankingFontColor = D3DXCOLOR(1.0f,1.0f,0.0f,1.0f);		//フォントの色

	wsprintf(g_RankingText, "%d.%d", g_nRankScore / TIMER_INTERVAL, g_nRankScore % TIMER_INTERVAL);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRanking(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	//メッシュフィールドの終了処理
	UninitMeshField();

	//メッシュウォールの終了処理
	UninitMeshWall();

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

	if (pRankingFont != NULL)
	{
		pRankingFont->Release();
		pRankingFont = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRanking(void)
{

	// カメラの更新処理
	UpdateCamera();

	// ライトの更新処理
	UpdateLight();

	//メッシュフィールドの更新処理
	UpdateMeshField();

	//メッシュウォールの更新処理
	UpdateMeshWall();


	FADE *pFade;
	pFade = GetFade();

	g_nCntTimer++;

 //ENTERキーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true || g_nCntTimer % 500 == 0)
	{
		if (*pFade != FADE_OUT)
		{
			SetFade(MODE_TITLE);
			StopSound();
			PlaySound(SOUND_LABEL_SE001);
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



}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRanking(void)
{
	// カメラの設定
	SetCamera();

	//メッシュフィールドの描画処理
	DrawMeshField();

	//メッシュウォールの描画処理
	DrawMeshWall();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_pTextureRanking[0]);//テクスチャの設定

	if (g_bRankingEnter == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
			0,					   //開始する頂点のインデックス 56
			2);		   	       //プリミティブの数
	}

	pDevice->SetTexture(0, g_pTextureRanking[1]);//テクスチャの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
		4,					   //開始する頂点のインデックス 56
		2);		   	       //プリミティブの数

	if (g_bScoreDisp == true)
	{
		//フォント
		pRankingFont->DrawText(
			NULL,								// NULL
			g_RankingText,						// 描画するテキスト
			-1,									// 描画する文字数(-1で上のテキストの文字数を取得してくれる)
			&g_RankingRect,						// 描画範囲(上で定義したRECT型の変数のポインタを入れる)
			DT_VCENTER | DT_LEFT,				// 描画オプション
			g_RankingFontColor					// 色指定
		);

	}


}


//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	//int nCntData;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANKING_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						// 頂点情報を設定
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(0, 550, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(400, 550, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 600, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(400, 600, 0.0f);


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
	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(400, 50, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(900, 50, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(400, 200, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(900, 200, 0.0f);


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

	g_pVtxBuffRanking->Unlock();

}

//=============================================================================
//	フォントの作成
//=============================================================================
void MakeRankingFont(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXCreateFont(
		pDevice,					// デバイスのポインタ
		60,							// 高さ
		30,							// 幅
		FW_BLACK,					// フォントの太さ
		NULL,						// 下線
		FALSE,						// 斜体(TRUEでon,FALSEでoff)
		SHIFTJIS_CHARSET,			// 文字セット
		OUT_DEFAULT_PRECIS,			// 出力制度(OUT_DEFAULT_PRECISで固定)
		PROOF_QUALITY,				// 文字の品質
		FIXED_PITCH | FF_SCRIPT,	// ピッチとファミリのインデックス
		TEXT("Meiryo UI"),			// フォント名(空白、大文字も含めて正確に入力すること)
		&pRankingFont);				// フォントのポインタ
}

//=============================================================================
//	スコアのセット
//=============================================================================
void SetRankScore(int nScore)
{

	if (nScore < g_nRankScore)
	{
		g_nRankScore = nScore;//ハイスコア更新
		g_bHighScore = true;
	}
	else
	{
		g_bHighScore = false;
	}

}