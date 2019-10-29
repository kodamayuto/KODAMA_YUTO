//=============================================================================
//
// x�t�@�C���I�u�W�F�N�g���� [sceneX.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "sceneX.h"
#include "Manager.h"

//==================================================================
// �ÓI�����o�ϐ��錾
//==================================================================
LPCSTR CSceneX::m_ModelNameInfo[CSceneX::MODEL_MAX] =
{
	{ "data/MODEL/airplane000.x" },
	{ "data/MODEL/car002.x" },
	{ "data/MODEL/KATANA.x" },
};

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CSceneX::CSceneX(CScene::PRIORITY pri = CScene::PRIORITY_3) : CScene(pri, OBJTYPE_XFILE)
{
	m_pBuffMat = NULL;
	m_pMesh = NULL;
	m_pTexture = NULL;
}
CSceneX::~CSceneX()
{

}

//==================================================================
// ����������
//==================================================================
void CSceneX::Set(D3DXVECTOR3 pos, CSceneX::MODEL_PROPERTY prop,D3DXVECTOR3 rot)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �ʒu�E�����̏����ݒ�
	m_pos = pos;
	m_rot = rot;
	m_modelProperty = prop;

	if (m_pBuffMat == NULL)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_ModelNameInfo[prop],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_nNumMat,
			&m_pMesh);

		// �}�e���A����񂩂�e�N�X�`���������o��
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
		D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[m_nNumMat];
		m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

		for (DWORD nCntMat = 0; nCntMat < m_nNumMat; nCntMat++)
		{// ���_���̐������J��Ԃ�
		 // �}�e���A������ǂݍ���
			pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

			// ����������������
			pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

			// �e�N�X�`������������
			m_pTexture[nCntMat] = NULL;

			// �e�N�X�`���̏���ǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL &&
				lstrlen(pMat[nCntMat].pTextureFilename) > 0)
			{// �e�N�X�`���̃t�@�C����������
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_pTexture[nCntMat]);
			}
		}
		delete[] pMatBuff;
		pMatBuff = NULL;
	}

	//�ړ��ʁE��]�ʂ̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�̎擾
	GetVertex();

	m_bTargetFlag = false;

}

//==================================================================
// ����������
//==================================================================
HRESULT CSceneX::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CSceneX::Uninit(void)
{
	// ���b�V���̉��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//�e�N�X�`���̊J��
	for (DWORD nCntMat = 0; nCntMat < m_nNumMat; nCntMat++)
	{
		if (m_pTexture[nCntMat] != NULL)
		{
			m_pTexture[nCntMat]->Release();
			m_pTexture[nCntMat] = NULL;
		}
	}
	delete[] m_pTexture;
	//�}�e���A���̉��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	Release();
}

//==================================================================
// �X�V����
//==================================================================
void CSceneX::Update(void)
{

}

//==================================================================
// �`�揈��
//==================================================================
void CSceneX::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		/*�e�N�X�`���̐ݒ�*/
		pDevice->SetTexture(0, m_pTexture[nCntMat]);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

}
//==================================================================
// ���_���W�擾����
//==================================================================
void CSceneX::GetVertex(void)
{
	//�ϐ��錾
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	m_vtxMin = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);
	m_vtxMax = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);

	//���_���̎擾
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());


	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

		//���_���r���ă��f���̍ŏ��E�ő�𔲂��o��
		//x
		if (m_vtxMin.x > vtx.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (m_vtxMax.x < vtx.x)
		{
			m_vtxMax.x = vtx.x;
		}

		//y
		if (m_vtxMin.y > vtx.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (m_vtxMax.y < vtx.y)
		{
			m_vtxMax.y = vtx.y;
		}

		//z
		if (m_vtxMin.z > vtx.z)
		{
			m_vtxMin.z = vtx.z;
		}
		if (m_vtxMax.z < vtx.z)
		{
			m_vtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
	}
	//�A�����b�N
	m_pMesh->UnlockVertexBuffer();

}

//==================================================================
// �e��ݒ菈��
//==================================================================
void CSceneX::SetPosition(D3DXVECTOR3 pos)
{//���W�̂ݐݒ�
	m_pos = pos;
}

void CSceneX::SetRotation(D3DXVECTOR3 rot)
{//�p�x�̂ݐݒ�
	m_rot = rot;
}

