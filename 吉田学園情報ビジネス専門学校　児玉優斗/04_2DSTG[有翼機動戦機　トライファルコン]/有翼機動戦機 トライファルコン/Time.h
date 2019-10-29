//=============================================================================
//
// êßå¿éûä‘ÉNÉâÉXèàóù [Time.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "number.h"
#include "scene.h"

//
//
//
#define MAX_TIME (999)		//êßå¿éûä‘ÇÃç≈ëÂíl

//
//
//
class CScene2D;

class CTime : public CScene
{
public:
	CTime();
	~CTime();
	static HRESULT Load(void);
	static void Unload(void);

	static CTime* Create(D3DXVECTOR3 pos, bool bUseFrame);

	HRESULT Init(D3DXVECTOR3 pos, bool bUseFrame);
	HRESULT Init(void);
	void   Uninit(void);
	void   Update(void);
	void   Draw(void);

	void   SetTime(int nTime);
	void   SetColor(D3DXCOLOR col);
	int    GetTime(void) { return m_nTime; };
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CNumber* m_pNumber[3];
	CScene2D* m_pFrame;
	int   m_nTime;
	bool  m_bUseFrame;
	D3DXVECTOR3 m_pos;

protected:
};

#endif