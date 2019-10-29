//=============================================================================
//
// �^�C�}�[�̏���[2D�|���S��] [timer.cpp]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================5
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "player.h"
#include "number.h"
#include "timer.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
int CTimer::m_nTimer = 0;	//�^�C�}�[
int CTimer::m_nTenMinutes = 0;
int CTimer::m_nOneMinutes = 0;
int CTimer::m_nTenSeconds = 0;
int CTimer::m_nOneSeconds = 0;
int CTimer::m_nTenComma = 0;
int CTimer::m_nOneComma = 0;

// �����L���O�̏����l�ݒ�
int CRankingTimer::m_nRank[RANKING_NUMBER][6] = { { 0, 0, 5, 0, 0, 0 },{ 0, 1, 0, 0, 0, 0 },{ 0, 1, 3, 0, 0, 0 },{ 0, 2, 0, 0, 0, 0 },{ 0, 2, 3, 0, 0, 0 } };

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MINUTES_WIDTH (60.0f)
#define MINUTES_HEIGHT (80.0f)

#define SECONDS_WIDTH (50.0f)
#define SECONDS_HEIGHT (70.0f)

#define COMMA_WIDTH (35.0f)
#define COMMA_HEIGHT (55.0f)

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTimer::CTimer() :CScene(7)
{//�N���A�Ȓl����
	m_nTimer = 0;	//�^�C�}�[
	m_nTenMinutes = 0;
	m_nOneMinutes = 0;
	m_nTenSeconds = 0;
	m_nOneSeconds = 0;
	m_nTenComma = 0;
	m_nOneComma = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTimer::~CTimer()
{
}

//=============================================================================
//�^�C�}�[�̐���
//=============================================================================
CTimer *CTimer::Create(D3DXVECTOR3 pos, TIMEMODE mode)
{
	//�^�C�}�[�̐���
	CTimer *pTimer = NULL;

	switch (mode)
	{
	case TIMEMODE_GAME:					// �Q�[���Ŏg�p
		pTimer = new CGameTimer;
		pTimer->m_pos = pos;
		pTimer->Init();
		break;

	case TIMEMODE_RESULT:				// ���U���g�Ŏg�p
		pTimer = new CResultTimer;
		pTimer->m_pos = pos;
		pTimer->Init();
		break;

	case TIMEMODE_RANKING:				// �����L���O�Ŏg�p
		pTimer = new CRankingTimer;
		pTimer->m_pos = pos;
		pTimer->Init();
		break;

	}

	return pTimer;
}

//=============================================================================
//�Q�[���̃R���X�g���N�^
//=============================================================================
CGameTimer::CGameTimer()
{
	for (int nCntTimer = 0; nCntTimer < TIMER_NUMBER; nCntTimer++)
	{
		m_apNumber[nCntTimer] = NULL;
	}
}

//=============================================================================
//�Q�[���̃f�X�g���N�^
//=============================================================================
CGameTimer::~CGameTimer()
{
	for (int nCntTimer = 0; nCntTimer < TIMER_NUMBER; nCntTimer++)
	{
		m_apNumber[nCntTimer] = 0;
	}
}

//=============================================================================
//�Q�[���̏���������
//=============================================================================
HRESULT CGameTimer::Init(void)
{
	//float fSpace;
	m_nCntFrame = 0;
	bUse = true;

	for (int nCntNumber = 0; nCntNumber < TIMER_NUMBER; nCntNumber++)
	{
		switch (nCntNumber)
		{
		case CTimer::TIMERTYPE_TENMINUTE:
			//10����
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), MINUTES_WIDTH, MINUTES_HEIGHT);
			break;
		case CTimer::TIMERTYPE_ONEMINUTE:
			//1����
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z), MINUTES_WIDTH, MINUTES_HEIGHT);
			break;

		case CTimer::TIMERTYPE_TENSECONDS:
			//10�b��
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 270.0f, m_pos.y + 5.0f, m_pos.z), SECONDS_WIDTH, SECONDS_HEIGHT);
			break;
		case CTimer::TIMERTYPE_ONESECONDS:
			//1�b��
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 350.0f, m_pos.y + 5.0f, m_pos.z), SECONDS_WIDTH, SECONDS_HEIGHT);
			break;
		case CTimer::TIMERTYPE_TENCOMMASECONDS:
			//10�R���}�b
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 480.0f, m_pos.y + 10.0f, m_pos.z), COMMA_WIDTH, COMMA_HEIGHT);
			break;
		case CTimer::TIMERTYPE_ONECOMMASECONDS:
			//1�R���}�b
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 540.0f, m_pos.y + 10.0f, m_pos.z), COMMA_WIDTH, COMMA_HEIGHT);
			break;
		}
	}

	return S_OK;
}

