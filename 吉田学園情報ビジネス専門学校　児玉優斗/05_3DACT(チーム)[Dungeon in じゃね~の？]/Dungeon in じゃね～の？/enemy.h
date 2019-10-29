//=============================================================================
//
// �G�̏���[2D �|���S��] [enemy.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMY_PARTS (15)	//�v���C���[�̃p�[�c��
#define MAX_KEY (10)			//�ő�L�[��
//*****************************************************************************
//�O���錾 --�X�y���~�X�ɒ��ӁI(�Ȃ�ł��ʂ邩��I)
//*****************************************************************************
class CModel;


//*****************************************************************************
//�G�̃N���X�錾
//*****************************************************************************
class CEnemy : public CScene
{
	//�L�[�v�f
	typedef struct
	{
		int nFrame;								//�t���[����
		D3DXVECTOR3 pos[MAX_ENEMY_PARTS];		//�ʒu���
		D3DXVECTOR3 rot[MAX_ENEMY_PARTS];		//�p�x���
	}KEY;

	typedef struct
	{
		int nLoop;								//���[�v���邩
		int nNumKey;							//�L�[��
		KEY aKey[MAX_KEY];						//�L�[
	}KEY_INFO;


public:
	typedef enum
	{//�G�̏��
		ENEMYSTATE_NORMAL = 0,	//�ʏ���
		ENEMYSTATE_LOITERING,	//�p�j���
		ENEMYSTATE_CHASE,		//�ǐՏ��
		ENEMYSTATE_MAX			//�G�̏�Ԃ̍ő吔
	}ENEMYSTATE;

	typedef enum
	{//�G�̎��
		ENEMYTYPE_LOITERING_Z = 0,	// Z���ړ��^�C�v
		ENEMYTYPE_LOITERING_X,		// X���ړ��^�C�v
		ENEMYTYPE_CHASE,			// �ǐՃ^�C�v
		ENEMYTYPE_TEST,				// �e�X�g�p�^�C�v
		ENEMYTYPE_MAX				// �G�̎�ނ̍ő吔
	}ENEMYTYPE;

	typedef enum
	{// ���[�V�����̎��
		MOTION_NEUTRAL = 0,			// �j���[�g������
		MOTION_MOVE,				// �ړ���
		MOTION_MOVE_2,				// �ړ���2
		MOTION_JUMP,				// �W�����v��
		MOTION_LANDING,				// ���n��
		MOTION_MAX					// ���[�V�����̑���
	}MOTIONSTATE;

	typedef enum
	{// �t���O�̎��
		ENEMYBOOLTYPE_JUMP = 0,		// �W�����v
		ENEMYBOOLTYPE_LANDING,		// ���n
		ENEMYBOOLTYPE_DAMAGE,		// �_���[�W
		ENEMYBOOLTYPE_DEAD,			// ���S
		ENEMYBOOLTYPE_MAX			// ����
	}ENEMYBOOLTYPE;

	CEnemy(int nPriority = 5, OBJTYPE type = OBJTYPE_PLAYER);						//�R���X�g���N�^
	~CEnemy();																		//�f�X�g���N�^
	static HRESULT Load(void);														//�e�N�X�`���̓ǂݍ���
	static void Unload(void);														//�e�N�X�`���̔j��
	static CEnemy *Create(D3DXVECTOR3 pos, ENEMYTYPE type);							//�v���C���[�̐���
	HRESULT Init(void);																//����������
	void Uninit(void);																//�I������
	void Update(void);																//�X�V����
	void Draw(void);																//�`�揈��
	void EnemyMotion(void);															//�v���C���[�̃��[�V����
	void EnemyMotionState(bool *bAction);											//���[�V�����̏�Ԑݒ�
	void EnemyRotFixes(D3DXVECTOR3 *rot);											//�p�x�C��
	void EnemyRotFixes(float *rot);													//�p�x�C��
	bool FindPlayer(D3DXVECTOR3 *pos, float fRange);								//�v���C���[�T��
	D3DXVECTOR3 GetPos(void);														//�ʒu���̎擾
	D3DXVECTOR3 GetRot(void);														//�p�x���̎擾
	bool CollisionEnemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *move, D3DXVECTOR3 *rot);		//�G�Ƃ̓����蔻��


private:
	 D3DXVECTOR3 m_Partspos[MAX_ENEMY_PARTS];		//�p�[�c�̈ʒu
	 D3DXVECTOR3 m_Partsrot[MAX_ENEMY_PARTS];		//�p�[�c�̊p�x
	 D3DXVECTOR3 m_Motionpos[MAX_ENEMY_PARTS];	//���[�V������������p�ʒu
	 D3DXVECTOR3 m_Motionrot[MAX_ENEMY_PARTS];	//���[�V������������p�p�x
	 D3DXVECTOR3 m_PartsDefaultpos[MAX_ENEMY_PARTS];	//�p�[�c�̈ʒu
	 D3DXVECTOR3 m_PartsDefaultrot[MAX_ENEMY_PARTS];	//�p�[�c�̊p�x

	static int m_aParent[MAX_ENEMY_PARTS];	//�p�[�c�̐e
	static int m_aIndex[MAX_ENEMY_PARTS];	//�p�[�c�̔ԍ�

	//�v���C���[�̊�{���//
	static LPDIRECT3DTEXTURE9 m_pTexture; //���L�e�N�X�`���̃|�C���^
	float m_fPlayerMove;					//�v���C���[�̈ړ���
	float m_fDestAngle;						//�ړI�̊p�x
	float m_fAngle;							//�p�x
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_posold;					//�ʒu
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_rot;						//����
	D3DXVECTOR3 m_jumppower;				//�W�����v��
	CModel *m_apModel[MAX_ENEMY_PARTS];		//�L�����N�^�[�̃p�[�c
	D3DXVECTOR3 m_Startpos;					//�X�^�[�g�ʒu
	bool m_bSwitch;							//�X�C�b�`
	MOTIONSTATE m_state;					//�G�̏��
	ENEMYTYPE m_type;						//�G�̎��


	////���[�V�����֌W�̕ϐ�////
	int m_nNumKey;							//�L�[�̑���
	KEY_INFO *m_pKeyInfo;					//�L�[���̃|�C���^
	KEY_INFO m_aKeyInfo[MOTION_MAX];		//�L�[���̃|�C���^
	MOTIONSTATE m_Motionstate;				//���[�V�����̏��
	MOTIONSTATE m_MotionstateOld;			//�ȑO�̃��[�V�����̏��
	bool m_bAction[ENEMYBOOLTYPE_MAX];		// �s�����̃t���O
	bool m_bMotionBlend;					//�u�����h���邩
	int m_nKey;								//���݂̃L�[�i���o�[
	int m_nAllFrame;						//���݂̃L�[�i���o�[
	int m_nCountMotion;						//���[�V�����J�E���^�[
	int m_nCounterFrame;					//�t���[���̃J�E���^�[
	int m_nCounterAllFrame;					//���[�V�����J�E���^�[
	int m_nCounterKey;						//�L�[�̃J�E���^�[
	int m_nFrame;							//���̃t���[��
	float m_fHeight;						//�G�̍���
};


#endif