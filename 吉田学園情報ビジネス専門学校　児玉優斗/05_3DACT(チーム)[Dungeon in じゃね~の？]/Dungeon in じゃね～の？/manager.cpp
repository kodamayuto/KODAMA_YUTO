//=============================================================================
//
// �}�l�[�W������ [manager.cpp]
// Author :�ݓc��(Kishida Rei)
//
//=============================================================================

#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "manager.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "sceneX.h"
#include "scene_billboard.h"
#include "debugproc.h"
#include "player.h"
#include "meshfield.h"
#include "model.h"
#include "enemy.h"
#include "number.h"
#include "timer.h"
#include "object.h"
#include "scene_meshcylinder.h"
#include "itemcounter.h"
#include "ui.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "sound.h"
#include "inputx.h"
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;			//�����_���[�̃|�C���^
CInputKeyboard *CManager::m_pInputKeyboard = NULL;	//�L�[�{�[�h���͂̃|�C���^
CSound *CManager::m_pSound = NULL;					//�T�E���h
CCamera *CManager::m_pCamera = NULL;				//�J����
CLight *CManager::m_pLight = NULL;					//���C�g
CDebugProc *CManager::m_pDebugProc = NULL;			//�f�o�b�O�\��
CScene3D *CManager::m_pScene3D = NULL;				//�V�[��3D
CTitle *CManager::m_pTitle = NULL;					//�^�C�g��
CGame *CManager::m_pGame = NULL;					//�Q�[��
CTutorial *CManager::m_pTutorial = NULL;			//�`���[�g���A��
CResult *CManager::m_pResult = NULL;				//���U���g
CRanking *CManager::m_pRanking = NULL;				//�����L���O
CInputX *CManager::m_pInputX = NULL;				//�W���C�p�b�h

// �^�C�}�[�Ŏg�p
int CManager::m_nTimer;										//�^�C�}�[
int CManager::m_nTenMinutes = 0;							//10����
int CManager::m_nOneMinutes = 0;							//1����
int CManager::m_nTenSeconds = 4;							//10�b��
int CManager::m_nOneSeconds = 0;							//10�b��
int CManager::m_nTenComma = 0;								//�R���}�b
int CManager::m_nOneComma = 0;								//�R���}�b



CManager::MODE CManager::m_mode = CManager::MODE_TITLE;		//���[�h�̐ݒ�
//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�Ō�ɌĂяo�����B
//=============================================================================
CManager::~CManager()
{

}


