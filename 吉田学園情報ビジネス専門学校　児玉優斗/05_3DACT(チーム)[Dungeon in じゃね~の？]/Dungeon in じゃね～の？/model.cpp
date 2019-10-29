//=============================================================================
//
// �V�[��X����[3D�|���S��] [scene3D.cpp]
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
#include "model.h"
#include "scene2D.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_CHAR (256)
#define GRAVITY_NUM (0.7f)
#define MODEL_FILENAME ("data/TEXT/model_data.txt")

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
char CModel::m_acFileName[MAX_PARTS][256] = {};		// �ǂݍ��ރ��f���̖��O
//LPDIRECT3DTEXTURE9	*CModel::m_apTexture[MAX_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH CModel::m_apMesh[MAX_PARTS] = {};	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CModel::m_apBuffMat[MAX_PARTS] = {};	//�}�e���A�����ւ̃|�C���^
DWORD CModel::m_aNumMat[MAX_PARTS] = {};	//�}�e���A���̏��̐�


//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CModel::CModel()
{

}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�Ō�ɌĂяo�����
//=============================================================================
CModel::~CModel()
{
}


//=============================================================================
// �֐����F�v���C���[�̃p�[�c�ǂݍ���
// �֐��̊T�v�F�p�[�c��ǂݍ���
//=============================================================================
void CModel::Load(void)
{

	FILE *pFile = fopen(MODEL_FILENAME, "r");		// �ǂݍ��ރe�L�X�g�t�@�C���̃A�h���X

													// �ǂݍ��ނ��߂̕ϐ��錾
	char acLine[MAX_CHAR];							// 1�s���ǂݍ��ޕϐ�
	char acData[MAX_CHAR];							// 1����ǂݍ��ޕϐ�
	int nCntModel = 0;								// �ǂݍ��ރ��f���̐�
	int nCntTexture = 0;							// �ǂݍ��ރe�N�X�`����
	int nIndex = 0;									// �g�p���郂�f���̃^�C�v
	int nParent = 0;								//�e�̐���
	int nMaxParts = 0;								//�p�[�c��
	D3DXVECTOR3 pos;								// �ʒu������ϐ�
	D3DXVECTOR3 rot;								// ����������ϐ�
	int nCntParts = 0;								//�p�[�c�̃J�E���g

	if (pFile != NULL)
	{// �k���`�F�b�N

		while (fgets(&acLine[0], MAX_CHAR, pFile) != NULL)
		{
			sscanf(&acLine[0], "%s", &acData);				// �����f�[�^�ɃR�s�[

			if (strcmp(acData, "NUM_MODEL") == 0)
			{// "NUM_MODEL"�̕����񂪂�������
				sscanf(&acLine[0], "%s %s %d", &acData[0], &acData[0], &nMaxParts);	// ���f���̐����擾
			}
			else if (strcmp(acData, "MODEL_FILENAME") == 0)
			{// "MODEL_FILENAME"�̕����񂪂�������
				sscanf(&acLine[0], "%s %s %s", &acData[0], &acData[0], &m_acFileName[nCntModel][0]);	// ���f���̐����擾
				nCntModel++;		// ���f���������Z
			}
		}
		fclose(pFile);								// �J�����t�@�C�������
	}
}

//=============================================================================
// �֐����F�v���C���[�̃p�[�c�̔j��
// �֐��̊T�v�F�p�[�c��ǂݍ���
//=============================================================================
void CModel::Unload(void)
{
	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		m_acFileName[nCntModel][0] = NULL;
	}
}


//=============================================================================
// �֐����FX�t�@�C���V�[���̐���
// �֐��̊T�v�FX�t�@�C���V�[���𐶐�����
//=============================================================================
CModel *CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumParts, MODELTYPE type)
{
	CModel  *pModel;
	pModel = new CModel;//�V�[���N���X�̐���
	if (pModel != NULL)
	{
		pModel->m_nNumParts = nNumParts;
		pModel->m_type = type;
		pModel->Init();
		pModel->m_pos = pos;
		pModel->m_rot = rot;

	}
	return pModel;
}

