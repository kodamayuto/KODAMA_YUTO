//=============================================================================
//
// 荷物配送機クラス処理 [truck.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TRUCK_H_
#define _TRUCK_H_

#include "scene.h"
#include "Baggage.h"

class CTruck : public CScene
{
public:
	CTruck();
	CTruck(CScene::PRIORITY pri);
	~CTruck();

	void Set(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BaggageCreate(void);
private:
	CScene2D* m_pBaggagePolygon[3];
	CBaggage::BAGGAGE_TYPE m_CreateBaggageType[3];
	CBaggage* m_pBaggage;
};

#endif // !_TRUCK_H_
