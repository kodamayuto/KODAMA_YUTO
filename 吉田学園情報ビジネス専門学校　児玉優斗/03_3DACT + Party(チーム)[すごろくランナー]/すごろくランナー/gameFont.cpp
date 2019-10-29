//=============================================================================
//
// フォント処理 [gameFont.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "gameFont.h"
#include "game.h"

//=============================================================================
//	プロトタイプ宣言
//=============================================================================
void MakeGameFont(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pvtxBuffFont = NULL;					//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureFont = NULL; //テクスチャへのポインタ

LPD3DXFONT	g_pGameFont = NULL;	// フォントオブジェクト
D3DXCOLOR g_FontCol;		//フォントの色
char g_FontText[256];	//フォントの文字[256で固定]

RECT g_FontRect = {	//フォントを置く範囲
	900,		// 左上のx座標
	300,		// 左上のy座標
	1300,		// 右下のx座標
	500			// 右下のy座標
};

//=============================================================================
//	初期化処理
//=============================================================================
void InitFont(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//変数の初期化
	g_FontCol = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
	//フォントの作成
	MakeGameFont(pDevice);

	ZeroMemory(&g_FontText, sizeof(char));

	wsprintf(g_FontText, "Yボタンでマップモード\nAボタンでダイスを振る");
	D3DXCreateTextureFromFile(pDevice, FONT_TEXFILE, &g_pTextureFont);


}

//=============================================================================
//	終了処理
//=============================================================================
void UninitFont(void)
{
	//テクスチャの解放
	if (g_pTextureFont != NULL)
	{
		g_pTextureFont->Release();
		g_pTextureFont = NULL;

	}
	//頂点バッファの解放
	if (g_pvtxBuffFont != NULL)
	{
		g_pvtxBuffFont->Release();
		g_pvtxBuffFont = NULL;
	}
	//フォントの解放
	if (g_pGameFont != NULL)
	{
		g_pGameFont->Release();
		g_pGameFont = NULL;
	}

}

//=============================================================================
//	更新処理
//=============================================================================
void UpdateFont(void)
{

}

//=============================================================================
//	描画処理
//=============================================================================
void DrawFont(void)
{
	if (GetTurnState() == TURNSTATE_DICE)
	{
		//変数宣言
		LPDIRECT3DDEVICE9 pDevice;

		//デバイスの取得
		pDevice = GetDevice();

		//描画
		pDevice->SetStreamSource(0, g_pvtxBuffFont, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

		pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定
		pDevice->SetTexture(0, g_pTextureFont);//テクスチャの設定

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
			0,										//開始する頂点のインデックス(基本０)
			2);		   							   //プリミティブの数


		//フォントの描画
		g_pGameFont->DrawText(
			NULL,								// NULL
			g_FontText,						// 描画するテキスト
			-1,									// 描画する文字数(-1で上のテキストの文字数を取得してくれる)
			&g_FontRect,						// 描画範囲(上で定義したRECT型の変数のポインタを入れる)
			DT_VCENTER | DT_LEFT,				// 描画オプション
			g_FontCol					// 色指定
		);


	}
}

//=============================================================================
//	フォントの作成
//=============================================================================
void MakeGameFont(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	D3DXCreateFont(
		pDevice,					// デバイスのポインタ
		48,							// 高さ
		20,							// 幅
		FW_BLACK,					// フォントの太さ
		NULL,						// 下線
		FALSE,						// 斜体(TRUEでon,FALSEでoff)
		SHIFTJIS_CHARSET,			// 文字セット
		OUT_DEFAULT_PRECIS,			// 出力制度(OUT_DEFAULT_PRECISで固定)
		PROOF_QUALITY,				// 文字の品質
		FIXED_PITCH | FF_SCRIPT,	// ピッチとファミリのインデックス
		TEXT("Meiryo UI"),			// フォント名(空白、大文字も含めて正確に入力すること)
		&g_pGameFont);				// フォントのポインタ

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pvtxBuffFont,
		NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pvtxBuffFont->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(870.0f,320.0f,0.0f);
	pVtx[1].pos = D3DXVECTOR3(1300.0f, 320.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(870.0f, 480.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1300.0f, 480.0f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pvtxBuffFont->Unlock();

}

