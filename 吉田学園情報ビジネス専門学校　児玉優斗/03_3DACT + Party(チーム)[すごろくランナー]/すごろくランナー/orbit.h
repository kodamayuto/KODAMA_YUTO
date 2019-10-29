//=============================================================================
//
// �O���̏��� [orbit.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _ORBIT_H_
#define _ORBIT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ORBIT_BLOCK      (100)
#define MAX_ORBIT        (2)

//*****************************************************************************
// �O���̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posUp;      // ���݂̍��W���
	D3DXVECTOR3 posoldUp;   // �O��̍��W���
	D3DXVECTOR3 posDown;    // ���݂̍��W���
	D3DXVECTOR3 posoldDown; // �O��̍��W���
	D3DXCOLOR   colUp;      // �F(�㑤)
	D3DXCOLOR   colDown;    // �F(����)
	D3DXVECTOR3 radius;     // ��
}VerOrbit;

typedef struct
{
	D3DXVECTOR3 pos;        // ���W
	D3DXVECTOR3 rot;        // ����
	D3DXMATRIX  mtxWorld;   // ���[���h�}�g���b�N�X
	VerOrbit    orbit[ORBIT_BLOCK + 1];      // ���_���
	float       Length;     // ����
	int         XBlock;     // ���̕�����
	int         YBlock;     // �c�̕�����
	int         nNumVertex; // ���_��
	int         nNumIndex;  // �C���f�b�N�X��
	int         nNumPolygon;// �|���S����
}Orbit;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitOrbit(void);
void UninitOrbit(void);
void UpdateOrbit(void);
void DrawOrbit(void);
void SetOrbit(D3DXVECTOR3 mtx1, D3DXVECTOR3 mtx2, D3DXCOLOR colUp, D3DXCOLOR colDown, int nIdxOrbit);
void SetPosiotionOrbit(D3DXVECTOR3 mtx1, D3DXVECTOR3 mtx2, int nIdxOrbit);
#endif
