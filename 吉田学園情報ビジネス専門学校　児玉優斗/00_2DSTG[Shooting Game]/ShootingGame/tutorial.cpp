//*****************************************************************************
//
//					DirectX タイトル処理 [tutorial.cpp]
//					Author Kodama Yuto
//
//****************************************************************************
//インクルードファイル
#include "tutorial.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
//							グローバル変数宣言
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTutorial[2] = {};	                //テクスチャへのポインタ

int g_CounterTutorial = 0;
bool g_bEnterDispTutorial = true;

//-----------------------------------------------------------------------------
//						   背景の初期化処理
//-----------------------------------------------------------------------------
void InitTutorial(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得

	pDevice = GetDevice();
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE, &g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_ENTER, &g_pTextureTutorial[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_HEIGHT, 0.0f);

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
	g_pVtxBuffTutorial->Unlock();

	PlaySound(SOUND_LABEL_BGM003);//音
}

//-----------------------------------------------------------------------------
//						   背景の終了処理
//-----------------------------------------------------------------------------

void UninitTutorial(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureTutorial[nCntTex] != NULL)
		{
			g_pTextureTutorial[nCntTex]->Release();
			g_pTextureTutorial[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}

//-----------------------------------------------------------------------------
//							背景の更新処理
//-----------------------------------------------------------------------------
void UpdateTutorial(void)
{
	FADE *pFade;
	pFade = GetFade();

	g_CounterTutorial++;
	if (g_CounterTutorial % 40 == 0 || *pFade == FADE_OUT && g_CounterTutorial % 3 == 0)
	{
		g_bEnterDispTutorial = g_bEnterDispTutorial ? false : true;
	}

	//ENTERキーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{

		if (*pFade != FADE_OUT)
		{
			StopSound(SOUND_LABEL_BGM003);
			PlaySound(SOUND_LABEL_SE_DECIDE);//音

			SetFade(MODE_GAME);
		}	
	}
}

//-----------------------------------------------------------------------------
//							背景の描画処理
//-----------------------------------------------------------------------------

void DrawTutorial(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//描画
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (nCntTex != 1 || nCntTex == 1 && g_bEnterDispTutorial == true)
		{
			pDevice->SetTexture(0, g_pTextureTutorial[nCntTex]);//テクスチャの設定

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
				4 * nCntTex,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数
		}
	}
}