//=============================================================================
// �֐����F�}�l�[�W���̏���������
// �֐��̊T�v�F�����_���[�A�f�o�b�N�A�L�[�{�[�h�A�J�����̐���
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����_���[�̐���
	m_pRenderer = new CRenderer;
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}

	//�f�o�b�O�\���̏�����
	m_pDebugProc = new CDebugProc;
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Init();
	}

	//�T�E���h�̍쐬
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->InitSound(hWnd);
	}

	//�L�[�{�[�h�̐���
	m_pInputKeyboard = new CInputKeyboard;
	if (m_pInputKeyboard != NULL)
	{
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//�W���C�p�b�h�̐���
	m_pInputX = new CInputX;
	if (m_pInputX != NULL)
	{
		m_pInputX->Init();
	}

	//�J�����̍쐬
	m_pCamera = new CCamera;
	if (m_pCamera != NULL)
	{
		m_pCamera->Init();
	}

	//���C�g�̍쐬
	m_pLight = new CLight;
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}




	//���[�h�̐ݒ�
	SetMode(m_mode);

	//���C���[�t���[���̗L��
	m_bDebug = false;

	return S_OK;

}
//=============================================================================
// �֐����F�}�l�[�W���̏I������
// �֐��̊T�v�F�����_���[�A�f�o�b�N�A�L�[�{�[�h�A�J�����̔j��
//=============================================================================
void CManager::Uninit()
{
	CScene::ReleaseSceneAll();

	switch (m_mode)
	{
	case MODE_TITLE:
		//�^�C�g����ʂ̏I������
		m_pTitle->Uninit();
		//�^�C�g����ʂ̔j��
		delete m_pTitle;
		m_pTitle = NULL;
		break;

	case MODE_TUTORIAL:
		//�`���[�g���A����ʂ̏I��
		m_pTutorial->Uninit();
		//�`���[�g���A����ʂ̔j��
		delete m_pTutorial;
		m_pTutorial = NULL;
		break;

	case MODE_GAME:
		//�Q�[����ʂ̏I��
		m_pGame->Uninit();
		//�Q�[����ʂ̔j��
		delete m_pGame;
		m_pGame = NULL;
		break;

	case MODE_RESULT:
		//���U���g��ʂ̏I��
		m_pResult->Uninit();
		//���U���g��ʂ̔j��
		delete m_pResult;
		m_pResult = NULL;
		break;

	case MODE_RANKING:
		//�����L���O��ʂ̏I��
		m_pRanking->Uninit();
		//�����L���O��ʂ̔j��
		delete m_pRanking;
		m_pRanking = NULL;
		break;
	}

	//���C�g�̏I������
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	//�J�����̏I������
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}


	//�W���C�p�b�h�̏I������
	if (m_pInputX != NULL)
	{
		// �I������
		m_pInputX->Uninit();

		//�L�[�{�[�h�̔j��
		delete m_pInputX;
		m_pInputX = NULL;
	}

	//�L�[�{�[�h�̏I������
	if (m_pInputKeyboard != NULL)
	{
		// �I������
		m_pInputKeyboard->Uninit();

		//�L�[�{�[�h�̔j��
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�T�E���h�̏I������
	if (m_pSound != NULL)
	{
		//�I������
		m_pSound->UninitSound();
		//�T�E���h�̔j��
		delete m_pSound;
		m_pSound = NULL;
	}


	//�f�o�b�O�\���̏I������
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}


	//�����_���[�̏I������
	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();
		//�����_���[�̔j��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}


}
//=============================================================================
// �֐����F�}�l�[�W���̍X�V����
// �֐��̊T�v�F�����_���[�A�f�o�b�N�A�L�[�{�[�h�A�J�����̍X�V
//=============================================================================
void CManager::Update()
{
	//�L�[�{�[�h�̍X�V
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	//�W���C�p�b�h�̍X�V����
	if (m_pInputX != NULL)
	{
		// �I������
		m_pInputX->Update();
	}

	//�J�����̍X�V
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//���C�g�̍X�V
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	//�����_���[�̍X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}


	switch (m_mode)
	{//���[�h
	case MODE_TITLE:
		m_pTitle->Update();

		break;
	case MODE_TUTORIAL:
		m_pTutorial->Update();
		break;

	case MODE_GAME:
		m_pGame->Update();
		break;


	case MODE_RESULT:
		m_pResult->Update();
		break;

	case MODE_RANKING:
		m_pRanking->Update();
		break;

	}

	//if (m_pInputKeyboard->GetKeyboardTrigger(DIK_0) == true)
	//{//2�L�[�������ꂽ�Ƃ�
	//	m_bDebug = m_bDebug ? false : true;;
	//}
}

//=============================================================================
// �֐����F�}�l�[�W���̕`�揈��
// �֐��̊T�v�F�����_���[�̕`��A�J�����̐ݒu
//=============================================================================
void CManager::Draw()
{
	//�����_���[�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();


	//if (m_bDebug == true)
	//{
	//	// ���C���[�t���[��
	//	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//}
	//else if (m_bDebug == false)
	//{
	//	// �񃏃C���[�t���[��
	//	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//}

	//�J�����̐ݒu
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}

	//�����_���[�̍X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}

	switch (m_mode)
	{//���[�h
	case MODE_TITLE:
		m_pTitle->Draw();
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Draw();
		break;


	case MODE_GAME:
		m_pGame->Draw();
		break;


	case MODE_RESULT:
		m_pResult->Draw();
		break;

	case MODE_RANKING:
		m_pRanking->Draw();
		break;

	}
}

