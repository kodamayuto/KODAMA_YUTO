//*****************************************************************************
//
//					DirectX モード選択処理 [modeSelect.cpp]
//					Author Kodama Yuto
//
//*****************************************************************************
//インクルードファイル
#include "modeSelect.h"
#include "input.h"
#include "polygon.h"
#include "island.h"
#include "camera.h"
#include "light.h"
#include "sky.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define	SELECTMENU_NUM_POLYGON (5)
#define FADEFONT_A			   (0.06f)

//=============================================================================
//							プロトタイプ宣言
//=============================================================================
void MakeVertexSelect(LPDIRECT3DDEVICE9 pDevice);
void MakeFont(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//							グローバル変数宣言
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;					//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturemodeSelect[SELECTMENU_NUM_POLYGON] = {}; //テクスチャへのポインタ

D3DXCOLOR g_aColormodeSelect;
int g_nSerectMenuX;		//ポーズ画面でのモード選択
int g_nSerectMenuY;
bool g_bmodeSelectMenuDisp;		//ポーズ画面の表示・非表示		true == 表示

LPD3DXFONT	pFont = NULL;	// フォントオブジェクト
D3DXCOLOR g_FontColor;		//フォントの色
char g_ModeselectText[256];	//フォントの文字

RECT g_Rect = {					//フォントを置く範囲
	250,		// 左上のx座標
	580,		// 左上のy座標
	1230,		// 右下のx座標
	720			// 右下のy座標
};

//-----------------------------------------------------------------------------
//						   初期化処理
//-----------------------------------------------------------------------------
void InitModeSelect(void)
{
	InitCamera();
	InitLight();

	InitPolygon();
	//InitMeshCylinder();
	InitIsland();
	InitSky();
	SetPolygon(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGONTYPE_FIELD, 10000.0f, 10000.0f);


	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//初期化
	g_nSerectMenuX = 0;
	g_nSerectMenuY = 0;
	g_aColormodeSelect = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_FontColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_bmodeSelectMenuDisp = true;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MODESELECT_TEXTURE_002, &g_pTexturemodeSelect[0]);
	D3DXCreateTextureFromFile(pDevice, MODESELECT_TEXTURE_003, &g_pTexturemodeSelect[1]);
	D3DXCreateTextureFromFile(pDevice, MODESELECT_TEXTURE_004, &g_pTexturemodeSelect[2]);
	D3DXCreateTextureFromFile(pDevice, MODESELECT_TEXTURE_005, &g_pTexturemodeSelect[3]);
	D3DXCreateTextureFromFile(pDevice, MODESELECT_TEXTURE_006, &g_pTexturemodeSelect[4]);
	//D3DXCreateTextureFromFile(pDevice, MODESELECT_TEXTURE_006, &g_pTexturemodeSelect[5]);

	//頂点の作成
	MakeVertexSelect(pDevice);

	// フォントの作成
	MakeFont(pDevice);

}

//-----------------------------------------------------------------------------
//						  終了処理
//-----------------------------------------------------------------------------
void UninitModeSelect(void)
{
	UninitCamera();
	UninitLight();
	UninitPolygon();
	UninitIsland();
	UninitSky();
	//テクスチャの破棄
	for (int nCntData = 0; nCntData < SELECTMENU_NUM_POLYGON; nCntData++)
	{
		if (g_pTexturemodeSelect[nCntData] != NULL)
		{
			g_pTexturemodeSelect[nCntData]->Release();
			g_pTexturemodeSelect[nCntData] = NULL;

		}

	}
	//頂点バッファの破棄
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;

	}

	//フォントのポインタの破棄
	if (pFont != NULL)
	{
		pFont->Release();
		pFont = NULL;

	}

}

