//=============================================================================
//
// 制限時間クラス処理 [Time.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "Time.h"
#include "Manager.h"
#include "scene2D.h"
//
//
//
LPDIRECT3DTEXTURE9 CTime::m_pTexture = NULL;
//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CTime::CTime() : CScene(5)
{
	for (int nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		m_pNumber[nCntTime] = NULL;
	}
	m_pFrame = NULL;
}
CTime::~CTime()
{

}

//==================================================================
// 共有テクスチャの読み込み＆解放
//==================================================================
HRESULT CTime::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TimerFrame000.png", &m_pTexture);

	return S_OK;
}
void CTime::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==================================================================
// 生成処理
//==================================================================
CTime* CTime::Create(D3DXVECTOR3 pos, bool bUseFrame)
{
	CTime* pTime = NULL;

	pTime = new CTime;

	pTime->Init(pos,bUseFrame);

	return pTime;
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CTime::Init(D3DXVECTOR3 pos, bool bUseFrame)
{
	Init();
	m_pos = pos;
	m_bUseFrame = bUseFrame;

	for (int nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		m_pNumber[nCntTime] = CNumber::Create(D3DXVECTOR3(m_pos.x - (40.0f * nCntTime), m_pos.y, 0.0f),
			D3DXVECTOR2(35.0f, 50.0f),
			0);

	}

	if (m_bUseFrame == true)
	{
		m_pFrame = CScene2D::Create(5);
		m_pFrame->SetPosition(m_pos,D3DXVECTOR3(-95.0f,-20.0f,0.0f),D3DXVECTOR3(60.0f,65.0f,0.0f));
		m_pFrame->BindTexture(m_pTexture);
	}
	SetTime(0);
	return S_OK;
}
HRESULT CTime::Init(void)
{
	return S_OK;
}
//==================================================================
// 終了処理
//==================================================================
void CTime::Uninit(void)
{
	for (int nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		if (m_pNumber[nCntTime] != NULL)
		{
			m_pNumber[nCntTime]->Uninit();

			delete m_pNumber[nCntTime];
			m_pNumber[nCntTime] = NULL;

		}
	}

	if (m_pFrame != NULL)
	{
		m_pFrame->Uninit();

		m_pFrame = NULL;
	}

	Release();

}

//==================================================================
// 更新処理
//==================================================================
void CTime::Update(void)
{
	m_nCount++;

	if (m_nCount % 60 == 0)
	{
		m_nTime--;

	}

	if (m_nTime <= 0)
	{
		m_nTime = 0;
	}

	for (int nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		int nDigit = m_nTime % (int)pow(10, nCntTime + 1) / (int)pow(10, nCntTime);
		m_pNumber[nCntTime]->SetNumber(nDigit);
		m_pNumber[nCntTime]->Update();
	}

}

//==================================================================
// 描画処理
//==================================================================
void CTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		m_pNumber[nCntTime]->Draw();
	}

}

//==================================================================
// タイマー設定処理
//==================================================================
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;


	for (int nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		int nDigit = m_nTime % (int)pow(10, nCntTime + 1) / (int)pow(10, nCntTime);
		m_pNumber[nCntTime]->SetNumber(nDigit);
	}

}

void CTime::SetColor(D3DXCOLOR col)
{
	for (int nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		m_pNumber[nCntTime]->SetColor(col);
	}
}