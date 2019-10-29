//=============================================================================
//
// スコアクラス処理 [Score.h]
// Author : Kodama Yuto
//
//=============================================================================

#ifndef _SCORE_H_
#define _SCORE_H_

#include "scene.h"

#define MAX_SCOREDIGIT (9)	//最大桁数
class CNumber;

class CScore : public CScene
{
public:
	CScore();
	~CScore();
	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CScore* Create(D3DXVECTOR3 pos);

	void SetScore(int nScore);
	int GetScore(void) { return (int)m_nScore; };
	void AddScore(int nValue);

private:
	CNumber* m_pNumber[MAX_SCOREDIGIT];
	int m_nScore;
	D3DXVECTOR3 m_pos;
};

#endif // !_SCORE_H_
