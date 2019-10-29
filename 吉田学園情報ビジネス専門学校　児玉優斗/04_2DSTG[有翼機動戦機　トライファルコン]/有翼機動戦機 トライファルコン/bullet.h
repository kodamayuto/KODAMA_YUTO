//=============================================================================
//
// �e�N���X���� [bullet.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "scene2D.h"

//==================================================================
//	�}�N����`
//==================================================================
#define BULLET_PRIORITY (3)
//==================================================================
//	�N���X�̒�`
//==================================================================
//�v���C���[�N���X
class CBullet : public CScene2D
{
public:
	typedef enum
	{//�e�̌`�ƈړ����[�`�������p
		TYPE_BULLET_NORMAL = 0,
		TYPE_BULLET_HOMING,
		TYPE_MAX
	}TYPE;

	typedef enum
	{//�e�̊Ǘ��ҕ����p
		AUTHOR_NONE,
		AUTHOR_PLAYER,
		AUTHOR_ENEMY,
	}AUTHORITY;

	//�R���X�g���N�^&�f�X�g���N�^
	CBullet();
	~CBullet();

	static HRESULT Load(void);
	static void    Unload(void);

	HRESULT Init(void);
	void Init(D3DXVECTOR3 pos, float fMove, D3DXVECTOR3 rot, D3DXCOLOR col);

	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CBullet* Create(D3DXVECTOR3 pos,float fMove,D3DXVECTOR3 rot,ELEMENT element,TYPE type,AUTHORITY author,bool bEffectUse);

	AUTHORITY GetAuthor(void) { return m_Author; };

	void SetElement(ELEMENT element) { m_element = element; };
	ELEMENT GetElement(void) { return m_element; };
	void SetTarget(CScene2D* pTarget) { m_pTarget = pTarget; };
private:
	CScene::ELEMENT m_element;
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	//���L�e�N�X�`���ւ̃|�C���^
	AUTHORITY				m_Author;					//�e�̌�����
	TYPE					m_type;						//�e�̃^�C�v
	D3DXVECTOR3				m_Rot;						//��]
	float					m_fMove;					//�ړ���
	bool					m_bEffectFlag;				//�G�t�F�N�g�g�p�̉�
	D3DXCOLOR				m_Col;						//�F
	CScene2D*				m_pTarget;					//�ǔ��Ώ�
	D3DXVECTOR3				m_TargetPosOld;
protected:
};
#endif // !_PLAYER_H_
