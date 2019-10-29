//=============================================================================
//
// XInput�R���g���[�����͏��� [inputXPad.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "InputXPad.h"
#include "debugProc.h"
#include "manager.h"

#define XPAD_L_DEADZONE (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3000)
#define XPAD_R_DEADZONE (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 3000)

//===================================================================
//	�ÓI�����o�ϐ��錾
//===================================================================
int CInputXPad::m_nCntXPadNum = 0;
//===================================================================
//	�R���X�g���N�^&�f�X�g���N�^
//===================================================================
CInputXPad::CInputXPad()
{
	m_nID = m_nCntXPadNum;
	m_nCntXPadNum++;

	for (int nCntInput = 0; nCntInput < XPAD_MAX; nCntInput++)
	{
		m_State.abPadStatePress[nCntInput] = false;
		m_State.abPadStateTrigger[nCntInput] = false;
		m_State.abPadStateRelease[nCntInput] = false;
		m_State.abPadStateRepeat[nCntInput] = false;
		m_State.nCntRepeatTime[nCntInput] = 0;
	}
}
CInputXPad::~CInputXPad()
{
	m_nCntXPadNum--;
}

//===================================================================
//	����������
//===================================================================
HRESULT CInputXPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(m_nID, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		CheckDeadZone(state);
		m_bConnect = true;
	}
	else
	{
		m_bConnect = false;
	}
	return S_OK;
}

//===================================================================
//	�I������
//===================================================================
void CInputXPad::Uninit(void)
{
	XInputEnable(false);
}

