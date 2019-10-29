//*****************************************************************************
//
//					DirectX ポーズ処理 [pause.cpp]
//					Author Kodama Yuto
//
//*****************************************************************************
//インクルードファイル
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define	PAUSEMENU_NUM_POLYGON (4)

//=============================================================================
//							プロトタイプ宣言
//=============================================================================
void MakeVertexPause(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//							グローバル変数宣言
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;					//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePause[PAUSEMENU_NUM_POLYGON] = {}; //テクスチャへのポインタ

D3DXCOLOR g_aColorPause;
int g_nSerectPauseMenu;		//ポーズ画面でのモード選択
bool g_bPauseMenuDisp;		//ポーズ画面の表示・非表示		true == 表示

//-----------------------------------------------------------------------------
//						   ポーズ画面の初期化処理
//-----------------------------------------------------------------------------
void InitPause(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得
	
	pDevice = GetDevice();

	//初期化
	g_nSerectPauseMenu = 0;
	g_aColorPause = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	g_bPauseMenuDisp = true;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURE_001,&g_pTexturePause[0]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURE_002, &g_pTexturePause[1]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURE_003, &g_pTexturePause[2]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURE_004, &g_pTexturePause[3]);

	//頂点の作成
	MakeVertexPause(pDevice);

}

//-----------------------------------------------------------------------------
//						   ポーズ画面の終了処理
//-----------------------------------------------------------------------------
void UninitPause(void)
{
	//テクスチャの破棄
	for (int nCntData = 0; nCntData < PAUSEMENU_NUM_POLYGON; nCntData++)
	{
		if (g_pTexturePause[nCntData] != NULL)
		{
			g_pTexturePause[nCntData]->Release();
			g_pTexturePause[nCntData] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//-----------------------------------------------------------------------------
//							ポーズ画面の更新処理
//-----------------------------------------------------------------------------
void UpdatePause(void)
{
	FADE *pFade;
	pFade = GetFade();

	//ポーズ画面の表示・非表示
	if (GetKeyboardTrigger(DIK_O) == true)
	{
		g_bPauseMenuDisp = g_bPauseMenuDisp ? false : true;
		SerectReset();

	}
	//モード選択
	if (GetKeyboardTrigger(DIK_W) == true && g_bPauseMenuDisp == true)//↑
	{
		g_nSerectPauseMenu = (g_nSerectPauseMenu + 1) % 2;//0→1→0
		PlaySound(SOUND_LABEL_SE_001);
	}
	else if (GetKeyboardTrigger(DIK_S) == true && g_bPauseMenuDisp == true)//↓
	{
		g_nSerectPauseMenu = (g_nSerectPauseMenu + 1) % 2;//0→1→0
		PlaySound(SOUND_LABEL_SE_001);
	}


	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//押したときのg_nSerectPauseMenuの位置に応じて挙動を決める
		switch (g_nSerectPauseMenu)
		{
		case 0://再開
			PauseModeChange();
			PlaySound(SOUND_LABEL_SE_002);
			break;
		case 1://終了
			if (*pFade != FADE_OUT)
			{
				SetFade(MODE_TITLE);
				StopSound(SOUND_LABEL_BGM001);
				PlaySound(SOUND_LABEL_SE_000);
			}
			break;
		}

		DispReset();
	}
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	for (int nCntPausePolygon = 2; nCntPausePolygon < PAUSEMENU_NUM_POLYGON; nCntPausePolygon++)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntPausePolygon;

		pVtx[0].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffPause->Unlock();
	}
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * (g_nSerectPauseMenu + 2);

	pVtx[0].col = g_aColorPause;
	pVtx[1].col = g_aColorPause;
	pVtx[2].col = g_aColorPause;
	pVtx[3].col = g_aColorPause;

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

}

//-----------------------------------------------------------------------------
//							ポーズ画面の描画処理
//-----------------------------------------------------------------------------
void DrawPause(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//描画
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

	pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

	if (g_bPauseMenuDisp == true)
	{
		//ポリゴンの描画
		for (int nCntPausePolygon = 0; nCntPausePolygon < PAUSEMENU_NUM_POLYGON; nCntPausePolygon++)
		{
			pDevice->SetTexture(0, g_pTexturePause[nCntPausePolygon]);//テクスチャの設定

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
				4 * nCntPausePolygon,				   //開始する頂点のインデックス(基本０)
				2);		   							   //プリミティブの数

		}
	}
												
}
//-----------------------------------------------------------------------------
//						ポーズ画面の頂点の作成
//-----------------------------------------------------------------------------
void MakeVertexPause(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSEMENU_NUM_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);
	
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	/*バックスクリーン*/
	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);
	
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	
	//頂点カラー	白
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	pVtx += 4;

	/*操作説明*/
	pVtx[0].pos = D3DXVECTOR3(PAUSE_WIDTH-750, PAUSE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSE_WIDTH-750, PAUSE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);

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
	for (int nCntPausePolygon = 0; nCntPausePolygon < 2; nCntPausePolygon++)
	{

		pVtx[0].pos = D3DXVECTOR3(50, 140.0f + (250 * nCntPausePolygon), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(480, 140.0f + (250 * nCntPausePolygon), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(50, 190.0f + (250 * nCntPausePolygon), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(480, 190.0f + (250 * nCntPausePolygon), 0.0f);

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
	g_pVtxBuffPause->Unlock();

}
//=============================================================================
//		選択の初期化
//=============================================================================
void SerectReset(void)
{
	g_nSerectPauseMenu = 0;	
}

//=============================================================================
//		表示状態の初期化
//=============================================================================
void DispReset(void)
{
	g_bPauseMenuDisp = true;
}