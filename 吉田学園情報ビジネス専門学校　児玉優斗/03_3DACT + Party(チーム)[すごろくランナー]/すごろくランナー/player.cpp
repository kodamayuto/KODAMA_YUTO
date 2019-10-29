//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "wall.h"
#include "billboard.h"
#include "shadow.h"
#include "effect.h"
#include "particle.h"
#include "obstacle.h"
#include "course.h"
#include "masu.h"
#include "timer.h"
#include "game.h"
#include "orbit.h"
#include "fade.h"
#include "rank.h"
#include "turnNum.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_FILENAME   "MODEL_FILENAME"
#define CHARACTERSET     "CHARACTERSET"
#define MOVE             "MOVE"
#define JUMP             "JUMP"
#define INDEX            "INDEX"
#define PARENT           "PARENT"
#define POS              "POS"
#define ROT              "ROT"
#define PARTSSET         "PARTSSET"
#define END_PARTSSET     "END_PARTSSET"
#define END_CHARACTERSET "END_CHARACTERSET"
#define MOTIONSET        "MOTIONSET"
#define LOOP             "LOOP"
#define NUM_KEY          "NUM_KEY"
#define KEYSET           "KEYSET"
#define FRAME            "FRAME"
#define KEY              "KEY"
#define END_KEY          "END_KEY"
#define END_KEYSET       "END_KEYSET"
#define END_MOTIONSET    "END_MOTIONSET"

#define PLAYER_INERTIA	(0.123f)			// ����
#define GRAVITY_POWER	(-0.4f)				// �d��
#define MOVE_NORMAL		(0.5f)				// �ړ�
#define JUMP_NORMAL		(8.0f)				// �W�����v��
#define JUMP_UP			(9.0f)				// �W�����v��UP
#define JUMP_DOWN		(7.5f)				// �W�����v��DOWN
#define MOVE_UP			(0.8f)				// �ړ�UP
#define MOVE_DOWN		(0.3f)				// �ړ�DOWN


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void PlayerMove(int nIdxPlayer);               // ����ł���v���C���[�̈ړ�����
void PlayerTransition(int nIdxPlayer);         // ����ł���v���C���[�̑J�ڏ���
void PlayerImpossible(int nIdxPlayer);         // ����ł��Ȃ��v���C���[�̏���
void PlayerMotion(int nIdxPlayer);             // ���[�V��������
void PlayerMotionBlend(int nIdxPlayer);        // ���[�V�����u�����h����
void PlayerMotionAdvance(int nIdxPlayer);      // ���[�V�����i�s����
void SwitchKey(int nIdxPlayer);                // �L�[�t���[���̐؂�ւ�����
void SwitchMotion(int nIdxPlayer);             // ���[�V�����؂�ւ�����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Player  g_Player[MAX_PLAYER];                 // �v���C���[���
int     g_PlayerPossible;                     // ���ݑ���ł���v���[���[�̔ԍ�

