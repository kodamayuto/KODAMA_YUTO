//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "camera.h"
#include "InputKeyboard.h"
#include "Manager.h"
#include "renderer.h"

#define ANGLE_MOVE  (0.03f) //カメラ角度の移動量
#define CAMERA_POSR_COEFFICIENT (0.18f);	//カメラ注視点の係数
#define CAMERA_POS_INTERVAL (20.0f)			//カメラの注視点の位置

//=============================================================================
// コンストラクタ&デストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_fCameraAngle = 45.0f;
}
CCamera::~CCamera()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f,80.0f, -300.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
	CInputKeyboard* pInput = CManager::GetInputKeyboard();

	//if (pInput->GetPress(DIK_LEFT) == true )//時計回り
	//{
	//	m_rot.y -= ANGLE_MOVE;
	//}
	//if (pInput->GetPress(DIK_RIGHT) == true )//反時計回り
	//{
	//	m_rot.y += ANGLE_MOVE;
	//}

	//if (m_rot.y < -D3DX_PI)
	//{
	//	m_rot.y += D3DX_PI * 2.0f;
	//}
	//if (m_rot.y > D3DX_PI)
	//{
	//	m_rot.y -= D3DX_PI * 2.0f;
	//}

	//m_posV = D3DXVECTOR3(m_posR.x + sinf(m_rot.y) * -300.0f,
	//	m_posV.y,
	//	m_posR.z + cosf(m_rot.y) * -300.0f);

	//視点移動
	if (pInput->GetPress(DIK_LEFT) == true)//時計回り
	{
		m_rot.y -= ANGLE_MOVE;
		if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}
	}
	if (pInput->GetPress(DIK_RIGHT) == true)//反時計回り
	{
		m_rot.y += ANGLE_MOVE;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	m_posV = D3DXVECTOR3(m_posR.x + sinf(m_rot.y) * -300.0f,
		m_posV.y,
		m_posR.z + cosf(m_rot.y) * -300.0f);

	if (pInput->GetPress(DIK_L) == true)
	{
		m_posV.y -= 5.0f;
	}
	if (pInput->GetPress(DIK_O) == true)
	{
		m_posV.y += 5.0f;
	}
}

//=============================================================================
// 設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	CRenderer* pRenderder = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderder->GetDevice();	// デバイスの取得

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(m_fCameraAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);


	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
#ifdef _DEBUG
	CDebugProc::Print("Camera.PosV : (%f,%f,%f)\n", m_posV.x, m_posV.y, m_posV.z);
	CDebugProc::Print("Camera.PosR : (%f,%f,%f)\n", m_posR.x, m_posR.y, m_posR.z);
#endif


}