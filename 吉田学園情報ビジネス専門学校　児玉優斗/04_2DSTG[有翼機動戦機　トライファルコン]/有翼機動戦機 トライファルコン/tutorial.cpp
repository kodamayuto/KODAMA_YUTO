//=============================================================================
//
// �Q�[����ʊǗ��N���X���� [tutorial.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "tutorial.h"
#include "fade.h"
#include "sound.h"

//==================================================================
// �ÓI�����o�ϐ�
//==================================================================
CPlayer* CTutorial::m_pPlayer = NULL;
CPlayerUI* CTutorial::m_pPlayerUI = NULL;
int CTutorial::m_nRespawnTimer = -1;

LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CTutorial::CTutorial()
{
	m_nRespawnTimer = -1;
}
CTutorial::~CTutorial()
{

}

//==================================================================
// ���L�e�N�X�`���̓ǂݍ���&���
//==================================================================
HRESULT CTutorial::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Tutorial.jpg", &m_pTexture);
	return S_OK;
}
void CTutorial::Unload(void)
{
	//�e�N�X�`���j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//==================================================================
// ��������
//==================================================================
CTutorial* CTutorial::Create(void)
{
	CTutorial* pTutorial = NULL;

	pTutorial = new CTutorial;

	if (pTutorial != NULL)
	{
		pTutorial->Init();
	}
	return pTutorial;
}
//==================================================================
// ����������
//==================================================================
HRESULT CTutorial::Init(void)
{
	//�I�u�W�F�N�g�̐���

	m_pPlayerUI = CPlayerUI::Create();
	CPlayer::SetStock();
	m_pPlayer = CPlayer::Create();

	CBg::Create();

	//�`���[�g���A���̐���
	m_pTutorial = CScene2D::Create(5);
	if (m_pTutorial != NULL)
	{
		m_pTutorial->SetPosition(D3DXVECTOR3(SCREEN_WIDTH - 330.0f,0.0f,0.0f),
									D3DXVECTOR3(0.0f,0.0f,0.0f),
									D3DXVECTOR3(330.0f,SCREEN_HEIGHT,0.0f));
		m_pTutorial->BindTexture(m_pTexture);
	}
	//BGM�炷
	CSound* pSound = CManager::GetSound();
	pSound->StopAll();
	if (pSound != NULL)
	{
		pSound->Play(CSound::SOUND_LABEL_BGM_002);
	}

	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CTutorial::Uninit(void)
{
	CSound* pSound = CManager::GetSound();

	//�I�u�W�F�N�g�S�j��
	if (m_pTutorial != NULL)
	{
		m_pTutorial->Uninit();
		m_pTutorial = NULL;
	}
	CScene::ReleaseAll();

	m_pPlayer = NULL;
	m_pPlayerUI = NULL;

	if (pSound != NULL)
	{
		pSound->StopAll();
	}
}

//==================================================================
// �X�V����
//==================================================================
void CTutorial::Update(void)
{
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CDInputController* pController = CManager::GetController();
	CFade*			pFade = CManager::GetFade();

	if (pInput->GetTrigger(DIK_P) == true || pController != NULL && pController->GetTrigger(CDInputController::DIJS_BUTTON_9) == true)
	{
		CManager::PauseModeChange();
	}

	//�v���C���[�̍ďo��
	if (m_nRespawnTimer >= -1)
	{
		m_nRespawnTimer--;

		if (m_nRespawnTimer == 0)
		{
			if (CPlayer::GetStock() >= 0)
			{
				m_pPlayer = NULL;
				m_pPlayer = CPlayer::Create();

				m_nRespawnTimer = -1;
			}
		}
	}


}

//==================================================================
// �`�揈��
//==================================================================
void CTutorial::Draw(void)
{

}

