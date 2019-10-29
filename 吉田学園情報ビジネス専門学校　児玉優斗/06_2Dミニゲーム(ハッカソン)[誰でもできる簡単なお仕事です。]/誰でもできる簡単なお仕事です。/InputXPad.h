//=============================================================================
//
// XInput�R���g���[�����͏��� [inputXPad.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _INPUT_X_PAD_H_
#define _INPUT_X_PAD_H_
#include "input.h"

class CInputXPad : public CInput
{
public:
	typedef enum
	{
		XPAD_UP = 0,			//��{�^��
		XPAD_DOWN,				//���{�^��
		XPAD_LEFT,				//���{�^��
		XPAD_RIGHT,				//�E�{�^��
		XPAD_START,				//START�{�^��
		XPAD_BACK,				//BACK�{�^��
		XPAD_LEFT_THUMB,		//���X�e�B�b�N��������(L3)
		XPAD_RIGHT_THUMB,		//�E�X�e�B�b�N��������(R3)
		XPAD_LEFT_SHOULDER,		//LB(L1)�{�^��
		XPAD_RIGHT_SHOULDER,	//RB(R1)�{�^��
		XPAD_A,					//A�{�^��
		XPAD_B,					//B�{�^��
		XPAD_X,					//X�{�^��
		XPAD_Y,					//Y�{�^��
		XPAD_LEFT_TRIGGER,		//LT(L2)�{�^��
		XPAD_RIGHT_TRIGGER,		//RT(R2)�{�^��
		XPAD_RIGHTSTICK_UP,		//�E�X�e�B�b�N�����
		XPAD_RIGHTSTICK_DOWN,	//�E�X�e�B�b�N������
		XPAD_RIGHTSTICK_LEFT,	//�E�X�e�B�b�N�E����
		XPAD_RIGHTSTICK_RIGHT,	//�E�X�e�B�b�N������
		XPAD_MAX
	}XPAD_KEY;

	typedef struct
	{
		bool abPadStatePress[XPAD_MAX];			//�v���X���
		bool abPadStateTrigger[XPAD_MAX];		//�g���K�[���
		bool abPadStateRelease[XPAD_MAX];		//�����[�X���
		bool abPadStateRepeat[XPAD_MAX];		//���s�[�g���
		int nCntRepeatTime[XPAD_MAX];
	}XPAD_STATE;
	CInputXPad();
	~CInputXPad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void    Uninit(void);
	void    Update(void);

	bool GetPress(XPAD_KEY key);
	bool GetTrigger(XPAD_KEY key);
	bool GetRelease(XPAD_KEY key);
	bool GetRepeat(XPAD_KEY key);
	bool GetConnect(void) { return m_bConnect; };

	SHORT GetLStickRotX(void) { return m_sLStickRotX; };
	SHORT GetLStickRotY(void) { return m_sLStickRotY; };
	SHORT GetRStickRotX(void) { return m_sRStickRotX; };
	SHORT GetRStickRotY(void) { return m_sRStickRotY; };

private:
	void SetInputState(XPAD_KEY key,bool bPress);
	WORD ThumbToDPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);
	void CheckDeadZone(XINPUT_STATE& state);

	XPAD_STATE m_State;			//���͏��
	static int m_nCntXPadNum;	//XInput�R���g���[���[�̐ڑ���
	int m_nID;					//�v���C���[ID
	bool m_bConnect;			//�Ȃ����Ă��邩

	SHORT m_sLStickRotX;
	SHORT m_sLStickRotY;
	SHORT m_sRStickRotX;
	SHORT m_sRStickRotY;
};
#endif // !_INPUT_X_PAD_H_
