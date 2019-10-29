//=============================================================================
//
// �ԍ��N���X���� [Gauge.h]
// Author : Kodama Yuto
//
//=============================================================================

#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"
#include "scene.h"
//==================================================================
// �N���X
//==================================================================
class CGauge
{
public:
	CGauge();
	~CGauge();

	static HRESULT Load(void);
	static void    Unload(void);

	static CGauge* Create(D3DXVECTOR3 pos, float fSizeY,float fLength,CScene::ELEMENT elem);// ���W�A�T�C�Y��Init�ɓn��
	HRESULT Init(D3DXVECTOR3 pos, float fSizeY, float fLength, CScene::ELEMENT elem);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	void SetGauge(float fElementGauge);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;					// �e�N�X�`���ւ̃|�C���^		// BindTexture�͎g��Ȃ�
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3						m_pos;						// �|���S���̈ʒu
	float							m_fSizeY;					// �Q�[�W�̕�

	float							m_fElementGauge;			// �Q�[�W�̒���
	CScene::ELEMENT					m_Element;					// �Q�[�W�̑���

	int								m_nCntTime;				    // �J�E���^
	D3DXCOLOR						m_OrgColor;					// �F�ۑ��p
};
#endif