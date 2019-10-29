//=============================================================================
//
// �X�R�A���� [Score.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "Score.h"
#include "number.h"
#include "Manager.h"


//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CScore::CScore(CScene::PRIORITY pri) : CScene(pri, OBJTYPE_2D)
{

}
CScore::~CScore()
{

}

//==================================================================
// �ݒ菈��
//==================================================================
void CScore::Set(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect, int nScore,D3DXCOLOR col,  int nScoreDigit)
{
	m_Pos = pos;
	m_PolygonRect = polygonRect;
	m_Color = col;

	m_nScore = nScore;
	if (m_nScore < 0) { m_nScore = 0; }
	if (m_nScore > SCORECOUNT_MAX) { m_nScore = SCORECOUNT_MAX; }

	CNumber* pNumber = NULL;

	int nDigit = nScoreDigit;

	//�����␳
	if (nDigit < 0) { nDigit = 0; }
	if (nDigit > MAX_DIGIT) { nDigit = MAX_DIGIT; }

	for (int nCntNumber = 0; nCntNumber < nScoreDigit; nCntNumber++)
	{
		int nDigit = m_nScore % (int)pow(10, nCntNumber + 1) / (int)pow(10, nCntNumber);

		if (Create(pNumber))
		{
			pNumber->Set(pos + D3DXVECTOR3((-polygonRect.x * nCntNumber) - 0.25f,0.0f,0.0f),polygonRect, nDigit,m_Color);

			m_vecNumber.emplace_back(pNumber);
		}
	}
}

//==================================================================
// ����������
//==================================================================
HRESULT CScore::Init(void)
{
	m_vecNumber.clear();
	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CScore::Uninit(void)
{
	for (auto itr = m_vecNumber.begin(); itr != m_vecNumber.end(); itr++)
	{//�����z��̍폜����
		if ((*itr) != NULL)
		{
			(*itr)->Uninit();
			delete (*itr);
			(*itr) = NULL;
		}
	}
	m_vecNumber.clear();


	Release();
}

//==================================================================
// �X�V����
//==================================================================
void CScore::Update(void)
{
	//�����̍X�V
	int nCntNum = 0;
	for (auto itr = m_vecNumber.begin(); itr != m_vecNumber.end(); itr++)
	{
		int nDigit = m_nScore % (int)pow(10, nCntNum + 1) / (int)pow(10, nCntNum);
		if ((*itr) != NULL)
		{
			(*itr)->Set(m_Pos + D3DXVECTOR3(((-m_PolygonRect.x - 0.25f) * nCntNum), 0.0f, 0.0f), m_PolygonRect, nDigit, m_Color);
			(*itr)->Update();
		}
		nCntNum++;
	}
}

//==================================================================
// �`�揈��
//==================================================================
void CScore::Draw(void)
{
	//�����̕`��
	for (auto itr = m_vecNumber.begin(); itr != m_vecNumber.end(); itr++)
	{
		if ((*itr) != NULL)
		{
			(*itr)->Draw();
		}
	}
}

//==================================================================
// �X�R�A�ݒ菈��
//==================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;

	//���l�␳
	if (m_nScore < 0) { m_nScore = 0; }
	if (m_nScore > SCORECOUNT_MAX) { m_nScore = SCORECOUNT_MAX; }

	int nCntNum = 0;
	for (auto itr = m_vecNumber.begin(); itr != m_vecNumber.end(); itr++)
	{
		int nDigit = m_nScore % (int)pow(10, nCntNum + 1) / (int)pow(10, nCntNum);
		if ((*itr) != NULL)
		{
			(*itr)->SetNumber(nDigit);
		}

		nCntNum++;
	}
}
//==================================================================
// �X�R�A���Z����
//==================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;

	//���l�␳
	if (m_nScore < 0) { m_nScore = 0; }
	if (m_nScore > SCORECOUNT_MAX) { m_nScore = SCORECOUNT_MAX; }

	int nCntNum = 0;
	for (auto itr = m_vecNumber.begin(); itr != m_vecNumber.end(); itr++)
	{
		int nDigit = m_nScore % (int)pow(10, nCntNum + 1) / (int)pow(10, nCntNum);
		if ((*itr) != NULL)
		{
			(*itr)->SetNumber(nDigit);
		}

		nCntNum++;
	}
}