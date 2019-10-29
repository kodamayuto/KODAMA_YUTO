//=============================================================================
//
// 軌道の処理 [meshOrbit.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "orbit.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ORBIT_TEXTURE_NAME   "data/TEXTURE/COMMON/gradation000.jpg" // 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexOrbit(LPDIRECT3DDEVICE9 pDevice, int nIdxOrbit);
void MakeIndexOrbit(LPDIRECT3DDEVICE9 pDevice, int nIdxOrbit);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureOrbit[MAX_ORBIT] = {};  // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOrbit[MAX_ORBIT] = {};  // 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9  g_pIdxBuffOrbit[MAX_ORBIT] = {};  // インデックスバッファへのポインタ
Orbit                   g_Orbit[MAX_ORBIT];               // 軌道の情報

														  //=============================================================================
														  // 初期化処理
														  //=============================================================================
void InitOrbit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();   // デバイスの取得

	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{// 軌道の数だけ繰り返し
		g_Orbit[nCntOrbit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 座標を初期化
		g_Orbit[nCntOrbit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 向きを初期化

		g_Orbit[nCntOrbit].XBlock = ORBIT_BLOCK;        // 横の分割数を設定
		g_Orbit[nCntOrbit].YBlock = 1;                  // 縦の分割数を設定
		g_Orbit[nCntOrbit].nNumVertex = (g_Orbit[nCntOrbit].XBlock + 1) * (g_Orbit[nCntOrbit].YBlock + 1); // 頂点数を設定
		g_Orbit[nCntOrbit].nNumIndex = ((g_Orbit[nCntOrbit].XBlock + 1) * (g_Orbit[nCntOrbit].YBlock + 1)) + (2 * (g_Orbit[nCntOrbit].YBlock - 1)) + (g_Orbit[nCntOrbit].XBlock + 1) * (g_Orbit[nCntOrbit].YBlock - 1) - (g_Orbit[nCntOrbit].YBlock - 1);  // インデックス数を設定
		g_Orbit[nCntOrbit].nNumPolygon = ((g_Orbit[nCntOrbit].XBlock * g_Orbit[nCntOrbit].YBlock) * 2) + ((g_Orbit[nCntOrbit].YBlock - 1) * 4);  // 描画するポリゴン数を設定

		for (int nCntOrbit = 0; nCntOrbit < g_Orbit[nCntOrbit].XBlock + 1; nCntOrbit++)
		{// 横の分割数だけ繰り返し
			g_Orbit[nCntOrbit].orbit[nCntOrbit].posUp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Orbit[nCntOrbit].orbit[nCntOrbit].posoldUp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Orbit[nCntOrbit].orbit[nCntOrbit].posDown = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Orbit[nCntOrbit].orbit[nCntOrbit].posoldDown = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Orbit[nCntOrbit].orbit[nCntOrbit].colUp = D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f);
			g_Orbit[nCntOrbit].orbit[nCntOrbit].colDown = D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f);
			g_Orbit[nCntOrbit].orbit[nCntOrbit].radius = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			ORBIT_TEXTURE_NAME,
			&g_pTextureOrbit[nCntOrbit]);

		// 頂点情報の作成
		MakeVertexOrbit(pDevice, nCntOrbit);

		// インデックス情報の作成
		MakeIndexOrbit(pDevice, nCntOrbit);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitOrbit(void)
{
	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{// 軌道の数だけ繰り返し
	 // テクスチャの開放
		if (g_pTextureOrbit[nCntOrbit] != NULL)
		{
			g_pTextureOrbit[nCntOrbit]->Release();
			g_pTextureOrbit[nCntOrbit] = NULL;
		}

		// 頂点バッファの開放
		if (g_pVtxBuffOrbit[nCntOrbit] != NULL)
		{
			g_pVtxBuffOrbit[nCntOrbit]->Release();
			g_pVtxBuffOrbit[nCntOrbit] = NULL;
		}

		// インデックスバッファの開放
		if (g_pIdxBuffOrbit[nCntOrbit] != NULL)
		{
			g_pIdxBuffOrbit[nCntOrbit]->Release();
			g_pIdxBuffOrbit[nCntOrbit] = NULL;
		}
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateOrbit(void)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;

	for (int nCntOrbit1 = 0; nCntOrbit1 < MAX_ORBIT; nCntOrbit1++)
	{// 軌道の数だけ繰り返し
	 // 頂点バッファをロックし,頂点データへのポインタを取得
		g_pVtxBuffOrbit[nCntOrbit1]->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntOrbit = 1; nCntOrbit < g_Orbit[nCntOrbit1].XBlock + 1; nCntOrbit++)
		{// 設定しない頂点の分だけ繰り返し
		 // 前回の位置保存
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].posoldUp = g_Orbit[nCntOrbit1].orbit[nCntOrbit].posUp;
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].posoldDown = g_Orbit[nCntOrbit1].orbit[nCntOrbit].posDown;

			// 現在の座標をずらす
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].posUp = g_Orbit[nCntOrbit1].orbit[nCntOrbit - 1].posoldUp;
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].posDown = g_Orbit[nCntOrbit1].orbit[nCntOrbit - 1].posoldDown;

			// 頂点座標の更新
			pVtx[nCntOrbit].pos = D3DXVECTOR3(g_Orbit[nCntOrbit1].orbit[nCntOrbit].posUp.x, g_Orbit[nCntOrbit1].orbit[nCntOrbit].posUp.y, g_Orbit[nCntOrbit1].orbit[nCntOrbit].posUp.z);
			pVtx[nCntOrbit + g_Orbit[nCntOrbit1].XBlock + 1].pos = D3DXVECTOR3(g_Orbit[nCntOrbit1].orbit[nCntOrbit].posDown.x, g_Orbit[nCntOrbit1].orbit[nCntOrbit].posDown.y, g_Orbit[nCntOrbit1].orbit[nCntOrbit].posDown.z);

			// 色を移す
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].colUp = g_Orbit[nCntOrbit1].orbit[nCntOrbit - 1].colUp;
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].colDown = g_Orbit[nCntOrbit1].orbit[nCntOrbit - 1].colDown;

			// 透明度を減らす
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].colUp.a -= 0.02f;
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].colDown.a -= 0.02f;

			// 頂点カラーの更新
			pVtx[nCntOrbit].col = g_Orbit[nCntOrbit1].orbit[nCntOrbit].colUp;
			pVtx[nCntOrbit + g_Orbit[nCntOrbit1].XBlock + 1].col = g_Orbit[nCntOrbit1].orbit[nCntOrbit].colDown;
		}
		// 頂点バッファをアンロックする
		g_pVtxBuffOrbit[nCntOrbit1]->Unlock();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawOrbit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;                // 計算用マトリックス

												// カリングの設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// カリングしない

															// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{// 軌道の総数分繰り返し
	 // ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Orbit[nCntOrbit].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Orbit[nCntOrbit].rot.y, g_Orbit[nCntOrbit].rot.x, g_Orbit[nCntOrbit].rot.z);
		D3DXMatrixMultiply(&g_Orbit[nCntOrbit].mtxWorld, &g_Orbit[nCntOrbit].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Orbit[nCntOrbit].pos.x, g_Orbit[nCntOrbit].pos.y, g_Orbit[nCntOrbit].pos.z);
		D3DXMatrixMultiply(&g_Orbit[nCntOrbit].mtxWorld, &g_Orbit[nCntOrbit].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Orbit[nCntOrbit].mtxWorld);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pVtxBuffOrbit[nCntOrbit], 0, sizeof(VERTEX_3D));

		// インデックスバッファをデバイスのデータストリームにバインド
		pDevice->SetIndices(g_pIdxBuffOrbit[nCntOrbit]);

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

