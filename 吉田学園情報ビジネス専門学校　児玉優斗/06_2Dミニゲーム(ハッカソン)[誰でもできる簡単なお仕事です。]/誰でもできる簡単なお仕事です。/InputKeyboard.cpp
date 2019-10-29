//=============================================================================
//
// ���͏��� [InputKeyboard.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "InputKeyboard.h"

//===================================================================
//	�R���X�g���N�^&�f�X�g���N�^
//===================================================================
CInputKeyboard::CInputKeyboard()
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aState[nCntKey].KeyState = 0;
		m_aState[nCntKey].KeyStateTrigger = 0;
		m_aState[nCntKey].KeyStateRelease = 0;
		m_aState[nCntKey].KeyStateRepeat = 0;
		m_aState[nCntKey].nCntRepeatTime = 0;
	}

}
CInputKeyboard::~CInputKeyboard()
{

}
//===================================================================
//	����������
//===================================================================
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

//===================================================================
//	�I������
//===================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//===================================================================
//	�X�V����
//===================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;
	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
            m_aState[nCntKey].KeyStateRelease = (m_aState[nCntKey].KeyState ^ aKeyState[nCntKey]) & m_aState[nCntKey].KeyState;//�����[�X
			m_aState[nCntKey].KeyStateTrigger = (m_aState[nCntKey].KeyState ^ aKeyState[nCntKey]) & aKeyState[nCntKey];//�g���K�[
			m_aState[nCntKey].KeyState = aKeyState[nCntKey];//�v���X
			m_aState[nCntKey].KeyStateRepeat = 0;

			if (GetPress(nCntKey))
			{
				m_aState[nCntKey].nCntRepeatTime++;
				if (m_aState[nCntKey].nCntRepeatTime % REPEAT_TIME == 1)
				{
					m_aState[nCntKey].KeyStateRepeat = aKeyState[nCntKey];	//���s�[�g
				}
			}
			else
			{
				m_aState[nCntKey].nCntRepeatTime = 0;
			}
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//===================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//===================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aState[nKey].KeyState & 0x80) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aState[nKey].KeyStateTrigger & 0x80) ? true : false;
}

bool CInputKeyboard::GetRelease(int nKey)
{
	return(m_aState[nKey].KeyStateRelease & 0x80) ? true : false;
}
bool CInputKeyboard::GetRepeat(int nKey)
{
	return(m_aState[nKey].KeyStateRepeat & 0x80) ? true : false;
}
