//=============================================================================
//
// モデル処理 [npc.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "npc.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshNPC[MAX_NUM_NPC] = {};		//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatNPC[MAX_NUM_NPC] = {};	//マテリアル情報へのポインタ

NPC g_NPC[MAX_NUM_NPC];
//=============================================================================
// 初期化処理
//=============================================================================
void InitNpc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (int nCntNpc = 0; nCntNpc < MAX_NUM_NPC; nCntNpc++)
	{

		g_NPC[nCntNpc].aModel[0].FireName = NPC_FILENAME0;
		g_NPC[nCntNpc].aModel[1].FireName = NPC_FILENAME1;
		g_NPC[nCntNpc].aModel[2].FireName = NPC_FILENAME2;
		g_NPC[nCntNpc].aModel[3].FireName = NPC_FILENAME3;
		g_NPC[nCntNpc].aModel[4].FireName = NPC_FILENAME4;
		g_NPC[nCntNpc].aModel[5].FireName = NPC_FILENAME5;
		g_NPC[nCntNpc].aModel[6].FireName = NPC_FILENAME6;
		g_NPC[nCntNpc].aModel[7].FireName = NPC_FILENAME7;
		g_NPC[nCntNpc].aModel[8].FireName = NPC_FILENAME8;
		g_NPC[nCntNpc].aModel[9].FireName = NPC_FILENAME9;
		g_NPC[nCntNpc].aModel[10].FireName = NPC_FILENAME10;

		for (int nCntParts = 0; nCntParts < PARTS_NUM_NPC; nCntParts++)
		{
			// Xファイルの読み込み
			D3DXLoadMeshFromX(g_NPC[nCntNpc].aModel[nCntParts].FireName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_NPC[nCntNpc].aModel[nCntParts].pBuffMat,
				NULL,
				&g_NPC[nCntNpc].aModel[nCntParts].nNumMat,
				&g_NPC[nCntNpc].aModel[nCntParts].pMesh);
		}
		/*当たり判定の設定*/
		SetNpcVertex(nCntNpc);
		// 位置・向きの初期設定
		//g_NPC[nCntNpc].pos = D3DXVECTOR3(20.0f, 0.0f, 0.0f);
		g_NPC[nCntNpc].rot = D3DXVECTOR3(0.0f, (rand() % 628 - 314) * 0.01f, 0.0f);
		g_NPC[nCntNpc].bUse = true;
		//移動量・回転量の初期化
		g_NPC[nCntNpc].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_NPC[nCntNpc].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_NPC[nCntNpc].state = NPCSTATE_MOVE;
		g_NPC[nCntNpc].nCntMove = 0;
		g_NPC[nCntNpc].npcAI = AI_CHASE;
		g_NPC[nCntNpc].nIdxShadow = SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_NPC[nCntNpc].nCntBullet = 0;
		g_NPC[nCntNpc].aModel[0].pos = D3DXVECTOR3(0.0f, 16.0f, 0.0f);//体
		g_NPC[nCntNpc].aModel[1].pos = D3DXVECTOR3(0.0f, 14.5f, 0.0f);//頭
		g_NPC[nCntNpc].aModel[2].pos = D3DXVECTOR3(-5.0f, 11.5f, 0.0f);//右腕
		g_NPC[nCntNpc].aModel[3].pos = D3DXVECTOR3(-13.0f, 0.0f, 0.0f);//右手
		g_NPC[nCntNpc].aModel[4].pos = D3DXVECTOR3(5.0f, 11.5f, 0.0f);//左腕
		g_NPC[nCntNpc].aModel[5].pos = D3DXVECTOR3(13.0f, 0.0f, 0.0f);//左手
		g_NPC[nCntNpc].aModel[6].pos = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);//右腿
		g_NPC[nCntNpc].aModel[7].pos = D3DXVECTOR3(0.0f, -12.0f, 0.0f);//右足
		g_NPC[nCntNpc].aModel[8].pos = D3DXVECTOR3(3.0f, 0.0f, 0.0f);  //左腿
		g_NPC[nCntNpc].aModel[9].pos = D3DXVECTOR3(0.0f, -12.0f, 0.0f);//左足
		g_NPC[nCntNpc].aModel[10].pos = D3DXVECTOR3(2.0f, 0.0f, 0.0f);//武器

		g_NPC[nCntNpc].aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//体
		g_NPC[nCntNpc].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//頭
		g_NPC[nCntNpc].aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右腕
		g_NPC[nCntNpc].aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右手
		g_NPC[nCntNpc].aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左腕
		g_NPC[nCntNpc].aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左手
		g_NPC[nCntNpc].aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右腿
		g_NPC[nCntNpc].aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右足
		g_NPC[nCntNpc].aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左腿
		g_NPC[nCntNpc].aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左足
		g_NPC[nCntNpc].aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//武器

		g_NPC[nCntNpc].aModel[0].nIdxModelParent = -1;//体
		g_NPC[nCntNpc].aModel[1].nIdxModelParent = 0;//頭
		g_NPC[nCntNpc].aModel[2].nIdxModelParent = 0;//右腕
		g_NPC[nCntNpc].aModel[3].nIdxModelParent = 2;//右手
		g_NPC[nCntNpc].aModel[4].nIdxModelParent = 0;//左腕
		g_NPC[nCntNpc].aModel[5].nIdxModelParent = 4;//左手
		g_NPC[nCntNpc].aModel[6].nIdxModelParent = 0;//右腿
		g_NPC[nCntNpc].aModel[7].nIdxModelParent = 6;//右足
		g_NPC[nCntNpc].aModel[8].nIdxModelParent = 0;//左腿
		g_NPC[nCntNpc].aModel[9].nIdxModelParent = 8;//左足
		g_NPC[nCntNpc].aModel[10].nIdxModelParent = 5;//武器

		g_NPC[nCntNpc].aModel[0].motion.motion0[0] = { D3DXVECTOR3(-0.27f, -0.16f, 0.00f) };
		g_NPC[nCntNpc].aModel[1].motion.motion0[0] = { D3DXVECTOR3(0.09f, -0.25f, 0.00f) };
		g_NPC[nCntNpc].aModel[2].motion.motion0[0] = { D3DXVECTOR3(1.51f, 0.00f, 1.09f) };
		g_NPC[nCntNpc].aModel[3].motion.motion0[0] = { D3DXVECTOR3(0.00f, -1.09f, 0.00f) };
		g_NPC[nCntNpc].aModel[4].motion.motion0[0] = { D3DXVECTOR3(-1.51f, 0.00f, -1.09f) };
		g_NPC[nCntNpc].aModel[5].motion.motion0[0] = { D3DXVECTOR3(0.00f, 1.09f, 0.00f) };
		g_NPC[nCntNpc].aModel[6].motion.motion0[0] = { D3DXVECTOR3(-1.06f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[7].motion.motion0[0] = { D3DXVECTOR3(-0.97f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[8].motion.motion0[0] = { D3DXVECTOR3(1.16f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[9].motion.motion0[0] = { D3DXVECTOR3(0.00f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[10].motion.motion0[0] = { D3DXVECTOR3(0.00f, 0.00f, 1.45f) };

		g_NPC[nCntNpc].aModel[0].motion.motion0[1] = { D3DXVECTOR3(-0.27f, 0.14f, 0.00f) };
		g_NPC[nCntNpc].aModel[1].motion.motion0[1] = { D3DXVECTOR3(0.10f, 0.25f, 0.00f) };
		g_NPC[nCntNpc].aModel[2].motion.motion0[1] = { D3DXVECTOR3(-1.52f, 0.00f, 1.09f) };
		g_NPC[nCntNpc].aModel[3].motion.motion0[1] = { D3DXVECTOR3(0.00f, -1.09f, 0.00f) };
		g_NPC[nCntNpc].aModel[4].motion.motion0[1] = { D3DXVECTOR3(1.52f, 0.00f, -1.09f) };
		g_NPC[nCntNpc].aModel[5].motion.motion0[1] = { D3DXVECTOR3(0.00f, 1.09f, 0.00f) };
		g_NPC[nCntNpc].aModel[6].motion.motion0[1] = { D3DXVECTOR3(1.16f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[7].motion.motion0[1] = { D3DXVECTOR3(-0.05f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[8].motion.motion0[1] = { D3DXVECTOR3(-1.07f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[9].motion.motion0[1] = { D3DXVECTOR3(-0.92f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[10].motion.motion0[1] = { D3DXVECTOR3(0.50f, 0.00f, -0.97f) };

		g_NPC[nCntNpc].aModel[0].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[1].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[2].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[3].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[4].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[5].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[6].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[7].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[8].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[9].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[10].motion.nKeyFrame = 20;


	}
	g_NPC[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_NPC[1].pos = D3DXVECTOR3(-300.0f, 0.0f, -300.0f);
	g_NPC[2].pos = D3DXVECTOR3(-700.0f, 0.0f, -500.0f);
	g_NPC[3].pos = D3DXVECTOR3(-400.0f, 0.0f, 900.0f);



}

//=============================================================================
// 終了処理
//=============================================================================
void UninitNpc(void)
{
	// メッシュの解放
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_NPC; nCntMesh++)
	{
		if (g_pMeshNPC[nCntMesh] != NULL)
		{
			g_pMeshNPC[nCntMesh]->Release();
			g_pMeshNPC[nCntMesh] = NULL;
		}
		/*テクスチャの解放*/
		//マテリアルの解放
		if (g_pBuffMatNPC[nCntMesh] != NULL)
		{
			g_pBuffMatNPC[nCntMesh]->Release();
			g_pBuffMatNPC[nCntMesh] = NULL;
		}
	}
	
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateNpc(void)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	for (int nCntNpc = 0; nCntNpc < MAX_NUM_NPC; nCntNpc++)
	{
		if (g_NPC[nCntNpc].bUse == true)
		{
			if (pPlayer->bUse == true)
			{
				//現在のposをposOldに格納
				g_NPC[nCntNpc].posOld = g_NPC[nCntNpc].pos;
				switch (g_NPC[nCntNpc].state)
				{//状態
				case NPCSTATE_MOVE:			//動ける状態
					//移動アルゴリズム
					switch (g_NPC[nCntNpc].npcAI)
					{
					case AI_RANDOM://ランダム
						g_NPC[nCntNpc].move.x = sinf(g_NPC[nCntNpc].rot.y + D3DX_PI) * NPC_MOVE_SPEED;
						g_NPC[nCntNpc].move.z = cosf(g_NPC[nCntNpc].rot.y + D3DX_PI) * NPC_MOVE_SPEED;

						//移動係数の加算
						g_NPC[nCntNpc].move.x += (0.0f - g_NPC[nCntNpc].move.x) * 0.2f;
						g_NPC[nCntNpc].move.z += (0.0f - g_NPC[nCntNpc].move.z) * 0.2f;

						if (g_NPC[nCntNpc].pos.x < -1000.0f && g_NPC[nCntNpc].move.x < 0 ||
							g_NPC[nCntNpc].pos.x > 1000.0f && g_NPC[nCntNpc].move.x > 0)
						{
							g_NPC[nCntNpc].move.x = 0.0f;
							g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;
						}
						if (g_NPC[nCntNpc].pos.z < -1000.0f && g_NPC[nCntNpc].move.z < 0 ||
							g_NPC[nCntNpc].pos.z > 1000.0f && g_NPC[nCntNpc].move.z > 0)
						{
							g_NPC[nCntNpc].move.z = 0.0f;
							g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;
						}

						g_NPC[nCntNpc].nMoveCount++;
						if (g_NPC[nCntNpc].nMoveCount % ((rand() % 10) + 200) == 0)
						{
							g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;
						}

						g_NPC[nCntNpc].rot.y = RotOverwhelming(g_NPC[nCntNpc].rot.y);

						break;
					case AI_CHASE://追跡
						if ((fabs(pPlayer->pos.x - g_NPC[nCntNpc].pos.x) <= CHASE_RANGE ||
							fabs(pPlayer->pos.z - g_NPC[nCntNpc].pos.z) <= CHASE_RANGE) &&
							CollisionMeshWall(&g_NPC[nCntNpc].pos, &pPlayer->pos) == false)
						{
							float rotY = 
								atan2f(pPlayer->OldPos.x - g_NPC[nCntNpc].pos.x, pPlayer->OldPos.z - g_NPC[nCntNpc].pos.z);

							g_NPC[nCntNpc].move.x = sinf(rotY) * NPC_MOVE_SPEED;
							g_NPC[nCntNpc].move.z = cosf(rotY) * NPC_MOVE_SPEED;
							g_NPC[nCntNpc].rot.y = rotY + D3DX_PI;
							//弾の発射
							g_NPC[nCntNpc].nCntBullet++;
							if (g_NPC[nCntNpc].nCntBullet % 100 == 0)
							{
								SetBullet(D3DXVECTOR3(g_NPC[nCntNpc].pos.x, 15.0f, g_NPC[nCntNpc].pos.z),
									g_NPC[nCntNpc].rot,
									D3DXVECTOR3(5.0f, 0.0f, 5.0f),
									3.0f,
									3.0f,
									BULLETTYPE_ENEMY);

							}

						}
						else
						{
							g_NPC[nCntNpc].nCntBullet = -1;

							g_NPC[nCntNpc].move.x = sinf(g_NPC[nCntNpc].rot.y + D3DX_PI) * NPC_MOVE_SPEED;
							g_NPC[nCntNpc].move.z = cosf(g_NPC[nCntNpc].rot.y + D3DX_PI) * NPC_MOVE_SPEED;

							//移動係数の加算
							g_NPC[nCntNpc].move.x += (0.0f - g_NPC[nCntNpc].move.x) * 0.2f;
							g_NPC[nCntNpc].move.z += (0.0f - g_NPC[nCntNpc].move.z) * 0.2f;

							if (g_NPC[nCntNpc].pos.x < -1000.0f && g_NPC[nCntNpc].move.x < 0 ||
								g_NPC[nCntNpc].pos.x > 1000.0f && g_NPC[nCntNpc].move.x > 0)
							{
								g_NPC[nCntNpc].move.x = 0.0f;
								g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;
							}
							if (g_NPC[nCntNpc].pos.z < -1000.0f && g_NPC[nCntNpc].move.z < 0 ||
								g_NPC[nCntNpc].pos.z > 1000.0f && g_NPC[nCntNpc].move.z > 0)
							{
								g_NPC[nCntNpc].move.z = 0.0f;
								g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;
							}

							g_NPC[nCntNpc].nMoveCount++;
							if (g_NPC[nCntNpc].nMoveCount % ((rand() % 10) + 200) == 0)
							{
								g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;
							}

							g_NPC[nCntNpc].rot.y = RotOverwhelming(g_NPC[nCntNpc].rot.y);
						}

						break;
					}

					//moveの量だけposを動かす
					g_NPC[nCntNpc].pos += g_NPC[nCntNpc].move;

					if (CollisionMeshWall(&g_NPC[nCntNpc].pos, &g_NPC[nCntNpc].posOld) == true)
					{//内壁の当たり判定
						g_NPC[nCntNpc].pos = g_NPC[nCntNpc].posOld;
						g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;

					}

					break;

				case NPCSTATE_DAMAGE:			//ダメージ状態
					g_NPC[nCntNpc].move.x = 0.0f;
					g_NPC[nCntNpc].move.z = 0.0f;
					g_NPC[nCntNpc].nCntMove++;

					if (g_NPC[nCntNpc].nCntMove >= 150)
					{
						g_NPC[nCntNpc].state = NPCSTATE_MOVE;
						g_NPC[nCntNpc].nCntMove = 0;
						float rotY =
							atan2f(pPlayer->OldPos.x - g_NPC[nCntNpc].pos.x, pPlayer->OldPos.z - g_NPC[nCntNpc].pos.z);
						g_NPC[nCntNpc].rot.y = rotY + D3DX_PI;


					}
					break;
				}

				//影の更新
				SetPositionShadow(g_NPC[nCntNpc].nIdxShadow, D3DXVECTOR3(g_NPC[nCntNpc].pos.x, 0.0f, g_NPC[nCntNpc].pos.z));
				SetSizeShadow(g_NPC[nCntNpc].nIdxShadow, g_NPC[nCntNpc].pos.y, 5.0f);

				//アニメーション
				if (fabs(g_NPC[nCntNpc].move.x) >= 0.1f ||
					fabs(g_NPC[nCntNpc].move.z) >= 0.1f)
				{
					for (int nCntModel = 0; nCntModel < PARTS_NUM_NPC; nCntModel++)
					{
						g_NPC[nCntNpc].aModel[nCntModel].nMotionCount++;

						if (g_NPC[nCntNpc].aModel[nCntModel].nMotionCount % g_NPC[nCntNpc].aModel[nCntModel].motion.nKeyFrame == 0)
						{
							g_NPC[nCntNpc].aModel[nCntModel].nMotionNum = (g_NPC[nCntNpc].aModel[nCntModel].nMotionNum + 1) % 2;

						}

						g_NPC[nCntNpc].aModel[nCntModel].rot +=
							(g_NPC[nCntNpc].aModel[nCntModel].motion.motion0[g_NPC[nCntNpc].aModel[nCntModel].nMotionNum]
								- g_NPC[nCntNpc].aModel[nCntModel].rot) / (g_NPC[nCntNpc].aModel[nCntModel].motion.nKeyFrame * 1.0f);
					}
				}
				else
				{
					g_NPC[nCntNpc].aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//体
					g_NPC[nCntNpc].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//頭
					g_NPC[nCntNpc].aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 1.0f);//右腕
					g_NPC[nCntNpc].aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右手
					g_NPC[nCntNpc].aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, -1.0f);//左腕
					g_NPC[nCntNpc].aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左手
					g_NPC[nCntNpc].aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右腿
					g_NPC[nCntNpc].aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右足
					g_NPC[nCntNpc].aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左腿
					g_NPC[nCntNpc].aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左足
					g_NPC[nCntNpc].aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//武器

				}
			}

			//// ライトの方向の設定
			//D3DXVECTOR3 vecDir;
			//D3DXVec3Normalize(&vecDir, &g_NPC[nCntNpc].rot);
			//g_NPC[nCntNpc].light.Direction = vecDir;


		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawNpc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータのポインタ

	for (int nCntNpc = 0; nCntNpc < MAX_NUM_NPC; nCntNpc++)
	{
		if (g_NPC[nCntNpc].bUse == true)
		{

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_NPC[nCntNpc].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_NPC[nCntNpc].rot.y,
				g_NPC[nCntNpc].rot.x,
				g_NPC[nCntNpc].rot.z);

			D3DXMatrixMultiply(&g_NPC[nCntNpc].mtxWorld,
				&g_NPC[nCntNpc].mtxWorld,
				&mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_NPC[nCntNpc].pos.x,
				g_NPC[nCntNpc].pos.y,
				g_NPC[nCntNpc].pos.z);

			D3DXMatrixMultiply(&g_NPC[nCntNpc].mtxWorld,
				&g_NPC[nCntNpc].mtxWorld,
				&mtxTrans);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_NPC[nCntNpc].mtxWorld);

			for (int nCntModel = 0; nCntModel < PARTS_NUM_PLAYER; nCntModel++)
			{
				if (g_NPC[nCntNpc].aModel[nCntModel].nIdxModelParent == -1)
				{//親モデルがなければ
					mtxParent = g_NPC[nCntNpc].mtxWorld;
				}
				else
				{
					mtxParent = g_NPC[nCntNpc].aModel[g_NPC[nCntNpc].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_NPC[nCntNpc].aModel[nCntModel].rot.y,
					g_NPC[nCntNpc].aModel[nCntModel].rot.x,
					g_NPC[nCntNpc].aModel[nCntModel].rot.z);

				D3DXMatrixMultiply(&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld,
					&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld,
					&mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans,
					g_NPC[nCntNpc].aModel[nCntModel].pos.x,
					g_NPC[nCntNpc].aModel[nCntModel].pos.y,
					g_NPC[nCntNpc].aModel[nCntModel].pos.z);

				D3DXMatrixMultiply(&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld,
					&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld,
					&mtxTrans);

				//親のマトリックスを掛け合わせる
				D3DXMatrixMultiply(&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld,
					&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld,
					&mtxParent);

				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_NPC[nCntNpc].aModel[nCntModel].mtxWorld);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_NPC[nCntNpc].aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_NPC[nCntNpc].aModel[nCntModel].nNumMat; nCntMat++)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					/*テクスチャの設定*/
					pDevice->SetTexture(0, NULL);//テクスチャの設定(使わなければNULLを入れる)

					 // モデル(パーツ)の描画
					g_NPC[nCntNpc].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}

				// マテリアルをデフォルトに戻す
				pDevice->SetMaterial(&matDef);

			}
		}
	}

}
//=============================================================================
// 弾以外との当たり判定の処理
//=============================================================================
bool CollisionNpc(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pOldPos, D3DXVECTOR3 *pMove,D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax)
{
	//変数宣言
	bool bLand = false;

	for (int nCntData = 0; nCntData < MAX_NUM_NPC; nCntData++)
	{
		if (g_NPC[nCntData].bUse == true)
		{
			if (g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z <= pPos->z + pVtxMax->z&&
				g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z >= pPos->z + pVtxMin->z)
			{
				if (g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x <= pPos->x + pVtxMax->x&&
					g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x >= pOldPos->x + pVtxMax->x)
				{//左から右
					pPos->x = g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x - pVtxMax->x;
					pMove->x = 0.0f;
				}
				if (g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x >= pPos->x + pVtxMin->x&&
					g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x <= pOldPos->x + pVtxMin->x)
				{//右から左
					pPos->x = g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x - pVtxMin->x;
					pMove->x = 0.0f;
				}
			}

			if (g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x <= pPos->x + pVtxMax->x&&
				g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x >= pPos->x + pVtxMin->x)
			{
				if (g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z >= pOldPos->z + pVtxMax->z)
				{//手前から奥
					pPos->z = g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z - pVtxMax->z;
					pMove->z = 0.0f;
				}
				if (g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z >= pPos->z + pVtxMin->z&&
					g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z <= pOldPos->z + pVtxMin->z)
				{//奥から手前
					pPos->z = g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z - pVtxMin->z;
					pMove->z = 0.0f;
				}
			}
		}
	}
	return bLand;
}

//=============================================================================
// 弾との当たり判定の処理
//=============================================================================

int CollisionBullet(D3DXVECTOR3 *pPos,D3DXVECTOR3 *pOldPos,D3DXVECTOR3 *pMove,D3DXVECTOR3 *pVtxMin,D3DXVECTOR3 *pVtxMax, int *pDeleteIdxNpc)
{
	for (int nCntData = 0; nCntData < MAX_NUM_NPC; nCntData++)
	{
		if (g_NPC[nCntData].bUse == true)
		{
			if (g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z <= pPos->z + pVtxMax->z&&
				g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z >= pPos->z + pVtxMin->z)
			{
				if (g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x <= pPos->x + pVtxMax->x&&
					g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x >= pOldPos->x + pVtxMax->x)
				{//左から右
					pDeleteIdxNpc = (int*)nCntData;

					return nCntData;

				}
				if (g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x >= pPos->x + pVtxMin->x&&
					g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x <= pOldPos->x + pVtxMin->x)
				{//右から左
					pDeleteIdxNpc = (int*)nCntData;

					return nCntData;

				}
			}

			if (g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x <= pPos->x + pVtxMax->x&&
				g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x >= pPos->x + pVtxMin->x)
			{
				if (g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z >= pOldPos->z + pVtxMax->z)
				{//手前から奥
					pDeleteIdxNpc = (int*)nCntData;

					return nCntData;

				}
				if (g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z >= pPos->z + pVtxMin->z&&
					g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z <= pOldPos->z + pVtxMin->z)
				{//奥から手前
					pDeleteIdxNpc = (int*)nCntData;

					return nCntData;
				}
			}
		}
	}
	return -1;
}

//=============================================================================
// 最大・最小の頂点座標を取得
//=============================================================================
void SetNpcVertex(int nCntNpc)
{
	//変数宣言
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファへのポインタ
	g_NPC[nCntNpc].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_NPC[nCntNpc].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);
	for (int nCntParts = 0; nCntParts < PARTS_NUM_NPC; nCntParts++)
	{

		//頂点数の取得
		nNumVtx = g_NPC[nCntNpc].aModel[nCntParts].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_NPC[nCntNpc].aModel[nCntParts].pMesh->GetFVF());
		//頂点バッファのロック
		g_NPC[nCntNpc].aModel[nCntParts].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

			//頂点を比較してモデルの最小・最大を抜き出す
			//x
			if (g_NPC[nCntNpc].VtxMin.x > vtx.x)
			{
				g_NPC[nCntNpc].VtxMin.x = vtx.x;
			}
			if (g_NPC[nCntNpc].VtxMax.x < vtx.x)
			{
				g_NPC[nCntNpc].VtxMax.x = vtx.x;
			}

			//y
			if (g_NPC[nCntNpc].VtxMin.y > vtx.y)
			{
				g_NPC[nCntNpc].VtxMin.y = vtx.y;
			}
			if (g_NPC[nCntNpc].VtxMax.y < vtx.y)
			{
				g_NPC[nCntNpc].VtxMax.y = vtx.y;
			}

			//z
			if (g_NPC[nCntNpc].VtxMin.z > vtx.z)
			{
				g_NPC[nCntNpc].VtxMin.z = vtx.z;
			}
			if (g_NPC[nCntNpc].VtxMax.z < vtx.z)
			{
				g_NPC[nCntNpc].VtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;		//サイズ分ポインタを進める
		}
		//アンロック
		g_NPC[nCntNpc].aModel[nCntParts].pMesh->UnlockVertexBuffer();
	}
}

//=============================================================================
// npcを消す処理
//=============================================================================
void DeleteNpc(int nIdxNpc)
{
	//g_NPC[nIdxNpc].bUse = false;
	//DeleteShadow(g_NPC[nIdxNpc].nIdxShadow);
	g_NPC[nIdxNpc].state = NPCSTATE_DAMAGE;
	g_NPC[nIdxNpc].nCntMove = 0;
	PlaySound(SOUND_LABEL_SE004);
}

//=============================================================================
// npcの数を調べる処理
//=============================================================================
bool CountUseNpc(void)
{
	int nCntNumNpc = 0;
	for (int nCntData = 0; nCntData < MAX_NUM_NPC; nCntData++)
	{
		if (g_NPC[nCntData].bUse == true)
		{
			nCntNumNpc++;
		}
	}

	if (nCntNumNpc != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//
//
//
NPC *GetNPC(void)
{
	return &g_NPC[0];
}