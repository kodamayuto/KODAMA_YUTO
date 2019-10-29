//=============================================================================
//
// ���b�V���V�����_�[���� [meshcylinder.cpp]
// Author : �ݓc��(Kishida Rei)
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene3D.h"
#include "manager.h"
#include "input.h"
#include "scene_meshcylinder.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHCYLINDER_RADIUS (2000.0f)
#define MESHCYLINDER_HEIGHT (250.0f)

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
int CMeshCylinder::m_nSquareNum = 0;	//�l�p�ʂ̐�
int CMeshCylinder::m_nVecNum = 0;	//�l�p�ʂ̐�
//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�N���A�Ȓl����
//=============================================================================
CMeshCylinder::CMeshCylinder(int nPriority, OBJTYPE type) : CScene(nPriority, type)
{

}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�����̍Ō�ɌĂяo�����
//=============================================================================
CMeshCylinder::~CMeshCylinder()
{
}

//=============================================================================
// �֐����F���b�V���V�����_�[�̐�������
// �֐��̊T�v�F���b�V���V�����_�[�𐶐�����
//=============================================================================
CMeshCylinder * CMeshCylinder::Create(D3DXVECTOR3 pos)
{
	CMeshCylinder  *pSceneMeshfield;
	pSceneMeshfield = new CMeshCylinder;//�V�[���N���X�̐���
	if (pSceneMeshfield != NULL)
	{
		pSceneMeshfield->m_pos = pos;
		pSceneMeshfield->m_nMesh_H = 30;
		pSceneMeshfield->m_nMesh_V = 1;
		pSceneMeshfield->Init();

	}
	return pSceneMeshfield;
}

//=============================================================================
// �֐����F���b�V���V�����_�[�̏���������
// �֐��̊T�v�F���_���ƃ|���S�����ɒ���
//=============================================================================
HRESULT CMeshCylinder::Init(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//���_��
	m_nVertexNum = (m_nMesh_H + 1) * (m_nMesh_V + 1);
	//�C���f�b�N�X��
	m_nIndexNum = (m_nMesh_H * m_nMesh_V) * 2 + (4 * (m_nMesh_V - 1)) + 2;
	//�|���S����
	m_nPolygonNum = (m_nMesh_H * m_nMesh_V) * 2 + (4 * (m_nMesh_V - 1));
	//�l�p�̖ʂ̐�
	m_nSquareNum = (m_nMesh_H * m_nMesh_V);
	//�͂��x�N�g���̐�
	m_nVecNum = 6 * m_nSquareNum;

	MakeVertex(pDevice);
	MakeIndex(pDevice);

	return S_OK;
}

//=============================================================================
// �֐����F���b�V���V�����_�[�̏I������
// �֐��̊T�v�F�e�N�X�`���A���_�o�b�t�@�̔j��
//=============================================================================
void CMeshCylinder::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	Release();
}

//=============================================================================
// �֐����F���b�V���V�����_�[�̕`�揈��
// �֐��̊T�v�F--
//=============================================================================
void CMeshCylinder::Update(void)
{

	m_rot.y += 0.0001f;

}

//=============================================================================
// �֐����F���b�V���V�����_�[�̕`��
// �֐��̊T�v�F���_���ƃ|���S�����ɒ���
//=============================================================================
void CMeshCylinder::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxrot, mtxtrans;//�}�g���b�N�X���

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 220);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


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

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	//pDevice->SetFVF(D3DXGetFVFVertexSize);
	pDevice->SetTexture(0, m_pTexture);


	// ���b�V���V�����_�[�̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nIndexNum, 0, m_nPolygonNum);

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}


//=============================================================================
// �֐����F���_���̍쐬
// �֐��̊T�v�F�Ƃ肠�����͒��_��u������
//=============================================================================
void CMeshCylinder::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mountain000.png", &m_pTexture);


	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVertexNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);



	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMeshCylinder_V = 0; nCntMeshCylinder_V < m_nMesh_V + 1; nCntMeshCylinder_V++)
	{
		for (int nCntMeshCylinder_H = 0; nCntMeshCylinder_H < m_nMesh_H + 1; nCntMeshCylinder_H++)
		{
			pVtx[0].pos.x = sinf(-D3DX_PI * (nCntMeshCylinder_H * (1.0f / (m_nMesh_H / 2)))) * MESHCYLINDER_RADIUS;
			pVtx[0].pos.y = MESHCYLINDER_HEIGHT * nCntMeshCylinder_V;
			pVtx[0].pos.z = cosf(-D3DX_PI * (nCntMeshCylinder_H * (1.0f / (m_nMesh_H / 2)))) * MESHCYLINDER_RADIUS;
			//�@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(sinf(-D3DX_PI * (0.25f * nCntMeshCylinder_H)), 0.0f, cosf(D3DX_PI * (0.25f * nCntMeshCylinder_H)));
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(nCntMeshCylinder_H * (1.0f / (m_nMesh_H / 2)), nCntMeshCylinder_V * -1.0f);


			pVtx += 1;
		}
	}
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}
//=============================================================================
// �֐����F�C���f�b�N�X���̍쐬
// �֐��̊T�v�F�C���f�b�N�X�Ń|���S���𐶐�����
//=============================================================================
void CMeshCylinder::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//�C���f�b�N�X�̃J�E���g


	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < m_nMesh_V; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= m_nMesh_H; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (m_nMesh_H + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == m_nMesh_H && nCntIndex_V <= m_nMesh_V)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (m_nMesh_H + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();
}


