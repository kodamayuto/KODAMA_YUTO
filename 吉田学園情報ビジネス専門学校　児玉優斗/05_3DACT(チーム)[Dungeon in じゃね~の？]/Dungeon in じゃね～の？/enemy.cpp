//=============================================================================
//
// �G����[���f��] [player.cpp]
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
#include "enemy.h"
#include "camera.h"
#include "meshfield.h"
#include "model.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_MOVE (0.35f)										//�ړ���
#define ENEMY_WALK_DEFAULT		(0.15f)							// �G�������Ă��̈ړ���
#define ENEMY_DASH_DEFAULT		(1.5f)							// �G�������Ă��̈ړ���
#define MAX_CHAR (256)											//�����̍ő吔
#define GRAVITY_NUM (0.8f)										//�d�͂̒l
#define PLAYER_MOTION_BLEND_FRAME	(5)							// ���[�V�����u�����h�̃t���[����
#define JUMP_POWER (20.0f)										//�W�����v��
#define ENEMY_INDEX (14)
#define MODEL_FILENAME ("data/TEXT/motion_enemy.txt")			//�ǂݍ��ރt�@�C����


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL; //���L�e�N�X�`���̃|�C���^
int CEnemy::m_aParent[MAX_ENEMY_PARTS] = {};				//�p�[�c�̐e
int CEnemy::m_aIndex[MAX_ENEMY_PARTS] = {};				//�p�[�c�ԍ�


//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CEnemy::CEnemy(int nPriority, OBJTYPE type) : CScene(nPriority, type)
{
}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�Ō�ɌĂяo�����
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// �֐����F�g�p����e�N�X�`���̓ǂݍ���
// �֐��̊T�v�F--
//=============================================================================
HRESULT CEnemy::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/skeleton.png", &m_pTexture);

	return S_OK;

}

//=============================================================================
// �֐����F�g�p�����e�N�X�`���̔j��
// �֐��̊T�v�F--
//=============================================================================
void CEnemy::Unload(void)
{

	m_pTexture->Release();
	m_pTexture = NULL;

}


//=============================================================================
// �֐����F�G�V�[���̐���
// �֐��̊T�v�F�G�V�[���𐶐�����
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	CEnemy  *pEnemy;
	pEnemy = new CEnemy;//�V�[���N���X�̐���
	if (pEnemy != NULL)
	{
		pEnemy->m_pos = pos;
		pEnemy->m_Startpos = pos;
		pEnemy->m_type = type;
		pEnemy->m_fHeight = 25.0f;
		pEnemy->m_bAction[ENEMYBOOLTYPE_JUMP] = false;
		pEnemy->Init();

	}
	return pEnemy;
}

