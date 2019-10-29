//=============================================================================
//
// タイマー処理 [timer.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "Timer.h"
#include "fade.h"
//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_TIMER_POLYGON (2)

//=============================================================================
//	プロトタイプ宣言
//=============================================================================
void MakeTimerFont(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;					//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTimer[MAX_TIMER_POLYGON] = {};						//テクスチャへのポインタ

LPD3DXFONT	pTimerFont = NULL;	// フォントオブジェクト
D3DXCOLOR g_TimerFontColor;		//フォントの色
char g_TimerText[256];	//フォントの文字[256で固定]

RECT g_TimerRect = {	//フォントを置く範囲
	990,		// 左上のx座標
	10,			// 左上のy座標
	1300,		// 右下のx座標
	110			// 右下のy座標
};

int g_nCountTimer;		//タイマーカウント用
int g_nDiceTime;		//サイコロのタイマー

bool g_bSetTimerFlag;		//タイマーのカウント制御

//=============================================================================
//	初期化処理
//=============================================================================
void InitTimer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/timer.png", &g_pTextureTimer[1]);

	//変数の初期化
	g_nCountTimer = 0;
	g_nDiceTime = 0;
	g_TimerFontColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_bSetTimerFlag = true;
	//フォントの作成
	MakeTimerFont(pDevice);
	MakeVertexTimer(pDevice);
}

//=============================================================================
//	終了処理
//=============================================================================
void UninitTimer(void)
{
	//テクスチャの解放
	for (int nCntTex = 0; nCntTex < MAX_TIMER_POLYGON; nCntTex++)
	{
		if (g_pTextureTimer[nCntTex] != NULL)
		{
			g_pTextureTimer[nCntTex]->Release();
			g_pTextureTimer[nCntTex] = NULL;
		}

	}
	//バッファの解放
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;

	}
	//フォントの解放
	if (pTimerFont != NULL)
	{
		pTimerFont->Release();
		pTimerFont = NULL;
	}

}

//=============================================================================
//	更新処理
//=============================================================================
void UpdateTimer(void)
{
	GAMESTATE pGamestate;
	pGamestate = GetGameState();
	FADE *pFade;
	pFade = GetFade();

		//タイマーのカウントダウン
		if (*pFade != FADE_OUT)
		{
		g_nCountTimer++;
			if (g_nCountTimer % TIMER_INTERVAL == 0 && pGamestate != GAMESTATE_END)
			{
				g_nDiceTime++;

			}
			//出力する文字列を設定
			wsprintf(g_TimerText, "%d.%d", g_nCountTimer / TIMER_INTERVAL, g_nCountTimer % TIMER_INTERVAL);

		}

}

//=============================================================================
//	描画処理
//=============================================================================
void DrawTimer(void)
{

	for (int nCntTimer = 0; nCntTimer < MAX_TIMER_POLYGON; nCntTimer++)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = GetDevice();

		pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

		pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

									   // テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTimer[nCntTimer]);//テクスチャの設定

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
			4 * nCntTimer,					   //開始する頂点のインデックス(基本０)
			2);		   	       //プリミティブの数
	}
	 //フォントの描画
		pTimerFont->DrawText(
			NULL,								// NULL
			g_TimerText,						// 描画するテキスト
			-1,									// 描画する文字数(-1で上のテキストの文字数を取得してくれる)
			&g_TimerRect,						// 描画範囲(上で定義したRECT型の変数のポインタを入れる)
			DT_VCENTER | DT_LEFT,				// 描画オプション
			g_TimerFontColor					// 色指定
		);
}

//=============================================================================
//	フォントの作成
//=============================================================================
void MakeTimerFont(LPDIRECT3DDEVICE9 pDevice)
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
		&pTimerFont);				// フォントのポインタ
}

int GetTimer(void)
{
	return g_nCountTimer;
}

//=============================================================================
//	頂点情報の追加
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	for (int nCntTimer = 0; nCntTimer < MAX_TIMER_POLYGON; nCntTimer++)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntTimer;
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(970.0f, 0.0f + ((MAX_TIMER_POLYGON-nCntTimer) * 10.0f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1200.0f, 0.0f + ((MAX_TIMER_POLYGON - nCntTimer) * 10.0f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(970.0f, 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1200.0f, 100.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー	白
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
		g_pVtxBuffTimer->Unlock();

	}

}
