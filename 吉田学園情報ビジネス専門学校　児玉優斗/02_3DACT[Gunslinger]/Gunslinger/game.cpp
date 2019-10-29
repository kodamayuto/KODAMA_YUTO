//*****************************************************************************
//
// �Q�[���̏���[game.cpp]
// Author : kodama Yuto
//     (:3 )�O
//*****************************************************************************
//�C���N���[�h�t�@�C��
#include "game.h"
#include "fade.h"
#include "pause.h"
//#include"ranking.h"

//=============================================================================
//	�O���[�o���ϐ��錾
//=============================================================================
GAMESTATE g_gamestate		  = GAMESTATE_NONE;		//�Q�[���̏���
int g_nCounterGameState;    						//�J�E���^�[

bool g_bPause;				//�|�[�Y�����p  true = �|�[�Y��
int g_nStage;
int g_nCntenter = 0;
//=============================================================================
//	����������
//=============================================================================
void InitGame(void)
{
	InitPause();

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	//�e�̏���������(�e���g�����̂���ɒu��)
	InitShadow();
	//���b�V���t�B�[���h�̏���������
	InitMeshField();

	//���b�V���E�H�[���̏���������
	InitMeshWall();

	//���b�V���V�����_�[�̏���������
	InitMeshCylinder();

	// �ǂ̏���������
	InitWall();

	//�����̏���������
	InitRoof();

	//���f���̏���������
	InitModel();

	//���̏���������
	InitPiller();

	//�ݒu���̏���������
	InitObject();

	//NPC�̏���������
	InitNpc();

	//����L�����̏���������
	InitPlayer();

	//�e�̏���������
	InitBullet();

	//�����̏���������
	InitExplosion();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�p�[�e�B�N���̏���������
	InitParticle();

	//���̏���������
	InitArrow();

	//�^�C�}�[�̏���������
	InitTimer();

	//�}�b�v�̏���������
	InitMiniMap();

	//�O���[�o���ϐ��̏�����
	g_gamestate = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPause = false;
	g_nCntenter = 0;

	SetWall(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WALLTYPE_1, 1000.0f, 100.0f);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WALLTYPE_1, 1000.0f, 100.0f);
	SetWall(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f), WALLTYPE_1, 1000.0f, 100.0f);
	SetWall(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f), WALLTYPE_1, 1000.0f, 100.0f);


	SetRoof(D3DXVECTOR3(0.0f, 100.0f, 1000.0f), D3DXVECTOR3(-D3DX_PI / 4.0f, 0.0f, 0.0f), ROOFTYPE_1, 1000.0f, 1000.0f);
	SetRoof(D3DXVECTOR3(0.0f, 100.0f, -1000.0f), D3DXVECTOR3(-D3DX_PI / 4.0f, D3DX_PI, 0.0f), ROOFTYPE_1, 1000.0f, 1000.0f);
	SetRoof(D3DXVECTOR3(1000.0f, 100.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.0f, D3DX_PI / 2.0f, 0.0f), ROOFTYPE_1, 1000.0f, 1000.0f);
	SetRoof(D3DXVECTOR3(-1000.0f, 100.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.0f, -D3DX_PI / 2.0f, 0.0f), ROOFTYPE_1, 1000.0f, 1000.0f);

	SetMeshWall(D3DXVECTOR3(700.0f,0.0f,-900.0f),D3DXVECTOR3(0.0f,D3DX_PI * 0.5f,0.0f));
	SetMeshWall(D3DXVECTOR3(700.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(700.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(750.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.75f, 0.0f));
	SetMeshWall(D3DXVECTOR3(820.0f, 0.0f, -180.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(820.0f, 0.0f, 20.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(820.0f, 0.0f, 220.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(720.0f, 0.0f, 320.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(520.0f, 0.0f, 320.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(320.0f, 0.0f, 320.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(220.0f, 0.0f, 220.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(290.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.75f, 0.0f));
	SetMeshWall(D3DXVECTOR3(350.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(350.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(350.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(350.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(350.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(350.0f, 0.0f, -900.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));

	SetMeshWall(D3DXVECTOR3(800.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(700.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f,0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(500.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(400.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(500.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(700.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetMeshWall(D3DXVECTOR3(200.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(100.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-100.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-200.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-100.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(100.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, 900.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-600.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, 900.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));

	SetMeshWall(D3DXVECTOR3(200.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(100.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-100.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-200.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-100.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(100.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetMeshWall(D3DXVECTOR3(200.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(100.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-100.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-200.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-100.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(100.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));


	SetMeshWall(D3DXVECTOR3(-400.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-800.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	SetMeshWall(D3DXVECTOR3(-400.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-800.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-700.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetMeshWall(D3DXVECTOR3(-500.0f, 0.0f, -800.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//��
	SetPiller(D3DXVECTOR3(1000.0f, 0.0f, -1000.0f));
	SetPiller(D3DXVECTOR3(1000.0f, 0.0f, -600.0f));
	SetPiller(D3DXVECTOR3(1000.0f, 0.0f, -200.0f));
	SetPiller(D3DXVECTOR3(1000.0f, 0.0f, 200.0f));
	SetPiller(D3DXVECTOR3(1000.0f, 0.0f, 600.0f));
	SetPiller(D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	SetPiller(D3DXVECTOR3(600.0f, 0.0f, 1000.0f));
	SetPiller(D3DXVECTOR3(200.0f, 0.0f, 1000.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, 1000.0f));
	SetPiller(D3DXVECTOR3(-600.0f, 0.0f, 1000.0f));
	SetPiller(D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f));

	SetPiller(D3DXVECTOR3(-1000.0f, 0.0f, 600.0f));
	SetPiller(D3DXVECTOR3(-1000.0f, 0.0f, 200.0f));
	SetPiller(D3DXVECTOR3(-1000.0f, 0.0f, -200.0f));
	SetPiller(D3DXVECTOR3(-1000.0f, 0.0f, -600.0f));
	SetPiller(D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f));

	SetPiller(D3DXVECTOR3(-600.0f, 0.0f, -1000.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, -1000.0f));
	SetPiller(D3DXVECTOR3(200.0f, 0.0f, -1000.0f));
	SetPiller(D3DXVECTOR3(600.0f, 0.0f, -1000.0f));

	SetPiller(D3DXVECTOR3(700.0f, 0.0f, -1000.0f));
	SetPiller(D3DXVECTOR3(700.0f, 0.0f, -400.0f));
	SetPiller(D3DXVECTOR3(820.0f, 0.0f, -280.0f));
	SetPiller(D3DXVECTOR3(820.0f, 0.0f, 320.0f));
	SetPiller(D3DXVECTOR3(220.0f, 0.0f, 320.0f));
	SetPiller(D3DXVECTOR3(220.0f, 0.0f, 120.0f));
	SetPiller(D3DXVECTOR3(350.0f, 0.0f, -15.0f));
	SetPiller(D3DXVECTOR3(350.0f, 0.0f, -1000.0f));

	SetPiller(D3DXVECTOR3(800.0f, 0.0f, 600.0f));
	SetPiller(D3DXVECTOR3(800.0f, 0.0f, 800.0f));
	SetPiller(D3DXVECTOR3(400.0f, 0.0f, 800.0f));
	SetPiller(D3DXVECTOR3(400.0f, 0.0f, 600.0f));

	SetPiller(D3DXVECTOR3(200.0f, 0.0f, 600.0f));
	SetPiller(D3DXVECTOR3(200.0f, 0.0f, 800.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, 800.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, 600.0f));

	SetPiller(D3DXVECTOR3(200.0f, 0.0f, -200.0f));
	SetPiller(D3DXVECTOR3(200.0f, 0.0f, -400.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, -400.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, -200.0f));

	SetPiller(D3DXVECTOR3(200.0f, 0.0f, -600.0f));
	SetPiller(D3DXVECTOR3(200.0f, 0.0f, -800.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, -800.0f));
	SetPiller(D3DXVECTOR3(-200.0f, 0.0f, -600.0f));

	SetPiller(D3DXVECTOR3(-400.0f, 0.0f, -200.0f));
	SetPiller(D3DXVECTOR3(-400.0f, 0.0f, -400.0f));
	SetPiller(D3DXVECTOR3(-800.0f, 0.0f, -400.0f));
	SetPiller(D3DXVECTOR3(-800.0f, 0.0f, -200.0f));

	SetPiller(D3DXVECTOR3(-400.0f, 0.0f, -600.0f));
	SetPiller(D3DXVECTOR3(-400.0f, 0.0f, -800.0f));
	SetPiller(D3DXVECTOR3(-800.0f, 0.0f, -800.0f));
	SetPiller(D3DXVECTOR3(-800.0f, 0.0f, -600.0f));

	SetPiller(D3DXVECTOR3(-500.0f, 0.0f, 1000.0f));
	SetPiller(D3DXVECTOR3(-500.0f, 0.0f, 0.0f));
	SetPiller(D3DXVECTOR3(-700.0f, 0.0f, 0.0f));
	SetPiller(D3DXVECTOR3(-700.0f, 0.0f, 1000.0f));

	PlaySound(SOUND_LABEL_BGM002);

}

//=============================================================================
//	�I������
//=============================================================================
void UninitGame(void)
{
	UninitPause();

	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	//�e�̏I������
	UninitShadow();

	//���b�V���t�B�[���h�̏I������
	UninitMeshField();

	//���b�V���E�H�[���̏I������
	UninitMeshWall();

	//���b�V���V�����_�[�̏I������
	UninitMeshCylinder();


	// �ǂ̏I������
	UninitWall();

	//�����̏I������
	UninitRoof();

	//���f���̏I������
	UninitModel();

	//���̏I������
	UninitPiller();

	//�ݒu���̏I������
	UninitObject();

	//NPC�̏I������
	UninitNpc();

	//����L�����̏I������
	UninitPlayer();

	//�e�̏I������
	UninitBullet();

	//�����̏I������
	UninitExplosion();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//���̏I������
	UninitArrow();

	//�^�C�}�[�̏I������
	UninitTimer();

	//�}�b�v�̏I������
	UninitMiniMap();

}

//=============================================================================
//	�X�V����
//=============================================================================
void UpdateGame(void)
{
	//�ϐ��錾
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	//�|�[�Y�@ON/OFF
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		PauseModeChange();
		SerectReset();
		DispReset();
	}


	if (g_bPause == false || g_gamestate == GAMESTATE_END || g_gamestate == GAMESTATE_NONE)
	{

		// �J�����̍X�V����
		UpdateCamera();

		// ���C�g�̍X�V����
		UpdateLight();

		//�e�̍X�V����
		UpdateShadow();

		// �ǂ̍X�V����
		UpdateWall();

		//�����̍X�V����
		UpdateRoof();

		//���f���̍X�V����
		UpdateModel();

		//���̍X�V����
		UpdatePiller();

		//�ݒu���̍X�V����
		UpdateObject();

		//NPC�̍X�V����
		UpdateNpc();

		//����L�����̍X�V����
		UpdatePlayer();

		//�e�̍X�V����
		UpdateBullet();

		//�����̍X�V����
		UpdateExplosion();

		//���b�V���t�B�[���h�̍X�V����
		UpdateMeshField();

		//���b�V���E�H�[���̍X�V����
		UpdateMeshWall();

		//���b�V���V�����_�[�̍X�V����
		UpdateMeshCylinder();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�p�[�e�B�N���̍X�V����
		UpdateParticle();

		//���̍X�V����
		UpdateArrow();

		//�^�C�}�[�̍X�V����
		UpdateTimer();

		//�}�b�v�̍X�V����
		UpdateMiniMap();

		if (pPlayer->bUse == false && g_gamestate != GAMESTATE_END)
		{
			SetGameState(GAMESTATE_END);
		}
	}
	else if(g_bPause == true && g_gamestate != GAMESTATE_END || g_gamestate != GAMESTATE_NONE)
	{
		UpdatePause();//�|�[�Y����
	}

	switch (g_gamestate)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			if (pPlayer->bUse == true)
			{
				SetRankScore(GetTimer());
			}

			StopSound();
			BulletErese();
			SetFade(MODE_RESULT);
			g_gamestate = GAMESTATE_NONE;			//���[�h�ݒ�
		}
		break;
	}
}

//=============================================================================
//	�`�揈��
//=============================================================================
void DrawGame(void)
{
	//***�e��I�u�W�F�N�g�̕`�揈��***
	// �J�����̐ݒ�
	SetCamera();

	//���b�V���t�B�[���h�̕`�揈��
	DrawMeshField();

	//���b�V���E�H�[���̕`�揈��
	DrawMeshWall();

	//���b�V���V�����_�[�̕`�揈��
	DrawMeshCylinder();

	// �ǂ̕`�揈��
	DrawWall();

	//�����̕`�揈��
	DrawRoof();

	//���f���̕`�揈��
	DrawModel();

	//���̕`�揈��
	DrawPiller();

	//�ݒu���̕`�揈��
	DrawObject();

	//NPC�̕`�揈��
	DrawNpc();

	//����L�����̕`�揈��
	DrawPlayer();

	//�e�̕`�揈��
	DrawShadow();

	//�e�̕`�揈��
	DrawBullet();

	//�����̕`�揈��
	DrawExplosion();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�p�[�e�B�N���̕`�揈��
	DrawParticle();

	//���̕`�揈��
	DrawArrow();

	//�^�C�}�[�̕`�揈��
	DrawTimer();

	//�}�b�v�̕`�揈��
	DrawMiniMap();


	if (g_bPause == true && g_gamestate == GAMESTATE_NORMAL)
	{
		DrawPause();	//�|�[�Y���
	}
}

//=============================================================================
//	�Q�[���̏�Ԃ̐ݒ�
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
	g_nCounterGameState = 0;
}

//=============================================================================
//	�Q�[���̏�Ԃ̎擾
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gamestate;
}
//=============================================================================
//	�|�[�Y��Ԃ̐؂�ւ�
//=============================================================================
void PauseModeChange(void)
{
	g_bPause = g_bPause ? false : true;
	PlaySound(SOUND_LABEL_SE002);
}

