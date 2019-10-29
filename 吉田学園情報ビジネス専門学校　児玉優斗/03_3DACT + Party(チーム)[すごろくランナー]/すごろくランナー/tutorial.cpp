//=============================================================================
//
// �`���[�g���A����ʏ��� [tutorial.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "tutorial.h"
#include "fade.h"
#include "pressenter.h"
#include "input.h"
#include "sound.h"
#include "tutorialBG.h"
#include "camera.h"
#include "light.h"
#include "main.h" 
#include "course.h"
#include "woodbg.h"
#include "masu.h"
#include "course.h"
#include "sky.h"
#include "shadow.h"
#include "effect.h"
#include "particle.h"
#include "meshField.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �}�X�̏��
//*****************************************************************************
typedef struct
{// �u���b�N�̏��
	D3DXVECTOR3 pos;
	MASUTYPE masuType;	// �u���b�N�̎��
} MasuInfo;

//*****************************************************************************
// �R�[�X�̏��
//*****************************************************************************
typedef struct
{// �u���b�N�̏��
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fWidth;
	float fHeight;
} CourseInfo;

//*****************************************************************************
// �O���[�o���ϐ�
//***************************************************************************** 
TUTORIAL_STATE g_TutorialState;		//���
int g_MoveTimer;	//�ړ��̃^�C�}�[
int g_nCntMove;	//�ړ��̃J�E���^�[
MasuInfo g_aMasuInfo3[] =
{
	{ D3DXVECTOR3(0.0f, 0.0f, -150.0f), MASUTYPE_START },
	{ D3DXVECTOR3(1700.0f, 0.0f, -150.0f),MASUTYPE_GOAL },
	//{ D3DXVECTOR3(5100.0f, 0.0f, -150.0f), MASUTYPE_GOAL },

};

