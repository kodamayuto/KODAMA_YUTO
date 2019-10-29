//=============================================================================
//
//	�A�C�e���J�E���^�̏���[�V�[��] [itemcounter.cpp]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================5
#include "main.h"
#include "renderer.h"
#include "itemcounter.h"
#include "scene.h"
#include "number.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CNumber *CItemCounter::m_apNumber[COUNTER_NUMBER] = {};		//����
 int CItemCounter::m_nCoin = 0;								//�R�C���̐�
 int CItemCounter::m_nKey = 0;								//�J�M�̐�
 int CItemCounter::m_nKeyMax = 0;								//�J�M�̍ő吔

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	COUNTER_WIDTH (30.0f)
#define	COUNTER_HEIGHT (45.0f)


//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CItemCounter::CItemCounter(int nPriority, OBJTYPE type) : CScene(nPriority, type)
{
}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�Ō�ɌĂяo�����
//=============================================================================
CItemCounter::~CItemCounter()
{
}

//=============================================================================
// �֐����F�A�C�e���J�E���^�̐���
// �֐��̊T�v�F2�A�C�e���J�E���^�𐶐�����
//=============================================================================
CItemCounter * CItemCounter::Create(void)
{
	//�X�R�A�̐���
	CItemCounter *pItemCounter;
	pItemCounter = new CItemCounter;

	if (pItemCounter != NULL)
	{
		//�X�R�A�̏���������
		pItemCounter->Init();
	}

	return pItemCounter;
}

//=============================================================================
// �֐����F�A�C�e���J�E���^�̏���������
// �֐��̊T�v�F--
//=============================================================================
HRESULT CItemCounter::Init(void)
{

	//�����̐���
	m_apNumber[0] = CNumber::Create(D3DXVECTOR3(250.0f, 50.0f, 0.0f), COUNTER_WIDTH, COUNTER_HEIGHT);
	m_apNumber[1] = CNumber::Create(D3DXVECTOR3(250.0f, 150.0f, 0.0f), COUNTER_WIDTH, COUNTER_HEIGHT);
	m_apNumber[2] = CNumber::Create(D3DXVECTOR3(350.0f, 150.0f, 0.0f), COUNTER_WIDTH, COUNTER_HEIGHT);

	//�X�R�A�̃I�u�W�F�N�g�̐ݒ�
	SetObjType(CScene::OBJTYPE_ITEMCOUNTER);

	//�R�C���̐��̏�����
	m_nCoin = 0;

	//�J�M�̐��̏�����
	m_nKey = 0;

	//�J�M�̍ő吔�̏�����
	m_nKeyMax = 6;
	m_apNumber[2]->SetNumber(m_nKeyMax);

	return S_OK;
}

//=============================================================================
// �֐����F�A�C�e���J�E���^�̏I������
// �֐��̊T�v�F�������I�������ăI�u�W�F�N�g��j������
//=============================================================================
void CItemCounter::Uninit(void)
{
	for (int nCntItemCounter = 0; nCntItemCounter < COUNTER_NUMBER; nCntItemCounter++)
	{
		m_apNumber[nCntItemCounter]->Uninit();
		delete m_apNumber[nCntItemCounter];
		m_apNumber[nCntItemCounter] = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �֐����F�A�C�e���J�E���^�̍X�V����
// �֐��̊T�v�F--
//=============================================================================
void CItemCounter::Update(void)
{

}

//=============================================================================
// �֐����F�A�C�e���J�E���^�̕`�揈��
// �֐��̊T�v�F--
//=============================================================================
void CItemCounter::Draw(void)
{
	for (int nCntItemCounter = 0; nCntItemCounter < COUNTER_NUMBER; nCntItemCounter++)
	{
		m_apNumber[nCntItemCounter]->Draw();
	}
}

//=============================================================================
// �֐����F�R�C���̐��̎擾����
// �֐��̊T�v�F--
//=============================================================================
int CItemCounter::GetCoin(void)
{
	return m_nCoin;
}

//=============================================================================
// �֐����F�J�M�̐��̎擾����
// �֐��̊T�v�F--
//=============================================================================
int CItemCounter::GetKey(void)
{
	return m_nKey;
}

//=============================================================================
// �֐����F�J�M�̐��̎擾����
// �֐��̊T�v�F--
//=============================================================================
int CItemCounter::GetMaxKey(void)
{
	return m_nKeyMax;
}

//=============================================================================
// �֐����F�R�C���̐��̉��Z����
// �֐��̊T�v�F--
//=============================================================================
void CItemCounter::AddCoin(int nValue)
{
	m_nCoin += nValue;
	m_apNumber[0]->SetNumber(m_nCoin);

}

//=============================================================================
// �֐����F�J�M�̐��̉��Z����
// �֐��̊T�v�F--
//=============================================================================
void CItemCounter::AddKey(int nValue)
{
	m_nKey += nValue;
	if (m_nKey > 6)
	{
		m_nKey = 6;
	}
	m_apNumber[1]->SetNumber(m_nKey);
}

//=============================================================================
// �֐����F�J�M�̍ő吔�̉��Z����
// �֐��̊T�v�F--
//=============================================================================
void CItemCounter::AddKeyMax(int nValue)
{
	m_nKeyMax += nValue;
	m_apNumber[2]->SetNumber(m_nKey);

}

//=============================================================================
// �֐����F�R�C���̐��̐ݒ�
// �֐��̊T�v�F--
//=============================================================================
void CItemCounter::SetCoinNum(int nValue)
{
	m_nCoin = nValue;
	m_apNumber[0]->SetNumber(m_nCoin);

}
