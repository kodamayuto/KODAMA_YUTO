//=============================================================================
//
// PRESS ENTER èàóù [PressEnter.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _PRESS_ENTER_H_
#define _PRESS_ENTER_H_
#include "scene2D.h"

//=========================================================
// PRESS ENTER ÉNÉâÉX
//=========================================================
class CPressEnter : public CScene2D
{
public:
	CPressEnter();
	CPressEnter(CScene::PRIORITY pri);
	~CPressEnter();

	void Set(D3DXVECTOR3 pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Enter(void) { m_bEnter = true; };
private:
	bool m_bDraw;
	bool m_bEnter;
};



#endif //!_PRESS_ENTER_H_