//=============================================================================
// �֐����F�����_�����O�N���X�̎擾
// �֐��̊T�v�F�����_���[�N���X��Ԃ�
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}


//=============================================================================
// �֐����F�C���v�b�g�N���X�̎擾
// �֐��̊T�v�F�C���v�b�g�N���X��Ԃ�
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// �֐����F�J�����N���X�̎擾
// �֐��̊T�v�F�J�����N���X��Ԃ�
//=============================================================================
CCamera * CManager::GetCamera(void)
{
	return m_pCamera;
}


//=============================================================================
// �֐����F�V�[��3D�N���X�̎擾
// �֐��̊T�v�F�V�[��3D�N���X��Ԃ�
//=============================================================================
CScene3D *CManager::GetScene3D(void)
{
	return m_pScene3D;
}


//=============================================================================
// �֐����F�T�E���h�N���X�̎擾
// �֐��̊T�v�F�T�E���h�N���X��Ԃ�
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

CInputX * CManager::GetInput(void)
{
	return m_pInputX;
}


//=============================================================================
// �֐����F���[�h�̐ݒ�
// �֐��̊T�v�F���̃��[�h��ݒ肷��
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = NULL;
		//�T�E���h�̍Đ�
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
		break;

	case MODE_GAME:
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = NULL;
		//�T�E���h�̍Đ�
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_GAME);
		break;


	case MODE_TUTORIAL:
		m_pTutorial->Uninit();
		delete m_pTutorial;
		m_pTutorial = NULL;
		//�T�E���h�̍Đ�
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		break;

	case MODE_RESULT:
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = NULL;
		//�T�E���h�̍Đ�
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_RESULT);
		break;

	case MODE_RANKING:
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = NULL;
		//�T�E���h�̍Đ�
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_RANKING);
		break;

	}

	//�V�������(���[�h)�̏���������
	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = new CTitle;
		m_pTitle->Init();
		//�T�E���h�̍Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
		break;

	case MODE_GAME:
		m_pGame = new CGame;
		m_pGame->Init();
		//�T�E���h�̍Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);
		break;

	case MODE_TUTORIAL:
		m_pTutorial = new CTutorial;
		m_pTutorial->Init();
		//�T�E���h�̍Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		break;

	case MODE_RESULT:
		m_pResult = new CResult;
		m_pResult->Init();
		//�T�E���h�̍Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);
		break;

	case MODE_RANKING:
		m_pRanking = new CRanking;
		m_pRanking->Init();
		//�T�E���h�̍Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RANKING);
		break;


	}

	m_mode = mode;
}

//=============================================================================
// �֐����F���[�h�̎擾
// �֐��̊T�v�F���݂̃��[�h���擾����
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}


//=============================================================================
// �^�C�}�[�̐ݒ�
//=============================================================================
void CManager::SetTimer(int nTenMinutes, int nOneMinutes, int nTenSeconds, int nOneSeconds, int nTenComma, int nOneComma)
{
	m_nTenMinutes = nTenMinutes;
	m_nOneMinutes = nOneMinutes;
	m_nTenSeconds = nTenSeconds;
	m_nOneSeconds = nOneSeconds;
	m_nTenComma = nTenComma;
	m_nOneComma = nOneComma;
}

//=============================================================================
//�^�C�}�[�̎擾
//=============================================================================
int CManager::GetTimer(void)
{
	int nTenMinutes = m_nTenMinutes;
	int nOneMinutes = m_nOneMinutes;
	int nTenSeconds = m_nTenSeconds;
	int nOneSeconds = m_nOneSeconds;
	int nTenComma = m_nTenComma;
	int nOneComma = m_nOneComma;

	m_nTenMinutes = nTenMinutes * 100000;
	m_nOneMinutes = nOneMinutes * 10000;
	nTenSeconds = nTenSeconds * 1000;
	nOneSeconds = nOneSeconds * 100;
	nTenComma = nTenComma * 10;
	nOneComma = nOneComma;

	m_nTimer = m_nTenMinutes + nOneMinutes + nTenSeconds + nOneSeconds + nTenComma + nOneComma;

	return m_nTimer;
}