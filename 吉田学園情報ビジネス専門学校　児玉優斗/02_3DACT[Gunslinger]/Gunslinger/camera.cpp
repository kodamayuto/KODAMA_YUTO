//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "camera.h"
#include "input.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_camera;	//�J�����̏��

float g_fCameraAngle;

bool g_bCameraRotFollow = false;	//�J�����̉�荞�݃t���O
//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
		g_camera.posV = D3DXVECTOR3(0.0f, 70.0f, -180.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.nRotmoveCount = 0;
		g_camera.fLength = g_camera.posV.z - g_camera.posR.z;
		g_fCameraAngle = 37.0f;

		g_bCameraRotFollow = false;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	if (GetMode() == MODE_TITLE)
	{
		g_camera.rot.y -= ANGLE_MOVE /5.0f;
		g_camera.rot.y = RotOverwhelming(g_camera.rot.y);

		g_camera.posV = D3DXVECTOR3(g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength,
			g_camera.posV.y,
			g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength);

	}
	else if (GetMode() == MODE_RANKING)
	{
		g_camera.rot.y += ANGLE_MOVE / 5.0f;
		g_camera.rot.y = RotOverwhelming(g_camera.rot.y);

		g_camera.posV = D3DXVECTOR3(g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength,
			g_camera.posV.y,
			g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength);


	}
	else if (GetMode() == MODE_GAME)
	{

		PLAYER *pPlayer;

		pPlayer = GetPlayer();
		//�J������荞�݂�on/off
		if (GetKeyboardTrigger(DIK_M) == true)
		{
			g_bCameraRotFollow = g_bCameraRotFollow ? false : true;
		}

		//�J������荞��
		if (pPlayer->move.x <= 0.1f &&
			pPlayer->move.x >= -0.1f&&
			pPlayer->move.z <= 0.1f &&
			pPlayer->move.z >= -0.1f&&
			GetKeyboardPress(DIK_LEFT) == false &&
			GetKeyboardPress(DIK_RIGHT) == false &&
			g_bCameraRotFollow == true)
		{

			g_camera.nRotmoveCount++;
			if (g_camera.nRotmoveCount > CAMERA_ROTMOVE_INTERVAL)
			{
				//��]�ʂ̌v�Z
				g_camera.rotmove.y = (pPlayer->rot.y + D3DX_PI) - g_camera.rot.y;
				g_camera.rotmove.y = RotOverwhelming(g_camera.rotmove.y);

				//�p�x�ɉ�]�ʂɌW�����|�����l����
				g_camera.rot.y += g_camera.rotmove.y * 0.01f;
				g_camera.rot.y = RotOverwhelming(g_camera.rot.y);

				//�J�����̒����_�E���_�̌v�Z
				g_camera.posRDest = pPlayer->pos;
				g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.006f;
				//g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.035f;
				g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.004f;

				g_camera.posVDest.x = g_camera.posRDest.x + sinf(g_camera.rot.y) * g_camera.fLength;
				g_camera.posVDest.y = g_camera.posV.y;
				g_camera.posVDest.z = g_camera.posRDest.z + cosf(g_camera.rot.y) * g_camera.fLength;

				g_camera.posV += (g_camera.posVDest - g_camera.posV) * CAMERA_POSV_COEFFICIENT;
			}
		}
		else
		{
			g_camera.nRotmoveCount = 0;

			g_camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * CAMERA_POS_INTERVAL;
			g_camera.posRDest.y = g_camera.posR.y;
			g_camera.posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * CAMERA_POS_INTERVAL;

			g_camera.posR += (g_camera.posRDest - g_camera.posR) * CAMERA_POSR_COEFFICIENT;

			g_camera.posVDest.x = g_camera.posRDest.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posVDest.y = g_camera.posV.y;
			g_camera.posVDest.z = g_camera.posRDest.z + cosf(g_camera.rot.y) * g_camera.fLength;

			g_camera.posV += (g_camera.posVDest - g_camera.posV) * CAMERA_POSV_COEFFICIENT;
		}


		//���_�ړ�
		if (GetKeyboardPress(DIK_LEFT)== true)//���v���
		{
			g_camera.rot.y -= ANGLE_MOVE;
		}
		if (GetKeyboardPress(DIK_RIGHT) == true)//�����v���
		{
			g_camera.rot.y += ANGLE_MOVE;
		}
		g_camera.rot.y = RotOverwhelming(g_camera.rot.y);

		g_camera.posV = D3DXVECTOR3(g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength,
			g_camera.posV.y,
			g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength);

		//�J�����p�̊g�k
		if (GetKeyboardPress(DIK_0) == true)
		{
			g_fCameraAngle -= 1.0f;
		}
		if (GetKeyboardPress(DIK_9) == true)
		{
			g_fCameraAngle += 1.0f;
		}
	}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(g_fCameraAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		4000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,&g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
					   &g_camera.posV,
					   &g_camera.posR,
		               &g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}


//=============================================================================
//	�J�����̎擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}