bool g_bPlayerMoveFlag = false;			// �v���C���[�̑���t���O
int  g_ChangeTimer;                     // �p�[�e�B�N�����ڂ����Ԃ𐔂���^�C�}�[
//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	FILE  *pFile;           // �e�L�X�g�t�@�C���ւ̃|�C���^
	char  str0[128];        // ����Ȃ�����
	char  xFileName[64];    // x�t�@�C���̖��O
	D3DXVECTOR3 OffsetPos;  // �e���f������̋���
	D3DXVECTOR3 OffsetRot;  // �e���f������̌���
	float fJump;            // �W�����v��
	float fMovement;        // �ړ���
	int   nIdxParent;       // �e���f��
	int   nCntModel = 0;    // ���f����ǂݍ��񂾐��𐔂���ϐ�
	int   nCntParts = 0;    // ���f���̃p�[�c����ǂݍ��񂾉񐔂𐔂���ϐ�
	int   nCntPlayer = 0;   // �v���C���[�̐�
	int   nCntMotion = 0;   // ���[�V�����̔ԍ�
	int   nCntKey = 0;      // �L�[�t���[���̔ԍ��𐔂���ϐ�
	int   nPlaybackKey;     // �t���[����
	int   nCntKeyModel = 0; // ���f���̐����̃L�[�t���[���𐔂���ϐ�
	int   bLoop;            // ���[�V���������[�v���邩���Ȃ���
	int   nNumKey = 0;      // �L�[�t���[���̐�
	D3DXVECTOR3 posAdd;     // ��̈ʒu�ɉ�����l
	D3DXVECTOR3 DestAngle;  // �ړI�̌���

	// �t�@�C���I�[�v��
	pFile = fopen("data/player_00.txt", "r");

	if (pFile != NULL)
	{// �t�@�C�����J����
		while (fscanf(pFile, "%s", &str0[0]) != EOF)
		{// �e�L�X�g�t�@�C���̖��[�܂ŕ���������s���󔒂�����܂œǂݎ��
			if (strcmp(&str0[0], MODEL_FILENAME) == 0)
			{// x�t�@�C���̊g���q��������Ă�����
				if (fscanf(pFile, "%s %s", &str0[0], &xFileName[0]) == 2)
				{// ���f���̃t�@�C������ǂݎ������
				 // x�t�@�C���̓ǂݍ���
					D3DXLoadMeshFromX(&xFileName[0],
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_Player[nCntPlayer].aModel[nCntModel].pBuffMat,
						NULL,
						&g_Player[nCntPlayer].aModel[nCntModel].nNumMat,
						&g_Player[nCntPlayer].aModel[nCntModel].pMesh);

					// �}�e���A����񂩂�e�N�X�`���������o��
					D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_Player[nCntPlayer].aModel[nCntModel].pBuffMat->GetBufferPointer();
					D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_Player[nCntPlayer].aModel[nCntModel].nNumMat];
					g_Player[nCntPlayer].aModel[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[g_Player[nCntPlayer].aModel[nCntModel].nNumMat];

					for (DWORD nCntMat = 0; nCntMat < g_Player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
					{// ���_���̐������J��Ԃ� 
					 // �}�e���A������ǂݍ���
						pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

						// ����������������
						pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

						// �e�N�X�`������������
						g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat] = NULL;

						// �e�N�X�`���̏���ǂݍ���
						if (pMat[nCntMat].pTextureFilename != NULL &&
							lstrlen(pMat[nCntMat].pTextureFilename) > 0)
						{// �e�N�X�`���̃t�@�C����������
							D3DXCreateTextureFromFile(pDevice,
								pMat[nCntMat].pTextureFilename,
								&g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]);
						}

					}
				}
				nCntModel++;  // ��ނ��ς��̂Ői�߂Ă���
			}
			if (strcmp(&str0[0], CHARACTERSET) == 0)
			{// �L�����N�^�[��񂪏�����Ă�����
				while (strcmp(&str0[0], END_CHARACTERSET) != 0)
				{// �L�����N�^�[��񂪏I���܂œǂݎ��
					if (strcmp(&str0[0], MOVE) == 0)
					{// �ړ��͂�������Ă�����
						if (fscanf(pFile, "%s %f", &str0[0], &fMovement) == 2)
						{// �ړ��͂�ǂݎ������
							g_Player[nCntPlayer].fMovement = fMovement;
						}
					}
					if (strcmp(&str0[0], JUMP) == 0)
					{// �W�����v�͂�������Ă�����
						if (fscanf(pFile, "%s %f", &str0[0], &fJump) == 2)
						{// �W�����v�͂�ǂݎ������
							g_Player[nCntPlayer].fJumpPower = fJump;
						}
					}

					if (strcmp(&str0[0], PARTSSET) == 0)
					{// ���f���̃p�[�c��񂪏�����Ă�����
						int nCntSet = 0;
						int nCntPartsNum = 0;
						while (strcmp(&str0[0], END_PARTSSET) != 0)
						{// ���f���̃p�[�c��񂪏I���܂œǂݎ��
							if (strcmp(&str0[0], INDEX) == 0)
							{// �p�[�c�ԍ���ǂݎ��
								fscanf(pFile, "%s %d", &str0[0], &nCntPartsNum);
							}
							else if (strcmp(&str0[0], PARENT) == 0)
							{// �e���f���̔ԍ���ǂݎ��
								if (fscanf(pFile, "%s %d", &str0[0], &nIdxParent) == 2)
								{// �e���f���̔ԍ���ǂݎ��
									g_Player[nCntPlayer].aModel[nCntPartsNum].nIdxModelParent = nIdxParent;
								}
							}
							else if (strcmp(&str0[0], POS) == 0)
							{// �e���f������̋�����ǂݎ��
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetPos.x, &OffsetPos.y, &OffsetPos.z) == 4)
								{// ���W����ǂݎ������
									g_Player[nCntPlayer].aModel[nCntPartsNum].pos = OffsetPos;
								}
							}
							else if (strcmp(&str0[0], ROT) == 0)
							{// �e���f������̌�����ǂݎ��
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetRot.x, &OffsetRot.y, &OffsetRot.z) == 4)
								{// ��������ǂݎ������
									g_Player[nCntPlayer].aModel[nCntPartsNum].rot = OffsetRot;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
							nCntSet++;                     // �Z�b�g�����񐔂𑝂₷
						}
					}
					fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
				}
			}
			if (strcmp(&str0[0], MOTIONSET) == 0)
			{// ���[�V������񂪏�����Ă�����
				nCntKey = 0;    // �L�[�t���[���̃|�C���^���W��߂�
				while (strcmp(&str0[0], END_MOTIONSET) != 0)
				{// ���[�V������񂪏I���܂œǂݎ��
					if (strcmp(&str0[0], LOOP) == 0)
					{// ���[�v���邩���Ȃ�����ǂݎ��
						if (fscanf(pFile, "%s %d", &str0[0], &bLoop) == 2)
						{// ���[�v���邩���Ȃ�����ǂݎ�ꂽ
							if (bLoop == 1)
							{
								g_Player[nCntPlayer].aMotion[nCntMotion].bLoop = true;
							}
							else
							{
								g_Player[nCntPlayer].aMotion[nCntMotion].bLoop = false;
							}
						}
					}
					else if (strcmp(&str0[0], NUM_KEY) == 0)
					{// �L�[�t���[������ǂݎ��
						if (fscanf(pFile, "%s %d", &str0[0], &nNumKey) == 2)
						{// �L�[�t���[������ǂݎ�ꂽ
							g_Player[nCntPlayer].aMotion[nCntMotion].nNumKey = nNumKey;
						}
					}
					else if (strcmp(&str0[0], KEYSET) == 0)
					{// �L�[�t���[����񂪏�����Ă�����
						nCntKeyModel = 0;
						while (strcmp(&str0[0], FRAME) != 0)
						{// �L�[�t���[������񂪏I���܂œǂݎ��
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
						}
						if (fscanf(pFile, "%s %d", &str0[0], &nPlaybackKey) == 2)
						{// �L�[�t���[������ǂݎ�ꂽ
							g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].nPlayBackKey = nPlaybackKey;
						}
						while (strcmp(&str0[0], END_KEYSET) != 0)
						{// �L�[�t���[����񂪏I���܂œǂݎ��
							if (strcmp(&str0[0], KEY) == 0)
							{// �L�[�t���[���̖ړI�̈ʒu��񂪏�����Ă�����
								while (strcmp(&str0[0], END_KEY) != 0)
								{// �L�[�t���[���̖ړI�̈ʒu��񂪏I���܂œǂݎ��
									if (strcmp(&str0[0], POS) == 0)
									{// ���W����ǂݎ��
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &posAdd.x, &posAdd.y, &posAdd.z) == 4)
										{// ���W����ǂݎ������
											g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].posAdd[nCntKeyModel] = posAdd;
										}
									}
									else if (strcmp(&str0[0], ROT) == 0)
									{// ��������ǂݎ��
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &DestAngle.x, &DestAngle.y, &DestAngle.z) == 4)
										{// ��������ǂݎ������
											g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].DestAngle[nCntKeyModel] = DestAngle;
										}
									}
									fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
								}
								if (nCntKeyModel < MAX_MODEL - 1)
								{// ���f�����Ƃ̃L�[�t���[�����p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
									nCntKeyModel++;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
						}
						if (nCntKey < MAX_MODEL - 1)
						{// �L�[�t���[�����p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
							nCntKey++;
						}
					}
					fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
				}
				if (nCntMotion < MAX_MOTION - 1)
				{// ���[�V�������p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
					nCntMotion++;   // ���[�V�����ԍ������炷
				}
			}
		}
	}

	// �t�@�C������đ��̃v���O�������炢�����悤�ɂ���
	fclose(pFile);

	nCntModel = 0;    // ���f����ǂݍ��񂾐��𐔂���ϐ�
	nCntParts = 0;    // ���f���̃p�[�c����ǂݍ��񂾉񐔂𐔂���ϐ�
	nCntMotion = 0;   // ���[�V�����̔ԍ�
	nCntKey = 0;      // �L�[�t���[���̔ԍ��𐔂���ϐ�
	nCntKeyModel = 0; // ���f���̐����̃L�[�t���[���𐔂���ϐ�
	nNumKey = 0;      // �L�[�t���[���̐�

	if (nCntPlayer < MAX_PLAYER)
	{// �v���C���[�̍ő�l�����|�C���^���i��łȂ�
		nCntPlayer++;    // �v���C���[���̃|�C���^��i�߂�
	}

	// �t�@�C���I�[�v��
	pFile = fopen("data/player_01.txt", "r");

	if (pFile != NULL)
	{// �t�@�C�����J����
		while (fscanf(pFile, "%s", &str0[0]) != EOF)
		{// �e�L�X�g�t�@�C���̖��[�܂ŕ���������s���󔒂�����܂œǂݎ��
			if (strcmp(&str0[0], MODEL_FILENAME) == 0)
			{// x�t�@�C���̊g���q��������Ă�����
				if (fscanf(pFile, "%s %s", &str0[0], &xFileName[0]) == 2)
				{// ���f���̃t�@�C������ǂݎ������
				 // x�t�@�C���̓ǂݍ���
					D3DXLoadMeshFromX(&xFileName[0],
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_Player[nCntPlayer].aModel[nCntModel].pBuffMat,
						NULL,
						&g_Player[nCntPlayer].aModel[nCntModel].nNumMat,
						&g_Player[nCntPlayer].aModel[nCntModel].pMesh);

					// �}�e���A����񂩂�e�N�X�`���������o��
					D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_Player[nCntPlayer].aModel[nCntModel].pBuffMat->GetBufferPointer();
					D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_Player[nCntPlayer].aModel[nCntModel].nNumMat];
					g_Player[nCntPlayer].aModel[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[g_Player[nCntPlayer].aModel[nCntModel].nNumMat];

					for (DWORD nCntMat = 0; nCntMat < g_Player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
					{// ���_���̐������J��Ԃ� 
					 // �}�e���A������ǂݍ���
						pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

						// ����������������
						pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

						// �e�N�X�`������������
						g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat] = NULL;

						// �e�N�X�`���̏���ǂݍ���
						if (pMat[nCntMat].pTextureFilename != NULL &&
							lstrlen(pMat[nCntMat].pTextureFilename) > 0)
						{// �e�N�X�`���̃t�@�C����������
							D3DXCreateTextureFromFile(pDevice,
								pMat[nCntMat].pTextureFilename,
								&g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]);
						}

					}
				}
				nCntModel++;  // ��ނ��ς��̂Ői�߂Ă���
			}
			if (strcmp(&str0[0], CHARACTERSET) == 0)
			{// �L�����N�^�[��񂪏�����Ă�����
				while (strcmp(&str0[0], END_CHARACTERSET) != 0)
				{// �L�����N�^�[��񂪏I���܂œǂݎ��
					if (strcmp(&str0[0], MOVE) == 0)
					{// �ړ��͂�������Ă�����
						if (fscanf(pFile, "%s %f", &str0[0], &fMovement) == 2)
						{// �ړ��͂�ǂݎ������
							g_Player[nCntPlayer].fMovement = fMovement;
						}
					}
					if (strcmp(&str0[0], JUMP) == 0)
					{// �W�����v�͂�������Ă�����
						if (fscanf(pFile, "%s %f", &str0[0], &fJump) == 2)
						{// �W�����v�͂�ǂݎ������
							g_Player[nCntPlayer].fJumpPower = fJump;
						}
					}

					if (strcmp(&str0[0], PARTSSET) == 0)
					{// ���f���̃p�[�c��񂪏�����Ă�����
						int nCntSet = 0;
						int nCntPartsNum = 0;
						while (strcmp(&str0[0], END_PARTSSET) != 0)
						{// ���f���̃p�[�c��񂪏I���܂œǂݎ��
							if (strcmp(&str0[0], INDEX) == 0)
							{// �p�[�c�ԍ���ǂݎ��
								fscanf(pFile, "%s %d", &str0[0], &nCntPartsNum);
							}
							else if (strcmp(&str0[0], PARENT) == 0)
							{// �e���f���̔ԍ���ǂݎ��
								if (fscanf(pFile, "%s %d", &str0[0], &nIdxParent) == 2)
								{// �e���f���̔ԍ���ǂݎ��
									g_Player[nCntPlayer].aModel[nCntPartsNum].nIdxModelParent = nIdxParent;
								}
							}
							else if (strcmp(&str0[0], POS) == 0)
							{// �e���f������̋�����ǂݎ��
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetPos.x, &OffsetPos.y, &OffsetPos.z) == 4)
								{// ���W����ǂݎ������
									g_Player[nCntPlayer].aModel[nCntPartsNum].pos = OffsetPos;
								}
							}
							else if (strcmp(&str0[0], ROT) == 0)
							{// �e���f������̌�����ǂݎ��
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetRot.x, &OffsetRot.y, &OffsetRot.z) == 4)
								{// ��������ǂݎ������
									g_Player[nCntPlayer].aModel[nCntPartsNum].rot = OffsetRot;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
							nCntSet++;                     // �Z�b�g�����񐔂𑝂₷
						}
					}
					fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
				}
			}
			if (strcmp(&str0[0], MOTIONSET) == 0)
			{// ���[�V������񂪏�����Ă�����
				nCntKey = 0;   // �L�[�t���[���̃|�C���^���W��߂�
				while (strcmp(&str0[0], END_MOTIONSET) != 0)
				{// ���[�V������񂪏I���܂œǂݎ��
					if (strcmp(&str0[0], LOOP) == 0)
					{// ���[�v���邩���Ȃ�����ǂݎ��
						if (fscanf(pFile, "%s %d", &str0[0], &bLoop) == 2)
						{// ���[�v���邩���Ȃ�����ǂݎ�ꂽ
							if (bLoop == 1)
							{
								g_Player[nCntPlayer].aMotion[nCntMotion].bLoop = true;
							}
							else
							{
								g_Player[nCntPlayer].aMotion[nCntMotion].bLoop = false;
							}
						}
					}
					else if (strcmp(&str0[0], NUM_KEY) == 0)
					{// �L�[�t���[������ǂݎ��
						if (fscanf(pFile, "%s %d", &str0[0], &nNumKey) == 2)
						{// �L�[�t���[������ǂݎ�ꂽ
							g_Player[nCntPlayer].aMotion[nCntMotion].nNumKey = nNumKey;
						}
					}
					else if (strcmp(&str0[0], KEYSET) == 0)
					{// �L�[�t���[����񂪏�����Ă�����
						nCntKeyModel = 0;
						while (strcmp(&str0[0], FRAME) != 0)
						{// �L�[�t���[������񂪏I���܂œǂݎ��
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
						}
						if (fscanf(pFile, "%s %d", &str0[0], &nPlaybackKey) == 2)
						{// �L�[�t���[������ǂݎ�ꂽ
							g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].nPlayBackKey = nPlaybackKey;
						}
						while (strcmp(&str0[0], END_KEYSET) != 0)
						{// �L�[�t���[����񂪏I���܂œǂݎ��
							if (strcmp(&str0[0], KEY) == 0)
							{// �L�[�t���[���̖ړI�̈ʒu��񂪏�����Ă�����
								while (strcmp(&str0[0], END_KEY) != 0)
								{// �L�[�t���[���̖ړI�̈ʒu��񂪏I���܂œǂݎ��
									if (strcmp(&str0[0], POS) == 0)
									{// ���W����ǂݎ��
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &posAdd.x, &posAdd.y, &posAdd.z) == 4)
										{// ���W����ǂݎ������
											g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].posAdd[nCntKeyModel] = posAdd;
										}
									}
									else if (strcmp(&str0[0], ROT) == 0)
									{// ��������ǂݎ��
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &DestAngle.x, &DestAngle.y, &DestAngle.z) == 4)
										{// ��������ǂݎ������
											g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].DestAngle[nCntKeyModel] = DestAngle;
										}
									}
									fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
								}
								if (nCntKeyModel < MAX_MODEL - 1)
								{// ���f�����Ƃ̃L�[�t���[�����p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
									nCntKeyModel++;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
						}
						if (nCntKey < MAX_MODEL)
						{// �L�[�t���[�����p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
							nCntKey++;
						}
					}
					fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
				}
				if (nCntMotion < MAX_MOTION)
				{// ���[�V�������p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
					nCntMotion++;   // ���[�V�����ԍ������炷
				}
			}
		}
	}

	// �t�@�C������đ��̃v���O�������炢�����悤�ɂ���
	fclose(pFile);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// �v���C���[�̐l�������J��Ԃ�
		g_Player[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);           // �ړ��ʂ�������
		g_Player[nCntPlayer].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);            // ���݂̌�����������
		g_Player[nCntPlayer].DestAngle = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);      // �ړI�̌�����������
		g_Player[nCntPlayer].DiffAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // ������������
		g_Player[nCntPlayer].state = PLAYERSTATE_NORMAL;                     // �ʏ�̏�Ԃ�
		g_Player[nCntPlayer].radius = D3DXVECTOR3(11.5f, 30.0f, 11.5f);      // �����蔻������͈͂�������
		g_Player[nCntPlayer].ShadowCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f); // �e�̐F��ݒ�
		g_Player[nCntPlayer].ShadowWidth = 15;                               // �e�̕���ݒ�
		g_Player[nCntPlayer].ShadowDepth = 15;                               // �e�̉��s��ݒ�
		g_Player[nCntPlayer].pMasu = NULL;                                   // �}�X�̃|�C���^����ɂ��Ă���
		g_Player[nCntPlayer].bJump = false;                                  // �W�����v���Ă��Ȃ���Ԃ�
		g_Player[nCntPlayer].bGrab = false;                                  // �c�^�ɂ��܂��Ă��Ȃ����
		g_Player[nCntPlayer].bDisp = true;                                   // �`�悷���Ԃɂ���
		g_Player[nCntPlayer].mState = MOTIONSTATE_NORMAL;                    // ���[�V�����̏�Ԃ͒ʏ�̏�Ԃ�

		// �e�̔ԍ���ݒ�
		g_Player[nCntPlayer].nIdxShadow = SetShadow(D3DXVECTOR3(g_Player[nCntPlayer].pos.x, 1.0f, g_Player[nCntPlayer].pos.z), g_Player[nCntPlayer].rot, g_Player[nCntPlayer].ShadowCol, g_Player[nCntPlayer].ShadowWidth, g_Player[nCntPlayer].ShadowDepth);

		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// ���f���̃p�[�c�����J��Ԃ�
			g_Player[nCntPlayer].aModel[nCntModel].posStd = g_Player[nCntPlayer].aModel[nCntModel].pos;
			g_Player[nCntPlayer].aModel[nCntModel].rot = g_Player[nCntPlayer].aMotion[nCntModel].Key[g_Player[nCntPlayer].state].DestAngle[nCntModel];
		}
	}

	g_Player[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ���݂̈ʒu��������
	g_Player[0].posold = g_Player[0].pos;  // ���݂̈ʒu��������

	g_Player[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ���݂̈ʒu��������
	g_Player[1].posold = g_Player[1].pos;  // ���݂̈ʒu��������

	if (GetMode() == MODE_CLEAR || GetMode() == MODE_OVER)
	{// ���ʉ�ʂ�������
		g_Player[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ���݂̌�����������
		g_Player[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ���݂̌�����������
	}

	g_PlayerPossible = 0;   // �ԍ���0��
	g_ChangeTimer = 0;      // �^�C�}�[��0��
	g_bPlayerMoveFlag = false; // �������Ԃł͂Ȃ�����
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// �v���C���[�̐������J��Ԃ�
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// ���f���̃p�[�c�������J��Ԃ�
		 // ���b�V���̔j��
			if (g_Player[nCntPlayer].aModel[nCntModel].pMesh != NULL)
			{
				g_Player[nCntPlayer].aModel[nCntModel].pMesh->Release();
				g_Player[nCntPlayer].aModel[nCntModel].pMesh = NULL;
			}

			// �}�e���A���̔j��
			if (g_Player[nCntPlayer].aModel[nCntModel].pBuffMat != NULL)
			{
				g_Player[nCntPlayer].aModel[nCntModel].pBuffMat->Release();
				g_Player[nCntPlayer].aModel[nCntModel].pBuffMat = NULL;
			}

			// �e�N�X�`���̔j��
			for (DWORD nCntMat = 0; nCntMat < g_Player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
			{
				if (g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat] != NULL)
				{
					g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]->Release();
					g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat] = NULL;
				}
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	int nMasu;

	MODE g_Mode = GetMode();

	if (g_Mode == MODE_GAME)
	{

		if (GetTimer() != -1)
		{//�^�C�}�[�������Ă����
			if (g_bPlayerMoveFlag == true )
			{//�v���C���[���������Ԃł����

				if (g_Player[g_PlayerPossible].bDisp == true)
				{
					if (g_Player[g_PlayerPossible].state != PLAYERSTATE_PANCH
						&& g_Player[g_PlayerPossible].state != PLAYERSTATE_LANDING)
					{// �������Ԃł���
					 // �ړ�����
						PlayerMove(g_PlayerPossible);

						// ����ł��Ȃ��v���C���[�̏���
						PlayerImpossible((g_PlayerPossible + 1) % 2);

					}
				}
			}
		}
		else
		{//�����Ă��Ȃ����
			if (g_Player[g_PlayerPossible].state != PLAYERSTATE_NORMAL)
			{
				g_Player[g_PlayerPossible].state = PLAYERSTATE_NORMAL;   // �ʏ��Ԃ�
																		 // ���[�V�����؂�ւ�����
				SwitchMotion(g_PlayerPossible);
			}
			g_Player[g_PlayerPossible].move.y += GRAVITY_POWER;
			g_Player[g_PlayerPossible].pos.y += g_Player[g_PlayerPossible].move.y;

			if (g_Player[g_PlayerPossible].pos.y < 0.0f)
			{// ���n����
				g_Player[g_PlayerPossible].pos.y = 0.0f;
				g_Player[g_PlayerPossible].move.y = 0.0f;
				if (g_Player[g_PlayerPossible].bJump == true)
				{// �W�����v���Ă���
					if (g_Player[g_PlayerPossible].move.x <= 0.5f && g_Player[g_PlayerPossible].move.x >= -0.5f &&
						g_Player[g_PlayerPossible].move.z <= 0.5f && g_Player[g_PlayerPossible].move.z >= -0.5f)
					{// �ړ����Ă��Ȃ�������
						g_Player[g_PlayerPossible].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																				 // ���[�V�����؂�ւ�����
						SwitchMotion(g_PlayerPossible);
					}
				}
				else if (g_Player[g_PlayerPossible].state == PLAYERSTATE_DAMAGE)
				{// �_���[�W��Ԃ�����
					g_Player[g_PlayerPossible].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																			 // ���[�V�����؂�ւ�����
					SwitchMotion(g_PlayerPossible);
				}
				else if (g_Player[g_PlayerPossible].state == PLAYERSTATE_KICK)
				{// �L�b�N��Ԃ�����
					if (g_Player[g_PlayerPossible].move.x <= 0.5f && g_Player[g_PlayerPossible].move.x >= -0.5f &&
						g_Player[g_PlayerPossible].move.z <= 0.5f && g_Player[g_PlayerPossible].move.z >= -0.5f)
					{// �ړ����Ă��Ȃ�������
						g_Player[g_PlayerPossible].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																				 // ���[�V�����؂�ւ�����
						SwitchMotion(g_PlayerPossible);
					}
					else if (g_Player[g_PlayerPossible].move.x > 0.5f || g_Player[g_PlayerPossible].move.x < -0.5f ||
						g_Player[g_PlayerPossible].move.z > 0.5f || g_Player[g_PlayerPossible].move.z < -0.5f)
					{// �ړ����Ă�����
						if (g_Player[g_PlayerPossible].state != PLAYERSTATE_MOVE)
						{// �ړ����Ă����Ԃ���Ȃ�������
							g_Player[g_PlayerPossible].state = PLAYERSTATE_MOVE;   // �ړ����Ă����Ԃ�
																				   // ���[�V�����؂�ւ�����
							SwitchMotion(g_PlayerPossible);
						}
					}
				}
				g_Player[g_PlayerPossible].bJump = false;  // �W�����v���Ă��Ȃ������
			}
		}

		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{// �v���C���[�̐������J��Ԃ�
			if (g_Player[nCntPlayer].bDisp == true)
			{// �`�悷���ԂȂ��
				if (g_Player[nCntPlayer].mState == MOTIONSTATE_NORMAL)
				{// �ʏ�̃��[�V������Ԃ�������
				 // ���[�V��������
					PlayerMotion(nCntPlayer);
				}
				else if (g_Player[nCntPlayer].mState == MOTIONSTATE_SWITCH)
				{// ���[�V�����؂�ւ���Ԃ�������
				 // ���[�V�����u�����h����
					PlayerMotionBlend(nCntPlayer);
				}

				if (g_Player[nCntPlayer].mState == MOTIONSTATE_NORMAL)
				{// �L�[�t���[����i�߂��Ԃ�������
				 // ���[�V�����i�s����
					PlayerMotionAdvance(nCntPlayer);
				}

				SetOrbit(D3DXVECTOR3(g_Player[nCntPlayer].aModel[0].mtxWorld._41, g_Player[nCntPlayer].aModel[0].mtxWorld._42 - 7.0f, g_Player[nCntPlayer].aModel[0].mtxWorld._43), D3DXVECTOR3(g_Player[nCntPlayer].aModel[1].mtxWorld._41, g_Player[nCntPlayer].aModel[1].mtxWorld._42 + 10.0f, g_Player[nCntPlayer].aModel[1].mtxWorld._43), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f), nCntPlayer);


				if (g_Player[nCntPlayer].state == PLAYERSTATE_DAMAGE)
				{// �_���[�W��Ԃ�������
					for (int nCntParticle = 0; nCntParticle < 1; nCntParticle++)
					{// ����������p�[�e�B�N���̐������J��Ԃ�
						SetParticle(D3DXVECTOR3(g_Player[nCntPlayer].aModel[0].mtxWorld._41, g_Player[nCntPlayer].aModel[0].mtxWorld._42, g_Player[nCntPlayer].aModel[0].mtxWorld._43), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 100 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 100 * D3DX_PI / 100 - 1.0f) * 1.5f, 0.0f), 8.0f, 60);
					}
				}

				if (CollisionObstacle(&g_Player[nCntPlayer].pos, &g_Player[nCntPlayer].posold, &g_Player[nCntPlayer].move, D3DXVECTOR3(12.0f, 30.0f, 12.0f)) == true)
				{// ��Q���ɓ������Ă���
					if (g_Player[nCntPlayer].state == PLAYERSTATE_KICK || g_Player[nCntPlayer].state == PLAYERSTATE_DAMAGE)
					{// �L�b�N���Ă��邩�_���[�W��Ԃ�������
						g_Player[nCntPlayer].state = PLAYERSTATE_LANDING;   // ���n�̏�Ԃ�
						SwitchMotion(nCntPlayer);
					}
					if (g_Player[nCntPlayer].bJump == true)
					{// �W�����v���Ă���
						if (g_Player[nCntPlayer].move.x <= 0.5f && g_Player[nCntPlayer].move.x >= -0.5f &&
							g_Player[nCntPlayer].move.z <= 0.5f && g_Player[nCntPlayer].move.z >= -0.5f)
						{// �ړ����Ă��Ȃ�������
							if (g_Player[nCntPlayer].state != PLAYERSTATE_LANDING)
							{// �ړ����Ă��Ȃ���Ԃ���Ȃ�������
								g_Player[nCntPlayer].state = PLAYERSTATE_LANDING;   // ���n�̏�Ԃ�
								SwitchMotion(nCntPlayer);
							}
						}
						else if (g_Player[nCntPlayer].move.x > 0.5f || g_Player[nCntPlayer].move.x < -0.5f ||
							g_Player[nCntPlayer].move.z > 0.5f || g_Player[nCntPlayer].move.z < -0.5f)
						{// �ړ����Ă�����
							if (g_Player[nCntPlayer].state != PLAYERSTATE_MOVE)
							{// �ړ����Ă����Ԃ���Ȃ�������
								g_Player[nCntPlayer].state = PLAYERSTATE_MOVE;     // �ړ����Ă����Ԃ�
								SwitchMotion(nCntPlayer);
							}
						}
					}
					g_Player[nCntPlayer].bJump = false;  // �W�����v���Ȃ������
				}

				if (CollisionMasu(&g_Player[nCntPlayer].pos, &g_Player[nCntPlayer].posold, &g_Player[nCntPlayer].move, D3DXVECTOR3(15.0f, 30.0f, 15.0f), &g_Player[nCntPlayer].pMasu) == true)
				{// �}�X�ɓ������Ă���
					if (g_Player[nCntPlayer].state == PLAYERSTATE_KICK || g_Player[nCntPlayer].state == PLAYERSTATE_DAMAGE)
					{// �L�b�N���Ă��邩�_���[�W��Ԃ�������
						g_Player[nCntPlayer].state = PLAYERSTATE_LANDING;   // ���n�̏�Ԃ�
						SwitchMotion(nCntPlayer);
					}
					if (g_Player[nCntPlayer].bJump == true)
					{// �W�����v���Ă���
						if (g_Player[nCntPlayer].move.x <= 0.5f && g_Player[nCntPlayer].move.x >= -0.5f &&
							g_Player[nCntPlayer].move.z <= 0.5f && g_Player[nCntPlayer].move.z >= -0.5f)
						{// �ړ����Ă��Ȃ�������
							if (g_Player[nCntPlayer].state != PLAYERSTATE_LANDING)
							{// �ړ����Ă��Ȃ���Ԃ���Ȃ�������
								g_Player[nCntPlayer].state = PLAYERSTATE_LANDING;   // ���n�̏�Ԃ�
								SwitchMotion(nCntPlayer);
							}
						}
						else if (g_Player[nCntPlayer].move.x > 0.5f || g_Player[nCntPlayer].move.x < -0.5f ||
							g_Player[nCntPlayer].move.z > 0.5f || g_Player[nCntPlayer].move.z < -0.5f)
						{// �ړ����Ă�����
							if (g_Player[nCntPlayer].state != PLAYERSTATE_MOVE)
							{// �ړ����Ă����Ԃ���Ȃ�������
								g_Player[nCntPlayer].state = PLAYERSTATE_MOVE;     // �ړ����Ă����Ԃ�
								SwitchMotion(nCntPlayer);
							}
						}
					}
					g_Player[nCntPlayer].bJump = false;  // �W�����v���Ȃ������

					if (g_Player[nCntPlayer].pMasu->masuType == MASUTYPE_NORMAL)
					{
						g_Player[nCntPlayer].pMasu->bUse = false;

						nMasu = rand() % 4;

						if (nMasu == 0)
						{
							SetMasu(g_Player[nCntPlayer].pMasu->pos, MASUTYPE_JUMP_UP);
							PlaySound(SOUND_LABEL_SE009);							for (int nCntParticle = 0; nCntParticle < 15; nCntParticle++)
							{// ����������p�[�e�B�N���̐������J��Ԃ�
								SetParticle(g_Player[nCntPlayer].pMasu->pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f), 12.0f, 100);
							}

						}
						else if (nMasu == 1)
						{
							SetMasu(g_Player[nCntPlayer].pMasu->pos, MASUTYPE_JUMP_DOWN);

							PlaySound(SOUND_LABEL_SE010);

							for (int nCntParticle = 0; nCntParticle < 15; nCntParticle++)
							{// ����������p�[�e�B�N���̐������J��Ԃ�
								SetParticle(g_Player[nCntPlayer].pMasu->pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f), 12.0f, 100);
							}
						}
						else if (nMasu == 2)
						{
							SetMasu(g_Player[nCntPlayer].pMasu->pos, MASUTYPE_SPEED_DOWN);

							PlaySound(SOUND_LABEL_SE010);

							for (int nCntParticle = 0; nCntParticle < 15; nCntParticle++)
							{// ����������p�[�e�B�N���̐������J��Ԃ�
								SetParticle(g_Player[nCntPlayer].pMasu->pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f), 12.0f, 100);
							}
						}
						else if (nMasu == 3)
						{
							SetMasu(g_Player[nCntPlayer].pMasu->pos, MASUTYPE_SPEED_UP);

							PlaySound(SOUND_LABEL_SE009);

							for (int nCntParticle = 0; nCntParticle < 15; nCntParticle++)
							{// ����������p�[�e�B�N���̐������J��Ԃ�
								SetParticle(g_Player[nCntPlayer].pMasu->pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f), 12.0f, 100);
							}
						}
					}
				}
				else
				{
					if (g_Player[g_PlayerPossible].bGrab == false)
					{// �c�^�ɂ��܂��Ă��Ȃ�
						if (GetKeyboardTrigger(DIK_SPACE) == true || GetJoyPadTrigger(DIJS_BUTTON_2, g_PlayerPossible))
						{// �A�N�V�����{�^���������ꂽ
							if (g_Player[g_PlayerPossible].bJump == true)
							{// �󒆂ɂ���
								g_Player[g_PlayerPossible].state = PLAYERSTATE_KICK;   // �L�b�N��Ԃ�
								PlaySound(SOUND_LABEL_SE013);
																					   // ���[�V�����؂�ւ�����
								SwitchMotion(g_PlayerPossible);
							}
							else
							{
								g_Player[g_PlayerPossible].state = PLAYERSTATE_PANCH;  // �p���`��Ԃ�
								PlaySound(SOUND_LABEL_SE005);
																					   // ���[�V�����؂�ւ�����
								SwitchMotion(g_PlayerPossible);
							}
						}

						if (GetKeyboardTrigger(DIK_SPACE) == true || GetJoyPadTrigger(DIJS_BUTTON_2, g_PlayerPossible ^ 1))
						{// �A�N�V�����{�^���������ꂽ
							if (g_Player[g_PlayerPossible ^ 1].bJump == true)
							{// �󒆂ɂ���
								g_Player[g_PlayerPossible ^ 1].state = PLAYERSTATE_KICK;   // �L�b�N��Ԃ�
																					   // ���[�V�����؂�ւ�����
								SwitchMotion(g_PlayerPossible ^ 1);
							}
							else
							{
								g_Player[g_PlayerPossible ^ 1].state = PLAYERSTATE_PANCH;  // �p���`��Ԃ�
																					   // ���[�V�����؂�ւ�����
								SwitchMotion(g_PlayerPossible ^ 1);
							}
						}

					}
				}

				if (g_Player[nCntPlayer].pMasu != NULL)
				{
					if (g_Player[nCntPlayer].pMasu->masuType == MASUTYPE_GOAL)
					{

						SetGameState(GAMESTATE_CLEAR);
					}
				}
			}
			else
			{// �`�悵�Ȃ���ԂȂ��
				g_ChangeTimer++;
				if (g_ChangeTimer >= 60)
				{// ��b�o��
					g_Player[g_PlayerPossible].bDisp = true;
					//�ʒu����
					//D3DXVECTOR3 NearMasu = PlayerDistance(g_Player[g_PlayerPossible].pos);
					g_Player[g_PlayerPossible].pos = g_Player[g_PlayerPossible].pMasu->pos;
					g_Player[g_PlayerPossible].posold = g_Player[g_PlayerPossible].pMasu->pos;
					g_Player[g_PlayerPossible].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);

					g_Player[g_PlayerPossible].ShadowCol.a = 0.35f;  // �e��������x�o��

																	 // �e�̈ʒu�X�V
					SetPositionShadow(g_Player[g_PlayerPossible].nIdxShadow, D3DXVECTOR3(g_Player[g_PlayerPossible].pos.x, 0.0f, g_Player[g_PlayerPossible].pos.z));
					// �e�̐F�X�V
					SetColShadow(g_Player[g_PlayerPossible].nIdxShadow, g_Player[g_PlayerPossible].ShadowCol);
					// �e�̑傫���X�V
					SetSizeShadow(g_Player[g_PlayerPossible].nIdxShadow, g_Player[g_PlayerPossible].ShadowWidth, g_Player[g_PlayerPossible].ShadowDepth);

					// �O���̈ʒu�C��(1�l��)
					SetPosiotionOrbit(D3DXVECTOR3(g_Player[g_PlayerPossible].aModel[0].mtxWorld._41, g_Player[g_PlayerPossible].aModel[0].mtxWorld._42 - 7.0f, g_Player[g_PlayerPossible].aModel[0].mtxWorld._43), D3DXVECTOR3(g_Player[g_PlayerPossible].aModel[1].mtxWorld._41, g_Player[g_PlayerPossible].aModel[1].mtxWorld._42 + 10.0f, g_Player[g_PlayerPossible].aModel[1].mtxWorld._43), g_PlayerPossible);

					if (GetIdxPlayer() == 1)
					{
						AddTurnNum(1);
					}

					// ���[�V�����؂�ւ�����
					SwitchMotion(g_PlayerPossible);
					g_PlayerPossible = (g_PlayerPossible + 1) % 2;          // ����ł���v���C���[�����ւ���

					SetTurnState(TURNSTATE_DICE);

					g_ChangeTimer = 0;  // �^�C�}�[��߂�

					// �O���̈ʒu�C��(2�l��)
					SetPosiotionOrbit(D3DXVECTOR3(g_Player[g_PlayerPossible].aModel[0].mtxWorld._41, g_Player[g_PlayerPossible].aModel[0].mtxWorld._42 - 7.0f, g_Player[g_PlayerPossible].aModel[0].mtxWorld._43), D3DXVECTOR3(g_Player[g_PlayerPossible].aModel[1].mtxWorld._41, g_Player[g_PlayerPossible].aModel[1].mtxWorld._42 + 10.0f, g_Player[g_PlayerPossible].aModel[1].mtxWorld._43), g_PlayerPossible);

				}
			}
		}

		if (g_Player[g_PlayerPossible].bGrab == false)
		{// �c�^�ɂ��܂��Ă��Ȃ�
		 // �v���C���[�̍U������
			if (g_Player[g_PlayerPossible].state == PLAYERSTATE_PANCH)
			{// �p���`���[�V������������
				g_Player[g_PlayerPossible].move.x = 0.0f;  // �ړ��𖳎�
				g_Player[g_PlayerPossible].move.z = 0.0f;  // �ړ��𖳎�
				if (g_Player[g_PlayerPossible].nKey >= 2)
				{// ���[�V������16�t���[�����Đ��ł���
					CollisionPlayer(0, g_PlayerPossible, (g_PlayerPossible + 1) % 2);
				}
				// �G�t�F�N�g�̐ݒ�
				SetEffect(D3DXVECTOR3(g_Player[g_PlayerPossible].aModel[3].mtxWorld._41, g_Player[g_PlayerPossible].aModel[3].mtxWorld._42, g_Player[g_PlayerPossible].aModel[3].mtxWorld._43), g_Player[g_PlayerPossible].rot, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 15.0f, 100);
			}
			else if (g_Player[g_PlayerPossible].state == PLAYERSTATE_KICK)
			{// �L�b�N���[�V������������
				CollisionPlayer(0, g_PlayerPossible, (g_PlayerPossible + 1) % 2);
				// �G�t�F�N�g�̐ݒ�
				SetEffect(D3DXVECTOR3(g_Player[g_PlayerPossible].aModel[7].mtxWorld._41, g_Player[g_PlayerPossible].aModel[7].mtxWorld._42, g_Player[g_PlayerPossible].aModel[7].mtxWorld._43), g_Player[g_PlayerPossible].rot, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 15.0f, 100);
			}
		}

		if (g_Player[g_PlayerPossible].state != PLAYERSTATE_GRABJUMP && g_Player[g_PlayerPossible].bGrab == false)
		{// �c�^�ɂ��܂��Ă��Ȃ�
			if (CollisionBillboard(g_Player[g_PlayerPossible].pos, D3DXVECTOR3(10.0f, 20.0f, 10.0f)) == true)
			{// �c�^�ɐG�ꂽ
				g_Player[g_PlayerPossible].move.y = 0.0f;             // �d�͂𖳎�
				g_Player[g_PlayerPossible].move.x = 0.0f;             // �ړ��𖳎�
				g_Player[g_PlayerPossible].move.z = 0.0f;             // �ړ��𖳎�
				g_Player[g_PlayerPossible].state = PLAYERSTATE_GRAB;  // �c�^�ɂ��܂��Ă����Ԃɂ���
				g_Player[g_PlayerPossible].bJump = false;             // �W�����v���Ă��Ȃ���Ԃ�
				g_Player[g_PlayerPossible].bGrab = true;              // �c�^�ɂ��܂��Ă����Ԃ�
																	  // ���[�V�����؂�ւ�����
				SwitchMotion(g_PlayerPossible);
				PlaySound(SOUND_LABEL_SE011);
			}
		}
		else if (g_Player[g_PlayerPossible].bGrab == true)
		{// �c�^�ɂ��܂��Ă���
			if (CollisionBillboard(g_Player[g_PlayerPossible].pos, D3DXVECTOR3(10.0f, 20.0f, 10.0f)) == false)
			{// �c�^�ɐG�ꂽ
				g_Player[g_PlayerPossible].move.y = 0.0f;                  // �d�͂𖳎�
				g_Player[g_PlayerPossible].state = PLAYERSTATE_GRABJUMP;   // �c�^�ɂ��܂��Ă����Ԃɂ���
				g_Player[g_PlayerPossible].bJump = true;                   // �W�����v���Ă����Ԃ�
				g_Player[g_PlayerPossible].bGrab = false;                  // �c�^�ɂ��܂��Ă��Ȃ���Ԃ�
			}
		}
		else if (g_Player[g_PlayerPossible].move.y <= -5.0f && g_Player[g_PlayerPossible].state == PLAYERSTATE_GRABJUMP)
		{// �c�^����W�����v�����������Ă���
			if (CollisionBillboard(g_Player[g_PlayerPossible].pos, D3DXVECTOR3(10.0f, 40.0f, 10.0f)) == true)
			{// �c�^�ɐG�ꂽ
				g_Player[g_PlayerPossible].move.y = 0.0f;             // �d�͂𖳎�
				g_Player[g_PlayerPossible].state = PLAYERSTATE_GRAB;  // �c�^�ɂ��܂��Ă����Ԃɂ���
				g_Player[g_PlayerPossible].bJump = false;             // �W�����v���Ă��Ȃ���Ԃ�
				g_Player[g_PlayerPossible].bGrab = true;              // �c�^�ɂ��܂��Ă����Ԃ�
																	  // ���[�V�����؂�ւ�����
				SwitchMotion(g_PlayerPossible);
			}
		}


		if (g_Player[g_PlayerPossible ^ 1].bGrab == false)
		{// �c�^�ɂ��܂��Ă��Ȃ�
		 // �v���C���[�̍U������
			if (g_Player[g_PlayerPossible ^ 1].state == PLAYERSTATE_PANCH)
			{// �p���`���[�V������������
				PlaySound(SOUND_LABEL_SE005);
				g_Player[g_PlayerPossible ^ 1].move.x = 0.0f;  // �ړ��𖳎�
				g_Player[g_PlayerPossible ^ 1].move.z = 0.0f;  // �ړ��𖳎�
				if (g_Player[g_PlayerPossible ^ 1].nKey >= 2)
				{// ���[�V������16�t���[�����Đ��ł���
					CollisionPlayer(0, g_PlayerPossible ^ 1, g_PlayerPossible);
				}
				// �G�t�F�N�g�̐ݒ�
				SetEffect(D3DXVECTOR3(g_Player[g_PlayerPossible ^ 1].aModel[3].mtxWorld._41, g_Player[g_PlayerPossible ^ 1].aModel[3].mtxWorld._42, g_Player[g_PlayerPossible ^ 1].aModel[3].mtxWorld._43), g_Player[g_PlayerPossible ^ 1].rot, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 15.0f, 100);
			}
			else if (g_Player[g_PlayerPossible ^ 1].state == PLAYERSTATE_KICK)
			{// �L�b�N���[�V������������
				PlaySound(SOUND_LABEL_SE013);
				CollisionPlayer(0, g_PlayerPossible ^ 1, g_PlayerPossible);
				// �G�t�F�N�g�̐ݒ�
				SetEffect(D3DXVECTOR3(g_Player[g_PlayerPossible ^ 1].aModel[7].mtxWorld._41, g_Player[g_PlayerPossible ^ 1].aModel[7].mtxWorld._42, g_Player[g_PlayerPossible ^ 1].aModel[7].mtxWorld._43), g_Player[g_PlayerPossible ^ 1].rot, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 15.0f, 100);
			}
		}

		if (g_Player[g_PlayerPossible ^ 1].state != PLAYERSTATE_GRABJUMP && g_Player[g_PlayerPossible ^ 1].bGrab == false)
		{// �c�^�ɂ��܂��Ă��Ȃ�
			if (CollisionBillboard(g_Player[g_PlayerPossible ^ 1].pos, D3DXVECTOR3(10.0f, 20.0f, 10.0f)) == true)
			{// �c�^�ɐG�ꂽ
				g_Player[g_PlayerPossible ^ 1].move.y = 0.0f;             // �d�͂𖳎�
				g_Player[g_PlayerPossible ^ 1].move.x = 0.0f;             // �ړ��𖳎�
				g_Player[g_PlayerPossible ^ 1].move.z = 0.0f;             // �ړ��𖳎�
				g_Player[g_PlayerPossible ^ 1].state = PLAYERSTATE_GRAB;  // �c�^�ɂ��܂��Ă����Ԃɂ���
				g_Player[g_PlayerPossible ^ 1].bJump = false;             // �W�����v���Ă��Ȃ���Ԃ�
				g_Player[g_PlayerPossible ^ 1].bGrab = true;              // �c�^�ɂ��܂��Ă����Ԃ�
																	  // ���[�V�����؂�ւ�����
				SwitchMotion(g_PlayerPossible ^ 1);
				PlaySound(SOUND_LABEL_SE011);
			}
		}
		else if (g_Player[g_PlayerPossible ^ 1].bGrab == true)
		{// �c�^�ɂ��܂��Ă���
			if (CollisionBillboard(g_Player[g_PlayerPossible ^ 1].pos, D3DXVECTOR3(10.0f, 20.0f, 10.0f)) == false)
			{// �c�^�ɐG�ꂽ
				g_Player[g_PlayerPossible ^ 1].move.y = 0.0f;                  // �d�͂𖳎�
				g_Player[g_PlayerPossible ^ 1].state = PLAYERSTATE_GRABJUMP;   // �c�^�ɂ��܂��Ă����Ԃɂ���
				g_Player[g_PlayerPossible ^ 1].bJump = true;                   // �W�����v���Ă����Ԃ�
				g_Player[g_PlayerPossible ^ 1].bGrab = false;                  // �c�^�ɂ��܂��Ă��Ȃ���Ԃ�
			}
		}
		else if (g_Player[g_PlayerPossible ^ 1].move.y <= -5.0f && g_Player[g_PlayerPossible ^ 1].state == PLAYERSTATE_GRABJUMP)
		{// �c�^����W�����v�����������Ă���
			if (CollisionBillboard(g_Player[g_PlayerPossible ^ 1].pos, D3DXVECTOR3(10.0f, 40.0f, 10.0f)) == true)
			{// �c�^�ɐG�ꂽ
				g_Player[g_PlayerPossible ^ 1].move.y = 0.0f;             // �d�͂𖳎�
				g_Player[g_PlayerPossible ^ 1].state = PLAYERSTATE_GRAB;  // �c�^�ɂ��܂��Ă����Ԃɂ���
				g_Player[g_PlayerPossible ^ 1].bJump = false;             // �W�����v���Ă��Ȃ���Ԃ�
				g_Player[g_PlayerPossible ^ 1].bGrab = true;              // �c�^�ɂ��܂��Ă����Ԃ�
																	  // ���[�V�����؂�ւ�����
				SwitchMotion(g_PlayerPossible ^ 1);
			}
		}

		// �e�̈ʒu�X�V
		SetPositionShadow(g_Player[g_PlayerPossible].nIdxShadow, D3DXVECTOR3(g_Player[g_PlayerPossible].pos.x, g_Player[g_PlayerPossible].pos.y + 1.0f, g_Player[g_PlayerPossible].pos.z));

		// �e�̐F�X�V
		SetColShadow(g_Player[g_PlayerPossible].nIdxShadow, g_Player[g_PlayerPossible].ShadowCol);

		// �e�̑傫���X�V
		SetSizeShadow(g_Player[g_PlayerPossible].nIdxShadow, g_Player[g_PlayerPossible].ShadowWidth, g_Player[g_PlayerPossible].ShadowDepth);

