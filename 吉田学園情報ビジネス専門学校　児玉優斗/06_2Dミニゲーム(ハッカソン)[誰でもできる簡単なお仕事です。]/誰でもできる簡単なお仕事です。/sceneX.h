//=============================================================================
//
// x�t�@�C���I�u�W�F�N�g���� [sceneX.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCENE_X_H_
#define _SCENE_X_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneX : public CScene
{
public:
	typedef enum
	{
		MODEL_AIRPLANE = 0,
		MODEL_CAR,
		MODEL_KATANA,
		MODEL_MAX
	}MODEL_PROPERTY;

	CSceneX();
	CSceneX(CScene::PRIORITY pri);

	~CSceneX();


	void Set(D3DXVECTOR3 pos,CSceneX::MODEL_PROPERTY prop,
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f));
	HRESULT Init(void);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void GetVertex(void);


	void        SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; };
	void        SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation(void) { return m_rot; };
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; };

	D3DXVECTOR3 GetVertexMin(void) { return m_vtxMin; };
	D3DXVECTOR3 GetVertexMax(void) { return m_vtxMax; };

private:
	LPD3DXMESH m_pMesh = NULL;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat = NULL;//�}�e���A�����ւ̃|�C���^
	DWORD		 m_nNumMat = 0;	//�}�e���A�����̐�
	LPDIRECT3DTEXTURE9* m_pTexture;	//�e�N�X�`��
	//��{���
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_rotMove;
	D3DXMATRIX  m_mtxWorld;

	//�����蔻��p
	D3DXVECTOR3 m_vtxMin;
	D3DXVECTOR3 m_vtxMax;

	//���f�����
	MODEL_PROPERTY m_modelProperty;
	static LPCSTR m_ModelNameInfo[MODEL_MAX];

	//test
	bool m_bTargetFlag;
};

#endif
