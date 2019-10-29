//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "main.h"
#include "modeselect.h"
#include "player.h"
#include "fade.h"
#include "game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_ANGEL_VIEW  (45.0f)    // �J�����̉�p
#define CAMERA_MOVE        (20.0f)     // �J�����̈ړ���
#define AROUND_SPEED       (0.02f)    // ��荞�ݑ��x�����l
#define AROUND_TIME        (50)       // ��荞�ݑ҂����ԏ����l

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_camera;  // �J�����̏��
int g_Timer;	  //�^�C�}�[

				  //=============================================================================
				  // �J�����̏���������
				  //=============================================================================
void InitCamera(void)
{
	MODE pMode;
	pMode = GetMode();

	switch (pMode)
	{
	case MODE_TITLE:
		g_camera.posV = D3DXVECTOR3(0.0f, 130.0f, -1700.0f);  // ���݂̎��_��������
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // ���݂̒����_��������
		g_camera.fLength = 1000.0f;                           // ������������

		break;
	case MODE_SELECT:
		g_camera.posV = D3DXVECTOR3(0.0f, 40.0f, -200.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 40.0f, 0.0f);       // ���݂̒����_��������
		g_camera.fLength = 400.0f;
		break;
	case MODE_TUTORIAL:
		g_camera.posV = D3DXVECTOR3(0.0f, 265.0f, -1000.0f);  // ���݂̎��_��������
		g_camera.posR = D3DXVECTOR3(0.0f, 228.0f, 0.0f);       // ���݂̒����_��������
		g_camera.fLength = 1000.0f;								// ������������

		break;
	case MODE_GAME:
		g_camera.posV = D3DXVECTOR3(0.0f, 130.0f, 0.0f);  // ���݂̎��_��������
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // ���݂̒����_��������
		g_camera.fLength = 1000.0f;                           // ������������
		break;
	case MODE_CLEAR:
		g_camera.posV = D3DXVECTOR3(0.0f, 70.0f, -1700.0f);  // ���݂̎��_��������
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // ���݂̒����_��������
		g_camera.fLength = 1000.0f;								// ������������
		break;
	case MODE_OVER:
		g_camera.posV = D3DXVECTOR3(0.0f, 100.0f, -1700.0f);  // ���݂̎��_��������
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // ���݂̒����_��������
		g_camera.fLength = 1000.0f;								// ������������
		break;
	case MODE_RANKING:
		g_camera.posV = D3DXVECTOR3(0.0f, 20.0f, -100.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.fLength = g_camera.posV.z - g_camera.posR.z;

		break;
	}

	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // �ړI�̎��_��������
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // �ړI�̒����_��������
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       // �x�N�g����������
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // ���݂̌�����������
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ړI�̌�����������
	g_camera.state = CAMERASTATE_NORMAL;                 // �ʏ�̏�Ԃ�
	g_camera.fWaraparoundSpeed = AROUND_SPEED;           // ��荞�ݑ��x��������
	g_camera.nWaraparoundTime = AROUND_TIME;             // ��荞�ݑ҂����Ԃ�������
	g_camera.nCounterTime = 0;                           // �҂����ԃJ�E���^�[��������
	g_camera.posVAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �����镪�̎��_���W��������
	g_camera.posRAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �����镪�̒����_���W��������

	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	g_Timer = 0;
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
	D3DXVECTOR3 MasuPos;
	float masuRot;

	Player *pPlayer;
	pPlayer = GetPlayer();

	switch (GetMode())
	{
	case MODE_TITLE:
		g_camera.posV.x += sinf(g_camera.rot.y) * CAMERA_MOVE / 5;
		g_camera.posV.z += cosf(g_camera.rot.y) * CAMERA_MOVE / 5;
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;

		break;
	case MODE_SELECT:
		g_camera.SelectModelpos[0] = D3DXVECTOR3(-200.0f, 0.0f, 200.0f);
		g_camera.SelectModelpos[1] = D3DXVECTOR3(200.0f, 0.0f, 200.0f);
		g_camera.SelectModelpos[2] = D3DXVECTOR3(-200.0f, 0.0f, -200.0f);
		g_camera.SelectModelpos[3] = D3DXVECTOR3(200.0f, 0.0f, -200.0f);
		g_camera.fLength = -300.0f;

		g_camera.posRDest = g_camera.SelectModelpos[GetNumber()] - g_camera.posR;

		g_camera.posR.x += g_camera.posRDest.x * 0.04f;
		g_camera.posR.z += g_camera.posRDest.z * 0.04f;

		g_camera.posVDest.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posVDest.y = g_camera.posV.y;
		g_camera.posVDest.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength;

		g_camera.posV += (g_camera.posVDest - g_camera.posV) * 0.86f;
		break;
	case MODE_GAME:
		g_camera.fLength = -500.0f;                           // ������������

		switch (GetTurnState())
		{
		case TURNSTATE_DICE:
			MasuPos = PlayerDistance();

			masuRot = atan2f(MasuPos.x - g_camera.posR.x, MasuPos.z - g_camera.posR.z);
			//��]�ʂ̌v�Z
			g_camera.rotDest.y = (masuRot)-g_camera.rot.y;
			g_camera.rotDest.y = RotOverwhelming(g_camera.rotDest.y);

			//�p�x�ɉ�]�ʂɌW�����|�����l����
			g_camera.rot.y += g_camera.rotDest.y * 0.01f;
			g_camera.rot.y = RotOverwhelming(g_camera.rot.y);

			pPlayer->rot.y = g_camera.rot.y + D3DX_PI;

			//�J�����̒����_�E���_�̌v�Z
			g_camera.posRDest = pPlayer->pos;
			g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.166f;
			g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.1f;
			g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.166f;

			g_camera.posVDest.x = g_camera.posRDest.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posVDest.y = g_camera.posRDest.y + 300.0f;
			g_camera.posVDest.z = g_camera.posRDest.z + cosf(g_camera.rot.y) * g_camera.fLength;

			g_camera.posV += (g_camera.posVDest - g_camera.posV) * 0.15f;

			break;

		case TURNSTATE_MAP:
			//���s�ړ�
			if (GetKeyboardPress(DIK_D) == true || GetJoyPadPress(DIJS_BUTTON_20, GetIdxPlayer()) == true || GetJoyPadPress(DIJS_BUTTON_12, GetIdxPlayer()) == true)//��
			{
				g_camera.posV.x += sinf((D3DX_PI * 0.5f) + g_camera.rot.y) * CAMERA_MOVE;
				g_camera.posV.z += cosf((D3DX_PI * 0.5f) + g_camera.rot.y) * CAMERA_MOVE;
			}
			if (GetKeyboardPress(DIK_A) == true || GetJoyPadPress(DIJS_BUTTON_21, GetIdxPlayer()) == true || GetJoyPadPress(DIJS_BUTTON_13, GetIdxPlayer()) == true)//��
			{
				g_camera.posV.x += sinf((D3DX_PI * -0.5f) + g_camera.rot.y) * CAMERA_MOVE;
				g_camera.posV.z += cosf((D3DX_PI * -0.5f) + g_camera.rot.y) * CAMERA_MOVE;
			}
			if (GetKeyboardPress(DIK_W) == true || GetJoyPadPress(DIJS_BUTTON_18, GetIdxPlayer()) == true || GetJoyPadPress(DIJS_BUTTON_10, GetIdxPlayer()) == true)//��
			{
				g_camera.posV.x += sinf((D3DX_PI * 0.0f) + g_camera.rot.y) * CAMERA_MOVE;
				g_camera.posV.z += cosf((D3DX_PI * 0.0f) + g_camera.rot.y) * CAMERA_MOVE;
			}
			if (GetKeyboardPress(DIK_S) == true || GetJoyPadPress(DIJS_BUTTON_19, GetIdxPlayer()) == true || GetJoyPadPress(DIJS_BUTTON_11, GetIdxPlayer()) == true)//��
			{
				g_camera.posV.x += sinf((D3DX_PI)+g_camera.rot.y) * CAMERA_MOVE;
				g_camera.posV.z += cosf((D3DX_PI)+g_camera.rot.y) * CAMERA_MOVE;

			}

			g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * g_camera.fLength;

			break;
		default:

			//��]�ʂ̌v�Z
			g_camera.rotDest.y = (pPlayer->rot.y + D3DX_PI) - g_camera.rot.y;
			g_camera.rotDest.y = RotOverwhelming(g_camera.rotDest.y);

			//�p�x�ɉ�]�ʂɌW�����|�����l����
			g_camera.rot.y += g_camera.rotDest.y * 0.01f;
			g_camera.rot.y = RotOverwhelming(g_camera.rot.y);

			//�J�����̒����_�E���_�̌v�Z
			g_camera.posRDest = pPlayer->pos;
			g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.166f;
			g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.1f;
			g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.166f;

			g_camera.posVDest.x = g_camera.posRDest.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posVDest.y = g_camera.posRDest.y + 300.0f;
			g_camera.posVDest.z = g_camera.posRDest.z + cosf(g_camera.rot.y) * g_camera.fLength;

			g_camera.posV += (g_camera.posVDest - g_camera.posV) * 0.15f;


			break;

		}

		break;
	case MODE_RANKING:
		break;
	}
	// �J��������̏���
#if 0
	//-----------------
	// ���_�ړ�
	//-----------------
	if (GetKeyboardPress(DIK_LEFT) == true)
	{// A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP) == true)
		{// ������W�L�[�������ꂽ
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{// ������S�L�[�������ꂽ
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else
		{// �����ɉ���������Ă��Ȃ�
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{// D�L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP) == true)
		{// ������W�L�[�������ꂽ
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{// ������S�L�[�������ꂽ
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else
		{// �����ɉ���������Ă��Ȃ�
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}
	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{// W�L�[�������ꂽ
		g_camera.posV.x += sinf(g_camera.rot.y) * CAMERA_MOVE;
		g_camera.posV.z += cosf(g_camera.rot.y) * CAMERA_MOVE;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{// S�L�[�������ꂽ
		g_camera.posV.x -= sinf(g_camera.rot.y) * CAMERA_MOVE;
		g_camera.posV.z -= cosf(g_camera.rot.y) * CAMERA_MOVE;
	}
	//-----------------
	// ���_����
	//-----------------
	if (GetKeyboardPress(DIK_Z) == true)
	{// Z�L�[�������ꂽ
		g_camera.rot.y -= D3DX_PI / 120;
		if (g_camera.rot.y <= -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;

	}
	if (GetKeyboardPress(DIK_C) == true)
	{// C�L�[�������ꂽ
		g_camera.rot.y += D3DX_PI / 120;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}
	//-----------------
	// �����_����
	//-----------------
	if (GetKeyboardPress(DIK_Q) == true)
	{// Q�L�[�������ꂽ
		g_camera.rot.y -= D3DX_PI / 120;
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}
	}
	if (GetKeyboardPress(DIK_E) == true)
	{// E�L�[�������ꂽ
		g_camera.rot.y += D3DX_PI / 120;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
	}
	//-----------------
	// �J�������Z�b�g
	//-----------------
	if (GetKeyboardPress(DIK_G) == true)
	{// SPACE�L�[�������ꂽ
		g_camera.posV = D3DXVECTOR3(0.0f, 130.0f, -250.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 00.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//-----------------
	// �����_�㏸���~
	//-----------------
	if (GetKeyboardPress(DIK_T) == true)
	{// T�L�[�������ꂽ
		g_camera.posR.y += 1.5f;
	}
	if (GetKeyboardPress(DIK_B) == true)
	{// B�L�[�������ꂽ
		g_camera.posR.y -= 1.5f;
	}
	//-----------------
	// ���_�㏸���~
	//-----------------
	if (GetKeyboardPress(DIK_Y) == true)
	{// Y�L�[�������ꂽ
		g_camera.posV.y += 1.5f;
	}
	if (GetKeyboardPress(DIK_N) == true)
	{// N�L�[�������ꂽ
		g_camera.posV.y -= 1.5f;
	}

	//------------------------
	// �Y�[���C�� �Y�[���A�E�g
	//------------------------
	if (GetKeyboardPress(DIK_U) == true)
	{// U�L�[�������ꂽ
		if (g_camera.fLength >= 100)
		{
			g_camera.fLength -= 0.5f;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}
	if (GetKeyboardPress(DIK_M) == true)
	{// M�L�[�������ꂽ
		if (g_camera.fLength <= 500)
		{
			g_camera.fLength += 0.5f;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}

	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;


	/*Player *pPlayer = GetPlayer();*/  // �v���C���[�̎擾

										// ���_�ݒ�
										//g_camera.posVDest.x = (pPlayer->pos.x + g_camera.posVAdd.x) + sinf(-g_camera.rot.y) * g_camera.fLength;  // �ړI�̎��_��ݒ�
										//g_camera.posVDest.y = (pPlayer->pos.y + g_camera.posVAdd.y) + cosf(D3DX_PI) * -g_camera.fLength / 2;  // �ړI�̎��_��ݒ�
										//g_camera.posVDest.z = (pPlayer->pos.z + g_camera.posVAdd.z) + cosf(-g_camera.rot.y) * g_camera.fLength;  // �ړI�̎��_��ݒ�

										//// �����_�ݒ�
										//g_camera.posRDest.x = (pPlayer->pos.x + g_camera.posRAdd.x) - sinf(pPlayer->rot.y) * ((pPlayer->move.x * pPlayer->move.x) + (7.0f + 1.5f * (pPlayer->move.x * pPlayer->move.x))); // �ړI�̒����_��ݒ�
										//g_camera.posRDest.y = (pPlayer->pos.y + g_camera.posRAdd.y) - sinf(pPlayer->rot.y) * ((pPlayer->move.x * pPlayer->move.x) + (7.0f + 1.5f * (pPlayer->move.y * pPlayer->move.y))); // �ړI�̒����_��ݒ�
										//g_camera.posRDest.z = (pPlayer->pos.z + g_camera.posRAdd.z) - cosf(pPlayer->rot.y) * ((pPlayer->move.x * pPlayer->move.x) + (7.0f + 1.5f * (pPlayer->move.z * pPlayer->move.z))); // �ړI�̒����_��ݒ�

										//if (pPlayer->state == PLAYERSTATE_NORMAL)
										//{// �ʏ�̏�Ԃ�������
										//	g_camera.nCounterTime++;               // �J�E���^�[��i�߂�
										//	if (g_camera.nCounterTime >= g_camera.nWaraparoundTime)
										//	{// ��荞�ݑ҂����Ԃ�����̒l�𒴂���
										//		g_camera.rotDest = -pPlayer->rot;  // �ړI�̌�����ݒ�
										//		g_camera.rotDiff = g_camera.rotDest.y - g_camera.rot.y;  // �ړI�ƌ��݂̌����̍������v�Z
										//		if (g_camera.rotDiff > D3DX_PI)
										//		{// ������D3DX_PI�𒴂���
										//			g_camera.rotDiff -= D3DX_PI * 2.0f;
										//		}
										//		if (g_camera.rotDiff < -D3DX_PI)
										//		{// ������-D3DX_PI�𒴂���
										//			g_camera.rotDiff += D3DX_PI * 2.0f;
										//		}

										//		g_camera.rot.y += g_camera.rotDiff * g_camera.fWaraparoundSpeed;  // ���݂̌�����ړI�̌����Ɉڍs

										//		if (g_camera.rot.y > D3DX_PI)
										//		{// ���݂̌�����D3DX_PI�𒴂���
										//			g_camera.rot.y -= D3DX_PI * 2.0f;
										//		}
										//		if (g_camera.rot.y < -D3DX_PI)
										//		{// ���݂̌�����-D3DX_PI�𒴂���
										//			g_camera.rot.y += D3DX_PI * 2.0f;
										//		}
										//	}
										//}
										//else if (pPlayer->state != PLAYERSTATE_NORMAL)
										//{// �ړ����Ă����Ԃ�������
										//	g_camera.nCounterTime = 0;  // �J�E���^�[��0�ɖ߂�
										//}

										//-----------------
										// �����_�㏸���~
										//-----------------
	if (GetKeyboardPress(DIK_T) == true)
	{// T�L�[�������ꂽ
		g_camera.posRAdd.y += 1.5f;
	}
	if (GetKeyboardPress(DIK_B) == true)
	{// B�L�[�������ꂽ
		g_camera.posRAdd.y -= 1.5f;
	}
	//-----------------
	// ���_�㏸���~
	//-----------------
	if (GetKeyboardPress(DIK_Y) == true)
	{// Y�L�[�������ꂽ
		g_camera.posVAdd.y += 1.5f;
	}
	if (GetKeyboardPress(DIK_N) == true)
	{// N�L�[�������ꂽ
		g_camera.posVAdd.y -= 1.5f;
	}

	//------------------------
	// �Y�[���C�� �Y�[���A�E�g
	//------------------------
	if (GetKeyboardPress(DIK_U) == true)
	{// U�L�[�������ꂽ
		if (g_camera.fLength >= 60)
		{
			g_camera.fLength -= 2.0f;
		}
	}
	if (GetKeyboardPress(DIK_M) == true)
	{// M�L�[�������ꂽ
		if (g_camera.fLength <= 350)
		{
			g_camera.fLength += 2.0f;
		}
	}

	//g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.54f; // ���݂̎��_��ݒ�
	//g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.54f;  // ���݂̎��_��ݒ�
	//g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.54f; // ���݂̎��_��ݒ�

	//g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.07f; // ���݂̒����_��ݒ�
	//g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.07f; // ���݂̒����_��ݒ�
	//g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.07f; // ���݂̒����_��ݒ�

	//// �����𓭂�����
	//g_camera.posV.x += (0.0f - g_camera.posV.x) * 0.25f;
	//g_camera.posV.y += (0.0f - g_camera.posV.y) * 0.25f;
	//g_camera.posV.z += (0.0f - g_camera.posV.z) * 0.25f;
	//g_camera.posR.x += (0.0f - g_camera.posR.x) * (0.00001f);
	//g_camera.posR.y += (0.0f - g_camera.posR.y) * (0.00001f);
	//g_camera.posR.z += (0.0f - g_camera.posR.z) * (0.00001f);
#endif
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
		D3DXToRadian(CAMERA_ANGEL_VIEW),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		50000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

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
// �J�����̎擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}