//=============================================================================
//
// ��ʑJ�ڃN���X���� [fade.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "fade.h"
#include "Manager.h"

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CFade::CFade()
{
	m_pTexture = NULL;
	m_pFadePolygon = NULL;
}
CFade::~CFade()
{

}

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

	m_pFadePolygon = CScene2D::Create(7);
	m_pFadePolygon->SetPosition(D3DXVECTOR3(0.0f,0.0f,0.0f),
		D3DXVECTOR3(0.0f,0.0f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f));
	m_pFadePolygon->SetColor(m_colorFade);
	m_pFadePolygon->BindTexture(m_pTexture);
	m_pFadePolygon->SetObjType(CScene::OBJTYPE_FADE);
	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CFade::Uninit(void)
{
	if (m_pFadePolygon != NULL)
	{
		m_pFadePolygon->Uninit();
		m_pFadePolygon = NULL;
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
	if (m_Fade != FADE_NONE)
	{
		m_pFadePolygon->SetColor(m_colorFade);
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

}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext, FADECOLOR fCol)
{
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

	m_pFadePolygon->SetColor(m_colorFade);
}
