//=============================================================================
//
// �v���C���[����[���f��] [player.cpp]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene3D.h"
#include "manager.h"
#include "input.h"
#include "sceneX.h"
#include "scene2D.h"
#include "debugproc.h"
#include "player.h"
#include "camera.h"
#include "model.h"
#include "enemy.h"
#include "object.h"
#include "meshfield.h"
#include "game.h"
#include "sound.h"
#include "inputx.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//=====================================
// �v���C���[���
//=====================================
#define PLAYER_MOVE (0.28f)										//�ړ���
#define PLAYER_MOVE_DEFAULT		(0.2f)							// �v���C���[�������Ă��̈ړ���
#define MAX_CHAR (256)											//�����̍ő吔
#define GRAVITY_NUM (0.8f)										//�d�͂̒l
#define PLAYER_MOTION_BLEND_FRAME	(5)							// ���[�V�����u�����h�̃t���[����
#define JUMP_POWER (22.0f)										//�W�����v��
#define PLAYER_COLLISION_RADIUS		(20.0f)						// �v���C���[�̓����蔻��̔��a

#define SCREEN_LIMIT_MAX_X (690.0f )	//��ʒ[(�E�[)
#define SCREEN_LIMIT_MIN_X (80.0f)			//���(���[)

#define SCREEN_LIMIT_MIN_Z (-1100)			//���(��[)


//=====================================
// �D�揇��
//=====================================
#define ENEMY_PRIORITY (5)										//�G�̗D�揇��
#define OBJECT_PRIORITY (4)										//�I�u�W�F�N�g�̗D�揇��

//=====================================
// �ǂݍ��ރe�L�X�g�t�@�C��
//=====================================
#define MODEL_FILENAME ("data/TEXT/motion_player.txt")			//�ǂݍ��ރt�@�C����

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL; //���L�e�N�X�`���̃|�C���^
D3DXVECTOR3 CPlayer::m_Partspos[MAX_PLAYER_PARTS] = {};			//�p�[�c�̈ʒu
D3DXVECTOR3 CPlayer::m_Partsrot[MAX_PLAYER_PARTS] = {};			//�p�[�c�̈ʒu
D3DXVECTOR3 CPlayer::m_PartsDefaultpos[MAX_PLAYER_PARTS] = {};	//�f�t�H���g�̃p�[�c�ʒu
D3DXVECTOR3 CPlayer::m_PartsDefaultrot[MAX_PLAYER_PARTS] = {};	//�f�t�H���g�̃p�[�c�p�x
D3DXVECTOR3 CPlayer::m_Motionpos[MAX_PLAYER_PARTS] = {};		//���[�V������������p�ʒu
D3DXVECTOR3 CPlayer::m_Motionrot[MAX_PLAYER_PARTS] = {};		//���[�V������������p�p�x
int CPlayer::m_aParent[MAX_PLAYER_PARTS] = {};					//�p�[�c�̐e
int CPlayer::m_aIndex[MAX_PLAYER_PARTS] = {};					//�p�[�c�ԍ�


//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CPlayer::CPlayer(int nPriority, OBJTYPE type) : CScene(nPriority, type)
{
	m_bUseDraw = true;
}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�Ō�ɌĂяo�����
//=============================================================================
CPlayer::~CPlayer()
{
}


//=============================================================================
// �֐����F�g�p����e�N�X�`���̓ǂݍ���
// �֐��̊T�v�F--
//=============================================================================
HRESULT CPlayer::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player.png", &m_pTexture);

	return S_OK;

}

//=============================================================================
// �֐����F�g�p�����e�N�X�`���̔j��
// �֐��̊T�v�F--
//=============================================================================
void CPlayer::Unload(void)
{

		m_pTexture->Release();
		m_pTexture = NULL;

}


//=============================================================================
// �֐����F�v���C���[�V�[���̐���
// �֐��̊T�v�F�v���C���[�V�[���𐶐�����
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer  *pPlayer;
	pPlayer = new CPlayer;//�V�[���N���X�̐���
	if (pPlayer != NULL)
	{
		pPlayer->m_pos = pos;
		pPlayer->m_bAction[PLAYERBOOLTYPE_JUMP] = false;
		pPlayer->Init();
	}
	return pPlayer;
}

