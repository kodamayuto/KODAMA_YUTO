//=============================================================================
//
// ゲーム画面管理クラス処理 [title.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "modeSelect.h"
#include "Manager.h"
#include "fade.h"

//
//
//

int				   CModeSelect::m_nSelectTile = 1;
LPDIRECT3DTEXTURE9 CModeSelect::m_apTexture[TILE_TEX] = {};
LPDIRECT3DTEXTURE9 CModeSelect::m_apTexBG[MAX_BG] = {};

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CModeSelect::CModeSelect()
{
	for (int nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		m_pBG[nCntBG] = NULL;
	}

	for (int nCntSelect = 0; nCntSelect < TILE_NUM; nCntSelect++)
	{
		m_apModeSelectTile[nCntSelect] = NULL;
	}
	m_nCount = 0;
}
CModeSelect::~CModeSelect()
{

}

//==================================================================
// テクスチャ読み込み＆解放
//==================================================================
HRESULT CModeSelect::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ModeSelectTile0001.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ModeSelectTile0002.png", &m_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &m_apTexBG[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTexBG[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTexBG[2]);

	return S_OK;
}
void CModeSelect::Unload(void)
{
	for (int nCntTexBG = 0; nCntTexBG < MAX_BG; nCntTexBG++)
	{
		if (m_apTexBG[nCntTexBG] != NULL)
		{
			m_apTexBG[nCntTexBG]->Release();
			m_apTexBG[nCntTexBG] = NULL;
		}
	}

	for (int nCntTex = 0; nCntTex < TILE_TEX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}

	}
}
//==================================================================
// 生成処理
//==================================================================
CModeSelect* CModeSelect::Create(void)
{
	CModeSelect* pModeSelect = NULL;

	pModeSelect = new CModeSelect;

	if (pModeSelect != NULL)
	{
		pModeSelect->Init();
	}
	return pModeSelect;
}
//==================================================================
// 初期化処理
//==================================================================
HRESULT CModeSelect::Init(void)
{
	CSound*         pSound = CManager::GetSound();

	for (int nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		m_pBG[nCntBG] = CScene2D::Create(4);
		m_pBG[nCntBG]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		m_pBG[nCntBG]->BindTexture(m_apTexBG[nCntBG]);
	}

	for (int nCntSelect = 0; nCntSelect < TILE_NUM; nCntSelect++)
	{
		if (m_apModeSelectTile[nCntSelect] == NULL)
		{
			m_apModeSelectTile[nCntSelect] = CScene2D::Create(5);
			m_apModeSelectTile[nCntSelect]->SetPosition(D3DXVECTOR3(180.0f + 300.0f * nCntSelect,300.0f,0.0f),
				D3DXVECTOR3(-120.0f,-120.0f,0.0f),
				D3DXVECTOR3(120.0f, 120.0f, 0.0f));
			m_apModeSelectTile[nCntSelect]->BindTexture(m_apTexture[0]);
		}
	}

	m_apModeSelectTile[0]->SetUV(D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(0.5f,0.5f));
	m_apModeSelectTile[1]->SetUV(D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
	m_apModeSelectTile[2]->SetUV(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.5f, 1.0f));
	m_apModeSelectTile[3]->SetUV(D3DXVECTOR2(0.5f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	m_apModeSelectTile[m_nSelectTile]->BindTexture(m_apTexture[1]);

	pSound->Play(CSound::SOUND_LABEL_BGM_004);
	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CModeSelect::Uninit(void)
{
	CSound*         pSound = CManager::GetSound();

	for (int nCntData = 0; nCntData < MAX_BG; nCntData++)
	{
		if (m_pBG[nCntData] != NULL)
		{
			m_pBG[nCntData]->Uninit();
			m_pBG[nCntData] = NULL;
		}
	}

	CScene::ReleaseAll();

}

//==================================================================
// 更新処理
//==================================================================
void CModeSelect::Update(void)
{
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CDInputController* pController = CManager::GetController();
	CFade*			pFade = CManager::GetFade();
	CSound*         pSound = CManager::GetSound();
	m_nCount++;

	//テクスチャのUVアニメーション(BG)
	m_nCount++;
	m_pBG[0]->SetUV(D3DXVECTOR2(0.0f, 0.001f * -m_nCount + 0.0f),
		D3DXVECTOR2(1.0f, 0.001f * -m_nCount + 1.0f));

	m_pBG[1]->SetUV(D3DXVECTOR2(0.0002f * -m_nCount + 0.0f, 0.0016f * -m_nCount + 0.0f),
		D3DXVECTOR2(0.0002f * -m_nCount + 1.0f, 0.0016f * -m_nCount + 1.0f));

	m_pBG[2]->SetUV(D3DXVECTOR2(0.0001f * m_nCount + 0.0f, 0.002f * -m_nCount + 0.0f),
		D3DXVECTOR2(0.0001f * m_nCount + 1.0f, 0.002f * -m_nCount + 1.0f));

	//モード選択の処理
	if (pInput != NULL && pFade != NULL)
	{
		m_apModeSelectTile[m_nSelectTile]->BindTexture(m_apTexture[0]);
		m_apModeSelectTile[m_nSelectTile]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		//点滅させるタイルを変える
		if (pInput->GetTrigger(DIK_D) == true ||
			pController != NULL && pController->GetTrigger(CDInputController::DIJS_BUTTON_20) == true)
		{
			m_nSelectTile = (m_nSelectTile + 1) % TILE_NUM;
		}
		if (pInput->GetTrigger(DIK_A) == true ||
			pController != NULL && pController->GetTrigger(CDInputController::DIJS_BUTTON_21) == true)
		{
			m_nSelectTile = (m_nSelectTile + (TILE_NUM - 1)) % TILE_NUM;
		}
		m_apModeSelectTile[m_nSelectTile]->BindTexture(m_apTexture[1]);
		m_apModeSelectTile[m_nSelectTile]->SetColor(D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));

		if (*pFade->GetFade() != CFade::FADE_OUT)
		{
			//ENTERを押したときに、点滅しているタイルの場所に遷移する
			if (pInput->GetTrigger(DIK_RETURN) == true ||
				pController != NULL && pController->GetTrigger(CDInputController::DIJS_BUTTON_1) == true)
			{
				pSound->Play(CSound::SOUND_LABEL_SE_003);
				switch (m_nSelectTile)
				{
				case 0://キャラバンモード
					pFade->SetFade(CManager::MODE_GAME_CARAVAN, CFade::COLOR_WHITE);
					break;
				case 1://チュートリアル
					pFade->SetFade(CManager::MODE_TUTORIAL, CFade::COLOR_WHITE);
					break;
				case 2://ランキング
					pFade->SetFade(CManager::MODE_RANKING, CFade::COLOR_WHITE);
					break;
				case 3://タイトル
					pFade->SetFade(CManager::MODE_TITLE, CFade::COLOR_WHITE);
					break;

				}
			}
		}
	}
}

//==================================================================
// 描画処理
//==================================================================
void CModeSelect::Draw(void)
{

}

