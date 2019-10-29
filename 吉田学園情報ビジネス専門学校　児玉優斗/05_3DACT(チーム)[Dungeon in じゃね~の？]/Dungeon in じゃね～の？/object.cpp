//=============================================================================
//
// �I�u�W�F�N�g�̔z�u�̏��� [object.cpp]
// Author : �ݓc��(Kishida Rei)
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "object.h"
#include "manager.h"
#include "renderer.h"
#include "sceneX.h"
#include "input.h"
#include "debugproc.h"
#include "itemcounter.h"
#include "meshfield.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_FILE_NAME			("data/TEXT/object_data.txt")		// X�t�@�C���̃A�h���X
#define MAX_CHAR (256)	// �������̍ő吔
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
char *CObject::m_pModelName[MAXMODEL_TYPE] = {};
int	 CObject::m_nMaxModelNum = 0;
LPDIRECT3DTEXTURE9 CObject::m_apTexture[MAX_TEXTURE_OBJ] = {}; //���L�e�N�X�`���̃|�C���^

//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CObject::CObject(int nPriority, OBJTYPE type) : CSceneX(nPriority, type)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu�̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu�̈ړ��ʂ̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �����̏�����
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړI�̌�����������
}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�Ō�ɌĂяo�����
//=============================================================================
CObject::~CObject()
{

}


//=============================================================================
// �֐����F�g�p����e�N�X�`���̓ǂݍ���
// �֐��̊T�v�F--
//=============================================================================
HRESULT CObject::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/coin_UV.jpg", &m_apTexture[0]);		// �R�C��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/key02.jpg", &m_apTexture[1]);			// �J�M
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/wood01.png", &m_apTexture[2]);			// ��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/sky222.png", &m_apTexture[3]);			// ��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/cloud.png", &m_apTexture[4]);			// �_
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/skyObj_UI.png", &m_apTexture[5]);		// �_
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/D_UV222_.png", &m_apTexture[6]);		// �_���W����
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UV_DOOR.jpg", &m_apTexture[7]);		// �h�A
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/skyObj_UI.png", &m_apTexture[8]);		// �_


	return S_OK;

}

//=============================================================================
// �֐����F�g�p�����e�N�X�`���̔j��
// �֐��̊T�v�F--
//=============================================================================
void CObject::Unload(void)
{
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE_OBJ; nCntTexture++)
	{
		m_apTexture[nCntTexture]->Release();
		m_apTexture[nCntTexture] = NULL;
	}
}


//=============================================================================
// �֐����F���f���̐���
// �֐��̊T�v�F���f���𐶐�����
//=============================================================================
CObject *CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type)
{
	CObject  *pModel;
	pModel = new CObject;//�V�[���N���X�̐���
	if (pModel != NULL)
	{
		pModel->m_nTypeModel = type;
		pModel->m_pos = pos;
		pModel->m_rot = rot;
		pModel->m_fHeight = 100.0f;
		//������
		pModel->Init();
	}
	return pModel;
}

//=============================================================================
// �֐����F���f���̏���������
// �֐��̊T�v�F���f���̏�����
//=============================================================================
HRESULT CObject::Init(void)
{
	//�ʒu���̑��
	SetPos(m_pos);

	//�p�x���̑��
	SetRot(m_rot);

	//�t�@�C�����̊��蓖��
	BindFileName(m_pModelName[m_nTypeModel]);

	//����������
	CSceneX::Init();

	//�e�N�X�`���̊��蓖��
	BindTexture(m_apTexture[m_nTypeModel]);

	m_vtxMax = GetVtxMax();		//�ő咸�_���W�̎擾
	m_vtxMin = GetVtxMin();		//�ŏ����_���W�̎擾

	return S_OK;
}

//=============================================================================
// �֐����F���f���̏I������
// �֐��̊T�v�F���f���̏I��
//=============================================================================
void CObject::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// �֐����F���f���̍X�V
// �֐��̊T�v�F--
//=============================================================================
void CObject::Update(void)
{
	//�f�o�C�X�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//���b�V���t�B�[���h�擾
	CMeshField *pMeshField;
	pMeshField = CGame::GetSceneMeshField();


	switch (m_nTypeModel)
	{
	case OBJECTTYPE_COIN:	// �R�C��
		m_rot.y += 0.05f;
		//m_pos.y = pMeshField->GetHeight(m_pos);
		break;
	case OBJECTTYPE_KEY:	// �J�M
		m_rot.y += 0.05f;
		//m_pos.y = pMeshField->GetHeight(m_pos);
		break;
	case OBJECTTYPE_WOOD:	// ��
		break;
	case OBJECTTYPE_SKY:	// ��
		m_rot.x -= 0.0006f;
		break;
	case OBJECTTYPE_CLOUD:	// �_
		m_rot.y += 0.001f;
		break;
	case OBJECTTYPE_GOAL:	// �S�[��
		break;
	}
	//�p�x���̑��
	SetRot(m_rot);

	//�ʒu���̑��
	SetPos(m_pos);
}

