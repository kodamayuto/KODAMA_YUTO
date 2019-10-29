// �����_�����O���� [renderer.h]
// Author :�ݓc��(Kishida Rei)
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

class CFade;
class CPause;
//*****************************************************************************
// �`��̃N���X�\����
//*****************************************************************************
class CRenderer
{
public:
	CRenderer::CRenderer();	//�R���X�g���N�^
	CRenderer::~CRenderer();	//�f�X�g���N�^
	HRESULT Init(HWND hWnd, bool bWindow);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	LPDIRECT3DDEVICE9 GetDevice(void);	//�f�o�C�X�̎擾
	static void SetPause(void);
	static bool GetPause(void);

private:
#ifdef _DEBUG
	void DrawFPS(void);			//FPS�\������
#endif

	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)

	int m_nCntFPS;//FPS

#ifdef _DEBUG
	LPD3DXFONT				m_pFont;			// �t�H���g�ւ̃|�C���^
#endif
	static CFade *m_pFade;//�t�F�[�h
	static CPause *m_pPause;//�|�[�Y
	static bool m_bPause;	//�|�[�Y���Ă��邩


};

#endif