//=============================================================================
//
// ブロックの処理 [block.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "block.h"
#include "Player.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBlock(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_BLOCK_TEXTURE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// 頂点バッファへのポインタ
Block					g_aBlock[MAX_BLOCK];		//ブロックの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].bFlag = false;
		g_aBlock[nCntBlock].nWarpCount = 10;
		g_aBlock[nCntBlock].type = BLOCKTYPE_NORMAL;
		g_aBlock[nCntBlock].ContBlock = BLOCKCONTACT_NONE;
	}

	// 頂点情報の作成
	MakeVertexBlock(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBlock(void)
{
	for (int nCntTex = 0; nCntTex < MAX_BLOCK_TEXTURE; nCntTex++)
	{	// テクスチャの開放
		if (g_pTextureBlock[nCntTex] != NULL)
		{
			g_pTextureBlock[nCntTex]->Release();
			g_pTextureBlock[nCntTex] = NULL;
		}

		//頂点バッファの破棄
		if (g_pVtxBuffBlock != NULL)
		{
			g_pVtxBuffBlock->Release();
			g_pVtxBuffBlock = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBlock(void)
{
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	for (int nCntData = 0; nCntData < MAX_BLOCK; nCntData++)
	{
		if (g_aBlock[nCntData].bUse == true)
		{
				g_aBlock[nCntData].pos += g_aBlock[nCntData].move;

			switch (g_aBlock[nCntData].type)
			{
			case BLOCKTYPE_MOVE://移動
				if (g_aBlock[nCntData].OldPos.x - g_aBlock[nCntData].pos.x <= -150||
					g_aBlock[nCntData].OldPos.x - g_aBlock[nCntData].pos.x >= 150)
				{
					g_aBlock[nCntData].move.x *= -1;
				}
				if (g_aBlock[nCntData].OldPos.y - g_aBlock[nCntData].pos.y <= -250 ||
					g_aBlock[nCntData].OldPos.y - g_aBlock[nCntData].pos.y >= 250)
				{
					g_aBlock[nCntData].move.y *= -1;
				}
				break;

			case BLOCKTYPE_FALL://落ちる
				if (g_aBlock[nCntData].ContBlock == BLOCKCONTACT_ON)
				{
					g_aBlock[nCntData].bFlag = true;
				}
				if (g_aBlock[nCntData].bFlag == true)
				{
					g_aBlock[nCntData].move.y += 0.6f;
				}
				if (g_aBlock[nCntData].pos.y > SCREEN_HEIGHT)
				{
					g_aBlock[nCntData].bUse = false;
					g_aBlock[nCntData].bFlag = false;
					g_aBlock[nCntData].ContBlock = BLOCKCONTACT_NONE;
				}
				break;

			case BLOCKTYPE_ATTACK_MOVE:
				if (g_aBlock[nCntData].ContBlock == BLOCKCONTACT_UNDER)
				{
					g_aBlock[nCntData].pos.y -= g_aBlock[nCntData].fHeight - 5;
				}
				break;

			case BLOCKTYPE_INV:
				if (g_aBlock[nCntData].ContBlock == BLOCKCONTACT_ON)
				{
					g_aBlock[nCntData].bFlag = true;
				}
				if (g_aBlock[nCntData].bFlag == true)
				{
					g_aBlock[nCntData].col.a -= 0.01f;
				}
				if (g_aBlock[nCntData].col.a <= 0.0f)
				{
					g_aBlock[nCntData].col.a = 0.0f;
					g_aBlock[nCntData].bUse = false;
					g_aBlock[nCntData].bFlag = false;
					g_aBlock[nCntData].ContBlock = BLOCKCONTACT_NONE;
				}
				break;

			case BLOCKTYPE_WARP_IN:
				int nOUTIndex;
				Player *pPlayer;
				pPlayer = GetPlayer();

				if (g_aBlock[nCntData].ContBlock == BLOCKCONTACT_ON)
				{
					g_aBlock[nCntData].bFlag = true;
				}
				if (g_aBlock[nCntData].bFlag == true)
				{
					pPlayer->move.x = 0.0f;
					pPlayer->move.y -= 2.0f;
					pPlayer->col.a -= 0.2f;
					g_aBlock[nCntData].nWarpCount--;
				}
				if (g_aBlock[nCntData].nWarpCount == 5)
				{
					nOUTIndex = ReturnBlockIndex(nCntData);
					PlaySound(SOUND_LABEL_SE_005);

					pPlayer->pos = D3DXVECTOR3(g_aBlock[nOUTIndex].pos.x + g_aBlock[nOUTIndex].fWidth / 2,
											   g_aBlock[nOUTIndex].pos.y,
											   0.0f);
					pPlayer->col.a += 0.2f;
					pPlayer->move.x = 0.0f;
					pPlayer->move.y = 0.0f;
				}
				if (g_aBlock[nCntData].nWarpCount <= 0)
				{
					g_aBlock[nCntData].bFlag = false;
					pPlayer->col.a = 1.0f;
					g_aBlock[nCntData].nWarpCount = 10;
				}
				break;
			case BLOCKTYPE_RESET:
				if (g_aBlock[nCntData].ContBlock == BLOCKCONTACT_UNDER)
				{
					ResetAttackMoveBlock();
				}

				break;
			}

			// 頂点情報を設定
			g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntData;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x, g_aBlock[nCntData].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth, g_aBlock[nCntData].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x, g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth, g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight, 0.0f);

			pVtx[0].col = g_aBlock[nCntData].col;
			pVtx[1].col = g_aBlock[nCntData].col;
			pVtx[2].col = g_aBlock[nCntData].col;
			pVtx[3].col = g_aBlock[nCntData].col;

			//頂点バッファをアンロックする
			g_pVtxBuffBlock->Unlock();
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBlock;
	
	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定

	// ポリゴンの描画
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類		//プリミティブ == ポリゴン
				4 * nCntBlock,					   //開始する頂点のインデックス(基本０)
				2);		   			   //プリミティブの数
		}

	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexBlock(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntData;

	//テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK,	&g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_1, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_2, &g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_3, &g_pTextureBlock[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_4, &g_pTextureBlock[4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_5, &g_pTextureBlock[5]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_6, &g_pTextureBlock[6]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_7, &g_pTextureBlock[7]);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						// 頂点情報を設定
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < MAX_BLOCK; nCntData++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x, g_aBlock[nCntData].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth, g_aBlock[nCntData].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x, g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth, g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = g_aBlock[nCntData].col;
		pVtx[1].col = g_aBlock[nCntData].col;
		pVtx[2].col = g_aBlock[nCntData].col;
		pVtx[3].col = g_aBlock[nCntData].col;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();


}

//=============================================================================
// ブロックの設定
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move,float fWidth,float fHeight, BLOCKTYPE type)
{
	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	int nCntData;
	for (nCntData = 0; nCntData < MAX_BLOCK; nCntData++)
	{
		if (g_aBlock[nCntData].bUse == false)
		{
			g_aBlock[nCntData].pos = pos;
			g_aBlock[nCntData].OldPos = pos;
			g_aBlock[nCntData].move = move;
			g_aBlock[nCntData].fWidth = fWidth;
			g_aBlock[nCntData].fHeight = fHeight;
		
			// 頂点情報を設定
			g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntData;
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x, g_aBlock[nCntData].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth, g_aBlock[nCntData].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x, g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth, g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight, 0.0f);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラー
			pVtx[0].col = g_aBlock[nCntData].col;
			pVtx[1].col = g_aBlock[nCntData].col;
			pVtx[2].col = g_aBlock[nCntData].col;
			pVtx[3].col = g_aBlock[nCntData].col;

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f * (g_aBlock[nCntData].fWidth / 40.0f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f * (g_aBlock[nCntData].fHeight / 40.0f));
			pVtx[3].tex = D3DXVECTOR2(1.0f * (g_aBlock[nCntData].fWidth / 40.0f), 1.0f * (g_aBlock[nCntData].fHeight / 40.0f));


			//頂点バッファをアンロックする
			g_pVtxBuffBlock->Unlock();
			g_aBlock[nCntData].type = type;

			g_aBlock[nCntData].bUse = true;
			break;
		}
	}
}

//=============================================================================
//	ブロックの当たり判定
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pOldPos, D3DXVECTOR3 *pMove)
{
	//変数宣言
	bool bLand = false;

	for (int nCntData = 0; nCntData < MAX_BLOCK; nCntData++)
	{
		g_aBlock[nCntData].ContBlock = BLOCKCONTACT_NONE;
		if (g_aBlock[nCntData].bUse == true)//使われていたら
		{
			if (g_aBlock[nCntData].pos.x  <= pOldPos->x &&
				g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth >= pOldPos->x)
			{
				if (g_aBlock[nCntData].pos.y <= pPos->y&&
					g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight >= pOldPos->y)
				{//上から下へ
					bLand = true;//地面に乗っている判定
					g_aBlock[nCntData].ContBlock = BLOCKCONTACT_ON;
					pPos->y = g_aBlock[nCntData].pos.y;
					pMove->x += g_aBlock[nCntData].move.x /2.4f;
					pMove->y = 0.0f;
					pMove->y += g_aBlock[nCntData].move.y;
				}
				
				if (g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight >= pPos->y - PLAYER_SIZE_Y * 2 &&
					g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight <= pOldPos->y - PLAYER_SIZE_Y * 2)
				{//下から上へ
					g_aBlock[nCntData].ContBlock = BLOCKCONTACT_UNDER;
					pPos->y = g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight + PLAYER_SIZE_Y * 2;
					pMove->y = 0.1f;
					PlaySound(SOUND_LABEL_SE_007);
				}
			}
			 if (g_aBlock[nCntData].pos.y < pOldPos->y - PLAYER_SIZE_Y&&
				g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight >= pOldPos->y - PLAYER_SIZE_Y * 2)
			{
				if (g_aBlock[nCntData].pos.x <= pPos->x + PLAYER_SIZE_X &&
					g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth >= pPos->x + PLAYER_SIZE_X &&
					g_aBlock[nCntData].pos.x >= pOldPos->x)
				{//左から右へ
					g_aBlock[nCntData].ContBlock = BLOCKCONTACT_LEFT;
					pPos->x = g_aBlock[nCntData].pos.x - PLAYER_SIZE_X;
					pMove->x = 0;
				}

				if (g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth >= pPos->x - PLAYER_SIZE_X&&
					g_aBlock[nCntData].pos.x <= pPos->x - PLAYER_SIZE_X &&
					g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth <= pOldPos->x)
				{//右から左へ
					g_aBlock[nCntData].ContBlock = BLOCKCONTACT_RIGHT;
					pPos->x = g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth + PLAYER_SIZE_X;
					pMove->x = 0;
				}
			}
		}
	}
	return bLand;//どこかの地面に乗っていればtrueを返す
}

//=============================================================================
//	ワープ先のブロックを返す関数
//=============================================================================
int ReturnBlockIndex(int nIndex)
{
	int nCntData = nIndex;
	while (1)
	{
		nCntData++;
		if (g_aBlock[nCntData].type == BLOCKTYPE_WARP_OUT)
		{
			break;
		}
	}

	return nCntData;
}
//=============================================================================
//	ブロックの位置を元に戻す関数
//=============================================================================
void ResetAttackMoveBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].type == BLOCKTYPE_ATTACK_MOVE)
		{
			g_aBlock[nCntBlock].pos = g_aBlock[nCntBlock].OldPos;
		}
	}
}