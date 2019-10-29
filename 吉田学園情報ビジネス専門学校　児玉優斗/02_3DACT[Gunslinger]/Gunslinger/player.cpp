//=============================================================================
//
// モデル処理 [Player.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "player.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PLAYER g_Player;
int g_nCntBullet;
//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_Player.aModel[0].FireName = PLAYER_FILENAME0;
	g_Player.aModel[1].FireName = PLAYER_FILENAME1;
	g_Player.aModel[2].FireName = PLAYER_FILENAME2;
	g_Player.aModel[3].FireName = PLAYER_FILENAME3;
	g_Player.aModel[4].FireName = PLAYER_FILENAME4;
	g_Player.aModel[5].FireName = PLAYER_FILENAME5;
	g_Player.aModel[6].FireName = PLAYER_FILENAME6;
	g_Player.aModel[7].FireName = PLAYER_FILENAME7;
	g_Player.aModel[8].FireName = PLAYER_FILENAME8;
	g_Player.aModel[9].FireName = PLAYER_FILENAME9;
	g_Player.aModel[10].FireName = PLAYER_FILENAME10;

	// Xファイルの読み込み
	for (int nCntParts = 0; nCntParts < PARTS_NUM_PLAYER; nCntParts++)
	{
		D3DXLoadMeshFromX(g_Player.aModel[nCntParts].FireName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aModel[nCntParts].pBuffMat,
			NULL,
			&g_Player.aModel[nCntParts].nNumMat,
			&g_Player.aModel[nCntParts].pMesh);
	}

	/*当たり判定の設定*/
	SetPlayerVertex();

	// 位置・向きの初期設定
	g_Player.pos = D3DXVECTOR3(900.0f, 0.0f, -900.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);

	//移動量・回転量の初期化
	g_Player.move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//モデルの座標設定
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 16.0f, 0.0f);//体
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 14.5f, 0.0f);//頭
	g_Player.aModel[2].pos = D3DXVECTOR3(-5.0f, 11.5f, 0.0f);//右腕
	g_Player.aModel[3].pos = D3DXVECTOR3(-13.0f, 0.0f, 0.0f);//右手
	g_Player.aModel[4].pos = D3DXVECTOR3(5.0f, 11.5f, 0.0f);//左腕
	g_Player.aModel[5].pos = D3DXVECTOR3(13.0f, 0.0f, 0.0f);//左手
	g_Player.aModel[6].pos = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);//右腿
	g_Player.aModel[7].pos = D3DXVECTOR3(0.0f, -12.0f, 0.0f);//右足
	g_Player.aModel[8].pos = D3DXVECTOR3(3.0f, 0.0f, 0.0f);  //左腿
	g_Player.aModel[9].pos = D3DXVECTOR3(0.0f, -12.0f, 0.0f);//左足
	g_Player.aModel[10].pos = D3DXVECTOR3(2.0f, 0.0f, 0.0f);//武器

	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//体
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//頭
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右腕
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右手
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左腕
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左手
	g_Player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右腿
	g_Player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右足
	g_Player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左腿
	g_Player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左足
	g_Player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//武器

	g_Player.aModel[0].nIdxModelParent = -1;//体
	g_Player.aModel[1].nIdxModelParent = 0;//頭
	g_Player.aModel[2].nIdxModelParent = 0;//右腕
	g_Player.aModel[3].nIdxModelParent = 2;//右手
	g_Player.aModel[4].nIdxModelParent = 0;//左腕
	g_Player.aModel[5].nIdxModelParent = 4;//左手
	g_Player.aModel[6].nIdxModelParent = 0;//右腿
	g_Player.aModel[7].nIdxModelParent = 6;//右足
	g_Player.aModel[8].nIdxModelParent = 0;//左腿
	g_Player.aModel[9].nIdxModelParent = 8;//左足
	g_Player.aModel[10].nIdxModelParent = 5;//武器

	g_Player.nIdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x,1.0f, g_Player.pos.z),D3DXVECTOR3(0.0f,0.0f,0.0f));
	SetArrow(D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_Player.nChargeTime = 0;
	g_Player.bUse = true;

	g_Player.aModel[0].motion.motion0[0] = {D3DXVECTOR3(-0.27f, -0.16f, 0.00f)};
	g_Player.aModel[1].motion.motion0[0] = { D3DXVECTOR3(0.09f, -0.25f, 0.00f) };
	g_Player.aModel[2].motion.motion0[0] = { D3DXVECTOR3(1.51f, 0.00f, 1.09f) };
	g_Player.aModel[3].motion.motion0[0] = { D3DXVECTOR3(0.00f, -1.09f, 0.00f) };
	g_Player.aModel[4].motion.motion0[0] = { D3DXVECTOR3(-1.51f, 0.00f, -1.09f) };
	g_Player.aModel[5].motion.motion0[0] = { D3DXVECTOR3(0.00f, 1.09f, 0.00f) };
	g_Player.aModel[6].motion.motion0[0] = { D3DXVECTOR3(-1.06f, 0.00f, 0.00f) };
	g_Player.aModel[7].motion.motion0[0] = { D3DXVECTOR3(-0.97f, 0.00f, 0.00f) };
	g_Player.aModel[8].motion.motion0[0] = { D3DXVECTOR3(1.16f, 0.00f, 0.00f) };
	g_Player.aModel[9].motion.motion0[0] = { D3DXVECTOR3(0.00f, 0.00f, 0.00f) };
	g_Player.aModel[10].motion.motion0[0] = { D3DXVECTOR3(0.00f, 0.00f, 1.45f) };

	g_Player.aModel[0].motion.motion0[1] = { D3DXVECTOR3(-0.27f, 0.14f, 0.00f) };
	g_Player.aModel[1].motion.motion0[1] = { D3DXVECTOR3(0.10f, 0.25f, 0.00f) };
	g_Player.aModel[2].motion.motion0[1] = { D3DXVECTOR3(-1.52f, 0.00f, 1.09f) };
	g_Player.aModel[3].motion.motion0[1] = { D3DXVECTOR3(0.00f, -1.09f, 0.00f) };
	g_Player.aModel[4].motion.motion0[1] = { D3DXVECTOR3(1.52f, 0.00f, -1.09f) };
	g_Player.aModel[5].motion.motion0[1] = { D3DXVECTOR3(0.00f, 1.09f, 0.00f) };
	g_Player.aModel[6].motion.motion0[1] = { D3DXVECTOR3(1.16f, 0.00f, 0.00f) };
	g_Player.aModel[7].motion.motion0[1] = { D3DXVECTOR3(-0.05f, 0.00f, 0.00f) };
	g_Player.aModel[8].motion.motion0[1] = { D3DXVECTOR3(-1.07f, 0.00f, 0.00f) };
	g_Player.aModel[9].motion.motion0[1] = { D3DXVECTOR3(-0.92f, 0.00f, 0.00f) };
	g_Player.aModel[10].motion.motion0[1] = { D3DXVECTOR3(0.50f, 0.00f, -0.97f) };

	g_Player.aModel[0].motion.nKeyFrame = 20;
	g_Player.aModel[1].motion.nKeyFrame = 20;
	g_Player.aModel[2].motion.nKeyFrame = 20;
	g_Player.aModel[3].motion.nKeyFrame = 20;
	g_Player.aModel[4].motion.nKeyFrame = 20;
	g_Player.aModel[5].motion.nKeyFrame = 20;
	g_Player.aModel[6].motion.nKeyFrame = 20;
	g_Player.aModel[7].motion.nKeyFrame = 20;
	g_Player.aModel[8].motion.nKeyFrame = 20;
	g_Player.aModel[9].motion.nKeyFrame = 20;
	g_Player.aModel[10].motion.nKeyFrame = 20;

	g_nCntBullet = 0;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	// メッシュの解放
	for (int nCntMat = 0; nCntMat < PARTS_NUM_PLAYER; nCntMat++)
	{
		if (g_Player.aModel[nCntMat].pMesh != NULL)
		{
			g_Player.aModel[nCntMat].pMesh->Release();
			g_Player.aModel[nCntMat].pMesh = NULL;
		}
		/*テクスチャの解放*/
		//マテリアルの解放
		if (g_Player.aModel[nCntMat].pBuffMat != NULL)
		{
			g_Player.aModel[nCntMat].pBuffMat->Release();
			g_Player.aModel[nCntMat].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	//変数宣言
	Camera *pCamera;
	pCamera = GetCamera();


	if (g_Player.bUse == true)
	{
		//OldPosに前回のPosを代入
		g_Player.OldPos = g_Player.pos;

		//モデルの移動と回転
		if (GetKeyboardPress(DIK_A) == true)//←
		{
			if (GetKeyboardPress(DIK_S) == true)//↓
			{
				g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI * 0.25f) - g_Player.rot.y);
				g_Player.move.x += sinf((D3DX_PI * -0.75f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
				g_Player.move.z += cosf((D3DX_PI * -0.75f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_W) == true)//↑
			{
				g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI * 0.75f) - g_Player.rot.y);
				g_Player.move.x += sinf((D3DX_PI * -0.25f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
				g_Player.move.z += cosf((D3DX_PI * -0.25f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			}
			else
			{
				g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI * 0.5f) - g_Player.rot.y);
				g_Player.move.x += sinf((D3DX_PI * -0.5f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
				g_Player.move.z += cosf((D3DX_PI * -0.5f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)//→
		{
			if (GetKeyboardPress(DIK_S) == true)//↓
			{
				g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI * -0.25f) - g_Player.rot.y);
				g_Player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
				g_Player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_W) == true)//↑
			{
				g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI * -0.75f) - g_Player.rot.y);
				g_Player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
				g_Player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			}
			else
			{
				g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI * -0.5f) - g_Player.rot.y);
				g_Player.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
				g_Player.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)//↓
		{
			g_Player.rotMove.y = (pCamera->rot.y - g_Player.rot.y);
			g_Player.move.x += sinf((D3DX_PI)+pCamera->rot.y) * PLAYER_MOVE_SPEED;
			g_Player.move.z += cosf((D3DX_PI)+pCamera->rot.y) * PLAYER_MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_W) == true)//↑
		{
			g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI)-g_Player.rot.y);
			g_Player.move.x += sinf((0.0f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			g_Player.move.z += cosf((0.0f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
		}

		//移動係数の加算
		g_Player.move += (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - g_Player.move) * 0.05f;

		if (g_Player.pos.x < -1000.0f && g_Player.move.x < 0 ||
			g_Player.pos.x > 1000.0f && g_Player.move.x > 0)
		{
			g_Player.move.x = 0.0f;
		}
		if (g_Player.pos.z < -1000.0f && g_Player.move.z < 0 ||
			g_Player.pos.z > 1000.0f && g_Player.move.z > 0)
		{
			g_Player.move.z = 0.0f;
		}
		if (g_Player.pos.y < 0.0f && g_Player.move.y < 0)
		{
			g_Player.move.y = 0.0f;
		}

		//エフェクト設置
		if (g_Player.move.x > 0.5f ||
			g_Player.move.x < -0.5f ||
			g_Player.move.z > 0.5f ||
			g_Player.move.z < -0.5f)
		{
			SetEffect(D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.y) * 7.0f, g_Player.pos.y, g_Player.pos.z + cosf(g_Player.rot.y) * 7.0f),
				g_Player.rot,
				D3DXCOLOR(0.0f, 0.7f, 1.0f, 1.0f),
				3.0f,
				2.0f);
		}

		//moveの量だけposを動かす
		g_Player.pos += g_Player.move;
		if (CollisionMeshWall(&g_Player.pos, &g_Player.OldPos) == true)
		{
			g_Player.pos = g_Player.OldPos;
			//g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		//回転速度の丸め込み
		g_Player.rotMove.y = RotOverwhelming(g_Player.rotMove.y);

		//回転量の加算
		g_Player.rot.y += g_Player.rotMove.y * PLAYER_ROTMOVE_COEFFICIENT;
		g_Player.rot.y = RotOverwhelming(g_Player.rot.y);

		//回転量のリセット
		g_Player.rotMove.y = 0.0f;

		/*当たり判定*/
		if (CollisionNpc(&g_Player.pos,
			&g_Player.OldPos,
			&g_Player.move,
			&g_Player.VtxMin,
			&g_Player.VtxMax) == true)
		{

		}
		if (CollisionModel(&g_Player.pos,
			&g_Player.OldPos,
			&g_Player.move,
			&g_Player.VtxMin,
			&g_Player.VtxMax) == true)
		{
			g_Player.nChargeTime++;
		}
		else
		{
			g_Player.nChargeTime = 0;

		}

		if (g_Player.nChargeTime == 50)
		{
			SetGameState(GAMESTATE_END);
			//g_Player.nChargeTime = 0;
		}

		if (CollisionPiller(&g_Player.pos, &g_Player.OldPos, &g_Player.move, &g_Player.VtxMin, &g_Player.VtxMax) == true)
		{

		}

		//影の更新
		SetPositionShadow(g_Player.nIdxShadow, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));
		SetSizeShadow(g_Player.nIdxShadow, g_Player.pos.y, 20.0f);

		//矢印の更新
		SetPositionArrow(D3DXVECTOR3(g_Player.pos.x, 10.0f, g_Player.pos.z));

		//弾の発射
		if (GetKeyboardTrigger(DIK_RETURN) == true ||
			GetKeyboardTrigger(DIK_SPACE) == true )
		{
			SetBullet(D3DXVECTOR3(g_Player.pos.x - sinf(g_Player.rot.y) * 15.0f, g_Player.pos.y + 20.0f, g_Player.pos.z - cosf(g_Player.rot.y) * 15.0f),
				g_Player.rot,
				D3DXVECTOR3(5.0f, 0.0f, 5.0f),
				3.0f,
				3.0f,
				BULLETTYPE_PLAYER);
			SetBullet(D3DXVECTOR3(g_Player.pos.x - sinf(g_Player.rot.y) * 15.0f, g_Player.pos.y + 20.0f, g_Player.pos.z - cosf(g_Player.rot.y) * 15.0f),
				D3DXVECTOR3(g_Player.rot.x, g_Player.rot.y + 0.1f, g_Player.rot.z),
				D3DXVECTOR3(5.0f, 0.0f, 5.0f),
				3.0f,
				3.0f,
				BULLETTYPE_PLAYER);
			SetBullet(D3DXVECTOR3(g_Player.pos.x - sinf(g_Player.rot.y) * 15.0f, g_Player.pos.y + 20.0f, g_Player.pos.z - cosf(g_Player.rot.y) * 15.0f),
				D3DXVECTOR3(g_Player.rot.x, g_Player.rot.y - 0.1f, g_Player.rot.z),
				D3DXVECTOR3(5.0f, 0.0f, 5.0f),
				3.0f,
				3.0f,
				BULLETTYPE_PLAYER);

			PlaySound(SOUND_LABEL_SE000);
		}



		//アニメーション
		if (fabs(g_Player.move.x) >= 0.1f ||
			fabs(g_Player.move.z) >= 0.1f)
		{
			for (int nCntModel = 0; nCntModel < PARTS_NUM_PLAYER; nCntModel++)
			{
				g_Player.aModel[nCntModel].nMotionCount++;

				if (g_Player.aModel[nCntModel].nMotionCount % g_Player.aModel[nCntModel].motion.nKeyFrame == 0)
				{
					g_Player.aModel[nCntModel].nMotionNum = (g_Player.aModel[nCntModel].nMotionNum + 1) % 2;

				}
				g_Player.aModel[nCntModel].rot +=
					((g_Player.aModel[nCntModel].motion.motion0[g_Player.aModel[nCntModel].nMotionNum]
						- g_Player.aModel[nCntModel].rot) / (g_Player.aModel[nCntModel].motion.nKeyFrame * 1.0f));

				RotOverwhelming(g_Player.aModel[nCntModel].rot.x);
				RotOverwhelming(g_Player.aModel[nCntModel].rot.y);
				RotOverwhelming(g_Player.aModel[nCntModel].rot.z);

			}
		}
		else
		{
			g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//体
			g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//頭
			g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 1.0f);//右腕
			g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右手
			g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, -1.0f);//左腕
			g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左手
			g_Player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右腿
			g_Player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右足
			g_Player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左腿
			g_Player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//左足
			g_Player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//武器

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans,mtxParent;
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータのポインタ

	if (g_Player.bUse == true)
	{


		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Player.rot.y,
			g_Player.rot.x,
			g_Player.rot.z);

		D3DXMatrixMultiply(&g_Player.mtxWorld,
			&g_Player.mtxWorld,
			&mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			g_Player.pos.x,
			g_Player.pos.y,
			g_Player.pos.z);

		D3DXMatrixMultiply(&g_Player.mtxWorld,
			&g_Player.mtxWorld,
			&mtxTrans);
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

		for (int nCntModel = 0; nCntModel < PARTS_NUM_PLAYER; nCntModel++)
		{
			if (g_Player.aModel[nCntModel].nIdxModelParent == -1)
			{//親モデルがなければ
				mtxParent = g_Player.mtxWorld;
			}
			else
			{
				mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Player.aModel[nCntModel].rot.y,
				g_Player.aModel[nCntModel].rot.x,
				g_Player.aModel[nCntModel].rot.z);

			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld,
				&g_Player.aModel[nCntModel].mtxWorld,
				&mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Player.aModel[nCntModel].pos.x,
				g_Player.aModel[nCntModel].pos.y,
				g_Player.aModel[nCntModel].pos.z);

			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld,
				&g_Player.aModel[nCntModel].mtxWorld,
				&mtxTrans);

			//親のマトリックスを掛け合わせる
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld,
				&g_Player.aModel[nCntModel].mtxWorld,
				&mtxParent);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				/*テクスチャの設定*/
				pDevice->SetTexture(0, NULL);//テクスチャの設定(使わなければNULLを入れる)

											 // モデル(パーツ)の描画
				g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);

		}
	}
}
//=============================================================================
// 構造体の取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