#if _DEBUG

		if (GetKeyboardTrigger(DIK_F2) == true || GetJoyPadTrigger(DIJS_BUTTON_5, g_PlayerPossible) == TRUE)
		{// �v���C���[�̐؂�ւ�
		 //g_Player[g_PlayerPossible].move.y = 0.0f;               // �d�͂𖳎�
		 //g_Player[g_PlayerPossible].move.x = 0.0f;               // �ړ��𖳎�
		 //g_Player[g_PlayerPossible].move.z = 0.0f;               // �ړ��𖳎�
		 //g_Player[g_PlayerPossible].state = PLAYERSTATE_NORMAL;  // �ʏ��Ԃɂ���
		 //g_Player[g_PlayerPossible].bJump = false;               // �W�����v���Ă��Ȃ���Ԃ�
		 //g_Player[g_PlayerPossible].bGrab = false;               // �c�^�ɂ��܂��Ă��Ȃ���Ԃ�
		 // ���[�V�����؂�ւ�����
			PlayerChange(g_PlayerPossible);

			//SwitchMotion(g_PlayerPossible);
			//g_PlayerPossible = (g_PlayerPossible + 1) % 2;          // ����ł���v���C���[�����ւ���
		}
#endif

		//�����N�̎擾
		RANK *pRank;
		pRank = GetRank();

		if (g_PlayerPossible == 0)
		{//����v���C���[���O�Ԃ̏ꍇ
			if (g_Player[0].pos.z >= g_Player[1].pos.z)
			{//�v���C���[�O���v���C���[�P���O�̏ꍇ
				SetRank(RANK_1);	//�����N�P�ɐݒ�
			}
			else
			{//����ȊO�̏ꍇ
				SetRank(RANK_2);	//�����N�Q�ɐݒ�
			}
		}
		else if (g_PlayerPossible == 1)
		{//����v���C���[���P�Ԃ̏ꍇ
			if (g_Player[0].pos.z <= g_Player[1].pos.z)
			{//�v���C���[�P���v���C���[�O���O�̏ꍇ
				SetRank(RANK_1);	//�����N�P�ɐݒ�
			}
			else
			{
				SetRank(RANK_2);	//�����N�Q�ɐݒ�
			}
		}
	}
	else if (g_Mode == MODE_CLEAR)
	{// �Q�[���N���A
		if (GetIdxPlayer() == 0)
		{// �v���C���[0���������炱�̈ʒu
			g_Player[0].pos = D3DXVECTOR3(-40.0f, 0.0f, -1550.0f);	// �ʒu
			g_Player[1].pos = D3DXVECTOR3(50.0f, 0.0f, -1500.0f);	// �ʒu
		}
		else if (GetIdxPlayer() == 1)
		{// �v���C���[1���������炱�̈ʒu
			g_Player[1].pos = D3DXVECTOR3(-40.0f, 0.0f, -1550.0f);	// �ʒu
			g_Player[0].pos = D3DXVECTOR3(50.0f, 0.0f, -1500.0f);	// �ʒu
		}

		// �v���C���[�̃��[�V����
		if (g_Player[0].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotion(0);
		}
		if (g_Player[1].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotion(1);
		}
		if (g_Player[0].mState == MOTIONSTATE_SWITCH)
		{
			PlayerMotionBlend(0);
		}
		if (g_Player[1].mState == MOTIONSTATE_SWITCH)
		{
			PlayerMotionBlend(1);
		}
		if (g_Player[0].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotionAdvance(0);
		}
		if (g_Player[1].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotionAdvance(1);
		}
	}
	else if (g_Mode == MODE_OVER)
	{// �Q�[���I�[�o�[
		g_Player[0].pos = D3DXVECTOR3(-40.0f, 0.0f, -1480.0f);	// �ʒu
		g_Player[1].pos = D3DXVECTOR3(50.0f, 0.0f, -1480.0f);	// �ʒu

																// �v���C���[�̃��[�V����
		if (g_Player[0].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotion(0);
		}
		if (g_Player[1].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotion(1);
		}
		if (g_Player[0].mState == MOTIONSTATE_SWITCH)
		{
			PlayerMotionBlend(0);
		}
		if (g_Player[1].mState == MOTIONSTATE_SWITCH)
		{
			PlayerMotionBlend(1);
		}
		if (g_Player[0].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotionAdvance(0);
		}
		if (g_Player[1].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotionAdvance(1);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;      // �v�Z�p�}�g���b�N�X
	D3DXVECTOR3 vecRot, vecTrans;               // �v�Z�p���f���̌���,���W
	D3DMATERIAL9 matDef;                        // ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;                         // �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// �v���C���[�̐l�������J��Ԃ�
		if (g_Player[nCntPlayer].bDisp == true)
		{// �`�悷���ԂȂ�
		 // ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Player[nCntPlayer].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player[nCntPlayer].rot.y, g_Player[nCntPlayer].rot.x, g_Player[nCntPlayer].rot.z);
			D3DXMatrixMultiply(&g_Player[nCntPlayer].mtxWorld, &g_Player[nCntPlayer].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Player[nCntPlayer].pos.x, g_Player[nCntPlayer].pos.y, g_Player[nCntPlayer].pos.z);
			D3DXMatrixMultiply(&g_Player[nCntPlayer].mtxWorld, &g_Player[nCntPlayer].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player[nCntPlayer].mtxWorld);

			for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
			{// ���f���̃p�[�c�������J��Ԃ�
				if (g_Player[nCntPlayer].aModel[nCntModel].nIdxModelParent == -1)
				{// �e�����Ȃ�
					mtxParent = g_Player[nCntPlayer].mtxWorld;     // �v���C���[�̃}�g���b�N�X�������炤
				}
				else
				{// �e������
					mtxParent = g_Player[nCntPlayer].aModel[g_Player[nCntPlayer].aModel[nCntModel].nIdxModelParent].mtxWorld;   // �e���f���̃}�g���b�N�X�������炤
				}
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Player[nCntPlayer].aModel[nCntModel].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player[nCntPlayer].aModel[nCntModel].rot.y, g_Player[nCntPlayer].aModel[nCntModel].rot.x, g_Player[nCntPlayer].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_Player[nCntPlayer].aModel[nCntModel].pos.x, g_Player[nCntPlayer].aModel[nCntModel].pos.y, g_Player[nCntPlayer].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxTrans);

				// �e�̏��������ɔ��f
				D3DXMatrixMultiply(&g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxParent);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Player[nCntPlayer].aModel[nCntModel].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_Player[nCntPlayer].aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
				{// �ݒ肳��Ă����}�e���A���̐������J��Ԃ�
				 // �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]);

					// ���f��(�p�[�c)�̕`��
					g_Player[nCntPlayer].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}

				// �ۑ����Ă����}�e���A���ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}
//=============================================================================
// �v���C���[�̈ړ�����
//=============================================================================
void PlayerMove(int nIdxPlayer)
{
	g_Player[nIdxPlayer].posold = g_Player[nIdxPlayer].pos;   // �O��̈ʒu�X�V

															  //�v���C���[�̎擾
	Player *pPlayer;
	pPlayer = GetPlayer();


	if (g_Player[nIdxPlayer].bGrab == false)
	{// �c�^�ɂ��܂��Ă��Ȃ�
		if (GetKeyboardPress(DIK_A) == true)
		{// �������̓��͂����ꂽ
			Camera *pCamera;
			pCamera = GetCamera();
			if (GetKeyboardPress(DIK_W) == true)
			{// �����ɏ�����̓��͂����ꂽ
			 // �ړ�����
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.75f);
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// �����ɉ������̓��͂����ꂽ
			 // �ړ�����
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.25f);
			}
			else
			{// ����������ĂȂ�
			 // �ړ�����
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.5f);
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// �E�����̓��͂����ꂽ
			Camera *pCamera;
			pCamera = GetCamera();
			if (GetKeyboardPress(DIK_W) == true)
			{// �����ɏ�����̓��͂����ꂽ
			 // �ړ�����
				g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.75f);
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// �����ɉ������̓��͂����ꂽ
			 // �ړ�����
				g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.25f);
			}
			else
			{// ����������ĂȂ�
			 // �ړ�����
				g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.5f);
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{// ������̓��͂����ꂽ
			Camera *pCamera;
			pCamera = GetCamera();

			// �ړ�����
			g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y + D3DX_PI) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y + D3DX_PI) * g_Player[nIdxPlayer].fMovement;

			// �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + D3DX_PI;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// �������̓��͂����ꂽ
			Camera *pCamera;
			pCamera = GetCamera();

			// �ړ�����
			g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;

			// �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_10, g_PlayerPossible) == true || GetJoyPadPress(DIJS_BUTTON_11, g_PlayerPossible) == true ||
			GetJoyPadPress(DIJS_BUTTON_12, g_PlayerPossible) == true || GetJoyPadPress(DIJS_BUTTON_13, g_PlayerPossible) == true)
		{// ���A�i���O�X�e�B�b�N�̓��͂����ꂽ
			Camera *pCamera;
			pCamera = GetCamera();

			// �ړ�����
			g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - GetJotPadRightStick(g_PlayerPossible)) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - GetJotPadRightStick(g_PlayerPossible)) * g_Player[nIdxPlayer].fMovement;

			// �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y - GetJotPadRightStick(g_PlayerPossible);
		}
		else if (GetJoyPadPress(DIJS_BUTTON_18, g_PlayerPossible) == true || GetJoyPadPress(DIJS_BUTTON_19, g_PlayerPossible) == true
			|| GetJoyPadPress(DIJS_BUTTON_20, g_PlayerPossible) == true || GetJoyPadPress(DIJS_BUTTON_21, g_PlayerPossible) == true)
		{// �\���L�[���͂����ꂽ
			Camera *pCamera;
			pCamera = GetCamera();

			// �ړ�����
			g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y + GetJotPadRadian(g_PlayerPossible)) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y + GetJotPadRadian(g_PlayerPossible)) * g_Player[nIdxPlayer].fMovement;

			// �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + GetJotPadRadian(g_PlayerPossible) - D3DX_PI;
		}
	}
	else if (g_Player[nIdxPlayer].bGrab == true)
	{// �c�^�ɂ��܂��Ă���
		if (GetJoyPadPress(DIJS_BUTTON_10, g_PlayerPossible) == TRUE ||
			GetJoyPadPress(DIJS_BUTTON_18, g_PlayerPossible) == TRUE ||
			GetKeyboardPress(DIK_W) == true)
		{// ������̓��͂����ꂽ
			g_Player[nIdxPlayer].move.y += 1.0f;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_11, g_PlayerPossible) == TRUE ||
			GetJoyPadPress(DIJS_BUTTON_19, g_PlayerPossible) == TRUE ||
			GetKeyboardPress(DIK_S) == true)
		{// �������̓��͂����ꂽ
			g_Player[nIdxPlayer].move.y -= 1.0f;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_16, g_PlayerPossible) == TRUE ||
			GetKeyboardPress(DIK_A) == true)
		{// �������̓��͂����ꂽ
		 // �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = -D3DX_PI * 0.5f;

			// ���W�C��
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x - 7.0f;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_17, g_PlayerPossible) == TRUE ||
			GetKeyboardPress(DIK_D) == true)
		{// �E�����̓��͂����ꂽ
		 // �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = D3DX_PI * 0.5f;

			// ���W�C��
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x + 7.0f;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_14, g_PlayerPossible) == TRUE ||
			GetKeyboardPress(DIK_K) == true)
		{// ������̓��͂����ꂽ
		 // �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = D3DX_PI;

			// ���W�C��
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z - 10.0f;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_15, g_PlayerPossible) == TRUE ||
			GetKeyboardPress(DIK_I) == true)
		{// �������̓��͂����ꂽ
		 // �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = 0.0f;

			// ���W�C��
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z + 10.0f;
		}
		if (g_Player[nIdxPlayer].move.y <= 0.1f && g_Player[nIdxPlayer].move.y >= -0.1f)
		{// �ړ����Ă��Ȃ�������
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_GRABNOR)
			{// �ړ����Ă��Ȃ���Ԃ���Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABNOR;        // �c�^�j���[�g�����̏�Ԃ�
																		 // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.y > 0.1f)
		{// ����Ă���
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_GRABUP)
			{// �ړ����Ă����Ԃ���Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABUP;         // �c�^������Ă����Ԃ�
																		 // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.y < -0.1f)
		{// �����Ă�����
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_GRABDOWN)
			{// �ړ����Ă����Ԃ���Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABDOWN;        // �c�^������Ă����Ԃ�
																		  // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
		}
	}


	if (GetJoyPadTrigger(DIJS_BUTTON_1, g_PlayerPossible) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
	{// �L�[�{�[�h��[ENTER]�L�[�������ꂽ
		if (g_Player[nIdxPlayer].bJump == false)
		{// �W�����v���Ă��Ȃ�����
			if (g_Player[nIdxPlayer].bGrab == true)
			{// �c�^�ɂ��܂��Ă���
				Camera *pCamera;
				pCamera = GetCamera();

				// �ړ�����
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + D3DX_PI;

				g_Player[nIdxPlayer].move.y += g_Player[nIdxPlayer].fJumpPower;          // ��ɔ�΂�
				g_Player[nIdxPlayer].bJump = true;                  // �W�����v���Ă��锻���
				g_Player[nIdxPlayer].bGrab = false;                 // �c�^�ɂ��܂��Ă��Ȃ���Ԃ�
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABJUMP;  // �c�^����W�����v������Ԃ�
				PlaySound(SOUND_LABEL_SE011);		
				// ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
			else
			{// �c�^�ɂ��܂��Ă��Ȃ�
				g_Player[nIdxPlayer].move.y += g_Player[nIdxPlayer].fJumpPower;    // ��ɔ�΂�
				g_Player[nIdxPlayer].bJump = true;                  // �W�����v���Ă��锻���
				g_Player[nIdxPlayer].state = PLAYERSTATE_JUMP;      // �W�����v��Ԃ�
				PlaySound(SOUND_LABEL_SE008);
				// ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
		}
	}

	// �ړI�̊p�x�̏C��
	g_Player[nIdxPlayer].DiffAngle.y = g_Player[nIdxPlayer].DestAngle.y - g_Player[nIdxPlayer].rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

	if (g_Player[nIdxPlayer].DiffAngle.y > D3DX_PI)
	{// ������D3DX_PI�𒴂���
		g_Player[nIdxPlayer].DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].DiffAngle.y < -D3DX_PI)
	{// ������-D3DX_PI�𒴂���
		g_Player[nIdxPlayer].DiffAngle.y += D3DX_PI * 2.0f;
	}

	//���݂̊p�x�̏C��
	g_Player[nIdxPlayer].rot.y += g_Player[nIdxPlayer].DiffAngle.y * 0.1f;

	if (g_Player[nIdxPlayer].rot.y > D3DX_PI)
	{// ���݂̌�����D3DX_PI�𒴂���
		g_Player[nIdxPlayer].rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].rot.y < -D3DX_PI)
	{// ���݂̌�����-D3DX_PI�𒴂���
		g_Player[nIdxPlayer].rot.y += D3DX_PI * 2.0f;
	}

	// ��������
	if (g_Player[nIdxPlayer].bGrab == false)
	{// �c�^�ɂ��܂��Ă��Ȃ�
		g_Player[nIdxPlayer].move.y += GRAVITY_POWER;
	}

	// �ʒu���ړ�
	g_Player[nIdxPlayer].pos.x += g_Player[nIdxPlayer].move.x;
	g_Player[nIdxPlayer].pos.y += g_Player[nIdxPlayer].move.y;
	g_Player[nIdxPlayer].pos.z += g_Player[nIdxPlayer].move.z;

	if (g_Player[nIdxPlayer].bGrab == true)
	{// �c�^�ɂ��܂��Ă���
		g_Player[nIdxPlayer].move.y = 0.0f;
	}

	if (g_Player[nIdxPlayer].bJump == false && g_Player[nIdxPlayer].state != PLAYERSTATE_LANDING && g_Player[nIdxPlayer].state != PLAYERSTATE_KICK && g_Player[nIdxPlayer].state != PLAYERSTATE_PANCH
		&& g_Player[nIdxPlayer].state != PLAYERSTATE_DAMAGE && g_Player[nIdxPlayer].bGrab == false)
	{// �W�����v���Ă��Ȃ������n��ԂłȂ����A�N�V������ԂłȂ����_���[�W��ԂłȂ�
		if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
			g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
		{// �ړ����Ă��Ȃ�������
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_NORMAL)
			{// �ړ����Ă��Ȃ���Ԃ���Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_NORMAL;   // �ʏ�̏�Ԃ�
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
			g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
		{// �ړ����Ă�����
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
			{// �ړ����Ă����Ԃ���Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;     // �ړ����Ă����Ԃ�
				SwitchMotion(nIdxPlayer);
			}
		}
	}

	// �R�[�X�̓����蔻��
#if 1
	if (CollisionCourse(&g_Player[nIdxPlayer].pos, &g_Player[nIdxPlayer].posold, &g_Player[nIdxPlayer].move, D3DXVECTOR3(0.0f, 0.0f, 0.0f)) == true)
	{// �R�[�X�ɏ��Ă���
		if (g_Player[nIdxPlayer].bJump == true)
		{// �W�����v���Ă���
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// �ړ����Ă��Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE)
		{// �_���[�W��Ԃ�����
			g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;      // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
			SwitchMotion(nIdxPlayer);
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_KICK)
		{// �L�b�N��Ԃ�����
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// �ړ����Ă��Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// �ړ����Ă�����
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// �ړ����Ă����Ԃ���Ȃ�������
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // �ړ����Ă����Ԃ�
																	// ���[�V�����؂�ւ�����
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		g_Player[nIdxPlayer].bJump = false;  // �W�����v���Ă��Ȃ������
	}
	else
	{
		if (g_Player[nIdxPlayer].pos.y < -200.0f)
		{
			PlayerChange(nIdxPlayer);
		}
	}
#endif

	// �f�o�b�N�p
#if 0
	if (g_Player[nIdxPlayer].pos.y <= 0.0f)
	{// �n��ɂ���
		g_Player[nIdxPlayer].pos.y = 0.0f;
		g_Player[nIdxPlayer].move.y = 0.0f;
		if (g_Player[nIdxPlayer].bJump == true)
		{// �W�����v���Ă���
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// �ړ����Ă��Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE)
		{// �_���[�W��Ԃ�����
			g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;      // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
			SwitchMotion(nIdxPlayer);
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_KICK)
		{// �L�b�N��Ԃ�����
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// �ړ����Ă��Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// �ړ����Ă�����
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// �ړ����Ă����Ԃ���Ȃ�������
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // �ړ����Ă����Ԃ�
																	// ���[�V�����؂�ւ�����
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		g_Player[nIdxPlayer].bJump = false;  // �W�����v���Ă��Ȃ������
	}
#endif

	// �����𓭂�����
	g_Player[nIdxPlayer].move.x += (0.0f - g_Player[nIdxPlayer].move.x) * PLAYER_INERTIA;
	g_Player[nIdxPlayer].move.z += (0.0f - g_Player[nIdxPlayer].move.z) * PLAYER_INERTIA;
}

//=============================================================================
// ����ł���v���C���[�̑J�ڏ���
//=============================================================================
void PlayerTransition(int nIdxPlayer)
{
	g_Player[nIdxPlayer].posold = g_Player[nIdxPlayer].pos;   // �O��̈ʒu�X�V

															  // �ړI�̊p�x�̏C��
	g_Player[nIdxPlayer].DiffAngle.y = g_Player[nIdxPlayer].DestAngle.y - g_Player[nIdxPlayer].rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

	if (g_Player[nIdxPlayer].DiffAngle.y > D3DX_PI)
	{// ������D3DX_PI�𒴂���
		g_Player[nIdxPlayer].DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].DiffAngle.y < -D3DX_PI)
	{// ������-D3DX_PI�𒴂���
		g_Player[nIdxPlayer].DiffAngle.y += D3DX_PI * 2.0f;
	}

	//���݂̊p�x�̏C��
	g_Player[nIdxPlayer].rot.y += g_Player[nIdxPlayer].DiffAngle.y * 0.1f;

	if (g_Player[nIdxPlayer].rot.y > D3DX_PI)
	{// ���݂̌�����D3DX_PI�𒴂���
		g_Player[nIdxPlayer].rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].rot.y < -D3DX_PI)
	{// ���݂̌�����-D3DX_PI�𒴂���
		g_Player[nIdxPlayer].rot.y += D3DX_PI * 2.0f;
	}

	// ��������
	if (g_Player[nIdxPlayer].bGrab == false)
	{// �c�^�ɂ��܂��Ă��Ȃ�
		g_Player[nIdxPlayer].move.y += GRAVITY_POWER;
	}

	// �ʒu���ړ�
	g_Player[nIdxPlayer].pos.x += g_Player[nIdxPlayer].move.x;
	g_Player[nIdxPlayer].pos.y += g_Player[nIdxPlayer].move.y;
	g_Player[nIdxPlayer].pos.z += g_Player[nIdxPlayer].move.z;

	if (g_Player[nIdxPlayer].bGrab == true)
	{// �c�^�ɂ��܂��Ă���
		g_Player[nIdxPlayer].move.y = 0.0f;
	}

	if (g_Player[nIdxPlayer].state != PLAYERSTATE_JUMP && g_Player[nIdxPlayer].state != PLAYERSTATE_LANDING && g_Player[nIdxPlayer].state != PLAYERSTATE_KICK && g_Player[nIdxPlayer].state != PLAYERSTATE_PANCH
		&& g_Player[nIdxPlayer].state != PLAYERSTATE_DAMAGE && g_Player[nIdxPlayer].state != PLAYERSTATE_GRABJUMP && g_Player[nIdxPlayer].bGrab == false)
	{// �W�����v���Ă��Ȃ������n��ԂłȂ����A�N�V������ԂłȂ����_���[�W��ԂłȂ�
		if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
			g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
		{// �ړ����Ă��Ȃ�������
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_NORMAL)
			{// �ړ����Ă��Ȃ���Ԃ���Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_NORMAL;   // �ʏ�̏�Ԃ�
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
			g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
		{// �ړ����Ă�����
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
			{// �ړ����Ă����Ԃ���Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;     // �ړ����Ă����Ԃ�
				SwitchMotion(nIdxPlayer);
			}
		}
	}

	// �e�̈ʒu�X�V
	SetPositionShadow(g_Player[nIdxPlayer].nIdxShadow, D3DXVECTOR3(g_Player[nIdxPlayer].pos.x, 1.0f, g_Player[nIdxPlayer].pos.z));

	// �e�̐F�X�V
	SetColShadow(g_Player[nIdxPlayer].nIdxShadow, g_Player[nIdxPlayer].ShadowCol);

	// �e�̑傫���X�V
	SetSizeShadow(g_Player[nIdxPlayer].nIdxShadow, g_Player[nIdxPlayer].ShadowWidth, g_Player[nIdxPlayer].ShadowDepth);

	if (CollisionObstacle(&g_Player[nIdxPlayer].pos, &g_Player[nIdxPlayer].posold, &g_Player[nIdxPlayer].move, g_Player[nIdxPlayer].radius) == true)
	{// ��Q���ɓ������Ă���
		if (g_Player[nIdxPlayer].state == PLAYERSTATE_KICK || g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE)
		{// �L�b�N���Ă�����
			g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;   // ���n�̏�Ԃ�
			SwitchMotion(nIdxPlayer);
		}
		if (g_Player[nIdxPlayer].state == PLAYERSTATE_JUMP || g_Player[nIdxPlayer].state == PLAYERSTATE_GRABJUMP)
		{// �W�����v���Ă���
			g_Player[nIdxPlayer].bJump = false;    // �W�����v���锻���
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// �ړ����Ă��Ȃ�������
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_LANDING)
				{// �ړ����Ă��Ȃ���Ԃ���Ȃ�������
					g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;   // ���n�̏�Ԃ�
					SwitchMotion(nIdxPlayer);
				}
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// �ړ����Ă�����
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// �ړ����Ă����Ԃ���Ȃ�������
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;     // �ړ����Ă����Ԃ�
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		// �e�̈ʒu�X�V
		SetPositionShadow(g_Player[nIdxPlayer].nIdxShadow, D3DXVECTOR3(g_Player[nIdxPlayer].pos.x, g_Player[nIdxPlayer].pos.y + 1.0f, g_Player[nIdxPlayer].pos.z));
	}
	else
	{// ��Q���ɏ���Ă��Ȃ�
		if (g_Player[nIdxPlayer].bJump == false)
		{// �W�����v���Ă���
			g_Player[nIdxPlayer].bJump = true;  // �W�����v���Ȃ������
		}
	}

	// �R�[�X�̓����蔻��
#if 1
	if (CollisionCourse(&g_Player[nIdxPlayer].pos, &g_Player[nIdxPlayer].posold, &g_Player[nIdxPlayer].move, D3DXVECTOR3(0.0f, 0.0f, 0.0f)) == true)
	{// �R�[�X�ɏ��Ă���
		if (g_Player[nIdxPlayer].state == PLAYERSTATE_JUMP || g_Player[nIdxPlayer].state == PLAYERSTATE_GRABJUMP)
		{// �W�����v���Ă���
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// �ړ����Ă��Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// �ړ����Ă�����
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// �ړ����Ă����Ԃ���Ȃ�������
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // �ړ����Ă����Ԃ�
																	// ���[�V�����؂�ւ�����
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE)
		{// �_���[�W��Ԃ�����
			g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;      // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
			SwitchMotion(nIdxPlayer);
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_KICK)
		{// �L�b�N��Ԃ�����
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// �ړ����Ă��Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// �ړ����Ă�����
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// �ړ����Ă����Ԃ���Ȃ�������
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // �ړ����Ă����Ԃ�
																	// ���[�V�����؂�ւ�����
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		g_Player[nIdxPlayer].bJump = false;  // �W�����v���Ă��Ȃ������
	}
	else
	{// �R�[�X�ɏ���Ă��Ȃ�
	 // �e�̈ʒu�X�V
		SetPositionShadow(g_Player[nIdxPlayer].nIdxShadow, D3DXVECTOR3(g_Player[nIdxPlayer].pos.x, g_Player[nIdxPlayer].pos.y + 1.0f, g_Player[nIdxPlayer].pos.z));

#if _DEBUG
		if (GetKeyboardTrigger(DIK_F8) == true)
		{
			g_Player[nIdxPlayer].pos.y = 30.0f;
			g_Player[nIdxPlayer].move.y = 0.0f;
		}
#endif
	}
#endif

	// �f�o�b�N�p
#if 0
	if (g_Player[nIdxPlayer].pos.y <= 0.0f)
	{// �n��ɂ���
		g_Player[nIdxPlayer].pos.y = 0.0f;
		g_Player[nIdxPlayer].move.y = 0.0f;
		g_Player[nIdxPlayer].bJump = false;  // �W�����v���Ă��Ȃ������
		if (g_Player[nIdxPlayer].state == PLAYERSTATE_JUMP || g_Player[nIdxPlayer].state == PLAYERSTATE_GRABJUMP)
		{// �W�����v���Ă���
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// �ړ����Ă��Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// �ړ����Ă�����
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// �ړ����Ă����Ԃ���Ȃ�������
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // �ړ����Ă����Ԃ�
																	// ���[�V�����؂�ւ�����
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE)
		{// �_���[�W��Ԃ�����
			g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;      // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
			SwitchMotion(nIdxPlayer);
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_KICK)
		{// �L�b�N��Ԃ�����
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// �ړ����Ă��Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// �ړ����Ă�����
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// �ړ����Ă����Ԃ���Ȃ�������
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // �ړ����Ă����Ԃ�
																	// ���[�V�����؂�ւ�����
					SwitchMotion(nIdxPlayer);
				}
			}
		}
	}
#endif

	// �����𓭂�����
	g_Player[nIdxPlayer].move.x += (0.0f - g_Player[nIdxPlayer].move.x) * PLAYER_INERTIA;
	g_Player[nIdxPlayer].move.z += (0.0f - g_Player[nIdxPlayer].move.z) * PLAYER_INERTIA;
}

//=============================================================================
// ����ł��Ȃ��v���C���[�̏���
//=============================================================================
void PlayerImpossible(int nIdxPlayer)
{
	g_Player[nIdxPlayer].posold = g_Player[nIdxPlayer].pos;   // �O��̈ʒu�X�V

	// ��������
	g_Player[nIdxPlayer].move.y += GRAVITY_POWER;

	if (g_Player[nIdxPlayer].bGrab == false)
	{// �c�^�ɂ��܂��Ă��Ȃ�
		if (GetKeyboardPress(DIK_A) == true)
		{// �������̓��͂����ꂽ
			Camera *pCamera;
			pCamera = GetCamera();
			if (GetKeyboardPress(DIK_W) == true)
			{// �����ɏ�����̓��͂����ꂽ
			 // �ړ�����
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.75f);
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// �����ɉ������̓��͂����ꂽ
			 // �ړ�����
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.25f);
			}
			else
			{// ����������ĂȂ�
			 // �ړ�����
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.5f);
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// �E�����̓��͂����ꂽ
			Camera *pCamera;
			pCamera = GetCamera();
			if (GetKeyboardPress(DIK_W) == true)
			{// �����ɏ�����̓��͂����ꂽ
			 // �ړ�����
				g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.75f);
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// �����ɉ������̓��͂����ꂽ
			 // �ړ�����
				g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.25f);
			}
			else
			{// ����������ĂȂ�
			 // �ړ�����
				g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.5f);
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{// ������̓��͂����ꂽ
			Camera *pCamera;
			pCamera = GetCamera();

			// �ړ�����
			g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y + D3DX_PI) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y + D3DX_PI) * g_Player[nIdxPlayer].fMovement;

			// �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + D3DX_PI;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// �������̓��͂����ꂽ
			Camera *pCamera;
			pCamera = GetCamera();

			// �ړ�����
			g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;

			// �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_10, g_PlayerPossible ^ 1) == true || GetJoyPadPress(DIJS_BUTTON_11, g_PlayerPossible ^ 1) == true ||
			GetJoyPadPress(DIJS_BUTTON_12, g_PlayerPossible ^ 1) == true || GetJoyPadPress(DIJS_BUTTON_13, g_PlayerPossible ^ 1) == true)
		{// ���A�i���O�X�e�B�b�N�̓��͂����ꂽ
			Camera *pCamera;
			pCamera = GetCamera();

			// �ړ�����
			g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - GetJotPadRightStick(g_PlayerPossible ^ 1)) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - GetJotPadRightStick(g_PlayerPossible ^ 1)) * g_Player[nIdxPlayer].fMovement;

			// �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y - GetJotPadRightStick(g_PlayerPossible ^ 1);
		}
		else if (GetJoyPadPress(DIJS_BUTTON_18, g_PlayerPossible ^ 1) == true || GetJoyPadPress(DIJS_BUTTON_19, g_PlayerPossible ^ 1) == true
			|| GetJoyPadPress(DIJS_BUTTON_20, g_PlayerPossible ^ 1) == true || GetJoyPadPress(DIJS_BUTTON_21, g_PlayerPossible ^ 1) == true)
		{// �\���L�[���͂����ꂽ
			Camera *pCamera;
			pCamera = GetCamera();

			// �ړ�����
			g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y + GetJotPadRadian(g_PlayerPossible ^ 1)) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y + GetJotPadRadian(g_PlayerPossible ^ 1)) * g_Player[nIdxPlayer].fMovement;

			// �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + GetJotPadRadian(g_PlayerPossible ^ 1) - D3DX_PI;
		}
	}
	else if (g_Player[nIdxPlayer].bGrab == true)
	{// �c�^�ɂ��܂��Ă���
		if (GetJoyPadPress(DIJS_BUTTON_10, g_PlayerPossible ^ 1) == TRUE ||
			GetJoyPadPress(DIJS_BUTTON_18, g_PlayerPossible ^ 1) == TRUE ||
			GetKeyboardPress(DIK_W) == true)
		{// ������̓��͂����ꂽ
			g_Player[nIdxPlayer].move.y += 1.0f;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_11, g_PlayerPossible ^ 1) == TRUE ||
			GetJoyPadPress(DIJS_BUTTON_19, g_PlayerPossible ^ 1) == TRUE ||
			GetKeyboardPress(DIK_S) == true)
		{// �������̓��͂����ꂽ
			g_Player[nIdxPlayer].move.y -= 1.0f;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_16, g_PlayerPossible ^ 1) == TRUE ||
			GetKeyboardPress(DIK_A) == true)
		{// �������̓��͂����ꂽ
		 // �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = -D3DX_PI * 0.5f;

			// ���W�C��
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x - 7.0f;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_17, g_PlayerPossible ^ 1) == TRUE ||
			GetKeyboardPress(DIK_D) == true)
		{// �E�����̓��͂����ꂽ
		 // �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = D3DX_PI * 0.5f;

			// ���W�C��
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x + 7.0f;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_14, g_PlayerPossible ^ 1) == TRUE ||
			GetKeyboardPress(DIK_K) == true)
		{// ������̓��͂����ꂽ
		 // �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = D3DX_PI;

			// ���W�C��
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z - 10.0f;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_15, g_PlayerPossible ^ 1) == TRUE ||
			GetKeyboardPress(DIK_I) == true)
		{// �������̓��͂����ꂽ
		 // �ړI�̊p�x�ύX
			g_Player[nIdxPlayer].DestAngle.y = 0.0f;

			// ���W�C��
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z + 10.0f;
		}
		if (g_Player[nIdxPlayer].move.y <= 0.1f && g_Player[nIdxPlayer].move.y >= -0.1f)
		{// �ړ����Ă��Ȃ�������
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_GRABNOR)
			{// �ړ����Ă��Ȃ���Ԃ���Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABNOR;        // �c�^�j���[�g�����̏�Ԃ�
																		 // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.y > 0.1f)
		{// ����Ă���
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_GRABUP)
			{// �ړ����Ă����Ԃ���Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABUP;         // �c�^������Ă����Ԃ�
																		 // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.y < -0.1f)
		{// �����Ă�����
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_GRABDOWN)
			{// �ړ����Ă����Ԃ���Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABDOWN;        // �c�^������Ă����Ԃ�
																		  // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
		}
	}


	if (GetJoyPadTrigger(DIJS_BUTTON_1, g_PlayerPossible ^ 1) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
	{// �L�[�{�[�h��[ENTER]�L�[�������ꂽ
		if (g_Player[nIdxPlayer].bJump == false)
		{// �W�����v���Ă��Ȃ�����
			if (g_Player[nIdxPlayer].bGrab == true)
			{// �c�^�ɂ��܂��Ă���
				Camera *pCamera;
				pCamera = GetCamera();

				// �ړ�����
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;

				// �ړI�̊p�x�ύX
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + D3DX_PI;

				g_Player[nIdxPlayer].move.y += g_Player[nIdxPlayer].fJumpPower;          // ��ɔ�΂�
				g_Player[nIdxPlayer].bJump = true;                  // �W�����v���Ă��锻���
				g_Player[nIdxPlayer].bGrab = false;                 // �c�^�ɂ��܂��Ă��Ȃ���Ԃ�
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABJUMP;  // �c�^����W�����v������Ԃ�
				PlaySound(SOUND_LABEL_SE011);				
				// ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
			else
			{// �c�^�ɂ��܂��Ă��Ȃ�
				g_Player[nIdxPlayer].move.y += g_Player[nIdxPlayer].fJumpPower;    // ��ɔ�΂�
				g_Player[nIdxPlayer].bJump = true;                  // �W�����v���Ă��锻���
				g_Player[nIdxPlayer].state = PLAYERSTATE_JUMP;      // �W�����v��Ԃ�
				PlaySound(SOUND_LABEL_SE008);
				// ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
		}
	}

	// �ړI�̊p�x�̏C��
	g_Player[nIdxPlayer].DiffAngle.y = g_Player[nIdxPlayer].DestAngle.y - g_Player[nIdxPlayer].rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

	if (g_Player[nIdxPlayer].DiffAngle.y > D3DX_PI)
	{// ������D3DX_PI�𒴂���
		g_Player[nIdxPlayer].DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].DiffAngle.y < -D3DX_PI)
	{// ������-D3DX_PI�𒴂���
		g_Player[nIdxPlayer].DiffAngle.y += D3DX_PI * 2.0f;
	}

	//���݂̊p�x�̏C��
	g_Player[nIdxPlayer].rot.y += g_Player[nIdxPlayer].DiffAngle.y * 0.1f;

	if (g_Player[nIdxPlayer].rot.y > D3DX_PI)
	{// ���݂̌�����D3DX_PI�𒴂���
		g_Player[nIdxPlayer].rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].rot.y < -D3DX_PI)
	{// ���݂̌�����-D3DX_PI�𒴂���
		g_Player[nIdxPlayer].rot.y += D3DX_PI * 2.0f;
	}

	// �ʒu���ړ�
	g_Player[nIdxPlayer].pos.x += g_Player[nIdxPlayer].move.x;
	g_Player[nIdxPlayer].pos.y += g_Player[nIdxPlayer].move.y;
	g_Player[nIdxPlayer].pos.z += g_Player[nIdxPlayer].move.z;

	if (CollisionWall(&g_Player[nIdxPlayer].pos, &g_Player[nIdxPlayer].posold) == true)
	{
		g_Player[nIdxPlayer].pos.x = g_Player[nIdxPlayer].posold.x;
		g_Player[nIdxPlayer].pos.z = g_Player[nIdxPlayer].posold.z;
	}

	// �ړI�̊p�x�̏C��
	g_Player[nIdxPlayer].DiffAngle.y = g_Player[nIdxPlayer].DestAngle.y - g_Player[nIdxPlayer].rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

	if (g_Player[nIdxPlayer].DiffAngle.y > D3DX_PI)
	{// ������D3DX_PI�𒴂���
		g_Player[nIdxPlayer].DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].DiffAngle.y < -D3DX_PI)
	{// ������-D3DX_PI�𒴂���
		g_Player[nIdxPlayer].DiffAngle.y += D3DX_PI * 2.0f;
	}

	//���݂̊p�x�̏C��
	g_Player[nIdxPlayer].rot.y += g_Player[nIdxPlayer].DiffAngle.y * 0.1f;

	if (g_Player[nIdxPlayer].rot.y > D3DX_PI)
	{// ���݂̌�����D3DX_PI�𒴂���
		g_Player[nIdxPlayer].rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].rot.y < -D3DX_PI)
	{// ���݂̌�����-D3DX_PI�𒴂���
		g_Player[nIdxPlayer].rot.y += D3DX_PI * 2.0f;
	}


	if (g_Player[nIdxPlayer].bGrab == true)
	{// �c�^�ɂ��܂��Ă���
		g_Player[nIdxPlayer].move.y = 0.0f;
	}

	if (g_Player[nIdxPlayer].bJump == false && g_Player[nIdxPlayer].state != PLAYERSTATE_LANDING && g_Player[nIdxPlayer].state != PLAYERSTATE_KICK && g_Player[nIdxPlayer].state != PLAYERSTATE_PANCH
		&& g_Player[nIdxPlayer].state != PLAYERSTATE_DAMAGE && g_Player[nIdxPlayer].bGrab == false)
	{// �W�����v���Ă��Ȃ������n��ԂłȂ����A�N�V������ԂłȂ����_���[�W��ԂłȂ�
		if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
			g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
		{// �ړ����Ă��Ȃ�������
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_NORMAL)
			{// �ړ����Ă��Ȃ���Ԃ���Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_NORMAL;   // �ʏ�̏�Ԃ�
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
			g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
		{// �ړ����Ă�����
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
			{// �ړ����Ă����Ԃ���Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;     // �ړ����Ă����Ԃ�
				SwitchMotion(nIdxPlayer);
			}
		}
	}

	// �R�[�X�̓����蔻��
	if (CollisionCourse(&g_Player[nIdxPlayer].pos, &g_Player[nIdxPlayer].posold, &g_Player[nIdxPlayer].move, D3DXVECTOR3(0.0f, 0.0f, 0.0f)) == true)
	{// �R�[�X�ɏ��Ă���
		if (g_Player[nIdxPlayer].bJump == true)
		{// �W�����v���Ă���
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// �ړ����Ă��Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE)
		{// �_���[�W��Ԃ�����
			g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;      // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
			SwitchMotion(nIdxPlayer);
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_KICK)
		{// �L�b�N��Ԃ�����
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// �ړ����Ă��Ȃ�������
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // ���n��Ԃ�
																   // ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// �ړ����Ă�����
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// �ړ����Ă����Ԃ���Ȃ�������
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // �ړ����Ă����Ԃ�
																	// ���[�V�����؂�ւ�����
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		g_Player[nIdxPlayer].bJump = false;  // �W�����v���Ă��Ȃ������
	}

	// �����𓭂�����
	g_Player[nIdxPlayer].move.x += (0.0f - g_Player[nIdxPlayer].move.x) * PLAYER_INERTIA;
	g_Player[nIdxPlayer].move.z += (0.0f - g_Player[nIdxPlayer].move.z) * PLAYER_INERTIA;


}
//=============================================================================
// �v���C���[�̃��[�V����
//=============================================================================
void PlayerMotion(int nIdxPlayer)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�����J��Ԃ�
	 // ���݂̈ʒu�X�V
		g_Player[nIdxPlayer].aModel[nCntModel].pos.x += g_Player[nIdxPlayer].aModel[nCntModel].posDiff.x / g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey;
		g_Player[nIdxPlayer].aModel[nCntModel].pos.y += g_Player[nIdxPlayer].aModel[nCntModel].posDiff.y / g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey;
		g_Player[nIdxPlayer].aModel[nCntModel].pos.z += g_Player[nIdxPlayer].aModel[nCntModel].posDiff.z / g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey;

		g_Player[nIdxPlayer].aModel[nCntModel].rot.x += g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x / g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey;

		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.x > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.x < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}

		g_Player[nIdxPlayer].aModel[nCntModel].rot.y += g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y / g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey;

		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.y > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.y < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}

		g_Player[nIdxPlayer].aModel[nCntModel].rot.z += g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z / g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey;

		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.z > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.z < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}
}
//=============================================================================
// �v���C���[�̃��[�V�����u�����h����
//=============================================================================
void PlayerMotionBlend(int nIdxPlayer)
{
	// �u�����h�J�E���^�[��i�߂�
	g_Player[nIdxPlayer].nBlendCounter++;
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�����J��Ԃ�
	 // ���݂̈ʒu�X�V
		g_Player[nIdxPlayer].aModel[nCntModel].pos.x += g_Player[nIdxPlayer].aModel[nCntModel].posDiff.x / (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f);
		g_Player[nIdxPlayer].aModel[nCntModel].pos.y += g_Player[nIdxPlayer].aModel[nCntModel].posDiff.y / (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f);
		g_Player[nIdxPlayer].aModel[nCntModel].pos.z += g_Player[nIdxPlayer].aModel[nCntModel].posDiff.z / (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f);

		g_Player[nIdxPlayer].aModel[nCntModel].rot.x += g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x / (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f);

		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.x > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.x < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}
		g_Player[nIdxPlayer].aModel[nCntModel].rot.y += g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y / (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f);

		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.y > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.y < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}

		g_Player[nIdxPlayer].aModel[nCntModel].rot.z += g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z / (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f);

		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.z > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.z < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}

	if (g_Player[nIdxPlayer].nBlendCounter >= g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f)
	{// �u�����h�J�E���^�[������̒l��
		g_Player[nIdxPlayer].nBlendCounter = 0;            // �u�����h�J�E���^�[��������
		if (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].nNumKey >= 2)
		{// �L�[�t���[����2�ȏ゠������
			g_Player[nIdxPlayer].mState = MOTIONSTATE_NORMAL;  // ���[�V�����̏�Ԃ�ʏ�̏�Ԃ�
			g_Player[nIdxPlayer].nKey++;                       // �L�[�t���[����i�߂�
															   // �L�[�t���[���؂�ւ�����
			SwitchKey(nIdxPlayer);
		}
		else
		{// �L�[�t���[��������ȏ�Ȃ�
			g_Player[nIdxPlayer].mState = MOTIONSTATE_STOP;    // ���[�V�����̏�Ԃ����[�V�������Ȃ���Ԃ�
		}
	}
}
//=============================================================================
// ���[�V�����i�s����
//=============================================================================
void PlayerMotionAdvance(int nIdxPlayer)
{
	g_Player[nIdxPlayer].nMotionCounter++;   // ���[�V�����J�E���^�[��i�߂�
	if (g_Player[nIdxPlayer].nMotionCounter >= g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey)
	{// �Đ��t���[�����ɒB����
		if (g_Player[nIdxPlayer].nKey == g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].nNumKey - 1)
		{// ���݂̃L�[�t���[���������̃��[�V�����̃L�[�t���[���̑�����������
			if (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].bLoop == true)
			{// ���[�v���锻�肾������
				g_Player[nIdxPlayer].nKey = 0;             // ���݂̃L�[�t���[�������ɖ߂�
														   // �L�[�t���[���؂�ւ�����
				SwitchKey(nIdxPlayer);
			}
			else
			{// ���[�v���Ȃ����肾������
				if (g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE || g_Player[nIdxPlayer].state == PLAYERSTATE_LANDING || g_Player[nIdxPlayer].state == PLAYERSTATE_PANCH || g_Player[nIdxPlayer].state == PLAYERSTATE_KICK)
				{// ���n��Ԃ��A�N�V������Ԃ�������
					g_Player[nIdxPlayer].state = PLAYERSTATE_NORMAL;  // �ʏ��Ԃ�

																	  // ���[�V�����؂�ւ�����
					SwitchMotion(nIdxPlayer);
				}
				else if (g_Player[nIdxPlayer].state == PLAYERSTATE_GRAB)
				{// �c�^���܂胂�[�V������������
					g_Player[nIdxPlayer].state = PLAYERSTATE_GRABNOR;  // �c�^�j���[�g������Ԃ�

																	   // ���[�V�����؂�ւ�����
					SwitchMotion(nIdxPlayer);
				}
				else
				{// ����ȊO�̃��[�V�����Ȃ��
					g_Player[nIdxPlayer].mState = MOTIONSTATE_STOP;
				}
			}
		}
		else
		{
			g_Player[nIdxPlayer].nKey++;         // ���݂̃L�[�t���[����i�߂�

												 // �L�[�t���[���؂�ւ�����
			SwitchKey(nIdxPlayer);
		}
		g_Player[nIdxPlayer].nMotionCounter = 0;   // �J�E���^�[��߂�
	}
}
//=============================================================================
// �L�[�t���[���؂�ւ�����
//=============================================================================
void SwitchKey(int nIdxPlayer)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�����J��Ԃ�
	 // �ڕW�̍��W�ݒ�
		g_Player[nIdxPlayer].aModel[nCntModel].posDiff.x = g_Player[nIdxPlayer].aModel[nCntModel].posStd.x - (g_Player[nIdxPlayer].aModel[nCntModel].pos.x - g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].posAdd[nCntModel].x);
		g_Player[nIdxPlayer].aModel[nCntModel].posDiff.y = g_Player[nIdxPlayer].aModel[nCntModel].posStd.y - (g_Player[nIdxPlayer].aModel[nCntModel].pos.y - g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].posAdd[nCntModel].y);
		g_Player[nIdxPlayer].aModel[nCntModel].posDiff.z = g_Player[nIdxPlayer].aModel[nCntModel].posStd.z - (g_Player[nIdxPlayer].aModel[nCntModel].pos.z - g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].posAdd[nCntModel].z);

		// �p�x�̍����̏C��
		g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x = g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].DestAngle[nCntModel].x - g_Player[nIdxPlayer].aModel[nCntModel].rot.x;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x += D3DX_PI * 2.0f;
		}
		// �p�x�̍����̏C��
		g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y = g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].DestAngle[nCntModel].y - g_Player[nIdxPlayer].aModel[nCntModel].rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y += D3DX_PI * 2.0f;
		}

		// �p�x�̍����̏C��
		g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z = g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].DestAngle[nCntModel].z - g_Player[nIdxPlayer].aModel[nCntModel].rot.z;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z += D3DX_PI * 2.0f;
		}
	}
}

