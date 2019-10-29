//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIGHT (3)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_light[MAX_LIGHT];		//���C�g�̏��
D3DXVECTOR3 vecDir[MAX_LIGHT];
D3DXCOLOR DifCol[MAX_LIGHT];

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	vecDir[0] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	vecDir[1] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
	vecDir[2] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);

	//DifCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//DifCol[1] = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	//DifCol[2] = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	DifCol[0] = D3DXCOLOR(0.60f, 0.60f, 0.60f, 1.0f);
	DifCol[1] = D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f);
	DifCol[2] = D3DXCOLOR(0.05f, 0.05f, 0.05f, 1.0f);

	// ���C�g���N���A����
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g�̏�����
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		g_light[nCntLight].Diffuse = DifCol[nCntLight];

		// ���C�g�̕����̐ݒ�
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		g_light[nCntLight].Direction = vecDir[nCntLight];

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
}

