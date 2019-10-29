//*****************************************************************************
//
//	DirectX ���C������ [main.cpp]
//�@Author : Kodama Yuto
//
//*****************************************************************************
//�C���N���[�h�t�@�C��
#include "main.h"
#include"fade.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define CLASS_NAME		"WindowClass"		// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME		"Coin Hunter"		// �E�C���h�E�̖��O(�L���v�V������)

//=============================================================================
//	�v���g�^�C�v�錾
//=============================================================================
//�E�C���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//DirectX�̊�{���
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;

MODE g_Mode = MODE_TITLE;

int g_nNumStage = 0;
//=============================================================================
//	���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};

	RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	HWND hWnd;
	MSG msg;

	DWORD dwCurrentTime;
	DWORD dwExecLastTime;

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�C���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̐���
	hWnd = CreateWindowEx(0,
							CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							(rect.right - rect.left),
							(rect.bottom - rect.top),
							NULL,
							NULL,
							hInstance,
							NULL);

	// ����������(�E�B���h�E�𐶐����Ă���s��)
	if (FAILED(Init(hInstance, hWnd, FALSE)))
	{
		return -1;
	}

	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//����\��ݒ�
	timeBeginPeriod(1);

	// ���b�Z�[�W���[�v
	while(1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// ���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		{// Windows�̏���
			if (msg.message == WM_QUIT)
			{// "WM_QUIT"���b�Z�[�W�������Ă����烋�[�v�𔲂���
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectX�̏���

			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;
				//�X�V����
				Update();

				// �`�揈��
				Draw();
			}
		}
	}
	// �I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
//	�E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		// "WM_QUIT"���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			// �E�B���h�E��j������("WM_DESTROY"���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
			break;
		case VK_RCONTROL:
			ShowCursor(TRUE);
			break;
		}
		break;
	case WM_CREATE:
		ShowCursor(FALSE);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// ����̏�����Ԃ�
}

//-----------------------------------------------------------------------------
//	����������
//-----------------------------------------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^�[

	// Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (g_pD3D == NULL)
		{
			return E_FAIL;
		}

	// ���݂̃f�B�X�v���C���[�h���擾
		if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		{
			return E_FAIL;
		}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferWidth            = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight           = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount			 = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// �f�v�X�o�b�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed                   = bWindow;						// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g(���݂̑��x�ɍ��킹��)
	d3dpp.PresentationInterval		 = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��(VSync��҂��ĕ`��)

	// Direct3D�f�o�C�X�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// �f�B�X�v���C�A�_�v�^
									D3DDEVTYPE_HAL,							// �f�o�C�X�^�C�v
									hWnd,									// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
									D3DCREATE_HARDWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
									&d3dpp,									// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
									&g_pD3DDevice)))						// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp,
										&g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp,
											&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

//�����_�[�X�e�[�g�̐ݒ�
	//�J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//�A���t�@�u�����h�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//***�e��I�u�W�F�N�g�̏���������***
	InitKeyboard(hInstance,hWnd);		//���͏���
	InitSound(hWnd);
	g_nNumStage = 0;
	ResetScore();

	InitFade(g_Mode);//�t�F�[�h����
	SetMode(g_Mode);


	return S_OK;
}

//-----------------------------------------------------------------------------
//	�I������
//-----------------------------------------------------------------------------
void Uninit(void)
{
	//***�e��I�u�W�F�N�g�̏I������***
	UninitKeyboard();		//���͏���
	UninitTitle();   //�^�C�g�����
	UninitTutorial();//�`���[�g���A�����
	UninitGame();	 //�Q�[�����
	UninitChange();	 //�X�e�[�W�J��
	UninitResult();	 //���U���g���
	UninitRanking(); //�����L���O���
	UninitFade();	 //�t�F�[�h����
	UninitSound();

	// Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice -> Release();
		g_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D -> Release();
		g_pD3D = NULL;
	}
}

//-----------------------------------------------------------------------------
//	�X�V����
//-----------------------------------------------------------------------------
void Update(void)
{
	//***�e��I�u�W�F�N�g�̍X�V����***
	UpdateKeyboard();		//���͏���

	switch (g_Mode)
	{
	case MODE_TITLE:
		UpdateTitle();		//�^�C�g��
		break;
	case MODE_TUTORIAL:
		UpdateTutorial();	//�`���[�g���A��
		break;
	case MODE_GAME:
		UpdateGame();		//�Q�[�����
		break;
	case MODE_CHANGE:
		UpdateChange();		//�X�e�[�W�J�ډ��
		break;
	case MODE_RESULT:
		UpdateResult();		//���U���g���
		break;
	case MODE_RANKING:
		UpdateRanking();	//�����L���O���
		break;

	}

	UpdateFade();//�t�F�[�h����
}

//-----------------------------------------------------------------------------
//	�`�揈��
//-----------------------------------------------------------------------------
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��̊J�n
	if(SUCCEEDED(g_pD3DDevice ->BeginScene()))
	{

		switch (g_Mode)
		{
		case MODE_TITLE:
			DrawTitle();	//�^�C�g��
			break;
		case MODE_TUTORIAL:
			DrawTutorial();	//�`���[�g���A��
			break;
		case MODE_GAME:
			DrawGame();		//�Q�[�����
			break;
		case MODE_CHANGE:
			DrawChange();	//�X�e�[�W�J�ډ��
			break;
		case MODE_RESULT:
			DrawResult();	//���U���g���
			break;
		case MODE_RANKING:
			DrawRanking();	//�����L���O���
			break;

		}

		DrawFade();//�t�F�[�h����


		// �`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//-----------------------------------------------------------------------------
//	�f�o�C�X�̎擾
//-----------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//-----------------------------------------------------------------------------
//							���[�h�̐ݒ�
//-----------------------------------------------------------------------------
void SetMode(MODE mode)
{
	//�I������
	switch (g_Mode)
	{
	case MODE_TITLE:
		UninitTitle();
		ResetNumStage();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_CHANGE:
		UninitChange();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	case MODE_RANKING:
		UninitRanking();	//�����L���O���
		break;

	}

	switch (mode)
	{
	case MODE_TITLE:
		ResetScore();
		InitTitle();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	case MODE_GAME:
		InitGame(g_nNumStage);
		break;
	case MODE_CHANGE:
		InitChange();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	case MODE_RANKING:
		InitRanking();	//�����L���O���
		break;

	}

	g_Mode = mode;
}
//=============================================================================
//	���[�h�̎擾
//=============================================================================
MODE GetMode(void)
{
	return g_Mode;
}

//=============================================================================
//	�X�e�[�W�̎擾
//=============================================================================
int GetNumStage(void)
{
	return g_nNumStage;
}

//=============================================================================
//	�X�e�[�W�̐i�s
//=============================================================================
void AddNumStage(void)
{
	g_nNumStage++;
}

//=============================================================================
//	�X�e�[�W�̃��Z�b�g
//=============================================================================
void ResetNumStage(void)
{
	g_nNumStage = 0;
}