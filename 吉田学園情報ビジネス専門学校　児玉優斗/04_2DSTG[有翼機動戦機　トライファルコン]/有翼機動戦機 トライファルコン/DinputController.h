//=============================================================================
//
// ���͏��� [DInputConrtroller.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _DINPUTCONTROLLER_H_
#define _DINPUTCONTROLLER_H_

#include "main.h"
#include "input.h"

//===================================================================
//	�}�N����`
//===================================================================
#define DI_JOY_I_INPUT   (1000)  // �X�e�B�b�N�̕������͎�t���s���͈�

class CDInputController : public CInput
{
public:
	typedef enum
	{
		DIJS_BUTTON_0 = 0,  // X�{�^��
		DIJS_BUTTON_1,      // A�{�^��
		DIJS_BUTTON_2,      // B�{�^��
		DIJS_BUTTON_3,      // Y�{�^��
		DIJS_BUTTON_4,      // LB�{�^��
		DIJS_BUTTON_5,      // RB�{�^��
		DIJS_BUTTON_6,      // LT�{�^��
		DIJS_BUTTON_7,      // RT�{�^��
		DIJS_BUTTON_8,      // BACK�{�^��
		DIJS_BUTTON_9,      // START�{�^��
		DIJS_BUTTON_10,     // ���A�i���O�X�e�B�b�N���������
		DIJS_BUTTON_11,     // ���A�i���O�X�e�B�b�N����������
		DIJS_BUTTON_12,     // ���A�i���O�X�e�B�b�N�E��������
		DIJS_BUTTON_13,     // ���A�i���O�X�e�B�b�N����������
		DIJS_BUTTON_14,     // �E�A�i���O�X�e�B�b�N���������
		DIJS_BUTTON_15,     // �E�A�i���O�X�e�B�b�N����������
		DIJS_BUTTON_16,     // �E�A�i���O�X�e�B�b�N�E��������
		DIJS_BUTTON_17,     // �E�A�i���O�X�e�B�b�N����������
		DIJS_BUTTON_18,     // �\���L�[���������
		DIJS_BUTTON_19,     // �\���L�[����������
		DIJS_BUTTON_20,     // �\���L�[�E��������
		DIJS_BUTTON_21,     // �\���L�[����������
							// �ȉ����蓖�ĂȂ�
							DIJS_BUTTON_22,
							DIJS_BUTTON_23,
							DIJS_BUTTON_24,
							DIJS_BUTTON_25,
							DIJS_BUTTON_26,
							DIJS_BUTTON_27,
							DIJS_BUTTON_28,
							DIJS_BUTTON_29,
							DIJS_BUTTON_30,
							DIJS_BUTTON_31,
							DIJS_BUTTON_MAX
	}PADBUTTON;

	CDInputController();
	~CDInputController();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void    Uninit(void);
	void    Update(void);
	bool    GetPress(int nButton) { return (m_aJoyState[nButton] & 0x80) ? true : false; };
	bool    GetTrigger(int nButton) { return (m_aJoyStateTrigger[nButton] & 0x80) ? true : false; };

private:
	BYTE m_aJoyState[DIJS_BUTTON_MAX];           // �W���C�p�b�h�̓��͏��(�v���X���)
	BYTE m_aJoyStateTrigger[DIJS_BUTTON_MAX];    // �W���C�p�b�h�̓��͏��(�g���K�[���)

	float m_Radian;                              // �\���L�[�̃��W�A�����i�[����
	float m_Xziku;                               // ���A�i���O�X�e�B�b�N��X�����i�[����
	float m_Yziku;                               // ���A�i���O�X�e�B�b�N��Y�����i�[����

};
#endif