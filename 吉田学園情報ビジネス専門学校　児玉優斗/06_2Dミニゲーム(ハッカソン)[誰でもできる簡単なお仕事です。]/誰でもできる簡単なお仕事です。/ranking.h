//=============================================================================
//
// ランキング画面管理クラス処理 [ranking.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "main.h"
#include "Manager.h"

class CSound;
class CScore;
class CScene2D;

//===================================================================
//	マクロ定義
//===================================================================
#define MAX_RANKING (5)
#define MAX_RANKING_TEX (5)

//===================================================================
//	クラスの定義
//===================================================================
class CRanking
{
public:
	CRanking();
	~CRanking();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static void SetRankScore(int nScore);
private:
	static int m_aRankingScore[MAX_RANKING];

	static CScore* m_pRanking[MAX_RANKING];

	//	---<<追加>>---
	static CSound *m_pSound;
	CScene2D * m_pScene2D[MAX_RANKING_TEX];
	int m_nCnt;				//	タイムカウントを進める
	//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★


};
#endif // !_RANKING_H_
