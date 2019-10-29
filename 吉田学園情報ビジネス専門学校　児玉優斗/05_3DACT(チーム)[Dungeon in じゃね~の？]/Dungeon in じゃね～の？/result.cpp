//=============================================================================
//
// ���U���g�̏��� [result.h]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "input.h"				//����
#include "result.h"				//�^�C�g��
#include "DebugProc.h"			// �f�o�b�O�\��
#include "number.h"				// �i���o�[
#include "timer.h"				// �^�C�}�[
#include "fade.h"				//�t�F�[�h
#include "ui_result.h"
#include "meshfield.h"
#include "object.h"
#include "inputx.h"
#include "sound.h"
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CUiResult *CResult::m_pUiResult = NULL;
CObject *CResult::m_pObject = NULL;				//�I�u�W�F�N�g
CMeshField *CResult::m_pMeshField = NULL;			//���b�V���t�B�[���h

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{	//���������Ȃ�
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(void)
{
	// �e�N�X�`���̓ǂݍ��݁i�K��Create�̑O�œǂݍ��݁I�j
	CNumber::Load();					// �i���o�[

	//�e�N�X�`���̓ǂݍ���
	m_pUiResult->Load();

	//�z�u����I�u�W�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pObject->Load();


	//===============================================
	// �Q�[�����Ŏg�p���鏈���̐���
	//===============================================
	//���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	//�g�p����I�u�W�F�N�g���f���̓ǂݍ��݁E�I�u�W�F�N�g����
	m_pObject->LoadModelText();




	// ����
	CTimer::Create(D3DXVECTOR3(500.0f, 200.0f, 0.0f), CTimer::TIMEMODE_RESULT);

	// ���U���gUI�̐���
	m_pUiResult->Create();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	// �e�N�X�`���̔j��
	CNumber::Unload();

	//�e�N�X�`���̓ǂݍ���
	m_pUiResult->Unload();




	//�V�[���̔j��
	CScene::ReleaseSceneAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	CInputX::InputJoyState JoyState = CInputX::GetJoystate();
	bool bConnect = CInputX::GetbConnect();			//�W���C�p�b�h�̐ڑ����

	//���
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();


	//�t�F�[�h�̎擾
	CFade::FADE pFade;
	pFade = CFade::GetFade();


	//�f�o�C�X�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_START && bConnect == true))
	{//�G���^�[�L�[�������ꂽ�Ƃ�
		if (JoyState == CInputX::INPUT_JOYSTATE_NOTPUSH)
		{
			if (pFade == CFade::FADE_NONE)
			{
				pSound->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
				CFade::SetFade(CManager::MODE_RANKING);//�����L���O�ֈڍs
			}
		}
		JoyState = CInputX::INPUT_JOYSTATE_PUSH;
	}


	if (JoyState == CInputX::INPUT_JOYSTATE_PUSH)
	{
		JoyState = CInputX::INPUT_JOYSTATE_NONE;
	}
	else if (JoyState == CInputX::INPUT_JOYSTATE_NONE)
	{
		JoyState = CInputX::INPUT_JOYSTATE_NOTPUSH;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
}