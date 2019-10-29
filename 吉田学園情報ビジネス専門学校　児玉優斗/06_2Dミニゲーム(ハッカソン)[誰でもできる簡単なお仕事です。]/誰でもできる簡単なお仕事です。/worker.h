//=============================================================================
//
// çÏã∆àıèàóù [woeker.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _WOEKER_H_
#define _WOEKER_H_
#include "scene2D.h"

//=========================================================
// ÉçÉSÉNÉâÉX
//=========================================================
class CWoker : public CScene2D
{
public:
	CWoker(CScene::PRIORITY pri);
	~CWoker();

	void Set(D3DXVECTOR3 StartPos, D3DXVECTOR2 Size,int nTypeState);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


private:
	D3DXVECTOR3 m_move;
	int	m_nCount;
	int m_nType;
	int m_nTypeState;

};

#endif //!_TITLE_OBJECT_H_