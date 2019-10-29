//=============================================================================
//
// �^�C�}�[����[2D �|���S��] [timer.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;				// �i���o�[

							//*****************************************************************************
							// �}�N����`
							//*****************************************************************************
#define TIMER_NUMBER			(6)		// �^�C���̌���
#define RANKING_NUMBER		(5)		// ���ʂ̐�

							//*****************************************************************************
							// �^�C�}�[�N���X
							//*****************************************************************************
class CTimer : public CScene
{
public:
	typedef enum
	{
		TIMERTYPE_TENMINUTE = 0,	//10����
		TIMERTYPE_ONEMINUTE,	//1����
		TIMERTYPE_TENSECONDS,	//10�b��
		TIMERTYPE_ONESECONDS,	//1�b��
		TIMERTYPE_TENCOMMASECONDS,	//�R���}10�b��
		TIMERTYPE_ONECOMMASECONDS,	//�R���}1�b��
	} TIMETYPE;

	typedef enum
	{
		TIMEMODE_NONE = 0,				// ������
		TIMEMODE_GAME,					// �Q�[��
		TIMEMODE_RESULT,					// ���U���g
		TIMEMODE_RANKING,				// �����L���O
		TIMEMODE_MAX						// ���[�h�̎��
	} TIMEMODE;

	CTimer();	//�R���X�g���N�^
	virtual ~CTimer();	//�f�X�g���N�^
	static CTimer *Create(D3DXVECTOR3 pos, TIMEMODE mode);	//�����̐���
	virtual HRESULT Init(void) = 0;	//����������
	virtual void Uninit(void) = 0;	//�I������
	virtual void Update(void) = 0;	//�X�V����
	virtual void Draw(void) = 0;	//�`�揈��

protected:
	D3DXVECTOR3 m_pos;	//�ʒu���
	static int m_nTimer;		 //�^�C�}�[
	static int m_nTenMinutes;	 //10����
	static int m_nOneMinutes;	 //1����
	static int m_nTenSeconds;	 //10�b��
	static int m_nOneSeconds;	 //10�b��
	static int m_nTenComma;	//�R���}�b
	static int m_nOneComma;	//�R���}�b
};

//*****************************************************************************
// �Q�[���̃^�C�}�[
//*****************************************************************************
class CGameTimer : public CTimer
{
public:
	CGameTimer();			//�R���X�g���N�^
	~CGameTimer();			//�f�X�g���N�^
	HRESULT Init(void);	//����������
	void Uninit(void);			//�I������
	void Update(void);		//�X�V����
	void Draw(void);			//�`�揈��

private:
	CNumber *m_apNumber[TIMER_NUMBER];	//����
	int m_nCntFrame;	//�t���[�����J�E���g�p
	int m_nCntColor;	//�J���[�J�E���g�p
	bool bUse;//�J�E���g���邩
};

//*****************************************************************************
// ���U���g�̃^�C�}�[
//*****************************************************************************
class CResultTimer : public CTimer
{
public:
	CResultTimer();			//�R���X�g���N�^
	~CResultTimer();		//�f�X�g���N�^
	HRESULT Init(void);	//����������
	void Uninit(void);			//�I������
	void Update(void);		//�X�V����
	void Draw(void);			//�`�揈��
	void SetResultTimer(int nTenMinutes, int nOneMinutes, int nTenSeconds, int nOneSeconds, int nTenComma, int nOneComma);	//�X�R�A�̐ݒ�

private:
	CNumber *m_apNumber[TIMER_NUMBER];	//����
};

//*****************************************************************************
// �����L���O�̃^�C�}�[
//*****************************************************************************
class CRankingTimer : public CTimer
{
public:
	CRankingTimer();		//�R���X�g���N�^
	~CRankingTimer();		//�f�X�g���N�^
	HRESULT Init(void);	//����������
	void Uninit(void);			//�I������
	void Update(void);		//�X�V����
	void Draw(void);			//�`�揈��
	void SetRankingTimer();	//�X�R�A�̐ݒ�

private:
	static int m_nRank[RANKING_NUMBER][6];
	CNumber *m_apNumber[RANKING_NUMBER][TIMER_NUMBER];	//���ʁA����
	int m_nChange;		// �v�Z�p1
};

#endif