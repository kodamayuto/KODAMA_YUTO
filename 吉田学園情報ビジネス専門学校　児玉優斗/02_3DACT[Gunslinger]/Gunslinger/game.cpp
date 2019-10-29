//*****************************************************************************
//
// ゲームの処理[game.cpp]
// Author : kodama Yuto
//     (:3 )三
//*****************************************************************************
//インクルードファイル
#include "game.h"
#include "fade.h"
#include "pause.h"
//#include"ranking.h"

//=============================================================================
//	グローバル変数宣言
//=============================================================================
GAMESTATE g_gamestate		  = GAMESTATE_NONE;		//ゲームの条件
int g_nCounterGameState;    						//カウンター

bool g_bPause;				//ポーズ処理用  true = ポーズ中
int g_nStage;
int g_nCntenter = 0;
//=============================================================================
//	初期化処理
//=============================================================================
void InitGame(void)
{
	InitPause();

	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	//影の初期化処理(影を使うものより先に置く)
	InitShadow();
	//メッシュフィールドの初期化処理
	InitMeshField();

	//メッシュウォールの初期化処理
	InitMeshWall();

	//メッシュシリンダーの初期化処理
	InitMeshCylinder();

	// 壁の初期化処理
	InitWall();

	//屋根の初期化処理
	InitRoof();

	//モデルの初期化処理
	InitModel();

	//柱の初期化処理
	InitPiller();

	//設置物の初期化処理
	InitObject();

	//NPCの初期化処理
	InitNpc();

	//操作キャラの初期化処理
	InitPlayer();

	//弾の初期化処理
	InitBullet();

	//爆発の初期化処理
	InitExplosion();

	//エフェクトの初期化処理
	InitEffect();

	//パーティクルの初期化処理
	InitParticle();

	//矢印の初期化処理
	InitArrow();

	//タイマーの初期化処理
	InitTimer();

	//マップの初期化処理
	InitMiniMap();

	//グローバル変数の初期化
	g_gamestate = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPause = false;
	g_nCntenter = 0;

	SetWall(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WALLTYPE_1, 1000.0f, 100.0f);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WALLTYPE_1, 1000.0f, 100.0f);
	SetWall(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f), WALLTYPE_1, 1000.0f, 100.0f);
	SetWall(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f), WALLTYPE_1, 1000.0f, 100.0f);


	SetRoof(D3DXVECTOR3(0.0f, 100.0f, 1000.0f), D3DXVECTOR3(-D3DX_PI / 4.0f, 0.0f, 0.0f), ROOFTYPE_1, 1000.0f, 1000.0f);
	SetRoof(D3DXVECTOR3(0.0f, 100.0f, -1000.0f), D3DXVECTOR3(-D3DX_PI / 4.0f, D3DX_PI, 0.0f), ROOFTYPE_1, 1000.0f, 1000.0f);
	SetRoof(D3DXVECTOR3(1000.0f, 100.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.0f, D3DX_PI / 2.0f, 0.0f), ROOFTYPE_1, 1000.0f, 1000.0f);
	SetRoof(D3DXVECTOR3(-1000.0f, 100.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.0f, -D3DX_PI / 2.0f, 0.0f), ROOFTYPE_1, 1000.0f, 1000.0f);

	SetMeshWall(D3DXVECTOR3(700.0f,0.0f,-900.0f),D3DXVECTOR3(0.0f,D3DX_PI * 0.5f,0.0f));
	SetMeshWall(D3DXVECTOR3(700.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(700.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(750.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.75f, 0.0f));
	SetMeshWall(D3DXVECTOR3(820.0f, 0.0f, -180.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(820.0f, 0.0f, 20.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(820.0f, 0.0f, 220.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(720.0f, 0.0f, 320.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(520.0f, 0.0f, 320.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(320.0f, 0.0f, 320.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(220.0f, 0.0f, 220.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(290.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.75f, 0.0f));
	SetMeshWall(D3DXVECTOR3(350.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(350.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(350.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(350.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(350.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(350.0f, 0.0f, -900.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));

	SetMeshWall(D3DXVECTOR3(800.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(700.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f,0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(500.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(400.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(500.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(700.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetMeshWall(D3DXVECTOR3(200.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(100.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-100.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-200.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-100.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(100.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, 900.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-600.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, 900.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));

	SetMeshWall(D3DXVECTOR3(200.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(100.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-100.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-200.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-100.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(100.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetMeshWall(D3DXVECTOR3(200.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(100.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-100.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-200.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-100.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(100.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));


	SetMeshWall(D3DXVECTOR3(-400.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-800.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetMeshWall(D3DXVECTOR3(-400.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-800.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//柱
	SetPiller(D3DXVECTOR3(1000.0f, 0.0f, -1000.0f));
	SetPiller(D3DXVECTOR3(1000.0f, 0.0f, -600.0f));
	SetPiller(D3DXVECTOR3(1000.0f, 0.0f, -200.0f));
	SetPiller(D3DXVECTOR3(1000.0f, 0.0f, 200.0f));
	SetPiller(D3DXVECTOR3(1000.0f, 0.0f, 600.0f));
	SetPiller(D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	SetPiller(D3DXVECTOR3(600.0f, 0.0f, 1000.0f));
	SetPiller(D3DXVECTOR3(200.0f, 0.0f, 1000.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, 1000.0f));
	SetPiller(D3DXVECTOR3(-600.0f, 0.0f, 1000.0f));
	SetPiller(D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f));

	SetPiller(D3DXVECTOR3(-1000.0f, 0.0f, 600.0f));
	SetPiller(D3DXVECTOR3(-1000.0f, 0.0f, 200.0f));
	SetPiller(D3DXVECTOR3(-1000.0f, 0.0f, -200.0f));
	SetPiller(D3DXVECTOR3(-1000.0f, 0.0f, -600.0f));
	SetPiller(D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f));

	SetPiller(D3DXVECTOR3(-600.0f, 0.0f, -1000.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, -1000.0f));
	SetPiller(D3DXVECTOR3(200.0f, 0.0f, -1000.0f));
	SetPiller(D3DXVECTOR3(600.0f, 0.0f, -1000.0f));

	SetPiller(D3DXVECTOR3(700.0f, 0.0f, -1000.0f));
	SetPiller(D3DXVECTOR3(700.0f, 0.0f, -400.0f));
	SetPiller(D3DXVECTOR3(820.0f, 0.0f, -280.0f));
	SetPiller(D3DXVECTOR3(820.0f, 0.0f, 320.0f));
	SetPiller(D3DXVECTOR3(220.0f, 0.0f, 320.0f));
	SetPiller(D3DXVECTOR3(220.0f, 0.0f, 120.0f));
	SetPiller(D3DXVECTOR3(350.0f, 0.0f, -15.0f));
	SetPiller(D3DXVECTOR3(350.0f, 0.0f, -1000.0f));

	SetPiller(D3DXVECTOR3(800.0f, 0.0f, 600.0f));
	SetPiller(D3DXVECTOR3(800.0f, 0.0f, 800.0f));
	SetPiller(D3DXVECTOR3(400.0f, 0.0f, 800.0f));
	SetPiller(D3DXVECTOR3(400.0f, 0.0f, 600.0f));

	SetPiller(D3DXVECTOR3(200.0f, 0.0f, 600.0f));
	SetPiller(D3DXVECTOR3(200.0f, 0.0f, 800.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, 800.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, 600.0f));

	SetPiller(D3DXVECTOR3(200.0f, 0.0f, -200.0f));
	SetPiller(D3DXVECTOR3(200.0f, 0.0f, -400.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, -400.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, -200.0f));

	SetPiller(D3DXVECTOR3(200.0f, 0.0f, -600.0f));
	SetPiller(D3DXVECTOR3(200.0f, 0.0f, -800.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, -800.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, -600.0f));

	SetPiller(D3DXVECTOR3(-400.0f, 0.0f, -200.0f));
	SetPiller(D3DXVECTOR3(-400.0f, 0.0f, -400.0f));
	SetPiller(D3DXVECTOR3(-800.0f, 0.0f, -400.0f));
	SetPiller(D3DXVECTOR3(-800.0f, 0.0f, -200.0f));

	SetPiller(D3DXVECTOR3(-400.0f, 0.0f, -600.0f));
	SetPiller(D3DXVECTOR3(-400.0f, 0.0f, -800.0f));
	SetPiller(D3DXVECTOR3(-800.0f, 0.0f, -800.0f));
	SetPiller(D3DXVECTOR3(-800.0f, 0.0f, -600.0f));

	SetPiller(D3DXVECTOR3(-500.0f, 0.0f, 1000.0f));
	SetPiller(D3DXVECTOR3(-500.0f, 0.0f, 0.0f));
	SetPiller(D3DXVECTOR3(-700.0f, 0.0f, 0.0f));
	SetPiller(D3DXVECTOR3(-700.0f, 0.0f, 1000.0f));

	PlaySound(SOUND_LABEL_BGM002);

}

//=============================================================================
//	終了処理
//=============================================================================
void UninitGame(void)
{
	UninitPause();

	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	//影の終了処理
	UninitShadow();

	//メッシュフィールドの終了処理
	UninitMeshField();

	//メッシュウォールの終了処理
	UninitMeshWall();

	//メッシュシリンダーの終了処理
	UninitMeshCylinder();


	// 壁の終了処理
	UninitWall();

	//屋根の終了処理
	UninitRoof();

	//モデルの終了処理
	UninitModel();

	//柱の終了処理
	UninitPiller();

	//設置物の終了処理
	UninitObject();

	//NPCの終了処理
	UninitNpc();

	//操作キャラの終了処理
	UninitPlayer();

	//弾の終了処理
	UninitBullet();

	//爆発の終了処理
	UninitExplosion();

	//エフェクトの終了処理
	UninitEffect();

	//パーティクルの終了処理
	UninitParticle();

	//矢印の終了処理
	UninitArrow();

	//タイマーの終了処理
	UninitTimer();

	//マップの終了処理
	UninitMiniMap();

}

//=============================================================================
//	更新処理
//=============================================================================
void UpdateGame(void)
{
	//変数宣言
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	//ポーズ　ON/OFF
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		PauseModeChange();
		SerectReset();
		DispReset();
	}


	if (g_bPause == false || g_gamestate == GAMESTATE_END || g_gamestate == GAMESTATE_NONE)
	{

		// カメラの更新処理
		UpdateCamera();

		// ライトの更新処理
		UpdateLight();

		//影の更新処理
		UpdateShadow();

		// 壁の更新処理
		UpdateWall();

		//屋根の更新処理
		UpdateRoof();

		//モデルの更新処理
		UpdateModel();

		//柱の更新処理
		UpdatePiller();

		//設置物の更新処理
		UpdateObject();

		//NPCの更新処理
		UpdateNpc();

		//操作キャラの更新処理
		UpdatePlayer();

		//弾の更新処理
		UpdateBullet();

		//爆発の更新処理
		UpdateExplosion();

		//メッシュフィールドの更新処理
		UpdateMeshField();

		//メッシュウォールの更新処理
		UpdateMeshWall();

		//メッシュシリンダーの更新処理
		UpdateMeshCylinder();

		//エフェクトの更新処理
		UpdateEffect();

		//パーティクルの更新処理
		UpdateParticle();

		//矢印の更新処理
		UpdateArrow();

		//タイマーの更新処理
		UpdateTimer();

		//マップの更新処理
		UpdateMiniMap();

		if (pPlayer->bUse == false && g_gamestate != GAMESTATE_END)
		{
			SetGameState(GAMESTATE_END);
		}
	}
	else if(g_bPause == true && g_gamestate != GAMESTATE_END || g_gamestate != GAMESTATE_NONE)
	{
		UpdatePause();//ポーズ処理
	}

	switch (g_gamestate)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			if (pPlayer->bUse == true)
			{
				SetRankScore(GetTimer());
			}

			StopSound();
			BulletErese();
			SetFade(MODE_RESULT);
			g_gamestate = GAMESTATE_NONE;			//モード設定
		}
		break;
	}
}

//=============================================================================
//	描画処理
//=============================================================================
void DrawGame(void)
{
	//***各種オブジェクトの描画処理***
	// カメラの設定
	SetCamera();

	//メッシュフィールドの描画処理
	DrawMeshField();

	//メッシュウォールの描画処理
	DrawMeshWall();

	//メッシュシリンダーの描画処理
	DrawMeshCylinder();

	// 壁の描画処理
	DrawWall();

	//屋根の描画処理
	DrawRoof();

	//モデルの描画処理
	DrawModel();

	//柱の描画処理
	DrawPiller();

	//設置物の描画処理
	DrawObject();

	//NPCの描画処理
	DrawNpc();

	//操作キャラの描画処理
	DrawPlayer();

	//影の描画処理
	DrawShadow();

	//弾の描画処理
	DrawBullet();

	//爆発の描画処理
	DrawExplosion();

	//エフェクトの描画処理
	DrawEffect();

	//パーティクルの描画処理
	DrawParticle();

	//矢印の描画処理
	DrawArrow();

	//タイマーの描画処理
	DrawTimer();

	//マップの描画処理
	DrawMiniMap();


	if (g_bPause == true && g_gamestate == GAMESTATE_NORMAL)
	{
		DrawPause();	//ポーズ画面
	}
}

//=============================================================================
//	ゲームの状態の設定
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
	g_nCounterGameState = 0;
}

//=============================================================================
//	ゲームの状態の取得
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gamestate;
}
//=============================================================================
//	ポーズ状態の切り替え
//=============================================================================
void PauseModeChange(void)
{
	g_bPause = g_bPause ? false : true;
	PlaySound(SOUND_LABEL_SE002);
}