//=============================================================================
// ���[�V�����؂�ւ�����
//=============================================================================
void SwitchMotion(int nIdxPlayer)
{

	g_Player[nIdxPlayer].nMotionCounter = 0;          // ���[�V�����J�E���^�[�����Z�b�g
	g_Player[nIdxPlayer].nKey = 0;                    // ���݂̃L�[�t���[�������Z�b�g
	g_Player[nIdxPlayer].mState = MOTIONSTATE_SWITCH; // ���[�V�����؂�ւ���Ԃ�

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�����J��Ԃ�
	 // �ڕW�̍��W�ݒ�
		g_Player[nIdxPlayer].aModel[nCntModel].posDiff.x = g_Player[nIdxPlayer].aModel[nCntModel].posStd.x - (g_Player[nIdxPlayer].aModel[nCntModel].pos.x - g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].posAdd[nCntModel].x);
		g_Player[nIdxPlayer].aModel[nCntModel].posDiff.y = g_Player[nIdxPlayer].aModel[nCntModel].posStd.y - (g_Player[nIdxPlayer].aModel[nCntModel].pos.y - g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].posAdd[nCntModel].y);
		g_Player[nIdxPlayer].aModel[nCntModel].posDiff.z = g_Player[nIdxPlayer].aModel[nCntModel].posStd.z - (g_Player[nIdxPlayer].aModel[nCntModel].pos.z - g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].posAdd[nCntModel].z);

		// �p�x�̍����̏C��
		g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x = g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].DestAngle[nCntModel].x - g_Player[nIdxPlayer].aModel[nCntModel].rot.x;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x += D3DX_PI * 2.0f;
		}
		// �p�x�̍����̏C��
		g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y = g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].DestAngle[nCntModel].y - g_Player[nIdxPlayer].aModel[nCntModel].rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y += D3DX_PI * 2.0f;
		}

		// �p�x�̍����̏C��
		g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z = g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].DestAngle[nCntModel].z - g_Player[nIdxPlayer].aModel[nCntModel].rot.z;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z += D3DX_PI * 2.0f;
		}
	}
}
//=============================================================================
// �v���C���[�̎擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player[g_PlayerPossible];
}

