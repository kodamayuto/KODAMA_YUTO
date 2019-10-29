//=============================================================================
//
// 敵出現クラス処理 [enemyGenerator.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "enemyGenerator.h"
#include "game.h"

#define GENERATE_LOOPTIME (350)			//生成の１ループ
#define MAX_GEN_PATTERN (17)			//最大ループ数

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
int CEGenerator::m_nCntEnemy = 0;

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CEGenerator::CEGenerator()
{
	m_nGenPattern = 0;

}

CEGenerator::~CEGenerator()
{

}

//==================================================================
// 生成処理
//==================================================================
CEGenerator* CEGenerator::Create(CEGenerator::GENERATE_MODE GMode)
{
	CEGenerator* pEGenerator = NULL;

	pEGenerator = new CEGenerator;

	if (pEGenerator != NULL)
	{
		pEGenerator->Init(GMode);
	}

	return pEGenerator;
}

//==================================================================
// 4初期化処理
//==================================================================
HRESULT CEGenerator::Init(void)
{
	return S_OK;
}

HRESULT CEGenerator::Init(CEGenerator::GENERATE_MODE GMode)
{
	Init();
	m_GMode = GMode;
	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CEGenerator::Uninit(void)
{
	Release();
}

//==================================================================
// 更新処理
//==================================================================
void CEGenerator::Update(void)
{
	m_nCount++;

	if (m_nCount % GENERATE_LOOPTIME == 0)
	{
		PatternChange();
	}

	Generate();
	if (m_nCntEnemy <= 0)
	{
		m_nCntEnemy = 0;
		PatternChange();
	}
}

//==================================================================
// 描画処理
//==================================================================
void CEGenerator::Draw(void)
{

}

void CEGenerator::Generate(void)
{
	ELEMENT pcElement = ELEMENT_RED;
	CPlayer* pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		pcElement = pPlayer->GetElement();

		if (pcElement == ELEMENT_SUPER)
		{
			pcElement = ELEMENT_RED;
		}
	}
	CEnemy::ELEMENT elm = (CEnemy::ELEMENT)((pcElement + 1) % (ELEMENT_MAX - 1));

	D3DXVECTOR3 pos;
	if (m_nCount == 1)
	{
		switch (m_nGenPattern)
		{//生成パターン
		case 0:
			pos = D3DXVECTOR3(400.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.9f, 0.0f), 30.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(470.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.9f, 0.0f), 35.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL_SECOND);
			pos = D3DXVECTOR3(540.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.9f, 0.0f), 30.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL);
			break;
		case 1:
			pos = D3DXVECTOR3(700.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.9f, 0.0f), 30.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(770.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.9f, 0.0f), 35.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL_SECOND);
			pos = D3DXVECTOR3(840.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.9f, 0.0f), 30.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL);
			break;
		case 2:
			pos = D3DXVECTOR3(300.0f, 200.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.9f, 0.0f, 0.0f), 35.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.9f, 0.0f, 0.0f), 35.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(980.0f, 400.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(-0.9f, 0.0f, 0.0f), 35.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(980.0f, 500.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(-0.9f, 0.0f, 0.0f), 35.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL);
			break;
		case 3:
			pos = D3DXVECTOR3(640.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.9f, 0.0f), 30.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(540.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.9f, 0.0f), 35.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_NORMAL_SECOND);
			pos = D3DXVECTOR3(740.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.9f, 0.0f), 30.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_NORMAL);
			break;
		case 4:
			pos = D3DXVECTOR3(640.0f, 750.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, -0.9f, 0.0f), 30.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(540.0f, 750.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, -0.9f, 0.0f), 35.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_NORMAL_SECOND);
			pos = D3DXVECTOR3(740.0f, 750.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, -0.9f, 0.0f), 30.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_NORMAL);
			break;
		case 5:
			pos = D3DXVECTOR3(280.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.6f, 0.6f, 0.0f), 35.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(1000.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(-0.6f, 0.6f, 0.0f), 35.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_NORMAL);
			break;
		case 6:
			pos = D3DXVECTOR3(420.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.7f, 0.0f), 35.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL_SECOND);
			pos = D3DXVECTOR3(860.0f, 730.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, -0.7f, 0.0f), 35.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL_SECOND);
			break;
		case 7:
			pos = D3DXVECTOR3(300.0f, 200.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.8f, 0.0f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.8f, 0.0f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(300.0f, 400.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.8f, 0.0f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(980.0f, 250.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(-0.8f, 0.0f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(980.0f, 350.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(-0.8f, 0.0f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(980.0f, 450.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(-0.8f, 0.0f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL);
			break;
		case 8:
			pos = D3DXVECTOR3(640.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.8f, 0.0f), 30.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_LIGHT);
			pos = D3DXVECTOR3(540.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.8f, 0.0f), 30.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(740.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.8f, 0.0f), 30.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL);
			break;
		case 9:
			pos = D3DXVECTOR3(540.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.8f, 0.0f), 30.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_LIGHT);
			pos = D3DXVECTOR3(740.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.8f, 0.0f), 30.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_LIGHT);
			pos = D3DXVECTOR3(280.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.6f, 0.6f, 0.0f), 35.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(1000.0f, -10.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(-0.6f, 0.6f, 0.0f), 35.0f, CScene::ELEMENT_RED, CEnemy::TYPE_NORMAL);
			break;
		case 10:
			pos = D3DXVECTOR3(500.0f, -20.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.7f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_LIGHT);
			pos = D3DXVECTOR3(600.0f, -20.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.7f, 0.0f), 30.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(700.0f, -20.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.7f, 0.0f), 30.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(800.0f, -20.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.7f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_LIGHT);
			break;
		case 11:
			pos = D3DXVECTOR3(640.0f, -20.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.7f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_LIGHT);
			pos = D3DXVECTOR3(280.0f, 730.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.6f, -0.6f, 0.0f), 35.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(1000.0f, 730.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(-0.6f, -0.6f, 0.0f), 35.0f, CScene::ELEMENT_GREEN, CEnemy::TYPE_NORMAL);
			break;
		case 12:
			pos = D3DXVECTOR3(540.0f, -20.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.6f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(540.0f, -70.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.6f, 0.0f), 30.0f, CScene::ELEMENT_RED, CEnemy::TYPE_LIGHT);
			pos = D3DXVECTOR3(540.0f, -120.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.6f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL);
			break;
		case 13:
			pos = D3DXVECTOR3(740.0f, -20.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.6f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(740.0f, -70.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.6f, 0.0f), 30.0f, CScene::ELEMENT_RED, CEnemy::TYPE_LIGHT);
			pos = D3DXVECTOR3(740.0f, -120.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.6f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL);
			break;
		case 14:
			pos = D3DXVECTOR3(640.0f, -20.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.6f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(640.0f, -70.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.6f, 0.0f), 30.0f, CScene::ELEMENT_RED, CEnemy::TYPE_LIGHT);
			pos = D3DXVECTOR3(640.0f, -120.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.6f, 0.0f), 30.0f, CScene::ELEMENT_BLUE, CEnemy::TYPE_NORMAL);
			break;
		case 15:
			pos = D3DXVECTOR3(540.0f, 800.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, -0.9f, 0.0f), 30.0f, pcElement, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(640.0f, -20.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, 0.9f, 0.0f), 30.0f, elm, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(740.0f, 800.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.0f, -0.9f, 0.0f), 30.0f, pcElement, CEnemy::TYPE_NORMAL);
			break;
		case 16:
			pos = D3DXVECTOR3(1000.0f, 260.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(-0.9f, 0.0f, 0.0f), 30.0f, elm, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(200.0f, 360.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(0.9f, 0.0f, 0.0f), 30.0f, pcElement, CEnemy::TYPE_NORMAL);
			pos = D3DXVECTOR3(1000.0f, 460.0f, 0.0f);
			CEnemy::Create(pos, D3DXVECTOR3(-0.9f, 0.0f, 0.0f), 30.0f, elm, CEnemy::TYPE_NORMAL);
			break;
		}
	}

}
//==================================================================
// パターン変更処理
//==================================================================
void CEGenerator::PatternChange(void)
{
	m_nGenPattern = (m_nGenPattern + 1) % MAX_GEN_PATTERN;
	m_nCount = 0;
}