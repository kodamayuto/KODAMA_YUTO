//=============================================================================
//
// カウントダウン処理 [countDown.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "countDown.h"
#include "game.h"
#include "meter.h"

//=============================================================================
//	プロトタイプ宣言
//=============================================================================
void MakeVertexCountDown(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCountDown = NULL;					//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureCountDown = NULL;						//テクスチャへのポインタ

int g_nCountDown = 0;			//カウントダウンの数字
int g_nCntNumber = 0;			//カウンター

bool g_bCountDownFlag = false;	//カウントダウンの表示

//=============================================================================
//	初期化処理
//=============================================================================
void InitCountDown(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
		
	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, COUNTDOWN_TEXTURE_FIRENAME, &g_pTextureCountDown);

	//頂点情報の設定
	MakeVertexCountDown(pDevice);
}

//=============================================================================
//	終了処理
//=============================================================================
void UninitCountDown(void)
{
	//テクスチャの破棄
	if (g_pTextureCountDown != NULL)
	{
		g_pTextureCountDown->Release();
		g_pTextureCountDown = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffCountDown != NULL)
	{
		g_pVtxBuffCountDown->Release();
		g_pVtxBuffCountDown = NULL;
	}

}

//=============================================================================
//	更新処理
//=============================================================================
void UpdateCountDown(void)
{
	VERTEX_2D *pVtx;			//頂点情報へのポインタ
		
	if (g_bCountDownFlag == true)
	{//カウントダウンが始まっていたら
		g_nCntNumber++;
		if (g_nCntNumber % 60 == 59)
		{
			g_nCountDown--;
		}

		if (g_nCountDown == 0)
		{
			g_bCountDownFlag = false;
			SetTurnState(TURNSTATE_MOVEandATTACK);
		}

	}
	//頂点情報の更新
	g_pVtxBuffCountDown->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(1.0f, (g_nCountDown - 1) * 0.25f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, (g_nCountDown - 1) * 0.25f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, (g_nCountDown - 1) * 0.25f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, (g_nCountDown - 1) * 0.25f, 0.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2((g_nCountDown) * 0.2f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_nCountDown + 1) * 0.2f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((g_nCountDown) * 0.2f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2((g_nCountDown + 1) * 0.2f, 0.5f);


	g_pVtxBuffCountDown->Unlock();

}

//=============================================================================
//	描画処理
//=============================================================================
void DrawCountDown(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//描画
	if (g_bCountDownFlag == true)
	{
		pDevice->SetStreamSource(0, g_pVtxBuffCountDown, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

		pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

		for (int nCntCountDown = 0; nCntCountDown < MAX_POLYGON_METER; nCntCountDown++)
		{
			pDevice->SetTexture(0, g_pTextureCountDown);//テクスチャの設定

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
				4 * nCntCountDown,									   //開始する頂点のインデックス(基本０)
				2);		   							   //プリミティブの数
		}

	}

}

//=============================================================================
//	頂点の設定
//=============================================================================
void MakeVertexCountDown(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCountDown,
		NULL);

	//頂点情報の初期設定
	g_pVtxBuffCountDown->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(520.0f, 200.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(720.0f, 200.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(520.0f, 400.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(720.0f, 400.0f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
	

	g_pVtxBuffCountDown->Unlock();

}
//=============================================================================
//	カウントダウンの設定処理
//=============================================================================
void SetCountDown(void)
{
	g_nCountDown = 3;
	g_nCntNumber = 0;
	g_bCountDownFlag = true;
}