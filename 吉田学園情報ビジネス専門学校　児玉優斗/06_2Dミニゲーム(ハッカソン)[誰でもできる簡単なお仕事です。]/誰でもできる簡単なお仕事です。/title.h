//=============================================================================
//
// �^�C�g����ʊǗ��N���X���� [title.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "Scene3D.h"

#include "TitleObject.h"
#include "PressEnter.h"

class CScene2D;
class CSound;
//===================================================================
//	�}�N����`
//===================================================================
#define MAX_TITLE_TEX (3)


//===================================================================
//	�N���X�̒�`
//===================================================================
class CTitle
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nCount;
	CTitleLogo* m_pTitleLogo;
	CPressEnter* m_pPressEnter;

	//	---<<�ǉ�>>---
	static CSound *m_pSound;
	CScene2D * m_pScene2D[MAX_TITLE_TEX];
	int m_nStopTime;
	bool m_bEnterStop;
	int m_nCnt;				//	�^�C���J�E���g��i�߂�

	//	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��

};
#endif // !_TITLE_H_