#if 1
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureOrbit[nCntOrbit]);
#endif

		// ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_Orbit[nCntOrbit].nNumVertex, 0, g_Orbit[nCntOrbit].nNumPolygon);
	}

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// カリングの設定を戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	// 裏面をカリング
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexOrbit(LPDIRECT3DDEVICE9 pDevice, int nIdxOrbit)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_Orbit[nIdxOrbit].nNumVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOrbit[nIdxOrbit],
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffOrbit[nIdxOrbit]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < g_Orbit[nIdxOrbit].YBlock + 1; nCntV++)
	{// 縦の分割数分繰り返し
		for (int nCntH = 0; nCntH < g_Orbit[nIdxOrbit].XBlock + 1; nCntH++)
		{// 横の分割数分繰り返し
		 // 頂点座標
			pVtx[nCntH].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 法線
			pVtx[nCntH].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);

			// 頂点カラー
			pVtx[nCntH].col = g_Orbit[nIdxOrbit].orbit[nCntH].colUp;

			// テクスチャ座標
			pVtx[nCntH].tex = D3DXVECTOR2(nCntH * (1.0f / g_Orbit[nIdxOrbit].XBlock), nCntV * (1.0f / g_Orbit[nIdxOrbit].YBlock));
		}
		pVtx += g_Orbit[nIdxOrbit].XBlock + 1; // 横の分割数分ポインタを進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffOrbit[nIdxOrbit]->Unlock();
}
//=============================================================================
// インデックス情報の作成
//=============================================================================
void MakeIndexOrbit(LPDIRECT3DDEVICE9 pDevice, int nIdxOrbit)
{
	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_Orbit[nIdxOrbit].nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffOrbit[nIdxOrbit],
		NULL);

	WORD *pIdx;      // インデックスデータへのポインタ
	int nCntIdx = 0; // インデックス番号

					 // インデックスバッファをロックし,インデックスデータへのポインタを取得
	g_pIdxBuffOrbit[nIdxOrbit]->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxY = 0; nCntIdxY < g_Orbit[nIdxOrbit].YBlock; nCntIdxY++)
	{// 縦の分割数分繰り返し
		for (int nCntIdxX = 0; nCntIdxX < g_Orbit[nIdxOrbit].XBlock + 1; nCntIdxX++, nCntIdx++)
		{// 横の分割数+１繰り返し
		 // 上下の二つ分インデックス番号を設定
			pIdx[0] = nCntIdx + g_Orbit[nIdxOrbit].XBlock + 1; // 下側
			pIdx[1] = nCntIdx;                      // 上側

			pIdx += 2;  // 2つ分進める
			if (nCntIdxY < g_Orbit[nIdxOrbit].YBlock && nCntIdxX > g_Orbit[nIdxOrbit].XBlock)
			{// 1 , 下側が縦の分割数の最下層ではない
			 // 2 , 横の分割数分設定が終わった
				pIdx[0] = nCntIdx;                            // 上側
				pIdx[1] = nCntIdx + (g_Orbit[nIdxOrbit].XBlock + 1) + 1; // 次の下側

				pIdx += 2; // 2つ分進める
			}
		}
	}

	// インデックスバッファをアンロックする
	g_pIdxBuffOrbit[nIdxOrbit]->Unlock();
}
//=============================================================================
// 軌道の設定
//=============================================================================
void SetOrbit(D3DXVECTOR3 mtx1, D3DXVECTOR3 mtx2, D3DXCOLOR colUp, D3DXCOLOR colDown, int nIdxOrbit)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffOrbit[nIdxOrbit]->Lock(0, 0, (void**)&pVtx, 0);

	// 左端の頂点座標を設定
	pVtx[0].pos = D3DXVECTOR3(mtx1.x, mtx1.y, mtx1.z);
	pVtx[g_Orbit[nIdxOrbit].XBlock + 1].pos = D3DXVECTOR3(mtx2.x, mtx2.y, mtx2.z);

	// 頂点カラー
	pVtx[0].col = colUp;
	pVtx[g_Orbit[nIdxOrbit].XBlock + 1].col = colDown;

	// 頂点バッファをアンロックする
	g_pVtxBuffOrbit[nIdxOrbit]->Unlock();

	// 座標を保存
	g_Orbit[nIdxOrbit].orbit[0].posUp = mtx1;
	g_Orbit[nIdxOrbit].orbit[0].posoldUp = mtx1;

	g_Orbit[nIdxOrbit].orbit[0].posDown = mtx2;
	g_Orbit[nIdxOrbit].orbit[0].posoldDown = mtx2;

	// 色を設定
	g_Orbit[nIdxOrbit].orbit[0].colUp = colUp;
	g_Orbit[nIdxOrbit].orbit[0].colDown = colDown;

}
//=============================================================================
// 軌道の座標設定
//=============================================================================
void SetPosiotionOrbit(D3DXVECTOR3 mtx1, D3DXVECTOR3 mtx2, int nIdxOrbit)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffOrbit[nIdxOrbit]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntOrbit = 0; nCntOrbit < g_Orbit[nIdxOrbit].XBlock + 1; nCntOrbit++)
	{// 設定しない頂点の分だけ繰り返し
	 // 頂点座標を設定
		pVtx[nCntOrbit].pos = D3DXVECTOR3(mtx1.x, mtx1.y, mtx1.z);
		pVtx[nCntOrbit + g_Orbit[nIdxOrbit].XBlock + 1].pos = D3DXVECTOR3(mtx2.x, mtx2.y, mtx2.z);
		g_Orbit[nIdxOrbit].orbit[nCntOrbit].posUp = mtx1;
		g_Orbit[nIdxOrbit].orbit[nCntOrbit].posoldUp = mtx1;
		g_Orbit[nIdxOrbit].orbit[nCntOrbit].posDown = mtx2;
		g_Orbit[nIdxOrbit].orbit[nCntOrbit].posoldDown = mtx2;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffOrbit[nIdxOrbit]->Unlock();
}