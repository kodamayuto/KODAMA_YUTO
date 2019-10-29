//=============================================================================
//
// �����N���X���� [BG.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "scene.h"
#include "scene2D.h"

//==================================================================
// �}�N����`
//==================================================================
#define MAIN_BG_NUM (2)
#define SIDE_BG_NUM (2)

//==================================================================
//	�N���X�̒�`
//==================================================================
//�v���C���[�N���X
class CBg : public CScene
{
public:
	typedef enum
	{
		TYPE_0 = 0,
		TYPE_1,
		TYPE_2,
		TYPE_MAX
	}TYPE;
	//�R���X�g���N�^&�f�X�g���N�^
	CBg();
	~CBg();

	static HRESULT Load(void);
	static void    Unload(void);

	HRESULT Init(void);

	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CBg* Create();

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];				//���L�e�N�X�`���ւ̃|�C���^
	CScene2D* m_apMainBG[MAIN_BG_NUM];
	CScene2D* m_apSideBG[SIDE_BG_NUM];

protected:
};
#endif // !_BG_H_
