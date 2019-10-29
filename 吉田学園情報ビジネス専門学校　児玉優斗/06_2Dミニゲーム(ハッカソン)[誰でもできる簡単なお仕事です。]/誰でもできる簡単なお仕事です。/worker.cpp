//=============================================================================
//
// ���C�t���� [���C�t.cpp]
// Author : Yutaro Abe
//
//=============================================================================
#include "worker.h"
#include "Command.h"

//==================================================================
// �}�N����`
//==================================================================

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CWoker::CWoker(CScene::PRIORITY pri) : CScene2D(pri)
{

}
CWoker::~CWoker()
{

}

//==================================================================
// �ݒ菈��
//==================================================================
void CWoker::Set(D3DXVECTOR3 StartPos, D3DXVECTOR2 Size, int nTypeState)
{
	m_nTypeState = nTypeState;
	CScene2D::Set(StartPos, "�Ђ�");
	CScene2D::SetPosition(StartPos, Size);
	CScene2D::SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / 4, 1.0f));
}

//==================================================================
// ����������
//==================================================================
HRESULT CWoker::Init(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
	m_nType = 0;
	CScene2D::Init();
	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CWoker::Uninit(void)
{
	CScene2D::Uninit();
}

//==================================================================
// �X�V����
//==================================================================
void CWoker::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();
	D3DXVECTOR2 size = CScene2D::GetSize();
	if (m_nTypeState == 0)
	{//	�����ꏊ�̎��
		switch (m_nType)
		{//	�����̍�ƈ�
		case 0:
			if (pos.y > 450)
			{
				m_move.y = -2.75f;
				pos += m_move;
			}
			if (pos.y < 450)
			{
				m_move.y = 0.0f;
				m_nType = 1;
			}
			CScene2D::SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / 4, 1.0f));
			break;
		case 1:
			if (pos.x > 180)
			{
				m_move.x = -2.75f;
				pos += m_move;
			}
			if (pos.x < 180)
			{
				m_move.x = 0.0f;
				m_nType = 2;
			}
			CScene2D::SetUV(D3DXVECTOR2(1.0f / 4 * 3, 0.0f), D3DXVECTOR2(1.0f / 4 * 4, 1.0f));
			break;
		case 2:
			if (pos.x < 500)
			{
				m_move.x = 2.75f;
				pos += m_move;
			}
			if (pos.x == 500)
			{
				m_move.x = 0.0f;
				m_nType = 3;
			}
			CScene2D::SetUV(D3DXVECTOR2(1.0f / 4, 0.0f), D3DXVECTOR2(1.0f / 4 * 2, 1.0f));
			break;
		case 3:
			if (pos.y < 1800)
			{
				m_move.y = 2.75f;
				pos += m_move;
			}
			if (pos.y == 1800)
			{
				m_move.y = 0.0f;
				m_nType = 0;
			}
			CScene2D::SetUV(D3DXVECTOR2(1.0f / 2, 0.0f), D3DXVECTOR2(1.0f / 4 * 3, 1.0f));
			break;
		}
	}
	else  if (m_nTypeState == 1)
	{//	�E��̍�ƈ�
		switch (m_nType)
		{
		case 0:
			if (pos.y < 200)
			{
				m_move.y = 2.75f;
				pos += m_move;
			}
			if (pos.y > 200)
			{
				m_move.y = 0.0f;
				m_nType = 1;
			}
			CScene2D::SetUV(D3DXVECTOR2(1.0f / 2, 0.0f), D3DXVECTOR2(1.0f / 4 * 3, 1.0f));
			break;
		case 1:
			if (pos.x < 1100)
			{
				m_move.x = 2.75f;
				pos += m_move;
			}
			if (pos.x > 1100)
			{
				m_move.x = 0.0f;
				m_nType = 2;
			}
			CScene2D::SetUV(D3DXVECTOR2(1.0f / 4, 0.0f), D3DXVECTOR2(1.0f / 4 * 2, 1.0f));
			break;
		case 2:
			if (pos.x > 920)
			{
				m_move.x = -2.75f;
				pos += m_move;
			}
			if (pos.x == 920)
			{
				m_move.x = 0.0f;
				m_nType = 3;
			}
			CScene2D::SetUV(D3DXVECTOR2(1.0f / 4 * 3, 0.0f), D3DXVECTOR2(1.0f / 4 * 4, 1.0f));
			break;
		case 3:
			if (pos.y > -800)
			{
				m_move.y = -2.75f;
				pos += m_move;
			}
			if (pos.y < -800)
			{
				m_move.y = 0.0f;
				m_nType = 0;
			}
			CScene2D::SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / 4, 1.0f));
			break;
		}
	}
	else  if (m_nTypeState == 2)
	{//	�E���̍�ƈ�
		switch (m_nType)
		{
		case 0:
			if (pos.y > 450)
			{
				m_move.y = -2.75f;
				pos += m_move;
			}
			if (pos.y < 450)
			{
				m_move.y = 0.0f;
				m_nType = 1;
			}
			CScene2D::SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / 4, 1.0f));
			break;
		case 1:

			if (pos.x < 1100)
			{
				m_move.x = 2.75f;
				pos += m_move;
			}
			if (pos.x > 1100)
			{
				m_move.x = 0.0f;
				m_nType = 2;
			}
			CScene2D::SetUV(D3DXVECTOR2(1.0f / 4, 0.0f), D3DXVECTOR2(1.0f / 4 * 2, 1.0f));

			break;
		case 2:
			if (pos.x > 880)
			{
				m_move.x = -2.75f;
				pos += m_move;
			}
			if (pos.x < 880)
			{
				m_move.x = 0.0f;
				m_nType = 3;
			}
			CScene2D::SetUV(D3DXVECTOR2(1.0f / 4 * 3, 0.0f), D3DXVECTOR2(1.0f / 4 * 4, 1.0f));
			break;
		case 3:
			if (pos.y < 1200)
			{
				m_move.y = 2.75f;
				pos += m_move;
			}
			if (pos.y > 1200)
			{
				m_move.y = 0.0f;
				m_nType = 0;
			}
			CScene2D::SetUV(D3DXVECTOR2(1.0f / 2, 0.0f), D3DXVECTOR2(1.0f / 4 * 3, 1.0f));
			break;
		}
	}


	CScene2D::SetPosition(pos, size);
	CScene2D::Update();
}

//==================================================================
// �`�揈��
//==================================================================
void CWoker::Draw(void)
{
	CScene2D::Draw();
}
