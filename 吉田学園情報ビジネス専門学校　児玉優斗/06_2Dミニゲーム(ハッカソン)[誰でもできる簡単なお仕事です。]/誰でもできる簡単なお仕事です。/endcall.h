//=============================================================================
//
// エンドコール処理 [endcall.h]
// Author : Yutaro　Abe
//
//=============================================================================
#ifndef _ENDCALL_H_
#define _ENDCALL_H_
#include "scene2D.h"

class CSound;

//=========================================================
// ロゴクラス
//=========================================================
class CEndCall : public CScene2D
{
public:
	CEndCall(CScene::PRIORITY pri);
	~CEndCall();

	void Set(D3DXVECTOR3 StartPos, D3DXVECTOR2 Size);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static CSound *m_pSound;

	D3DXVECTOR3 m_StartPos;
	float		m_fAddValue;

};

#endif //!_TITLE_OBJECT_H_
