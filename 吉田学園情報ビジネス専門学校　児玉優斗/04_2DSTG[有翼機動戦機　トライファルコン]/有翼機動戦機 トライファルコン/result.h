//=============================================================================
//
// リザルト画面管理クラス処理 [result.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "Score.h"

//
//
//
#define NUM_ABSORB_DIGIT (4)

//
//
//
class CScene2D;
class CResult
{
public:
	CResult();
	~CResult();

	static CResult* Create(void);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore*			GetScore(void) { return m_pScore; };

private:
	static CScore*          m_pScore;
	static LPDIRECT3DTEXTURE9 m_apTexture[4];
	CScene2D*				m_apBG[3];
	int m_nCount;
};
#endif // !_RESULT_H_
