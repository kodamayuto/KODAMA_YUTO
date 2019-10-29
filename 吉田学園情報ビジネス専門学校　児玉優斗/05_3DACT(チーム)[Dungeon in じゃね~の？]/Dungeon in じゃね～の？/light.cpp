//=============================================================================
//
// ���C�g���� [light.cpp]
// Author :�ݓc��(Kishida Rei)
//
//=============================================================================
#include "light.h"
#include "renderer.h"
#include "manager.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CManager *CLight::m_pManager = NULL;



//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CLight::CLight()
{
}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CLight::~CLight()
{
}

//=============================================================================
// �֐����F���C�g�̏���������
// �֐��̊T�v�F���C�g3�̐���
//=============================================================================
HRESULT CLight::Init(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 vecDir0;	//���C�g�̕���[0]
	D3DXVECTOR3 vecDir1;	//���C�g�̕���[1]
	D3DXVECTOR3 vecDir2;	//���C�g�̕���[2]

	// ���C�g���N���A����
	ZeroMemory(&m_Light[0], sizeof(D3DLIGHT9));
	ZeroMemory(&m_Light[1], sizeof(D3DLIGHT9));
	ZeroMemory(&m_Light[2], sizeof(D3DLIGHT9));


	// ���C�g�̎�ނ�ݒ�
	m_Light[0].Type = D3DLIGHT_DIRECTIONAL;
	m_Light[1].Type = D3DLIGHT_DIRECTIONAL;
	m_Light[2].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	m_Light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
	m_Light[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 0.8f);
	m_Light[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir0 = D3DXVECTOR3(0.2f, -0.7f, 0.4f);
	D3DXVec3Normalize(&vecDir0, &vecDir0);

	vecDir1 = D3DXVECTOR3(-0.3f, 0.8f, -0.5f);
	D3DXVec3Normalize(&vecDir1, &vecDir1);

	vecDir2 = D3DXVECTOR3(-0.3f, -0.8f, 0.3f);
	D3DXVec3Normalize(&vecDir2, &vecDir2);


	//���C�g�̕����̐ݒ�
	m_Light[0].Direction = vecDir0;
	m_Light[1].Direction = vecDir1;
	m_Light[2].Direction = vecDir2;

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &m_Light[0]);
	pDevice->SetLight(1, &m_Light[1]);
	pDevice->SetLight(2, &m_Light[2]);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);


	return S_OK;
}

//=============================================================================
// �֐����F���C�g�̏I������
// �֐��̊T�v�F
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// �֐����F���C�g�̍X�V����
// �֐��̊T�v�F
//=============================================================================
void CLight::Update(void)
{
}
