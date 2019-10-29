//=============================================================================
//
// �J�������� [camera.cpp]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "player.h"
#include "game.h"
#include "inputx.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define CAMERA_MOVE (3.5f)
#define ROT_CAMERASPEED (0.04f)
#define ROT_SPEED (0.1f)

#define CAMERA_ANGLE (12.0f)
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CManager *CCamera::m_pManager = NULL;
//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0);

	m_fLength = 0.0f;
	m_fHeight = m_posV.y - m_posR.y;

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0);
	m_pManager = NULL;
}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�Ō�ɌĂяo�����
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// �֐����F�J�����̏���������
// �֐��̊T�v�F�J�����̈ʒu��A������ݒ肷��B
//=============================================================================
HRESULT CCamera::Init(void)
{
	//�J�����̈ʒu���̏�����
	m_posV = D3DXVECTOR3(450.0f, 100.0f, -800.0f);
	m_posR = D3DXVECTOR3(450.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0);

	m_eyepoint = 0.0f;
	m_fLength =150.0f;		// �����_����̋���
	m_fHeight = m_posV.y - m_posR.y;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0);	// �p�x���


	return S_OK;
}

//=============================================================================
// �֐����F�J�����̏I��
// �֐��̊T�v�F
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �֐����F�J�����̍X�V
// �֐��̊T�v�F�e��L�[�{�[�h����
//=============================================================================
void CCamera::Update(void)
{

#if 1
	CInputX::InputJoyState JoyState = CInputX::GetJoystate();
	bool bConnect = CInputX::GetbConnect();			//�W���C�p�b�h�̐ڑ����

													//���
	XINPUT_STATE state;
	XInputGetState(0, &state);


	//�f�o�C�X�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//���[�h�̎擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	if (mode == CManager::MODE_TITLE || mode == CManager::MODE_RESULT || mode == CManager::MODE_RANKING)
	{
		m_posV = D3DXVECTOR3(450.0f, 100.0f, -800.0f);
		m_posR = D3DXVECTOR3(450.0f, 0.0f, 0.0f);
		m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0);

	}
	if (mode == CManager::MODE_GAME)
	{

		//===============================�҂�����Ǐ]==================================//
		//�v���C���[�̎擾
		CPlayer *pPlayer;
		pPlayer = CGame::GetPlayer();
		D3DXVECTOR3 playerpos = pPlayer->GetPos();
		D3DXVECTOR3 playerrot = pPlayer->GetRot();
		D3DXVECTOR3 playermove = pPlayer->GetMove();


		m_posVDest.x = playerpos.x + sinf(m_rot.y) * -m_fLength;
		m_posVDest.y = (playerpos.y  + 60.0f) + m_eyepoint;
		m_posVDest.z = playerpos.z + cosf(m_rot.y) * -m_fLength;

		m_posRDest.x = playerpos.x - sinf(playerrot.y) * 1.0f;
		m_posRDest.y = (playerpos.y + 50.0f) ;
		m_posRDest.z = playerpos.z - cosf(playerrot.y) * 1.0f;

		m_posV.x += (m_posVDest.x - m_posV.x) * 0.4f;
		m_posV.y += (m_posVDest.y - m_posV.y) * 0.4f;
		m_posV.z += (m_posVDest.z - m_posV.z) * 0.4f;

		m_posR.x += (m_posRDest.x - m_posR.x) * 0.4f;
		m_posR.y +=	(m_posRDest.y - m_posR.y) * 0.4f;
		m_posR.z += (m_posRDest.z - m_posR.z) * 0.4f;

		if (pInputKeyboard->GetKeyboardPress(DIK_LEFT) == true || (state.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && bConnect == true))
		{
			m_rot.y -= ROT_CAMERASPEED;

			m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
			m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
		}
		if (pInputKeyboard->GetKeyboardPress(DIK_RIGHT) == true || (state.Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && bConnect == true))
		{
			m_rot.y += ROT_CAMERASPEED;

			m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
			m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
		}

		if (pInputKeyboard->GetKeyboardPress(DIK_DOWN) == true || (state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && bConnect == true))
		{
			m_eyepoint += 2.1f;
			if (m_eyepoint >= 70.0f)
			{
				m_eyepoint = 70.0f;
			}

		}
		if (pInputKeyboard->GetKeyboardPress(DIK_UP) == true || (state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && bConnect == true))
		{
			m_eyepoint -= 2.1f;


			if (m_eyepoint <= -32.0f)
			{
				m_eyepoint = -32.0f;
			}

		}


		if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB && bConnect == true))
		{//�J�������v���C���[�̉�]�ɍ��킹��
			if (JoyState == CInputX::INPUT_JOYSTATE_NOTPUSH)
			{
				m_rot.y = playerrot.y + (-1.0f * D3DX_PI);
				m_posV = D3DXVECTOR3(0.0f, 100.0f + playerpos.y, -150.0f);
			}
			JoyState = CInputX::INPUT_JOYSTATE_PUSH;

		}
	//============================================================================//
	}

	//�J�����̈ʒu���
	//CDebugProc::Print("PosV(X,Y,Z):%.1f, %.1f, %.1f\n", m_posV.x, m_posV.y, m_posV.z);
	//CDebugProc::Print("Rot(X,Y,Z):%.1f, %.1f, %.1f\n", m_rot.x, m_rot.y, m_rot.z);
	//CDebugProc::Print("PosR(X,Y,Z):%.1f, %.1f, %.1f\n", m_posR.x, m_posR.y, m_posR.z);
	//CDebugProc::Print("eyepoint: %.1f\n", m_eyepoint);



	OverView();
#endif

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
// �֐����F�J�����̐ݒ菈��
// �֐��̊T�v�F�J������ݒu����
//=============================================================================
void CCamera::SetCamera(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();


	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		4000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView,//�r���[�}�g���b�N�X
		&m_posV,//���_
		&m_posR,//�����_
		&m_vecU);//������x�N�g��

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=============================================================================
// �֐����F�J�����̒���
// �֐��̊T�v�F�J�����̊p�x������߂����Ƃ��̒���
//=============================================================================
void CCamera::OverView()
{
	if (m_rot.y > D3DX_PI)
	{

		m_rot.y -= D3DX_PI * 2;
	}

	if (m_rot.y < -D3DX_PI)
	{

		m_rot.y += D3DX_PI * 2;
	}


	if (m_rot.z > D3DX_PI)
	{

		m_rot.z -= D3DX_PI * 2;
	}

	if (m_rot.z < -D3DX_PI)
	{

		m_rot.z += D3DX_PI * 2;
	}

	if (m_rot.x > D3DX_PI)
	{

		m_rot.x -= D3DX_PI * 2;
	}

	if (m_rot.x < -D3DX_PI)
	{

		m_rot.x += D3DX_PI * 2;
	}


}

//=============================================================================
// �֐����F�J�����̃}�g���b�N�X�̎擾
// �֐��̊T�v�F�J�����̃}�g���b�N�X��Ԃ�
//=============================================================================
D3DXMATRIX CCamera::GetmtxView(void)
{
	return m_mtxView;
}

D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

