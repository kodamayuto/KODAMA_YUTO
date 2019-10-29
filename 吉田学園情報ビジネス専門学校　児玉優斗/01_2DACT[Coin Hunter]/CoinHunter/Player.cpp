//*****************************************************************************
//
//	DirectX プレイヤーの処理 [player.cpp]
//	Author : Kodama Yuto
//
//*****************************************************************************
//インクルードファイル
#include "Player.h"
#include "block.h"

//=============================================================================
//	グローバル変数宣言
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;					//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;	                    //テクスチャへのポインタ

Player g_Player;		//プレイヤーの情報

//-----------------------------------------------------------------------------
//	ポリゴンの初期化処理
//-----------------------------------------------------------------------------
void InitPlayer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//プレイヤーの情報の初期化
	g_Player.pos = D3DXVECTOR3(PLAYER_POS_X,PLAYER_POS_Y,0.0f);
	g_Player.oldPos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_POS_Y, 0.0f);
	g_Player.col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.fJump = PLAYER_JUMP_MOVE;
	g_Player.fGravity = GRAVITY;
	g_Player.bDirection = false;
	g_Player.bJump = false;
	g_Player.bUse = true;
	g_Player.nCntAnim = 0;
	g_Player.nTexAnim = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE, &g_pTexturePlayer);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_SIZE_X, g_Player.pos.y - PLAYER_SIZE_Y * 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_SIZE_X, g_Player.pos.y - PLAYER_SIZE_Y * 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_SIZE_X, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_SIZE_X, g_Player.pos.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = g_Player.col;
	pVtx[1].col = g_Player.col;
	pVtx[2].col = g_Player.col;
	pVtx[3].col = g_Player.col;
	//pVtx[0].col = D3DXCOLOR(0, 0, 0, PLAYER_COLOR_A);
	//pVtx[1].col = D3DXCOLOR(0, 0, 0, PLAYER_COLOR_A);
	//pVtx[2].col = D3DXCOLOR(0, 0, 0, PLAYER_COLOR_A);
	//pVtx[3].col = D3DXCOLOR(0, 0, 0, PLAYER_COLOR_A);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//-----------------------------------------------------------------------------
