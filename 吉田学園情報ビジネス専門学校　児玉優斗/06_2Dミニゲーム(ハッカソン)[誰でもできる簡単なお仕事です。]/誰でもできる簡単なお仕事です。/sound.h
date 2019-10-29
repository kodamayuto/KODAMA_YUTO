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
		// ---<<BGM>>---
		BGM_TITLE,			// �^�C�g��BGM
		BGM_GAME,			// �Q�[��BGM
		BGM_GAME02,			// �Q�[��02BGM
		BGM_RANKING,		// �����L���OBGM
							// ---<<SE>>---
							SE_PUSH,			// ����SE
							SE_COUNT01,			// �J�E���g�_�E��01SE
							SE_COUNT02,			// �J�E���g�_�E��02SE
							SE_COUNT03,			// �J�E���g�_�E��03SE
							SE_START_SE,		// �J�n��SE
							SE_END_SE,			// �I����SE
							SE_SUCCESS,			// ����SE
							SE_MISS,			// ���sSE
							SOUND_LABEL_MAX
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
	 // ---<<BGM>>---
		{ "data/BGM/retrogamecenter3.wav",-1 },		// �^�C�g��BGM
		{ "data/BGM/sanjinooyatsu.wav",-1 },		// �Q�[��BGM
		{ "data/SE/escalator-1.wav",-1 },		// �Q�[��02BGM
		{ "data/BGM/tw088.wav",-1 },		// �����L���OBGM

											// ---<<SE>>---
		{ "data/SE/decision20.wav",0 },		// ����SE
		{ "data/SE/select08.wav",0 },		// �J�E���g�_�E��01SE
		{ "data/SE/select03.wav",0 },		// �J�E���g�_�E��02SE
		{ "data/SE/select02.wav",0 },		// �J�E���g�_�E��03SE
		{ "data/SE/police-whistle1.wav",0 },		// �J�n��SE
		{ "data/SE/police-whistle2.wav",0 },		// �I����SE
		{ "data/SE/putting_a_heavy_box.wav",0 },		// ����SE
		{ "data/SE/deleteSE.wav",0 },		// ���sSE
	};

};
#endif
