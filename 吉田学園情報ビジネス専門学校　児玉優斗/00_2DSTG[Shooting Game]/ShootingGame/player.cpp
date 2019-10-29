//*****************************************************************************
//
//					DirectX プレイヤーの処理 [player.cpp]
//						Author Kodama Yuto
//
//*****************************************************************************
//インクルードファイル
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
//=============================================================================
//							グローバル変数宣言
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;					//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;	                    //テクスチャへのポインタ

int g_nCounterAnim;				//アニメーションカウンター
int g_nPattrenAnim;				//アニメーションパターンNo.
int g_Score;
Player g_Player;

//-----------------------------------------------------------------------------
//						   ポリゴンの初期化処理
//-----------------------------------------------------------------------------
void InitPlayer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3(SENT_POS_X, SENT_POS_Y, 0.0f);
	g_Player.bDisp = true;
	g_Player.nLife = PLAYER_LIFE;
	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.move = D3DXVECTOR3(0, 0, 0.0f);
	g_Player.nBulletPattern = 0;
	g_Player.nCntBullet = 0;
	g_Player.bMove = false;
	g_Player.nCountState = 50;

	g_nCounterAnim = 0;		//カウンターの初期化
	g_nPattrenAnim = 0;		//パターンNo.の初期化


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE,&g_pTexturePolygon);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);


	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(0 - PLAYER_SIZE, 0 - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0 + PLAYER_SIZE, 0 - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0 - PLAYER_SIZE, 0 + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0 + PLAYER_SIZE, 0 + PLAYER_SIZE, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPolygon->Unlock();
}

//-----------------------------------------------------------------------------
//						   ポリゴンの終了処理
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon -> Release();
		g_pTexturePolygon =  NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//-----------------------------------------------------------------------------
