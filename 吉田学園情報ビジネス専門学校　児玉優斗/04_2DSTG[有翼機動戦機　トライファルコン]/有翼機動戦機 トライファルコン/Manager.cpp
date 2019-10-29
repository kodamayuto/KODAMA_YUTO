//=============================================================================
//
// �Ǘ��N���X���� [Manager.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "Manager.h"
#include "title.h"
#include "modeSelect.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "fade.h"

//==================================================================
// �ÓI�����o�ϐ�
//==================================================================
CRenderer*			CManager::m_pRenderer = NULL;
CInputKeyboard*		CManager::m_pInputKeyboard = NULL;
CDInputController*	CManager::m_pDInputController = NULL;
CSound*				CManager::m_pSound = NULL;
CFade*				CManager::m_pFade = NULL;
CPause*				CManager::m_pPause = NULL;

CTitle*				CManager::m_pTitle = NULL;
CModeSelect*		CManager::m_pModeSelect = NULL;
CTutorial*			CManager::m_pTutorial = NULL;
CGame*				CManager::m_pGame = NULL;
CResult*			CManager::m_pResult = NULL;
CRanking*			CManager::m_pRanking = NULL;

CManager::MODE		CManager::m_Mode = CManager::MODE_TITLE;
bool				CManager::m_bPauseFrag = false;
//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CManager::CManager()
{
}
CManager::~CManager()
{

}

//==================================================================
// ����������
//==================================================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd)
{
	srand((unsigned int)time(0));

	//�����_���̐���
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}

	if (m_pRenderer != NULL)
	{
		// ����������(�E�B���h�E���쐬���Ă���s��)
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{
			// �I������
			m_pRenderer->Uninit();

			delete m_pRenderer;
			m_pRenderer = NULL;
			return -1;
		}
	}

	m_pSound = CSound::Create(hWnd);

	//�e��e�N�X�`�����[�h
	CBullet::Load();
	CExplosion::Load();
	CPlayer::Load();
	CBg::Load();
	CEnemy::Load();
	CEffect::Load();
	CGauge::Load();
	CNumber::Load();
	CPlayerUI::Load();
	CTime::Load();
	CTitle::Load();
	CTitleLogo::Load();
	CModeSelect::Load();
	CTutorial::Load();
	CResult::Load();
	CRanking::Load();
	CPause::Load();


	SetMode(m_Mode);
	//�|�[�Y�̐���
	m_pPause = CPause::Create();
	m_pFade = CFade::Create(m_Mode);



	//���̓f�o�C�X�̐���
	m_pInputKeyboard = new CInputKeyboard;

	if (m_pInputKeyboard != NULL)
	{
		// ����������(�E�B���h�E���쐬���Ă���s��)
		if (FAILED(m_pInputKeyboard->Init(hInstance,hWnd)))
		{
			// �I������
			m_pInputKeyboard->Uninit();

			delete m_pInputKeyboard;
			m_pInputKeyboard = NULL;
			return -1;
		}
	}

	//�R���g���[���[�̐���
	m_pDInputController = new CDInputController;

	if (m_pDInputController != NULL)
	{
		if (FAILED(m_pDInputController->Init(hInstance,hWnd)))
		{
			m_pDInputController->Uninit();

			delete m_pDInputController;
			m_pDInputController = NULL;
			return -1;
		}
	}


	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CManager::Uninit(void)
{
	switch (m_Mode)
	{
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();

			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case CManager::MODE_SELECT:
		if (m_pModeSelect != NULL)
		{
			m_pModeSelect->Uninit();

			delete m_pModeSelect;
			m_pModeSelect = NULL;
		}
		break;
	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();

			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;

	case CManager::MODE_GAME_CARAVAN:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();

			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	case CManager::MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();

			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	case CManager::MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();

			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;

	}

	//�|�[�Y�폜
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();

		delete m_pPause;
		m_pPause = NULL;
	}

	//�t�F�[�h����
	CScene::ReleaseAll(CScene::OBJTYPE_FADE);

	//�e�N�X�`���j��
	CBullet::Unload();
	CExplosion::Unload();
	CPlayer::Unload();
	CBg::Unload();
	CEnemy::Unload();
	CEffect::Unload();
	CNumber::Unload();
	CPlayerUI::Unload();
	CTime::Unload();
	CTitle::Unload();
	CTitleLogo::Unload();
	CModeSelect::Unload();
	CTutorial::Unload();
	CResult::Unload();
	CRanking::Unload();
	CPause::Unload();

	//�T�E���h
	if (m_pSound != NULL)
	{
		m_pSound->StopAll();
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}


	//����(�L�[�{�[�h)
	if (m_pInputKeyboard != NULL)
	{
		// �I������
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//����(�R���g���[���[)
	if (m_pDInputController != NULL)
	{
		m_pDInputController->Uninit();

		delete m_pDInputController;
		m_pDInputController = NULL;
	}

	//�����_��
	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//==================================================================
// �X�V����
//==================================================================
void CManager::Update(void)
{
	switch (m_Mode)
	{
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Update();
		}
		break;

	case CManager::MODE_SELECT:
		if (m_pModeSelect != NULL)
		{
			m_pModeSelect->Update();
		}
		break;

	case CManager::MODE_GAME_CARAVAN:
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	case CManager::MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	case CManager::MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Update();
		}
		break;

	}

	//�t�F�[�h�̍X�V
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}


	//���̓f�o�C�X�̍X�V
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	if (m_pDInputController != NULL)
	{
		m_pDInputController->Update();
	}


	if (m_bPauseFrag == false)
	{	//�����_���̍X�V
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Update();
		}
	}
	else
	{//�|�[�Y�̍X�V
		if (m_pPause != NULL)
		{
			m_pPause->Update();
		}
	}

}

