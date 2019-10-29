//=============================================================================
//
// 草の処理 [leaf.cpp]
// Author :Jukiya Hayakawa
//
//=============================================================================
#include "leaf.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_LEAF			(256)								// 弾の最大数
#define POLYGON_X			(1200)								// ポリゴンのX座標
#define POLYGON_Y			(350)								// ポリゴンのY座標
#define LEAF_TEXTURENAME	"data\\TEXTURE\\leaf.png"			// テクスチャ名
#define LEAF_SIZE			(500.0f)							    // 弾の大きさ
#define LEAF_HIT			(30)								// 当たり判定

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLeaf = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLeaf = NULL;	// 頂点バッファへのポインタ
Leaf g_aLeaf[MAX_LEAF];						// 使用しているかどうか

//=============================================================================
// 初期化処理
//=============================================================================
void InitLeaf(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntLeaf;

	// デバイスの取得
	pDevice = GetDevice();

	//// ポリゴン座標の設定
	//g_aLeaf[0].pos = D3DXVECTOR3(POLYGON_X, POLYGON_Y, 0.0f);
	//g_aLeaf[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 草の情報の初期化
	for (nCntLeaf = 0; nCntLeaf < MAX_LEAF; nCntLeaf++)
	{
		g_aLeaf[nCntLeaf].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLeaf[nCntLeaf].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLeaf[nCntLeaf].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, LEAF_TEXTURENAME, &g_pTextureLeaf);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LEAF,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffLeaf,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

						// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLeaf->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLeaf = 0; nCntLeaf < MAX_LEAF; nCntLeaf++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x - LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y - LEAF_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x + LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y - LEAF_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x - LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y + LEAF_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x + LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y + LEAF_SIZE, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	// 頂点データを４つ分進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffLeaf->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLeaf(void)
{
	// テクスチャの開放
	if (g_pTextureLeaf != NULL)
	{
		g_pTextureLeaf->Release();
		g_pTextureLeaf = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffLeaf != NULL)
	{
		g_pVtxBuffLeaf->Release();
		g_pVtxBuffLeaf = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLeaf(void)
{
	int nCntLeaf;

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLeaf->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLeaf = 0; nCntLeaf < MAX_LEAF; nCntLeaf++)
	{
		if (g_aLeaf[nCntLeaf].bUse == true)	// 使用されている
		{
					g_aLeaf[nCntLeaf].pos += g_aLeaf[nCntLeaf].move;
	
			// 頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x - LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y - LEAF_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x + LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y - LEAF_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x - LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y + LEAF_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x + LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y + LEAF_SIZE, 0.0f);

		}

		pVtx += 4;	// 該当の位置まで進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffLeaf->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLeaf(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntLeaf;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffLeaf, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLeaf);

	// ポリゴンの描画
	for (nCntLeaf = 0; nCntLeaf < MAX_LEAF; nCntLeaf++)
	{
		if (g_aLeaf[nCntLeaf].bUse == true)	// 弾が使用されている
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntLeaf,
				2);
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetLeaf(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	for (int nCntLeaf = 0; nCntLeaf < MAX_LEAF; nCntLeaf++)
	{//壁の数だけ繰り返し
		if (g_aLeaf[nCntLeaf].bUse == false)
		{//壁を使用していない場合
			g_aLeaf[nCntLeaf].pos = pos;
			g_aLeaf[nCntLeaf].move = move;
			g_aLeaf[nCntLeaf].bUse = true;

			break;
		}
	}
}