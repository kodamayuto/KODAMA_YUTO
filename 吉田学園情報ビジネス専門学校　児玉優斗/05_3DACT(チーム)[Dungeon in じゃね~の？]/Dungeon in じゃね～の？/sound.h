//=============================================================================
//
// �T�E���h���� [sound.h]
// Author :Kishida Rei
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		// BGM(TITLE)
		SOUND_LABEL_BGM_TUTORIAL,		// BGM(TUTORIAL)
		SOUND_LABEL_BGM_GAME,			// BGM(GAME)
		SOUND_LABEL_BGM_RESULT,			// BGM(RESULT)
		SOUND_LABEL_BGM_RANKING,		// BGM(RESULT
		SOUND_LABEL_SE_PICKUP,			// �擾
		SOUND_LABEL_SE_HIT,				// �q�b�g
		SOUND_LABEL_SE_DECIDE,			// ����
		SOUND_LABEL_MAX
	} SOUND_LABEL;
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;


	CSound();	//�R���X�g���N�^
	~CSound();	//�f�X�g���N�^
	HRESULT InitSound(HWND hWnd);	//������
	void UninitSound(void);			//�I������
	HRESULT PlaySound(SOUND_LABEL label);//�T�E���h�̍Đ�
	void StopSound(SOUND_LABEL label);//�T�E���h�̒�~
	void StopSound(void);//�T�E���h�̒�~
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/title.wav", -1 },		// �^�C�g��
		{ "data/BGM/tutorial.wav", -1 },	// �`���[�g���A��
		{ "data/BGM/game.wav", -1 },		// �Q�[��
		{ "data/BGM/result.wav", 0 },		// ���U���g
		{ "data/BGM/ranking.wav",-1 },		// �����L���O
		{ "data/SE/item_pickup.wav", 0 },	// �擾
		{ "data/SE/hit.wav", 0 },			// ��_���[�W
		{ "data/SE/nyu3.wav", 0 }			// ��
	};


};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
