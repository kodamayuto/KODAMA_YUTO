//=============================================================================
//
// チュートリアル画面処理 [tutorial.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "tutorial.h"
#include "fade.h"
#include "pressenter.h"
#include "input.h"
#include "sound.h"
#include "tutorialBG.h"
#include "camera.h"
#include "light.h"
#include "main.h" 
#include "course.h"
#include "woodbg.h"
#include "masu.h"
#include "course.h"
#include "sky.h"
#include "shadow.h"
#include "effect.h"
#include "particle.h"
#include "meshField.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// マスの情報
//*****************************************************************************
typedef struct
{// ブロックの情報
	D3DXVECTOR3 pos;
	MASUTYPE masuType;	// ブロックの種類
} MasuInfo;

//*****************************************************************************
// コースの情報
//*****************************************************************************
typedef struct
{// ブロックの情報
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fWidth;
	float fHeight;
} CourseInfo;

//*****************************************************************************
// グローバル変数
//***************************************************************************** 
TUTORIAL_STATE g_TutorialState;		//状態
int g_MoveTimer;	//移動のタイマー
int g_nCntMove;	//移動のカウンター
MasuInfo g_aMasuInfo3[] =
{
	{ D3DXVECTOR3(0.0f, 0.0f, -150.0f), MASUTYPE_START },
	{ D3DXVECTOR3(1700.0f, 0.0f, -150.0f),MASUTYPE_GOAL },
	//{ D3DXVECTOR3(5100.0f, 0.0f, -150.0f), MASUTYPE_GOAL },

};

