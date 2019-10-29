//=============================================================================
//
// �ו��N���X���� [Baggage.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BAGGAGE_H_
#define _BAGGAGE_H_

#include "scene2D.h"
#include "Manager.h"
//=============================================================================
//	�N���X��`
//=============================================================================
class CBaggage : public CScene2D
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_CARDBOARD_BOX,		//�i�{�[����
		TYPE_LETTER,			//�莆
		TYPE_ENVELOVE,			//����
		TYPE_TRASH,				//�S�~
		TYPE_MAX
	}BAGGAGE_TYPE;		//�ו��̃^�C�v

	typedef enum
	{
		STATE_NEUTRAL = 0,			//�ʏ���(�Î~)
		STATE_MOVE,					//�ړ����Ă�����
		STATE_TRASH,				//�S�~���ɔ�΂���Ă�����
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
	BAGGAGE_TYPE m_Type;		//�ו��̃^�C�v
	BAGGAGE_STATE m_State;		//�ו��̏��

	float m_fRot;
	//Leap�p
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_GoalPos;
};
#endif // !_BAGGAGE_H_
