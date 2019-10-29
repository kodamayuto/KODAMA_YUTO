//=============================================================================
//
// �ԍ��N���X���� [number.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "number.h"
#include "Manager.h"

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
}
CNumber::~CNumber()
{

}

//==================================================================
// �ݒ菈��
//==================================================================
void CNumber::Set(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect, int nNum, D3DXCOLOR Col)
{
	m_pos = pos;
	m_polygonRect = polygonRect;
	m_nNumber = nNum;
	m_Col = Col;

	// ���_����ݒ�
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_polygonRect.x, 0.0f, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, m_polygonRect.y, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_polygonRect.x, m_polygonRect.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	pVtx[0].tex = D3DXVECTOR2((m_nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((m_nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();
}
//==================================================================
// ����������
//==================================================================
HRESULT CNumber::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`���̕R�Â�
	m_pTexture = CTexture::GetTexture("NUMBER");

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	m_pTexture = NULL;
}

//==================================================================
// �X�V����
//==================================================================
void CNumber::Update(void)
{
	// ���_����ݒ�
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_polygonRect.x, 0.0f, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, m_polygonRect.y, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_polygonRect.x, m_polygonRect.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	pVtx[0].tex = D3DXVECTOR2((m_nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((m_nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();
}

//==================================================================
// �`�揈��
//==================================================================
void CNumber::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	if (m_pTexture != NULL)
	{
		pDevice->SetTexture(0, m_pTexture);
	}
	else
	{
		pDevice->SetTexture(0, NULL);
	}

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


}

//==================================================================
// �ԍ��ݒ菈��
//==================================================================
void CNumber::SetNumber(int nNum)
{
	m_nNumber = nNum;

	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((m_nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((m_nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();


}
