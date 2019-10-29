//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "effect.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EFFECT_TEXTURE_NAME   "data/TEXTURE/effect000.jpg"          // 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureEffect = NULL;  // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;  // 頂点バッファへのポインタ
Effect                  g_aEffect[MAX_EFFECT];    // エフェクトの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

    // 頂点情報の作成
	MakeVertexEffect(pDevice);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// エフェクトの総数分繰り返し
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 位置を初期化
		g_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 向きを初期化
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f); // 色を初期化
		g_aEffect[nCntEffect].fRadius = 0.0f;                         // 半径を初期化
		g_aEffect[nCntEffect].bUse = false;                           // 使用していない状態にする
		g_aEffect[nCntEffect].nIdxShadow = 0;                         // 影の番号を初期化
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	// テクスチャの開放
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// エフェクトの総数分繰り返し
		if (g_aEffect[nCntEffect].bUse == true)
		{// エフェクトが使用されている
			g_aEffect[nCntEffect].nLife--;          // 寿命を削る
			g_aEffect[nCntEffect].fRadius -= 0.5f;  // 半径を減らす
  			g_aEffect[nCntEffect].col.r -= 0.01f;   // 赤を減らす
			g_aEffect[nCntEffect].col.g -= 0.01f;   // 緑を減らす
			g_aEffect[nCntEffect].col.b -= 0.01f;   // 青を減らす
			g_aEffect[nCntEffect].col.a -= 0.07f;   // 透明度を減らす

			// 大きさを更新
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

			// 頂点カラーを更新
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			// 影の位置更新
			SetPositionShadow(g_aEffect[nCntEffect].nIdxShadow, D3DXVECTOR3(g_aEffect[nCntEffect].pos.x, 0.0f, g_aEffect[nCntEffect].pos.z));
			
			if (g_aEffect[nCntEffect].nLife <= 0 || g_aEffect[nCntEffect].fRadius <= 0 || g_aEffect[nCntEffect].col.a <= 0)
			{// 寿命がなくなった
				g_aEffect[nCntEffect].bUse = false;              // 使用していない状態に
				DeleteShadow(g_aEffect[nCntEffect].nIdxShadow);  // 影も消す
			}
		}
		pVtx += 4;   // ポインタを進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxView, mtxTrans;               // 計算用マトリックス

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE); // 深度バッファの書き込み設定を無効に
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);// すべて描画する

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);     // 有効に
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);               // 透明度が0
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); // より大きいものを描画する

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// エフェクトの総数分繰り返し
		if (g_aEffect[nCntEffect].bUse == true)
		{// エフェクトが使用されている
		    // ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

			// 向きをカメラの正面に設定
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_aEffect[nCntEffect].mtxWorld._11 = mtxView._11;
			g_aEffect[nCntEffect].mtxWorld._12 = mtxView._21;
			g_aEffect[nCntEffect].mtxWorld._13 = mtxView._31;
			g_aEffect[nCntEffect].mtxWorld._21 = mtxView._12;
			g_aEffect[nCntEffect].mtxWorld._22 = mtxView._22;
			g_aEffect[nCntEffect].mtxWorld._23 = mtxView._32;
			g_aEffect[nCntEffect].mtxWorld._31 = mtxView._13;
			g_aEffect[nCntEffect].mtxWorld._32 = mtxView._23;
			g_aEffect[nCntEffect].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, NUM_POLYGON);
		}
	}

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Zテストを無効にする(デフォルトの値に)
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);      // 深度バッファへの書き込みを有効に
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL); // 以下のものを描画する
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		EFFECT_TEXTURE_NAME,
		&g_pTextureEffect);

	// 頂点情報の設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect= 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// エフェクトの総数分繰り返し
	    // 頂点座標
		pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

		// 法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[1].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[2].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[3].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);

		// 頂点カラー
		pVtx[0].col = g_aEffect[nCntEffect].col;
		pVtx[1].col = g_aEffect[nCntEffect].col;
		pVtx[2].col = g_aEffect[nCntEffect].col;
		pVtx[3].col = g_aEffect[nCntEffect].col;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;   // ポインタを進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}
//=============================================================================
// エフェクトの設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float radius, int life)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// エフェクトの総数分繰り返し
		if (g_aEffect[nCntEffect].bUse == false)
		{// エフェクトが使用されていない
			g_aEffect[nCntEffect].pos = pos;          // 位置を設定
			g_aEffect[nCntEffect].rot = rot;          // 向きを設定
			g_aEffect[nCntEffect].col = col;          // 色を設定
			g_aEffect[nCntEffect].fRadius = radius;   // 半径を設定
			g_aEffect[nCntEffect].nLife = life;       // 寿命を設定

			// 大きさ設定
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

			// 色設定
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].nIdxShadow = SetShadow(D3DXVECTOR3(g_aEffect[nCntEffect].pos.x, 0.0f, g_aEffect[nCntEffect].pos.z), g_aEffect[nCntEffect].rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.05f), 5, 5); // 影の番号を設定
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;  // ポインタを進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}