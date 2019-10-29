//=============================================================================
//
// コントロールUI処理 [ControlUI.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "ControlUI.h"
#include "Command.h"

//==================================================================
// マクロ定義
//==================================================================

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CControlUI::CControlUI(CScene::PRIORITY pri) : CScene2D(pri)
{
}
CControlUI::~CControlUI()
{

}

//==================================================================
// 設定処理
//==================================================================
void CControlUI::Set(D3DXVECTOR3 StartPos, D3DXVECTOR2 Size)
{
	m_StartPos = StartPos;
	CScene2D::Set(m_StartPos, "ControlUI");
	CScene2D::SetPosition(m_StartPos, Size);
	CScene2D::SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / 4, 1.0f));
	m_nCount = 0;
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CControlUI::Init(void)
{

	CScene2D::Init();
	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CControlUI::Uninit(void)
{
	CScene2D::Uninit();
}

//==================================================================
// 更新処理
//==================================================================
void CControlUI::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();
	D3DXVECTOR2 size = CScene2D::GetSize();

	if (CCommand::GetCommand("LEFT"))
	{
		CScene2D::SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / 4, 1.0f));
	}
	else if (CCommand::GetCommand("DOWN"))
	{
		CScene2D::SetUV(D3DXVECTOR2(1.0f / 4, 0.0f), D3DXVECTOR2(1.0f / 4*2, 1.0f));
	}
	else if (CCommand::GetCommand("RIGHT"))
	{
		CScene2D::SetUV(D3DXVECTOR2(1.0f / 4*2, 0.0f), D3DXVECTOR2(1.0f / 4 *3, 1.0f));
	}
	else if (CCommand::GetCommand("UP"))
	{
		CScene2D::SetUV(D3DXVECTOR2(1.0f / 4 * 3, 0.0f), D3DXVECTOR2(1.0f / 4 * 4, 1.0f));
	}

	CScene2D::SetPosition(CScene2D::GetPosition(), D3DXVECTOR2(size.x, size.y));
	CScene2D::Update();
}

//==================================================================
// 描画処理
//==================================================================
void CControlUI::Draw(void)
{
	CScene2D::Draw();
}
