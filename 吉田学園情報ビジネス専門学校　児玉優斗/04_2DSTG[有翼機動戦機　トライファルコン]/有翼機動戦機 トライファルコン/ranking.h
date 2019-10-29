//=============================================================================
//
// ランキング画面管理クラス処理 [ranking.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "Score.h"

//
//
//
#define MAX_RANKING (5)

//
//
//
class CScene2D;
class CRanking
{
public:
	CRanking();
	~CRanking();

	static CRanking* Create(void);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetRankScore(int nScore);
private:
	CScore* m_apScore[MAX_RANKING];
	static LPDIRECT3DTEXTURE9 m_apTexture[4];
	CScene2D*				m_apBG[3];
	int		m_nCount;
	static int m_aRankingScore[MAX_RANKING];
};
#endif // !_RESULT_H_
