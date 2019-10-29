//=============================================================================
//
// ���͏��� [input.cpp]
// Author :�ݓc��(Kishida Rei)
//
//=============================================================================
#include "input.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;	//���͂̃|�C���^

//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CInput::CInput()
{//�N���A�Ȓl����
	m_pDevice = NULL;
}


//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�Ō�ɌĂяo�����
//=============================================================================
CInput::~CInput()
{

}
//=============================================================================
// �֐����F���͂̏���������
// �֐��̊T�v�FDirectInput�̐���
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// �֐����F���͂̏I������
// �֐��̊T�v�F�f�o�C�X�̔j���A���͂̔j��
//=============================================================================
void CInput::Uninit(void)
{
	//�f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//���͂̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}




//=============================================================================
//
//
//								CInputKeyboard
//							  �`�L�[�{�[�h�̏����`
//
//=============================================================================
//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aKeyState[nCntKey] = 0;
		m_aKeyTrigger[nCntKey] = 0;
		m_aKeyRelease[nCntKey] = 0;
	}
}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�Ō�ɌĂяo�����
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}
//=============================================================================
// �֐����F�L�[�{�[�h�̏���������
// �֐��̊T�v�F�L�[�{�[�h�̐���
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �֐����F�L�[�{�[�h�̏I������
// �֐��̊T�v�F���͂̔j��
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �֐����F�L�[�{�[�h�̍X�V����
// �֐��̊T�v�FPress, Trigger, Release�̏���
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];	//�g���K�[
			m_aKeyRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];	//�����[�X
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//�L�[�{�[�h�̓��͏��ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=============================================================================
// �֐����F�L�[�{�[�h�̓��͏��(�v���X���)���擾
// �֐��̊T�v�FPress�����擾
//=============================================================================

bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �֐����F�L�[�{�[�h�̓��͏��(�g���K�[���)���擾
// �֐��̊T�v�FTrigger�����擾
//=============================================================================
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �֐����F�L�[�{�[�h�̓��͏��(�����[�X)���擾
// �֐��̊T�v�FTrigger�����擾
//=============================================================================
bool CInputKeyboard::GetKeyboardRelease(int nKey)
{
	return (m_aKeyRelease[nKey] & 0x80) ? true : false;
}
