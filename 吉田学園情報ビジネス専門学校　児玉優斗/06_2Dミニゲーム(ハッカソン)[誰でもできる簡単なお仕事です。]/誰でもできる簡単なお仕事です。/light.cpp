//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "light.h"
#include "Manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CLight::CLight()
{
}
CLight::~CLight()
{

}


void CLight::Init(void)
{
	CRenderer* pRenderder = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderder->GetDevice();	// �f�o�C�X�̎擾


	m_VecDir[0] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	m_VecDir[1] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
	m_VecDir[2] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);

	m_DifCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_DifCol[1] = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	m_DifCol[2] = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	// ���C�g���N���A����
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g�̏�����
		ZeroMemory(&m_Light[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		m_Light[nCntLight].Diffuse = m_DifCol[nCntLight];
		// ���C�g�̕����̐ݒ�
		D3DXVec3Normalize(&m_VecDir[nCntLight], &m_VecDir[nCntLight]);
		m_Light[nCntLight].Direction = m_VecDir[nCntLight];

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_Light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

void CLight::Uninit(void)
{

}

void CLight::Update(void)
{

}
