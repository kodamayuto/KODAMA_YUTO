//=============================================================================
//
// �f�o�b�N���\������ [DebugProc.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _DEBUG_PROC_H_
#define _DEBUG_PROC_H_

#include "main.h"

//==================================================================
//	�}�N����`
//==================================================================
#define MAX_CHARDATA (2048)	//������

//==================================================================
//	�N���X�̒�`
//==================================================================
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void    Init(void);
	void    Uninit(void);

	static void    Print(char* fmt,...);
	static void    Draw(void);

private:
	static LPD3DXFONT m_pFont;				//�t�H���g�p�̃|�C���^
	static char m_aStr[MAX_CHARDATA];		//�f�o�b�N���\���p�̕ϐ�

};
#endif // !_DEBUG_PROC_H_
