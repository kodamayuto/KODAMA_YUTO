//=============================================================================
//
// �G�N���X���� [enemy.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "scene2D.h"
#include "player.h"
//==================================================================
//	�N���X�̒�`
//==================================================================
//�v���C���[�N���X
class CEnemy : public CScene2D
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,
		TYPE_LIGHT,
		TYPE_NORMAL_SECOND,
		TYPE_MAX,
	}TYPE;

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_MOVE,
		STATE_DAMAGE,
		STATE_REPEAL,
		STATE_MAX
	}STATE;

	static HRESULT Load(void);
	static void    Unload(void);

	//�R���X�g���N�^&�f�X�g���N�^
	CEnemy();
	~CEnemy();

	HRESULT Init(void);
	void    Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSize, TYPE type);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CEnemy* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,float size,ELEMENT element,TYPE type);

	bool Damage(int nDamage);
	void SetElement(ELEMENT element) { m_element = element; };
	ELEMENT GetElement(void) { return m_element; };

private:
	CPlayer* GetTargetPlayer(void);
	void     HitCheck(D3DXVECTOR3 pos);

	CScene::ELEMENT m_element;
	STATE           m_State;
	TYPE			m_Type;
	static LPDIRECT3DTEXTURE9 m_apTexture[ELEMENT_MAX][TYPE_MAX];				//���L�e�N�X�`���ւ̃|�C���^

	D3DXVECTOR3				m_PosDest;					//�ڕW�̍��W
	int						m_nCntBullet = 0;			//�e�J�E���^
	float					m_fRot = D3DX_PI * 0.25f;	//��]
	D3DXVECTOR3				m_Move;						//�ړ���
	D3DXVECTOR3				m_OriginPos;				//��ʒu
	int						m_nHP;						//�̗�
	CPlayer*				m_pTargetPlayer;			//�ǔ��̃^�[�Q�b�g�ݒ�p
	int						m_nDamageCounter;			//�_���[�W���̓_�ŗp�J�E���^�[

	//�e�p
	CScene2D*               m_pShadow;

protected:
};
#endif // !_ENEMY_H_
