//=============================================================================
//
// �Ǘ��N���X���� [Manager.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "Manager.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "sceneBillboard.h"

#include "pause.h"
#include "fade.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
//==================================================================
// �ÓI�����o�ϐ�
//==================================================================
CRenderer* CManager::m_pRenderer = NULL;
CInputKeyboard* CManager::m_pInputKeyboard = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;
CDebugProc* CManager::m_pDebugProc = NULL;

CFade*				CManager::m_pFade = NULL;
CPause*				CManager::m_pPause = NULL;
CSound*				CManager::m_pSound = NULL;
CInputXPad*			CManager::m_pXInput = NULL;

//��ԑJ�ڗp�̃|�C���^
CTitle* CManager::m_pTitle = NULL;							//�^�C�g��
CTutorial* CManager::m_pTutorial = NULL;					//�`���[�g���A��
CGame* CManager::m_pGame = NULL;							//�Q�[��
CResult* CManager::m_pResult = NULL;						//���U���g
CRanking* CManager::m_pRanking = NULL;							//�Q�[��


CManager::MODE CManager::m_Mode = CManager::MODE_TITLE;		//���݂̉�ʏ��
CManager::MODE CManager::m_OrgMode = CManager::MODE_NONE;	//��O�̉�ʏ��
bool CManager::m_bPauseFlag = false;

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

	CTexture::Load();

	//�f�o�b�N�Ǘ��N���X�̐���
	Create(m_pDebugProc);

	//�|�[�Y��ʂ̐���
	Create(m_pPause);

	//�J�����E���C�g�̐���
	Create(m_pCamera);
	Create(m_pLight);

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

	//���̓N���X(XInput�R���g���[���[)�̐���
	if (m_pXInput == NULL)
	{
		m_pXInput = new CInputXPad;
		if (m_pXInput != NULL)
		{
			m_pXInput->Init(hInstance, hWnd);
		}
	}


	//�t�F�[�h�̐���
	m_pFade = CFade::Create(CManager::MODE_TITLE);

	//���[�h�̐ݒ�
	SetMode(m_Mode);

	//�R�}���h�o�^
	CCommand::RegistCommand("ENTER", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_RETURN);

	CCommand::RegistCommand("PAUSE", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_P);

	CCommand::RegistCommand("PAUSE_MENU_UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_UP);
	CCommand::RegistCommand("PAUSE_MENU_UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_W);
	CCommand::RegistCommand("PAUSE_MENU_DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_DOWN);
	CCommand::RegistCommand("PAUSE_MENU_DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_S);
	CCommand::RegistCommand("UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_W);
	CCommand::RegistCommand("RIGHT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_D);
	CCommand::RegistCommand("LEFT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_A);
	CCommand::RegistCommand("DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_S);

	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CManager::Uninit(void)
{

	//�I�u�W�F�N�g�S�j��
	CScene::ReleaseAll(true);

	//�t�F�[�h�j��
	Release(m_pFade);

	//Uninit
	switch (m_Mode)
	{
	case CManager::MODE_LOGO:
		break;
	case CManager::MODE_TITLE:
		Release(m_pTitle);
		break;
	case CManager::MODE_SELECT:
		break;
	case CManager::MODE_TUTORIAL:
		Release(m_pTutorial);
		break;
	case CManager::MODE_GAME:
		Release(m_pGame);
		break;
	case CManager::MODE_RESULT:
		Release(m_pResult);
		break;
	case CManager::MODE_RANKING:
		Release(m_pRanking);
		break;
	case CManager::MODE_OPTION:
		break;
	}

	if (m_pSound != NULL)
	{
		m_pSound->StopAll();
		Release(m_pSound);
	}

	//�L�[�{�[�h
	Release(m_pInputKeyboard);

	//XPad�R���g���[���[
	Release(m_pXInput);

	//�e�N�X�`���j��
	CTexture::Unload();

	//�|�[�Y��ʂ̐���
	Release(m_pPause);

	//�J����
	Release(m_pCamera);
	//���C�g
	Release(m_pLight);

	//�f�o�b�N
	Release(m_pDebugProc);

	//�����_���̍폜
	Release(m_pRenderer);

}

//==================================================================
// �X�V����
//==================================================================
void CManager::Update(void)
{
	//Update
	switch (m_Mode)
	{
	case CManager::MODE_LOGO:
		break;
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL) { m_pTitle->Update(); }
		break;
	case CManager::MODE_SELECT:
		break;
	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL) { m_pTutorial->Update(); }
		break;
	case CManager::MODE_GAME:
		if (m_pGame != NULL) { m_pGame->Update(); }
		break;
	case CManager::MODE_RESULT:
		if (m_pResult != NULL) { m_pResult->Update(); }
		break;
	case CManager::MODE_RANKING:
		if (m_pRanking != NULL) { m_pRanking->Update(); }
		break;
	case CManager::MODE_OPTION:
		break;
	}


	if (m_pInputKeyboard != NULL)
	{
		// �X�V����
		m_pInputKeyboard->Update();
	}


	if (m_pCamera != NULL)
	{
		// �X�V����
		m_pCamera->Update();
	}
	if (m_pLight != NULL)
	{
		// �X�V����
		m_pLight->Update();
	}

	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	if (m_bPauseFlag == false)
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

	if (m_pInputKeyboard->GetPress(DIK_Q) == true &&
		m_pInputKeyboard->GetTrigger(DIK_P) == true)
	{
		//�I�u�W�F�N�g�S�j��
		CScene::ReleaseAll(false);
	}

	CDebugProc::Print("MODE = %s\n",GetModeName());
}

//==================================================================
// �`�揈��
//==================================================================
void CManager::Draw(void)
{
	//Draw
	switch (m_Mode)
	{
	case CManager::MODE_LOGO:
		break;
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL) { m_pTitle->Draw(); }
		break;
	case CManager::MODE_SELECT:
		break;
	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL) { m_pTutorial->Draw(); }
		break;
	case CManager::MODE_GAME:
		if (m_pGame != NULL) { m_pGame->Draw(); }
		break;
	case CManager::MODE_RESULT:
		if (m_pResult != NULL) { m_pResult->Draw(); }
		break;
	case CManager::MODE_RANKING:
		if (m_pRanking != NULL) { m_pRanking->Draw(); }
		break;
	case CManager::MODE_OPTION:
		break;
	}

	if (m_pRenderer != NULL)
	{
		// �`�揈��
		m_pRenderer->Draw();
	}
}

//==================================================================
// ���[�h�ݒ菈��
//==================================================================
HRESULT CManager::SetMode(MODE mode)
{
	//Uninit
	switch (m_Mode)
	{
	case CManager::MODE_LOGO:
		break;
	case CManager::MODE_TITLE:
		Release(m_pTitle);//���
		break;
	case CManager::MODE_SELECT:
		break;
	case CManager::MODE_TUTORIAL:
		Release(m_pTutorial);
		break;
	case CManager::MODE_GAME:
		Release(m_pGame);
		break;
	case CManager::MODE_RESULT:
		Release(m_pResult);
		break;
	case CManager::MODE_RANKING:
		Release(m_pRanking);
		break;
	case CManager::MODE_OPTION:
		break;
	}

	switch (mode)
	{
	case CManager::MODE_LOGO:
		break;
	case CManager::MODE_TITLE:
		Create(m_pTitle); //����
		break;
	case CManager::MODE_SELECT:
		break;
	case CManager::MODE_TUTORIAL:
		Create(m_pTutorial);
		break;
	case CManager::MODE_GAME:
		Create(m_pGame);
		break;
	case CManager::MODE_RESULT:
		Create(m_pResult);
		break;
	case CManager::MODE_RANKING:
		Create(m_pRanking);
		break;
	case CManager::MODE_OPTION:
		break;
	}
	m_OrgMode = m_Mode;	//�J�ڑO�̃��[�h���i�[
	m_Mode = mode;		//���݂̃��[�h��ύX
	return S_OK;
}


//==================================================================
// ���[�h���擾����
//==================================================================
LPCSTR CManager::GetModeName(void)
{
	LPCSTR name = "";

	switch (m_Mode)
	{
	case CManager::MODE_LOGO:		name = "LOGO";
		break;
	case CManager::MODE_TITLE:		name = "TITLE";
		break;
	case CManager::MODE_SELECT:		name = "SELECT";
		break;
	case CManager::MODE_TUTORIAL:	name = "TUTORIAL";
		break;
	case CManager::MODE_GAME:		name = "GAME";
		break;
	case CManager::MODE_RESULT:		name = "RESULT";
		break;
	case CManager::MODE_RANKING:	name = "RANKING";
		break;
	case CManager::MODE_OPTION:		name = "OPTION";
		break;
	}

	return name;
}