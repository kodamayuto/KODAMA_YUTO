//=============================================================================
//
// ���͏��� [DInputController.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "DinputController.h"

//===================================================================
//	�R���X�g���N�^&�f�X�g���N�^
//===================================================================
CDInputController::CDInputController()
{

}
CDInputController::~CDInputController()
{

}

//===================================================================
//	����������
//===================================================================
HRESULT CDInputController::Init(HINSTANCE hInstance, HWND hWnd)
{
	//======================================
	// �W���C�p�b�h����������
	//======================================
	// ���̓f�o�C�X(�W���C�p�b�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	if (m_pDevice != NULL)
	{// �����ł���
		DIPROPRANGE diprg;

		// ���̒l�͈̔͂�ݒ�
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -DI_JOY_I_INPUT;
		diprg.lMax = DI_JOY_I_INPUT;

		// ���̐ݒ�
		// ���A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_X;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �E�A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_RX;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);


		// �\���L�[(���0�x�Ƃ����v���Ɋp�x * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �W���C�p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
		m_pDevice->Acquire();
	}

	return S_OK;

}

//===================================================================
//	�I������
//===================================================================
void CDInputController::Uninit(void)
{
	CInput::Uninit();
}

//===================================================================
//	�X�V����
//===================================================================
void CDInputController::Update(void)
{
	//======================================
	// �W���C�p�b�h�X�V����
	//======================================
	if (m_pDevice != NULL)
	{// �����ł���
		DIJOYSTATE dijs;    // �W���C�p�b�h�̓��͏����i�[����

							// ���̓f�o�C�X(�W���C�p�b�h)����f�[�^���擾
		m_pDevice->Poll();
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIJOYSTATE), &dijs)))
		{
			m_Yziku = 0.0f;
			m_Xziku = 0.0f;

			m_Xziku = (float)dijs.lX;
			m_Yziku = (float)dijs.lY;

			//-----------------------------
			// ���A�i���O�X�e�B�b�N
			//-----------------------------
			if (dijs.lY <= -100)
			{// ���A�i���O�X�e�B�b�N����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_10] = 0x80;
			}
			if (dijs.lY >= 100)
			{// ���A�i���O�X�e�B�b�N�����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_11] = 0x80;
			}
			if (dijs.lX <= -100)
			{// ���A�i���O�X�e�B�b�N�����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_13] = 0x80;
			}
			if (dijs.lX >= 100)
			{// ���A�i���O�X�e�B�b�N���E�ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_12] = 0x80;
			}

			//-----------------------------
			// �E�A�i���O�X�e�B�b�N
			//-----------------------------
			if (dijs.lRz <= -100)
			{// �E�A�i���O�X�e�B�b�N����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_14] = 0x80;
			}
			if (dijs.lRz >= 100)
			{// �E�A�i���O�X�e�B�b�N�����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_15] = 0x80;
			}
			if (dijs.lZ <= -100)
			{// �E�A�i���O�X�e�B�b�N�����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_17] = 0x80;
			}
			if (dijs.lZ >= 100)
			{// �E�A�i���O�X�e�B�b�N���E�ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_16] = 0x80;
			}

			//-----------------------------
			// �\���L�[
			//-----------------------------
			if (dijs.rgdwPOV[0] / 100 == 0)
			{// �\���L�[�̏オ�����ꂽ
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 45)
			{// �\���L�[�̉E�オ�����ꂽ
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 90)
			{// �\���L�[�̉��������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 135)
			{// �\���L�[�̉E���������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 180)
			{// �\���L�[�̉E�������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 225)
			{// �\���L�[�̍����������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 270)
			{// �\���L�[�̍��������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 315)
			{// �\���L�[�̍��オ�����ꂽ
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			for (int nCntJoyButton = 0; nCntJoyButton < DIJS_BUTTON_MAX; nCntJoyButton++)
			{// �W���C�p�b�h�̃{�^���̐������J��Ԃ�
				m_aJoyStateTrigger[nCntJoyButton] = (m_aJoyState[nCntJoyButton] ^ dijs.rgbButtons[nCntJoyButton]) & dijs.rgbButtons[nCntJoyButton];  // �W���C�p�b�h�̓��͏��(�g���K�[���)�ۑ�
				m_aJoyState[nCntJoyButton] = dijs.rgbButtons[nCntJoyButton];   // �W���C�p�b�h�̓��͏��(�v���X���)�ۑ�
			}
		}
		else
		{
			m_pDevice->Acquire(); // �W���C�p�b�h�ւ̃A�N�Z�X�����l��
		}
	}
}