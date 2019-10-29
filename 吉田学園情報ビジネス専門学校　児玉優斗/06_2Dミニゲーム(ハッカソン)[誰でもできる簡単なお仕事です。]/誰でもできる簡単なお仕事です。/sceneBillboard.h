//=============================================================================
//
// �r���{�[�h���� [sceneBillboard.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCENE_BILLBOARD_H_
#define _SCENE_BILLBOARD_H_

#include "scene.h"

//==================================================================
//	�N���X�̒�`
//==================================================================
class CSceneBillboard : public CScene
{
public:

	CSceneBillboard();
	CSceneBillboard(CScene::PRIORITY pri);
	~CSceneBillboard();

	void Set(D3DXVECTOR3 pos,LPCSTR TexTag,
		D3DXVECTOR2 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);



	void        SetPosition(D3DXVECTOR3 pos);
	void        SetSize(D3DXVECTOR2 Size);
	D3DXVECTOR3 GetPosition(void) { return m_pos; };

	void		BindTexture(LPCSTR TexTag);


protected:

private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;						//�|���S���̈ʒu
	D3DXVECTOR3				m_rot;
	D3DXMATRIX				m_mtxWorld;					//�|���S���̃}�g���b�N�X
	D3DXVECTOR2				m_Size;
};
#endif //!_SCENE_BILLBOARD_H_