//=============================================================================
//
// 荷物クラス処理 [Baggage.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BAGGAGE_H_
#define _BAGGAGE_H_

#include "scene2D.h"
#include "Manager.h"
//=============================================================================
//	クラス定義
//=============================================================================
class CBaggage : public CScene2D
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_CARDBOARD_BOX,		//段ボール箱
		TYPE_LETTER,			//手紙
		TYPE_ENVELOVE,			//封筒
		TYPE_TRASH,				//ゴミ
		TYPE_MAX
	}BAGGAGE_TYPE;		//荷物のタイプ

	typedef enum
	{
		STATE_NEUTRAL = 0,			//通常状態(静止)
		STATE_MOVE,					//移動している状態
		STATE_TRASH,				//ゴミ箱に飛ばされている状態
		STATE_MAX
	}BAGGAGE_STATE;

	CBaggage();
	CBaggage(CScene::PRIORITY pri);
	~CBaggage();

	void Set(D3DXVECTOR3 pos, BAGGAGE_TYPE type);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	BAGGAGE_TYPE GetType(void) { return m_Type; };

	void SetState(BAGGAGE_STATE state) { m_State = state; };
	void SetBPosition(D3DXVECTOR3 pos) { SetPosition(pos); };

	void SetMoveDir(CManager::DIRECTION dir);
private:
	BAGGAGE_TYPE m_Type;		//荷物のタイプ
	BAGGAGE_STATE m_State;		//荷物の状態

	float m_fRot;
	//Leap用
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_GoalPos;
};
#endif // !_BAGGAGE_H_
