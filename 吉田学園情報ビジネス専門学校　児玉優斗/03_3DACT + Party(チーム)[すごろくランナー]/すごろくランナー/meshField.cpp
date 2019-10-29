//=============================================================================
//
// メッシュフィールドの処理 [meshField.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "meshField.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME	"data\\TEXTURE\\grass.jpg"	// 地面のテクスチャ名
#define MESHFIELD_SIZE_X		(40000.0f)						// 地面大きさ
#define MESHFIELD_SIZE_Z		(40000.0f)						// 地面大きさ
#define POLYGON_X				(2)								// ポリゴンの数（X）
#define POLYGON_Z				(2)								// ポリゴンの数（Z）

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffMeshField = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9		g_pTextureMeshField = NULL;	// テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffMeshField = NULL;	// インデックスバッファへのポインタ
D3DXMATRIX				g_mtxWorldMeshField;		// ワールドマトリックス
MESHFIELD				g_meshField;
int						g_nNumVerTexMeshField;		// 頂点数
int						g_nNumIndexMeshField;		// インデックス数
int						g_nNumPolygonMeshField;		// ポリゴン数

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

												// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &g_pTextureMeshField);

	// 頂点情報の作成
	MakeVertexMeshField(pDevice);

	// ポリゴンの情報を設定
	g_meshField.pos = D3DXVECTOR3(0.0f, -500.0f, 13000.0f);
	g_meshField.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshField.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	// テクスチャの破棄
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// インデックスバッファの開放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

									// デバイスの取得
	pDevice = GetDevice();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshField.rot.y, g_meshField.rot.x, g_meshField.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_meshField.pos.x, g_meshField.pos.y, g_meshField.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nNumVerTexMeshField, 0, g_nNumPolygonMeshField);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	int nVtxCounter = 0;
	int nIdxCounter = 0;

	int nCntVtxZ;
	int nCntVtxX;
	int nCntIdxZ;
	int nCntIdxX;

	// 頂点数
	g_nNumVerTexMeshField = (POLYGON_X + 1) * (POLYGON_Z + 1);

	// インデックス数
	g_nNumIndexMeshField = (POLYGON_X + 1) * (POLYGON_Z + 1)
		+ (2 * (POLYGON_Z - 1))
		+ (POLYGON_X + 1) * (POLYGON_Z - 1);

	// ポリゴン数
	g_nNumPolygonMeshField = g_nNumIndexMeshField - 2;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nNumVerTexMeshField,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nNumIndexMeshField,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,						// 16ビットのデータを確保
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

						// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntVtxZ = 0; nCntVtxZ < POLYGON_Z + 1; nCntVtxZ++)
	{
		for (nCntVtxX = 0; nCntVtxX < POLYGON_X + 1; nCntVtxX++)
		{
			// 頂点座標の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].pos = D3DXVECTOR3(-MESHFIELD_SIZE_X + (nCntVtxX * MESHFIELD_SIZE_X), 0.0f, MESHFIELD_SIZE_Z - (nCntVtxZ * MESHFIELD_SIZE_Z));
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
	g_pVtxBuffMeshField->Unlock();

	WORD *pIdx;	// インデックスデータへのポインタ

				// インデックスバッファをロックし、インデックスデータへのポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffMeshField->Unlock();
}