//==================================================================
// �`�揈��
//==================================================================
void CManager::Draw(void)
{
	switch (m_Mode)
	{
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Draw();
		}
		break;
	case CManager::MODE_SELECT:
		if (m_pModeSelect != NULL)
		{
			m_pModeSelect->Draw();
		}
		break;
	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Draw();
		}
		break;

	case CManager::MODE_GAME_CARAVAN:
		if (m_pGame != NULL)
		{
			m_pGame->Draw();
		}
	case CManager::MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Draw();
		}

		break;
	case CManager::MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Draw();

		}
		break;

	}


	if (m_pFade != NULL)
	{
		m_pFade->Draw();
	}

	if (m_pRenderer != NULL)
	{
		// �`�揈��
		m_pRenderer->Draw();
	}



}


//==================================================================
// ��ʑJ�ڏ���
//==================================================================
HRESULT CManager::SetMode(CManager::MODE mode)
{
	PauseModeChange(false);

	//Uninit
	switch (m_Mode)
	{
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();

			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case CManager::MODE_SELECT:
		if (m_pModeSelect != NULL)
		{
			m_pModeSelect->Uninit();

			delete m_pModeSelect;
			m_pModeSelect = NULL;
		}
		break;
	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();

			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;

	case CManager::MODE_GAME_CARAVAN:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();

			delete m_pGame;
			m_pGame = NULL;
		}
	case CManager::MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();

			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	case CManager::MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();

			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;

	}

	//Init
	switch (mode)
	{
	case CManager::MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
		}

		break;
	case CManager::MODE_SELECT:
		if (m_pModeSelect == NULL)
		{
			m_pModeSelect = CModeSelect::Create();
		}
		break;
	case CManager::MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();
		}
		break;

	case CManager::MODE_GAME_CARAVAN:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}

		break;
	case CManager::MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();
		}
		break;
	case CManager::MODE_RANKING:
		if (m_pRanking == NULL)
		{
			m_pRanking = CRanking::Create();
		}
		break;

	}

	m_Mode = mode;
	return S_OK;
}
void CManager::PauseModeChange(void)
{
	m_bPauseFrag = m_bPauseFrag ? false : true;

	m_pSound->Pause(CSound::GetLabel());
	if (m_pSound != NULL)
	{
		m_pSound->Play(CSound::SOUND_LABEL_SE_003);
	}
}