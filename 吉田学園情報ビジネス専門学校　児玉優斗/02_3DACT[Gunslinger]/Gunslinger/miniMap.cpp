//=============================================================================
//
// タイマー処理 [miniMap.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "miniMap.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_MINIMAP_POLYGON (2 + MAX_NUM_NPC)

//=============================================================================
//	プロトタイプ宣言
//=============================================================================
void MakeVertexminiMap(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffminiMap = NULL;					//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureminiMap[2] = {};						//テクスチャへのポインタ

CHARACTER_TILE g_CharaTile[MAX_NUM_NPC + 1];
//=============================================================================
//	初期化処理
//=============================================================================
void InitMiniMap(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/MiniMap000.png", &g_pTextureminiMap[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mapChara000.png", &g_pTextureminiMap[1]);

	MakeVertexminiMap(pDevice);
}

//=============================================================================
//	終了処理
//=============================================================================
void UninitMiniMap(void)
{
	//テクスチャの解放
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureminiMap[nCntTex] != NULL)
		{
			g_pTextureminiMap[nCntTex]->Release();
			g_pTextureminiMap[nCntTex] = NULL;
		}

	}
	//バッファの解放
	if (g_pVtxBuffminiMap != NULL)
	{
		g_pVtxBuffminiMap->Release();
		g_pVtxBuffminiMap = NULL;

	}

}

//=============================================================================
//	更新処理
//=============================================================================
void UpdateMiniMap(void)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	PLAYER *pPlayer;
	pPlayer = GetPlayer();
	NPC *pNPC;
	pNPC = GetNPC();

	g_CharaTile[0].pos.x = (pPlayer->pos.x + 1000.0f) / 8.0f;
	g_CharaTile[0].pos.y = (-pPlayer->pos.z + 1000.0f) / 8.0f;
	g_CharaTile[0].nTextype = 0;

	for (int nCntNPC = 0; nCntNPC < MAX_NUM_NPC; nCntNPC++)
	{
		g_CharaTile[nCntNPC + 1].pos.x = (pNPC->pos.x + 1000.0f) / 8.0f;
		g_CharaTile[nCntNPC + 1].pos.y = (-pNPC->pos.z + 1000.0f) / 8.0f;
		g_CharaTile[nCntNPC + 1].nTextype = 1;

		pNPC++;
	}

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffminiMap->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	for (int nCntTile = 0; nCntTile < MAX_MINIMAP_POLYGON - 1; nCntTile++)
	{
		pVtx[0].pos = D3DXVECTOR3(g_CharaTile[nCntTile].pos.x - 10.0f + 10.0f, g_CharaTile[nCntTile].pos.y - 10.0f + 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_CharaTile[nCntTile].pos.x + 10.0f + 10.0f, g_CharaTile[nCntTile].pos.y - 10.0f + 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_CharaTile[nCntTile].pos.x - 10.0f + 10.0f, g_CharaTile[nCntTile].pos.y + 10.0f + 10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_CharaTile[nCntTile].pos.x + 10.0f + 10.0f, g_CharaTile[nCntTile].pos.y + 10.0f + 10.0f, 0.0f);

		if (g_CharaTile[nCntTile].nTextype == 0)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
		}
		else
		{
			pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		}
		pVtx += 4;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffminiMap->Unlock();

}

//=============================================================================
//	描画処理
//=============================================================================
void DrawMiniMap(void)
{
	for (int nCntminiMap = 0; nCntminiMap < MAX_MINIMAP_POLYGON; nCntminiMap++)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = GetDevice();

		pDevice->SetStreamSource(0, g_pVtxBuffminiMap, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

		pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

									   // テクスチャの設定
		if (nCntminiMap == 0)
		{
			pDevice->SetTexture(0, g_pTextureminiMap[0]);//テクスチャの設定
		}
		else
		{
			pDevice->SetTexture(0, g_pTextureminiMap[1]);//テクスチャの設定
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
			4 * nCntminiMap,					   //開始する頂点のインデックス(基本０)
			2);		   	       //プリミティブの数
	}
}

//=============================================================================
//	頂点情報の追加
//=============================================================================
void MakeVertexminiMap(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MINIMAP_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffminiMap,
		NULL);

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffminiMap->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(260.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(10.0f, 260.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(260.0f, 260.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー	白
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		for (int nCntTile = 1; nCntTile < MAX_MINIMAP_POLYGON; nCntTile++)
		{
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラー	白
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx += 4;

		}
		//頂点バッファをアンロックする
		g_pVtxBuffminiMap->Unlock();

}