//=============================================================================
// �֐����F�v���C���[�V�[���̏���������
// �֐��̊T�v�F�v���C���[���̐ݒ�
//=============================================================================
HRESULT CPlayer::Init(void)
{
#if 1
		CRenderer *pRenderer;
		pRenderer = CManager::GetRenderer();

		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = pRenderer->GetDevice();


		FILE *pFile = fopen(MODEL_FILENAME, "r");		// �ǂݍ��ރe�L�X�g�t�@�C���̃A�h���X

		char acLine[MAX_CHAR];							// 1�s���ǂݍ��ޕϐ�
		char acData[MAX_CHAR];							// 1����ǂݍ��ޕϐ�
		int nCntMotion = 0;								// ���[�V�����̃J�E���^
		int nCntKey = 0;								// �L�[�̃J�E���^
		int nCntParts = 0;								// �p�[�c�̃J�E���^
		int nCntModel = 0;								// �ǂݍ��ރ��f���̃J�E���^
		int nCntTexture = 0;							// �ǂݍ��ރe�N�X�`���̃J�E���^
		int nIndex = 0;									// �g�p���郂�f���̃^�C�v
		int nParent = 0;								// �e�̐���
		int nMaxParts = 0;								// �p�[�c���̍ő吔
		D3DXVECTOR3 pos;								// �ʒu������ϐ�
		D3DXVECTOR3 rot;								// ����������ϐ�

		if (pFile != NULL)
		{
			while (fgets(&acLine[0], MAX_CHAR, pFile) != NULL)
			{
				sscanf(&acLine[0], "%s", &acData);				// �����f�[�^�ɃR�s�[
				if (memcmp(acData, "CHARACTERSET", 12) == 0)
				{// "CHARACTERSET"�̕����񂪂�������
					nCntModel = 0;
					while (strcmp(acData, "END_CHARACTERSET") != 0)
					{// "END_CHARACTERSET"���܂ŏ����擾��������
						fgets(&acLine[0], MAXCHAR, pFile);					// �s���擾
						sscanf(&acLine[0], "%s", &acData);					// �f�[�^���R�s�[
						if (strcmp(acData, "PARTSSET") == 0)
						{// "MODELSET"�̕����񂪂�������
							while (strcmp(acData, "END_PARTSSET") != 0)
							{// "END_PARTSSET"���܂ŏ����擾��������
								fgets(&acLine[0], MAXCHAR, pFile);					// �s���擾
								sscanf(&acLine[0], "%s", &acData);					// �f�[�^���R�s�[
								if (strcmp(acData, "INDEX") == 0)
								{// "TYPE"�̕����񂪂�������
									sscanf(&acLine[0], "%s %s %d", &acData[0], &acData[0], &nIndex);					// �g�p���郂�f���̔ԍ����擾
									m_aIndex[nCntModel] = nIndex;
								}
								else if (strcmp(acData, "PARENT") == 0)
								{// "TYPE"�̕����񂪂�������
									sscanf(&acLine[0], "%s %s %d", &acData[0], &acData[0], &nParent);					// �g�p���郂�f���̔ԍ����擾
									m_aParent[nCntModel] = nParent;
								}
								else if (strcmp(acData, "POS") == 0)
								{// "POS"�̕����񂪂�������
									sscanf(&acLine[0], "%s %s %f %f %f", &acData[0], &acData[0], &pos.x, &pos.y, &pos.z);	// �ʒu���擾
									m_Partspos[nCntModel] = pos;
								}
								else if (strcmp(acData, "ROT") == 0)
								{// "ROT"�̕����񂪂�������
									sscanf(&acLine[0], "%s %s %f %f %f", &acData[0], &acData[0], &rot.x, &rot.y, &rot.z);	// �������擾
									//�e�L�X�g�̊p�x���ʂ�ɓ����v�Z
									rot.x = (D3DX_PI * 2 / 360.0f * rot.x);
									rot.y = (D3DX_PI * 2 / 360.0f * rot.y);
									rot.z = (D3DX_PI * 2 / 360.0f * rot.z);
									m_Partsrot[nCntModel] = rot;
								}
							}
							m_apModel[nCntModel] = CModel::Create(m_Partspos[nCntModel], m_Partsrot[nCntModel], m_aIndex[nCntModel], CModel::MODELTYPE_PLAYER);	//�p�[�c�̐���
							if (nCntModel == 0)
							{//�̂̃p�[�c�̂Ƃ�
								m_apModel[nCntModel]->SetParent(NULL);
							}
							else
							{//����ȊO�̃p�[�c�̂Ƃ�
								m_apModel[nCntModel]->SetParent(m_apModel[m_aParent[nCntModel]]);
							}
							m_apModel[nCntModel]->BindTexture(m_pTexture);
							nCntModel++;
						}//PARTSSET
					}//END_CHARACTERSET
				}//CHARACTERSET
				if (nCntMotion < MOTION_MAX)
				{// ���[�V�����̑����ȏ�͐ݒ肵�Ȃ�
					if (strcmp(acData, "MOTIONSET") == 0)
					{// MOTIONSET�̕����񂪂�������
						nCntKey = 0;
						while (strcmp(acData, "END_MOTIONSET") != 0)
						{// END_MOTIONSET��������܂Ń��[�v����
							fgets(&acLine[0], MAXCHAR, pFile);					// �s���擾
							sscanf(&acLine[0], "%s", &acData);					// �f�[�^���R�s�[

							if (strcmp(acData, "LOOP") == 0)
							{// LOOP����������
								sscanf(&acLine[0], "%s %s %d", &acData[0], &acData[0], &m_aKeyInfo[nCntMotion].nLoop);	// ���[�v���邩�ǂ������擾

							}
							else if (strcmp(acData, "NUM_KEY") == 0)
							{// NUM_KEY����������
								sscanf(&acLine[0], "%s %s %d", &acData[0], &acData[0], &m_aKeyInfo[nCntMotion].nNumKey);	// �L�[�����擾
							}
							else if (strcmp(acData, "KEYSET") == 0)
							{// KEYSET����������

								nCntParts = 0;// �p�[�c�̃J�E���g�ϐ���������

								while (strcmp(acData, "END_KEYSET") != 0)
								{// END_KEYSET������܂Ń��[�v
									fgets(&acLine[0], MAXCHAR, pFile);					// �s���擾
									sscanf(&acLine[0], "%s", &acData);					// �f�[�^���R�s�[

									if (strcmp(acData, "FRAME") == 0)
									{// FRAME����������
										sscanf(&acLine[0], "%s %s %d", &acData[0], &acData[0], &m_aKeyInfo[nCntMotion].aKey[nCntKey].nFrame);	// �L�[�̃t���[�������擾
									}
									else if (strcmp(acData, "KEY") == 0)
									{// KEY����������
										while (strcmp(acData, "END_KEY") != 0)
										{// END_KEY������܂Ń��[�v
											fgets(&acLine[0], MAXCHAR, pFile);					// �s���擾
											sscanf(&acLine[0], "%s", &acData);					// �f�[�^���R�s�[
											if (strcmp(acData, "POS") == 0)
											{// POS����������
												sscanf(&acLine[0],
													"%s %s %f %f %f",
													&acData[0],
													&acData[0],
													&m_aKeyInfo[nCntMotion].aKey[nCntKey].pos[nCntParts].x,		// �e�p�[�c�̃��[�V�����̈ʒu���擾
													&m_aKeyInfo[nCntMotion].aKey[nCntKey].pos[nCntParts].y,		// �e�p�[�c�̃��[�V�����̈ʒu���擾
													&m_aKeyInfo[nCntMotion].aKey[nCntKey].pos[nCntParts].z);		// �e�p�[�c�̃��[�V�����̈ʒu���擾
											}
											else if (strcmp(acData, "ROT") == 0)
											{// ROT����������
												sscanf(&acLine[0],
													"%s %s %f %f %f",
													&acData[0],
													&acData[0],
													&m_aKeyInfo[nCntMotion].aKey[nCntKey].rot[nCntParts].x,		// �e�p�[�c�̃��[�V�����̉�]���擾
													&m_aKeyInfo[nCntMotion].aKey[nCntKey].rot[nCntParts].y,		// �e�p�[�c�̃��[�V�����̉�]���擾
													&m_aKeyInfo[nCntMotion].aKey[nCntKey].rot[nCntParts].z);		// �e�p�[�c�̃��[�V�����̉�]���擾
											}//ROT
										}// END_KEY
										nCntParts++;// �p�[�c�̃J�E���g��i�߂�
									}// KEY
								}// END_KEYSET
								nCntKey++;// �L�[�t���[����i�߂�
							}//KEYSET
						}// END_MOTIONSET
						nCntMotion++;// ���[�V������ς���
					}// MOTIONSET
				}//���[�V�����̑����ȏ�͐ݒ肵�Ȃ�
			}//while
				fclose(pFile);// �J�����t�@�C�������
		}//�t�@�C�����J���Ă���

		//���[�V�����֌W
		m_nNumKey = 2;
		m_pKeyInfo = m_aKeyInfo;
		m_nKey = 0;
		m_nCountMotion = 0;
		m_Motionstate = MOTION_NEUTRAL;


		//�v���C���[���
		m_fRadius = PLAYER_COLLISION_RADIUS; // �v���C���[�̓����蔻��̔��a
		m_StateCnt = 20;
		m_state = PLAYERSTATE_APPEAR;

		for (int nCntKey = 0; nCntKey < m_aKeyInfo[m_Motionstate].nNumKey; nCntKey++)
		{//���t���[�����̌v�Z
			m_nAllFrame += m_aKeyInfo[m_Motionstate].aKey[nCntKey].nFrame;
		}

		for (int nCntParts = 0; nCntParts < MAX_PLAYER_PARTS; nCntParts++)
		{// �p�[�c�������[�v
			 // ���f���̈ʒu���j���[�g�������[�V�����ɏ�����
			m_PartsDefaultpos[nCntParts] = m_Partspos[nCntParts] + m_aKeyInfo[m_Motionstate].aKey[0].pos[nCntParts];
			m_PartsDefaultrot[nCntParts] = m_aKeyInfo[m_Motionstate].aKey[0].rot[nCntParts];
		}
		//2D�V�[���̃I�u�W�F�N�g�̐ݒ�
		SetObjType(CScene::OBJTYPE_PLAYER);
#endif
		return S_OK;
}
//=============================================================================
// �֐����F�v���C���[�V�[���̏I������
// �֐��̊T�v�F���b�V���A�}�e���A���A���g�̔j��
//=============================================================================
void CPlayer::Uninit(void)
{
	for (int nCntParts = 0; nCntParts < MAX_PLAYER_PARTS; nCntParts++)
	{
		//���f���̏I������
		if (m_apModel[nCntParts] != NULL)
		{
			m_apModel[nCntParts]->Uninit();
			delete m_apModel[nCntParts];
			m_apModel[nCntParts] = NULL;
		}
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �֐����F�v���C���[�V�[���̍X�V����
// �֐��̊T�v�F�v���C���[�̈ړ��A�p�[�c�̃��[�V�����X�V
//=============================================================================
void CPlayer::Update(void)
{

#if 1
	CInputX::InputJoyState JoyState = CInputX::GetJoystate();
	bool bConnect = CInputX::GetbConnect();			//�W���C�p�b�h�̐ڑ����

	//���
	XINPUT_STATE state;
	XInputGetState(0, &state);


	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//�f�o�C�X�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�J�����̎擾
	CCamera *pCamera;
	pCamera = CManager::GetCamera();

	//�J�����̊p�x�擾
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	//���b�V���t�B�[���h�擾
	CMeshField *pFieldField;
	pFieldField = CGame::GetSceneMeshField();


	//�G
	CEnemy *pEnemyTop;

	//�I�u�W�F�N�g
	CObject *pObjectTop;

	//�������擾
	float fHeight = pFieldField->GetHeight(m_pos);

	//���[�h�̎擾
	CManager::MODE mode;
	mode = CManager::GetMode();
	switch (mode)
	{
	case CManager::MODE_TITLE:
		break;
	case CManager::MODE_GAME:
		break;
	}

		//===========================================================================
		//�v���C���[�̏��
		//===========================================================================
		switch (m_state)
		{
		case PLAYERSTATE_NORMAL:
			break;

		case PLAYERSTATE_DAMAGE:
			m_StateCnt--;
			if (m_StateCnt <= 0)
			{
				m_StateCnt = 120;
				m_state = PLAYERSTATE_INVISIBLE;
			}
			break;

		case PLAYERSTATE_INVISIBLE:
			m_StateCnt--;
			if (m_StateCnt % 2 == 0)
			{// �_��
				m_bUseDraw = m_bUseDraw ? false : true;
			}
			if (m_StateCnt <= 0)
			{
				m_bUseDraw = true;
				m_state = PLAYERSTATE_NORMAL;
			}
			break;
		case PLAYERSTATE_APPEAR:
			m_StateCnt--;
			if (m_StateCnt <= 0)
			{
				m_state = PLAYERSTATE_NORMAL;

			}
		}

		//===========================================================================
		//�v���C���[�̈ړ�
		//===========================================================================
		if (m_state == PLAYERSTATE_NORMAL || m_state == PLAYERSTATE_INVISIBLE)
		{//�v���C���[�̏�Ԃňړ��ł��邩
			//=========================================
			//�C�ӂ̃L�[(���L�[)�������ꂽ���ǂ���    //
			//=========================================
			if (pInputKeyboard->GetKeyboardPress(DIK_A) == true || (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && bConnect == true))
			{//A�L�[�������ꂽ�Ƃ�
				if (pInputKeyboard->GetKeyboardPress(DIK_W) == true || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && bConnect == true))
				{//��L�[(W�L�[)�������ꂽ
					m_move.x += sinf(-D3DX_PI * 0.25f + CameraRot.y) * PLAYER_MOVE;
					m_move.z += cosf(-D3DX_PI * 0.25f + CameraRot.y) * PLAYER_MOVE;
					m_fDestAngle = (D3DX_PI * 0.75f) + CameraRot.y;


				}
				else if (pInputKeyboard->GetKeyboardPress(DIK_S) == true || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && bConnect == true))
				{//���L�[(���L�[)�������ꂽ
					m_move.x += sinf(-D3DX_PI * 0.75f + CameraRot.y) * PLAYER_MOVE;
					m_move.z += cosf(-D3DX_PI * 0.75f + CameraRot.y) * PLAYER_MOVE;
					m_fDestAngle = (D3DX_PI * 0.25f) + CameraRot.y;


				}
				else
				{//���L�[(���L�[)�̂�
					m_move.x += sinf((-D3DX_PI *  0.5f) + CameraRot.y) * PLAYER_MOVE;
					m_move.z += cosf((-D3DX_PI *  0.5f) + CameraRot.y) * PLAYER_MOVE;

					m_fDestAngle = (D3DX_PI * 0.5f + CameraRot.y);
				}
			}
			//=========================================
			//�C�ӂ̃L�[(D�L�[)�������ꂽ���ǂ���    //
			//=========================================
			else if (pInputKeyboard->GetKeyboardPress(DIK_D) == true || (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && bConnect == true))
			{
				if (pInputKeyboard->GetKeyboardPress(DIK_W) == true || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && bConnect == true))
				{//��L�[(���L�[)�������ꂽ
					m_move.x += sinf(D3DX_PI *  0.25f + CameraRot.y) * PLAYER_MOVE;
					m_move.z += cosf(D3DX_PI *  0.25f + CameraRot.y) * PLAYER_MOVE;
					m_fDestAngle = (D3DX_PI * -0.75f) + CameraRot.y;

				}
				else if (pInputKeyboard->GetKeyboardPress(DIK_S) == true || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && bConnect == true))
				{//���L�[(���L�[)�������ꂽ
					m_move.x += sinf(D3DX_PI * 0.75f + CameraRot.y) * PLAYER_MOVE;
					m_move.z += cosf(D3DX_PI * 0.75f + CameraRot.y) * PLAYER_MOVE;
					m_fDestAngle = (D3DX_PI * -0.25f) + CameraRot.y;

				}
				else
				{//�E�L�[(���L�[)�̂�
					m_move.x += sinf((D3DX_PI *  0.5f) + CameraRot.y) * PLAYER_MOVE;
					m_move.z += cosf((D3DX_PI *  0.5f) + CameraRot.y) * PLAYER_MOVE;
					m_fDestAngle = (D3DX_PI * -0.5f) + CameraRot.y;

				}
			}
			//=========================================
			//�C�ӂ̃L�[(W�L�[)�������ꂽ���ǂ���    //
			//=========================================
			else if (pInputKeyboard->GetKeyboardPress(DIK_W) == true || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && bConnect == true))
			{//���L�[�������ꂽ�Ƃ�
				m_move.x += sinf(D3DX_PI * 0.0f + CameraRot.y) * PLAYER_MOVE;
				m_move.z += cosf(D3DX_PI * 0.0f + CameraRot.y) * PLAYER_MOVE;

				m_fDestAngle = (D3DX_PI)+CameraRot.y;
			}
			//=========================================
			//�C�ӂ̃L�[(S�L�[)�������ꂽ���ǂ���    //
			//=========================================
			else if (pInputKeyboard->GetKeyboardPress(DIK_S) == true || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && bConnect == true))
			{//���L�[�������ꂽ�Ƃ�
				m_move.x -= sinf(D3DX_PI * 0.0f + CameraRot.y) * PLAYER_MOVE;
				m_move.z -= cosf(D3DX_PI * 0.0f + CameraRot.y) * PLAYER_MOVE;

				m_fDestAngle = (D3DX_PI * 0.0f) + CameraRot.y;
			}


			//=============================================
			//�C�ӂ̃L�[(�G���^�[�L�[)�������ꂽ���ǂ��� //
			//=============================================
			if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true)
			{//�G���^�[�L�[�������ꂽ�Ƃ�
			}

			//=============================================
			//�C�ӂ̃L�[(�X�y�[�X�L�[)�������ꂽ���ǂ��� //
			//=============================================
			if (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) == true )
			{//�X�y�[�X�L�[�������ꂽ�Ƃ�
					if (m_bAction[PLAYERBOOLTYPE_JUMP] == false)
					{
						m_bAction[PLAYERBOOLTYPE_JUMP] = true;
						m_move.y += JUMP_POWER;
					}
			}

		}//(��)�v���C���[�̏�Ԃňړ��ł��邩


		if (JoyState == CInputX::INPUT_JOYSTATE_PUSH)
		{
			JoyState = CInputX::INPUT_JOYSTATE_NONE;
		}
		else if (JoyState == CInputX::INPUT_JOYSTATE_NONE)
		{
			JoyState = CInputX::INPUT_JOYSTATE_NOTPUSH;
		}


	 //=============================================
	 // �����蔻��		(�G)
	 //=============================================
	pEnemyTop = (CEnemy*)GetSceneTop(ENEMY_PRIORITY);
	while (pEnemyTop != NULL)//NULL�ɂȂ�܂�
	{
		CEnemy *pEnemyNext;
		pEnemyNext = (CEnemy*)pEnemyTop->GetSceneNext(ENEMY_PRIORITY);
		if (pEnemyTop->GetObjType() == CScene::OBJTYPE_ENEMY)
		{
			if (m_state == PLAYERSTATE_NORMAL)
			{
				if (pEnemyTop->CollisionEnemy(&m_pos, &m_move, &m_rot) == true)
				{
					pSound->PlaySound(CSound::SOUND_LABEL_SE_HIT);
					m_bAction[PLAYERBOOLTYPE_DAMAGE] = true;
					m_StateCnt = 30;
					m_state = PLAYERSTATE_DAMAGE;
				}
			}
		}
		pEnemyTop = pEnemyNext;
	}


	 //=============================================
	 // ���[�V�����̏�ԍX�V
	 //=============================================
	PlayerMotionState(m_bAction);
	PlayerMotion();

	//�ʒu������
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
	//�����ړ�
	m_move.x += (0.0f - m_move.x) * 0.12f;
	m_move.y += (0.0f - m_move.y) * 0.12f;
	m_move.z += (0.0f - m_move.z) * 0.12f;


	//=============================================
	// �����蔻��		(�I�u�W�F�N�g)
	//=============================================
	pObjectTop = (CObject*)GetSceneTop(OBJECT_PRIORITY);
	while (pObjectTop != NULL)//NULL�ɂȂ�܂�
	{
		CObject *pObjectNext;
		pObjectNext = (CObject*)pObjectTop->GetSceneNext(OBJECT_PRIORITY);
		if (pObjectTop->GetObjType() == CScene::OBJTYPE_OBJECT)
		{
			if (pObjectTop->CollisionObject(&m_pos, &m_posold, &m_move, m_fRadius) == true)
			{
				m_bAction[PLAYERBOOLTYPE_JUMP] = false;
			}
		}
		pObjectTop = pObjectNext;
	}

	//�ړI�̊p�x�܂�
	m_fAngle = m_fDestAngle - m_rot.y;
	//�p�x����
	if (m_fAngle > D3DX_PI)
	{
		m_fAngle -= D3DX_PI * 2;
	}

	if (m_fAngle < -D3DX_PI)
	{
		m_fAngle += D3DX_PI * 2;
	}
	//�v���C���[�̊p�x����
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}

	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	//�p�x���
	m_rot.y += m_fAngle * 0.1f;

	//�J�����̊p�x����
	if (CameraRot.y > D3DX_PI)
	{
		CameraRot.y -= D3DX_PI * 2;
	}

	if (CameraRot.y < -D3DX_PI)
	{
		CameraRot.y += D3DX_PI * 2;
	}


	//����
	m_move.y -= GRAVITY_NUM;
	if (m_pos.y <= fHeight)
	{//���̍����ȉ���������
		m_pos.y = fHeight;//������n�ʂ̍�����
		m_move.y = 0.0f;
		if (m_bAction[PLAYERBOOLTYPE_JUMP] == true)
		{
			if (m_move.x < 0.2f && m_move.x > -0.2f && m_move.z < 0.2f && m_move.z > -0.2f)
			{
				m_bAction[PLAYERBOOLTYPE_LANDING] = true;//���n��Ԃ�
				m_bAction[PLAYERBOOLTYPE_JUMP] = false;	//�W�����v��Ԃ�����
			}
			m_bAction[PLAYERBOOLTYPE_JUMP] = false;//�W�����v�ł����Ԃ�
		}
		if (m_bAction[PLAYERBOOLTYPE_DAMAGE] == true)
		{// �_���[�W���ɒ��n������
			m_StateCnt = 120;
			m_state = PLAYERSTATE_INVISIBLE;
			m_bAction[PLAYERBOOLTYPE_DAMAGE] = false;				//�_���[�W��Ԃ�����
		}
	}


	if (m_pos.x >= SCREEN_LIMIT_MAX_X)
	{
		m_pos.x = SCREEN_LIMIT_MAX_X;
	}
	if (m_pos.x <= SCREEN_LIMIT_MIN_X)
	{
		m_pos.x = SCREEN_LIMIT_MIN_X;

	}



	//==================================================================================================
	// �f�o�b�O���O�֌W
	//==================================================================================================
	//CDebugProc::Print("\n");
	//CDebugProc::Print("[%d]�v���C���[\n", GetPriority());
	//CDebugProc::Print("�v���C���[�ʒu(XYZ): %.1f, %.1f, %.1f�F\n",m_pos.x, m_pos.y, m_pos.z);
	//CDebugProc::Print("�v���C���[�p�x(XYZ): %.1f, %.1f, %.1f�F\n", m_rot.x, m_rot.y, m_rot.z);
	//CDebugProc::Print("�v���C���[�ړ���(XYZ): %.1f, %.1f, %.1f�F\n", m_move.x, m_move.y, m_move.z);
	//CDebugProc::Print("��ԕω��̃J�E���^�F%d\n", m_StateCnt);

	//switch (m_state)
	//{
	//case PLAYERSTATE_NORMAL://�ʏ��Ԃ̂Ƃ�
	//	CDebugProc::Print("STATE�F[0]NORMAL\n");
	//	break;
	//case PLAYERSTATE_DAMAGE://�_���[�W��Ԃ̂Ƃ�
	//	CDebugProc::Print("STATE�F[1]DAMAGE\n");
	//	break;
	//case PLAYERSTATE_INVISIBLE://���G�̂Ƃ�
	//	CDebugProc::Print("STATE�F[2]INVISIBLE\n");
	//	break;
	//case PLAYERSTATE_APPEAR://�o�����̂Ƃ�
	//	CDebugProc::Print("STATE�F[3]PLAYERSTATE_APPEAR\n");
	//	break;
	//}

	//switch (m_Motionstate)
	//{
	//case MOTION_NEUTRAL://�j���[�g�����̂Ƃ�
	//	CDebugProc::Print("MOTION�F[0]NEUTRAL\n");
	//	break;
	//case MOTION_MOVE://�ړ��̂Ƃ�
	//	CDebugProc::Print("MOTION�F[1]MOVE\n");
	//	break;
	//case MOTION_JUMP://�W�����v�̂Ƃ�
	//	CDebugProc::Print("MOTION�F[2]JUMP\n");
	//	break;
	//case MOTION_LANDING://���n�̂Ƃ�
	//	CDebugProc::Print("MOTION�F[3]LANDING\n");
	//	break;
	//}

	//CDebugProc::Print("KEY�F%d / %d\n", m_nCounterKey, m_aKeyInfo[m_Motionstate].nNumKey);
	//CDebugProc::Print("FRAME�F%d / %d (%d / %d)\n", m_nCounterFrame, m_nFrame, m_nCounterAllFrame, m_nAllFrame);
	//CDebugProc::Print("AllFrame�F%d\n", m_nCounterAllFrame);

	//�ȑO�̈ʒu�ɍ��̈ʒu����
	m_posold = m_pos;

	//�ȑO�̃��[�V��������
	m_MotionstateOld = m_Motionstate;

