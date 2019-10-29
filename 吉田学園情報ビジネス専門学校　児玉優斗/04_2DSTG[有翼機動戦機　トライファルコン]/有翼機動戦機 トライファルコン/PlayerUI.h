//=============================================================================
//
// プレイヤーUIクラス処理 [PlayerUI.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _PLAYER_UI_H_
#define _PLAYER_UI_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"

class CGauge;
//
//
//

#define UI_TEX_NUM (3)
class CPlayerUI : public CScene
{
public:
	CPlayerUI();
	~CPlayerUI();

	static HRESULT Load(void);
	static void    Unload(void);
	static CPlayerUI* Create(void);

	HRESULT Init(void);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	void    SetLife(int nLife);
	void    SetGauge(ELEMENT elem,float fElementGauge);
	void    SetStock(int nStock);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[UI_TEX_NUM];			//テクスチャ数
	CScene2D* m_apVitarity[MAX_VITALITY];		//体力
	int m_nVITcount;

	CScene2D* m_apStock[MAX_STOCK];				//残機
	int m_nStockCount;
	CGauge* m_apGauge[3];						//ゲージ
};
#endif // !_PLAYER_UI_H_
