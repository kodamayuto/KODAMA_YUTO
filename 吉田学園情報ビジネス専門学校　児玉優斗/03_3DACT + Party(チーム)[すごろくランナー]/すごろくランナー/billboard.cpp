//=============================================================================
//
// ビルボードの処理 [billboard.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "billboard.h"
#include "shadow.h"
#include "wall.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BILLBOARD_TEXTURE_NAME   "data/TEXTURE/ivy000.png"          // 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureBillboard = NULL;  // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;  // 頂点バッファへのポインタ
Billboard               g_aBillboard[MAX_BILLBOARD]; // ビルボードの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// 頂点情報の作成
	MakeVertexBillboard(pDevice);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{// ビルボードの総数分繰り返し
		g_aBillboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 位置を初期化
		g_aBillboard[nCntBillboard].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // 移動量を初期化
		g_aBillboard[nCntBillboard].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 向きを初期化
		g_aBillboard[nCntBillboard].fWidth = 0.0f;                          // 幅を初期化
		g_aBillboard[nCntBillboard].fHeight = 0.0f;                         // 高さを初期化
		g_aBillboard[nCntBillboard].bUse = false;                           // 使用していない状態にする
		g_aBillboard[nCntBillboard].nIdxShadow = 0;                         // 影の番号を初期化
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBillboard(void)
{
	// テクスチャの開放
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBillboard(void)
{
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{// ビルボードの総数分繰り返し
		if (g_aBillboard[nCntBillboard].bUse == true)
		{// ビルボードが使用されている
			SetPositionShadow(g_aBillboard[nCntBillboard].nIdxShadow, D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x, 0.0f, g_aBillboard[nCntBillboard].pos.z));
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	// カリングしないようにする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);    // 有効に
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);              // 透明度が0
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER); // より大きいものを描画する

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{// ビルボードの総数分繰り返し
		if (g_aBillboard[nCntBillboard].bUse == true)
		{// ビルボードが使用されている
		    // ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBillboard[nCntBillboard].rot.y, g_aBillboard[nCntBillboard].rot.x, g_aBillboard[nCntBillboard].rot.z);
			D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBillboard);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, NUM_POLYGON);
		}
	}

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// カリングの設定を戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		BILLBOARD_TEXTURE_NAME,
		&g_pTextureBillboard);

	// 頂点情報の設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{// ビルボードの総数分繰り返し
	    // 頂点座標
		pVtx[0].pos = D3DXVECTOR3(-g_aBillboard[nCntBillboard].fWidth, g_aBillboard[nCntBillboard].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].fWidth, g_aBillboard[nCntBillboard].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aBillboard[nCntBillboard].fWidth, -g_aBillboard[nCntBillboard].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].fWidth, -g_aBillboard[nCntBillboard].fHeight, 0.0f);

		// 法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		pVtx[1].nor = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		pVtx[2].nor = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		pVtx[3].nor = D3DXVECTOR3(0.22f, -0.87f, 0.44f);

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;   // ポインタを進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();
}
//=============================================================================
// ビルボードの設定
//=============================================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, float width, float height)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{// ビルボードの総数分繰り返し
		if (g_aBillboard[nCntBillboard].bUse == false)
		{// ビルボードが使用されていない
			g_aBillboard[nCntBillboard].pos = pos;        // 位置を設定
			g_aBillboard[nCntBillboard].move = move;      // 移動量を設定
			g_aBillboard[nCntBillboard].rot = rot;        // 向きを設定
			g_aBillboard[nCntBillboard].fWidth = width;   // 幅を設定
			g_aBillboard[nCntBillboard].fHeight = height; // 高さを設定

			pVtx[0].pos = D3DXVECTOR3(-g_aBillboard[nCntBillboard].fWidth, g_aBillboard[nCntBillboard].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].fWidth, g_aBillboard[nCntBillboard].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aBillboard[nCntBillboard].fWidth, -g_aBillboard[nCntBillboard].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].fWidth, -g_aBillboard[nCntBillboard].fHeight, 0.0f);

			g_aBillboard[nCntBillboard].nIdxShadow = SetShadow(D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x, 0.0f, g_aBillboard[nCntBillboard].pos.z), g_aBillboard[nCntBillboard].rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.21f), 5, 5); // 影の番号を設定
			g_aBillboard[nCntBillboard].bUse = true;
			break;
		}
		pVtx += 4;  // ポインタを進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();
}
//=============================================================================
// ビルボードとの当たり判定
//=============================================================================
bool CollisionBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 radius)
{
	bool Col = false;  // 当たったかどうか
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{// ビルボードの総数分繰り返し
		if (g_aBillboard[nCntBillboard].bUse == true)
		{// ビルボードが使用されている
			if (pos.y + radius.y <= g_aBillboard[nCntBillboard].pos.y + g_aBillboard[nCntBillboard].fHeight
				&& pos.y + 30.0f >= g_aBillboard[nCntBillboard].pos.y - g_aBillboard[nCntBillboard].fHeight)
			{// Y座標の中にいる
				if (pos.x - radius.x <= g_aBillboard[nCntBillboard].pos.x + 5.0f
					&& pos.x + radius.x >= g_aBillboard[nCntBillboard].pos.x - 5.0f)
				{// X座標の中にいる
					if (pos.z - radius.z <= g_aBillboard[nCntBillboard].pos.z + 5.0f
						&& pos.z + radius.z >= g_aBillboard[nCntBillboard].pos.z - 5.0f)
					{// Z座標の中にいる
						Col = true;
					}
				}
			}
		
		}
	}

	return Col;
}
Billboard *GetBillboard(void)
{
	return &g_aBillboard[0];
}