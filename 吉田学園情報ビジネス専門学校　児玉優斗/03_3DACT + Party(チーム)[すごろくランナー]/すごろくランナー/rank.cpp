//=============================================================================
//
// ランク処理 [rank.cpp]
// Author :　Jukiya Hayakawa
//
//=============================================================================
#include "rank.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RANK_TEXTURE_NAME0	"data\\TEXTURE\\rank.png"		// テクスチャ名
#define	RANK_SIZE			(130)							// 大きさ
#define	MAX_RANK			(2)								//ランクの最大数

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureRank = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;				// 頂点バッファへのポインタ
RANK g_aRank;												// ランクの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitRank(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank;

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// デバイスの取得
	pDevice = GetDevice();

	// 情報の初期化
	g_aRank.pos = D3DXVECTOR3(1165.0f, 635.0f, 0.0f);	//位置の初期化
	g_aRank.rank = RANK_1;								//ランクの初期化
	g_aRank.bUse = true;								//使用状態にする

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, RANK_TEXTURE_NAME0, &g_apTextureRank);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aRank.pos.x - RANK_SIZE, g_aRank.pos.y - RANK_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aRank.pos.x + RANK_SIZE, g_aRank.pos.y - RANK_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aRank.pos.x - RANK_SIZE, g_aRank.pos.y + RANK_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aRank.pos.x + RANK_SIZE, g_aRank.pos.y + RANK_SIZE, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
		break;

		pVtx += 4;	// 頂点データを４つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffRank->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRank(void)
{

	// テクスチャの開放
	if (g_apTextureRank != NULL)
	{
		g_apTextureRank->Release();
		g_apTextureRank = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRank(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawRank(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		if (g_aRank.bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureRank);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntRank,
				2);
		}
	}
}

//=============================================================================
// ランクの設定
//=============================================================================
void SetRank(PLAYER_RANK rank)
{
	int nCntRank;

	g_aRank.rank = rank;

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//ランクの数だけ繰り返し
		VERTEX_2D *pVtx;	// 頂点情報へのポインタ

		// 頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntRank * 4);	// 該当の位置まで進める

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aRank.pos.x - RANK_SIZE, g_aRank.pos.y - RANK_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aRank.pos.x + RANK_SIZE, g_aRank.pos.y - RANK_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aRank.pos.x - RANK_SIZE, g_aRank.pos.y + RANK_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aRank.pos.x + RANK_SIZE, g_aRank.pos.y + RANK_SIZE, 0.0f);

		switch (g_aRank.rank)
		{
		case RANK_1:
			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
			break;

		case RANK_2:
			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;
		}
		// 頂点バッファをアンロック
		g_pVtxBuffRank->Unlock();
		break;
	}
}

//=============================================================================
// ランクの取得
//=============================================================================
RANK *GetRank(void)
{
	return &g_aRank;
}
