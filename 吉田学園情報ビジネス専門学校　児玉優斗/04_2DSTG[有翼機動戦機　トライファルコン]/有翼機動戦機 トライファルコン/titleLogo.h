//=============================================================================
//
// �����N���X���� [titleLogo.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "scene.h"
#include "scene2D.h"

//==================================================================
// �}�N����`
//==================================================================

//==================================================================
//	�N���X�̒�`
//==================================================================
//�v���C���[�N���X
class CTitleLogo : public CScene
{
public:
	//�R���X�g���N�^&�f�X�g���N�^
	CTitleLogo();
	~CTitleLogo();

	static HRESULT Load(void);
	static void    Unload(void);

	HRESULT Init(void);

	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CTitleLogo* Create();

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;				//���L�e�N�X�`���ւ̃|�C���^
	CScene2D* m_pLogo;


protected:
};
#endif // !_TITLELOGO_H_
