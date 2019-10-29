//=============================================================================
//
// inputx���� [inputx.h]
// Author : komatsu keisuke
//
//=============================================================================
#ifndef _INPUTX_H_
#define _INPUTX_H_

#include "main.h"

//=============================================================================
// �W���C�p�b�h�̍\����
//=============================================================================
class CInputX
{

public:
	typedef enum
	{
		INPUT_JOYSTATE_NOTPUSH = 0,
		INPUT_JOYSTATE_PUSH,
		INPUT_JOYSTATE_NONE,
		INPUT_JOYSTATE_MAX
	}InputJoyState;


	CInputX();
	~CInputX();
	void Init(void);
	void Uninit(void);
	void Update(void);

	static InputJoyState GetJoystate(void);
	static bool GetbConnect(void);
private:
	static InputJoyState m_nJoypadState;		//�W���C�p�b�h�̏��
	static bool m_bConnectionJoypad;			//�W���C�p�b�h�̐ڑ����
	static LPDIRECTINPUTDEVICE8 m_pDevJoyPad;			//���̓f�o�C�X(�W���C�p�b�h)�ւ̃|�C���^

};

#endif