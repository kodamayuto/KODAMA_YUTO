//=============================================================================
//
//					DirectX 弾の発射処理  [bullet.cpp]
//					Author Kodama Yuto
//
//=============================================================================
#include"game.h"

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファへのポインタ

Bullet g_aBullet[MAX_BULLET];						//弾の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE, &g_pTextureBullet);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (4*nCntBullet);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = g_aBullet[nCntBullet].col;
		pVtx[1].col = g_aBullet[nCntBullet].col;
		pVtx[2].col = g_aBullet[nCntBullet].col;
		pVtx[3].col = g_aBullet[nCntBullet].col;

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//体力
		g_aBullet[nCntBullet].nLife = MAX_BULLET_LIFE;

		//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

	}
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ
	Player *pPlayer;

	pPlayer = GetPlayer();

	int nCntEnemy;
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{

		//画面外で弾消滅
		if (g_aBullet[nCntBullet].pos.x < -20 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH + 20 ||
			g_aBullet[nCntBullet].pos.y < -20 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT + 20)
		{
			g_aBullet[nCntBullet].bUse = false;
		}

		if (g_aBullet[nCntBullet].bUse == true)//弾が使われていたら
		{

			//エフェクトの設置
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 0.48f, 1.0f, 1.0f), BULLET_SIZE * 1.55f, 10);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY || g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY_HOMING)
			{
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.6f, 0.85f, 0.1f, 1.0f), BULLET_SIZE * 1.5, 10);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_BOSS )
			{
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.7f, 0.4f, 0.95f, 1.0f), BULLET_SIZE * 2, 15);
			}

			ENEMY *pEnemy;
			int nNumEnemy;
			//敵の取得
			pEnemy = GetEnemy();
			nNumEnemy = GetNumEnemy();

		//当たり判定
		if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)//プレイヤーの弾
		{
			if (nNumEnemy != 0)
			{
				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)//敵が使われていたら
					{

						if (g_aBullet[nCntBullet].pos.x > pEnemy->pos.x - ENEMY_POLYGON_SIZE - BULLET_SIZE && g_aBullet[nCntBullet].pos.x < pEnemy->pos.x + ENEMY_POLYGON_SIZE + BULLET_SIZE && g_aBullet[nCntBullet].pos.y > pEnemy->pos.y - ENEMY_POLYGON_SIZE - BULLET_SIZE && g_aBullet[nCntBullet].pos.y < pEnemy->pos.y + ENEMY_POLYGON_SIZE + BULLET_SIZE)
						{//当たったら
							HitEnemy(nCntEnemy, 1);
							g_aBullet[nCntBullet].bUse = false;
						}
					}
				}
			}
			else
			{
				BOSS *pBoss;
				pBoss = GetBoss();

				if (pBoss->state == BOSSSTATE_NORMAL)
				{
					if (g_aBullet[nCntBullet].pos.x > pBoss->pos.x - BOSS_POLYGON_SIZE - BULLET_SIZE && g_aBullet[nCntBullet].pos.x < pBoss->pos.x + BOSS_POLYGON_SIZE + BULLET_SIZE && g_aBullet[nCntBullet].pos.y > pBoss->pos.y - BOSS_POLYGON_SIZE - BULLET_SIZE && g_aBullet[nCntBullet].pos.y < pBoss->pos.y + BOSS_POLYGON_SIZE + BULLET_SIZE)
					{//当たったら
						HitBoss(1);
						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}
		}
		else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)//敵の弾
		{

			if (pPlayer->state == PLAYERSTATE_NORMAL)
			{
				if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - PLAYER_SIZE && g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + PLAYER_SIZE + 0 && g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - PLAYER_SIZE - 0 && g_aBullet[nCntBullet].pos.y < pPlayer->pos.y + PLAYER_SIZE + 0)
				{//当たったら
					HitPlayer(1);
					g_aBullet[nCntBullet].bUse = false;
				}
			}
		}
		else if (g_aBullet[nCntBullet].type == BULLETTYPE_BOSS || g_aBullet[nCntBullet].type == BULLETTYPE_BOSS_OPTION)
		{
			if (pPlayer->state == PLAYERSTATE_NORMAL)
			{

				if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - PLAYER_SIZE - 0 && g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + PLAYER_SIZE + 0 && g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - PLAYER_SIZE - 0 && g_aBullet[nCntBullet].pos.y < pPlayer->pos.y + PLAYER_SIZE + 0)
				{//当たったら
					HitPlayer(1);
					g_aBullet[nCntBullet].bUse = false;
				}
			}
		}
		g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

	//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntBullet;

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

		g_aBullet[nCntBullet].nLife--;

			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY || g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY_HOMING)
				{
					SetExplosion(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
					g_aBullet[nCntBullet].bUse = false;
				}
				else if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
				{
					SetExplosion(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, 0.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
					g_aBullet[nCntBullet].bUse = false;
				}
			}
			else if (g_aBullet[nCntBullet].pos.y <= 0 || g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT || g_aBullet[nCntBullet].pos.x<=0 || g_aBullet[nCntBullet].pos.x>= SCREEN_WIDTH)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			//頂点バッファをアンロックする
			g_pVtxBuffBullet->Unlock();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	// ポリゴンの描画
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類		//プリミティブ == ポリゴン
				4*nCntBullet,					   //開始する頂点のインデックス(基本０)
				2);		   							       //プリミティブの数
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,D3DXCOLOR col,float angle)
{
	int nCntBullet;
//変数宣言
			VERTEX_2D *pVtx;	//頂点情報へのポインタ

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			if (type == BULLETTYPE_ENEMY || type == BULLETTYPE_ENEMY_HOMING || type == BULLETTYPE_BOSS)
			{
				//頂点バッファをロックし、頂点データへのポインタを取得
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (4 * nCntBullet);
				g_aBullet[nCntBullet].pos = pos;

				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = type;
				g_aBullet[nCntBullet].col = col;
				g_aBullet[nCntBullet].fAngle = angle;

				pVtx[0].col = g_aBullet[nCntBullet].col;
				pVtx[1].col = g_aBullet[nCntBullet].col;
				pVtx[2].col = g_aBullet[nCntBullet].col;
				pVtx[3].col = g_aBullet[nCntBullet].col;

				g_aBullet[nCntBullet].bUse = true;

				g_aBullet[nCntBullet].nLife = MAX_BULLET_LIFE;
				//頂点バッファをアンロックする
				g_pVtxBuffBullet->Unlock();


				break;
			}
			else if(type == BULLETTYPE_PLAYER)
			{
				//頂点バッファをロックし、頂点データへのポインタを取得
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (4 * nCntBullet);
				g_aBullet[nCntBullet].pos = pos;

				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = type;
				g_aBullet[nCntBullet].col = col;

				pVtx[0].col = g_aBullet[nCntBullet].col;
				pVtx[1].col = g_aBullet[nCntBullet].col;
				pVtx[2].col = g_aBullet[nCntBullet].col;
				pVtx[3].col = g_aBullet[nCntBullet].col;

				//頂点バッファをアンロックする
				g_pVtxBuffBullet->Unlock();
				g_aBullet[nCntBullet].bUse = true;

				g_aBullet[nCntBullet].nLife = MAX_BULLET_LIFE;

				PlaySound(SOUND_LABEL_SE_SHOT);//音

				break;
			}
			else if (type == BULLETTYPE_BOSS_OPTION)
			{
				//頂点バッファをロックし、頂点データへのポインタを取得
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (4 * nCntBullet);
				g_aBullet[nCntBullet].pos = pos;

				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = type;
				g_aBullet[nCntBullet].col = col;

				pVtx[0].col = g_aBullet[nCntBullet].col;
				pVtx[1].col = g_aBullet[nCntBullet].col;
				pVtx[2].col = g_aBullet[nCntBullet].col;
				pVtx[3].col = g_aBullet[nCntBullet].col;

				//頂点バッファをアンロックする
				g_pVtxBuffBullet->Unlock();
				g_aBullet[nCntBullet].bUse = true;

				g_aBullet[nCntBullet].nLife = MAX_BULLET_LIFE;

				PlaySound(SOUND_LABEL_SE_SHOT);//音

				break;
			}

		}
	}
}

//=============================================================================
// 弾の取得
//=============================================================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}

//=============================================================================
//	終了時弾消去
//=============================================================================
void BulletErese(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].bUse = false;
	}
}

