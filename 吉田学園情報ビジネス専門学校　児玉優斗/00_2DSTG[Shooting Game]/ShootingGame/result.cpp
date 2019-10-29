//*****************************************************************************
//
//					DirectX タイトル処理 [result.cpp]
//					Author Kodama Yuto
//
//*****************************************************************************
//インクルードファイル
#include "result.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
//							グローバル変数宣言
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureResult[3] = {};	                    //テクスチャへのポインタ

int g_CounterEnter = 0;
bool g_bEnterDisp = false;
//-----------------------------------------------------------------------------
//						   背景の初期化処理
//-----------------------------------------------------------------------------
void InitResult(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得

	pDevice = GetDevice();
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	g_CounterEnter = 0;
	g_bEnterDisp = false;
	
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURE_LOSE, &g_pTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURE_WIN, &g_pTextureResult[1]);
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURE_ENTER, &g_pTextureResult[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);



	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);


	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);

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


	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(400, 500, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(880, 500, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(400, 600, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(880, 600, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

	PlaySound(SOUND_LABEL_BGM002);//音

}

//-----------------------------------------------------------------------------
//						   背景の終了処理
//-----------------------------------------------------------------------------
void UninitResult(void)
{
	//テクスチャの破棄
	for (int nCntData = 0; nCntData < 3; nCntData++)
	{
		if (g_pTextureResult[nCntData] != NULL)
		{
			g_pTextureResult[nCntData] ->Release();
			g_pTextureResult[nCntData] = NULL;
		}

	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//-----------------------------------------------------------------------------
//							背景の更新処理
//-----------------------------------------------------------------------------
void UpdateResult(void)
{
	FADE *pFade;
	pFade = GetFade();

	g_CounterEnter++;
	if (g_CounterEnter % 40 == 0 && g_CounterEnter >= 90 ||*pFade ==FADE_OUT && g_CounterEnter % 3 == 0)
	{
		g_bEnterDisp = g_bEnterDisp ? false : true;
	}

	//ENTERキーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{

		if (*pFade != FADE_OUT)
		{
			SetFade(MODE_RANKING);
		}
	}
}

//-----------------------------------------------------------------------------
//							背景の描画処理
//-----------------------------------------------------------------------------
void DrawResult(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	Player *pPlayer;
	BOSS *pBoss;

	//デバイスの取得
	pDevice = GetDevice();

	//描画
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

	pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

	pPlayer = GetPlayer();
	pBoss = GetBoss();
	if (pPlayer->bDisp == false)
	{
		pDevice->SetTexture(0, g_pTextureResult[0]);//テクスチャの設定
													//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
			0,					   //開始する頂点のインデックス(基本０)
			2);		   	       //プリミティブの数

	}
	else
	{
		pDevice->SetTexture(0, g_pTextureResult[1]);//テクスチャの設定
													//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
			0,					   //開始する頂点のインデックス(基本０)
			2);		   	       //プリミティブの数

	}

	if (g_bEnterDisp == true)
	{
		pDevice->SetTexture(0, g_pTextureResult[2]);//テクスチャの設定

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
			4,					   //開始する頂点のインデックス(基本０)
			2);		   	       //プリミティブの数

	}
}

