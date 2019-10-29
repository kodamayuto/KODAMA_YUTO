//=============================================================================
//
// �ԍ��N���X���� [Gauge.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "Gauge.h"
#include "Manager.h"

//==================================================================
// �ÓI�����o�ϐ��錾
//==================================================================
LPDIRECT3DTEXTURE9	CGauge::m_pTexture;			// �e�N�X�`���ւ̃|�C���^

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CGauge::CGauge()
{
	m_pVtxBuff = NULL;
}
CGauge::~CGauge()
{

}

//==================================================================
// �e�N�X�`���ǂݍ���&�폜����
//==================================================================
HRESULT CGauge::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Gauge000.png", &m_pTexture);

	return S_OK;
}
void CGauge::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==================================================================
// ��������
//==================================================================
CGauge* CGauge::Create(D3DXVECTOR3 pos, float fSizeY, float fLength, CScene::ELEMENT elem)
{
	CGauge* pGauge = NULL;

	pGauge = new CGauge;

	if (pGauge != NULL)
	{
		pGauge->Init(pos, fSizeY, fLength,elem);
	}
	return pGauge;

}

//==================================================================
// ����������
//==================================================================
HRESULT CGauge::Init(D3DXVECTOR3 pos, float fSizeY, float fLength, CScene::ELEMENT elem)
{
	m_pos = pos;
	m_fSizeY = fSizeY;
	m_fElementGauge = fLength;
	m_Element = elem;

	m_nCntTime = 0;

	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	D3DXCOLOR col;
	switch (elem)
	{
	case CScene::ELEMENT_RED:
		col = D3DXCOLOR(1.0f, 0.2f, 0.1f, 1.0f);
		break;
	case CScene::ELEMENT_GREEN:
		col = D3DXCOLOR(0.2f, 0.8f, 0.2f, 1.0f);
		break;
	case CScene::ELEMENT_BLUE:
		col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
		break;
	case CScene::ELEMENT_SUPER:
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	}
	m_OrgColor = col;

	// ���_����ݒ�
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f,-fSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(fLength* 2.0f, -fSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, fSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(fLength* 2.0f, fSizeY, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;

}
//==================================================================
// �I������
//==================================================================
void CGauge::Uninit(void)
{

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

//==================================================================
// �X�V����
//==================================================================
void CGauge::Update(void)
{
	//m_nCntTime = ((m_nCntTime + 1) % 100)/* + 1*/;
	m_nCntTime++;
	float fColorFade;
	fColorFade = sinf((float)m_nCntTime / 10) * 0.5f + 1.5f;
	//D3DXCOLOR col = D3DXCOLOR(m_OrgColor.r + fColorFade, m_OrgColor.b + fColorFade, m_OrgColor.g + fColorFade,1.0f);
	D3DXCOLOR col = m_OrgColor * fColorFade;
	col.a = 1.0f;

	if (m_fElementGauge >= 100.0f)
	{
		// ���_����ݒ�
		VERTEX_2D* pVtx;
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;
		m_pVtxBuff->Unlock();
	}
}

//==================================================================
// �`�揈��
//==================================================================
void CGauge::Draw(void)
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

void CGauge::SetGauge(float fElementGauge)
{
	m_fElementGauge = fElementGauge;

	// ���_����ݒ�
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, -m_fSizeY, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(fElementGauge * 2.0f, -m_fSizeY, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, m_fSizeY, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(fElementGauge* 2.0f, m_fSizeY, 0.0f);

	m_pVtxBuff->Unlock();

}
