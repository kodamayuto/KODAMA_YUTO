//=============================================================================
//
// 壁処理[explosion.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "explosion.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EXPLOSION_FILENAME0 "data/TEXTURE/Effect_p011.png"		//ファイル名のマクロ
#define MAX_EXPLOSION (1024)									//

#define ANIM_EXPLOSION (8)

#define ANIM_COUNT_INTERVAL (4)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;	    //テクスチャへのポインタ

EXPLOSION g_Explosion[MAX_EXPLOSION];

//=============================================================================
// 初期化処理
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_FILENAME0, &g_pTextureExplosion);

	MakeVertexExplosion(pDevice);

	//構造体の初期化
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_Explosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Explosion[nCntExplosion].fWidth = 0.0f;
		g_Explosion[nCntExplosion].Haight = 0.0f;
		g_Explosion[nCntExplosion].nAnim = 0;
		g_Explosion[nCntExplosion].nCntAnimation = 0;
		g_Explosion[nCntExplosion].bUse = false;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	// 頂点バッファの開放
		if (g_pTextureExplosion != NULL)
		{
			g_pTextureExplosion->Release();
			g_pTextureExplosion = NULL;
		}

	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ
	
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_Explosion[nCntExplosion].bUse == true)
		{
			g_Explosion[nCntExplosion].fWidth += 0.8f;
			g_Explosion[nCntExplosion].Haight += 0.8f;
			g_Explosion[nCntExplosion].nCntAnimation++;
			if (g_Explosion[nCntExplosion].nCntAnimation % ANIM_COUNT_INTERVAL == 0)
			{
				g_Explosion[nCntExplosion].nAnim++;

				if (g_Explosion[nCntExplosion].nAnim >= ANIM_EXPLOSION)
				{
					g_Explosion[nCntExplosion].bUse = false;
				}
			}
			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntExplosion;

			pVtx[0].pos = D3DXVECTOR3(-g_Explosion[nCntExplosion].fWidth, g_Explosion[nCntExplosion].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Explosion[nCntExplosion].fWidth, g_Explosion[nCntExplosion].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Explosion[nCntExplosion].fWidth, -g_Explosion[nCntExplosion].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Explosion[nCntExplosion].fWidth, -g_Explosion[nCntExplosion].Haight, 0.0f);

			pVtx[0].tex = D3DXVECTOR2((1.0f / ANIM_EXPLOSION) * (g_Explosion[nCntExplosion].nAnim % ANIM_EXPLOSION), 0.0f);
			pVtx[1].tex = D3DXVECTOR2((1.0f / ANIM_EXPLOSION) * (g_Explosion[nCntExplosion].nAnim % ANIM_EXPLOSION) + (1.0f / ANIM_EXPLOSION), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((1.0f / ANIM_EXPLOSION) * (g_Explosion[nCntExplosion].nAnim % ANIM_EXPLOSION), 1.0f);
			pVtx[3].tex = D3DXVECTOR2((1.0f / ANIM_EXPLOSION) * (g_Explosion[nCntExplosion].nAnim % ANIM_EXPLOSION) + (1.0f / ANIM_EXPLOSION), 1.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffExplosion->Unlock();

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxTrans , mtxView;				// 計算用マトリックス

	// ポリゴンの描画
	//// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//αテストを有効にする
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// Zバッファを無効化
			pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);						

			// ライティングモードを無効化
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_Explosion[nCntExplosion].bUse == true)
		{
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			D3DXMatrixIdentity(&g_Explosion[nCntExplosion].g_mtxWorld);

			g_Explosion[nCntExplosion].g_mtxWorld._11 = mtxView._11;
			g_Explosion[nCntExplosion].g_mtxWorld._12 = mtxView._21;
			g_Explosion[nCntExplosion].g_mtxWorld._13 = mtxView._31;
			g_Explosion[nCntExplosion].g_mtxWorld._21 = mtxView._12;
			g_Explosion[nCntExplosion].g_mtxWorld._22 = mtxView._22;
			g_Explosion[nCntExplosion].g_mtxWorld._23 = mtxView._32;
			g_Explosion[nCntExplosion].g_mtxWorld._31 = mtxView._13;
			g_Explosion[nCntExplosion].g_mtxWorld._32 = mtxView._23;
			g_Explosion[nCntExplosion].g_mtxWorld._33 = mtxView._33;
			
			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Explosion[nCntExplosion].pos.x,
				g_Explosion[nCntExplosion].pos.y,
				g_Explosion[nCntExplosion].pos.z);

			D3DXMatrixMultiply(&g_Explosion[nCntExplosion].g_mtxWorld,
				&g_Explosion[nCntExplosion].g_mtxWorld,
				&mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Explosion[nCntExplosion].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

				// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion);//テクスチャの設定

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
				4 * nCntExplosion,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数
		}

	}

	// ライティングモードを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Zバッファの有効化
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//αテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// ポリゴンの設定
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fWidth, float haight)
{
	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_Explosion[nCntExplosion].bUse == false)
		{
			g_Explosion[nCntExplosion].pos = pos;
			g_Explosion[nCntExplosion].rot = rot;
			g_Explosion[nCntExplosion].col = col;
			g_Explosion[nCntExplosion].fWidth = fWidth;
			g_Explosion[nCntExplosion].Haight = haight;
			g_Explosion[nCntExplosion].nAnim = 0;
			g_Explosion[nCntExplosion].nCntAnimation = 0;


			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntExplosion;
			pVtx[0].pos = D3DXVECTOR3(-g_Explosion[nCntExplosion].fWidth, g_Explosion[nCntExplosion].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Explosion[nCntExplosion].fWidth, g_Explosion[nCntExplosion].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Explosion[nCntExplosion].fWidth, -g_Explosion[nCntExplosion].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Explosion[nCntExplosion].fWidth, -g_Explosion[nCntExplosion].Haight, 0.0f);

			pVtx[0].col = g_Explosion[nCntExplosion].col;
			pVtx[1].col = g_Explosion[nCntExplosion].col;
			pVtx[2].col = g_Explosion[nCntExplosion].col;
			pVtx[3].col = g_Explosion[nCntExplosion].col;


			//頂点バッファをアンロックする
			g_pVtxBuffExplosion->Unlock();
			g_Explosion[nCntExplosion].bUse = true;

			break;
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntExplosion;

		pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

		//pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffExplosion->Unlock();
	}
}

