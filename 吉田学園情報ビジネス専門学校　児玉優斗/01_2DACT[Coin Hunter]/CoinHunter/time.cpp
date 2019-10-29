//=============================================================================
//
// タイム処理 [time.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "time.h"
#include "fade.h"

//**************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime[2] = {};			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;			// 頂点バッファへのポインタ
Time					g_nTime;						// タイム
int						g_aTimeDigit[MAX_TIME_DIGIT];   // タイムのデータ

int g_nCounterTime;		//カウンター
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// 初期化処理
//=============================================================================
void InitTime(void)
{
	int nCntTime;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_nCounterTime = TIME_INTERVAL;
	g_nTime.col = D3DXCOLOR(1.0f,0.5f,0.0f,1.0f);
	g_nTime.nTime = 100;
	g_nTime.bScoreFlag = true;


	for (nCntTime = 0; nCntTime < MAX_TIME_DIGIT; nCntTime++)
	{
		g_aTimeDigit[nCntTime] = 0;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_TIME,		// ファイルの名前
								&g_pTextureTime[0]);	// テクスチャへのポインタ
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_TIME_1,		// ファイルの名前
								&g_pTextureTime[1]);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexTime(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTime(void)
{
	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureTime[nCntTex] != NULL)
		{
			g_pTextureTime[nCntTex]->Release();
			g_pTextureTime[nCntTex] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTime(void)
{//まだ書かない
 //変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ
	FADE *pFade;
	pFade = GetFade();
	int nCntTime;
	if (GetNumCoin() != 0)//コインが０になるまでカウンターを回す
	{
		g_nCounterTime--;
	}
	else if(GetNumCoin() == 0 && g_nTime.bScoreFlag == true)
	{
		AddScore(((g_nTime.nTime * 100) + (TIME_INTERVAL - g_nCounterTime)) * 10);
		g_nTime.bScoreFlag = false;
		SetGameState(GAMESTATE_END);
	}
	if (g_nCounterTime  == 0 && g_nTime.nTime > 0)
	{
		g_nTime.nTime--;
		g_nCounterTime = TIME_INTERVAL;
	}
	else if (g_nCounterTime == 0 && g_nTime.nTime <= 0)
	{
		SetRankScore(GetScore());
		SetFade(MODE_RESULT);
		StopSound(SOUND_LABEL_BGM001);
	}

	if (g_nTime.nTime <= 50)
	{
		g_nTime.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}

	g_aTimeDigit[0] = g_nTime.nTime % 1000 / 100;
	g_aTimeDigit[1] = g_nTime.nTime % 100 /  10;
	g_aTimeDigit[2] = g_nTime.nTime % 10 /   1;

	// 頂点情報を設定
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_TIME_DIGIT; nCntTime++)
	{
		pVtx[0].col = g_nTime.col;
		pVtx[1].col = g_nTime.col;
		pVtx[2].col = g_nTime.col;
		pVtx[3].col = g_nTime.col;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(g_aTimeDigit[nCntTime] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aTimeDigit[nCntTime] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aTimeDigit[nCntTime] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((g_aTimeDigit[nCntTime] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}


	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntTime;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定

	for (nCntTime = 0; nCntTime < MAX_TIME_DIGIT; nCntTime++)
	{
	pDevice->SetTexture(0, g_pTextureTime[0]);
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類		//プリミティブ == ポリゴン
			4 * nCntTime,							   //開始する頂点のインデックス(基本０)
			2);		   										   //プリミティブの数
	}
	pDevice->SetTexture(0, g_pTextureTime[1]);
	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類		//プリミティブ == ポリゴン
		4 * nCntTime,							   //開始する頂点のインデックス(基本０)
		2);		   										   //プリミティブの数

}

//=============================================================================
// 頂点情報の作成
//==========================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntTime;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_TIME_DIGIT + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	// 頂点情報を設定
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_TIME_DIGIT; nCntTime++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3((TIME_POS_X + ((TIME_SIZE * 1.75f) * nCntTime)) - TIME_SIZE, TIME_POS_Y - TIME_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((TIME_POS_X + ((TIME_SIZE * 1.75f) * nCntTime)) + TIME_SIZE, TIME_POS_Y - TIME_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((TIME_POS_X + ((TIME_SIZE * 1.75f) * nCntTime)) - TIME_SIZE, TIME_POS_Y + TIME_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((TIME_POS_X + ((TIME_SIZE * 1.75f) * nCntTime)) + TIME_SIZE, TIME_POS_Y + TIME_SIZE, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	pVtx[0].pos = D3DXVECTOR3(580, 10, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(700, 10, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(580, 60, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(700, 60, 0.0f);

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


	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();


}


//
//
//
int GetTime(void)
{
	return g_nTime.nTime;
}
