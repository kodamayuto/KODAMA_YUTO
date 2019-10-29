//=============================================================================
//
// �����L���O��ʊǗ��N���X���� [ranking.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "ranking.h"
#include "Manager.h"
#include "fade.h"
//
//
//
int CRanking::m_aRankingScore[MAX_RANKING] = {};
LPDIRECT3DTEXTURE9 CRanking::m_apTexture[4] = {};

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CRanking::CRanking()
{
	for (int nCntLength = 0; nCntLength < MAX_RANKING; nCntLength++)
	{
		m_apScore[nCntLength] = NULL;
	}
	for (int nCntBG = 0; nCntBG < 3; nCntBG++)
	{
		m_apBG[nCntBG] = NULL;
	}
	m_nCount = 0;

}
CRanking::~CRanking()
{

}

CRanking* CRanking::Create(void)
{
	CRanking* pRanking = NULL;

	pRanking = new CRanking;

	if (pRanking != NULL)
	{
		pRanking->Init();
	}
	return pRanking;
}
//==================================================================
// �e�N�X�`���ǂݍ��݁����
//==================================================================
HRESULT CRanking::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ranking000.png", &m_apTexture[3]);

	return S_OK;
}
void CRanking::Unload(void)
{
	for (int nCntTex = 0; nCntTex < 4; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}

	}
}
//==================================================================
// ����������
//==================================================================
HRESULT CRanking::Init(void)
{
	for (int nCntBG = 0; nCntBG < 3; nCntBG++)
	{
		m_apBG[nCntBG] = CScene2D::Create(4);
		m_apBG[nCntBG]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		m_apBG[nCntBG]->BindTexture(m_apTexture[nCntBG]);
	}

	for (int nCntLength = 0; nCntLength < MAX_RANKING; nCntLength++)
	{
		m_apScore[nCntLength] = CScore::Create(D3DXVECTOR3(700.0f,(nCntLength * 100.0f) + 150.0f,0.0f));
		m_apScore[nCntLength]->SetScore(m_aRankingScore[nCntLength]);
	}
	CScene2D *pRanking = CScene2D::Create(4);
	pRanking->SetPosition(D3DXVECTOR3(100.0f, 100.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(400.0f, 100.0f, 0.0f));
	pRanking->BindTexture(m_apTexture[3]);

	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CRanking::Uninit(void)
{
	CSound* pSound = CManager::GetSound();
	pSound->StopAll();

	CScene::ReleaseAll();
}

//==================================================================
// �X�V����
//==================================================================
void CRanking::Update(void)
{
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CDInputController* pController = CManager::GetController();

	CFade*			pFade = CManager::GetFade();

	m_nCount++;
	m_apBG[0]->SetUV(D3DXVECTOR2(0.0f, 0.001f * -m_nCount + 0.0f),
		D3DXVECTOR2(1.0f, 0.001f * -m_nCount + 1.0f));

	m_apBG[1]->SetUV(D3DXVECTOR2(0.0002f * -m_nCount + 0.0f, 0.0016f * -m_nCount + 0.0f),
		D3DXVECTOR2(0.0002f * -m_nCount + 1.0f, 0.0016f * -m_nCount + 1.0f));

	m_apBG[2]->SetUV(D3DXVECTOR2(0.0001f * m_nCount + 0.0f, 0.002f * -m_nCount + 0.0f),
		D3DXVECTOR2(0.0001f * m_nCount + 1.0f, 0.002f * -m_nCount + 1.0f));

	if (pInput != NULL && pFade != NULL)
	{
		if (*pFade->GetFade() != CFade::FADE_OUT)
		{
			if (pInput->GetTrigger(DIK_RETURN) == true ||
				pController != NULL && pController->GetTrigger(CDInputController::DIJS_BUTTON_1) == true)
			{
				pFade->SetFade(CManager::MODE_SELECT, CFade::COLOR_WHITE);
			}
		}
	}
}

//==================================================================
// �`�揈��
//==================================================================
void CRanking::Draw(void)
{

}

//==================================================================
// �����L���O�ݒ菈��
//==================================================================
void CRanking::SetRankScore(int nScore)
{
	int nRankScore = nScore;
	int nCntNum,nCntNum2;			//�X�R�A�̌����̃J�E���^�[

	for (int nCntLength = 0; nCntLength < MAX_RANKING; nCntLength++)
	{// ���ʕύX
		if (m_aRankingScore[nCntLength] < nScore)
		{// �㏑���j�~�̂��߂ɐ����𓦂���
			nCntNum = m_aRankingScore[nCntLength];
			m_aRankingScore[nCntLength] = nRankScore;

			// �֌W�Ȃ��Ƃ���͕��ׂȂ�for��
			for (int nCntLength2 = nCntLength + 1; nCntLength2 < MAX_RANKING; nCntLength2++)
			{// �����������Ƃ��̎��̐�������בւ�
				nCntNum2 = m_aRankingScore[nCntLength2];
				m_aRankingScore[nCntLength2] = nCntNum;
				nCntNum = nCntNum2;
			}
			break;
		}
	}

}
