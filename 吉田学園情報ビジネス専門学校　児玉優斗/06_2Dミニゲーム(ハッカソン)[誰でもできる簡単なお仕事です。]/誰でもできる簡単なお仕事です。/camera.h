//=============================================================================
//
// �J�������� [camera.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//===================================================================
// �N���X�̒�`
//===================================================================

class CCamera
{
public:
	CCamera();
	~CCamera();


	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	D3DXVECTOR3 GetRotation(void) { return m_rot; };
private:
	D3DXVECTOR3 m_posV;	//���_
	D3DXVECTOR3 m_posVdest;
	D3DXVECTOR3 m_posR;	//�����_
	D3DXVECTOR3 m_posRdest;
	D3DXVECTOR3 m_vecU;	//������x�N�g��
	D3DXVECTOR3 m_rot;	//�p�x
	D3DXMATRIX m_mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;	//�r���[�}�g���b�N�X

	float m_fCameraAngle;	//�J�����p

};
#endif // !_CAMERA_H_
