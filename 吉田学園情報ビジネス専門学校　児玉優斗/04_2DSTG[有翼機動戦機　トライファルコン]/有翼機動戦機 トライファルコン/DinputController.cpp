//=============================================================================
//
// 入力処理 [DInputController.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "DinputController.h"

//===================================================================
//	コンストラクタ&デストラクタ
//===================================================================
CDInputController::CDInputController()
{

}
CDInputController::~CDInputController()
{

}

//===================================================================
//	初期化処理
//===================================================================
HRESULT CDInputController::Init(HINSTANCE hInstance, HWND hWnd)
{
	//======================================
	// ジョイパッド初期化処理
	//======================================
	// 入力デバイス(ジョイパッド)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	if (m_pDevice != NULL)
	{// 生成できた
		DIPROPRANGE diprg;

		// 軸の値の範囲を設定
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -DI_JOY_I_INPUT;
		diprg.lMax = DI_JOY_I_INPUT;

		// 軸の設定
		// 左アナログスティック
		diprg.diph.dwObj = DIJOFS_X;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 右アナログスティック
		diprg.diph.dwObj = DIJOFS_RX;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);


		// 十字キー(上を0度とし時計回りに角度 * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ジョイパッドへのアクセス権を獲得(入力制御開始)
		m_pDevice->Acquire();
	}

	return S_OK;

}

//===================================================================
//	終了処理
//===================================================================
void CDInputController::Uninit(void)
{
	CInput::Uninit();
}

//===================================================================
//	更新処理
//===================================================================
void CDInputController::Update(void)
{
	//======================================
	// ジョイパッド更新処理
	//======================================
	if (m_pDevice != NULL)
	{// 生成できた
		DIJOYSTATE dijs;    // ジョイパッドの入力情報を格納する

							// 入力デバイス(ジョイパッド)からデータを取得
		m_pDevice->Poll();
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIJOYSTATE), &dijs)))
		{
			m_Yziku = 0.0f;
			m_Xziku = 0.0f;

			m_Xziku = (float)dijs.lX;
			m_Yziku = (float)dijs.lY;

			//-----------------------------
			// 左アナログスティック
			//-----------------------------
			if (dijs.lY <= -100)
			{// 左アナログスティックが上に倒された
				dijs.rgbButtons[DIJS_BUTTON_10] = 0x80;
			}
			if (dijs.lY >= 100)
			{// 左アナログスティックが下に倒された
				dijs.rgbButtons[DIJS_BUTTON_11] = 0x80;
			}
			if (dijs.lX <= -100)
			{// 左アナログスティックが左に倒された
				dijs.rgbButtons[DIJS_BUTTON_13] = 0x80;
			}
			if (dijs.lX >= 100)
			{// 左アナログスティックが右に倒された
				dijs.rgbButtons[DIJS_BUTTON_12] = 0x80;
			}

			//-----------------------------
			// 右アナログスティック
			//-----------------------------
			if (dijs.lRz <= -100)
			{// 右アナログスティックが上に倒された
				dijs.rgbButtons[DIJS_BUTTON_14] = 0x80;
			}
			if (dijs.lRz >= 100)
			{// 右アナログスティックが下に倒された
				dijs.rgbButtons[DIJS_BUTTON_15] = 0x80;
			}
			if (dijs.lZ <= -100)
			{// 右アナログスティックが左に倒された
				dijs.rgbButtons[DIJS_BUTTON_17] = 0x80;
			}
			if (dijs.lZ >= 100)
			{// 右アナログスティックが右に倒された
				dijs.rgbButtons[DIJS_BUTTON_16] = 0x80;
			}

			//-----------------------------
			// 十字キー
			//-----------------------------
			if (dijs.rgdwPOV[0] / 100 == 0)
			{// 十字キーの上が押された
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 45)
			{// 十字キーの右上が押された
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 90)
			{// 十字キーの下が押された
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 135)
			{// 十字キーの右下が押された
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 180)
			{// 十字キーの右が押された
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 225)
			{// 十字キーの左下が押された
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 270)
			{// 十字キーの左が押された
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			if (dijs.rgdwPOV[0] / 100 == 315)
			{// 十字キーの左上が押された
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			for (int nCntJoyButton = 0; nCntJoyButton < DIJS_BUTTON_MAX; nCntJoyButton++)
			{// ジョイパッドのボタンの数だけ繰り返し
				m_aJoyStateTrigger[nCntJoyButton] = (m_aJoyState[nCntJoyButton] ^ dijs.rgbButtons[nCntJoyButton]) & dijs.rgbButtons[nCntJoyButton];  // ジョイパッドの入力情報(トリガー情報)保存
				m_aJoyState[nCntJoyButton] = dijs.rgbButtons[nCntJoyButton];   // ジョイパッドの入力情報(プレス情報)保存
			}
		}
		else
		{
			m_pDevice->Acquire(); // ジョイパッドへのアクセス権を獲得
		}
	}
}