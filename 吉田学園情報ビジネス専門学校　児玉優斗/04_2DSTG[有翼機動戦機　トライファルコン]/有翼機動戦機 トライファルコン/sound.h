//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	//*************************************
	// �T�E���h�t�@�C��
	//*************************************
	typedef enum
	{
		SOUND_LABEL_BGM_000,		// BGM 0(�Q�[��BGM1)
		SOUND_LABEL_BGM_001,		// BGM 1(�Q�[��BGM2)
		SOUND_LABEL_BGM_002,		// BGM 2(�`���[�g���A��BGM)
		SOUND_LABEL_BGM_003,		// BGM 3(�^�C�g��BGM)
		SOUND_LABEL_BGM_004,		// BGM 4(���[�h�Z���N�gBGM)
		SOUND_LABEL_BGM_005,		// BGM 5(���U���gBGM)
		SOUND_LABEL_SE_000,			// SE 0(���ˉ�)
		SOUND_LABEL_SE_001,			// SE 1(�z����)
		SOUND_LABEL_SE_002,			// SE 2(���̉�)
		SOUND_LABEL_SE_003,			// SE 3(���艹)

		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	CSound();
	~CSound();

	static CSound* Create(HWND hWnd);
	HRESULT Init(HWND hWnd);
	void Uninit(void);

	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);

	static SOUND_LABEL GetLabel(void) { return m_NowPlayLabel; };
	void Pause(SOUND_LABEL label);

	void StopAll(void);

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);// �`�����N�̃`�F�b�N
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);// �`�����N�f�[�^�̓ǂݍ���

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

																// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{// -1 ���[�v�Đ��@,�@0 �ʏ�Đ�
		{ "data/BGM/CaravanMode0.wav",-1 },
		{ "data/BGM/CaravanMode1.wav",-1 },
		{ "data/BGM/Tutorial.wav",-1 },
		{ "data/BGM/Title.wav",-1 },
		{ "data/BGM/modeSelect.wav",-1 },
		{ "data/BGM/result.wav",-1 },
		{ "data/SE/shot000.wav",0 },
		{ "data/SE/absorb.wav",0 },
		{ "data/SE/union3.wav",0 },
		{ "data/SE/decision.wav",0 }
	};

	bool m_bPauseFlag;
	static SOUND_LABEL m_NowPlayLabel;
};
#endif