//=============================================================================
// �֐����FX�t�@�C���V�[���̏���������
// �֐��̊T�v�FX�t�@�C�����̐ݒ�
//=============================================================================
HRESULT CModel::Init(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();
	//D3DXMATERIAL *pMat;										// �}�e���A���f�[�^�ւ̃|�C���^


	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(m_acFileName[m_nNumParts],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_apBuffMat[m_nNumParts],
		NULL,
		&m_aNumMat[m_nNumParts],
		&m_apMesh[m_nNumParts]);

	//if (m_apMesh[m_nNumParts] != NULL)
	//{
	//	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	//	pMat = (D3DXMATERIAL*)m_apBuffMat[m_nNumParts]->GetBufferPointer();

	//	m_apTexture[m_type] = new LPDIRECT3DTEXTURE9[m_aNumMat[m_nNumParts]];		// �}�e���A�����e�ʂ𑝂₷
	//	for (int nCntMat = 0; nCntMat < (int)m_aNumMat[m_nNumParts]; nCntMat++)
	//	{// �}�e���A���̐������[�v
	//		if (pMat[nCntMat].pTextureFilename != NULL)
	//		{// �e�N�X�`���̃A�h���X�����݂��Ă�����
	//			D3DXCreateTextureFromFile(pDevice,		// 3D�f�o�C�X�̃A�h���X
	//				pMat[nCntMat].pTextureFilename,		// �ǂݍ��ރe�N�X�`���̃t�@�C���̃A�h���X
	//				m_apTexture[m_type]);						// �e�N�X�`���̃|�C���^�ɃA�h���X�ɐݒ肷��
	//		}
	//		else
	//		{// �e�N�X�`���̃A�h���X���Ȃ��Ȃ�
	//			m_apTexture[nCntMat] = NULL;							// NULL�ɐݒ肷��
	//		}
	//	}
	//}


	return S_OK;
}

//=============================================================================
// �֐����FX�t�@�C���V�[���̏I������
// �֐��̊T�v�F���b�V���A�}�e���A���A���g�̔j��
//=============================================================================
void CModel::Uninit(void)
{
	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{


		// �e�N�X�`���̊J��
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}



		// ���b�V���̊J��
		if (m_apMesh[nCntModel] != NULL)
		{
			m_apMesh[nCntModel]->Release();
			m_apMesh[nCntModel] = NULL;
		}

		// �}�e���A���̊J��
		if (m_apBuffMat[nCntModel] != NULL)
		{
			m_apBuffMat[nCntModel]->Release();
			m_apBuffMat[nCntModel] = NULL;
		}

		if (m_aNumMat[nCntModel] != NULL)
		{
			m_aNumMat[nCntModel] = NULL;
		}
	}

}

//=============================================================================
// �֐����FX�t�@�C���V�[���̍X�V����
// �֐��̊T�v�F--
//=============================================================================
void CModel::Update(void)
{
}


//=============================================================================
// �֐����FX�t�@�C���V�[���̕`�揈��
// �֐��̊T�v�F--
//=============================================================================
void CModel::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();


	//�e�̃}�g���b�N�X
	D3DXMATRIX mtxParent;


	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxrot, mtxtrans;

	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

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


	//�e�̃}�g���b�N�X�Ɗ|�����킹��
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMatrix();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	if (m_apMesh[m_nNumParts] != NULL)
	{
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_apBuffMat[m_nNumParts]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_aNumMat[m_nNumParts]; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				pDevice->SetTexture(0, m_pTexture);

			// ���f��(�p�[�c)�̕`��
			m_apMesh[m_nNumParts]->DrawSubset(nCntMat);
		}
	}
	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

}

//=============================================================================
// �֐����F�ʒu���̑��
// �֐��̊T�v�F�ʒu����������
//=============================================================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//=============================================================================
// �֐����F�p�x���̑��
// �֐��̊T�v�F�p�x����������
//=============================================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �֐����F���[���h�}�g���b�N�X�̑��
// �֐��̊T�v�F���[���h�}�g���b�N�X����������
//=============================================================================
void CModel::SetMtx(D3DXMATRIX mtx)
{
	m_mtxWorld = m_mtxWorld;
}

//=============================================================================
// �֐����F���[���h�}�g���b�N�X�̎擾
// �֐��̊T�v�F���[���h�}�g���b�N�X�����擾����
//=============================================================================
D3DXMATRIX CModel::GetMatrix(void)
{
	return m_mtxWorld;
}

//=============================================================================
// �֐����F�e�̃��f��
// �֐��̊T�v�F�e�̃��f���̐ݒ�
//=============================================================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}


//=============================================================================
// �֐����F�e�N�X�`���̊��蓖��
// �֐��̊T�v�F�e�N�X�`�������蓖�Ă�
//=============================================================================
void CModel::BindTexture(LPDIRECT3DTEXTURE9 tex)
{
	m_pTexture = tex;
}
