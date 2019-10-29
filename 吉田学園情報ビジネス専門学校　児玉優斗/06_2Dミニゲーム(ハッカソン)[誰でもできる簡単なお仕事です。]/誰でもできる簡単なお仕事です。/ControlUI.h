//=============================================================================
//
// コントロールUI [ControlUI.h]
// Author : Yutaro　Abe
//
//=============================================================================
#ifndef _CONTROLUI_H_
#define _CONTROLUI_H_
#include "scene2D.h"

//=========================================================
// ロゴクラス
//=========================================================
class CControlUI : public CScene2D
{
public:
	CControlUI(CScene::PRIORITY pri);
	~CControlUI();

	void Set(D3DXVECTOR3 StartPos, D3DXVECTOR2 Size);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_StartPos;
};

#endif //!_TITLE_OBJECT_H_
