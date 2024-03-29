//=============================================================================
//
// 入力処理 [DInputConrtroller.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _DINPUTCONTROLLER_H_
#define _DINPUTCONTROLLER_H_

#include "main.h"
#include "input.h"

//===================================================================
//	マクロ定義
//===================================================================
#define DI_JOY_I_INPUT   (1000)  // スティックの方向入力受付を行う範囲

class CDInputController : public CInput
{
public:
	typedef enum
	{
		DIJS_BUTTON_0 = 0,  // Xボタン
		DIJS_BUTTON_1,      // Aボタン
		DIJS_BUTTON_2,      // Bボタン
		DIJS_BUTTON_3,      // Yボタン
		DIJS_BUTTON_4,      // LBボタン
		DIJS_BUTTON_5,      // RBボタン
		DIJS_BUTTON_6,      // LTボタン
		DIJS_BUTTON_7,      // RTボタン
		DIJS_BUTTON_8,      // BACKボタン
		DIJS_BUTTON_9,      // STARTボタン
		DIJS_BUTTON_10,     // 左アナログスティック上方向入力
		DIJS_BUTTON_11,     // 左アナログスティック下方向入力
		DIJS_BUTTON_12,     // 左アナログスティック右方向入力
		DIJS_BUTTON_13,     // 左アナログスティック左方向入力
		DIJS_BUTTON_14,     // 右アナログスティック上方向入力
		DIJS_BUTTON_15,     // 右アナログスティック下方向入力
		DIJS_BUTTON_16,     // 右アナログスティック右方向入力
		DIJS_BUTTON_17,     // 右アナログスティック左方向入力
		DIJS_BUTTON_18,     // 十字キー上方向入力
		DIJS_BUTTON_19,     // 十字キー下方向入力
		DIJS_BUTTON_20,     // 十字キー右方向入力
		DIJS_BUTTON_21,     // 十字キー左方向入力
							// 以下割り当てなし
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
	BYTE m_aJoyState[DIJS_BUTTON_MAX];           // ジョイパッドの入力情報(プレス情報)
	BYTE m_aJoyStateTrigger[DIJS_BUTTON_MAX];    // ジョイパッドの入力情報(トリガー情報)

	float m_Radian;                              // 十字キーのラジアンを格納する
	float m_Xziku;                               // 左アナログスティックのX軸を格納する
	float m_Yziku;                               // 左アナログスティックのY軸を格納する

};
#endif