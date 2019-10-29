//=============================================================================
//
// フレームの処理 [frame.cpp]
// Author :　Jukiya Hayakawa
//
//=============================================================================
#include "frame.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FRAME_TEXTURE_NAME0	"data\\TEXTURE\\rankframe.png"		// テクスチャ名
#define	FRAME_SIZE_X			(160)								// 大きさ
#define	FRAME_SIZE_Y			(160)								// 大きさ
#define	MAX_FRAME			(1)									//ランクの最大数

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureFrame = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;					// 頂点バッファへのポインタ
FRAME g_aFrame;													// ランクの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFrame;

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// デバイスの取得
	pDevice = GetDevice();

	// 情報の初期化
	g_aFrame.pos = D3DXVECTOR3(1175.0f, 650.0f, 0.0f);	//位置の初期化
	g_aFrame.bUse = true;								//使用状態にする

														// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, FRAME_TEXTURE_NAME0, &g_apTextureFrame);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FRAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFrame,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aFrame.pos.x - FRAME_SIZE_X, g_aFrame.pos.y - FRAME_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aFrame.pos.x + FRAME_SIZE_X, g_aFrame.pos.y - FRAME_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aFrame.pos.x - FRAME_SIZE_X, g_aFrame.pos.y + FRAME_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aFrame.pos.x + FRAME_SIZE_X, g_aFrame.pos.y + FRAME_SIZE_Y, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		break;

		pVtx += 4;	// 頂点データを４つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffFrame->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFrame(void)
{

	// テクスチャの開放
	if (g_apTextureFrame != NULL)
	{
		g_apTextureFrame->Release();
		g_apTextureFrame = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffFrame != NULL)
	{
		g_pVtxBuffFrame->Release();
		g_pVtxBuffFrame = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFrame(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		if (g_aFrame.bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureFrame);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntFrame,
				2);
		}
	}
}