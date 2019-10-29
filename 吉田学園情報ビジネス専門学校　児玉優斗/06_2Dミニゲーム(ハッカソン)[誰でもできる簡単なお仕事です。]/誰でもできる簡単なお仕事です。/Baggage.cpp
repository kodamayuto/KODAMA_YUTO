//=============================================================================
//
// 荷物クラス処理 [Baggage.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "Baggage.h"

//=============================================================================
// コンストラクタ&デストラクタ
//=============================================================================
CBaggage::CBaggage(CScene::PRIORITY pri) : CScene2D(pri)
{

}
CBaggage::~CBaggage()
{

}

//=============================================================================
// 設定処理
//=============================================================================
void CBaggage::Set(D3DXVECTOR3 pos,CBaggage::BAGGAGE_TYPE type)
{
	CScene2D::Set(pos,"",true,0.0f);
	CScene2D::SetPosition(pos,D3DXVECTOR2(75.0f,75.0f));
	m_State = STATE_NEUTRAL;
	m_Type = type;
	m_StartPos = pos;

	BindTexture("ITEM");
	switch (m_Type)
	{
	case CBaggage::TYPE_CARDBOARD_BOX:
		SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 1.0f));
		break;
	case CBaggage::TYPE_ENVELOVE:
		SetUV(D3DXVECTOR2(0.25f, 0.0f), D3DXVECTOR2(0.5f, 1.0f));
		break;
	case CBaggage::TYPE_LETTER:
		SetUV(D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(0.75f, 1.0f));
		break;
	case CBaggage::TYPE_TRASH:
		SetUV(D3DXVECTOR2(0.75f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
		break;

	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBaggage::Init(void)
{
	m_Type = TYPE_NONE;
	m_fRot = 0.0f;
	m_nCount = 0;
	CScene2D::Init();

	SetObjType(CScene::OBJTYPE_BAGGAGE);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void  CBaggage::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void  CBaggage::Update(void)
{
	D3DXVECTOR3 LeapPos;
	float fRot = 0.0f;
	switch (m_State)
	{
	case CBaggage::STATE_NEUTRAL:
		break;
	case CBaggage::STATE_MOVE:
		if (m_nCount < 100)
		{
			D3DXVec3Lerp(&LeapPos, &m_StartPos, &m_GoalPos, (float)m_nCount / 100);
			SetPosition(LeapPos);
		}
		m_nCount++;
		break;
	case CBaggage::STATE_TRASH:
		if (m_nCount < 50)
		{
			D3DXVec3Lerp(&LeapPos, &m_StartPos, &m_GoalPos, (float)m_nCount / 50);
			SetPosition(LeapPos,D3DXVECTOR2(GetSize().x * 0.97f, GetSize().y * 0.97f));
			fRot = (-0.2f * m_nCount);
			SetRotation(fRot);

		}
		else
		{
			Uninit();
		}
		m_nCount++;
		break;
	}
	CScene2D::Update();

}
//=============================================================================
// 描画処理
//=============================================================================
void  CBaggage::Draw(void)
{
	CScene2D::Draw();
}


//=============================================================================
// 移動方向設定処理
//=============================================================================
void CBaggage::SetMoveDir(CManager::DIRECTION dir)
{
	switch (dir)
	{
	case CManager::DIR_UP:
		m_GoalPos = D3DXVECTOR3(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.25f, 0.0f);
		m_State = STATE_TRASH;
		break;
	case CManager::DIR_LEFT:
		m_GoalPos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT  * 0.4f, 0.0f);
		m_State = STATE_MOVE;
		break;
	case CManager::DIR_RIGHT:
		m_GoalPos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT  * 0.4f, 0.0f);
		m_State = STATE_MOVE;
		break;
	case CManager::DIR_DOWN:
		m_GoalPos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT, 0.0f);
		m_State = STATE_MOVE;
		break;
	}


}