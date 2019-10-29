//*****************************************************************************
//
//					DirectX 背景処理 [bg.cpp]
//					Author Kodama Yuto
//
//*****************************************************************************
//インクルードファイル
#include "main.h"
#include "bg.h"

//=============================================================================
//							グローバル変数宣言
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBG[3] = {};	                //テクスチャへのポインタ

int g_nCounterBG = 0;

D3DXVECTOR3 g_aBG_pos[3];

//-----------------------------------------------------------------------------
//						   背景の初期化処理
//-----------------------------------------------------------------------------
void InitBG(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得
	
	pDevice = GetDevice();
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	for (int nCntData = 0; nCntData < 3; nCntData++)
	{
		g_aBG_pos[nCntData] = D3DXVECTOR3(BG_POS_X,BG_POS_Y,0.0f);
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_100,&g_pTextureBG[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_101, &g_pTextureBG[1]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_102, &g_pTextureBG[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	for (int nCntData = 0; nCntData < 3; nCntData++)
	{

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntData;

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aBG_pos[nCntData].x - BG_POS_X, g_aBG_pos[nCntData].y - BG_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBG_pos[nCntData].x + BG_POS_X, g_aBG_pos[nCntData].y - BG_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBG_pos[nCntData].x - BG_POS_X, g_aBG_pos[nCntData].y + BG_POS_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBG_pos[nCntData].x + BG_POS_X, g_aBG_pos[nCntData].y + BG_POS_Y, 0.0f);

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
		g_pVtxBuffBG->Unlock();

	}
}

//-----------------------------------------------------------------------------
//						   背景の終了処理
//-----------------------------------------------------------------------------
void UninitBG(void)
{
	//テクスチャの破棄
	for (int nCntData = 0; nCntData < 3; nCntData++)
	{
		if (g_pTextureBG[nCntData] != NULL)
		{
			g_pTextureBG[nCntData]-> Release();
			g_pTextureBG[nCntData] =  NULL;
		}

	}

	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//-----------------------------------------------------------------------------
//							背景の更新処理
//-----------------------------------------------------------------------------
//まだ何も書かない
void UpdateBG(void)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ
	Player *pPlayer;

	pPlayer = GetPlayer();

	g_nCounterBG++;
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);


	//テクスチャ座標
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00025f + 0.0f, 0.0025f * -g_nCounterBG + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00025f + 1.0f, 0.0025f * -g_nCounterBG + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00025f + 0.0f, 0.0025f * -g_nCounterBG + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00025f + 1.0f, 0.0025f * -g_nCounterBG + 1.0f);

	pVtx += 4;
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.55f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.55f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.55f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.55f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(pPlayer->pos.x * 0.0004f, 0.005f * -g_nCounterBG + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(pPlayer->pos.x * 0.0004f + 1.0f, 0.005f * -g_nCounterBG + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(pPlayer->pos.x * 0.0004f, 0.005f * -g_nCounterBG + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(pPlayer->pos.x * 0.0004f + 1.0f, 0.005f * -g_nCounterBG + 1.0f);

	pVtx += 4;
	pVtx[0].col = D3DXCOLOR(1.0f, 0.59f, 0.54f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.59f, 0.54f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.59f, 0.54f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.59f, 0.54f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00065f, 0.008f * -g_nCounterBG + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00065f + 1.0f, 0.008f * -g_nCounterBG + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00065f, 0.008f * -g_nCounterBG + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(pPlayer->pos.x * 0.00065f + 1.0f, 0.008f * -g_nCounterBG + 1.0f);

	g_pVtxBuffBG->Unlock();

}

//-----------------------------------------------------------------------------
//							背景の描画処理
//-----------------------------------------------------------------------------
void DrawBG(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//描画
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

	pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定


	for (int nCntData = 0; nCntData < 3; nCntData++)
	{
		pDevice->SetTexture(0, g_pTextureBG[nCntData]);//テクスチャの設定

												//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
			4 * nCntData,					   //開始する頂点のインデックス(基本０)
			2);		   	       //プリミティブの数
	}
}

