//=============================================================================
//
// �V�[��X����[3D�|���S��] [sceneX.cpp]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene3D.h"
#include "manager.h"
#include "input.h"
#include "sceneX.h"
#include "scene2D.h"
#include "debugproc.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************


//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CSceneX::CSceneX(int nPriority, OBJTYPE type) : CScene(nPriority, type)
{
}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�Ō�ɌĂяo�����
//=============================================================================
CSceneX::~CSceneX()
{
}

//=============================================================================
// �֐����FX�t�@�C���V�[���̐���
// �֐��̊T�v�FX�t�@�C���V�[���𐶐�����
//=============================================================================
CSceneX *CSceneX::Create(D3DXVECTOR3 pos)
{
	CSceneX  *pSceneX;
	pSceneX = new CSceneX;//�V�[���N���X�̐���
	if (pSceneX != NULL)
	{
		pSceneX->m_pos = pos;
		pSceneX->Init();

	}
	return pSceneX;
}


//=============================================================================
// �֐����FX�t�@�C���V�[���̏���������
// �֐��̊T�v�FX�t�@�C�����̐ݒ�
//=============================================================================
HRESULT CSceneX::Init(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXMATERIAL *pMat;								// �}�e���A���f�[�^�ւ̃|�C���^

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(m_pAddressModel,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuff,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuff->GetBufferPointer();

	//m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];		// �}�e���A�����e�ʂ𑝂₷

	//for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	//{// �}�e���A���̐������[�v
	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{// �e�N�X�`���̂���Ƃ�
	//		D3DXCreateTextureFromFile(pDevice,
	//			pMat[nCntMat].pTextureFilename,					// �ǂݍ��ރe�N�X�`����
	//			&m_pTexture[nCntMat]);
	//	}
	//	else
	//	{// �e�N�X�`�����Ȃ��Ƃ�
	//		m_pTexture[nCntMat] = NULL;							// NULL�ɐݒ肷��
	//	}
	//}

	// �ϐ��錾
	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	// �ŏ��l�ƍő�l��������
	m_VtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);		// �ŏ��l��������
	m_VtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	// �ő�l��������

																												// ���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();

	// ���_�t�H�[�}�b�g���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// ���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// �v���C���[�̍ŏ��l�ƍő�l���r
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{// ���_�������[�v
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;								// ���_���W�̑��

																				// �ŏ��l�Ɣ�r
		if (m_VtxMin.x > vtx.x)
		{// �������Ă���ŏ��l��x�����������l��������
			m_VtxMin.x = vtx.x;						// �ŏ��l��x����
		}
		if (m_VtxMin.y > vtx.y)
		{// �������Ă���ŏ��l��y�����������l��������
			m_VtxMin.y = vtx.y;						// �ŏ��l��y����
		}
		if (m_VtxMin.z > vtx.z)
		{// �������Ă���ŏ��l��y�����������l��������
			m_VtxMin.z = vtx.z;						// �ŏ��l��z����
		}

		// �ő�l�Ɣ�r
		if (m_VtxMax.x < vtx.x)
		{// �������Ă���ő�l��x�����傫���l��������
			m_VtxMax.x = vtx.x;						// �ő�l��x����
		}
		if (m_VtxMax.y < vtx.y)
		{// �������Ă���ő�l��x�����傫���l��������
			m_VtxMax.y = vtx.y;						// �ő�l��y����
		}
		if (m_VtxMax.z < vtx.z)
		{// �������Ă���ő�l��x�����傫���l��������
			m_VtxMax.z = vtx.z;						// �ő�l��z����
		}

		pVtxBuff += sizeFVF;					// �|�C���^���T�C�Y���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();



	return S_OK;
}

//=============================================================================
// �֐����FX�t�@�C���V�[���̏I������
// �֐��̊T�v�F���b�V���A�}�e���A���A���g�̔j��
//=============================================================================
void CSceneX::Uninit(void)
{

	// �}�e���A���̊J��
	if (m_pBuff != NULL)
	{
		m_pBuff->Release();
		m_pBuff = NULL;
	}

	// ���b�V���̊J��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	if (m_nNumMat != NULL)
	{
		m_nNumMat = NULL;
	}

	//�I�u�W�F�N�g(�������g)�̔j��
	Release();
}

//=============================================================================
// �֐����FX�t�@�C���V�[���̍X�V����
// �֐��̊T�v�F--
//=============================================================================
void CSceneX::Update(void)
{

}

//=============================================================================
// �֐����FX�t�@�C���V�[���̕`�揈��
// �֐��̊T�v�F--
//=============================================================================
void CSceneX::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);



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

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuff->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�j�b�N�̂����Ă�
		pDevice->SetTexture(0, m_pTexture);
		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// �֐����FX�t�@�C�����̊��蓖�ď���
// �֐��̊T�v�F�t�@�C������������
//=============================================================================
void CSceneX::BindFileName(char *cFileName)
{
	m_pAddressModel = cFileName;
}

//=============================================================================
// �֐����F���_�o�b�t�@�̊��蓖��
// �֐��̊T�v�F���_�o�b�t�@��������
//=============================================================================
void CSceneX::BindBuff(LPD3DXBUFFER Buff)
{
	m_pBuff = Buff;
}

//=============================================================================
// �֐����F���b�V�����̊��蓖��
// �֐��̊T�v�F���b�V������������
//=============================================================================
void CSceneX::BindMesh(LPD3DXMESH Mesh)
{
	m_pMesh = Mesh;
}

//=============================================================================
// �֐����F�}�e���A�����̐����蓖��
// �֐��̊T�v�F�}�e���A������������
//=============================================================================
void CSceneX::BindNumMat(DWORD NumMat)
{
	m_nNumMat = NumMat;
}

//=============================================================================
// �֐����F�ʒu���̑��
// �֐��̊T�v�F�ʒu����������
//=============================================================================
void CSceneX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//=============================================================================
// �֐����F�p�x���̑��
// �֐��̊T�v�F�p�x����������
//=============================================================================
void CSceneX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}


//=============================================================================
// �֐����F�ő咸�_���W�̎擾
// �֐��̊T�v�F�ő咸�_���W��Ԃ�
//=============================================================================
D3DXVECTOR3 CSceneX::GetVtxMax(void)
{
	return m_VtxMax;
}

//=============================================================================
// �֐����F�ŏ����_���W�̎擾
// �֐��̊T�v�F�ŏ����_���W��Ԃ�
//=============================================================================
D3DXVECTOR3 CSceneX::GetVtxMin(void)
{
	return m_VtxMin;
}

//=============================================================================
// �֐����F�e�N�X�`���̊��蓖��
// �֐��̊T�v�F�e�N�X�`�������蓖�Ă�
//=============================================================================
void CSceneX::BindTexture(LPDIRECT3DTEXTURE9 tex)
{
	m_pTexture = tex;
}
