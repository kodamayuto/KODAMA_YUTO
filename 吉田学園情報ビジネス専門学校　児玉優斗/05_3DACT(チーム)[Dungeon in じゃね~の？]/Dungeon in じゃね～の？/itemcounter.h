//=============================================================================
//
// �A�C�e���J�E���^����[�V�[��] [itemcounter.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _ITEMCOUNTER_H_
#define _ITEMCOUNTER_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COUNTER_NUMBER (3)

class CNumber;
class CItemCounter : public CScene
{
public:
	typedef enum
	{
		COUNTERTYPE_KEY = 0,
		COUNTERTYPE_COIN,
		COUNTERTYPE_MAX
	}COUNTERTYPE;
	CItemCounter(int nPriority = 7, OBJTYPE type = OBJTYPE_ITEMCOUNTER);	//�R���X�g���N�^
	~CItemCounter();	//�f�X�g���N�^
	static CItemCounter *Create(void);	//�����̐���
	HRESULT Init(void);								//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
	static int GetCoin(void);						//�R�C���̎擾
	static int GetKey(void);						//�J�M�̎擾
	static int GetMaxKey(void);						//�J�M��
	static void AddCoin(int nValue);				//�R�C���̉��Z
	static void AddKey(int nValue);					//�J�M�̉��Z
	static void AddKeyMax(int nValue);				//�J�M�ő吔�̉��Z
	static void SetCoinNum(int nValue);				//�R�C���̐��̐ݒ�
private:
	static CNumber *m_apNumber[COUNTER_NUMBER];		//����
	static int m_nCoin;								//�R�C���̐�
	static int m_nKey;								//�J�M�̐�
	static int m_nKeyMax;							//�J�M�̍ő吔

};

#endif