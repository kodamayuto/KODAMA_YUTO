//=============================================================================
//
// �J�������� [camera.h]
// Author :
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �J�����̃N���X�\����
//*****************************************************************************
class CCamera
{
public:
	CCamera();	//�R���X�g���N�^
	~CCamera();	//�f�X�g���N�^
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void SetCamera(void);	//�`�揈��
	void OverView(void);	//�p�x����
	D3DXMATRIX GetmtxView(void);	//�r���[�}�g���b�N�X�̎擾
	D3DXVECTOR3 GetRot(void);		//�J�����̊p�x���̎擾
private:
	static CManager *m_pManager;//�}�l�[�W��
	D3DXVECTOR3 m_posVDest;
	D3DXVECTOR3 m_posRDest;
	D3DXVECTOR3 m_posV;		//���_
	D3DXVECTOR3 m_posR;		//�����_
	D3DXVECTOR3 m_vecU;		//������x�N�g��
	D3DXVECTOR3 m_rot;		//�p�x���
	D3DXMATRIX m_mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X
	float m_eyepoint;		//���_
	float m_fAngle;		//�p�x���
	float m_fLength;	//����
	float m_fHeight;	//����
};

#endif