//=============================================================================
// �֐����F���f���̕`�揈��
// �֐��̊T�v�F�K�w�\���ŕ`��
//=============================================================================
void CObject::Draw(void)
{
	//���f���̕`��
	CSceneX::Draw();
}




//=============================================================================
// �֐����F���f���̏��̓ǂݍ��ݏ���
// �֐��̊T�v�F�e�L�X�g�t�@�C�����烂�f������ǂݍ���
//=============================================================================
void CObject::LoadModelText(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();
	//D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

	FILE *pFile = fopen(MODEL_FILE_NAME, "r");		// �ǂݍ��ރe�L�X�g�t�@�C���̃A�h���X

	// �ǂݍ��ނ��߂̕ϐ��錾
	char acLine[MAX_CHAR];							// 1�s���ǂݍ��ޕϐ�
	char acData[MAX_CHAR];							// 1����ǂݍ��ޕϐ�
	char cFileName[MAXMODEL_TYPE][MAX_CHAR];		// �ǂݍ���
	int nCntModel = 0;								// �ǂݍ��ރ��f���̐�
	int nCntTexture = 0;							// �ǂݍ��ރe�N�X�`����
	int nTypeModel;									// �g�p���郂�f���̃^�C�v
	int nMaxModel = 0;								// ���f���̍ő吔
	D3DXVECTOR3 pos;								// �ʒu������ϐ�
	D3DXVECTOR3 rot;								// ����������ϐ�

	if (pFile != NULL)
	{// �k���`�F�b�N
		while (fgets(&acLine[0], MAX_CHAR, pFile) != NULL)
		{
			sscanf(&acLine[0], "%s", &acData);				// �����f�[�^�ɃR�s�[

			if (strcmp(acData, "NUM_MODEL") == 0)
			{// "NUM_MODEL"�̕����񂪂�������
				sscanf(&acLine[0], "%s %s %d", &acData[0], &acData[0], &nMaxModel);	// ���f���̐����擾
			}
			if (strcmp(acData, "MODEL_FILENAME") == 0)
			{// "MODEL_FILENAME"�̕����񂪂�������
				sscanf(&acLine[0], "%s %s %s", &acData[0], &acData[0], &cFileName[nCntModel][0]);	// ���f���̐����擾
				m_pModelName[nCntModel] = &cFileName[nCntModel][0];//�t�@�C�����̑��
				nCntModel++;		// ���f���������Z
			}
			if (strcmp(acData, "MODELSET") == 0)
			{// "MODELSET"�̕����񂪂�������

				while (strcmp(acData, "END_MODELSET") != 0)
				{// "END_MODELSET"���܂ŏ����擾��������
					fgets(&acLine[0], MAXCHAR, pFile);					// �s���擾
					sscanf(&acLine[0], "%s", &acData);					// �f�[�^���R�s�[

					if (strcmp(acData, "TYPE") == 0)
					{// "TYPE"�̕����񂪂�������
						sscanf(&acLine[0], "%s %s %d", &acData[0], &acData[0], &nTypeModel);					// �g�p���郂�f���̔ԍ����擾
					}
					else if (strcmp(acData, "POS") == 0)
					{// "POS"�̕����񂪂�������
						sscanf(&acLine[0], "%s %s %f %f %f", &acData[0], &acData[0], &pos.x, &pos.y, &pos.z);	// �ʒu���擾
					}
					else if (strcmp(acData, "ROT") == 0)
					{// "ROT"�̕����񂪂�������
						sscanf(&acLine[0], "%s %s %f %f %f", &acData[0], &acData[0], &rot.x, &rot.y, &rot.z);	// �������擾
						//�e�L�X�g�̊p�x���ʂ�ɓ����v�Z
						rot.x = (D3DX_PI * 2 / 360.0f * rot.x);
						rot.y = (D3DX_PI * 2 / 360.0f * rot.y);
						rot.z = (D3DX_PI * 2 / 360.0f * rot.z);
					}
				}
				//���f���̐���
				Create(pos, rot, nTypeModel);
			}
		}
		fclose(pFile);	// �J�����t�@�C�������
	}
}

