//=============================================================================
//
// サウンド処理 [sound.h]
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
	// サウンドファイル
	//*************************************
	typedef enum
	{
		SOUND_LABEL_BGM_000,		// BGM 0(ゲームBGM1)
		SOUND_LABEL_BGM_001,		// BGM 1(ゲームBGM2)
		SOUND_LABEL_BGM_002,		// BGM 2(チュートリアルBGM)
		SOUND_LABEL_BGM_003,		// BGM 3(タイトルBGM)
		SOUND_LABEL_BGM_004,		// BGM 4(モードセレクトBGM)
		SOUND_LABEL_BGM_005,		// BGM 5(リザルトBGM)
		SOUND_LABEL_SE_000,			// SE 0(発射音)
		SOUND_LABEL_SE_001,			// SE 1(吸収音)
		SOUND_LABEL_SE_002,			// SE 2(合体音)
		SOUND_LABEL_SE_003,			// SE 3(決定音)

		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// パラメータ構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント(-1でループ再生)
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
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);// チャンクのチェック
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);// チャンクデータの読み込み

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイスへのポインタ
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイスへのポインタ
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータへのポインタ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

																// 各音素材のパラメータ
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{// -1 ループ再生　,　0 通常再生
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
