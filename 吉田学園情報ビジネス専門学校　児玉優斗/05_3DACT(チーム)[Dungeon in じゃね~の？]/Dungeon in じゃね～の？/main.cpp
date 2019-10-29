//=============================================================================
//
// ���C������ [main.cpp]
// Author :�ݓc��(Kishida Rei)
//
//=============================================================================
#include "renderer.h"
#include "manager.h"
#include  "main.h"

#include < cstdio >
#include < cstdlib >
#include < crtdbg.h >
#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(X) _malloc_dbg(X,_NORMAL_BLOCK,__FILE__,__LINE__)
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"DUNGEON in����ˁ[��?"	// �E�C���h�E�̃L���v�V������
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int			g_nCountFPS;			// FPS�J�E���^

//=============================================================================
// �֐����F���C���֐�
// �֐��̊T�v�F�V�X�e���̍���
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	CManager *pManager = NULL;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
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
	//======================================================
	// ����������
	//======================================================
	if (pManager == NULL)
	{
		pManager = new CManager;//�����_�[�N���X�̐���

		if (FAILED(pManager->Init(hInstance,hWnd, TRUE)))	//FALSE�Ńt���X�N���[��//
		{
			return -1;
		}
	}


	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	dwCurrentTime =
		dwFrameCount = 0;
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b���ƂɎ��s
#ifdef _DEBUG
			 // FPS���Z�o
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�

				// �X�V����
				pManager->Update();

				// �`�揈��
				pManager->Draw();

				dwFrameCount++;
			}
		}
	}

	//================================================
	// �I������
	//================================================


	if (pManager != NULL)
	{
		// �I������
		pManager->Uninit();
		//�����_�����O�N���X�̔j��
		delete pManager;
		pManager = NULL;
	}


	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ����\��߂�
	timeEndPeriod(1);

	//_CrtDumpMemoryLeaks();
	_CrtDumpMemoryLeaks();
	return (int)msg.wParam;
}

//=============================================================================
// �֐����F�E�B���h�E�v���V�[�W��
// �֐��̊T�v�FEsc�L�[�ŃE�B���h�E��j��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:				// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);	// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//=============================================================================
// �֐����FFPS�̎擾
// �֐��̊T�v�FFPS�̃J�E���g��Ԃ�
//=============================================================================
int GetFPS(void)
{
	return g_nCountFPS;
}

