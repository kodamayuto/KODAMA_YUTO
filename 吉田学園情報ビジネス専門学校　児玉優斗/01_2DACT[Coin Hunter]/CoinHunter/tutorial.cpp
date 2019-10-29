//*****************************************************************************
//
//					DirectX タイトル処理 [tutorial.cpp]
//					Author Kodama Yuto
//	(:3 )三
//****************************************************************************
//インクルードファイル
#include "tutorial.h"
#include "fade.h"

//=============================================================================
//							グローバル変数宣言
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTutorial[5] = {};	                //テクスチャへのポインタ

int g_CounterTutorial = 0;
bool g_bEnterDispTutorial = true;
int g_nTutorialChange = 0;

//-----------------------------------------------------------------------------
//						   背景の初期化処理
//-----------------------------------------------------------------------------
void InitTutorial(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得

	pDevice = GetDevice();
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	g_nTutorialChange = 0;
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE, &g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_2, &g_pTextureTutorial[1]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_3, &g_pTextureTutorial[2]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_ENTER, &g_pTextureTutorial[3]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_START, &g_pTextureTutorial[4]);

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
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TUTORIAL_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, TUTORIAL_HEIGHT, 0.0f);
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

	pVtx[0].pos = D3DXVECTOR3(920, 120, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1170, 120, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(920, 160, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1170, 160, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();

}

//-----------------------------------------------------------------------------
//						   背景の終了処理
//-----------------------------------------------------------------------------

void UninitTutorial(void)
{

	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
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
		if (g_nTutorialChange < 2)
		{
			g_nTutorialChange++;
			PlaySound(SOUND_LABEL_SE_001);
		}
		else
		{
			if (*pFade != FADE_OUT)
			{

				StopSound(SOUND_LABEL_BGM000);
				PlaySound(SOUND_LABEL_SE_000);
				PlaySound(SOUND_LABEL_BGM001);
				SetFade(MODE_CHANGE);
			}
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
		if (nCntTex != 1)
		{
			if (g_nTutorialChange == 0)
			{
				pDevice->SetTexture(0, g_pTextureTutorial[0]);//テクスチャの設定

			}
			else if(g_nTutorialChange == 1)
			{
				pDevice->SetTexture(0, g_pTextureTutorial[1]);//テクスチャの設定

			}
			else if (g_nTutorialChange == 2)
			{
				pDevice->SetTexture(0, g_pTextureTutorial[2]);//テクスチャの設定

			}

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
				4 * nCntTex,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数

		}
		else if (nCntTex == 1 && g_bEnterDispTutorial == true)
		{
			if (g_nTutorialChange < 2)
			{
				pDevice->SetTexture(0, g_pTextureTutorial[3]);//テクスチャの設定
			}
			else
			{
				pDevice->SetTexture(0, g_pTextureTutorial[4]);//テクスチャの設定
			}
		

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
				4 * nCntTex,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数
		}
	}
}

