//=============================================================================
//
// 壁処理[particle.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "particle.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PARTICLE_FILENAME0 "data/TEXTURE/Ring000.png"
#define MAX_PARTICLE (4096)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;	    //テクスチャへのポインタ

PARTICLE g_Particle[MAX_PARTICLE];

//=============================================================================
// 初期化処理
//=============================================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, PARTICLE_FILENAME0, &g_pTextureParticle);

	MakeVertexParticle(pDevice);

	//構造体の初期化
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_Particle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Particle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Particle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Particle[nCntParticle].fWidth = 0.0f;
		g_Particle[nCntParticle].Haight = 0.0f;
		g_Particle[nCntParticle].nLife = 0;
		g_Particle[nCntParticle].bUse = false;
	}

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitParticle(void)
{
	// 頂点バッファの開放
		if (g_pTextureParticle != NULL)
		{
			g_pTextureParticle->Release();
			g_pTextureParticle = NULL;
		}

	//頂点バッファの破棄
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateParticle(void)
{
	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == true)
		{
			g_Particle[nCntParticle].fWidth -= 2.0f;
			g_Particle[nCntParticle].Haight -= 2.0f;

			if (g_Particle[nCntParticle].fWidth <= 0.0f || g_Particle[nCntParticle].Haight <= 0.0f)
			{
					g_Particle[nCntParticle].bUse = false;
			}


			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntParticle;

			pVtx[0].pos = D3DXVECTOR3(-g_Particle[nCntParticle].fWidth, g_Particle[nCntParticle].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Particle[nCntParticle].fWidth, g_Particle[nCntParticle].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Particle[nCntParticle].fWidth, -g_Particle[nCntParticle].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Particle[nCntParticle].fWidth, -g_Particle[nCntParticle].Haight, 0.0f);

			pVtx[0].col = g_Particle[nCntParticle].col;
			pVtx[1].col = g_Particle[nCntParticle].col;
			pVtx[2].col = g_Particle[nCntParticle].col;
			pVtx[3].col = g_Particle[nCntParticle].col;

			//頂点バッファをアンロックする
			g_pVtxBuffParticle->Unlock();

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans , mtxView;				// 計算用マトリックス
	PLAYER *pPlayer = GetPlayer();
	D3DXMATRIX playerMtx;
	// ポリゴンの描画
			//// αブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			//αテストを有効にする
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 120);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// Zバッファを無効化
			pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == true)
		{

			D3DXMatrixIdentity(&g_Particle[nCntParticle].g_mtxWorld);

			g_Particle[nCntParticle].g_mtxWorld._11 = mtxView._11;
			g_Particle[nCntParticle].g_mtxWorld._12 = mtxView._21;
			g_Particle[nCntParticle].g_mtxWorld._13 = mtxView._31;
			g_Particle[nCntParticle].g_mtxWorld._21 = mtxView._12;
			g_Particle[nCntParticle].g_mtxWorld._22 = mtxView._22;
			g_Particle[nCntParticle].g_mtxWorld._23 = mtxView._32;
			g_Particle[nCntParticle].g_mtxWorld._31 = mtxView._13;
			g_Particle[nCntParticle].g_mtxWorld._32 = mtxView._23;
			g_Particle[nCntParticle].g_mtxWorld._33 = mtxView._33;
			
			//// 位置を反映
			//D3DXMatrixTranslation(&mtxTrans,
			//	g_Particle[nCntParticle].pos.x,
			//	g_Particle[nCntParticle].pos.y,
			//	g_Particle[nCntParticle].pos.z);

			//D3DXMatrixMultiply(&g_Particle[nCntParticle].g_mtxWorld,
			//	&g_Particle[nCntParticle].g_mtxWorld,
			//	&mtxTrans);

			//プレイヤーの位置を反映
			D3DXMatrixTranslation(&playerMtx,
				pPlayer->pos.x,
				pPlayer->pos.y,
				pPlayer->pos.z);

			D3DXMatrixMultiply(&g_Particle[nCntParticle].g_mtxWorld,
				&g_Particle[nCntParticle].g_mtxWorld,
				&playerMtx);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Particle[nCntParticle].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

				// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureParticle);//テクスチャの設定

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
				4 * nCntParticle,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数
		}

	}
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
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float haight)
{
	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == false)
		{
			g_Particle[nCntParticle].pos = pos;
			g_Particle[nCntParticle].rot = rot;
			g_Particle[nCntParticle].col = col;
			g_Particle[nCntParticle].move = move;
			g_Particle[nCntParticle].fWidth = fWidth;
			g_Particle[nCntParticle].Haight = haight;


			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntParticle;
			pVtx[0].pos = D3DXVECTOR3(-g_Particle[nCntParticle].fWidth, g_Particle[nCntParticle].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Particle[nCntParticle].fWidth, g_Particle[nCntParticle].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Particle[nCntParticle].fWidth, -g_Particle[nCntParticle].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Particle[nCntParticle].fWidth, -g_Particle[nCntParticle].Haight, 0.0f);

			pVtx[0].col = g_Particle[nCntParticle].col;
			pVtx[1].col = g_Particle[nCntParticle].col;
			pVtx[2].col = g_Particle[nCntParticle].col;
			pVtx[3].col = g_Particle[nCntParticle].col;


			//頂点バッファをアンロックする
			g_pVtxBuffParticle->Unlock();
			g_Particle[nCntParticle].bUse = true;

			break;
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntParticle;

		pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffParticle->Unlock();
	}
}