//=============================================================================
// �v���C���[���m�̓����蔻��
//=============================================================================
void CollisionPlayer(int nIdxParts, int nAttackNum, int nDiffenceNum)
{
	if (g_Player[nAttackNum].aModel[nIdxParts].mtxWorld._42 - 20.0f < g_Player[nDiffenceNum].pos.y + 50.0f
		&& g_Player[nAttackNum].aModel[nIdxParts].mtxWorld._42 + 20.0f > g_Player[nDiffenceNum].pos.y)
	{// �U�����������h�q����Y���W�̒��ɂ���
		if (g_Player[nAttackNum].aModel[nIdxParts].mtxWorld._43 - 15.0f < g_Player[nDiffenceNum].pos.z + 15.0f
			&& g_Player[nAttackNum].aModel[nIdxParts].mtxWorld._43 + 15.0f >  g_Player[nDiffenceNum].pos.z - 15.0f)
		{// �U�����������h�q����Z���W�̒��ɂ���
			if (g_Player[nAttackNum].aModel[nIdxParts].mtxWorld._41 - 17.0f < g_Player[nDiffenceNum].pos.x + 17.0f
				&& g_Player[nAttackNum].aModel[nIdxParts].mtxWorld._41 + 17.0f >  g_Player[nDiffenceNum].pos.x - 17.0f)
			{// �U�����������h�q����X���W�̒��ɂ���
				if (g_Player[nDiffenceNum].state != PLAYERSTATE_DAMAGE)
				{// �h�q�����_���[�W��ԂłȂ�
					HitPlayer(nAttackNum, nDiffenceNum);
				}
			}
		}
	}
}
//=============================================================================
// �v���C���[�̃_���[�W����
//=============================================================================
void HitPlayer(int nAttackNum, int nDiffenceNum)
{
	PlaySound(SOUND_LABEL_SE006);
	// �Ԃ���я���
	g_Player[nDiffenceNum].move.x -= sinf(g_Player[nAttackNum].rot.y) * 15.0f;
	g_Player[nDiffenceNum].move.y += 10.0f;
	g_Player[nDiffenceNum].move.z -= cosf(g_Player[nAttackNum].rot.y) * 15.0f;

	g_Player[nDiffenceNum].DestAngle.y = g_Player[nAttackNum].rot.y + D3DX_PI;

	if (g_Player[nDiffenceNum].DestAngle.y > D3DX_PI)
	{// ���݂̌�����D3DX_PI�𒴂���
		g_Player[nDiffenceNum].DestAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nDiffenceNum].DestAngle.y < -D3DX_PI)
	{// ���݂̌�����-D3DX_PI�𒴂���
		g_Player[nDiffenceNum].DestAngle.y += D3DX_PI * 2.0f;
	}

	for (int nCntParticle = 0; nCntParticle < 50; nCntParticle++)
	{// ����������p�[�e�B�N���̐������J��Ԃ�
		SetParticle(D3DXVECTOR3(g_Player[nDiffenceNum].aModel[0].mtxWorld._41, g_Player[nDiffenceNum].aModel[0].mtxWorld._42, g_Player[nDiffenceNum].aModel[0].mtxWorld._43), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f), 12.0f, 100);
	}

	g_Player[nDiffenceNum].state = PLAYERSTATE_DAMAGE;   // �_���[�W��Ԃ�
														 // ���[�V�����؂�ւ�����
	SwitchMotion(nDiffenceNum);
}

