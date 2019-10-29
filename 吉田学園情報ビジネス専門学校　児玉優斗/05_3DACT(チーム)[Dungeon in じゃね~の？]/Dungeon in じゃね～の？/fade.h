//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : Kishida Rei
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
//�O���錾 --�X�y���~�X�ɒ��ӁI(�Ȃ�ł��ʂ邩��I)
class CManager;

class CFade
{
public:
	CFade();
	~CFade();
	typedef enum
	{
		FADE_NONE = 0,		// �������Ă��Ȃ����
		FADE_IN,			// �t�F�[�h�C�����
		FADE_OUT,			// �t�F�[�h�A�E�g���
		FADE_MAX
	} FADE;

	//static CFade *Create(D3DXVECTOR3 pos, CManager::MODE modeNext);	//�v���C���[�̐���
	//HRESULT Init(D3DXVECTOR3 pos, CManager::MODE modeNext);	//����������
	//void Uninit(void);	//�I������
	//void Update(void);	//�X�V����
	//void Draw(void);	//�`�揈��

	HRESULT Init(CManager::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetFade(CManager::MODE modeNext);
	static FADE GetFade(void);
	void SetTexture(float fTex_X_0, float fTex_X_1, float fTex_Y_0, float fTex_Y_1);
	static void AddTex();
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9  m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	static FADE					m_fade;					// �t�F�[�h���
	static CManager::MODE			m_modeNext;				// ���̃��[�h
	static D3DXCOLOR				m_color;			// �t�F�[�h�F
	static int m_nPatternAnim;	//�A�j���[�V�����p�^�[��
	static int m_nCounterAnim;//�A�j���[�V�����J�E���^�[
	static int m_nTex_Y;

};


#endif