//							ポリゴンの更新処理
//-----------------------------------------------------------------------------
void UpdatePlayer(void)
{
	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//ステータス
	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		if (g_Player.bMove == true)
		{
			SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 22, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), PLAYER_SIZE / 2.5f, 10);
		}
		else
		{
			SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 22, 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f), PLAYER_SIZE / 2, 10);
		}
		break;
	case PLAYERSTATE_DAMAGE:
		SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 22, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), PLAYER_SIZE / 2, 10);

		g_Player.nCountState--;
		if (g_Player.nCountState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, PLAYER_COLOR_GREEN, PLAYER_COLOR_BLUE, PLAYER_COLOR_ALPHA);

			//頂点バッファをアンロックする
			g_pVtxBuffPolygon->Unlock();

		}
		break;
	case PLAYERSTATE_APPEAR:
		break;
	case PLAYERSTATE_DEATH:
		SetGameState(GAMESTATE_END);
		g_Player.state = PLAYERSTATE_END;
		StopSound(SOUND_LABEL_BGM001);
		PlaySound(SOUND_LABEL_SE_EXPLOSION);//音

		break;
	case PLAYERSTATE_END:
		break;
	}
	g_nCounterAnim++;

	if (g_Player.bDisp == true)
	{
		if (GetKeyboardPress(DIK_A) == true)//←
		{
			if (GetKeyboardPress(DIK_W) == true)//↑
			{
				g_Player.move.x += sinf(D3DX_PI * -0.75f) * PLAYER_MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.75f) * PLAYER_MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)//↓
			{
				g_Player.move.x += sinf(D3DX_PI * -0.25f) * PLAYER_MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.25f) * PLAYER_MOVE_SPEED;
			}
			else
			{
				g_Player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)//→
		{
			if (GetKeyboardPress(DIK_W) == true)//↑
			{
				g_Player.move.x += sinf(D3DX_PI * 0.75f) * PLAYER_MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.75f) * PLAYER_MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)//↓
			{
				g_Player.move.x += sinf(D3DX_PI * 0.25f) * PLAYER_MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.25f) * PLAYER_MOVE_SPEED;
			}
			else
			{
				g_Player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_MOVE_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)//↑
		{
			g_Player.move.x += sinf(D3DX_PI) * PLAYER_MOVE_SPEED;
			g_Player.move.y += cosf(D3DX_PI) * PLAYER_MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)//↓
		{
			g_Player.move.x += sinf(0.0) * PLAYER_MOVE_SPEED;
			g_Player.move.y += cosf(0.0) * PLAYER_MOVE_SPEED;
		}

		//SPACEキーで減速切り替え
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			g_Player.bMove = g_Player.bMove ? false : true;

		}

		if (g_Player.bMove == true)
		{
			g_Player.move.x += (0.0f - g_Player.move.x) * 0.55f;
			g_Player.move.y += (0.0f - g_Player.move.y) * 0.55f;
		}
		else
		{
			g_Player.move.x += (0.0f - g_Player.move.x) * PLAYER_MOVE_COEFFICIENT;
			g_Player.move.y += (0.0f - g_Player.move.y) * PLAYER_MOVE_COEFFICIENT;

		}

		//x軸の壁判定
		if (g_Player.pos.x <= 0 + PLAYER_SIZE && GetKeyboardPress(DIK_A) == true || g_Player.pos.x >= SCREEN_WIDTH - PLAYER_SIZE && GetKeyboardPress(DIK_D) == true)
		{
			g_Player.move.x = 0;
		}
		//y軸の壁判定
		if (g_Player.pos.y <= 0 + PLAYER_SIZE && GetKeyboardPress(DIK_W) == true || g_Player.pos.y >= SCREEN_HEIGHT - PLAYER_SIZE&& GetKeyboardPress(DIK_S) == true)
		{
			g_Player.move.y = 0;
		}

		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		//無敵(デバック用)
		if (GetKeyboardTrigger(DIK_Q) == true&& GetKeyboardPress(DIK_LSHIFT) == true && GetKeyboardPress(DIK_RSHIFT) == true && GetKeyboardPress(DIK_0) == true)
		{
			g_Player.state = PLAYERSTATE_APPEAR;
			DebugEnemyLifeDown();
		}

		//弾パターン切り替え
		if (GetKeyboardTrigger(DIK_K) == true)
		{
			g_Player.nBulletPattern++;
			g_Player.nCntBullet = 0;
		}

		if (GetKeyboardTrigger(DIK_M) == true && GetKeyboardPress(DIK_L) == false)
		{//手動ショット
			if (g_Player.nBulletPattern % 3 == 0)
			{
				SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//中央
				SetBullet(g_Player.pos, D3DXVECTOR3(-2.5f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//左上側
				SetBullet(g_Player.pos, D3DXVECTOR3(2.5f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//右上側
			}
			else if (g_Player.nBulletPattern % 3 == 1)
			{
				SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//中央
				SetBullet(D3DXVECTOR3(g_Player.pos.x - 30, g_Player.pos.y + 20, 0.0f), D3DXVECTOR3(2.5f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//左上側
				SetBullet(D3DXVECTOR3(g_Player.pos.x + 30, g_Player.pos.y + 20, 0.0f), D3DXVECTOR3(-2.5f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//右上側
			}
			else
			{
				SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -7.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//中央
				SetBullet(D3DXVECTOR3(g_Player.pos.x - 10, g_Player.pos.y + 15, 0.0f), D3DXVECTOR3(0.0f, -7.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//左上側
				SetBullet(D3DXVECTOR3(g_Player.pos.x + 10, g_Player.pos.y + 15, 0.0f), D3DXVECTOR3(0.0f, -7.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);		//右上側

			}

		}
		if (GetKeyboardPress(DIK_L) == true)
		{//自動ショット
			if (g_Player.nBulletPattern % 3 == 0)
			{
				if (g_nCounterAnim % 11 == 0)
				{
					SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);												 //中央
					SetBullet(D3DXVECTOR3(g_Player.pos.x - 50, g_Player.pos.y + 20, 0.0f), D3DXVECTOR3(0.0f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f); //左上側
					SetBullet(D3DXVECTOR3(g_Player.pos.x + 50, g_Player.pos.y + 20, 0.0f), D3DXVECTOR3(0.0f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);//右上側
				}
			}
			else if (g_Player.nBulletPattern % 3 == 1)
			{
				if (g_nCounterAnim % 5 == 0)
				{
					SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -7.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f); //中央
				}
			}
			else
			{
				if (g_nCounterAnim % 11 == 0)
				{
					SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);												 //中央
					SetBullet(D3DXVECTOR3(g_Player.pos.x - (10), g_Player.pos.y + 20, 0.0f), D3DXVECTOR3(-1.0f * (1.5f + (g_Player.nCntBullet % 5)), -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f); //左上側
					SetBullet(D3DXVECTOR3(g_Player.pos.x + (10), g_Player.pos.y + 20, 0.0f), D3DXVECTOR3(1.0f * (1.5f + (g_Player.nCntBullet % 5)), -9.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.0f);//右上側
					g_Player.nCntBullet++;
				}
			}
		}


		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_SIZE, g_Player.pos.y - PLAYER_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_SIZE, g_Player.pos.y - PLAYER_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_SIZE, g_Player.pos.y + PLAYER_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_SIZE, g_Player.pos.y + PLAYER_SIZE, 0.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffPolygon->Unlock();
	}

}
//-----------------------------------------------------------------------------
//							ポリゴンの描画処理
//-----------------------------------------------------------------------------
void DrawPlayer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	if (g_Player.bDisp == true)
	{
		//デバイスの取得
		pDevice = GetDevice();

		//描画
		pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

		pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

		pDevice->SetTexture(0, g_pTexturePolygon);//テクスチャの設定

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
			0,					   //開始する頂点のインデックス(基本０)
			2);		   	       //プリミティブの数
	}
}

//=============================================================================
//	プレイヤーの取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}

//=============================================================================
//	ダメージ処理
//=============================================================================
void HitPlayer(int nDamage)
{

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	g_Player.nLife -= nDamage;
	PlaySound(SOUND_LABEL_SE_HIT001);//音
	SetLife(g_Player.nLife);

	if (g_Player.nLife <= 0)
	{
		SetExplosion(g_Player.pos, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		g_Player.bDisp = false;
		g_Player.state = PLAYERSTATE_DEATH;
		g_Player.nCountState = 60;
		g_Score = -200000;
		AddScore(g_Score);
	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCountState = 5;
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, 0, 0, PLAYER_COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, 0, 0, PLAYER_COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, 0, 0, PLAYER_COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(PLAYER_COLOR_RED, 0, 0, PLAYER_COLOR_ALPHA);

		//頂点バッファをアンロックする
		g_pVtxBuffPolygon->Unlock();
	}
}