//-----------------------------------------------------------------------------
//							更新処理
//-----------------------------------------------------------------------------
void UpdateModeSelect(void)
{
	UpdateCamera();
	UpdateLight();

	UpdatePolygon();
	UpdateIsland();
	UpdateSky();
	
	//モード選択
	if (GetKeyboardTrigger(DIK_A) == true || GetJoyPadTrigger(DIJS_BUTTON_21, 0) == true && g_bmodeSelectMenuDisp == true)//↑
	{
		g_nSerectMenuX = (g_nSerectMenuX + 1) % 2;//0→2→1→0
		g_FontColor.a = 0.0f;
		PlaySound(SOUND_LABEL_SE002);
	}
	else if (GetKeyboardTrigger(DIK_D) == true || GetJoyPadTrigger(DIJS_BUTTON_20, 0) == true && g_bmodeSelectMenuDisp == true)//↓
	{
		g_nSerectMenuX = (g_nSerectMenuX + 1) % 2;//0→1→2→0
		g_FontColor.a = 0.0f;
		PlaySound(SOUND_LABEL_SE002);

	}

	if (GetKeyboardTrigger(DIK_W) == true || GetJoyPadTrigger(DIJS_BUTTON_18, 0) == true && g_bmodeSelectMenuDisp == true)
	{
		if (g_nSerectMenuY == 0)
		{
			g_nSerectMenuY = 2;

		}
		else if (g_nSerectMenuY == 2)
		{
			g_nSerectMenuY = 0;

		}
		g_FontColor.a = 0.0f;
		PlaySound(SOUND_LABEL_SE002);
	}
	else if (GetKeyboardTrigger(DIK_S) == true || GetJoyPadTrigger(DIJS_BUTTON_19, 0) == true && g_bmodeSelectMenuDisp == true)//↓
	{
		if (g_nSerectMenuY == 0)
		{
			g_nSerectMenuY = 2;

		}
		else if (g_nSerectMenuY == 2)
		{
			g_nSerectMenuY = 0;

		}
		g_FontColor.a = 0.0f;
		PlaySound(SOUND_LABEL_SE002);
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE || GetJoyPadTrigger(DIJS_BUTTON_1, 0) == true && GetFade() == FADE_NONE)
	{//押したときのg_nSerectmodeSelectMenuの位置に応じて挙動を決める
		PlaySound(SOUND_LABEL_SE000);
		switch (g_nSerectMenuX + g_nSerectMenuY)
		{
		case 0://ゲーム
			SetFade(MODE_GAME);
			break;
		case 1://チュートリアル
			SetFade(MODE_TUTORIAL);
			break;
		case 2://ランキング
			SetFade(MODE_RANKING);
			SetRankingOld(RANKINGOLD_SELECT);

			break;
		case 3://タイトル
			SetFade(MODE_TITLE);

			break;
		}
		//DispReset();
		//SerectReset();

	}
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	for (int nCntmodeSelectPolygon = 1; nCntmodeSelectPolygon < SELECTMENU_NUM_POLYGON; nCntmodeSelectPolygon++)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntmodeSelectPolygon;

		pVtx[0].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffSelect->Unlock();

	}
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * ((g_nSerectMenuX + g_nSerectMenuY) + 1);

	pVtx[0].col = g_aColormodeSelect;
	pVtx[1].col = g_aColormodeSelect;
	pVtx[2].col = g_aColormodeSelect;
	pVtx[3].col = g_aColormodeSelect;

	//頂点バッファをアンロックする
	g_pVtxBuffSelect->Unlock();


	//数値に応じて描画する文字列を決める
	switch (GetNumber())
	{
	case 0:
		wsprintf(g_ModeselectText, "mode ゲーム : ゲームを開始します");
		break;
	case 1:
		wsprintf(g_ModeselectText, "mode チュートリアル : 操作説明を開きます");
		break;
	case 2:
		wsprintf(g_ModeselectText, "mode ランキング : これまでの戦績を表示します");
		break;
	case 3:
		wsprintf(g_ModeselectText, "mode タイトル : タイトルに戻ります");
		break;
	}

	//文字のフェード
	if (g_FontColor.a <= 1.0f)
	{
		g_FontColor.a += FADEFONT_A;

	}
	else
	{
		g_FontColor.a = 1.0f;

	}

}