// �u���b�N���̃f�[�^
CourseInfo g_aCourseInfo3[] =
{
	{ D3DXVECTOR3(900.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 850.0f, 200.0f },
};


//=============================================================================
//�w�i�̖؂̐ݒu
//=============================================================================
WOODBG_INFO g_WoodBGInfo3[] =
{
	{ D3DXVECTOR3(0.0f, -500.0f, 0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),WOODBG_TYPE_PALM },
	{ D3DXVECTOR3(1700.0f, -500.0f, 0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),WOODBG_TYPE_PALM },


	{ D3DXVECTOR3(1400.0f, -500.0f, 2300.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),WOODBG_TYPE_LAKE },
};
//=============================================================================
// ����������
//=============================================================================
void InitTutorial(void)
{
	g_nCntMove = 0;							//�ړ��J�E���^�[��������
	g_MoveTimer = 0;						//�ړ��^�C�}�[��������
	g_TutorialState = TUTORIAL_STATE_NONE;	//��Ԃ̏�����

											// �J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	//�e�̏���������
	InitShadow();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�p�[�e�B�N���̏���������
	InitParticle();

	//��̏���������
	InitSky();

	//�}�X�̏���������
	InitMasu();

	//�R�[�X�̏���������
	InitCourse();

	//�w�i�̖؂̏���������
	InitWoodBG();

	//���b�V���t�B�[���h�̏���������
	InitMeshField();

	//�`���[�g���A���w�i�̏���������
	InitTutorialBG();
	SetTutorialBG(D3DXVECTOR3(0.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetTutorialBG(D3DXVECTOR3(850.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetTutorialBG(D3DXVECTOR3(1700.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//SetTutorialBG(D3DXVECTOR3(2550.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �}�X�̐ݒu
	for (int nCntMasu = 0; nCntMasu < sizeof g_aMasuInfo3 / sizeof(MasuInfo); nCntMasu++)
	{
		SetMasu(g_aMasuInfo3[nCntMasu].pos, g_aMasuInfo3[nCntMasu].masuType);
	}

	// �R�[�X�̐ݒu
	for (int nCntCourse = 0; nCntCourse < sizeof g_aCourseInfo3 / sizeof(CourseInfo); nCntCourse++)
	{
		SetCourse(g_aCourseInfo3[nCntCourse].pos, g_aCourseInfo3[nCntCourse].rot, g_aCourseInfo3[nCntCourse].fWidth, g_aCourseInfo3[nCntCourse].fHeight);
	}

	//�@�w�i�̖؂̐ݒu
	for (int nCntWoodBG = 0; nCntWoodBG < sizeof g_WoodBGInfo3 / sizeof(WOODBG_INFO); nCntWoodBG++)
	{
		SetWoodBG(g_WoodBGInfo3[nCntWoodBG].pos, g_WoodBGInfo3[nCntWoodBG].rot, g_WoodBGInfo3[nCntWoodBG].move, g_WoodBGInfo3[nCntWoodBG].nType);
	}

}
//=============================================================================
// �I������
//=============================================================================
void UninitTutorial(void)
{
	// �J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//�e�̏I������
	UninitShadow();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//�}�X�̏I������
	UninitMasu();

	//�w�i�̖؂̏I������
	UninitWoodBG();

	//�R�[�X�̏I������
	UninitCourse();

	//�`���[�g���A���w�i�̏I������
	UninitTutorialBG();

	//��̏I������
	UninitSky();

	//���b�V���t�B�[���h�̏I������
	UninitMeshField();

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorial(void)
{
	FADE fade;
	fade = GetFade();



	//bool *disp;
	//disp = GetDispPressEnter();

	// �J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	//�e�̍X�V����
	UpdateShadow();

	//�G�t�F�N�g�̍X�V����
	UpdateEffect();

	//�p�[�e�B�N���̍X�V����
	UpdateParticle();

	//�}�X�̍X�V����
	UpdateMasu();

	//�R�[�X�̍X�V����
	UpdateCourse();

	//�w�i�̖؂̍X�V����
	UpdateWoodBG();

	//�`���[�g���A���w�i�̍X�V����
	UpdateTutorialBG();

	//��̍X�V����
	UpdateSky();

	//���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();

	//�J�����̎擾
	Camera *pCamera = GetCamera();

	switch (g_TutorialState)
	{
	case TUTORIAL_STATE_NONE:	//�ʏ���
		pCamera->posV.x -= 0.0f;
		pCamera->posV.z -= 0.0f;
		pCamera->posR.x = pCamera->posV.x + sinf(pCamera->rot.y) * pCamera->fLength;
		pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * pCamera->fLength;
		break;
	case TUTORIAL_STATE_MOVE:	//�ړ����


		pCamera->posV.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posV.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posR.x = pCamera->posV.x + sinf(pCamera->rot.y) * pCamera->fLength;
		pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * pCamera->fLength;
		g_MoveTimer++;
		if (g_MoveTimer == 85.0f)
		{//�J�E���g���W�T�ɂȂ����ꍇ
			g_TutorialState = TUTORIAL_STATE_NONE;		//�ʏ��Ԃɖ߂�
			g_nCntMove++;								//�ړ��J�E���^�[�𑫂�
			g_MoveTimer = 0;							//�^�C�}�[������������
		}

		break;
	case TUTORIAL_STATE_REMOVE:	//�߂���

		pCamera->posV.x += sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posV.z += cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * 20.0f;
		pCamera->posR.x = pCamera->posV.x + sinf(pCamera->rot.y) * pCamera->fLength;
		pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * pCamera->fLength;
		g_MoveTimer++;
		if (g_MoveTimer == 85.0f)
		{//�J�E���g���W�T�ɂȂ����ꍇ
			g_TutorialState = TUTORIAL_STATE_NONE;		//�ʏ��Ԃɖ߂�
			g_nCntMove--;								//�ړ��J�E���^�[�𑫂�
			g_MoveTimer = 0;							//�^�C�}�[������������
		}
		break;
	}
	if (g_TutorialState == TUTORIAL_STATE_NONE)
	{//�ʏ��Ԃ̏ꍇ
		if (g_nCntMove == 0)
		{
			if (GetKeyboardTrigger(DIK_RIGHT) == true || GetJoyPadTrigger(DIJS_BUTTON_20, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_12, 0) == true)
			{
				g_TutorialState = TUTORIAL_STATE_MOVE;
				PlaySound(SOUND_LABEL_SE002);
			}
		}
		if (g_nCntMove == 1)
		{
			if (GetKeyboardTrigger(DIK_LEFT) == true || GetJoyPadTrigger(DIJS_BUTTON_21, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_13, 0) == true)
			{
				g_TutorialState = TUTORIAL_STATE_REMOVE;
				PlaySound(SOUND_LABEL_SE003);
			}
		}
	}
	if (g_nCntMove == 1)
	{
		for (int nCntJoyPad = 0; nCntJoyPad < 8; nCntJoyPad++)
		{
			if (GetJoyPadTrigger(nCntJoyPad, 0) == TRUE && fade == FADE_NONE)
			{
				SetFade(MODE_SELECT);
				PlaySound(SOUND_LABEL_SE000);
			}
		}
		if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE )
		{// ����{�^���������ꂽ
			SetFade(MODE_SELECT);
			PlaySound(SOUND_LABEL_SE000);
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorial(void)
{
	// �J�����̕`�揈��
	SetCamera();

	//�}�X�̕`�揈��
	DrawMasu();

	//���b�V���t�B�[���h�̕`�揈��
	DrawMeshField();

	//�R�[�X�̕`�揈��
	DrawCourse();

	//�w�i�̖؂̕`�揈��
	DrawWoodBG();

	//��̍X�V����
	DrawSky();

	//�e�̕`�揈��
	DrawShadow();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�p�[�e�B�N���̕`�揈��
	DrawParticle();

	//�`���[�g���A���w�i�̕`�揈��
	DrawTutorialBG();
}