//=============================================================================
// �v���C���[�̈ړ��t���O�Ǘ�
//=============================================================================
void SetPlayerMoveFlag(bool bFlag)
{
	g_bPlayerMoveFlag = bFlag;
}

//=============================================================================
// �v���C���[�̌�㏈��
//=============================================================================
void PlayerChange(int nIdxPlayer)
{
	g_Player[nIdxPlayer].move.y = 0.0f;               // �d�͂𖳎�
	g_Player[nIdxPlayer].move.x = 0.0f;               // �ړ��𖳎�
	g_Player[nIdxPlayer].move.z = 0.0f;               // �ړ��𖳎�
	g_Player[nIdxPlayer].state = PLAYERSTATE_NORMAL;  // �ʏ��Ԃɂ���
	g_Player[nIdxPlayer].bJump = false;               // �W�����v���Ă��Ȃ���Ԃ�
	g_Player[nIdxPlayer].bGrab = false;               // �c�^�ɂ��܂��Ă��Ȃ���Ԃ�

	if (g_Player[nIdxPlayer].pMasu != NULL)
	{
		switch (g_Player[nIdxPlayer].pMasu->masuType)
		{
			// �ʏ�}�X
		case MASUTYPE_NORMAL:
			g_Player[nIdxPlayer].fJumpPower = JUMP_NORMAL;
			g_Player[nIdxPlayer].fMovement = MOVE_NORMAL;
			break;
			// �W�����vUP�}�X
		case MASUTYPE_JUMP_UP:
			g_Player[nIdxPlayer].fJumpPower = JUMP_UP;
			g_Player[nIdxPlayer].fMovement = MOVE_NORMAL;
			break;
			// �W�����vDOWN�}�X
		case MASUTYPE_JUMP_DOWN:
			g_Player[nIdxPlayer].fJumpPower = JUMP_DOWN;
			g_Player[nIdxPlayer].fMovement = MOVE_NORMAL;
			break;
			// �ړ�UP�}�X
		case MASUTYPE_SPEED_UP:
			g_Player[nIdxPlayer].fJumpPower = JUMP_NORMAL;
			g_Player[nIdxPlayer].fMovement = MOVE_UP;
			break;

			// �ړ�UP�}�X
		case MASUTYPE_SPEED_DOWN:
			g_Player[nIdxPlayer].fJumpPower = JUMP_NORMAL;
			g_Player[nIdxPlayer].fMovement = MOVE_DOWN;
			break;
		}
	}

	g_Player[nIdxPlayer].bDisp = false;  // �`�悵�Ȃ���Ԃɂ���

	g_Player[nIdxPlayer].ShadowCol.a = 0.0f;  // �e������

	//if (g_Player[nIdxPlayer ^ 1].pMasu != NULL)
	//{
	//	g_Player[nIdxPlayer ^ 1].pos = g_Player[nIdxPlayer ^ 1].pMasu->pos;
	//}
	//else
	//{
	//	g_Player[nIdxPlayer ^ 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//}
	// �e�̐F�X�V
	SetColShadow(g_Player[nIdxPlayer].nIdxShadow, g_Player[nIdxPlayer].ShadowCol);

	for (int nCntParticle = 0; nCntParticle < 15; nCntParticle++)
	{// ����������p�[�e�B�N���̐������J��Ԃ�
		SetParticle(g_Player[nIdxPlayer].pos, D3DXCOLOR(rand() % 10 / 10.0f, rand() % 10 / 10.0f, rand() % 10 / 10.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 4.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 4.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 4.5f), 30.0f, 100);
	}


	//�����삷��L�����̈ʒu��߂�
	g_Player[nIdxPlayer ^ 1].pos = g_Player[nIdxPlayer ^ 1].pMasu->pos;

}
//=============================================================================
// �v���C���[�ԍ��擾����
//=============================================================================
int GetIdxPlayer(void)
{
	return g_PlayerPossible;
}