//=============================================================================
//�Q�[���̏I������
//=============================================================================
void CGameTimer::Uninit(void)
{
	// �Q�[�����I���������ɁA���U���g�ɃX�R�A��n��
	CManager::SetTimer(m_nTenMinutes, m_nOneMinutes, m_nTenSeconds, m_nOneSeconds, m_nTenComma, m_nOneComma);

	for (int nCntTimer = 0; nCntTimer < TIMER_NUMBER; nCntTimer++)
	{
		if (m_apNumber[nCntTimer] != NULL)
		{
			m_apNumber[nCntTimer]->Uninit();
			delete m_apNumber[nCntTimer];
			m_apNumber[nCntTimer] = NULL;
		}
	}

	// �������g�̔j��
	Release();
}

//=============================================================================
//�Q�[���̍X�V����
//=============================================================================
void CGameTimer::Update(void)
{
	//�J�E���g�p�t���[���̉��Z
	m_nCntFrame++;

	if (bUse == true)
	{
		m_nOneComma++;
	}
	//�P�O��R���}�b�𑝉�
	if (m_nCntFrame % 6 == 0)
	{//6�t���[���ōX�V
		m_nTenComma++;
	}

	if (m_nTenComma > 9)
	{//�R���}10�b�䂪�ő�܂ł�������
		m_nTenComma = 0;
		m_nOneSeconds++;
	}

	if (m_nOneSeconds > 9)
	{
		m_nTenSeconds++;
		m_nOneSeconds = 0;
	}

	if (m_nTenSeconds > 5)
	{
		m_nOneMinutes++;

		m_nTenSeconds = 0;
	}
	if (m_nOneMinutes > 9)
	{
		m_nTenMinutes++;

		m_nOneMinutes = 0;
	}

	//=======================================================
	//�ԍ��̃e�N�X�`���ݒ�
	//=======================================================
	//��
	m_apNumber[0]->SetNumber(m_nTenMinutes);
	m_apNumber[1]->SetNumber(m_nOneMinutes);

	//�b
	m_apNumber[2]->SetNumber(m_nTenSeconds);
	m_apNumber[3]->SetNumber(m_nOneSeconds);

	//�R���}�b
	m_apNumber[4]->SetNumber(m_nTenComma);
	m_apNumber[5]->SetNumber(m_nOneComma);
}

//=============================================================================
//�Q�[���̕`�揈��
//=============================================================================
void CGameTimer::Draw(void)
{
	for (int nCntTimer = 0; nCntTimer < TIMER_NUMBER; nCntTimer++)
	{
		m_apNumber[nCntTimer]->Draw();
	}
}

//=============================================================================
//���U���g�̃R���X�g���N�^
//=============================================================================
CResultTimer::CResultTimer()
{
	for (int nCntTimer = 0; nCntTimer < TIMER_NUMBER; nCntTimer++)
	{
		m_apNumber[nCntTimer] = NULL;
	}
}

//=============================================================================
//���U���g�̃f�X�g���N�^
//=============================================================================
CResultTimer::~CResultTimer()
{
}

//=============================================================================
//���U���g�̏���������
//=============================================================================
HRESULT CResultTimer::Init()
{
	for (int nCntNumber = 0; nCntNumber < TIMER_NUMBER; nCntNumber++)
	{
		switch (nCntNumber)
		{
		case CTimer::TIMERTYPE_TENMINUTE:
			//10����
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), MINUTES_WIDTH, MINUTES_HEIGHT);
			break;
		case CTimer::TIMERTYPE_ONEMINUTE:
			//1����
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z), MINUTES_WIDTH, MINUTES_HEIGHT);
			break;

		case CTimer::TIMERTYPE_TENSECONDS:
			//10�b��
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 290.0f, m_pos.y + 5.0f, m_pos.z), SECONDS_WIDTH, SECONDS_HEIGHT);
			break;
		case CTimer::TIMERTYPE_ONESECONDS:
			//1�b��
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 370.0f, m_pos.y + 5.0f, m_pos.z), SECONDS_WIDTH, SECONDS_HEIGHT);
			break;
		case CTimer::TIMERTYPE_TENCOMMASECONDS:
			//10�R���}�b
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 470.0f, m_pos.y + 10.0f, m_pos.z), COMMA_WIDTH, COMMA_HEIGHT);
			break;
		case CTimer::TIMERTYPE_ONECOMMASECONDS:
			//1�R���}�b
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 530.0f, m_pos.y + 10.0f, m_pos.z), COMMA_WIDTH, COMMA_HEIGHT);
			break;
		}
	}

	// �Q�[���̃X�R�A���擾
	SetResultTimer(CManager::GetTenMinutes(), CManager::GetOneMinutes(), CManager::GetTenSeconds(), CManager::GetOneSeconds(), CManager::GetTenComma(), CManager::GetOneComma());

	return S_OK;
}