#endif


}

//=============================================================================
// �֐����F�v���C���[�V�[���̕`�揈��
// �֐��̊T�v�F�v���C���[�̃}�g���b�N�X�ݒ�A�e�p�[�c�̕`��
//=============================================================================
void CPlayer::Draw(void)
{
#if 1
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();


	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxrot, mtxtrans;


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxrot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxrot);


	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxtrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxtrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxPartsrot, mtxPartstrans;

	if (m_bUseDraw == true)
	{
		for (int nCntParts = 0; nCntParts < MAX_PLAYER_PARTS; nCntParts++)
		{
			//���f���̕`��
			m_apModel[nCntParts]->Draw();
		}
	}
#endif
}

//=============================================================================
// �֐����F�v���C���[�̃��[�V����
// �֐��̊T�v�F�u�����h�ݒ��A���[�V����
//=============================================================================
void CPlayer::PlayerMotion(void)
{
	//-----------------------------------------------------------------------
	// ���[�V�����u�����h�̐ݒ�
	//-----------------------------------------------------------------------
	if (m_Motionstate != m_MotionstateOld)
	{// ���[�V�����̃X�e�[�g���ς������
		m_nCounterFrame = 0;						// ���݂̃L�[�t���[���̃t���[������������
		m_nCounterKey = 0;							// �L�[�t���[���̏�����
		m_nCounterAllFrame = 0;						// ���[�V�����̃t���[������������
		m_nFrame = PLAYER_MOTION_BLEND_FRAME;		// ���[�V�����u�����h�̃t���[������ݒ�
		m_nAllFrame = 0;
		for (int nCntKey = 0; nCntKey < m_aKeyInfo[m_Motionstate].nNumKey; nCntKey++)
		{//���t���[�����̌v�Z
			m_nAllFrame += m_aKeyInfo[m_Motionstate].aKey[nCntKey].nFrame;
		}
		m_bMotionBlend = true;						// ���[�V�����u�����h��true�ɂ���
	}

	//-----------------------------------------------------------------------
	// �L�[�t���[���̐؂�ւ��
	//-----------------------------------------------------------------------
	if (m_nCounterFrame == m_nFrame)
	{// ���[�V�����u�����h�̎��A�t���[�������Ō�ɂȂ�����
		m_nCounterFrame = 0; // ���݂̃L�[�t���[���̃t���[������������
		m_nFrame = m_aKeyInfo[m_Motionstate].aKey[m_nCounterKey].nFrame; // ���[�V�����̃t���[������ݒ�

		m_nCounterKey++; // �L�[�t���[����i�߂�

		if (m_nCounterKey == m_aKeyInfo[m_Motionstate].nNumKey)
		{// �L�[�t���[�����Ō�܂ŗ�����
			if (m_aKeyInfo[m_Motionstate].nLoop == 0)
			{// ���[�v���Ȃ��ꍇ
				switch (m_Motionstate)
				{// �v���C���[�̃��[�V������
				case MOTION_JUMP: // �W�����v���[�V������������
					m_nCounterKey--; // �L�[�t���[����߂�
					break;

				case MOTION_LANDING: // ���n���[�V������������
					m_bAction[PLAYERBOOLTYPE_LANDING] = false;
					m_nCounterKey--; // �L�[�t���[����߂�
					break;

				case MOTION_DAMAGE: // �_���[�W���[�V������������
					m_bAction[PLAYERBOOLTYPE_DAMAGE] = false;// �_���[�W������Ȃ���Ԃɂ���
					m_nCounterKey--; // �L�[�t���[����߂�
					break;
				}
			}
			else
			{// ���[�v����
				m_nCounterKey = m_nCounterKey % m_aKeyInfo[m_Motionstate].nNumKey; // �L�[�t���[����i�߂�
				m_nCounterAllFrame = 0; // ���[�V�����̃t���[����(ALL)��������
			}
		}
	}

	//-----------------------------------------------------------------------
	// ���[�V�����̍�������
	//-----------------------------------------------------------------------
	if (m_nCounterFrame == 0)
	{// �t���[�������ŏ��̎�
		for (int nCntParts = 0; nCntParts < MAX_PLAYER_PARTS; nCntParts++)
		{// �p�[�c�������[�v
		 // ���[�V�����̈ʒu��������
			m_Motionpos[nCntParts] = (m_aKeyInfo[m_Motionstate].aKey[m_nCounterKey].pos[nCntParts] + m_Partspos[nCntParts]) - m_PartsDefaultpos[nCntParts];
			// ���[�V�����̉�]��������
			m_Motionrot[nCntParts] = m_aKeyInfo[m_Motionstate].aKey[m_nCounterKey].rot[nCntParts] - m_PartsDefaultrot[nCntParts];

			// ��]�̍������C������
			// X���̏C��
			if (m_Motionrot[nCntParts].x > D3DX_PI)
			{// +3.14���A�����Ă��܂�����
				m_Motionrot[nCntParts].x -= D3DX_PI * 2.0f;
			}
			else if (m_Motionrot[nCntParts].x < -D3DX_PI)
			{// -3.14���A���������
				m_Motionrot[nCntParts].x += D3DX_PI * 2.0f;
			}
			// Y���̏C��
			if (m_Motionrot[nCntParts].y > D3DX_PI)
			{// +3.14���A�����Ă��܂�����
				m_Motionrot[nCntParts].y -= D3DX_PI * 2.0f;
			}
			else if (m_Motionrot[nCntParts].y < -D3DX_PI)
			{// -3.14���A���������
				m_Motionrot[nCntParts].y += D3DX_PI * 2.0f;
			}
			// Z���̏C��
			if (m_Motionrot[nCntParts].z > D3DX_PI)
			{// +3.14���A�����Ă��܂�����
				m_Motionrot[nCntParts].z -= D3DX_PI * 2.0f;
			}
			else if (m_Motionrot[nCntParts].z < -D3DX_PI)
			{// -3.14���A���������
				m_Motionrot[nCntParts].z += D3DX_PI * 2.0f;
			}
		}
	}

	//----------------------------------------------
	// ���[�V�����̓���
	//----------------------------------------------
	for (int nCntParts = 0; nCntParts < MAX_PLAYER_PARTS; nCntParts++)
	{// �p�[�c�������[�v
	 // �ʒu�������t���[�����Ŋ������l�����Z���Ă���
		m_PartsDefaultpos[nCntParts].x += m_Motionpos[nCntParts].x / m_nFrame;		// �ʒu�̍������t���[�����Ŋ������l�����Z���Ă���
		m_PartsDefaultpos[nCntParts].y += m_Motionpos[nCntParts].y / m_nFrame;		// �ʒu�̍������t���[�����Ŋ������l�����Z���Ă���
		m_PartsDefaultpos[nCntParts].z += m_Motionpos[nCntParts].z / m_nFrame;		// �ʒu�̍������t���[�����Ŋ������l�����Z���Ă���
		//��]�l�̑��
		m_apModel[nCntParts]->SetPos(m_PartsDefaultpos[nCntParts]);

		// ��]�������t���[�����Ŋ������l�����Z���Ă���
		m_PartsDefaultrot[nCntParts].x += m_Motionrot[nCntParts].x / m_nFrame;				// ��]�̍������t���[�����Ŋ������l�����Z���Ă���
		m_PartsDefaultrot[nCntParts].y += m_Motionrot[nCntParts].y / m_nFrame;				// ��]�̍������t���[�����Ŋ������l�����Z���Ă���
		m_PartsDefaultrot[nCntParts].z += m_Motionrot[nCntParts].z / m_nFrame;				// ��]�̍������t���[�����Ŋ������l�����Z���Ă���
		//��]�l�̑��
		m_apModel[nCntParts]->SetRot(m_PartsDefaultrot[nCntParts]);

		// ���f���̉�]���C������
		// X���̏C��
		if (m_Partsrot[nCntParts].x > D3DX_PI)
		{// +3.14���A�����Ă��܂�����
			m_Partsrot[nCntParts].x -= D3DX_PI * 2.0f;
		}
		else if (m_Partsrot[nCntParts].x < -D3DX_PI)
		{// -3.14���A���������
			m_Partsrot[nCntParts].x += D3DX_PI * 2.0f;
		}
		// Y���̏C��
		if (m_Partsrot[nCntParts].y > D3DX_PI)
		{// +3.14���A�����Ă��܂�����
			m_Partsrot[nCntParts].y -= D3DX_PI * 2.0f;
		}
		else if (m_Partsrot[nCntParts].y < -D3DX_PI)
		{// -3.14���A���������
			m_Partsrot[nCntParts].y += D3DX_PI * 2.0f;
		}
		// Z���̏C��
		if (m_Partsrot[nCntParts].z > D3DX_PI)
		{// +3.14���A�����Ă��܂�����
			m_Partsrot[nCntParts].z -= D3DX_PI * 2.0f;
		}
		else if (m_Partsrot[nCntParts].z < -D3DX_PI)
		{// -3.14���A���������
			m_Partsrot[nCntParts].z += D3DX_PI * 2.0f;
		}
	}

	m_nCounterFrame++;		// ���݃L�[�t���[���̃t���[���������Z
	m_nCounterAllFrame++;	// ���[�V�����̃t���[���������Z
}

