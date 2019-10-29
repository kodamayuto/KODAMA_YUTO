//=============================================================================
//
// ゲームUI処理 [gameUI.cpp]
// Author : Yutaro Abe
//
//=============================================================================
#include "gameUI.h"
#include "Command.h"

//==================================================================
// マクロ定義
//==================================================================

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CGameUI::CGameUI(CScene::PRIORITY pri) : CScene(pri)
{

	for (int nCount = 0; nCount < MAX_UI; nCount++)
	{
		m_pScene2D[nCount] = {};
	}
}
CGameUI::~CGameUI()
{
}

//==================================================================
// 設定処理
//==================================================================
void CGameUI::Set(void)
{

}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CGameUI::Init(void)
{
	m_State = 0;
	m_nCount = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nValue = 0;
	for (int nCount = 0; nCount < 4; nCount++)
	{
		m_bUse[nCount] = false;
		m_nCouter[nCount] = 0;
	}

	if (SceneCreate(m_pScene2D[0], CScene::PRIORITY_1))
	{
		//	背景
		m_pScene2D[0]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "BGUI");
		m_pScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	}
	if (SceneCreate(m_pScene2D[1], CScene::PRIORITY_1))
	{
		//	レール縦上
		m_pScene2D[1]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "レル縦");
		m_pScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 220, 0.0f), D3DXVECTOR2(70.0f, 120.0f));
	}
	if (SceneCreate(m_pScene2D[2], CScene::PRIORITY_1))
	{
		//	レール縦下
		m_pScene2D[2]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "レル縦");
		m_pScene2D[2]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 120, 0.0f), D3DXVECTOR2(70.0f, 120.0f));
	}
	if (SceneCreate(m_pScene2D[3], CScene::PRIORITY_1))
	{
		//	レール横左
		m_pScene2D[3]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "レル横");
		m_pScene2D[3]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR2(120.0f, 70.0f));
	}
	if (SceneCreate(m_pScene2D[4], CScene::PRIORITY_1))
	{
		//	レール横右
		m_pScene2D[4]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "レル横");
		m_pScene2D[4]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR2(120.0f, 70.0f));
	}
	if (SceneCreate(m_pScene2D[5], CScene::PRIORITY_1))
	{
		//	背景
		m_pScene2D[5]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "作業台");
		m_pScene2D[5]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR2(80.0f, 80.0f));
	}
	//if (SceneCreate(m_pScene2D[6], CScene::PRIORITY_1))
	//{
	//	//	ゴミ箱
	//	m_pScene2D[6]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "ゴミ箱");
	//	m_pScene2D[6]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 - 150, 0.0f), D3DXVECTOR2(70.0f, 70.0f));
	//}

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CGameUI::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_UI; nCount++)
	{
		m_pScene2D[nCount]->Uninit();
	}
	Release();
}

//==================================================================
// 更新処理
//==================================================================
void CGameUI::Update(void)
{
	if (CCommand::GetCommand("A"))
	{//	レール横右
		m_nValue = 3;
		m_bUse[0] = true;
		m_nCouter[0] = 0;
	}
	if (CCommand::GetCommand("S"))
	{//	レール縦下
		m_nValue = 2;
		m_bUse[1] = true;
		m_nCouter[1] = 0;
	}
	if (CCommand::GetCommand("D"))
	{//	レール横左
		m_nValue = 4;
		m_bUse[2] = true;
		m_nCouter[2] = 0;
	}
	if (CCommand::GetCommand("W"))
	{//	レール縦上
		m_nValue = 1;
		m_bUse[3] = true;
		m_nCouter[3] = 0;
	}

	if (m_bUse[0] == true)
	{
		m_nCouter[0]++;
		if (m_nCouter[0] < 300)
		{//	指定のフレーム以下の場合
			{// 横左スクロール
				m_pScene2D[3]->SetScroll(0.5f, 0);
			}
		}
		else
		{
			m_bUse[0] = false;
		}
	}
	if (m_bUse[1] == true)
	{
		m_nCouter[1]++;
		if (m_nCouter[1] < 300)
		{//	指定のフレーム以下の場合
			{// 縦下スクロール
				m_pScene2D[2]->SetScroll(-0.5f, 1);
			}
		}
		else
		{
			m_bUse[1] = false;
		}
	}
	if (m_bUse[2] == true)
	{
		m_nCouter[2]++;
		if (m_nCouter[2] < 300)
		{//	指定のフレーム以下の場合
			{// 横右スクロール
				m_pScene2D[4]->SetScroll(-0.5f, 0);
			}
		}
		else
		{
			m_bUse[2] = false;
		}
	}
	if (m_bUse[3] == true)
	{
		m_nCouter[3]++;
		if (m_nCouter[3] < 300)
		{//	指定のフレーム以下の場合
			{// 縦上スクロール
				m_pScene2D[1]->SetScroll(-0.5f, 1);
			}
		}
		else
		{
			m_bUse[3] = false;
		}
	}
	//D3DXVECTOR3 pos = m_pScene2D[6]->GetPosition();

	//switch (m_State)
	//{
	//case 0:
	//	//	位置の設定
	//	m_pScene2D[6]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 - 150, 0.0f));
	//	if (CCommand::GetCommand("S"))
	//	{//ゴミ箱揺らす
	//		m_State = 1;
	//	}
	//	break;
	//case 1:
	//	m_nCount++;
	//	if (m_nCount == 4)
	//	{
	//		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	}
	//	else if (m_nCount < 4)
	//	{
	//		m_move.x = 3.25f;
	//	}
	//	else if (m_nCount < 10)
	//	{
	//		m_move.x = -3.25f;
	//		m_nCount = 0;
	//		m_State = 0;
	//	}
	//	//	動きの加算
	//	pos += m_move;
	//	//	位置の設定
	//	m_pScene2D[6]->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
	//	break;
	//}

}

//==================================================================
// 描画処理
//==================================================================
void CGameUI::Draw(void)
{

}
