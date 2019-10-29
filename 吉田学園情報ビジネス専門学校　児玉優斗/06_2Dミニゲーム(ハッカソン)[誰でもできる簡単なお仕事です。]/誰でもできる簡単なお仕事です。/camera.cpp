//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "camera.h"
#include "InputKeyboard.h"
#include "Manager.h"
#include "renderer.h"

#define ANGLE_MOVE  (0.03f) //�J�����p�x�̈ړ���
#define CAMERA_POSR_COEFFICIENT (0.18f);	//�J���������_�̌W��
#define CAMERA_POS_INTERVAL (20.0f)			//�J�����̒����_�̈ʒu

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_fCameraAngle = 45.0f;
}
CCamera::~CCamera()
{

}

//=============================================================================
// ����������
//=============================================================================
void CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f,80.0f, -300.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	CInputKeyboard* pInput = CManager::GetInputKeyboard();

	//if (pInput->GetPress(DIK_LEFT) == true )//���v���
	//{
	//	m_rot.y -= ANGLE_MOVE;
	//}
	//if (pInput->GetPress(DIK_RIGHT) == true )//�����v���
	//{
	//	m_rot.y += ANGLE_MOVE;
	//}

	//if (m_rot.y < -D3DX_PI)
	//{
	//	m_rot.y += D3DX_PI * 2.0f;
	//}
	//if (m_rot.y > D3DX_PI)
	//{
	//	m_rot.y -= D3DX_PI * 2.0f;
	//}

	//m_posV = D3DXVECTOR3(m_posR.x + sinf(m_rot.y) * -300.0f,
	//	m_posV.y,
	//	m_posR.z + cosf(m_rot.y) * -300.0f);

	//���_�ړ�
	if (pInput->GetPress(DIK_LEFT) == true)//���v���
	{
		m_rot.y -= ANGLE_MOVE;
		if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}
	}
	if (pInput->GetPress(DIK_RIGHT) == true)//�����v���
	{
		m_rot.y += ANGLE_MOVE;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	m_posV = D3DXVECTOR3(m_posR.x + sinf(m_rot.y) * -300.0f,
		m_posV.y,
		m_posR.z + cosf(m_rot.y) * -300.0f);

	if (pInput->GetPress(DIK_L) == true)
	{
		m_posV.y -= 5.0f;
	}
	if (pInput->GetPress(DIK_O) == true)
	{
		m_posV.y += 5.0f;
	}
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	CRenderer* pRenderder = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderder->GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(m_fCameraAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);


	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
#ifdef _DEBUG
	CDebugProc::Print("Camera.PosV : (%f,%f,%f)\n", m_posV.x, m_posV.y, m_posV.z);
	CDebugProc::Print("Camera.PosR : (%f,%f,%f)\n", m_posR.x, m_posR.y, m_posR.z);
#endif


}