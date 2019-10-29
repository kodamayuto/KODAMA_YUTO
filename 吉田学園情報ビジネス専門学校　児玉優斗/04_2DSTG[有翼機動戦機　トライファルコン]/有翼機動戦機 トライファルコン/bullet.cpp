//=============================================================================
//
// プレイヤー処理 [bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "bullet.h"
#include "game.h"
#include "input.h"

//==================================================================
// マクロ定義
//==================================================================
#define MOVE_SPEED		(5.0f)		//移動速度
#define HOMING_ACCURACY (0.03f)		//ホーミング精度
#define BOMBER_COUNT	(60)		//破裂までの時間
#define DELETE_LENGTH (50.0f)
//==================================================================
// 静的メンバ変数宣言
//==================================================================
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[CBullet::TYPE_MAX];				//共有テクスチャへのポインタ

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CBullet::CBullet() : CScene2D(BULLET_PRIORITY)
{

}
CBullet::~CBullet()
{
	CScene2D::~CScene2D();
}

//==================================================================
// 共有テクスチャの読み込み&解放
//==================================================================
HRESULT CBullet::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Bullet_001.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Bullet_002.png", &m_apTexture[1]);


	return S_OK;
}
void CBullet::Unload(void)
{
	for (int nCntTex = 0; nCntTex < CBullet::TYPE_MAX; nCntTex++)
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
CBullet* CBullet::Create(D3DXVECTOR3 pos, float fMove, D3DXVECTOR3 rot,
	CScene2D::ELEMENT element,CBullet::TYPE type,CBullet::AUTHORITY author, bool bEffectUse)
{
	CBullet* pBullet = NULL;
	pBullet = new CBullet;

	if (pBullet != NULL)
	{
		if (author == AUTHOR_ENEMY)
		{
			switch (element)
			{
			case CScene2D::ELEMENT_RED:
				pBullet->m_Col = D3DXCOLOR(1.0f, 0.2f, 0.1f, 1.0f);
				break;
			case CScene2D::ELEMENT_GREEN:
				pBullet->m_Col = D3DXCOLOR(0.1f, 1.0f, 0.2f, 1.0f);
				break;
			case CScene2D::ELEMENT_BLUE:
				pBullet->m_Col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
				break;
			case CScene2D::ELEMENT_SUPER:
				pBullet->m_Col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
				break;

			}
		}
		else if (author == AUTHOR_PLAYER)
		{
			switch (element)
			{
			case CScene2D::ELEMENT_RED:
				pBullet->m_Col = D3DXCOLOR(1.0f, 0.4f, 0.2f, 1.0f);
				break;
			case CScene2D::ELEMENT_GREEN:
				pBullet->m_Col = D3DXCOLOR(0.4f, 1.0f, 0.4f, 1.0f);
				break;
			case CScene2D::ELEMENT_BLUE:
				pBullet->m_Col = D3DXCOLOR(0.2f, 0.4f, 1.0f, 1.0f);
				break;
			case CScene2D::ELEMENT_SUPER:
				pBullet->m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			}
		}

		pBullet->Init(pos, fMove,rot, pBullet->m_Col);				//オーバーロードしたInitで初期化
		pBullet->BindTexture(m_apTexture[type]);	//テクスチャ割り当て
		pBullet->m_Author = author;					//弾の持ち主設定
		pBullet->m_type = type;
		pBullet->SetElement(element);				//弾の属性設定
		pBullet->m_bEffectFlag = bEffectUse;		//エフェクト設定
	}

	return pBullet;
}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CBullet::Init(void)
{
	CScene2D::Init();
	m_fSize = 6.5f;
	SetObjType(CScene::OBJTYPE_BULLET);//オブジェクトの種類設定

	return S_OK;
}
void CBullet::Init(D3DXVECTOR3 pos, float fMove, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	Init();
	m_Rot = rot;
	m_fMove = fMove;
	SetPosition(pos);
	SetColor(col);
}

//==================================================================
// 終了処理
//==================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//==================================================================
// 更新処理
//==================================================================
void CBullet::Update(void)
{
	m_nCount++;

	D3DXVECTOR3 pos = GetPosition();	//現在の位置を取得
	//移動
	pos += D3DXVECTOR3(sinf(m_Rot.y) * m_fMove, cosf(m_Rot.y) * m_fMove, 0.0f);
	//pos += m_move;
	SetPosition(pos);					//位置更新

	CScene2D::Update();

	//エフェクト
	if (m_bEffectFlag == true)
	{
		CEffect::Create(pos, (CEffect::AUTHORITY)m_Author, m_fSize * 1.1f, m_Col);
	}

	switch (m_type)
	{
	case TYPE_BULLET_HOMING:

		if (m_pTarget != NULL)
		{
			if (m_nCount < 300)
			{
				D3DXVECTOR3 TargetPos = m_pTarget->GetPosition();

				float fTargetAngle = atan2f(TargetPos.x - pos.x,
					TargetPos.y - pos.y);

				if ((fTargetAngle + D3DX_PI) - (m_Rot.y + D3DX_PI) > HOMING_ACCURACY)
				{
					if ((fTargetAngle + D3DX_PI) - (m_Rot.y + D3DX_PI) > D3DX_PI)
					{
						m_Rot.y -= HOMING_ACCURACY;
					}
					else
					{
						m_Rot.y += HOMING_ACCURACY;
					}
				}
				else if ((fTargetAngle + D3DX_PI) - (m_Rot.y + D3DX_PI) < -HOMING_ACCURACY)
				{
					if ((fTargetAngle + D3DX_PI) - (m_Rot.y + D3DX_PI) < -D3DX_PI)
					{
						m_Rot.y += HOMING_ACCURACY;
					}
					else
					{
						m_Rot.y -= HOMING_ACCURACY;
					}
				}

				if (m_Rot.y > D3DX_PI)
				{
					m_Rot.y -= D3DX_PI * 2.0f;
				}
				else if (m_Rot.y < -D3DX_PI)
				{
					m_Rot.y += D3DX_PI * 2.0f;

				}

			}
		}
		break;
	}



	if (pos.y <= -DELETE_LENGTH || pos.y >= (SCREEN_HEIGHT + DELETE_LENGTH) ||
		pos.x <= (MOVESTOP_RANGE - DELETE_LENGTH) || pos.x >= (SCREEN_WIDTH + DELETE_LENGTH) - MOVESTOP_RANGE)
	{//画面枠(+オフセット)からはみ出したら消える
		Uninit();
	}
 	else if (m_nCount >= 1000)
	{//長時間画面上にいると消える(メモリ不足対策用)
		Uninit();
	}
}

//==================================================================
// 描画処理
//==================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