//=============================================================================
//���U���g�̏I������
//=============================================================================
void CResultTimer::Uninit(void)
{
	// �Q�[�����I���������ɁA���U���g�ɃX�R�A��n��
	CManager::SetTimer(m_nTenMinutes, m_nOneMinutes, m_nTenSeconds, m_nOneSeconds, m_nTenComma, m_nOneComma);

	for (int nCntTimer = 0; nCntTimer < TIMER_NUMBER; nCntTimer++)
	{
		if (m_apNumber[nCntTimer] != NULL)
		{
			m_apNumber[nCntTimer]->Uninit();
			delete m_apNumber[nCntTimer];
			m_apNumber[nCntTimer] = NULL;
		}
	}

	// �������g�̔j��
	Release();
}

//=============================================================================
//���U���g�̍X�V����
//=============================================================================
void CResultTimer::Update(void)
{
}

//=============================================================================
//���U���g�̕`�揈��
//=============================================================================
void CResultTimer::Draw(void)
{
	for (int nCntTimer = 0; nCntTimer < TIMER_NUMBER; nCntTimer++)
	{
		m_apNumber[nCntTimer]->Draw();
	}
}

//=============================================================================
//�X�R�A�̐ݒ�
//=============================================================================
void CResultTimer::SetResultTimer(int nTenMinutes, int nOneMinutes, int nTenSeconds, int nOneSeconds, int nTenComma, int nOneComma)
{
	m_nTenMinutes = nTenMinutes;
	m_nOneMinutes = nOneMinutes;
	m_nTenSeconds = nTenSeconds;
	m_nOneSeconds = nOneSeconds;
	m_nTenComma = nTenComma;
	m_nOneComma = nOneComma;

	//=======================================================
	//�ԍ��̃e�N�X�`���ݒ�
	//=======================================================
	//��
	m_apNumber[0]->SetNumber(m_nTenMinutes);
	m_apNumber[1]->SetNumber(m_nOneMinutes);

	//�b
	m_apNumber[2]->SetNumber(m_nTenSeconds);
	m_apNumber[3]->SetNumber(m_nOneSeconds);

	//�R���}�b
	m_apNumber[4]->SetNumber(m_nTenComma);
	m_apNumber[5]->SetNumber(m_nOneComma);

	//�X�R�A�̏�����
	//CManager::SetTimer(0, 0, 0, 0, 0, 0);
}

//=============================================================================
//�����L���O�̃R���X�g���N�^
//=============================================================================
CRankingTimer::CRankingTimer()
{
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntNumber = 0; nCntNumber < TIMER_NUMBER; nCntNumber++)
		{
			m_apNumber[nCntRank][nCntNumber] = NULL;
		}
	}

	// �ϐ��̏�����
	m_nChange = 0;
}

//=============================================================================
//�����L���O�̃f�X�g���N�^
//=============================================================================
CRankingTimer::~CRankingTimer()
{
}

//=============================================================================
//�����L���O�̏���������
//=============================================================================
HRESULT CRankingTimer::Init(void)
{
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntNumber = 0; nCntNumber < TIMER_NUMBER; nCntNumber++)
		{
			switch (nCntNumber)
			{
			case CTimer::TIMERTYPE_TENMINUTE:
				//10����
				//�����̐���
				m_apNumber[nCntRank][nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (120.0f * nCntRank), m_pos.z), 40.0f, 60.0f);
				break;
			case CTimer::TIMERTYPE_ONEMINUTE:
				//1����
				//�����̐���
				m_apNumber[nCntRank][nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 80.0f, m_pos.y + (120.0f * nCntRank), m_pos.z), 40.0f, 60.0f);
				break;

			case CTimer::TIMERTYPE_TENSECONDS:
				//10�b��
				//�����̐���
				m_apNumber[nCntRank][nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y + 5.0f + (120.0f * nCntRank), m_pos.z), 30.0f, 50.0f);
				break;
			case CTimer::TIMERTYPE_ONESECONDS:
				//1�b��
				//�����̐���
				m_apNumber[nCntRank][nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 270.0f, m_pos.y + 5.0f + (120.0f * nCntRank), m_pos.z), 30.0f, 50.0f);
				break;
			case CTimer::TIMERTYPE_TENCOMMASECONDS:
				//10�R���}�b
				//�����̐���
				m_apNumber[nCntRank][nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 380.0f, m_pos.y + 10.0f + (120.0f * nCntRank), m_pos.z), COMMA_WIDTH, COMMA_HEIGHT);
				break;
			case CTimer::TIMERTYPE_ONECOMMASECONDS:
				//1�R���}�b
				//�����̐���
				m_apNumber[nCntRank][nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + 450.0f, m_pos.y + 10.0f + (120.0f * nCntRank), m_pos.z), COMMA_WIDTH, COMMA_HEIGHT);
				break;
			}
		}
	}

	SetRankingTimer();

	return S_OK;
}

