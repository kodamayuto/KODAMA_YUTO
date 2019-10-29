//=============================================================================
//
// �V�[��2D���� [scene3D.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "scene3D.h"
#include "Manager.h"
#include "player.h"
#include "renderer.h"
//==================================================================
// �ÓI�����o�ϐ�
//==================================================================
static bool g_DeleteFlag = true;		//�u���b�N�����t���O(�e�X�g)

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CScene3D::CScene3D(int priority, OBJTYPE type) : CScene(priority, type)
{
	m_pTexture = NULL;
}
CScene3D::~CScene3D()
{

}

//==================================================================
// �e�N�X�`���̓K�p
//==================================================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//==================================================================
// ����
//==================================================================
CScene3D* CScene3D::Create(void)
{
	CScene3D* pScene3D = NULL;

	pScene3D = new CScene3D(4);

	if (pScene3D != NULL)
	{
		pScene3D->Init();
	}

	return pScene3D;
}


//==================================================================
// �|���S���̏���������
//==================================================================
HRESULT CScene3D::Init()
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	m_fSize = 200.0f;
	pVtx[0].pos = D3DXVECTOR3(sinf(D3DX_PI * 0.75f) * m_fSize, 0.0f, cosf(D3DX_PI * 0.75f) *m_fSize);
	pVtx[1].pos = D3DXVECTOR3(sinf(D3DX_PI * -0.75f) *m_fSize, 0.0f, cosf(D3DX_PI * -0.75f) *m_fSize);
	pVtx[2].pos = D3DXVECTOR3(sinf(D3DX_PI * 0.25f) *m_fSize, 0.0f, cosf(D3DX_PI * 0.25f) *m_fSize);
	pVtx[3].pos = D3DXVECTOR3(sinf(D3DX_PI * -0.25f) *m_fSize, 0.0f, cosf(D3DX_PI * -0.25f) *m_fSize);

	D3DXVECTOR3 Vec[4];

	//nor[0]
	Vec[0] = pVtx[1].pos - pVtx[0].pos;
	Vec[1] = pVtx[2].pos - pVtx[0].pos;

	D3DXVec3Cross(&pVtx[0].nor, &Vec[0], &Vec[1]);
	//nor[1]
	Vec[0] = pVtx[2].pos - pVtx[1].pos;
	Vec[1] = pVtx[0].pos - pVtx[1].pos;
	D3DXVec3Cross(&pVtx[1].nor, &Vec[0], &Vec[1]);
	//nor[2]
	Vec[0] = pVtx[1].pos - pVtx[2].pos;
	Vec[1] = pVtx[3].pos - pVtx[2].pos;
	D3DXVec3Cross(&pVtx[2].nor, &Vec[0], &Vec[1]);

	//nor[3]
	Vec[0] = pVtx[2].pos - pVtx[3].pos;
	Vec[1] = pVtx[1].pos - pVtx[3].pos;
	D3DXVec3Cross(&pVtx[3].nor, &Vec[0], &Vec[1]);

	//���K��
	D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);
	D3DXVec3Normalize(&pVtx[1].nor, &pVtx[1].nor);
	D3DXVec3Normalize(&pVtx[2].nor, &pVtx[2].nor);
	D3DXVec3Normalize(&pVtx[3].nor, &pVtx[3].nor);

	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==================================================================
// �|���S���̏I������
//==================================================================
void CScene3D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}

	Release();
}

//==================================================================
// �|���S���̍X�V����
//==================================================================
void CScene3D::Update(void)
{

}
//==================================================================
// �|���S���̕`�揈��
//==================================================================
void CScene3D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

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

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

								   // �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);//�e�N�X�`���̐ݒ�

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
		0,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
		2);		   	       //�v���~�e�B�u�̐�
}

//==================================================================
// �e��ݒ菈��
//==================================================================
void CScene3D::SetPosition(D3DXVECTOR3 pos)
{//���W�̂ݐݒ�
	m_pos = pos;
}

void CScene3D::SetRotation(D3DXVECTOR3 rot)
{//�p�x�̂ݐݒ�
	m_rot = rot;
}

void CScene3D::SetColor(D3DXCOLOR col)
{
	m_Color = col;

	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	m_pVtxBuff->Unlock();
}
void CScene3D::SetSize(float fSize)
{
	m_fSize = fSize;

	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(sinf(D3DX_PI * 0.75f) * m_fSize, 0.0f, cosf(D3DX_PI * 0.75f) *m_fSize);
	pVtx[1].pos = D3DXVECTOR3(sinf(D3DX_PI * -0.75f) *m_fSize, 0.0f, cosf(D3DX_PI * -0.75f) *m_fSize);
	pVtx[2].pos = D3DXVECTOR3(sinf(D3DX_PI * 0.25f) *m_fSize, 0.0f, cosf(D3DX_PI * 0.25f) *m_fSize);
	pVtx[3].pos = D3DXVECTOR3(sinf(D3DX_PI * -0.25f) *m_fSize, 0.0f, cosf(D3DX_PI * -0.25f) *m_fSize);

	m_pVtxBuff->Unlock();

}
