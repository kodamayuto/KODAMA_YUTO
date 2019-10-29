//=============================================================================
//
// 荷物配送機クラス処理 [truck.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "truck.h"
#include "game.h"
//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CTruck::CTruck(CScene::PRIORITY pri) : CScene(pri)
{
	m_pBaggage = NULL;
	for(int nCnt = 0;nCnt < 3;nCnt++)
	{
		m_pBaggagePolygon[nCnt] = NULL;
		m_CreateBaggageType[nCnt] = CBaggage::TYPE_NONE;
	}

	m_nCount = 0;
}
CTruck::~CTruck()
{

}

//==================================================================
// 設定処理
//==================================================================
void CTruck::Set(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_CreateBaggageType[nCnt] = (CBaggage::BAGGAGE_TYPE)((rand() % 4) + 1);
		m_pBaggagePolygon[nCnt] = NULL;

		if (SceneCreate(m_pBaggagePolygon[nCnt], PRIORITY_4))
		{
			m_pBaggagePolygon[nCnt]->Set(pos + D3DXVECTOR3(0.0f,(50.0f * (nCnt + 1)),0.0f),"",false ,0.0f,
				D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),D3DXVECTOR2(30.0f,30.0f));
			m_pBaggagePolygon[nCnt]->BindTexture("ITEM");
			switch (m_CreateBaggageType[nCnt])
			{
			case CBaggage::TYPE_CARDBOARD_BOX:
				m_pBaggagePolygon[nCnt]->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 1.0f));
				break;
			case CBaggage::TYPE_ENVELOVE:
				m_pBaggagePolygon[nCnt]->SetUV(D3DXVECTOR2(0.25f, 0.0f), D3DXVECTOR2(0.5f, 1.0f));
				break;
			case CBaggage::TYPE_LETTER:
				m_pBaggagePolygon[nCnt]->SetUV(D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(0.75f, 1.0f));
				break;
			case CBaggage::TYPE_TRASH:
				m_pBaggagePolygon[nCnt]->SetUV(D3DXVECTOR2(0.75f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
				break;

			}
		}

	}

	if (SceneCreate(m_pBaggage, CScene::PRIORITY_1))
	{
		int nRand = (rand() % 4) + 1;
		m_pBaggage->Set(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT  * 0.4f, 0.0f), (CBaggage::BAGGAGE_TYPE)nRand);
	}
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CTruck::Init(void)
{
	m_nCount = 0;

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CTruck::Uninit(void)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_pBaggagePolygon[nCnt] != NULL)
		{
			m_pBaggagePolygon[nCnt]->Uninit();
		}
	}

	Release();
}

//==================================================================
// 更新処理
//==================================================================
void CTruck::Update(void)
{
	CGame* pGame = CManager::GetGame();

	if (CStartCall::GetStartCallEnd() == true)
	{
		if (m_pBaggage != NULL)
		{
			if (CCommand::GetCommand("UP")) {
				m_pBaggage->SetMoveDir(CManager::DIR_UP);
				BaggageCreate();
				pGame->SetCountFlag(false);
				m_nCount = 0;
			}
			if (CCommand::GetCommand("RIGHT")) {
				m_pBaggage->SetMoveDir(CManager::DIR_RIGHT);
				BaggageCreate();
				pGame->SetCountFlag(false);
				m_nCount = 0;
			}
			if (CCommand::GetCommand("LEFT")) {
				m_pBaggage->SetMoveDir(CManager::DIR_LEFT);
				BaggageCreate();
				pGame->SetCountFlag(false);
				m_nCount = 0;
			}
			if (CCommand::GetCommand("DOWN")) {
				m_pBaggage->SetMoveDir(CManager::DIR_DOWN);
				BaggageCreate();
				pGame->SetCountFlag(false);
				m_nCount = 0;
			}
		}
		if (m_nCount == 60)
		{
			pGame->SetCountFlag(true);
		}
		else if (m_nCount == 172)
		{
			m_pBaggage->Uninit();

			/*ダメージ*/
		}
		else if (m_nCount == 182)
		{
			BaggageCreate();
			m_nCount = 0;
		}

		m_nCount++;

	}


}

//==================================================================
// 描画処理
//==================================================================
void CTruck::Draw(void)
{

}
void CTruck::BaggageCreate(void)
{
	if (SceneCreate(m_pBaggage, CScene::PRIORITY_1))
	{
		int nRand = (rand() % 4) + 1;
		m_pBaggage->Set(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT  * 0.4f, 0.0f), m_CreateBaggageType[2]);
		m_CreateBaggageType[2] = m_CreateBaggageType[1];
		m_CreateBaggageType[1] = m_CreateBaggageType[0];
		m_CreateBaggageType[0] = (CBaggage::BAGGAGE_TYPE)nRand;
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			switch (m_CreateBaggageType[nCnt])
			{
			case CBaggage::TYPE_CARDBOARD_BOX:
				m_pBaggagePolygon[nCnt]->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 1.0f));
				break;
			case CBaggage::TYPE_ENVELOVE:
				m_pBaggagePolygon[nCnt]->SetUV(D3DXVECTOR2(0.25f, 0.0f), D3DXVECTOR2(0.5f, 1.0f));
				break;
			case CBaggage::TYPE_LETTER:
				m_pBaggagePolygon[nCnt]->SetUV(D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(0.75f, 1.0f));
				break;
			case CBaggage::TYPE_TRASH:
				m_pBaggagePolygon[nCnt]->SetUV(D3DXVECTOR2(0.75f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
				break;
			}
		}
	}

}
