//=============================================================================
//
// タイトルロゴ処理 [endcall.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "endcall.h"
#include "Command.h"
#include "life.h"

#include "game.h"
//==================================================================
// 静的メンバ変数定義
//==================================================================
CSound *CEndCall::m_pSound = NULL;

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CEndCall::CEndCall(CScene::PRIORITY pri) : CScene2D(pri)
{
}
CEndCall::~CEndCall()
{

}

//==================================================================
// 設定処理
//==================================================================
void CEndCall::Set(D3DXVECTOR3 StartPos, D3DXVECTOR2 Size)
{
	m_StartPos = StartPos;
	CScene2D::Set(m_StartPos, "ENDCALL");
	CScene2D::SetPosition(m_StartPos, Size);

	m_nCount = 0;
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CEndCall::Init(void)
{
	m_pSound = CManager::GetSound();

	m_fAddValue = 5.0f;
	CScene2D::Init();
	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CEndCall::Uninit(void)
{

	CScene2D::Uninit();
}

//==================================================================
// 更新処理
//==================================================================
void CEndCall::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();
	D3DXVECTOR2 size = CScene2D::GetSize();
	CGame* pGame = CManager::GetGame();
	if (CLife::GetCount() == 2)
	{
		if (m_pSound != NULL)
		{
			m_pSound->Play(CSound::SE_END_SE);
		}
	}
	if (CLife::GetCount() >= 3)
	{

		if (size.x <= 320)
		{
			size.x += m_fAddValue;
		}
		if (size.y <= 250)
		{
			size.y += m_fAddValue;

		}
		CScene2D::SetPosition(CScene2D::GetPosition(), D3DXVECTOR2(size.x, size.y));
		CScene2D::Update();

		pGame->SetClearFlag();
	}
}

//==================================================================
// 描画処理
//==================================================================
void CEndCall::Draw(void)
{
	CScene2D::Draw();
}
