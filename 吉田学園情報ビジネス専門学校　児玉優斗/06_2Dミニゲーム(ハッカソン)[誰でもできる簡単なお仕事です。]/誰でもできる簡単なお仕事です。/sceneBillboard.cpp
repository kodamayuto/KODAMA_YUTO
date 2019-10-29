//=============================================================================
//
// �r���{�[�h���� [sceneBillboard.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "sceneBillboard.h"
#include "Manager.h"

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CSceneBillboard::CSceneBillboard(CScene::PRIORITY pri = CScene::PRIORITY_3) : CScene(pri,OBJTYPE_BILLBOARD)
{
}
CSceneBillboard::~CSceneBillboard()
{

}

//==================================================================
// �e�N�X�`���̓K�p
//==================================================================
void CSceneBillboard::BindTexture(LPCSTR TexTag)
{
	m_pTexture = CTexture::GetTexture(TexTag);
}

//==================================================================
// ��������
//==================================================================
void CSceneBillboard::Set(D3DXVECTOR3 pos, LPCSTR TexTag, D3DXVECTOR2 Size)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = pos;
	m_Size = Size;
	BindTexture(TexTag);

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
	pVtx[0].pos = D3DXVECTOR3(-m_Size.x, m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x, m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x, -m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x, -m_Size.y, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();


}
//==================================================================
// ����������
//==================================================================
HRESULT CSceneBillboard::Init(void)
{
	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CSceneBillboard::Uninit(void)
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
// �X�V����
//==================================================================
void CSceneBillboard::Update(void)
{

}

//==================================================================
// �`�揈��
//==================================================================
void CSceneBillboard::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;				// �v�Z�p�}�g���b�N�X

														//���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���C�e�B���O���[�h�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMatrixIdentity(&m_mtxWorld);

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

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


	// ���C�e�B���O���[�h��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//==================================================================
// �e��ݒ菈��
//==================================================================
void CSceneBillboard::SetPosition(D3DXVECTOR3 pos)
{//���W�̂ݐݒ�
	m_pos = pos;
}
void CSceneBillboard::SetSize(D3DXVECTOR2 Size)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
	m_Size = Size;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_Size.x, m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x, m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x, -m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x, -m_Size.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
