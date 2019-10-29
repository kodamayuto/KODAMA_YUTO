//=============================================================================
//
// ゲームUI [GAmeUI.h]
// Author : Yutaro　Abe
//
//=============================================================================
#ifndef _GAMEUI_H_
#define _GAMEUI_H_
#include "scene2D.h"


#define MAX_UI (6)
//=========================================================
// ロゴクラス
//=========================================================
class CGameUI : public CScene
{
public:
	CGameUI(CScene::PRIORITY pri);
	~CGameUI();

	void Set(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CScene2D *m_pScene2D[MAX_UI];
	int m_nValue;
	bool m_bUse[4];
	int m_nCouter[4];
	D3DXVECTOR3 m_move;
	int m_nCount;
	int m_State;

};

#endif //!_TITLE_OBJECT_H_