//=============================================================================
// 最大・最小の頂点座標を取得
//=============================================================================
void SetPlayerVertex(void)
{
	//変数宣言
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファへのポインタ
	g_Player.VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Player.VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//頂点数の取得
	for (int nCntParts = 0; nCntParts < PARTS_NUM_PLAYER; nCntParts++)
	{
		nNumVtx = g_Player.aModel[nCntParts].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntParts].pMesh->GetFVF());
		//頂点バッファのロック
		g_Player.aModel[nCntParts].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	/*	pVtxBuff += */
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

														//頂点を比較してモデルの最小・最大を抜き出す
														//x
			if (g_Player.VtxMin.x > vtx.x)
			{
				g_Player.VtxMin.x = vtx.x;
			}
			if (g_Player.VtxMax.x < vtx.x)
			{
				g_Player.VtxMax.x = vtx.x;
			}

			//y
			if (g_Player.VtxMin.y > vtx.y)
			{
				g_Player.VtxMin.y = vtx.y;
			}
			if (g_Player.VtxMax.y < vtx.y)
			{
				g_Player.VtxMax.y = vtx.y;
			}

			//z
			if (g_Player.VtxMin.z > vtx.z)
			{
				g_Player.VtxMin.z = vtx.z;
			}
			if (g_Player.VtxMax.z < vtx.z)
			{
				g_Player.VtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//サイズ分ポインタを進める
		}
		//アンロック
		g_Player.aModel[nCntParts].pMesh->UnlockVertexBuffer();


	}
}