//=============================================================================
// �v���C���[�Ɠ������̂̓����蔻��
//=============================================================================
void CollisionMoveOb(D3DXVECTOR3 Pos, D3DXVECTOR3 PosOld, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, int nIdxPlayer)
{
	if (g_Player[nIdxPlayer].pos.y < Pos.y + vtxMax.y && g_Player[nIdxPlayer].pos.y + g_Player[nIdxPlayer].radius.y > Pos.y + vtxMax.y
		|| g_Player[nIdxPlayer].pos.y < Pos.y + vtxMin.y && g_Player[nIdxPlayer].pos.y + g_Player[nIdxPlayer].radius.y > Pos.y + vtxMin.y
		|| g_Player[nIdxPlayer].pos.y > Pos.y + vtxMin.y && g_Player[nIdxPlayer].pos.y + g_Player[nIdxPlayer].radius.y < Pos.y + vtxMax.y)
	{// �������̂�Y���W���Ƀv���C���[������
		if (g_Player[nIdxPlayer].pos.z + g_Player[nIdxPlayer].radius.z > PosOld.z + vtxMin.z && g_Player[nIdxPlayer].pos.z - g_Player[nIdxPlayer].radius.z < PosOld.z + vtxMax.z)
		{// �������̂�Z���W���Ƀv���C���[������
			if (PosOld.x + vtxMin.x >= g_Player[nIdxPlayer].pos.x + g_Player[nIdxPlayer].radius.x - 5.0f && Pos.x + vtxMin.x < g_Player[nIdxPlayer].pos.x + g_Player[nIdxPlayer].radius.x
				|| g_Player[nIdxPlayer].posold.x + g_Player[nIdxPlayer].radius.x <= PosOld.x + vtxMin.x - 5.0f && g_Player[nIdxPlayer].pos.x + g_Player[nIdxPlayer].radius.x > Pos.x + vtxMin.x)
			{// �������̂̍�������v���C���[�����܂���
				g_Player[nIdxPlayer].pos.x = Pos.x + vtxMin.x - g_Player[nIdxPlayer].radius.x;
			}
			else if (PosOld.x + vtxMax.x <= g_Player[nIdxPlayer].pos.x - g_Player[nIdxPlayer].radius.x + 5.0f && Pos.x + vtxMax.x > g_Player[nIdxPlayer].pos.x - g_Player[nIdxPlayer].radius.x
				|| g_Player[nIdxPlayer].posold.x - g_Player[nIdxPlayer].radius.x + 5.0f >= PosOld.x + vtxMax.x && g_Player[nIdxPlayer].pos.x - g_Player[nIdxPlayer].radius.x < Pos.x + vtxMax.x)
			{// �������̂̉E������v���C���[�����܂���
				g_Player[nIdxPlayer].pos.x = Pos.x + vtxMax.x + g_Player[nIdxPlayer].radius.x;
			}
		}
		if (g_Player[nIdxPlayer].pos.x + g_Player[nIdxPlayer].radius.x >= PosOld.x + vtxMin.x && g_Player[nIdxPlayer].pos.x - g_Player[nIdxPlayer].radius.x <= PosOld.x + vtxMax.x)
		{// �������̂�X���W���Ƀv���C���[������
			if (PosOld.z + vtxMin.z >= g_Player[nIdxPlayer].pos.z + g_Player[nIdxPlayer].radius.z - 5.0f && Pos.z + vtxMin.z < g_Player[nIdxPlayer].pos.z + g_Player[nIdxPlayer].radius.z
				|| PosOld.z + vtxMin.z >= g_Player[nIdxPlayer].posold.z + g_Player[nIdxPlayer].radius.z - 5.0f && Pos.z + vtxMin.z < g_Player[nIdxPlayer].pos.z + g_Player[nIdxPlayer].radius.z)
			{// �������̂̑O������v���C���[�����܂���
				g_Player[nIdxPlayer].pos.z = Pos.z + vtxMin.z - g_Player[nIdxPlayer].radius.z - 1.0f;
			}
			else if (PosOld.z + vtxMax.z <= g_Player[nIdxPlayer].pos.z - g_Player[nIdxPlayer].radius.z + 5.0f && Pos.z + vtxMax.z > g_Player[nIdxPlayer].pos.z - g_Player[nIdxPlayer].radius.z
				|| PosOld.z + vtxMax.z <= g_Player[nIdxPlayer].posold.z - g_Player[nIdxPlayer].radius.z + 5.0f && Pos.z + vtxMax.z > g_Player[nIdxPlayer].pos.z - g_Player[nIdxPlayer].radius.z)
			{// �������̂̌�둤����v���C���[�����܂���
				g_Player[nIdxPlayer].pos.z = Pos.z + vtxMax.z + g_Player[nIdxPlayer].radius.z + 1.0f;
			}
		}
	}
	else
	{// Y���W�̒��ɂ��Ȃ�
		if (g_Player[nIdxPlayer].pos.x + g_Player[nIdxPlayer].radius.x <= Pos.x + vtxMax.x && g_Player[nIdxPlayer].pos.x - g_Player[nIdxPlayer].radius.x >= Pos.x + vtxMin.x
			&& g_Player[nIdxPlayer].pos.z + g_Player[nIdxPlayer].radius.z <= Pos.z + vtxMax.z && g_Player[nIdxPlayer].pos.z - g_Player[nIdxPlayer].radius.z >= Pos.z + vtxMin.z
			&& g_Player[nIdxPlayer].pos.x + g_Player[nIdxPlayer].radius.x <= PosOld.x + vtxMax.x && g_Player[nIdxPlayer].pos.x - g_Player[nIdxPlayer].radius.x >= PosOld.x + vtxMin.x
			&& g_Player[nIdxPlayer].pos.z + g_Player[nIdxPlayer].radius.z <= PosOld.z + vtxMax.z && g_Player[nIdxPlayer].pos.z - g_Player[nIdxPlayer].radius.z >= PosOld.z + vtxMin.z)
		{// �������̂̒��ɂ���
			if (g_Player[nIdxPlayer].posold.y >= Pos.y + vtxMax.y && g_Player[nIdxPlayer].posold.y <= Pos.y + vtxMax.y
				|| g_Player[nIdxPlayer].pos.y >= Pos.y + vtxMax.y && g_Player[nIdxPlayer].pos.y <= Pos.y + vtxMax.y
				|| g_Player[nIdxPlayer].posold.y >= PosOld.y + vtxMax.y && g_Player[nIdxPlayer].posold.y <= PosOld.y + vtxMax.y
				|| g_Player[nIdxPlayer].pos.y >= PosOld.y + vtxMax.y && g_Player[nIdxPlayer].pos.y <= PosOld.y + vtxMax.y)
			{// ���n����
				g_Player[nIdxPlayer].pos.y = Pos.y + vtxMax.y;
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;
				// ���[�V�����؂�ւ�����
				SwitchMotion(nIdxPlayer);
			}
		}
	}
}