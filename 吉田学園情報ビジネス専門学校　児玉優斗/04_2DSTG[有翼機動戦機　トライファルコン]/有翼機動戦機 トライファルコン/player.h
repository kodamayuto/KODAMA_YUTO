//=============================================================================
//
// �v���C���[�N���X���� [player.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene2D.h"


#define TEX_NUM			 (3)		//�e�N�X�`����
#define MAX_VITALITY     (12)		//�ő�HP
#define MAX_STOCK		 (3)		//�ő�c�@��
#define PLAYER_PRIORITY (4)
class CInputKeyboard;
class CTime;
//==================================================================
//	�N���X�̒�`
//==================================================================
//�v���C���[�N���X
class CPlayer : public CScene2D
{
public:

	typedef enum
	{
		STATE_NONE = 0,
		STATE_TRANSPARENT,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX
	}STATE;

	//�R���X�g���N�^&�f�X�g���N�^
	CPlayer();
	~CPlayer();

	//�����o�֐�
	static HRESULT Load(void);
	static void    Unload(void);

	HRESULT Init(void);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CPlayer* Create(void);
	static void     SetStock(int nStock = MAX_STOCK) { m_nStock = nStock; };
	static int      GetStock(void){ return m_nStock; };
	bool Damage(int nDamage);
	int GetHP(void) { return m_nHP; };

	void SetElement(ELEMENT element) { m_element = element; };
	ELEMENT GetElement(void) { return m_element; };

	void SetGauge(ELEMENT element, float fAddGauge) { m_fElementGauge[element] += fAddGauge; };

private:
	//�����o�֐�
	D3DXVECTOR3 Move(D3DXVECTOR3 pos);
	void		HitCheck(D3DXVECTOR3 pos);
	//�����o�ϐ�
	CScene::ELEMENT m_element;							//����
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_NUM];		//���L�e�N�X�`���ւ̃|�C���^
	static int				  m_nStock;					//�c�@

	D3DXVECTOR3				m_Move;						//�ړ���
	int						m_nCntBullet = 0;			//�e�p�J�E���^
	int						m_nCntTransParent;			//�����p�J�E���^
	int						m_nHP;						//�̗�
	float					m_fRot = D3DX_PI * 0.25f;	//��]
	float					m_fHitSize;					//�e�̓����蔻��̃T�C�Y
	float					m_fElementGauge[3];			//�������Ƃ̃Q�[�W
	STATE					m_PlayerState;				//�v���C���[�̏��
	ELEMENT					m_UnionElement;				//���̌�ɖ߂鑮��
	CTime*					m_UnionTimer;				//���̃^�C�}�[
	//�e�p
	CScene2D*               m_pShadow;

	//�o���A�p
	CScene2D*				m_pBarrier;

protected:
};
#endif // !_PLAYER_H_
