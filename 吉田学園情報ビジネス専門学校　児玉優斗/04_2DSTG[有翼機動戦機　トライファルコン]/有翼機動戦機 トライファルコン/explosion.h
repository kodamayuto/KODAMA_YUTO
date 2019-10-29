//=============================================================================
//
// �����N���X���� [explosion.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "scene2D.h"

//==================================================================
//	�N���X�̒�`
//==================================================================
//�v���C���[�N���X
class CExplosion : public CScene2D
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,
		TYPE_ABSORB,
		TYPE_MAX
	}TYPE;
	//�R���X�g���N�^&�f�X�g���N�^
	CExplosion();
	~CExplosion();

	static HRESULT Load(void);
	static void    Unload(void);

	HRESULT Init(void);
	void Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fSize);

	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CExplosion* Create(D3DXVECTOR3 pos,D3DXCOLOR col,float fSize,TYPE type);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];				//���L�e�N�X�`���ւ̃|�C���^

	int m_nAnim;				//�����̕\������
	int m_nAnimInterval;		//�A�j���[�V�����̑J�ڎ���
protected:
};
#endif // !_EXPLOSION_H_
