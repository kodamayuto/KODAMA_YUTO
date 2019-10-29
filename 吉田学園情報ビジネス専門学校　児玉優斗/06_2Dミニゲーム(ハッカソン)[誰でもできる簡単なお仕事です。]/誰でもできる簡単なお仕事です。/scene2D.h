//=============================================================================
//
// �I�u�W�F�N�g2D���� [scene2D.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "scene.h"

//==================================================================
//	�N���X�̒�`
//==================================================================
//�I�u�W�F�N�g2D�N���X
class CScene2D : public CScene
{
public:

	CScene2D();
	CScene2D(CScene::PRIORITY pri);

	~CScene2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos, LPCSTR TexTag,
		bool bRoll = false,float fRot = 0.0f,
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2 Size = D3DXVECTOR2(100.0f,100.0f),
		D3DXVECTOR2 UVrectMin = D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2 UVrectMax = D3DXVECTOR2(1.0f, 1.0f));

	void SetColor(D3DXCOLOR col);
	void SetUV(D3DXVECTOR2 MinRect, D3DXVECTOR2 MaxRect);

	void        SetPosition(D3DXVECTOR3 pos);
	void        SetPosition(D3DXVECTOR3 pos, D3DXVECTOR2 Size);
	void        SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 MinOffset, D3DXVECTOR3 MaxOffset);

	void		SetRotation(float fRot);

	D3DXVECTOR3 GetPosition(void) { return m_pos; };
	D3DXVECTOR2 GetSize(void) { return m_Size; };

	void		BindTexture(LPCSTR TexTag);

	//	---<<�ǉ�>>---
	void SetScroll(float fSpeed, int nScrollType);	//	�X�N���[��(���x , �cor��)
	//	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��


private:
	void UpdateVtx(void);

	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;						// �|���S���̈ʒu
	D3DXCOLOR				m_Col;						// �F
	D3DXVECTOR2				m_Size;						// �T�C�Y�ύX�p

	D3DXVECTOR2				m_UVRectMin;				//�|���S���̍����UV�ʒu
	D3DXVECTOR2				m_UVRectMax;				//�|���S���̉E����UV�ʒu

	bool m_bFreezeRotate;	//��]����I�u�W�F�N�g���ǂ����̔���p
	float m_fRot;			//�p�x


	//	---<<�ǉ�>>---
	float m_fScrollCnt;
	//	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��


};


#endif // !_SCENE2D_H_

