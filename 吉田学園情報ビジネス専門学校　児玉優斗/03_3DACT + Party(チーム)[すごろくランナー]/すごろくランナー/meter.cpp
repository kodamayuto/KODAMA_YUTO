//=============================================================================
//
// タイマー処理 [timer.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "meter.h"
#include "game.h"
#include "timer.h"

//=============================================================================
//	プロトタイプ宣言
//=============================================================================
void MakeVertexMeter(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeter = NULL;					//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeter[MAX_POLYGON_METER] = {};						//テクスチャへのポインタ

int g_nCntMeter;			//メーターの減少カウント
float g_fMeterSize;			//メーターの長さ

							//=============================================================================
							//	初期化処理
							//=============================================================================
void InitMeter(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//変数初期化
	g_nCntMeter = 0;
	g_fMeterSize = METER_SIZE_MAX;

	D3DXCreateTextureFromFile(pDevice, METER_TEXTURE_FIRENAME0, &g_pTextureMeter[0]);
	D3DXCreateTextureFromFile(pDevice, METER_TEXTURE_FIRENAME, &g_pTextureMeter[1]);

	//頂点情報の設定
	MakeVertexMeter(pDevice);
}

//=============================================================================
//	終了処理
//=============================================================================
void UninitMeter(void)
{
	//テクスチャの破棄
	for (int nCntMeter = 0; nCntMeter < MAX_POLYGON_METER; nCntMeter++)
	{

		if (g_pTextureMeter[nCntMeter] != NULL)
		{
			g_pTextureMeter[nCntMeter]->Release();
			g_pTextureMeter[nCntMeter] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffMeter != NULL)
	{
		g_pVtxBuffMeter->Release();
		g_pVtxBuffMeter = NULL;
	}

}

//=============================================================================
//	更新処理
//=============================================================================
void UpdateMeter(void)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ
	TURNSTATE pTstate;
	pTstate = GetTurnState();
	if (GetTimer() != -1 && GetSetTimerFlag() == true && pTstate == TURNSTATE_MOVEandATTACK)
	{//タイマーが動いているときだけメーターを動かす
		g_nCntMeter++;

		if (g_nCntMeter % 30 == 29 && g_fMeterSize >= METER_SIZE_MIN)
		{
			g_fMeterSize -= METER_MOVE;
		}
	}
	else
	{
		g_nCntMeter = 0;
	}

	//頂点情報の更新
	g_pVtxBuffMeter->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(METER_SIZE_MIN, 5.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_fMeterSize, 5.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(METER_SIZE_MIN, 100.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_fMeterSize, 100.0f, 0.0f);

	if (g_fMeterSize > (METER_SIZE_MAX + METER_SIZE_MIN) / 2)
	{

		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.8f);
	}
	else if (g_fMeterSize - METER_SIZE_MIN < (METER_SIZE_MAX - METER_SIZE_MIN) / 4)
	{
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);

	}
	else
	{

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f);

	}
	g_pVtxBuffMeter->Unlock();
}

//=============================================================================
//	描画処理
//=============================================================================
void DrawMeter(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//描画

	pDevice->SetStreamSource(0, g_pVtxBuffMeter, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

	pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

	for (int nCntMeter = 0; nCntMeter < MAX_POLYGON_METER; nCntMeter++)
	{
		pDevice->SetTexture(0, g_pTextureMeter[nCntMeter]);//テクスチャの設定

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
			4 * nCntMeter,									   //開始する頂点のインデックス(基本０)
			2);		   							   //プリミティブの数

	}

}

//=============================================================================
//	頂点の設定
//=============================================================================
void MakeVertexMeter(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

									//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON_METER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeter,
		NULL);

	//頂点情報の初期設定
	g_pVtxBuffMeter->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(400.0f, 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(500.0f, 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(400.0f, 200.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(500.0f, 200.0f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx += 4;

	pVtx[0].pos = D3DXVECTOR3(METER_SIZE_MIN - 20.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_fMeterSize + 20.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(METER_SIZE_MIN - 20.0f, 110.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_fMeterSize + 20.0f, 110.0f, 0.0f);

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


	g_pVtxBuffMeter->Unlock();

}
//=============================================================================
//	メーターサイズの取得
//=============================================================================
float GetMeterSize(void)
{
	return g_fMeterSize - METER_SIZE_MIN;
}