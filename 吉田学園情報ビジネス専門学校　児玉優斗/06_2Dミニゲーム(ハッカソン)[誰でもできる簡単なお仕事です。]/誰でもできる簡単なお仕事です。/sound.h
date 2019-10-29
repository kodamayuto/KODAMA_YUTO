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
		// ---<<BGM>>---
		BGM_TITLE,			// タイトルBGM
		BGM_GAME,			// ゲームBGM
		BGM_GAME02,			// ゲーム02BGM
		BGM_RANKING,		// ランキングBGM
							// ---<<SE>>---
							SE_PUSH,			// 決定SE
							SE_COUNT01,			// カウントダウン01SE
							SE_COUNT02,			// カウントダウン02SE
							SE_COUNT03,			// カウントダウン03SE
							SE_START_SE,		// 開始音SE
							SE_END_SE,			// 終了音SE
							SE_SUCCESS,			// 正解SE
							SE_MISS,			// 失敗SE
							SOUND_LABEL_MAX
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
	 // ---<<BGM>>---
		{ "data/BGM/retrogamecenter3.wav",-1 },		// タイトルBGM
		{ "data/BGM/sanjinooyatsu.wav",-1 },		// ゲームBGM
		{ "data/SE/escalator-1.wav",-1 },		// ゲーム02BGM
		{ "data/BGM/tw088.wav",-1 },		// ランキングBGM

											// ---<<SE>>---
		{ "data/SE/decision20.wav",0 },		// 決定SE
		{ "data/SE/select08.wav",0 },		// カウントダウン01SE
		{ "data/SE/select03.wav",0 },		// カウントダウン02SE
		{ "data/SE/select02.wav",0 },		// カウントダウン03SE
		{ "data/SE/police-whistle1.wav",0 },		// 開始音SE
		{ "data/SE/police-whistle2.wav",0 },		// 終了音SE
		{ "data/SE/putting_a_heavy_box.wav",0 },		// 正解SE
		{ "data/SE/deleteSE.wav",0 },		// 失敗SE
	};

};
#endif
