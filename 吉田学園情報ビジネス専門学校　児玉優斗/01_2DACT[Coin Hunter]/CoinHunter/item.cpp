//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "item.h"

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItem[NUM_TEXTURE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// 頂点バッファへのポインタ

ITEM g_aItem[MAX_ITEM];							// アイテムの情報

int g_nNumCoin = 0;
//=============================================================================
// 初期化処理
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].col  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aItem[nCntItem].fWidth = 0.0f;
		g_aItem[nCntItem].fHeight = 0.0f;
		g_aItem[nCntItem].nScore = 0;
		g_aItem[nCntItem].nCounterAnim = 0;
		g_aItem[nCntItem].nPatternAnim = 0;
		g_aItem[nCntItem].bUse = false;
		g_aItem[nCntItem].bDisp = false;
		g_aItem[nCntItem].Property = ITEM_SCOREUP_COIN;
	}
	g_nNumCoin = 0;
	// テクスチャの読み込み
	
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE, &g_pTextureItem[0]);

	// 頂点情報の作成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{

	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < NUM_TEXTURE; nCntTex++)
	{
		if (g_pTextureItem[nCntTex] != NULL)
		{
			g_pTextureItem[nCntTex]->Release();
			g_pTextureItem[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ
	Player *pPlayer;
	pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		
		if (g_aItem[nCntItem].bDisp == true)
		{
			//アニメーション
			g_aItem[nCntItem].nCounterAnim++;
			if (g_aItem[nCntItem].nCounterAnim % 5 == 0)
			{
				g_aItem[nCntItem].nPatternAnim = (g_aItem[nCntItem].nPatternAnim + 1) % TEX_PATTERN;
			}
			//g_aItem[nCntItem].fAngle = atan2f(g_aItem[nCntItem].fWidth ,g_aItem[nCntItem].fHeight);
			if (g_aItem[nCntItem].bDeleteFlag == true)
			{
				g_aItem[nCntItem].bUse = false;
				g_aItem[nCntItem].fAngle -= 0.05f;
				g_aItem[nCntItem].fLength -= 0.5f;
				g_aItem[nCntItem].pos.y -= 6.0f;
				g_aItem[nCntItem].col.a -= 0.05f;
				if (g_aItem[nCntItem].fAngle < 0.0f)
				{
					g_aItem[nCntItem].bDisp = false;
					NumCoinReduce();
				}
			}
			//g_aItem[nCntItem].fLength = sqrtf((g_aItem[nCntItem].fWidth) *(g_aItem[nCntItem].fWidth)+ 
			//									(g_aItem[nCntItem].fHeight) * (g_aItem[nCntItem].fHeight));

			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y - cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y - cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y + cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y + cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);

			pVtx[0].col = g_aItem[nCntItem].col;
			pVtx[1].col = g_aItem[nCntItem].col;
			pVtx[2].col = g_aItem[nCntItem].col;
			pVtx[3].col = g_aItem[nCntItem].col;

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2((1.0f / TEX_PATTERN) * (g_aItem[nCntItem].nPatternAnim % TEX_PATTERN), 0.0f);
			pVtx[1].tex = D3DXVECTOR2((1.0f / TEX_PATTERN) * (g_aItem[nCntItem].nPatternAnim % TEX_PATTERN) + (1.0f / TEX_PATTERN), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((1.0f / TEX_PATTERN) * (g_aItem[nCntItem].nPatternAnim % TEX_PATTERN), 1.0f);
			pVtx[3].tex = D3DXVECTOR2((1.0f / TEX_PATTERN) * (g_aItem[nCntItem].nPatternAnim % TEX_PATTERN) + (1.0f / TEX_PATTERN), 1.0f);
			
		}
		pVtx += 4;

	}
	
	// 頂点バッファをアンロックする
		g_pVtxBuffItem->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureItem[0]);

	// ポリゴンの描画
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bDisp == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類		//プリミティブ == ポリゴン
				4* nCntItem,					   //開始する頂点のインデックス(基本０)
				2);		   							       //プリミティブの数
		}
	}
}

//=============================================================================
// アイテムの設定処理
//=============================================================================
void SetItem(D3DXVECTOR3 pos, D3DXCOLOR col, int Score, ITEM_PROPERTY Property)
{
	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ
	int nCntItem;

	//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)//使用してないものから使用する
		{
			g_aItem[nCntItem].Property = Property;

			//サイズ
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].fWidth = ITEM_SIZE;
			g_aItem[nCntItem].fHeight = ITEM_SIZE;

			g_aItem[nCntItem].fAngle = atan2f(g_aItem[nCntItem].fWidth, g_aItem[nCntItem].fHeight);
			g_aItem[nCntItem].fLength = sqrtf((g_aItem[nCntItem].fWidth) *(g_aItem[nCntItem].fWidth) +
				(g_aItem[nCntItem].fHeight) * (g_aItem[nCntItem].fHeight));

			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y - cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y - cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y + cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y + cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);

			//色
			g_aItem[nCntItem].col = col;
			pVtx[0].col = g_aItem[nCntItem].col;
			pVtx[1].col = g_aItem[nCntItem].col;
			pVtx[2].col = g_aItem[nCntItem].col;
			pVtx[3].col = g_aItem[nCntItem].col;

			//テクスチャ
			g_aItem[nCntItem].nCounterAnim = 0;
			g_aItem[nCntItem].nPatternAnim = 0;

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

			//属性
			g_aItem[nCntItem].nScore = Score;
			g_aItem[nCntItem].bUse = true;
			g_aItem[nCntItem].bDisp = true;
			g_aItem[nCntItem].bDeleteFlag = false;

			if (g_aItem[nCntItem].Property == ITEM_SCOREUP_COIN)
			{
				g_nNumCoin++;
			}
			break;
		}
		pVtx += 4;
		
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();

}
//=============================================================================
// アイテムの情報取得
//=============================================================================
ITEM *GetItem(void)
{
	return &g_aItem[0];
}

//=============================================================================
// 残コインを取得
//=============================================================================
int GetNumCoin(void)
{
	return g_nNumCoin;
}

//=============================================================================
// コイン数を減らす
//=============================================================================
void NumCoinReduce(void)
{
	g_nNumCoin--;
}