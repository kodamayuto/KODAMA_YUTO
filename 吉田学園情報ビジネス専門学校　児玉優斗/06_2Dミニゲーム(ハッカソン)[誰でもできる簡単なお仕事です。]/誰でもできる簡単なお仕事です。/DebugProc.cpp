//=============================================================================
//
// �f�o�b�N���\������ [DebugProc.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "DebugProc.h"
#include "Manager.h"

//==================================================================
//	�ÓI�����o(static�����o)�ϐ��錾
//==================================================================
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[MAX_CHARDATA] = {};

//==================================================================
//	�R���X�g���N�^&�f�X�g���N�^
//==================================================================
CDebugProc::CDebugProc()
{

}
CDebugProc::~CDebugProc()
{

}

//==================================================================
//	����������
//==================================================================
void CDebugProc::Init(void)
{
	//�ϐ��錾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�H���g�̍쐬
	D3DXCreateFont(pDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

}

//==================================================================
//	�I������
//==================================================================
void CDebugProc::Uninit(void)
{
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}
//==================================================================
//	���͏���(printf�Ƃقړ��l�̏���)
//==================================================================
void CDebugProc::Print(char* fmt, ...)
{/*�ϒ�������ҏW�������Ƃ��͕K��va_start��va_end�̊Ԃł�邱��*/

	//�ϐ��錾
	va_list args;				//�ϒ������̃��X�g	[va = variable(��)]
	char cPrint[256];			//�ҏW�ł���悤�ɂ��邽�߂ɂ�������i�[���Ă����ϐ�

	va_start(args, fmt);			//�ϒ������̕ҏW�J�n

	vsprintf_s(cPrint,fmt, args);	//�ϐ���fmt��args�������������̂�����

	va_end(args);					//�ϒ������̕ҏW�I��

	/*�������ҏW�������Ƃ��͂����ł��*/

	strcat_s(m_aStr, cPrint);		//�`��p�̕ϐ��ɕ�������i�[����
}

//==================================================================
//	�`��(�o��)����
//==================================================================
void CDebugProc::Draw(void)
{
#ifdef _DEBUG
	//�ϐ��錾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	//�`��͈͂̎w��

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL,
		m_aStr,
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
#endif
	//�����񏉊���
	ZeroMemory(m_aStr,sizeof(char) * MAX_CHARDATA);
}