//=============================================================================
//�����L���O�̏I������
//=============================================================================
void CRankingTimer::Uninit(void)
{
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntTimer = 0; nCntTimer < TIMER_NUMBER; nCntTimer++)
		{
			if (m_apNumber[nCntRank][nCntTimer] != NULL)
			{
				m_apNumber[nCntRank][nCntTimer]->Uninit();
				delete m_apNumber[nCntRank][nCntTimer];
				m_apNumber[nCntRank][nCntTimer] = NULL;
			}
		}
	}

	// �������g�̔j��
	Release();
}

//=============================================================================
//�����L���O�̍X�V����
//=============================================================================
void CRankingTimer::Update(void)
{

}

//=============================================================================
//�����L���O�̕`�揈��
//=============================================================================
void CRankingTimer::Draw(void)
{
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntNumber = 0; nCntNumber < TIMER_NUMBER; nCntNumber++)
		{	//�`�揈��
			m_apNumber[nCntRank][nCntNumber]->Draw();
		}
	}
}

//=============================================================================
//�����L���O�̐ݒ�
//=============================================================================
void CRankingTimer::SetRankingTimer()
{
	int nRank[6];

	// �z��Ɍ��݂̃X�R�A����
	nRank[0] = CManager::GetTenMinutes();
	nRank[1] = CManager::GetOneMinutes();
	nRank[2] = CManager::GetTenSeconds();
	nRank[3] = CManager::GetOneSeconds();
	nRank[4] = CManager::GetTenComma();
	nRank[5] = CManager::GetOneComma();

	// �����L���O�̐ݒ�
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntNum = 0; nCntNum < TIMER_NUMBER; )
		{
			if (nRank[nCntNum] == m_nRank[nCntRank][nCntNum])
			{
				nCntNum++;
			}
			else if (nRank[nCntNum] < m_nRank[nCntRank][nCntNum])
			{
				m_nChange = m_nRank[nCntRank][0];
				m_nRank[nCntRank][0] = nRank[0];
				nRank[0] = m_nChange;

				m_nChange = m_nRank[nCntRank][1];
				m_nRank[nCntRank][1] = nRank[1];
				nRank[1] = m_nChange;

				m_nChange = m_nRank[nCntRank][2];
				m_nRank[nCntRank][2] = nRank[2];
				nRank[2] = m_nChange;

				m_nChange = m_nRank[nCntRank][3];
				m_nRank[nCntRank][3] = nRank[3];
				nRank[3] = m_nChange;

				m_nChange = m_nRank[nCntRank][4];
				m_nRank[nCntRank][4] = nRank[4];
				nRank[4] = m_nChange;

				m_nChange = m_nRank[nCntRank][5];
				m_nRank[nCntRank][5] = nRank[5];
				nRank[5] = m_nChange;
				break;
			}
			else
			{
				break;
			}
		}

		//=======================================================
		//�ԍ��̃e�N�X�`���ݒ�
		//=======================================================
		//��
		m_apNumber[nCntRank][0]->SetNumber(m_nRank[nCntRank][0]);
		m_apNumber[nCntRank][1]->SetNumber(m_nRank[nCntRank][1]);

		//�b
		m_apNumber[nCntRank][2]->SetNumber(m_nRank[nCntRank][2]);
		m_apNumber[nCntRank][3]->SetNumber(m_nRank[nCntRank][3]);

		//�R���}�b
		m_apNumber[nCntRank][4]->SetNumber(m_nRank[nCntRank][4]);
		m_apNumber[nCntRank][5]->SetNumber(m_nRank[nCntRank][5]);
	}

	//�X�R�A�̏�����
	CManager::SetTimer(0, 0, 0, 0, 0, 0);
}