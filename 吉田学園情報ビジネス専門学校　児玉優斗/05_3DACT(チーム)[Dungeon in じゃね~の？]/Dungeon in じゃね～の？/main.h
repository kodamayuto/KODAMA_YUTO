//=============================================================================
//
// ���C������ [main.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800)	//�x���Ώ��p

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <windows.h>
#include <dinput.h>
#include <Xinput.h>
#include <time.h>

#include "d3dx9.h"
#include "dinput.h"
#include "xaudio2.h"

//�O���錾(���̂ɒ��ӁI�Ȃ�ł��ʂ邩��I)
class CRenderer;
class CManager;
class CInputKeyboard;
//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment (lib,"d3d9.lib")		   //�`�揈���ɕK�v
#pragma comment (lib,"d3dx9.lib")		   //[d3d9.lib]�̊g�����C�u����
#pragma comment (lib, "dxguid.lib")		   //DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment (lib, "winmm.lib")		   //�V�X�e�������擾�ɕK�v
#pragma comment (lib, "dinput8.lib")	   //���͏����ɕK�v
#pragma comment (lib, "xinput.lib")		   //Xinput�ɕK�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH (1280)	//��ʂ̕�
#define SCREEN_HEIGHT (720)	//��ʂ̍���
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / ���_�J���[ / �e�N�X�`�����W )
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / ����/���_�J���[)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE| D3DFVF_TEX1)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

// �R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

// �R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
#ifdef _DEBUG
int GetFPS(void);
#endif

#endif