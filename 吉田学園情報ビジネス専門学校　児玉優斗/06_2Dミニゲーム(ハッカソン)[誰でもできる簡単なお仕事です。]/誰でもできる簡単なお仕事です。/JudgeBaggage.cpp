//=============================================================================
//
// �ו������N���X���� [JudgeBaggage.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "JudgeBaggage.h"
#include "Score.h"
#include "life.h"
#include "game.h"

CSound *CJudgeBaggage::m_pSound = NULL;

//=============================================================================
//	�R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CJudgeBaggage::CJudgeBaggage(CScene::PRIORITY pri) : CScene2D(pri)
{

}
CJudgeBaggage::~CJudgeBaggage()
{

}

//=============================================================================
// �ݒ菈��
//=============================================================================
void  CJudgeBaggage::Set(D3DXVECTOR3 pos, D3DXVECTOR2 Size, CBaggage::BAGGAGE_TYPE type)
{
	m_CollisionRectMin = D3DXVECTOR3(pos.x - Size.x, pos.y - Size.y,0.0f);
	m_CollisionRectMax = D3DXVECTOR3(pos.x + Size.x, pos.y + Size.y, 0.0f);
	m_Type = type;
	m_Size = Size;

	CScene2D::Set(pos,"BLOCK");
	CScene2D::SetPosition(pos,Size);

	BindTexture("BOX");
	switch (m_Type)
	{
	case CBaggage::TYPE_CARDBOARD_BOX:
		SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2((1.0f / 3), 1.0f));
		break;
	case CBaggage::TYPE_ENVELOVE:
		SetUV(D3DXVECTOR2((1.0f / 3), 0.0f), D3DXVECTOR2((1.0f / 3) * 2.0f, 1.0f));
		break;
	case CBaggage::TYPE_LETTER:
		SetUV(D3DXVECTOR2((1.0f / 3) * 2.0f, 0.0f), D3DXVECTOR2((1.0f / 3) * 3.0f, 1.0f));
		break;
	case CBaggage::TYPE_TRASH:
		BindTexture("�S�~��");
		break;
	}
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CJudgeBaggage::Init(void)
{
	m_pSound = CManager::GetSound();
	m_nBigTimer = 0;
	m_nColorTimer = 0;

	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void  CJudgeBaggage::Uninit(void)
{
	if (m_pSound != NULL)
	{
		m_pSound->StopAll();
	}
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void  CJudgeBaggage::Update(void)
{
	HitCheck();
	if (m_nBigTimer > 0)
	{
		m_nBigTimer--;
		D3DXVECTOR2 size = m_Size * 1.1f;
		SetPosition(GetPosition(), size);
	}
	else
	{
		m_nBigTimer = 0;
		SetPosition(GetPosition(), m_Size);

	}

	if (m_nColorTimer > 0)
	{
		m_nColorTimer--;
		SetColor(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
	}
	else
	{
		m_nColorTimer = 0;
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	CScene2D::Update();
}
//=============================================================================
// �`�揈��
//=============================================================================
void  CJudgeBaggage::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ���菈��
//=============================================================================
void  CJudgeBaggage::HitCheck(void)
{
	for (int nCntPri = 0; nCntPri < CScene::PRIORITY_MAX; nCntPri++)
	{
		CScene* pScene = CScene::GetTop((CScene::PRIORITY)nCntPri);
		if (pScene != NULL)
		{
			do
			{
				CScene* pSceneNext = pScene->GetNext();
				if (pScene->GetObjType() == OBJTYPE_BAGGAGE)
				{
					if (Collision(pScene))
					{
						pScene->Uninit();
						return;
					}
				}

				pScene = pSceneNext;

			} while (pScene != NULL);

		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
bool  CJudgeBaggage::Collision(CScene* pHitObj)
{
	D3DXVECTOR3 HitObjPos = ((CScene2D*)pHitObj)->GetPosition();

	if (HitObjPos.x > m_CollisionRectMin.x &&HitObjPos.x < m_CollisionRectMax.x)
	{
		if (HitObjPos.y > m_CollisionRectMin.y &&HitObjPos.y < m_CollisionRectMax.y)
		{//�I�u�W�F�N�g(�ו�)��������ɓ����Ă�����

			CBaggage::BAGGAGE_TYPE type = ((CBaggage*)pHitObj)->GetType();
			CScore* pScore = CGame::GetScore();
			CLife* pLife = CGame::GetLife();
			if (type == m_Type)
			{//�ݒ肵���^�C�v�Ɖו��̃^�C�v����v���Ă�����
			 /*�X�R�A���Z*/
				if (pScore != NULL) { pScore->AddScore(1); }
				m_nBigTimer = 10;

				if (m_pSound != NULL)
				{
					m_pSound->Play(CSound::SE_SUCCESS);
				}
			}
			else
			{
				/*�_���[�W*/
				if (pLife != NULL) { pLife->AddLife(1); }
				m_nColorTimer = 10;

				if (m_pSound != NULL)
				{
					m_pSound->Play(CSound::SE_MISS);
				}
			}

			return true;
		}
	}
	return false;
}
