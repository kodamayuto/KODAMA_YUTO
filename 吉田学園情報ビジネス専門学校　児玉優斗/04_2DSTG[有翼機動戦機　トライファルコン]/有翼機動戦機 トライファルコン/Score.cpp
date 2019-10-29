//=============================================================================
//
// �X�R�A�N���X���� [Score.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "Score.h"
#include "number.h"

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CScore::CScore() : CScene(5)
{
	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		m_pNumber[nCntScore] = NULL;
	}

	m_nScore = 0;
}
CScore::~CScore()
{

}

//==================================================================
// ��������
//==================================================================
CScore* CScore::Create(D3DXVECTOR3 pos)
{
	CScore* pScore = NULL;
	pScore = new CScore;

	if (pScore != NULL)
	{
		pScore->Init(pos);
	}

	return pScore;
}

//==================================================================
// ����������
//==================================================================
HRESULT CScore::Init(void)
{
	return S_OK;
}
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	Init();
	m_pos = pos;
	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		m_pNumber[nCntScore] = CNumber::Create(D3DXVECTOR3(m_pos.x - (30.0f * nCntScore),m_pos.y,0.0f),
												D3DXVECTOR2(30.0f,40.0f),
												0);
	}
	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CScore::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		if (m_pNumber[nCntScore] != NULL)
		{
			m_pNumber[nCntScore]->Uninit();

			delete m_pNumber[nCntScore];
			m_pNumber[nCntScore] = NULL;

		}
	}

	Release();
}

//==================================================================
// �X�V����
//==================================================================
void CScore::Update(void)
{
	//m_pos.y += 0.1f;
	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		//m_pNumber[nCntScore]->SetPosition(D3DXVECTOR3(m_pos.x - (27.0f * nCntScore), m_pos.y, 0.0f));
		m_pNumber[nCntScore]->Update();
	}
}

//==================================================================
// �`�揈��
//==================================================================
void CScore::Draw(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		m_pNumber[nCntScore]->Draw();
	}

}

//==================================================================
// �X�R�A�������
//==================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;

	if (m_nScore >= 999999999)
	{
		m_nScore = 999999999;
	}

	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		int nDigit = m_nScore % (int)pow(10, nCntScore + 1) / (int)pow(10, nCntScore);
		m_pNumber[nCntScore]->SetNumber(nDigit);
	}
}

//==================================================================
// �X�R�A���Z����
//==================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;

	if (m_nScore >= 999999999)
	{
		m_nScore = 999999999;
	}
	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		int nDigit = m_nScore % (int)pow(10, nCntScore + 1) / (int)pow(10, nCntScore);
		m_pNumber[nCntScore]->SetNumber(nDigit);
	}
}