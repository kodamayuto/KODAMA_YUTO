//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "enemy.h"
#include "Explosion.h"
#include "game.h"
#include"boss.h"

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// 頂点バッファへのポインタ

ENEMY g_aEnemy[MAX_ENEMY];	//敵のデータ格納
int g_nNumEnemy;			//敵の総数
int g_nCounterGame;			//出現時間の管理

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 5;
		g_aEnemy[nCntEnemy].nCounterBullet = 0;
	}
	g_nNumEnemy = 0;
	// テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_00, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_01, &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_02, &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_03, &g_apTextureEnemy[3]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_04, &g_apTextureEnemy[4]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_05, &g_apTextureEnemy[5]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_06, &g_apTextureEnemy[6]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_07, &g_apTextureEnemy[7]);

	// 頂点情報の作成
	VERTEX_2D *pVtx;
	

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		pVtx[0].pos = D3DXVECTOR3(0 - ENEMY_POLYGON_SIZE, 0 - ENEMY_POLYGON_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0 + ENEMY_POLYGON_SIZE, 0 - ENEMY_POLYGON_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0 - ENEMY_POLYGON_SIZE, 0 + ENEMY_POLYGON_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0 + ENEMY_POLYGON_SIZE, 0 + ENEMY_POLYGON_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(ENEMY_COLOR_RED, ENEMY_COLOR_GREEN, ENEMY_COLOR_BLUE, ENEMY_COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(ENEMY_COLOR_RED, ENEMY_COLOR_GREEN, ENEMY_COLOR_BLUE, ENEMY_COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(ENEMY_COLOR_RED, ENEMY_COLOR_GREEN, ENEMY_COLOR_BLUE, ENEMY_COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(ENEMY_COLOR_RED, ENEMY_COLOR_GREEN, ENEMY_COLOR_BLUE, ENEMY_COLOR_ALPHA);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	// 頂点情報の作成
	Player *pPlayer;
	float fBulletAngle;
	int nCntEnemy;
	
	pPlayer = GetPlayer();
	
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].nCounterBullet += rand() % 3 + 1;
		if (g_aEnemy[nCntEnemy].bUse == true)
		{

			//移動

			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				if (g_aEnemy[nCntEnemy].nCounterBullet % (rand() % 30 + 15 + (g_nNumEnemy * 4)) == 0)
				{//弾打ち
						if (g_aEnemy[nCntEnemy].nCounterBullet % 7 == 0)
						{//	直進
							SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 9.0f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 0.0f);
						}
						else if (g_aEnemy[nCntEnemy].nCounterBullet % 7 == 2|| g_aEnemy[nCntEnemy].nCounterBullet % 7 == 3)
						{
							fBulletAngle = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);
							SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(fBulletAngle) * 8.0f, cosf(fBulletAngle) * 8.0f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),0.0f);
						}	
						else if (g_aEnemy[nCntEnemy].nCounterBullet % 7 == 1|| g_aEnemy[nCntEnemy].nCounterBullet % 7 == 5)
						{
							fBulletAngle = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);
							SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(fBulletAngle - 0.4f) * 8.0f, cosf(fBulletAngle) * 8.0f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), 0.0f);
							SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(fBulletAngle + 0.4f) * 8.0f, cosf(fBulletAngle) * 8.0f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), 0.0f);
						}
				}
				break;
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

				}
				break;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_NORMAL)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			}
			else if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_DAMAGE)
			{
				pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType + 4]);
			}

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類		//プリミティブ == ポリゴン
				4 * nCntEnemy,							   //開始する頂点のインデックス(基本０)
				2);		   							       //プリミティブの数
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	int nCntEnemy;

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (4*nCntEnemy);

			g_aEnemy[nCntEnemy].pos = pos;

			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_POLYGON_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_POLYGON_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_POLYGON_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_POLYGON_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_POLYGON_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_POLYGON_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_POLYGON_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_POLYGON_SIZE, 0.0f);

			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nType = nType;

			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

			g_aEnemy[nCntEnemy].nCounterState = 0;

			g_aEnemy[nCntEnemy].nLife = 2 * (1 + nType);
			g_aEnemy[nCntEnemy].nCounterBullet = 0;
			g_aEnemy[nCntEnemy].bUse = true;

			g_pVtxBuffEnemy->Unlock();

			g_nNumEnemy++;
			break;
		}	
	}
}

//=============================================================================
// 敵の取得
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}
//=============================================================================
// 敵の数の取得
//=============================================================================
int GetNumEnemy(void)
{
	return g_nNumEnemy;
}

//=============================================================================
//	ダメージ処理
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	// 頂点情報の作成
	Player *pPlayer;

	int nValue = 0;			//点数

	pPlayer = GetPlayer();
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	PlaySound(SOUND_LABEL_SE_HIT000);//音

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		g_aEnemy[nCntEnemy].bUse = false;

		if (pPlayer->bDisp == true)
		{
		nValue = (10000 *(2 + g_aEnemy[nCntEnemy].nType)) + (1000 * (100 - g_nNumEnemy));
		AddScore(nValue);
		}

		PlaySound(SOUND_LABEL_SE_EXPLOSION);//音


		g_nNumEnemy--;
		if (g_nNumEnemy <= 0)
		{
			//StopSound(SOUND_LABEL_BGM001);
			//SetGameState(GAMESTATE_END);

			SetBoss(D3DXVECTOR3(SCREEN_WIDTH / 2, 0, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		}
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 3;
		if (pPlayer->bDisp == true)
		{
			nValue = 100 * (g_aEnemy[nCntEnemy].nType + 2);
			AddScore(nValue);
		}
	}
}
//=============================================================================
//	敵の体力減少(デバック用)
//=============================================================================
void DebugEnemyLifeDown(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].nLife = 1;
		}
	}
}