//=============================================================================
// �֐����F���f���Ƃ̓����蔻�菈��
// �֐��̊T�v�F�߂肱�񂾂�߂�����
//=============================================================================
bool CObject::CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadius)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();


	//�t�F�[�h�̎擾
	CFade::FADE pFade;
	pFade = CFade::GetFade();

	int nKey;
	nKey = CItemCounter::GetKey();

	bool bRand = false;			// ���n�������ǂ���
	//----------------------------------------------------------
	// ��`�ł̓����蔻��
	//----------------------------------------------------------
	if (m_pos.y + m_vtxMax.y > pPos->y + fRadius &&
		m_pos.y + m_vtxMin.y <= pPos->y + fRadius)
	{// �v���C���[���I�u�W�F�N�g�͈͓̔��Ȃ�

	 // �u���b�N�̓����蔻��
		if (m_pos.x + m_vtxMin.x < pPos->x + fRadius &&
			m_pos.x + m_vtxMax.x > pPos->x - fRadius)
		{// �I�u�W�F�N�g���I�u�W�F�N�g��Z���͈͓̔��ɓ�������

			if (m_pos.z + m_vtxMin.z >= pPosOld->z + fRadius &&
				m_pos.z + m_vtxMin.z < pPos->z + fRadius)
			{// ��O����̔���
				if (m_nTypeModel == OBJECTTYPE_COIN)
				{//�R�C���ɂӂꂽ�Ƃ�
					CItemCounter::AddCoin(1);
					Uninit();
				}
				else if (m_nTypeModel == OBJECTTYPE_KEY)
				{//�J�M�ɂӂꂽ�Ƃ�
					pSound->PlaySound(CSound::SOUND_LABEL_SE_PICKUP);
					CItemCounter::AddKey(1);
					Uninit();
				}
				else if (m_nTypeModel == OBJECTTYPE_GOAL)
				{//�h�A�ɂӂꂽ�Ƃ�
					if (nKey >= 6)
					{
						if (pFade == CFade::FADE_NONE)
						{
							CFade::SetFade(CManager::MODE_RESULT);//���U���g�ֈڍs
						}
					}
				}
				else
				{
					pPos->z = m_pos.z + m_vtxMin.z - fRadius;			// �I�u�W�F�N�g�̈ʒu��߂�
				}
			}
			else if (m_pos.z + m_vtxMax.z <= pPosOld->z - fRadius &&
				m_pos.z + m_vtxMax.z > pPos->z - fRadius)
			{// ������̔���
				if (m_nTypeModel == OBJECTTYPE_COIN)
				{//�R�C���ɂӂꂽ�Ƃ�
					CItemCounter::AddCoin(1);
					Uninit();
				}
				else if (m_nTypeModel == OBJECTTYPE_KEY)
				{//�J�M�ɂӂꂽ�Ƃ�
					pSound->PlaySound(CSound::SOUND_LABEL_SE_PICKUP);
					CItemCounter::AddKey(1);
					Uninit();
				}
				else if (m_nTypeModel == OBJECTTYPE_GOAL)
				{//�h�A�ɂӂꂽ�Ƃ�
					if (nKey >= 6)
					{
						if (pFade == CFade::FADE_NONE)
						{
							CFade::SetFade(CManager::MODE_RESULT);//���U���g�ֈڍs
						}
					}
				}
				else
				{
					pPos->z = m_pos.z + m_vtxMax.z + fRadius;			// �I�u�W�F�N�g�̈ʒu��߂�
				}
			}

		}
		if (m_pos.z + m_vtxMin.z < pPos->z + fRadius &&
			m_pos.z + m_vtxMax.z > pPos->z - fRadius)
		{// Z�����I�u�W�F�N�g�͈͓̔���������
			if (m_pos.x + m_vtxMin.x >= pPosOld->x + fRadius &&
				m_pos.x + m_vtxMin.x < pPos->x + fRadius)
			{// ������̔���
				if (m_nTypeModel == OBJECTTYPE_COIN)
				{//�R�C���ɂӂꂽ�Ƃ�
					CItemCounter::AddCoin(1);
					Uninit();
				}
				else if (m_nTypeModel == OBJECTTYPE_KEY)
				{//�J�M�ɂӂꂽ�Ƃ�
					pSound->PlaySound(CSound::SOUND_LABEL_SE_PICKUP);
					CItemCounter::AddKey(1);
					Uninit();
				}
				else if (m_nTypeModel == OBJECTTYPE_GOAL)
				{//�h�A�ɂӂꂽ�Ƃ�
					if (nKey >= 6)
					{
						if (pFade == CFade::FADE_NONE)
						{
							CFade::SetFade(CManager::MODE_RESULT);//���U���g�ֈڍs
						}
					}
				}
				else
				{
					pPos->x = m_pos.x + m_vtxMin.x - fRadius;			// �I�u�W�F�N�g�̈ʒu��߂�
				}
			}
			else if (m_pos.x + m_vtxMax.x <= pPosOld->x - fRadius &&
				m_pos.x + m_vtxMax.x > pPos->x - fRadius)
			{// �E����̔���
				if (m_nTypeModel == OBJECTTYPE_COIN)
				{//�R�C���ɂӂꂽ�Ƃ�
					CItemCounter::AddCoin(1);
					Uninit();
				}
				else if (m_nTypeModel == OBJECTTYPE_KEY)
				{//�J�M�ɂӂꂽ�Ƃ�
					pSound->PlaySound(CSound::SOUND_LABEL_SE_PICKUP);
					CItemCounter::AddKey(1);
					Uninit();
				}
				else if (m_nTypeModel == OBJECTTYPE_GOAL)
				{//�h�A�ɂӂꂽ�Ƃ�
					if (nKey >= 6)
					{
						if (pFade == CFade::FADE_NONE)
						{
							CFade::SetFade(CManager::MODE_RESULT);//���U���g�ֈڍs
						}
					}
				}
				else
				{
					pPos->x = m_pos.x + m_vtxMax.x + fRadius;			// �I�u�W�F�N�g�̈ʒu��߂�
				}
			}
		}
	}
	if (m_pos.x + m_vtxMin.x < pPos->x + fRadius &&
		m_pos.x + m_vtxMax.x > pPos->x - fRadius &&
		m_pos.z + m_vtxMin.z < pPos->z + fRadius &&
		m_pos.z + m_vtxMax.z > pPos->z - fRadius)
	{// �I�u�W�F�N�g�͈͓̔���������
		if (m_pos.y + m_vtxMax.y <= pPosOld->y &&
			m_pos.y + m_vtxMax.y > pPos->y)
		{// �ォ��̔���
			if (m_nTypeModel == OBJECTTYPE_COIN)
			{//�R�C���ɂӂꂽ�Ƃ�
				CItemCounter::AddCoin(1);
				Uninit();
			}
			else if (m_nTypeModel == OBJECTTYPE_GOAL)
			{//�h�A�ɂӂꂽ�Ƃ�
				if (nKey >= 6)
				{
					if (pFade == CFade::FADE_NONE)
					{
						CFade::SetFade(CManager::MODE_RESULT);//���U���g�ֈڍs
					}
				}
			}
			else if (m_nTypeModel == OBJECTTYPE_KEY)
			{//�J�M�ɂӂꂽ�Ƃ�
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PICKUP);
				CItemCounter::AddKey(1);
				Uninit();
			}
			pPos->y = m_pos.y + m_vtxMax.y;					// �I�u�W�F�N�g�̈ʒu��߂�
			pMove->y = 0.0f;								// �������x��0.0�ɖ߂�
			bRand = true;									// ���n��������ɂ���
		}
	}

	return bRand;
}


//=============================================================================
// �֐����F�S�[���Ƃ̓����蔻��
// �֐��̊T�v�F�v���C���[�����a�ɓ����Ă�����true��Ԃ�
//=============================================================================
bool CObject::CollisionGoal(D3DXVECTOR3 *pos, D3DXVECTOR3 *move, D3DXVECTOR3 *rot)
{
	bool bCol = false;

	float fLength = powf((pos->x - m_pos.x)*(pos->x - m_pos.x) + (pos->z - m_pos.z)*(pos->z - m_pos.z), 0.5f);	//�v���C���[�Ƃ̋���
	float fRadius = powf(30.0f, 1.0f);	//���a

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