bool CollisionPlayer(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax)
{
	if (g_Player.bUse == true)
	{


		if (g_Player.VtxMin.z + g_Player.pos.z <= pPos->z + pVtxMax->z&&
			g_Player.VtxMax.z + g_Player.pos.z >= pPos->z + pVtxMin->z)
		{
			if (g_Player.VtxMin.x + g_Player.pos.x <= pPos->x + pVtxMax->x&&
				g_Player.VtxMin.x + g_Player.pos.x >= pOldPos->x + pVtxMax->x)
			{//左から右
				SetExplosion(g_Player.pos,
					g_Player.rot,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					6.0f,
					6.0f);

				return true;
			}
			if (g_Player.VtxMax.x + g_Player.pos.x >= pPos->x + pVtxMin->x&&
				g_Player.VtxMax.x + g_Player.pos.x <= pOldPos->x + pVtxMin->x)
			{//右から左
				SetExplosion(g_Player.pos,
					g_Player.rot,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					6.0f,
					6.0f);

				return true;
			}
		}

		if (g_Player.VtxMin.x + g_Player.pos.x <= pPos->x + pVtxMax->x&&
			g_Player.VtxMax.x + g_Player.pos.x >= pPos->x + pVtxMin->x)
		{
			if (g_Player.VtxMin.z + g_Player.pos.z <= pPos->z + pVtxMax->z&&
				g_Player.VtxMin.z + g_Player.pos.z >= pOldPos->z + pVtxMax->z)
			{//手前から奥
				SetExplosion(g_Player.pos,
					g_Player.rot,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					6.0f,
					6.0f);

				return true;
			}
			if (g_Player.VtxMax.z + g_Player.pos.z >= pPos->z + pVtxMin->z&&
				g_Player.VtxMax.z + g_Player.pos.z <= pOldPos->z + pVtxMin->z)
			{//奥から手前
				SetExplosion(g_Player.pos,
					g_Player.rot,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					6.0f,
					6.0f);

				return true;
			}
		}
	}
			return false;
}

//=============================================================================
// 自分を消す関数
//=============================================================================
void DeletePlayer(void)
{
	g_Player.bUse = false;
	SetExplosion(g_Player.pos,
		g_Player.rot,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		20.0f,
		20.0f);

	PlaySound(SOUND_LABEL_SE005);

}