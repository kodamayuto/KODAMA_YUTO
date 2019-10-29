//=============================================================================
//
// �����L���O���� [ranking.h]
// Author : �����ʉ�
//
//=============================================================================
#include "main.h"				//���C��
#include "scene.h"				//�V�[��
#include "renderer.h"			//�����_�����O
#include "scene2D.h"			//�V�[��2D
#include "manager.h"			//�}�l�[�W���[
#include "input.h"				//����
#include "number.h"				// �i���o�[
#include "timer.h"				// �^�C�}�[
#include "game.h"				//�Q�[��
#include "ranking.h"			//�����L���O
#include "DebugProc.h"			//�f�o�b�O�\��
#include "fade.h"				//�t�F�[�h
#include "ui_ranking.h"
#include "meshfield.h"
#include "object.h"
#include "inputx.h"
#include "sound.h"
//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CUiRanking *CRanking::m_pUiRanking = NULL;
CObject *CRanking::m_pObject = NULL;				//�I�u�W�F�N�g
CMeshField *CRanking::m_pMeshField = NULL;			//���b�V���t�B�[���h
int CRanking::m_nJumpTitleFrame = 0;//�^�C�g����ʂ֑J�ڂ���Ƃ��̃t���[���J�E���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking::CRanking()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{	//���������Ȃ�
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRanking::Init(void)
{
	//�t���[���̏�����
	m_nJumpTitleFrame = 0;


	//�����̃e�N�X�`���̓ǂݍ���
	CNumber::Load();

	//UI�̃e�N�X�`���̓ǂݍ���
	m_pUiRanking->Load();

	//�z�u����I�u�W�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pObject->Load();


	//===============================================
	// �Q�[�����Ŏg�p���鏈���̐���
	//===============================================
	//���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	//�g�p����I�u�W�F�N�g���f���̓ǂݍ��݁E�I�u�W�F�N�g����
	m_pObject->LoadModelText();



	//UI�̐���
	m_pUiRanking->Create();

	//��������
	CTimer::Create(D3DXVECTOR3(500.0f, 100.0f, 0.0f), CTimer::TIMEMODE_RANKING);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRanking::Uninit(void)
{
	CScene::ReleaseSceneAll();

	//�����̃e�N�X�`���̔j��
	CNumber::Unload();

	//UI�̃e�N�X�`���̓ǂݍ���
	m_pUiRanking->Unload();

}

//=============================================================================
// �X�V����
//=============================================================================
void CRanking::Update(void)
{
	m_nJumpTitleFrame++;

	CInputX::InputJoyState JoyState = CInputX::GetJoystate();
	bool bConnect = CInputX::GetbConnect();			//�W���C�p�b�h�̐ڑ����

	//���
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//�t�F�[�h�̎擾
	CFade::FADE pFade;
	pFade = CFade::GetFade();


	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();


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
				CFade::SetFade(CManager::MODE_TITLE);//�����L���O�ֈڍs
			}
		}
		JoyState = CInputX::INPUT_JOYSTATE_PUSH;

	}

	if (m_nJumpTitleFrame % 600 == 0)
	{
		if (pFade == CFade::FADE_NONE)
		{
			CFade::SetFade(CManager::MODE_TITLE);//�����L���O�ւֈڍs
		}
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
void CRanking::Draw(void)
{
}