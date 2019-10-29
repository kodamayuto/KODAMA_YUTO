//=============================================================================
//
// ��ʑJ�ڃN���X���� [fade.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "fade.h"
#include "Manager.h"

//CScene2D*        CFade::m_pFadePolygon = NULL;
//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CFade::CFade()
{
	m_pTexture = NULL;
}
CFade::~CFade()
{

}

//==================================================================
// ��������
//==================================================================
CFade* CFade::Create(CManager::MODE modeNext)
{
	CFade* pFade = NULL;

	pFade = new CFade;

	if (pFade != NULL)
	{
		pFade->Init(modeNext);
	}
	return pFade;
}

//==================================================================
// ����������
//==================================================================
HRESULT CFade::Init(CManager::MODE modeNext)
{
	// �l�̏�����
	m_Fade = FADE_IN;
	m_modeNext = modeNext;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//m_pFadePolygon = SceneCreate(m_pFadePolygon,CScene::PRIORITY_7);
	//m_pFadePolygon->Set(D3DXVECTOR3(0.0f,0.0f,0.0f),"");
	//m_pFadePolygon->SetColor(m_colorFade);
	//m_pFadePolygon->SetObjType(CScene::OBJTYPE_FADE);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_����ݒ�
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
void CFade::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==================================================================
// �X�V����
//==================================================================
void CFade::Update(void)
{
	// ���_����ݒ�
	VERTEX_2D* pVtx;

	if (m_Fade != FADE_NONE)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;

		m_pVtxBuff->Unlock();

		if (m_Fade == FADE_IN)
		{
			m_colorFade.a -= 0.05f;//�����ɂ��Ă���
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_Fade = FADE_NONE;
			}
		}
		else if (m_Fade == FADE_OUT)
		{

			m_colorFade.a += 0.03f;//�s�����ɂ��Ă���
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_Fade = FADE_IN;

				CManager::SetMode(m_modeNext);
			}

		}
	}
}

//==================================================================
// �`�揈��
//==================================================================
void CFade::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

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

	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext, FADECOLOR fCol)
{
	if (m_Fade != FADE_OUT)
	{
		// ���_����ݒ�
		VERTEX_2D* pVtx;

		m_Fade = FADE_OUT;
		m_modeNext = modeNext;
		switch (fCol)
		{
		case CFade::COLOR_BLACK:
			m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			break;
		case CFade::COLOR_WHITE:
			m_colorFade = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			break;
		}

		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;

		m_pVtxBuff->Unlock();
	}
}
