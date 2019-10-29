//=============================================================================
//
// �^�C�g����ʊǗ��N���X���� [title.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "titleLogo.h"

//
//
//
#define MAX_TITLE_TEX (4)

//
//
//
class CTitleLogo;
class CTitle
{
public:
	CTitle();
	~CTitle();

	static HRESULT Load(void);
	static void    Unload(void);
	static CTitle* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static CTitleLogo* m_pTitleLogo;

	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TITLE_TEX];				//���L�e�N�X�`���ւ̃|�C���^
	CScene2D* m_pBG[MAX_TITLE_TEX];
	CScene2D* m_pPressEnter;
	int m_nCount;

};
#endif // !_TITLE_H_
