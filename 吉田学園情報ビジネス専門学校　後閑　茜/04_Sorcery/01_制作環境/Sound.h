//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// サウンドファイル
//*************************************
class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_TITLE = 0,		// BGM0
		SOUND_LABEL_STAGESELECT,	// BGM1
		SOUND_LABEL_CHARACTORSELECT,// BGM2
		SOUND_LABEL_GAMEOVER,		// BGM3 
		SOUND_LABEL_GAMECLEAR,		// BGM4 
		SOUND_LABEL_TUTORIAL,		// BGM5 
		SOUND_LABEL_RANKING,		// BGM6 
		SOUND_LABEL_STAGE1,			//ステージ1
		SOUND_LABEL_STAGE2,			//ステージ2
		SOUND_LABEL_STAGE3,			//ステージ3
		SOUND_LABEL_STAGE4,			//ステージ4
		SOUND_LABEL_SE_NOSELECT,	// 選択不可
		SOUND_LABEL_SE_SELECT,		//選択
		SOUND_LABEL_SE_CURSOR,		//カーソル
		SOUND_LABEL_SE_SKILL,		//魔法使用
		SOUND_LABEL_SE_HITPL,		//魔法使用
		SOUND_LABEL_SE_HITENE,		//魔法使用
		SOUND_LABEL_SE_DRAIN,		//魔法使用
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	static HRESULT PlaySound(SOUND_LABEL label);
	static void StopSound(SOUND_LABEL label);
	static void StopSound(void);

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	static IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのポインタ
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイスへのポインタ
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイスへのポインタ
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータへのポインタ
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// オーディオデータサイズ

};
#endif
