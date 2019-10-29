//=============================================================================
//
// タイトル画面管理クラス処理 [title.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "Scene3D.h"

#include "TitleObject.h"
#include "PressEnter.h"

class CScene2D;
class CSound;
//===================================================================
//	マクロ定義
//===================================================================
#define MAX_TITLE_TEX (3)


//===================================================================
//	クラスの定義
//===================================================================
class CTitle
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nCount;
	CTitleLogo* m_pTitleLogo;
	CPressEnter* m_pPressEnter;

	//	---<<追加>>---
	static CSound *m_pSound;
	CScene2D * m_pScene2D[MAX_TITLE_TEX];
	int m_nStopTime;
	bool m_bEnterStop;
	int m_nCnt;				//	タイムカウントを進める

	//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★

};
#endif // !_TITLE_H_
