//=============================================================================
//
// 海の床の処理 [ocean.cpp]
// Author : Miyu Takahashi
//
//=============================================================================
#include "ocean.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OCEAN_TEXTURE_NAME	"data\\TEXTURE\\ocean000.jpg"	// 地面のテクスチャ名
#define OCEAN_SIZE_X		(40000.0f)						// 地面大きさ
#define OCEAN_SIZE_Z		(40000.0f)						// 地面大きさ
#define POLYGON_X			(3)								// ポリゴンの数（X）
#define POLYGON_Z			(3)								// ポリゴンの数（Z）

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexOcean(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffOcean = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9		g_pTextureOcean = NULL;	// テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffOcean = NULL;	// インデックスバッファへのポインタ
D3DXMATRIX				g_mtxWorldOcean;		// ワールドマトリックス
OCEAN					g_ocean;
int						g_nNumVerTexOcean;		// 頂点数
int						g_nNumIndexOcean;		// インデックス数
int						g_nNumPolygonOcean;		// ポリゴン数

//=============================================================================
// 初期化処理
//=============================================================================
void InitOcean(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, OCEAN_TEXTURE_NAME, &g_pTextureOcean);

	// 頂点情報の作成
	MakeVertexOcean(pDevice);

	// ポリゴンの情報を設定
	g_ocean.pos = D3DXVECTOR3(0.0f, 25.0f, 13000.0f);
	g_ocean.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_ocean.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitOcean(void)
{
	// テクスチャの破棄
	if (g_pTextureOcean != NULL)
	{
		g_pTextureOcean->Release();
		g_pTextureOcean = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffOcean != NULL)
	{
		g_pVtxBuffOcean->Release();
		g_pVtxBuffOcean = NULL;
	}

	// インデックスバッファの開放
	if (g_pIdxBuffOcean != NULL)
	{
		g_pIdxBuffOcean->Release();
		g_pIdxBuffOcean = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateOcean(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawOcean(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// デバイスの取得
	pDevice = GetDevice();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldOcean);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ocean.rot.y, g_ocean.rot.x, g_ocean.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldOcean, &g_mtxWorldOcean, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_ocean.pos.x, g_ocean.pos.y, g_ocean.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldOcean, &g_mtxWorldOcean, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldOcean);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffOcean, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffOcean);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureOcean);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nNumVerTexOcean, 0, g_nNumPolygonOcean);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexOcean(LPDIRECT3DDEVICE9 pDevice)
{
	int nVtxCounter = 0;
	int nIdxCounter = 0;

	int nCntVtxZ;
	int nCntVtxX;
	int nCntIdxZ;
	int nCntIdxX;

	// 頂点数
	g_nNumVerTexOcean = (POLYGON_X + 1) * (POLYGON_Z + 1);

	// インデックス数
	g_nNumIndexOcean = (POLYGON_X + 1) * (POLYGON_Z + 1)
		+ (2 * (POLYGON_Z - 1))
		+ (POLYGON_X + 1) * (POLYGON_Z - 1);

	// ポリゴン数
	g_nNumPolygonOcean = g_nNumIndexOcean - 2;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nNumVerTexOcean,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOcean,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nNumIndexOcean,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,						// 16ビットのデータを確保
		D3DPOOL_MANAGED,
		&g_pIdxBuffOcean,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffOcean->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntVtxZ = 0; nCntVtxZ < POLYGON_Z + 1; nCntVtxZ++)
	{
		for (nCntVtxX = 0; nCntVtxX < POLYGON_X + 1; nCntVtxX++)
		{
			// 頂点座標の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].pos = D3DXVECTOR3(-OCEAN_SIZE_X + (nCntVtxX * OCEAN_SIZE_X), 0.0f, OCEAN_SIZE_Z - (nCntVtxZ * OCEAN_SIZE_Z));
			// 法線の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// 頂点カラーの設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// テクスチャ座標の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].tex = D3DXVECTOR2(0.0f + (nCntVtxX * (10.0f / POLYGON_X)), 0.0f + (nCntVtxZ * (50.0f / POLYGON_Z)));
		}
		nVtxCounter += POLYGON_X;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffOcean->Unlock();

	WORD *pIdx;	// インデックスデータへのポインタ

	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	g_pIdxBuffOcean->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntIdxZ = 0; nCntIdxZ < POLYGON_Z; nCntIdxZ++)
	{
		for (nCntIdxX = 0; nCntIdxX < POLYGON_X + 1; nCntIdxX++, nIdxCounter++)
		{
			pIdx[0] = nIdxCounter + POLYGON_X + 1;
			pIdx[1] = nIdxCounter;
			pIdx += 2;

			if (nCntIdxZ < POLYGON_Z - 1 && nCntIdxX == POLYGON_X)
			{
				pIdx[0] = nIdxCounter;
				pIdx[1] = nIdxCounter + (POLYGON_X + 1) + 1;
				pIdx += 2;
			}
		}
	}

	// インデックスの設定
	/*pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;*/	/*ださっ*/

	// インデックスバッファをアンロック
	g_pIdxBuffOcean->Unlock();
}