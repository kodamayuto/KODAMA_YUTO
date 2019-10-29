//=============================================================================
//
// スタートコール処理 [StartCall.cpp]
// Author : Yutaro　Abe
//
//=============================================================================
#include "StartCall.h"
#include "Command.h"
#include "life.h"
#include "Manager.h"
#include "sound.h"
//==================================================================
// マクロ定義
//==================================================================
CSound *CStartCall::m_pSound = NULL;
int CStartCall::m_nCount = 0;

bool CStartCall::m_bStop = false;
//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CStartCall::CStartCall(CScene::PRIORITY pri) : CScene2D(pri)
{
}
CStartCall::~CStartCall()
{

}

//==================================================================
// 設定処理
//==================================================================
void CStartCall::Set(D3DXVECTOR3 StartPos, D3DXVECTOR2 Size)
{
	m_StartPos = StartPos;
	CScene2D::Set(m_StartPos, "スタートコール");
	CScene2D::SetPosition(m_StartPos, Size);

	m_nCount = 0;
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CStartCall::Init(void)
{
	m_fAddValue = 5.0f;
	m_pSound = CManager::GetSound();
	if (m_pSound != NULL)
	{
		m_pSound->Play(CSound::SE_START_SE);
	}
	CScene2D::Init();
	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CStartCall::Uninit(void)
{

	CScene2D::Uninit();
}

//==================================================================
// 更新処理
//==================================================================
void CStartCall::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();
	D3DXVECTOR2 size = CScene2D::GetSize();

	m_nCount++;

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
	if (m_nCount >= 120)
	{
		CStartCall::Uninit();
		m_bStop = true;
	}
}

//==================================================================
// 描画処理
//==================================================================
void CStartCall::Draw(void)
{
	CScene2D::Draw();
}