//-----------------------------------------------------------------------------
//							描画処理
//-----------------------------------------------------------------------------
void DrawModeSelect(void)
{
	SetCamera();

	DrawPolygon();
	DrawIsland();
	DrawSky();
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//描画
	pDevice->SetStreamSource(0, g_pVtxBuffSelect, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

	pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

	if (g_bmodeSelectMenuDisp == true)
	{
		//ポリゴンの描画
		for (int nCntmodeSelectPolygon = 0; nCntmodeSelectPolygon < SELECTMENU_NUM_POLYGON; nCntmodeSelectPolygon++)
		{
			pDevice->SetTexture(0, g_pTexturemodeSelect[nCntmodeSelectPolygon]);//テクスチャの設定

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
				4 * nCntmodeSelectPolygon,				   //開始する頂点のインデックス(基本０)
				2);		   							   //プリミティブの数

		}

	}

	//フォントの描画
	pFont->DrawText(
		NULL,								// NULL
		g_ModeselectText,					// 描画するテキスト
		-1,									// 描画する文字数(-1でテキストの文字数を取得してくれる)
		&g_Rect,							// 描画範囲(上で定義したRECT型の変数のポインタを入れる)
		DT_VCENTER | DT_LEFT,				// 描画オプション
		g_FontColor							// 色指定
	);

}
//-----------------------------------------------------------------------------
//						頂点の作成
//-----------------------------------------------------------------------------
void MakeVertexSelect(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

									//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SELECTMENU_NUM_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelect,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	/*バックスクリーン*/
	//頂点座標
	//pVtx[0].pos = D3DXVECTOR3(MODESELECT_POS_X, MODESELECT_POS_Y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(MODESELECT_WIDTH, MODESELECT_POS_Y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(MODESELECT_POS_X, MODESELECT_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(MODESELECT_WIDTH, MODESELECT_HEIGHT, 0.0f);
	//
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;
	//
	////頂点カラー	白
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, MODESELECT_COL_A);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, MODESELECT_COL_A);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, MODESELECT_COL_A);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, MODESELECT_COL_A);
	////テクスチャ座標
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//
	//pVtx += 4;

	/*説明ふきだし*/
	pVtx[0].pos = D3DXVECTOR3(150, 580, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1130, 580, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(150, 720, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1130, 720, 0.0f);

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
	pVtx += 4;


	/*ポーズUI*/
	for (int nCntmodeSelectPolygon = 0; nCntmodeSelectPolygon < 4; nCntmodeSelectPolygon++)
	{

		pVtx[0].pos = D3DXVECTOR3(80.0f + (650.0f * (nCntmodeSelectPolygon % 2)), 40.0f + (300.0f * (nCntmodeSelectPolygon / 2)), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(550.0f + (650.0f * (nCntmodeSelectPolygon % 2)), 40.0f + (300.0f * (nCntmodeSelectPolygon / 2)), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(80.0f + (650.0f * (nCntmodeSelectPolygon % 2)), 250.0f + (300.0f * (nCntmodeSelectPolygon / 2)), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(550.0f + (650.0f * (nCntmodeSelectPolygon % 2)), 250.0f + (300.0f * (nCntmodeSelectPolygon / 2)), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffSelect->Unlock();

}
//-----------------------------------------------------------------------------
//						フォントの作成
//-----------------------------------------------------------------------------
void MakeFont(LPDIRECT3DDEVICE9 pDevice)
{
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
		&pFont);					// フォントのポインタ

}

//=============================================================================
//		選択の初期化
//=============================================================================
void SerectReset(void)
{
	g_nSerectMenuX = 0;
	g_nSerectMenuY = 0;

}

//=============================================================================
//		表示状態の初期化
//=============================================================================
void DispReset(void)
{
	g_bmodeSelectMenuDisp = true;

}

//=============================================================================
//		デバック用数字表示
//=============================================================================
int GetNumber(void)
{
	return (g_nSerectMenuX + g_nSerectMenuY);
}