//=============================================================================
// �֐����F�G�V�[���̏���������
// �֐��̊T�v�F�G���̐ݒ�
//=============================================================================
HRESULT CEnemy::Init(void)
{

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
								m_aIndex[nCntModel] = nIndex + ENEMY_INDEX;
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
						m_apModel[nCntModel] = CModel::Create(m_Partspos[nCntModel], m_Partsrot[nCntModel], m_aIndex[nCntModel], CModel::MODELTYPE_ENEMY);
						if (nCntModel == 0)
						{
							m_apModel[nCntModel]->SetParent(NULL);
						}
						else
						{
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
	for (int nCntKey = 0; nCntKey < m_aKeyInfo[m_Motionstate].nNumKey; nCntKey++)
	{//���t���[�����̌v�Z
		m_nAllFrame += m_aKeyInfo[m_Motionstate].aKey[nCntKey].nFrame;
	}
	for (int nCntParts = 0; nCntParts < MAX_ENEMY_PARTS; nCntParts++)
	{// �p�[�c�������[�v
		 // ���f���̈ʒu���j���[�g�������[�V�����ɏ�����
		m_PartsDefaultpos[nCntParts] = m_Partspos[nCntParts] + m_aKeyInfo[m_Motionstate].aKey[0].pos[nCntParts];
		m_PartsDefaultrot[nCntParts] = m_aKeyInfo[m_Motionstate].aKey[0].rot[nCntParts];

	}

	//2D�V�[���̃I�u�W�F�N�g�̐ݒ�
	SetObjType(CScene::OBJTYPE_ENEMY);
	return S_OK;
}
//=============================================================================
// �֐����F�G�V�[���̏I������
// �֐��̊T�v�F���b�V���A�}�e���A���A���g�̔j��
//=============================================================================
void CEnemy::Uninit(void)
{
	for (int nCntParts = 0; nCntParts < MAX_ENEMY_PARTS; nCntParts++)
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
// �֐����F�G�V�[���̍X�V����
// �֐��̊T�v�F�G�̈ړ��A�p�[�c�̃��[�V�����X�V
//=============================================================================
void CEnemy::Update(void)
{

	//�f�o�C�X�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�J�����̎擾
	CCamera *pCamera;
	pCamera = CManager::GetCamera();

	//�J�����̊p�x�擾
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	//���b�V���t�B�[���h�擾
	CMeshField *pMeshField;
	pMeshField = CGame::GetSceneMeshField();

	//�G�̎擾
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 playerpos = pPlayer->GetPos();

	switch (m_type)
	{
	case ENEMYTYPE_LOITERING_Z:
		if (m_pos.z <= m_Startpos.z - 150.0f)
		{//��O���Ɉړ�
			m_bSwitch = false;
		}
		if (m_pos.z >= m_Startpos.z + 150.0f)
		{//�����Ɉړ�
			m_bSwitch = true;
		}
		if (m_bSwitch == false)
		{
			m_move.z += 0.18f;
			m_fDestAngle = (D3DX_PI);
		}
		if (m_bSwitch == true)
		{
			m_move.z -= 0.18f;
			m_fDestAngle = (D3DX_PI * 0.0f);
		}
		break;
	case ENEMYTYPE_LOITERING_X:
		if (m_pos.x <= m_Startpos.x - 150.0f)
		{//��O���Ɉړ�
			m_bSwitch = false;
		}
		if (m_pos.x >= m_Startpos.x + 150.0f)
		{//�����Ɉړ�
			m_bSwitch = true;
		}
		if (m_bSwitch == false)
		{
			m_move.x += 0.18f;
			m_fDestAngle = (D3DX_PI * -0.5f);

		}
		if (m_bSwitch == true)
		{
			m_move.x -= 0.18f;
			m_fDestAngle = (D3DX_PI * 0.5f);
		}
		break;
	case ENEMYTYPE_CHASE:
		if (FindPlayer(&playerpos, 12.0f) == true)
		{//�v���C���[���͈͓��ɓ�������
			D3DXVECTOR3 DiffPos;

			//�v���C���[�ƓG�̃x�N�g�����Z�o
			DiffPos = m_pos - playerpos;
			D3DXVec3Normalize(&DiffPos, &DiffPos);

			//�x�N�g�������Ɍ������Ĉړ�
			m_move.x -= DiffPos.x * 0.21f;
			m_move.z -= DiffPos.z * 0.21f;

			//�G�̊p�x�ݒ�
			m_fDestAngle = atan2f(m_pos.x - playerpos.x, m_pos.z - playerpos.z);
		}
		else
		{//�v���C���[���͈͊O�ɏo����
			D3DXVECTOR3 DiffPos;
			//�G�̏����ʒu�Ƃ̃x�N�g�����Z�o
			DiffPos = m_pos - m_Startpos;
			D3DXVec3Normalize(&DiffPos, &DiffPos);

			if (m_pos.x >= m_Startpos.x - 5.0f && m_pos.x <= m_Startpos.x + 5.0f &&
				m_pos.z >= m_Startpos.z - 5.0f && m_pos.z <= m_Startpos.z + 5.0f)
			{//�����ʒu�ɖ߂�����
				m_move.x = 0.0f;
				m_move.z = 0.0f;

			}
			else
			{//�����ʒu�ɖ߂��Ă��Ȃ��Ƃ�
				//�x�N�g�������Ɍ������Ĉړ�
				m_move.x -= DiffPos.x * 0.15f;
				m_move.z -= DiffPos.z * 0.15f;
			}

			//�G�̊p�x�ݒ�
			m_fDestAngle = atan2f(m_pos.x - m_Startpos.x, m_pos.z - m_Startpos.z);
		}
		break;
	case ENEMYTYPE_TEST:

		break;

	}


	//�������擾
	float fHeight = pMeshField->GetHeight(m_pos);


	//---------------------------------------------------
	// ���[�V�����̏�ԍX�V
	//-------------------------------------------------
	EnemyMotionState(m_bAction);
	EnemyMotion();

	//�ʒu������
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
	//�����ړ�
	m_move.x += (0.0f - m_move.x) * 0.12f;
	m_move.y += (0.0f - m_move.y) * 0.12f;
	m_move.z += (0.0f - m_move.z) * 0.12f;

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
	//�G�̊p�x����
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
	if (m_pos.y <= 0.0)
	{
		m_pos.y = 0.0f;//������n�ʂ̍�����
		m_move.y = 0.0f;
		if (m_bAction[ENEMYBOOLTYPE_JUMP] == true)
		{
			if (m_move.x < 1.0f && m_move.x > -1.0f && m_move.z < 1.0f && m_move.z > -1.0f)
			{
				m_bAction[ENEMYBOOLTYPE_LANDING] = true;//���n��Ԃ�
			}
			m_bAction[ENEMYBOOLTYPE_JUMP] = false;//�W�����v�ł����Ԃ�

		}
	}
	if (m_pos.y <= fHeight)
	{//���̍����ȉ���������
		m_pos.y = fHeight;//������n�ʂ̍�����
		m_move.y = 0.0f;
		if (m_bAction[ENEMYBOOLTYPE_JUMP] == true)
		{
			if (m_move.x < 0.1f && m_move.x > -0.1 || m_move.z < 0.1f && m_move.z > -0.1)
			{
				m_bAction[ENEMYBOOLTYPE_LANDING] = true;//���n��Ԃ�
			}			m_bAction[ENEMYBOOLTYPE_JUMP] = false;//�W�����v�ł����Ԃ�
		}
	}
	else
	{//�󒆂ɂ���Ƃ�
		m_bAction[ENEMYBOOLTYPE_JUMP] = true;//�W�����v�ł��Ȃ���Ԃ�
	}

	//CDebugProc::Print("m_pos: %.1f,%.1f, %.1f\n", m_pos.x, m_pos.y, m_pos.z);


	//�ȑO�̈ʒu�����̈ʒu�ɑ��
	m_posold = m_pos;


	m_MotionstateOld = m_Motionstate;
}

//=============================================================================
// �֐����F�G�V�[���̕`�揈��
// �֐��̊T�v�F�G�̃}�g���b�N�X�ݒ�A�e�p�[�c�̕`��
//=============================================================================
void CEnemy::Draw(void)
{
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

	for (int nCntParts = 0; nCntParts < MAX_ENEMY_PARTS; nCntParts++)
	{
		//���f���̕`��
		m_apModel[nCntParts]->Draw();
	}
}

//=============================================================================
// �֐����F�G�̃��[�V����
// �֐��̊T�v�F�u�����h�ݒ��A���[�V����
//=============================================================================
void CEnemy::EnemyMotion(void)
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
				{// �G�̃��[�V������
				case MOTION_JUMP: // �W�����v���[�V������������
					m_nCounterKey--; // �L�[�t���[����߂�
					break;

				case MOTION_LANDING: // ���n���[�V������������
					m_bAction[ENEMYBOOLTYPE_LANDING] = false;
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
		for (int nCntParts = 0; nCntParts < MAX_ENEMY_PARTS; nCntParts++)
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
	for (int nCntParts = 0; nCntParts < MAX_ENEMY_PARTS; nCntParts++)
	{// �p�[�c�������[�v
	 // �ʒu�������t���[�����Ŋ������l�����Z���Ă���
		m_PartsDefaultpos[nCntParts].x += m_Motionpos[nCntParts].x / m_nFrame;		// �ʒu�̍������t���[�����Ŋ������l�����Z���Ă���
		m_PartsDefaultpos[nCntParts].y += m_Motionpos[nCntParts].y / m_nFrame;		// �ʒu�̍������t���[�����Ŋ������l�����Z���Ă���
		m_PartsDefaultpos[nCntParts].z += m_Motionpos[nCntParts].z / m_nFrame;		// �ʒu�̍������t���[�����Ŋ������l�����Z���Ă���
		//��]�l�̑��
		m_apModel[nCntParts]->SetPos(m_PartsDefaultpos[nCntParts]);


		// ��]�������t���[�����Ŋ������l�����Z���Ă���
		m_PartsDefaultrot[nCntParts].x += m_Motionrot[nCntParts].x / m_nFrame;		// ��]�̍������t���[�����Ŋ������l�����Z���Ă���
		m_PartsDefaultrot[nCntParts].y += m_Motionrot[nCntParts].y / m_nFrame;		// ��]�̍������t���[�����Ŋ������l�����Z���Ă���
		m_PartsDefaultrot[nCntParts].z += m_Motionrot[nCntParts].z / m_nFrame;		// ��]�̍������t���[�����Ŋ������l�����Z���Ă���
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
// �֐����F�G�̃��[�V�����X�e�[�g�̕ύX
// �֐��̊T�v�F�G�̏�ԑJ��
//=============================================================================
void CEnemy::EnemyMotionState(bool *bAction)
{
	if (bAction[ENEMYBOOLTYPE_LANDING] == true)
	{// �_���[�W���n
		//m_Motionstate = MOTION_LANDING; // ���n���[�V�����ɐݒ�
		m_Motionstate = MOTION_MOVE; // ���n���[�V�����ɐݒ�
	}

	else if (bAction[ENEMYBOOLTYPE_JUMP] == true)
	{// �G���W�����v���Ȃ�
		//m_Motionstate = MOTION_JUMP; // �W�����v���[�V�����ɐݒ�
		m_Motionstate = MOTION_MOVE; // �W�����v���[�V�����ɐݒ�
	}
	else if (m_move.x > ENEMY_WALK_DEFAULT ||
		m_move.x < -ENEMY_WALK_DEFAULT ||
		m_move.z >  ENEMY_WALK_DEFAULT ||
		m_move.z < -ENEMY_WALK_DEFAULT)
	{// �G�������Ă���Ƃ�
		m_Motionstate = MOTION_MOVE; // �ړ���Ԃɂ���
	}
	else
	{// �G�������ĂȂ��Ƃ�
		m_Motionstate = MOTION_NEUTRAL; // �j���[�g������Ԃɂ���
	}
}


//=============================================================================
// �֐����F�p�x�̏C��
// �֐��̊T�v�F�傫����΁A�����A��������΁A����
//=============================================================================
void CEnemy::EnemyRotFixes(D3DXVECTOR3 *rot)
{
	// X���̏C��
	if (rot->x > D3DX_PI)
	{// +3.14���A�����Ă��܂�����
		rot->x -= D3DX_PI * 2.0f;
	}
	else if (rot->x < -D3DX_PI)
	{// -3.14���A���������
		rot->x += D3DX_PI * 2.0f;
	}
	// Y���̏C��
	if (rot->y > D3DX_PI)
	{// +3.14���A�����Ă��܂�����
		rot->y -= D3DX_PI * 2.0f;
	}
	else if (rot->y < -D3DX_PI)
	{// -3.14���A���������
		rot->y += D3DX_PI * 2.0f;
	}
	// Z���̏C��
	if (rot->z > D3DX_PI)
	{// +3.14���A�����Ă��܂�����
		rot->z -= D3DX_PI * 2.0f;
	}
	else if (rot->z < -D3DX_PI)
	{// -3.14���A���������
		rot->z += D3DX_PI * 2.0f;
	}
}
//=============================================================================
// �֐����F�p�x�̏C��
// �֐��̊T�v�F�傫����΁A�����A��������΁A����
//=============================================================================
void CEnemy::EnemyRotFixes(float *rot)
{
	if (*rot > D3DX_PI)
	{// +3.14���A�����Ă��܂�����
		*rot -= D3DX_PI * 2.0f;
	}
	else if (*rot < -D3DX_PI)
	{// -3.14���A���������
		*rot += D3DX_PI * 2.0f;
	}

}

//=============================================================================
// �֐����F�v���C���[�̒T��
// �֐��̊T�v�F�v���C���[�����a�ɓ����Ă�����true��Ԃ�
//=============================================================================
bool CEnemy::FindPlayer(D3DXVECTOR3 *pos, float fRange)
{
	bool bfind = false;

	float fLength = powf((pos->x - m_pos.x)*(pos->x - m_pos.x) + (pos->z - m_pos.z)*(pos->z - m_pos.z), 0.5f);	//�v���C���[�Ƃ̋���
	float fFind = powf(fRange, 2.0f);	//���a
	//CDebugProc::Print("fFind:%.1f\n", fFind);
	//CDebugProc::Print("fLength:%.1f\n", fLength);

	if (fLength < fFind)
	{//�Ώۂ̒��_���͈͓���������
		bfind = true;
		//CDebugProc::Print("�������ɂ݂������I\n");
	}
	else
	{
		bfind = false;
	}


	return bfind;
}


//=============================================================================
// �֐����F�G�Ƃ̓����蔻��
// �֐��̊T�v�F�v���C���[�����a�ɓ����Ă�����true��Ԃ�
//=============================================================================
bool CEnemy::CollisionEnemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *move, D3DXVECTOR3 *rot)
{
	bool bCol = false;

	float fLength = powf((pos->x - m_pos.x)*(pos->x - m_pos.x) + (pos->z - m_pos.z)*(pos->z - m_pos.z), 0.5f);	//�v���C���[�Ƃ̋���
	float fRadius = powf(30.0f, 1.0f);	//���a
	//CDebugProc::Print("�����蔻��̔��a:%.1f\n", fRadius);
	//CDebugProc::Print("�v���C���[�Ƃ̋���:%.1f\n", fLength);

	if (fLength < fRadius && pos->y <= m_pos.y + m_fHeight && pos->y >= m_pos.y)
	{//�Ώۂ̒��_���͈͓���������
		bCol = true;
		float fAttackAngle = atan2f(pos->x - m_pos.x,
			pos->z - m_pos.z);// ���������p�x���v�Z
		move->x = sinf((D3DX_PI *  fAttackAngle)) * 25.0f;
		move->y = 20.0f;
		move->z = cosf((D3DX_PI *  fAttackAngle)) * 25.0f;
	}
	else
	{
		bCol = false;

	}
	return bCol;
}


//=============================================================================
// �֐����F�ʒu���̎擾
// �֐��̊T�v�F�v���C���[�̈ʒu����Ԃ�
//=============================================================================
D3DXVECTOR3 CEnemy::GetPos(void)
{
	return m_pos;
}
//=============================================================================
// �֐����F�p�x���̎擾
// �֐��̊T�v�F�G�̊p�x����Ԃ�
//=============================================================================
D3DXVECTOR3 CEnemy::GetRot(void)
{
	return m_rot;
}

