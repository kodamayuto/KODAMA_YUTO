//=============================================================================
//
// ��ʑJ�ڃN���X���� [fade.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "scene2D.h"
#include "Manager.h"

//=============================================================================
//
//=============================================================================
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,		// �������Ă��Ȃ����
		FADE_IN,			// �t�F�[�h�C�����
		FADE_OUT,			// �t�F�[�h�A�E�g���
		FADE_MAX
	} FADE;
	typedef enum
	{
		COLOR_BLACK = 0,
		COLOR_WHITE,
		COLOR_MAX
	}FADECOLOR;
	CFade();
	~CFade();

	static CFade* Create(CManager::MODE modeNext);
	HRESULT Init(CManager::MODE modeNext);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	void SetFade(CManager::MODE modeNext, FADECOLOR fCol);
	FADE* GetFade(void) { return &m_Fade; };
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture;				// �e�N�X�`���ւ̃|�C���^
	FADE					m_Fade;					// �t�F�[�h�̏��
	CManager::MODE			m_modeNext;				// ���̃��[�h
	D3DXCOLOR				m_colorFade;			// �t�F�[�h�F
};
#endif //!_FADE_H_