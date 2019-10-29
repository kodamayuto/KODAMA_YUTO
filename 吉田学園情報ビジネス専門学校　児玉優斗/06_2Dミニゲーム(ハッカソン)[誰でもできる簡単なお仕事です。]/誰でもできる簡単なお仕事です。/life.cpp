//=============================================================================
//
// ライフ処理 [ライフ.cpp]
// Author : Yutaro Abe
//
//=============================================================================
#include "life.h"
#include "Command.h"

//==================================================================
// マクロ定義
//==================================================================

int CLife::m_nCount = 0;
//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CLife::CLife(CScene::PRIORITY pri) : CScene2D(pri)
{
	m_fvalu = 0.0f;
}
CLife::~CLife()
{

}

//==================================================================
// 設定処理
//==================================================================
void CLife::Set(D3DXVECTOR3 StartPos, D3DXVECTOR2 Size)
{

	m_StartPos = StartPos;
	CScene2D::Set(m_StartPos, "LIFE");
	CScene2D::SetPosition(m_StartPos, Size);
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CLife::Init(void)
{
	m_bUse = false;
	m_nCount = 0;
	m_fsizeValue = 0.0f;
	m_fposValue = 0.0f;
	m_fvalu = 0.0f;
	CScene2D::Init();
	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CLife::Uninit(void)
{
	CScene2D::Uninit();
}

//==================================================================
// 更新処理
//==================================================================
void CLife::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();
	D3DXVECTOR2 size = CScene2D::GetSize();

	if (m_bUse == true)
	{
		m_nCount++;
		if (m_nCount <= 3)
		{//	3以下の場合
			m_fvalu += 1.0f / 3;
			m_fsizeValue = size.x / 3;
			m_fposValue = pos.x / 27;
			CScene2D::SetPosition(D3DXVECTOR3(pos.x - m_fposValue, pos.y, pos.z), D3DXVECTOR2(size.x - m_fsizeValue, size.y));
			m_bUse = false;
		}
	}

	CScene2D::SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f - m_fvalu, 1.0f));
	CScene2D::Update();
}

//==================================================================
// 描画処理
//==================================================================
void CLife::Draw(void)
{
	CScene2D::Draw();
}

//==================================================================
// HPの加算
//==================================================================
void CLife::AddLife(int nValue)
{
	//m_nCount += nValue;
	m_bUse = true;
}