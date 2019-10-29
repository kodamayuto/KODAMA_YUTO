//=============================================================================
//
// タイトルロゴ処理 [TitleObject.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TITLE_OBJECT_H_
#define _TITLE_OBJECT_H_
#include "scene2D.h"

//=========================================================
// ロゴクラス
//=========================================================
class CTitleLogo : public CScene2D
{
public:
	CTitleLogo();
	CTitleLogo(CScene::PRIORITY pri);
	~CTitleLogo();

	void Set(D3DXVECTOR3 StartPos, D3DXVECTOR3 GoalPos,D3DXVECTOR2 Size);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void TitleFade(void);
private:
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_GoalPos;
};

#endif //!_TITLE_OBJECT_H_
