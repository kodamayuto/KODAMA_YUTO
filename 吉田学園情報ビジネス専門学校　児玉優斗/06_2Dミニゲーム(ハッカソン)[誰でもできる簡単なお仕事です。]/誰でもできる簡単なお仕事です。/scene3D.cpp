//=============================================================================
//
// �V�[��2D���� [scene3D.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "scene3D.h"
#include "Manager.h"

//==================================================================
// �ÓI�����o�ϐ�
//==================================================================
static bool g_DeleteFlag = true;		//�u���b�N�����t���O(�e�X�g)

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CScene3D::CScene3D(CScene::PRIORITY pri = PRIORITY_3) : CScene(pri, OBJTYPE_3D)
{

}
CScene3D::~CScene3D()
{

}

//==================================================================
// �e�N�X�`���̓K�p
//==================================================================
void CScene3D::BindTexture(LPCSTR TexTag)
{
	m_pTexture = CTexture::GetTexture(TexTag);
}

//==================================================================
// �|���S���̐ݒ菈��
//==================================================================
void CScene3D::Set(D3DXVECTOR3 pos, LPCSTR TexTag, D3DXVECTOR3 Size,
	D3DXVECTOR3 rot,D3DXCOLOR col, D3DXVECTOR2 UVrectMin, D3DXVECTOR2 UVrectMax)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	BindTexture(TexTag);
	m_pos = pos;
	m_rot = rot;
	m_Col = col;
	m_Size = Size;
	m_UVRectMin = UVrectMin;
	m_UVRectMax = UVrectMax;

	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_Size.x, 0.0f, m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x, 0.0f, m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x, 0.0f, -m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x, 0.0f, -m_Size.z);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	pVtx[0].tex = D3DXVECTOR2(UVrectMin.x, UVrectMin.y);
	pVtx[1].tex = D3DXVECTOR2(UVrectMax.x, UVrectMin.y);
	pVtx[2].tex = D3DXVECTOR2(UVrectMin.x, UVrectMax.y);
	pVtx[3].tex = D3DXVECTOR2(UVrectMax.x, UVrectMax.y);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//==================================================================
// �|���S���̏���������
//==================================================================
HRESULT CScene3D::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/WS000635.JPG", &m_pTexture);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


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
	pDevice->SetTexture(0,m_pTexture);//�e�N�X�`���̐ݒ�

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
	// �ϐ��錾
	VERTEX_3D* pVtx;

	m_Col = col;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();

}

void CScene3D::SetUV(D3DXVECTOR2 MinRect, D3DXVECTOR2 MaxRect)
{
	// �ϐ��錾
	VERTEX_3D* pVtx;

	m_UVRectMin = MinRect;
	m_UVRectMax = MaxRect;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = MinRect;
	pVtx[1].tex = D3DXVECTOR2(MaxRect.x, MinRect.y);
	pVtx[2].tex = D3DXVECTOR2(MinRect.x, MaxRect.y);
	pVtx[3].tex = MaxRect;

	m_pVtxBuff->Unlock();

}

