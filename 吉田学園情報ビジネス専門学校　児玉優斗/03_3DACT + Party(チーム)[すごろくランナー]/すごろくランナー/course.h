//=============================================================================
//
// �R�[�X�̏��� [course.h]
// Author : ���R���
//
//=============================================================================
#ifndef _COURSE_H_
#define _COURSE_H_

#include "main.h"

//*****************************************************************************
// �|���S���̍\����
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;    // ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;        // ���W
	D3DXVECTOR3 rot;        // ����
}Vertex_Course;

typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 rot;			// ����
	D3DXVECTOR3 move;			// �ړ���
	float		fWidth;			// ��
	float		fDepth;			// ���s
	bool		bUse;			// �g�p���Ă��邩�ǂ���
	D3DXMATRIX	mtxWorldCourse; // �R�[�X�̃��[���h�}�g���b�N�X
	Vertex_Course Vertex[4];    // ���_�̃��[���h�}�g���b�N�X
} COURSE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCourse(void);
void UninitCourse(void);
void UpdateCourse(void);
void DrawCourse(void);
void SetCourse(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepth);
bool CollisionCourse(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius);

#endif