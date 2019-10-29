//=============================================================================
//
// �v���C���[���� [titleLogo.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "titleLogo.h"
#include "game.h"
#include "input.h"

//==================================================================
// �}�N����`
//==================================================================

//==================================================================
// �ÓI�����o�ϐ��錾
//==================================================================
LPDIRECT3DTEXTURE9 CTitleLogo::m_pTexture;				//���L�e�N�X�`���ւ̃|�C���^

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CTitleLogo::CTitleLogo() : CScene(5)
{
	m_pLogo = NULL;
}
CTitleLogo::~CTitleLogo()
{

}

//==================================================================
// ���L�e�N�X�`���̓ǂݍ���&���
//==================================================================
HRESULT CTitleLogo::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TitleLogo000.png", &m_pTexture);

	return S_OK;
}

void CTitleLogo::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==================================================================
// ��������
//==================================================================
CTitleLogo* CTitleLogo::Create()
{
	CTitleLogo* pLogo = NULL;
	pLogo = new CTitleLogo;

	if (pLogo != NULL)
	{
		pLogo->Init();
	}

	return pLogo;
}

//==================================================================
// ����������
//==================================================================
HRESULT CTitleLogo::Init(void)
{
	m_pLogo = CScene2D::Create(5);
	m_pLogo->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2,250.0f,0.0f),
		D3DXVECTOR3(-400.0f,-150.0f,0.0f),
		D3DXVECTOR3(400.0f, 150.0f, 0.0f));
	m_pLogo->BindTexture(m_pTexture);
	m_nCount = 0;
	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CTitleLogo::Uninit(void)
{
		if (m_pLogo != NULL)
		{
			m_pLogo->Uninit();
			m_pLogo = NULL;
		}

	Release();
}

//==================================================================
// �X�V����
//==================================================================
void CTitleLogo::Update(void)
{

}

//==================================================================
// �`�揈��
//==================================================================
void CTitleLogo::Draw(void)
{

}
