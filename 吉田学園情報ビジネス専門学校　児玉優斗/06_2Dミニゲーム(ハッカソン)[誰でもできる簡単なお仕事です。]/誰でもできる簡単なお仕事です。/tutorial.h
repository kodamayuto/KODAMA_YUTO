//=============================================================================
//
// ゲーム画面管理クラス処理 [tutorial.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "main.h"
#include "Manager.h"

class CSound;
class CScene2D;
#define MAX_TITLE_TEX (3)

//===================================================================
//	クラスの定義
//===================================================================
class CTutorial
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	//	---<<追加>>---
	static CSound *m_pSound;
	CScene2D * m_pScene2D[MAX_TITLE_TEX];
	int m_nCnt;				//	タイムカウントを進める
							//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★

private:
};
#endif // !_TUTORIAL_H_
