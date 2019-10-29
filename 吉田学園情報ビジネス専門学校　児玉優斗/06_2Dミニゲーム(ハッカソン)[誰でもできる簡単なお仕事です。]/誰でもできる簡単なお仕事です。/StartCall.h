//=============================================================================
//
// スタートコール処理 [StartCall.h]
// Author : Yutaro　Abe
//
//=============================================================================
#ifndef _START_CALL_H_
#define _START_CALL_H_
#include "scene2D.h"

class CSound;
//=========================================================
// ロゴクラス
//=========================================================
class CStartCall : public CScene2D
{
public:
	CStartCall(CScene::PRIORITY pri);
	~CStartCall();

	void Set(D3DXVECTOR3 StartPos, D3DXVECTOR2 Size);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static bool GetStartCallEnd(void) { return m_bStop; };
private:
	static CSound *m_pSound;
	D3DXVECTOR3 m_StartPos;
	float		m_fAddValue;
	static int	m_nCount;

	static bool m_bStop;
};

#endif //!_START_CALL_H_