//===================================================================
//	�X�V����
//===================================================================
void CInputXPad::Update(void)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(m_nID, &state);
	if (dwResult == ERROR_SUCCESS)
	{
		WORD RightStick = 0;

		//����Y�A�c��X�ɂȂ��Ă���̂ŋt�ɂ���
		m_sLStickRotX = state.Gamepad.sThumbLY;
		m_sLStickRotY = state.Gamepad.sThumbLX;
		m_sRStickRotX = state.Gamepad.sThumbRY;
		m_sRStickRotY = state.Gamepad.sThumbRX;

		CheckDeadZone(state);
		CDebugProc::Print("cn","L_STICKROT_X : ", m_sLStickRotX);
		CDebugProc::Print("cn", "L_STICKROT_Y : ", m_sLStickRotY);
		CDebugProc::Print("cn", "R_STICKROT_X : ", m_sRStickRotX);
		CDebugProc::Print("cn", "R_STICKROT_Y : ", m_sRStickRotY);

		if (m_bConnect == false)
		{
			for (int nCntInput = 0; nCntInput < XPAD_MAX; nCntInput++)
			{
				m_State.abPadStatePress[nCntInput] = false;
				m_State.abPadStateTrigger[nCntInput] = false;
				m_State.abPadStateRelease[nCntInput] = false;
				m_State.abPadStateRepeat[nCntInput] = false;
				m_State.nCntRepeatTime[nCntInput] = 0;
			}
			m_bConnect = true;
		}

		//�X�e�B�b�N���͂�����L�[���͂ɕϊ����ă}�[�W����
		state.Gamepad.wButtons |= ThumbToDPad(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, XPAD_L_DEADZONE);
		//�E�X�e�B�b�N�̓��͂͌ʂɐݒ�
		RightStick = ThumbToDPad(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, XPAD_R_DEADZONE);

		//���͏��ݒ�
		SetInputState(XPAD_KEY::XPAD_UP, (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP ? true : false));
		SetInputState(XPAD_KEY::XPAD_DOWN, (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN ? true : false));
		SetInputState(XPAD_KEY::XPAD_LEFT, (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHT, (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT ? true : false));
		SetInputState(XPAD_KEY::XPAD_START, (state.Gamepad.wButtons & XINPUT_GAMEPAD_START ? true : false));
		SetInputState(XPAD_KEY::XPAD_BACK, (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK ? true : false));
		SetInputState(XPAD_KEY::XPAD_LEFT_THUMB, (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHT_THUMB, (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB ? true : false));
		SetInputState(XPAD_KEY::XPAD_LEFT_SHOULDER, (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHT_SHOULDER, (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER ? true : false));
		SetInputState(XPAD_KEY::XPAD_A, (state.Gamepad.wButtons & XINPUT_GAMEPAD_A ? true : false));
		SetInputState(XPAD_KEY::XPAD_B, (state.Gamepad.wButtons & XINPUT_GAMEPAD_B ? true : false));
		SetInputState(XPAD_KEY::XPAD_X, (state.Gamepad.wButtons & XINPUT_GAMEPAD_X ? true : false));
		SetInputState(XPAD_KEY::XPAD_Y, (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y ? true : false));
		SetInputState(XPAD_KEY::XPAD_LEFT_TRIGGER, (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHT_TRIGGER, (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHTSTICK_UP, (RightStick & XINPUT_GAMEPAD_DPAD_UP ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHTSTICK_DOWN, (RightStick & XINPUT_GAMEPAD_DPAD_DOWN ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHTSTICK_LEFT, (RightStick & XINPUT_GAMEPAD_DPAD_LEFT ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHTSTICK_RIGHT, (RightStick & XINPUT_GAMEPAD_DPAD_RIGHT ? true : false));
	}
	else
	{
		for (int nCntInput = 0; nCntInput < XPAD_MAX; nCntInput++)
		{
			m_State.abPadStatePress[nCntInput] = false;
			m_State.abPadStateTrigger[nCntInput] = false;
			m_State.abPadStateRelease[nCntInput] = false;
			m_State.abPadStateRepeat[nCntInput] = false;
			m_State.nCntRepeatTime[nCntInput] = 0;
		}
		m_bConnect = false;
	}

}

//===================================================================
//	�ݒ菈��
//===================================================================
void CInputXPad::SetInputState(XPAD_KEY key, bool bPress)
{
	m_State.abPadStateTrigger[key] = (m_State.abPadStatePress[key] ^ bPress) & bPress;	//�g���K�[
	m_State.abPadStateRelease[key] = (m_State.abPadStatePress[key] ^ bPress) & m_State.abPadStatePress[key];	//�����[�X
	m_State.abPadStatePress[key] = bPress;	//�v���X
	m_State.abPadStateRepeat[key] = false;

	if (m_State.abPadStatePress[key] == true)
	{
		m_State.nCntRepeatTime[key]++;
		if ((m_State.nCntRepeatTime[key] % REPEAT_TIME) == 1)
		{
			m_State.abPadStateRepeat[key] = true;	//���s�[�g
		}
	}
	else
	{
		m_State.nCntRepeatTime[key] = 0;
	}

}
//===================================================================
//	�X�e�B�b�N���͂�����L�[���͂ɕϊ����鏈��
//===================================================================
WORD CInputXPad::ThumbToDPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}

//===================================================================
//	�f�b�h�]�[���̐ݒ菈��
//===================================================================
void CInputXPad::CheckDeadZone(XINPUT_STATE& state)
{
	// �f�b�h�]�[���̐ݒ�
	if ((state.Gamepad.sThumbLX < XPAD_L_DEADZONE &&
		state.Gamepad.sThumbLX > -XPAD_L_DEADZONE) &&
		(state.Gamepad.sThumbLY < XPAD_L_DEADZONE &&
			state.Gamepad.sThumbLY > -XPAD_L_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}
	if ((state.Gamepad.sThumbRX < XPAD_R_DEADZONE &&
		state.Gamepad.sThumbRX > -XPAD_R_DEADZONE) &&
		(state.Gamepad.sThumbRY < XPAD_R_DEADZONE &&
			state.Gamepad.sThumbRY > -XPAD_R_DEADZONE))
	{
		state.Gamepad.sThumbRX = 0;
		state.Gamepad.sThumbRY = 0;
	}
}

//===================================================================
//	���͏��擾����
//===================================================================
bool CInputXPad::GetPress(CInputXPad::XPAD_KEY key)		//�v���X
{
	if (GetConnect()) { return m_State.abPadStatePress[key]; }
	return false;
}
bool CInputXPad::GetTrigger(CInputXPad::XPAD_KEY key)	//�g���K�[
{
	if (GetConnect()) { return m_State.abPadStateTrigger[key]; }
	return false;
}
bool CInputXPad::GetRelease(CInputXPad::XPAD_KEY key)	//�����[�X
{
	if (GetConnect()) { return m_State.abPadStateRelease[key]; }
	return false;
}
bool CInputXPad::GetRepeat(CInputXPad::XPAD_KEY key)	//���s�[�g
{
	if (GetConnect()) { return m_State.abPadStateRepeat[key]; }
	return false;
}