//=============================================================================
// �֐����F�v���C���[�̃��[�V�����X�e�[�g�̕ύX
// �֐��̊T�v�F�v���C���[�̏�ԑJ��
//=============================================================================
void CPlayer::PlayerMotionState(bool *bAction)
{
	if (bAction[PLAYERBOOLTYPE_DEAD] == true)
	{// ���񂾂Ȃ�
	 m_Motionstate = MOTION_DEATH; // ���S���[�V�����ɐݒ�
	}
	else if (bAction[PLAYERBOOLTYPE_DAMAGE] == true)
	{// �_���[�W���Ȃ�
	 m_Motionstate = MOTION_DAMAGE; // �_���[�W���[�V�����ɐݒ�
	}
	else if (bAction[PLAYERBOOLTYPE_LANDING] == true)
	{// �_���[�W���n
		m_Motionstate = MOTION_LANDING; // ���n���[�V�����ɐݒ�
	}
	else if (bAction[PLAYERBOOLTYPE_JUMP] == true)
	{// �v���C���[���W�����v���Ȃ�
		m_Motionstate = MOTION_JUMP; // �W�����v���[�V�����ɐݒ�
	}
	else if (m_move.x >  PLAYER_MOVE_DEFAULT ||
		m_move.x < -PLAYER_MOVE_DEFAULT ||
		m_move.z >  PLAYER_MOVE_DEFAULT ||
		m_move.z < -PLAYER_MOVE_DEFAULT)
	{// �v���C���[�������Ă���Ƃ�
		m_Motionstate = MOTION_MOVE; // �ړ���Ԃɂ���
	}
	else
	{// �v���C���[�������ĂȂ��Ƃ�
		m_Motionstate = MOTION_NEUTRAL; // �j���[�g������Ԃɂ���
	}
}


