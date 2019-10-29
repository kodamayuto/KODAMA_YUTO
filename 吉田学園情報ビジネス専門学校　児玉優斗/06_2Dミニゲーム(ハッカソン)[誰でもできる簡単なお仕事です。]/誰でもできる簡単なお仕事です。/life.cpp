//=============================================================================
//
// ���C�t���� [���C�t.cpp]
// Author : Yutaro Abe
//
//=============================================================================
#include "life.h"
#include "Command.h"

//==================================================================
// �}�N����`
//==================================================================

int CLife::m_nCount = 0;
//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CLife::CLife(CScene::PRIORITY pri) : CScene2D(pri)
{
	m_fvalu = 0.0f;
}
CLife::~CLife()
{

}

//==================================================================
// �ݒ菈��
//==================================================================
void CLife::Set(D3DXVECTOR3 StartPos, D3DXVECTOR2 Size)
{

	m_StartPos = StartPos;
	CScene2D::Set(m_StartPos, "LIFE");
	CScene2D::SetPosition(m_StartPos, Size);
}

//==================================================================
// ����������
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
// �I������
//==================================================================
void CLife::Uninit(void)
{
	CScene2D::Uninit();
}

//==================================================================
// �X�V����
//==================================================================
void CLife::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();
	D3DXVECTOR2 size = CScene2D::GetSize();

	if (m_bUse == true)
	{
		m_nCount++;
		if (m_nCount <= 3)
		{//	3�ȉ��̏ꍇ
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
// �`�揈��
//==================================================================
void CLife::Draw(void)
{
	CScene2D::Draw();
}

//==================================================================
// HP�̉��Z
//==================================================================
void CLife::AddLife(int nValue)
{
	//m_nCount += nValue;
	m_bUse = true;
}