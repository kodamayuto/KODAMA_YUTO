//=============================================================================
//
// â◊ï®îªíËäÌÉNÉâÉXèàóù [JudgeBaggage.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _JUDGE_BAGGAGE_H_
#define _JUDGE_BAGGAGE_H_

#include "scene2D.h"
#include "Baggage.h"

class CSound;

class CJudgeBaggage : public CScene2D
{
public:
	CJudgeBaggage();
	CJudgeBaggage(CScene::PRIORITY pri);
	~CJudgeBaggage();

	void Set(D3DXVECTOR3 pos,D3DXVECTOR2 Size,CBaggage::BAGGAGE_TYPE type);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool Collision(CScene* pHitObj);
private:
	void HitCheck(void);


	CBaggage::BAGGAGE_TYPE m_Type;

	D3DXVECTOR3 m_CollisionRectMin;
	D3DXVECTOR3 m_CollisionRectMax;

	static CSound *m_pSound;

	D3DXVECTOR2 m_Size;
	int m_nBigTimer;
	int m_nColorTimer;


};

#endif //!_JUDGE_BAGGAGE_H_
