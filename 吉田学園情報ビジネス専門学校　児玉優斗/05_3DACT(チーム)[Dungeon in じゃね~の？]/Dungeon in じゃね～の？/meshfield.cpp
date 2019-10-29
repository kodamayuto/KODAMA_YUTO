//=============================================================================
//
// ���b�V���t�B�[���h�̏��� [meshField.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


#include "meshField.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESH_SIZE (25.0f)
//#define MESH_VERTEX ((MESH_X + 1) * (MESH_Z + 1))	//���_��
//#define MESH_NUMBER (((MESH_X * MESH_Z) * 2) + ((MESH_Z - 1) * 4))
//#define MESH_INDEX /*(MESH_X + 1) * (MESH_Z + 1) + (2 * (MESH_Z - 1)) + (MESH_X + 1) * (MESH_Z - 1)*/((((MESH_X + 1) * 2) * (MESH_Z)) + ((MESH_Z - 1) * 2))
//#define TXT_NAME "MeshHeight.txt"		//�e�L�X�g��
#define BIN_NAME "data/TEXT/MeshHeight.bin"		//�o�C�i����
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
float g_fHeight[MESH_X + 1][MESH_Z + 1];			//����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshField::CMeshField(int nPrioriry, OBJTYPE objtype) : CScene(nPrioriry, objtype)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏����ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	m_pTexture = NULL;							//�e�N�X�`���̏�����
	m_pVtxBuff = NULL;							//���_�o�b�t�@�̏�����
	m_pIdxBuff = NULL;							//�C���f�b�N�X�o�b�t�@�̏�����
	m_nNumVartex = 0;							//���_�̑�����������
	m_nNumIdx = 0;								//�C���f�b�N�X�̑�����������
	m_nNumPolygon = 0;							//�|���S���̑�����������

	for (int nCntNor = 0; nCntNor < NUM_POLYGON; nCntNor++)
	{//�|���S���̐������J��Ԃ�
		m_aNor[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�@����������
	}

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshField::~CMeshField()
{

}
//=============================================================================
// �I�u�W�F�N�gX�̐���
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos)
{
	CMeshField *pMeshField = NULL;		//�|�C���^

	if (pMeshField == NULL)
	{
		pMeshField = new CMeshField;	//���I�m��
		pMeshField->m_pos = pos;		//�ʒu�̑��
		pMeshField->Init();				//����������
	}
	return pMeshField;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshField::Init(void)
{
	m_pTexture = NULL;					//�e�N�X�`���̏�����
	m_pVtxBuff = NULL;					//���_�o�b�t�@��������
	m_pIdxBuff = NULL;					//�C���f�b�N�X�o�b�t�@��������
	m_nNumVartex = 0;					//���_�̑�����������
	m_nNumIdx = 0;						//�C���f�b�N�X�̑�����������
	m_nNumPolygon = 0;					//�|���S���̑�����������

										//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field002.jpg", &m_pTexture);

	//���_���̌v�Z
	m_nNumVartex = (MESH_X + 1) * (MESH_Z + 1);

	//�C���f�b�N�X���̌v�Z
	m_nNumIdx = (MESH_X + 1) * (MESH_Z + 1)
		+ (2 * (MESH_Z - 1))
		+ (MESH_X + 1) * (MESH_Z - 1);

	//�|���S�������v�Z
	m_nNumPolygon = m_nNumIdx - 2;

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVartex,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,		//�C���f�b�N�X�̏���2�o�C�g�ɂ���
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPolygon = 0;	//�|���S���̃J�E���^�[

	for (int nCntVtxZ = 0; nCntVtxZ < MESH_Z + 1; nCntVtxZ++)
	{
		for (int nCntVtxX = 0; nCntVtxX < MESH_X + 1; nCntVtxX++)
		{
			//�ʒu�̏�����
			pVtx[(nCntVtxZ + nCntVtxX) + nCntPolygon].pos = D3DXVECTOR3((-MESH_SIZE + (nCntVtxX * MESH_SIZE)), 0.0f, (MESH_SIZE - (nCntVtxZ * MESH_SIZE)));
			//�e�N�X�`���̏�����
			pVtx[(nCntVtxZ + nCntVtxX) + nCntPolygon].tex = D3DXVECTOR2(1.0f * (nCntVtxX % (MESH_X + 1)), 1.0f * (nCntVtxZ));
			//�F�̏�����
			pVtx[(nCntVtxZ + nCntVtxX) + nCntPolygon].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//�@���̏�����
			pVtx[(nCntVtxZ + nCntVtxX) + nCntPolygon].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		}
		nCntPolygon += MESH_X;	//�J�E���^�[��X���̑������Z
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�N���̓ǂݍ���
	//LoadHeight();

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	nCntPolygon = 0;	//�|���S���̃J�E���^�[������
	int nCntNor = 0;	//�@��

	for (int nCntZ = 0; nCntZ < MESH_Z; nCntZ++)
	{//Z�̐������J��Ԃ�
		for (int nCntX = 0; nCntX < MESH_X; nCntX++)
		{//X�̐������J��Ԃ�
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;	//�ʒu�̃|�C���^
			D3DXVECTOR3 vec0, vec1, vec2;				//�x�N�g��
			D3DXVECTOR3 nor;							//�@��

			//�ʒu�̑��
			pPos0 = &pVtx[(nCntZ + nCntX + nCntPolygon)].pos;
			pPos1 = &pVtx[(nCntZ + nCntX + nCntPolygon) + MESH_X + 1].pos;
			pPos2 = &pVtx[(nCntZ + nCntX + nCntPolygon) + MESH_X + 2].pos;
			pPos3 = &pVtx[(nCntZ + nCntX + nCntPolygon) + 1].pos;

			//�x�N�g�����擾
			vec0 = *pPos1 - *pPos0;
			vec1 = *pPos2 - *pPos0;
			vec2 = *pPos3 - *pPos0;

			D3DXVec3Cross(&nor, &vec1, &vec0);
			D3DXVec3Normalize(&nor, &nor);								//���K������
			m_aNor[((nCntZ * 2) + (nCntX * 2) + nCntNor)] = nor;		//�@����ۊ�

			D3DXVec3Cross(&nor, &vec2, &vec1);
			D3DXVec3Normalize(&nor, &nor);								//���K������
			m_aNor[((nCntZ * 2) + (nCntX * 2) + nCntNor + 1)] = nor;	//�@����ۊ�
		}
		nCntPolygon += MESH_X;			//�|���S���̃J�E���^�[X���̑��������Z
		nCntNor += (MESH_X * 2) - 2;	//�@���̃J�E���^�[���Z
	}
	for (int nCntZ = 0; nCntZ < MESH_Z + 1; nCntZ++)
	{//Z�̐������J��Ԃ�
		for (int nCntX = 0; nCntX < MESH_X + 1; nCntX++)
		{//X�̐������J��Ԃ�
			if (nCntZ == 0)
			{//��̏ꍇ
				if (nCntX == 0)
				{//���[�̏ꍇ
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntX == MESH_X)
				{//�E�[�̏ꍇ
					pVtx[MESH_X].nor = (m_aNor[MESH_X + (MESH_X - 1)]);
				}
				else
				{//����ȊO�̏ꍇ
					pVtx[nCntX].nor = (m_aNor[((nCntX * 2) - 1)]
						+ m_aNor[((nCntX * 2) - 1) + 1]
						+ m_aNor[((nCntX * 2) - 1) + 2]) / 3;
				}
			}
			else if (nCntZ == MESH_Z)
			{//���̏ꍇ
				if (nCntX == 0)
				{//���[�̏ꍇ
					pVtx[MESH_Z * (MESH_X + 1)].nor = m_aNor[2 * (MESH_X * (MESH_Z - 1))];
				}
				else if (nCntX == MESH_X)
				{//�E�[�̏ꍇ
					pVtx[(MESH_X * MESH_Z) + (MESH_X + MESH_Z)].nor =
						(m_aNor[(2 * (MESH_X * (MESH_Z - 1))) + (2 * (MESH_X - 1))] +
							m_aNor[((2 * (MESH_X * (MESH_Z - 1))) + (2 * (MESH_X - 1))) + 1]) / 2;
				}
				else
				{//����ȊO�̏ꍇ
					pVtx[(MESH_Z * (MESH_X + 1)) + nCntX].nor =
						(m_aNor[(MESH_Z - 1) * (MESH_X * 2) + (nCntX * 2) - 2] +
							m_aNor[((MESH_Z - 1) * (MESH_X * 2) + (nCntX * 2) - 2) + 1] +
							m_aNor[((MESH_Z - 1) * (MESH_X * 2) + (nCntX * 2) - 2) + 2]) / 3;
				}
			}
			else if (nCntZ > 0 && nCntZ < MESH_Z)
			{
				if (nCntX == 0)
				{//���[�̏ꍇ
					pVtx[(MESH_X + 1) + (((MESH_X + 1) * nCntZ) - (MESH_X + 1))].nor = (m_aNor[(2 * MESH_X)*(nCntZ - 1)]
						+ m_aNor[(2 * MESH_X)*(nCntZ)]
						+ m_aNor[(2 * MESH_X)*(nCntZ)+1]) / 3;
				}
				else if (nCntX == MESH_X)
				{//�E�[�̏ꍇ
					pVtx[((2 * MESH_X) + 1) + (((MESH_X + 1) * nCntZ) - (MESH_X + 1))].nor = (m_aNor[(MESH_X * nCntZ) * 2 - 1]
						+ m_aNor[(MESH_X * nCntZ) * 2 - 2]
						+ m_aNor[(MESH_X * (nCntZ + 1)) * 2 - 1]) / 3;
				}
				else
				{//����ȊO�̏ꍇ
					pVtx[(MESH_X + 2) + (nCntX - 1) + ((nCntZ * (MESH_X + 1)) - (MESH_X + 1))].nor =
						(m_aNor[((nCntX - 1) * 2) + ((nCntZ * (2 * MESH_X)) - (2 * MESH_X))] +
							m_aNor[((((nCntX - 1) * 2) + 1) + ((nCntZ * (2 * MESH_X)) - (2 * MESH_X)))] +
							m_aNor[((((nCntX - 1) * 2) + 2) + ((nCntZ * (2 * MESH_X)) - (2 * MESH_X)))] +
							m_aNor[((2 * MESH_X) + ((nCntZ * (2 * MESH_X)) - (2 * MESH_X))) + ((nCntX * 2) - 2)] +
							m_aNor[((2 * MESH_X) + ((nCntZ * (2 * MESH_X)) - (2 * MESH_X)) + 1) + ((nCntX * 2) - 2)] +
							m_aNor[((2 * MESH_X) + ((nCntZ * (2 * MESH_X)) - (2 * MESH_X)) + 2) + ((nCntX * 2) - 2)]) / 6;
				}
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	WORD *pIdx;	//�C���f�b�N�X�f�[�^�ւ̃|�C���^

				//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nCntMesh = 0;		//���b�V���̃J�E���^�[

	for (int nCntVtxZ = 0; nCntVtxZ < MESH_Z; nCntVtxZ++)
	{
		for (int nCntVtxX = 0; nCntVtxX < MESH_X + 1; nCntVtxX++, nCntMesh++)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = nCntMesh + MESH_X + 1;
			pIdx[1] = nCntMesh;
			pIdx += 2;						//�|�C���^��i�߂�

			if (nCntVtxZ < MESH_Z - 1 && nCntVtxX == MESH_X)
			{
				pIdx[0] = nCntMesh;
				pIdx[1] = nCntMesh + (MESH_X + 1) + 1;
				pIdx += 2;					//�|�C���^��i�߂�
			}
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	LoadHeight();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshField::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//�C���f�b�N�X�̊J��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
	//�f�[�^�̊J��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshField::Update(void)
{
	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPolygon = 0;		//�|���S���̃J�E���^�[
	int nCntNor = 0;			//�@���̃J�E���^�[

	for (int nCntZ = 0; nCntZ < MESH_Z; nCntZ++)
	{//Z�̐������J��Ԃ�
		for (int nCntX = 0; nCntX < MESH_X; nCntX++)
		{//X�̐������J��Ԃ�
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;	//�ʒu�̃|�C���^
			D3DXVECTOR3 vec0, vec1, vec2;				//�x�N�g��
			D3DXVECTOR3 nor;							//�@��

														//�ʒu�̑��
			pPos0 = &pVtx[(nCntZ + nCntX + nCntPolygon)].pos;
			pPos1 = &pVtx[(nCntZ + nCntX + nCntPolygon) + MESH_X + 1].pos;
			pPos2 = &pVtx[(nCntZ + nCntX + nCntPolygon) + MESH_X + 2].pos;
			pPos3 = &pVtx[(nCntZ + nCntX + nCntPolygon) + 1].pos;

			//�x�N�g�����擾
			vec0 = *pPos1 - *pPos0;
			vec1 = *pPos2 - *pPos0;
			vec2 = *pPos3 - *pPos0;

			D3DXVec3Cross(&nor, &vec1, &vec0);
			D3DXVec3Normalize(&nor, &nor);								//���K������
			m_aNor[((nCntZ * 2) + (nCntX * 2) + nCntNor)] = nor;		//�@����ۊ�

			D3DXVec3Cross(&nor, &vec2, &vec1);
			D3DXVec3Normalize(&nor, &nor);								//���K������
			m_aNor[((nCntZ * 2) + (nCntX * 2) + nCntNor + 1)] = nor;	//�@����ۊ�
		}
		nCntPolygon += MESH_X;			//�|���S���̃J�E���^�[X���̑��������Z
		nCntNor += (MESH_X * 2) - 2;	//�@���̃J�E���^�[���Z
	}
	for (int nCntZ = 0; nCntZ < MESH_Z + 1; nCntZ++)
	{//Z�̐������J��Ԃ�
		for (int nCntX = 0; nCntX < MESH_X + 1; nCntX++)
		{//X�̐������J��Ԃ�
			if (nCntZ == 0)
			{//��̏ꍇ
				if (nCntX == 0)
				{//���[�̏ꍇ
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntX == MESH_X)
				{//�E�[�̏ꍇ
					pVtx[MESH_X].nor = (m_aNor[MESH_X + (MESH_X - 1)]);
				}
				else
				{//����ȊO�̏ꍇ
					pVtx[nCntX].nor = (m_aNor[((nCntX * 2) - 1)]
						+ m_aNor[((nCntX * 2) - 1) + 1]
						+ m_aNor[((nCntX * 2) - 1) + 2]) / 3;
				}
			}
			else if (nCntZ == MESH_Z)
			{//���̏ꍇ
				if (nCntX == 0)
				{//���[�̏ꍇ
					pVtx[MESH_Z * (MESH_X + 1)].nor = m_aNor[2 * (MESH_X * (MESH_Z - 1))];
				}
				else if (nCntX == MESH_X)
				{//�E�[�̏ꍇ
					pVtx[(MESH_X * MESH_Z) + (MESH_X + MESH_Z)].nor =
						(m_aNor[(2 * (MESH_X * (MESH_Z - 1))) + (2 * (MESH_X - 1))] +
							m_aNor[((2 * (MESH_X * (MESH_Z - 1))) + (2 * (MESH_X - 1))) + 1]) / 2;
				}
				else
				{//����ȊO�̏ꍇ
					pVtx[(MESH_Z * (MESH_X + 1)) + nCntX].nor =
						(m_aNor[(MESH_Z - 1) * (MESH_X * 2) + (nCntX * 2) - 2] +
							m_aNor[((MESH_Z - 1) * (MESH_X * 2) + (nCntX * 2) - 2) + 1] +
							m_aNor[((MESH_Z - 1) * (MESH_X * 2) + (nCntX * 2) - 2) + 2]) / 3;
				}
			}
			else if (nCntZ > 0 && nCntZ < MESH_Z)
			{
				if (nCntX == 0)
				{//���[�̏ꍇ
					pVtx[(MESH_X + 1) + (((MESH_X + 1) * nCntZ) - (MESH_X + 1))].nor = (m_aNor[(2 * MESH_X)*(nCntZ - 1)]
						+ m_aNor[(2 * MESH_X)*(nCntZ)]
						+ m_aNor[(2 * MESH_X)*(nCntZ)+1]) / 3;
				}
				else if (nCntX == MESH_X)
				{//�E�[�̏ꍇ
					pVtx[((2 * MESH_X) + 1) + (((MESH_X + 1) * nCntZ) - (MESH_X + 1))].nor = (m_aNor[(MESH_X * nCntZ) * 2 - 1]
						+ m_aNor[(MESH_X * nCntZ) * 2 - 2]
						+ m_aNor[(MESH_X * (nCntZ + 1)) * 2 - 1]) / 3;
				}
				else
				{//����ȊO�̏ꍇ
					pVtx[(MESH_X + 2) + (nCntX - 1) + ((nCntZ * (MESH_X + 1)) - (MESH_X + 1))].nor =
						(m_aNor[((nCntX - 1) * 2) + ((nCntZ * (2 * MESH_X)) - (2 * MESH_X))] +
							m_aNor[((((nCntX - 1) * 2) + 1) + ((nCntZ * (2 * MESH_X)) - (2 * MESH_X)))] +
							m_aNor[((((nCntX - 1) * 2) + 2) + ((nCntZ * (2 * MESH_X)) - (2 * MESH_X)))] +
							m_aNor[((2 * MESH_X) + ((nCntZ * (2 * MESH_X)) - (2 * MESH_X))) + ((nCntX * 2) - 2)] +
							m_aNor[((2 * MESH_X) + ((nCntZ * (2 * MESH_X)) - (2 * MESH_X)) + 1) + ((nCntX * 2) - 2)] +
							m_aNor[((2 * MESH_X) + ((nCntZ * (2 * MESH_X)) - (2 * MESH_X)) + 2) + ((nCntX * 2) - 2)]) / 6;
				}
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshField::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

												// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,
		m_rot.x,
		m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVartex, 0, m_nNumPolygon);
	/*pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);*/
}

//=============================================================================
// �����̏�������
//=============================================================================
void CMeshField::SaveHeight(void)
{
	//�e�L�X�g�ł̏�������
#if 0
	//�t�@�C���̎擾
	FILE *pFile;

	pFile = fopen(TXT_NAME, "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntZ = 0; nCntZ < MESH_Z; nCntZ++)
		{
			for (int nCntX = 0; nCntX < MESH_X; nCntX++)
			{
				fprintf(pFile, "%.1f\n", pVtx->pos.y);
				printf("\n�Z�[�u���܂����B\n");
				pVtx++;
			}
		}
		fclose(pFile);
		// ���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("�t�@�C�����J�����Ƃ��ł��܂���ł����B\n");
	}
#endif

	//�o�C�i���ł̏�������
#if 1
	//�t�@�C���̎擾
	FILE *pFile;

	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < MESH_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESH_X + 1; nCntX++)
		{
			g_fHeight[nCntX][nCntZ] = pVtx->pos.y;
			pVtx++;
		}
	}
	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	pFile = fopen(BIN_NAME, "wb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		fwrite(&g_fHeight[0][0], sizeof(float), (MESH_X + 1) * (MESH_Z + 1), pFile);
		fclose(pFile);
	}
#endif
}

//=============================================================================
// �����̓ǂݍ���
//=============================================================================
void CMeshField::LoadHeight(void)
{
	//�e�L�X�g�ł̓ǂݍ���
#if 0
	//�t�@�C���̎擾
	FILE *pFile;

	pFile = fopen(TXT_NAME, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntZ = 0; nCntZ < MESH_Z; nCntZ++)
		{
			for (int nCntX = 0; nCntX < MESH_X; nCntX++)
			{
				fscanf(pFile, "%f\n", &pVtx->pos.y);
				pVtx++;
			}
		}
		fclose(pFile);
		// ���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("�t�@�C�����J�����Ƃ��ł��܂���ł����B\n");
	}
#endif

	//�o�C�i���ł̓ǂݍ���
#if 1
	//�t�@�C���̎擾
	FILE *pFile;

	pFile = fopen(BIN_NAME, "rb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		fread(&g_fHeight[0][0], sizeof(float), (MESH_X + 1) * (MESH_Z + 1), pFile);
	}
	fclose(pFile);
	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < MESH_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESH_X + 1; nCntX++)
		{
			pVtx->pos.y = g_fHeight[nCntX][nCntZ];
			pVtx++;
		}
	}
	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
#endif
}

//=============================================================================
// �����̎擾
//=============================================================================
float CMeshField::GetHeight(D3DXVECTOR3 pos)
{
	bool bVtxX[MESH_X];	//X���W
	bool bVtxZ[MESH_Z];	//Y���W

	for (int nCntX = 0; nCntX < MESH_X; nCntX++)
	{//X�̐������J��Ԃ�
		bVtxX[nCntX] = false;
	}
	for (int nCntZ = 0; nCntZ < MESH_Z; nCntZ++)
	{//Z�̐������J��Ԃ�
		bVtxZ[nCntZ] = false;
	}

	for (int nCntZ = 0; nCntZ < MESH_Z; nCntZ++)
	{//Z�̐������J��Ԃ�
		for (int nCntX = 0; nCntX < MESH_X; nCntX++)
		{//X�̐������J��Ԃ�
			if (pos.x >= -MESH_SIZE + (nCntX * MESH_SIZE) && pos.x <= (nCntX * MESH_SIZE))
			{//�����Q�̃|���S���̓����ɂ���ꍇ
				bVtxX[nCntX] = true;
			}
			else
			{//�E���Q�̃|���S���̓����ɂ���ꍇ
				bVtxX[nCntX] = false;
			}

			if (pos.z <= MESH_SIZE + (nCntZ * -MESH_SIZE) && pos.z >= MESH_SIZE + ((nCntZ + 1) * -MESH_SIZE))
			{//��̕ӂ�艺�ɂ��ĉ��̕ӂ���ɂ���ꍇ
				bVtxZ[nCntZ] = true;
			}
			else
			{//��̕ӂ���ɂ��ĉ��̕ӂ�艺�ɂ���ꍇ
				bVtxZ[nCntZ] = false;
			}
		}
	}

	int nCntPolygon = 0;							//�|���S���̃J�E���^�[
	int nCntNor = 0;								//�@���̃J�E���^�[
	D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;		//�ʒu
	D3DXVECTOR3 vec0, vec1, vec2, vec3;				//�x�N�g��
	D3DXVECTOR3 nor0, nor1;							//�@��
	float fData;									//�f�[�^�i�[

	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntZ = 0; nCntZ < MESH_Z; nCntZ++)
	{//Z�̐������J��Ԃ�
		for (int nCntX = 0; nCntX < MESH_X; nCntX++)
		{//X�̐������J��Ԃ�
			if (bVtxX[nCntX] == true && bVtxZ[nCntZ] == true)
			{
				//�ʒu�̑��
				pPos0 = &pVtx[(nCntZ + nCntX + nCntPolygon)].pos;
				pPos1 = &pVtx[(nCntZ + nCntX + nCntPolygon) + MESH_X + 1].pos;
				pPos2 = &pVtx[(nCntZ + nCntX + nCntPolygon) + MESH_X + 2].pos;
				pPos3 = &pVtx[(nCntZ + nCntX + nCntPolygon) + 1].pos;

				//�x�N�g�����擾
				vec0 = *pPos1 - *pPos0;
				vec1 = *pPos2 - *pPos0;
				vec2 = *pPos3 - *pPos0;
				vec3 = pos - *pPos0;

				//�Q�̃x�N�g������@�����Z�o
				D3DXVec3Cross(&nor0, &vec0, &vec1);
				//���K������
				D3DXVec3Normalize(&nor0, &nor0);

				//�Q�̃x�N�g������@�����Z�o
				D3DXVec3Cross(&nor1, &vec1, &vec2);
				//���K������
				D3DXVec3Normalize(&nor1, &nor1);

				//�Q�̖@�����畽�ϒl�����߂�
				fData = ((vec1.z * vec3.x) - (vec1.x * vec3.z));

				if (fData >= 0)
				{//���̃|���S���̓����ɂ���ꍇ
					pos.y = ((nor0.x *(pos.x - pPos0->x) + nor0.z * (pos.z - pPos0->z)) / -nor0.y) + pPos0->y;
				}
				else
				{//�E�̃|���S���̓����ɂ���ꍇ
					pos.y = ((nor1.x *(pos.x - pPos2->x) + nor1.z * (pos.z - pPos2->z)) / -nor1.y) + pPos2->y;
				}
			}
		}
		nCntPolygon += MESH_X;			//�|���S���̃J�E���^�[���Z
		nCntNor += (MESH_X * 2) - 2;	//�@���̃J�E���^�[���Z
	}
	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
	return pos.y;
}

//=============================================================================
// �����̐ݒu����
//=============================================================================
void CMeshField::SetHeight(D3DXVECTOR3 pos, float fValue, float fRange)
{
	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < MESH_Z + 1; nCntZ++)
	{//Z�̐������J��Ԃ�
		for (int nCntX = 0; nCntX < MESH_X + 1; nCntX++)
		{//X�̐������J��Ԃ�
		 //�v���C���[�̈ʒu�ƒ��_�̋������v�Z
			float fLength = sqrtf((pos.x - pVtx->pos.x) * (pos.x - pVtx->pos.x)
				+ (pos.z - pVtx->pos.z) * (pos.z - pVtx->pos.z));

			if (fLength < fRange)
			{//�Ώۂ̒��_���͈͓��̏ꍇ
				float fHeight = cosf((D3DX_PI / 2) *  (fLength / fRange))  * fValue;
				pVtx->pos.y += fHeight;
			}
			pVtx++;
		}
	}
	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
