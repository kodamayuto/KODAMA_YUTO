//=============================================================================
//
// �Q�[����ʊǗ��N���X���� [game.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "game.h"
#include "fade.h"
#include "sound.h"

//==================================================================
// �ÓI�����o�ϐ�
//==================================================================
CPlayer* CGame::m_pPlayer = NULL;
CScore* CGame::m_pScore = NULL;
CPlayerUI* CGame::m_pPlayerUI = NULL;
CTime* CGame::m_pTime = NULL;
CEGenerator* CGame::m_pEGenerator = NULL;
int CGame::m_nRespawnTimer = -1;

int CGame::m_nScore = 0;
int CGame::m_nNumAbsorb = 0;

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CGame::CGame()
{
	m_nRespawnTimer = -1;
	m_nNumAbsorb = 0;
}
CGame::~CGame()
{

}

//==================================================================
// ��������
//==================================================================
CGame* CGame::Create(void)
{
	CGame* pGame = NULL;

	pGame = new CGame;

	if (pGame != NULL)
	{
		pGame->Init();
	}
	return pGame;
}
//==================================================================
// ����������
//==================================================================
HRESULT CGame::Init(void)
{
	//�I�u�W�F�N�g�̐���

	m_pPlayerUI = CPlayerUI::Create();
	CPlayer::SetStock();
	m_pPlayer = CPlayer::Create();

	m_pEGenerator = CEGenerator::Create(CEGenerator::MODE_3MIN_CARAVAN);

	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(1220.0f, 20.0f, 0.0f));
	//�^�C�}�[�̐���
	m_pTime = CTime::Create(D3DXVECTOR3(1100.0f, 200.0f, 0.0f), true);
	m_pTime->SetTime(180);

	CBg::Create();

	//BGM�炷
	CSound* pSound = CManager::GetSound();
	pSound->StopAll();

	if (pSound != NULL)
	{
		int nSoundData = rand() % 2;

		switch (nSoundData)
		{
		case 0:
			pSound->Play(CSound::SOUND_LABEL_BGM_000);
			break;
		case 1:
			pSound->Play(CSound::SOUND_LABEL_BGM_001);
			break;
		}
	}

	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CGame::Uninit(void)
{
	CSound* pSound = CManager::GetSound();

	//�I�u�W�F�N�g�S�j��
	CScene::ReleaseAll();

	m_pPlayer = NULL;
	m_pScore = NULL;
	m_pPlayerUI = NULL;
	m_pTime = NULL;
	m_pEGenerator = NULL;

	if (pSound != NULL)
	{
		pSound->StopAll();
	}
}

//==================================================================
// �X�V����
//==================================================================
void CGame::Update(void)
{
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CDInputController* pController = CManager::GetController();
	CFade*			pFade = CManager::GetFade();

	if (pInput->GetTrigger(DIK_P) == true || pController != NULL && pController->GetTrigger(CDInputController::DIJS_BUTTON_9) == true)
	{
		CManager::PauseModeChange();
	}

	//�v���C���[�̍ďo��
	if (m_nRespawnTimer >= -1)
	{
		m_nRespawnTimer--;

		if (m_nRespawnTimer == 0)
		{
			if (CPlayer::GetStock() >= 0)
			{
				m_pPlayer = NULL;
				m_pPlayer = CPlayer::Create();

				m_nRespawnTimer = -1;
			}
			else
			{
				if (pFade != NULL && *pFade->GetFade() != CFade::FADE_OUT)
				{
					m_nScore = m_pScore->GetScore();
						pFade->SetFade(CManager::MODE_RESULT, CFade::COLOR_WHITE);
				}

			}
		}
	}

	//�I������Ƃ�
	if (pInput != NULL && pFade != NULL)
	{
		if (*pFade->GetFade() != CFade::FADE_OUT)
		{
			if (m_pTime->GetTime() <= 0)
			{
				m_nScore = m_pScore->GetScore();

				pFade->SetFade(CManager::MODE_RESULT, CFade::COLOR_WHITE);
			}
		}
	}
}

//==================================================================
// �`�揈��
//==================================================================
void CGame::Draw(void)
{

}

