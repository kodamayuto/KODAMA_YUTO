//=============================================================================
//
// ライフ処理 [life.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_
#include "scene2D.h"

//=========================================================
// ロゴクラス
//=========================================================
class CLife : public CScene2D
{
public:
	CLife(CScene::PRIORITY pri);
	~CLife();

	void Set(D3DXVECTOR3 StartPos, D3DXVECTOR2 Size);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddLife(int nValue);
	static int GetCount(void){ return m_nCount; }

private:
	D3DXVECTOR3 m_StartPos;
	float		m_fvalu;
	float		m_fsizeValue;
	float		m_fposValue;
	static int	m_nCount;
	bool		m_bUse;
};

#endif //!_TITLE_OBJECT_H_
