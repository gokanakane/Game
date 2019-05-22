//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �T�E���h�t�@�C��
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
		SOUND_LABEL_STAGE1,			//�X�e�[�W1
		SOUND_LABEL_STAGE2,			//�X�e�[�W2
		SOUND_LABEL_STAGE3,			//�X�e�[�W3
		SOUND_LABEL_STAGE4,			//�X�e�[�W4
		SOUND_LABEL_SE_NOSELECT,	// �I��s��
		SOUND_LABEL_SE_SELECT,		//�I��
		SOUND_LABEL_SE_CURSOR,		//�J�[�\��
		SOUND_LABEL_SE_SKILL,		//���@�g�p
		SOUND_LABEL_SE_HITPL,		//���@�g�p
		SOUND_LABEL_SE_HITENE,		//���@�g�p
		SOUND_LABEL_SE_DRAIN,		//���@�g�p
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
	static IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X�ւ̃|�C���^
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X�ւ̃|�C���^
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y

};
#endif
