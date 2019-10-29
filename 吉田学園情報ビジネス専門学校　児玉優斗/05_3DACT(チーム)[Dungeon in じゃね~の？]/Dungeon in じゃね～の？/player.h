//=============================================================================
//
// �v���C���[����[2D �|���S��] [player.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER_PARTS (14)	//�v���C���[�̃p�[�c��
#define MAX_KEY (10)			//�ő�L�[��
//*****************************************************************************
//�O���錾 --�X�y���~�X�ɒ��ӁI(�Ȃ�ł��ʂ邩��I)
//*****************************************************************************
class CModel;
//�L�[�v�f
typedef struct
{
	int nFrame;								//�t���[����
	D3DXVECTOR3 pos[MAX_PLAYER_PARTS];		//�ʒu���
	D3DXVECTOR3 rot[MAX_PLAYER_PARTS];		//�p�x���
}KEY;

typedef struct
{
	int nLoop;								//���[�v���邩
	int nNumKey;							//�L�[��
	KEY aKey[MAX_KEY];						//�L�[
}KEY_INFO;

//*****************************************************************************
//�v���C���[�̃N���X�錾
//*****************************************************************************
class CPlayer : public CScene
{

public:
	typedef enum
	{//�v���C���[�̏��
		PLAYERSTATE_NORMAL = 0,	//�ʏ���
		PLAYERSTATE_DAMAGE,		//�_���[�W���
		PLAYERSTATE_INVISIBLE,	//���G���
		PLAYERSTATE_APPEAR,		//�o�������
		PLAYERSTATE_MAX
	}PLAYERSTATE;
	typedef enum
	{// ���[�V�����̎��
		MOTION_NEUTRAL = 0,			// �j���[�g������
		MOTION_MOVE,				// �ړ���
		MOTION_ATTACK,				// �ʏ�U��00
		MOTION_JUMP,				// �W�����v��
		MOTION_LANDING,				// ���n��
		MOTION_DAMAGE,				//�_���[�W
		MOTION_DEATH,				// ���S��
		MOTION_MAX					// ���[�V�����̑���
	}MOTIONSTATE;

	typedef enum
	{// �t���O�̎��
		PLAYERBOOLTYPE_JUMP = 0,	// �W�����v
		PLAYERBOOLTYPE_LANDING,		// ���n
		PLAYERBOOLTYPE_DAMAGE,		// �_���[�W
		PLAYERBOOLTYPE_DEAD,		// ���S
		PLAYERBOOLTYPE_MAX			// ����
	}PLAYERBOOLTYPE;

	CPlayer(int nPriority = 3, OBJTYPE type = OBJTYPE_PLAYER);	//�R���X�g���N�^
	~CPlayer();													//�f�X�g���N�^
	static HRESULT Load(void);									//�e�N�X�`���̓ǂݍ���
	static void Unload(void);									//�e�N�X�`���̔j��
	static CPlayer *Create(D3DXVECTOR3 pos);					//�v���C���[�̐���
	HRESULT Init(void);											//����������
	void Uninit(void);											//�I������
	void Update(void);											//�X�V����
	void Draw(void);											//�`�揈��
	void PlayerMotion(void);									//�v���C���[�̃��[�V����
	void PlayerMotionState(bool *bAction);						//���[�V�����̏�Ԑݒ�
	void PlayerRotFixes(D3DXVECTOR3 rot);						//�p�x�C��
	void PlayerRotFixes(float rot);								//�p�x�C��
	D3DXVECTOR3 GetPos(void);									//�ʒu���̎擾
	D3DXVECTOR3 GetRot(void);									//�p�x���̎擾
	D3DXVECTOR3 GetMove(void);									//���x���̎擾

private:
	static D3DXVECTOR3 m_Partspos[MAX_PLAYER_PARTS];			//�p�[�c�̈ʒu
	static D3DXVECTOR3 m_Partsrot[MAX_PLAYER_PARTS];			//�p�[�c�̊p�x
	static D3DXVECTOR3 m_PartsDefaultpos[MAX_PLAYER_PARTS];		//�p�[�c�̈ʒu
	static D3DXVECTOR3 m_PartsDefaultrot[MAX_PLAYER_PARTS];		//�p�[�c�̊p�x
	static D3DXVECTOR3 m_Motionpos[MAX_PLAYER_PARTS];			//���[�V������������p�ʒu
	static D3DXVECTOR3 m_Motionrot[MAX_PLAYER_PARTS];			//���[�V������������p�p�x

	static int m_aParent[MAX_PLAYER_PARTS];						//�p�[�c�̐e
	static int m_aIndex[MAX_PLAYER_PARTS];						//�p�[�c�̔ԍ�

	//�v���C���[�̊�{���//
	static LPDIRECT3DTEXTURE9 m_pTexture; //���L�e�N�X�`���̃|�C���^
	float m_fPlayerMove;					//�v���C���[�̈ړ���
	float m_fDestAngle;						//�ړI�̊p�x
	float m_fAngle;							//�p�x
	bool m_bUseDraw;						//�`�悷�邩
	int m_StateCnt;							//��ԕω��̃J�E���^
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_posold;					//�ʒu
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_rot;						//����
	D3DXVECTOR3 m_jumppower;				//�W�����v��
	PLAYERSTATE m_state;					//�v���C���[�̏��
	CModel *m_apModel[MAX_PLAYER_PARTS];	//�L�����N�^�[�̃p�[�c
	////���[�V�����֌W�̕ϐ�////
	int m_nNumKey;							//�L�[�̑���
	KEY_INFO *m_pKeyInfo;					//�L�[���̃|�C���^
	KEY_INFO m_aKeyInfo[MOTION_MAX];		//�L�[���̃|�C���^
	MOTIONSTATE m_Motionstate;				//���[�V�����̏��
	MOTIONSTATE m_MotionstateOld;			//�ȑO�̃��[�V�����̏��
	bool m_bAction[PLAYERBOOLTYPE_MAX];		// �s�����̃t���O
	bool m_bMotionBlend;					//�u�����h���邩
	int m_nKey;								//���݂̃L�[�i���o�[
	int m_nAllFrame;						//���݂̃L�[�i���o�[
	int m_nCountMotion;						//���[�V�����J�E���^�[
	int m_nCounterFrame;					//�t���[���̃J�E���^�[
	int m_nCounterAllFrame;					//���[�V�����J�E���^�[
	int m_nCounterKey;						//�L�[�̃J�E���^�[
	int m_nFrame;							//���̃t���[��
	float m_fRadius;						//�����蔻��̔��a
};


#endif