//	 ポリゴンの終了処理
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//-----------------------------------------------------------------------------
//	ポリゴンの更新処理
//-----------------------------------------------------------------------------
void UpdatePlayer(void)
{
	if (g_Player.bUse == true)
	{
		//oldPosに前回のposを入れる
		g_Player.oldPos = g_Player.pos;

		//移動
		if (GetKeyboardPress(DIK_A) == true)		//←
		{
			if (g_Player.pos.x <= 0 - PLAYER_SIZE_X)
			{//左端に行ったら
				g_Player.pos.x = SCREEN_WIDTH + PLAYER_SIZE_X;
			}

			if (GetKeyboardPress(DIK_D) != true)		
			{//左キーを押してなければ

				if (g_Player.bJump == true)
				{
					g_Player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_JUMPMOVE_SPEED;
					g_Player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_JUMPMOVE_SPEED;

				}
				else
				{
					g_Player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_MOVE_SPEED;
					g_Player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_MOVE_SPEED;
				}
				g_Player.bDirection = true;//向きを左に
			}
			else
			{
				g_Player.move.x = 0;
			}
		}

		if (GetKeyboardPress(DIK_D) == true)	//→
		{
			if (g_Player.pos.x >= SCREEN_WIDTH + PLAYER_SIZE_X)
			{//右端に行ったら
				g_Player.pos.x = 0 - PLAYER_SIZE_X;
			}

			if (GetKeyboardPress(DIK_A) != true)		
			{//右キーを押してなければ

				if (g_Player.bJump == true)
				{
					g_Player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_JUMPMOVE_SPEED;
					g_Player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_JUMPMOVE_SPEED;

				}
				else
				{
					g_Player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_MOVE_SPEED;
					g_Player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_MOVE_SPEED;

				}
				g_Player.bDirection = false;//向きを右に
			}
			else
			{
				g_Player.move.x = 0;
			}
		}

		//加速(ダッシュ)
		if (GetKeyboardPress(DIK_M) == true)
		{
			if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_A) == true)
			{
				g_Player.move.x = g_Player.move.x * PLAYER_DASH_SPEED;
			}
		}

		//減速(今回はxのみ)
		g_Player.move.x += (0.0f - g_Player.move.x) * PLAYER_MOVE_COEFFICIENT;

		//重力加算
		g_Player.move.y += g_Player.fGravity;

		//ジャンプ
		if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.bLand == true || GetKeyboardPress(DIK_W) == true && g_Player.bLand== true)
		{
			g_Player.move.y = -g_Player.fJump;
			PlaySound(SOUND_LABEL_SE_006);
			g_Player.bJump = true;
			g_Player.bLand = false;

		}
		//posにmoveを加算
		g_Player.pos += g_Player.move;

		//アニメーション
		if (g_Player.bJump == false && g_Player.bLand == true)
		{
			g_Player.nCntAnim = (g_Player.nCntAnim + 1) % PLAYER_ANIM_INTERVAL;
		}
		else
		{//ジャンプ状態なら
			if (g_Player.nTexAnim % 2 == 0)
			{
				g_Player.nTexAnim = (g_Player.nTexAnim + 1) % 4;
			}
		}

		//TexAnimの更新
		if (g_Player.nCntAnim == PLAYER_ANIM_INTERVAL - 1)
		{
			if (GetKeyboardPress(DIK_D) == true && g_Player.move.x != 0 || GetKeyboardPress(DIK_A) == true && g_Player.move.x != 0)
			{//キーを押していて、かつ移動量が0でなければ
				
				g_Player.nTexAnim = (g_Player.nTexAnim + 1) % 4;
				g_Player.nCntAnim = 0;
			}
			else
			{//そうでなければ
				if (g_Player.nTexAnim % 2 == 1)
				{
					g_Player.nTexAnim = (g_Player.nTexAnim + 1) % 4;
				}
			}
		}
		//ブロックの当たり判定
		if (CollisionBlock(&g_Player.pos, &g_Player.oldPos, &g_Player.move) == true)
		{
			g_Player.bJump = false;
			g_Player.bLand = true;
		}
		else
		{
			g_Player.bJump = true;
			g_Player.bLand = false;

		}
		//アイテムの当たり判定
		CollisionItem();

		/*	pVtxの更新  */

		//変数宣言
		VERTEX_2D *pVtx;	//頂点情報へのポインタ

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_SIZE_X, g_Player.pos.y - PLAYER_SIZE_Y * 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_SIZE_X, g_Player.pos.y - PLAYER_SIZE_Y * 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_SIZE_X, g_Player.pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_SIZE_X, g_Player.pos.y, 0.0f);

		pVtx[0].col = g_Player.col;
		pVtx[1].col = g_Player.col;
		pVtx[2].col = g_Player.col;
		pVtx[3].col = g_Player.col;

		//bDirectionに応じて向きを変える
		if (g_Player.bDirection == false)
		{//右
			pVtx[0].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.0f,  0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.0f,  0.5f);
			pVtx[3].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.25f, 0.5f);
		}
		else
		{//左
			pVtx[0].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.0f,  0.5f);
			pVtx[1].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.25f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.0f,  1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.25f, 1.0f);
		}

		//頂点バッファをアンロックする
		g_pVtxBuffPlayer->Unlock();
	}
}

//-----------------------------------------------------------------------------
//	ポリゴンの描画処理
//-----------------------------------------------------------------------------
void DrawPlayer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

		//デバイスの取得
		pDevice = GetDevice();

		//描画
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

		pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

		pDevice->SetTexture(0, g_pTexturePlayer);//テクスチャの設定

		if (g_Player.bUse == true)
		{//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類			//プリミティブ == ポリゴン
					0,									   //開始する頂点のインデックス(基本０)
					2);		   							   //プリミティブの数
		}										 
}
//-----------------------------------------------------------------------------
//	プレイヤーとアイテムの当たり判定
//-----------------------------------------------------------------------------
void CollisionItem(void)
{
	ITEM *pItem;
	pItem = GetItem();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++,pItem++)
	{
		if (pItem->bUse == true)
		{
			//当たり判定(プレイヤーが重なると消える)
			if (g_Player.pos.y - PLAYER_SIZE_Y <= pItem->pos.y + pItem->fHeight&&//下側
				g_Player.pos.y - PLAYER_SIZE_Y >= pItem->pos.y - pItem->fHeight&&//上側
				g_Player.pos.x <= pItem->pos.x + pItem->fWidth&&				 //右側
				g_Player.pos.x >= pItem->pos.x - pItem->fWidth)					 //左側
			{
				AddScore(pItem->nScore);
				pItem->bDeleteFlag = true;
				
				int nCoinSound = rand() % 2;

				if (nCoinSound == 0)
				{
					PlaySound(SOUND_LABEL_SE_003);
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_004);
				}
			}
		}
	}
}

//=============================================================================
//	プレイヤーの取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}
