//=============================================================================
//
// inputx���� [xinput.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "inputx.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_CONTROLLERS			(1)		//�R���g���[���[�̍ő吔
#define	NUM_JOYKEY_MAX			(128)	//�L�[�̍ő吔


CInputX::InputJoyState CInputX::m_nJoypadState = INPUT_JOYSTATE_NOTPUSH;		//�W���C�p�b�h�̏��
bool CInputX::m_bConnectionJoypad = false;			//�W���C�p�b�h�̐ڑ����
LPDIRECTINPUTDEVICE8 m_pDevJoyPad = NULL;			//���̓f�o�C�X(�W���C�p�b�h)�ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputX::CInputX()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInputX::~CInputX()
{
}

//=============================================================================
// �W���C�p�b�h�̏�����
//=============================================================================
void CInputX::Init(void)
{
	m_nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	m_bConnectionJoypad = false;

	DWORD dwResult;

	for (DWORD dCnt = 0; dCnt < MAX_CONTROLLERS; dCnt++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(dCnt, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			//MessageBox(0, "�R���g���[���[���ڑ�����Ă��܂�", "", MB_OK );
			// �f�b�h�]�[���̐ݒ�
			if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
				(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			{
				state.Gamepad.sThumbLX = 0;
				state.Gamepad.sThumbLY = 0;
			}

			if ((state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
				(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
			{
				state.Gamepad.sThumbRX = 0;
				state.Gamepad.sThumbRY = 0;
			}

			m_bConnectionJoypad = true;
		}
		else
		{
			//MessageBox(0, "�R���g���[���[���ڑ�����Ă��܂���", "", MB_OK);
			m_bConnectionJoypad = false;
		}
	}
}

//=============================================================================
// �W���C�p�b�h�̏I������
//=============================================================================
void CInputX::Uninit(void)
{
	XInputEnable(false);
}

//=============================================================================
// �W���C�p�b�h�̍X�V����
//=============================================================================
void CInputX::Update(void)
{

}

CInputX::InputJoyState CInputX::GetJoystate(void)
{
	return m_nJoypadState;
}

bool CInputX::GetbConnect(void)
{
	return m_bConnectionJoypad;
}




//=============================================================================
// �W���C�p�b�h�̏�Ԏ擾
//=============================================================================