// ブロック情報のデータ
CourseInfo g_aCourseInfo3[] =
{
	{ D3DXVECTOR3(900.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 850.0f, 200.0f },
};


//=============================================================================
//背景の木の設置
//=============================================================================
WOODBG_INFO g_WoodBGInfo3[] =
{
	{ D3DXVECTOR3(0.0f, -500.0f, 0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),WOODBG_TYPE_PALM },
	{ D3DXVECTOR3(1700.0f, -500.0f, 0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),WOODBG_TYPE_PALM },


	{ D3DXVECTOR3(1400.0f, -500.0f, 2300.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),WOODBG_TYPE_LAKE },
};
//=============================================================================
// 初期化処理
//=============================================================================
void InitTutorial(void)
{
	g_nCntMove = 0;							//移動カウンターを初期化
	g_MoveTimer = 0;						//移動タイマーを初期化
	g_TutorialState = TUTORIAL_STATE_NONE;	//状態の初期化

											// カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	//影の初期化処理
	InitShadow();

	//エフェクトの初期化処理
	InitEffect();

	//パーティクルの初期化処理
	InitParticle();

	//空の初期化処理
	InitSky();

	//マスの初期化処理
	InitMasu();

	//コースの初期化処理
	InitCourse();

	//背景の木の初期化処理
	InitWoodBG();

	//メッシュフィールドの初期化処理
	InitMeshField();

	//チュートリアル背景の初期化処理
	InitTutorialBG();
	SetTutorialBG(D3DXVECTOR3(0.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetTutorialBG(D3DXVECTOR3(850.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetTutorialBG(D3DXVECTOR3(1700.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//SetTutorialBG(D3DXVECTOR3(2550.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// マスの設置
	for (int nCntMasu = 0; nCntMasu < sizeof g_aMasuInfo3 / sizeof(MasuInfo); nCntMasu++)
	{
		SetMasu(g_aMasuInfo3[nCntMasu].pos, g_aMasuInfo3[nCntMasu].masuType);
	}

	// コースの設置
	for (int nCntCourse = 0; nCntCourse < sizeof g_aCourseInfo3 / sizeof(CourseInfo); nCntCourse++)
	{
		SetCourse(g_aCourseInfo3[nCntCourse].pos, g_aCourseInfo3[nCntCourse].rot, g_aCourseInfo3[nCntCourse].fWidth, g_aCourseInfo3[nCntCourse].fHeight);
	}

	//　背景の木の設置
	for (int nCntWoodBG = 0; nCntWoodBG < sizeof g_WoodBGInfo3 / sizeof(WOODBG_INFO); nCntWoodBG++)
	{
		SetWoodBG(g_WoodBGInfo3[nCntWoodBG].pos, g_WoodBGInfo3[nCntWoodBG].rot, g_WoodBGInfo3[nCntWoodBG].move, g_WoodBGInfo3[nCntWoodBG].nType);
	}

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorial(void)
{
	// カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//影の終了処理
	UninitShadow();

	//エフェクトの終了処理
	UninitEffect();

	//パーティクルの終了処理
	UninitParticle();

	//マスの終了処理
	UninitMasu();

	//背景の木の終了処理
	UninitWoodBG();

	//コースの終了処理
	UninitCourse();

	//チュートリアル背景の終了処理
	UninitTutorialBG();

	//空の終了処理
	UninitSky();

	//メッシュフィールドの終了処理
	UninitMeshField();

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorial(void)
{
	FADE fade;
	fade = GetFade();



	//bool *disp;
	//disp = GetDispPressEnter();

	// カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	//影の更新処理
	UpdateShadow();

	//エフェクトの更新処理
	UpdateEffect();

	//パーティクルの更新処理
	UpdateParticle();

	//マスの更新処理
	UpdateMasu();

	//コースの更新処理
	UpdateCourse();

	//背景の木の更新処理
	UpdateWoodBG();

	//チュートリアル背景の更新処理
	UpdateTutorialBG();

	//空の更新処理
	UpdateSky();

	//メッシュフィールドの更新処理
	UpdateMeshField();

	//カメラの取得
	Camera *pCamera = GetCamera();

	switch (g_TutorialState)
	{
	case TUTORIAL_STATE_NONE:	//通常状態
		pCamera->posV.x -= 0.0f;
		pCamera->posV.z -= 0.0f;
		pCamera->posR.x = pCamera->posV.x + sinf(pCamera->rot.y) * pCamera->fLength;
		pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * pCamera->fLength;
		break;
	case TUTORIAL_STATE_MOVE:	//移動状態


		pCamera->posV.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posV.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posR.x = pCamera->posV.x + sinf(pCamera->rot.y) * pCamera->fLength;
		pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * pCamera->fLength;
		g_MoveTimer++;
		if (g_MoveTimer == 85.0f)
		{//カウントが８５になった場合
			g_TutorialState = TUTORIAL_STATE_NONE;		//通常状態に戻す
			g_nCntMove++;								//移動カウンターを足す
			g_MoveTimer = 0;							//タイマーを初期化する
		}

		break;
	case TUTORIAL_STATE_REMOVE:	//戻る状態

		pCamera->posV.x += sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posV.z += cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posR.x = pCamera->posV.x + sinf(pCamera->rot.y) * pCamera->fLength;
		pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * pCamera->fLength;
		g_MoveTimer++;
		if (g_MoveTimer == 85.0f)
		{//カウントが８５になった場合
			g_TutorialState = TUTORIAL_STATE_NONE;		//通常状態に戻す
			g_nCntMove--;								//移動カウンターを足す
			g_MoveTimer = 0;							//タイマーを初期化する
		}
		break;
	}
	if (g_TutorialState == TUTORIAL_STATE_NONE)
	{//通常状態の場合
		if (g_nCntMove == 0)
		{
			if (GetKeyboardTrigger(DIK_RIGHT) == true || GetJoyPadTrigger(DIJS_BUTTON_20, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_12, 0) == true)
			{
				g_TutorialState = TUTORIAL_STATE_MOVE;
				PlaySound(SOUND_LABEL_SE002);
			}
		}
		if (g_nCntMove == 1)
		{
			if (GetKeyboardTrigger(DIK_LEFT) == true || GetJoyPadTrigger(DIJS_BUTTON_21, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_13, 0) == true)
			{
				g_TutorialState = TUTORIAL_STATE_REMOVE;
				PlaySound(SOUND_LABEL_SE003);
			}
		}
	}
	if (g_nCntMove == 1)
	{
		for (int nCntJoyPad = 0; nCntJoyPad < 8; nCntJoyPad++)
		{
			if (GetJoyPadTrigger(nCntJoyPad, 0) == TRUE && fade == FADE_NONE)
			{
				SetFade(MODE_SELECT);
				PlaySound(SOUND_LABEL_SE000);
			}
		}
		if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE )
		{// 決定ボタンが押された
			SetFade(MODE_SELECT);
			PlaySound(SOUND_LABEL_SE000);
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorial(void)
{
	// カメラの描画処理
	SetCamera();

	//マスの描画処理
	DrawMasu();

	//メッシュフィールドの描画処理
	DrawMeshField();

	//コースの描画処理
	DrawCourse();

	//背景の木の描画処理
	DrawWoodBG();

	//空の更新処理
	DrawSky();

	//影の描画処理
	DrawShadow();

	//エフェクトの描画処理
	DrawEffect();

	//パーティクルの描画処理
	DrawParticle();

	//チュートリアル背景の描画処理
	DrawTutorialBG();
}