//=============================================================================
// �֐����F�p�x�̏C��
// �֐��̊T�v�F�傫����΁A�����A��������΁A����
//=============================================================================
void CPlayer::PlayerRotFixes(D3DXVECTOR3 rot)
{
	// X���̏C��
	if (rot.x > D3DX_PI)
	{// +3.14���A�����Ă��܂�����
		rot.x -= D3DX_PI * 2.0f;
	}
	else if (rot.x < -D3DX_PI)
	{// -3.14���A���������
		rot.x += D3DX_PI * 2.0f;
	}
	// Y���̏C��
	if (rot.y > D3DX_PI)
	{// +3.14���A�����Ă��܂�����
		rot.y -= D3DX_PI * 2.0f;
	}
	else if (rot.y < -D3DX_PI)
	{// -3.14���A���������
		rot.y += D3DX_PI * 2.0f;
	}
	// Z���̏C��
	if (rot.z > D3DX_PI)
	{// +3.14���A�����Ă��܂�����
		rot.z -= D3DX_PI * 2.0f;
	}
	else if (rot.z < -D3DX_PI)
	{// -3.14���A���������
		rot.z += D3DX_PI * 2.0f;
	}
}
//=============================================================================
// �֐����F�p�x�̏C��
// �֐��̊T�v�F�傫����΁A�����A��������΁A����
//=============================================================================
void CPlayer::PlayerRotFixes(float rot)
{
	if (rot > D3DX_PI)
	{// +3.14���A�����Ă��܂�����
		rot -= D3DX_PI * 2.0f;
	}
	else if (rot < -D3DX_PI)
	{// -3.14���A���������
		rot += D3DX_PI * 2.0f;
	}

}

//=============================================================================
// �֐����F�ʒu���̎擾
// �֐��̊T�v�F�v���C���[�̈ʒu����Ԃ�
//=============================================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �֐����F�p�x���̎擾
// �֐��̊T�v�F�v���C���[�̊p�x����Ԃ�
//=============================================================================
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}


