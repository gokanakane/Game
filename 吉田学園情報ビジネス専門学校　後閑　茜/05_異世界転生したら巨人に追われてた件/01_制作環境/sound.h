//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Shouta Sano
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	//*************************************
	// �T�E���h�t�@�C��
	//*************************************
	typedef enum
	{// �T�E���h��
	 // BGM
		SOUND_LABEL_BGM000 = 0,	// BGM(�^�C�g��)
		SOUND_LABEL_BGM001,		// BGM(�Q�[��)
		SOUND_LABEL_BGM002,		// BGM(�Q�[��2)
		SOUND_LABEL_BGM003,		// BGM(�Q�[���N���A)
		SOUND_LABEL_BGM004,		// BGM(�Q�[���I�[�o�[)
		SOUND_LABEL_BGM005,		// BGM(�`���[�g���A��)

								// SE(�V�X�e��)
								SOUND_LABEL_SE000,		// SE(�|�[�Y���j���[�\��)
								SOUND_LABEL_SE001,		// SE(����)
								SOUND_LABEL_SE002,		// SE(�Z���N�g)
								SOUND_LABEL_SE003,		// SE(�L�����Z��)
								SOUND_LABEL_SE004,		// SE(�X�s�[�h�A�b�v)
								SOUND_LABEL_SE005,		// SE(�X�s�[�h�_�E��)
								SOUND_LABEL_SE006,		// SE(�R�C���擾)
								SOUND_LABEL_SE007,		// SE(���C�t��)

														// SE(�v���C���[����)
														SOUND_LABEL_SE008,		// SE(���s(���n))
														SOUND_LABEL_SE009,		// SE(�_�b�V��(���n))
														SOUND_LABEL_SE010,		// SE(���s(�؁E�u���b�N��))
														SOUND_LABEL_SE011,		// SE(�_�b�V��(�؁E�u���b�N��))
														SOUND_LABEL_SE012,		// SE(���s(���ނ�))
														SOUND_LABEL_SE013,		// SE(�_�b�V��(���ނ�))
														SOUND_LABEL_SE014,		// SE(���s(����))
														SOUND_LABEL_SE015,		// SE(�u���[�L(�_�b�V���L�����Z��))
														SOUND_LABEL_SE016,		// SE(�W�����v)
														SOUND_LABEL_SE017,		// SE(���n)
														SOUND_LABEL_SE018,		// SE(�|���)
														SOUND_LABEL_SE019,		// SE(���S)
														SOUND_LABEL_SE020,		// SE(���V)

																				// SE(�����E���l�̑���)
																				SOUND_LABEL_SE021,		// SE(���l�̑���)
																				SOUND_LABEL_SE022,		// SE(��)
																				SOUND_LABEL_SE023,		// SE(����)
																				SOUND_LABEL_SE024,		// SE(���敗)
																				SOUND_LABEL_SE025,		// SE(�u���b�N������)
																				SOUND_LABEL_SE026,		// SE(�c�^��o��)
																				SOUND_LABEL_SE027,		// SE(�V�[�\�[)
																				SOUND_LABEL_SE028,		// SE(���򍞂�)
																				SOUND_LABEL_SE029,		// SE(����)
																				SOUND_LABEL_SE030,		// SE(����2)
																				SOUND_LABEL_SE031,		// SE(��(��))
																				SOUND_LABEL_SE032,		// SE(�X�e�[�W����)
																				SOUND_LABEL_SE033,		// SE(�J)
																				SOUND_LABEL_SE034,		// SE(��)
																				SOUND_LABEL_SE035,		// SE(��2)
																				SOUND_LABEL_SE036,		// SE(��3)
																				SOUND_LABEL_SE037,		// SE(��)

																										// �ǉ���
																										SOUND_LABEL_SE038,	// SE(����)
																										SOUND_LABEL_SE039,	// SE(������)
																										SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	void ChangeVolume(SOUND_LABEL label, float fVolume);
	void ChagePitch(SOUND_LABEL label, float fPitch);

private:
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

																// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{// �f�[�^�p�X
		{ "Data/SOUND/BGM/Title002.wav", -1 },				// BGM0	// �^�C�g��
		{ "Data/SOUND/BGM/Game000.wav", -1 },				// BGM1	// �Q�[��
		{ "Data/SOUND/BGM/Game003.wav", -1 },				// BGM2	// �Q�[��(���l�ڋߎ�)
		{ "Data/SOUND/BGM/GameClear.wav", -1 },				// BGM3	// ���U���g(�Q�[���N���A)
		{ "Data/SOUND/BGM/Result000.wav", -1 },				// BGM4 // ���U���g(�Q�[���I�[�o�[)
		{ "Data/SOUND/BGM/Tutorial_Loop.wav", -1 },			// BGM4 // ���U���g(�`���[�g���A��)
		{ "Data/SOUND/SE/SYSTEM/Pause_Open.wav", 0 },		// SE0	// �|�[�Y���j���[�\��
		{ "Data/SOUND/SE/SYSTEM/Pause_Decision.wav", 0 },	// SE1	// ����
		{ "Data/SOUND/SE/SYSTEM/Pause_Select.wav", 0 },		// SE2	// �Z���N�g
		{ "Data/SOUND/SE/SYSTEM/Pause_Cancel.wav", 0 },		// SE3	// �L�����Z��
		{ "Data/SOUND/SE/SYSTEM/SpeedUp.wav", 0 },			// SE4	// �X�s�[�h�A�b�v
		{ "Data/SOUND/SE/SYSTEM/SpeedDown.wav", 0 },		// SE5	// �X�s�[�h�_�E��
		{ "Data/SOUND/SE/SYSTEM/Coin.wav", 0 },				// SE6	// �R�C���擾
		{ "Data/SOUND/SE/SYSTEM/Recovery.wav", 0 },			// SE7	// ���C�t�擾
		{ "Data/SOUND/SE/PLAYER/Walk_Normal.wav", 0 },		// SE8	// ���s(���n)
		{ "Data/SOUND/SE/PLAYER/Dash_Normal.wav", 0 },		// SE9	// �_�b�V��(���n)
		{ "Data/SOUND/SE/PLAYER/Walk_Tree.wav", 0 },		// SE10	// ���s(�؁E�u���b�N��)
		{ "Data/SOUND/SE/PLAYER/Dash_Tree.wav", 0 },		// SE11	// �_�b�V��(�؁E�u���b�N��)
		{ "Data/SOUND/SE/PLAYER/Walk_Grassy.wav", 0 },		// SE12	// ���s(���ނ�)
		{ "Data/SOUND/SE/PLAYER/Dash_Grassy.wav", 0 },		// SE13	// �_�b�V��(���ނ�)
		{ "Data/SOUND/SE/PLAYER/Walk_Water.wav", 0 },		// SE14	// ���s(����)
		{ "Data/SOUND/SE/PLAYER/Action_Brake.wav", 0 },		// SE15	// �u���[�L(�_�b�V���L�����Z��)
		{ "Data/SOUND/SE/PLAYER/Action_Jump.wav", 0 },		// SE16	// �W�����v
		{ "Data/SOUND/SE/PLAYER/Action_Landing.wav", 0 },	// SE17	// ���n
		{ "Data/SOUND/SE/PLAYER/Action_Down.wav", 0 },		// SE18	// �|���
		{ "Data/SOUND/SE/PLAYER/Action_Death.wav", 0 },		// SE19	// ���S
		{ "Data/SOUND/SE/PLAYER/Action_Ascension.wav", 0 },	// SE20	// ���V
		{ "Data/SOUND/SE/GAME/Walk_Giant.wav", 0 },			// SE21	// ���l�̑���
		{ "Data/SOUND/SE/GAME/Wind000.wav", 0 },			// SE22	// ��
		{ "Data/SOUND/SE/GAME/Wind001.wav", 0 },			// SE23	// ����
		{ "Data/SOUND/SE/GAME/Wind002.wav", 0 },			// SE24	// ���敗
		{ "Data/SOUND/SE/GAME/Push.wav", 0 },				// SE25	// �u���b�N������
		{ "Data/SOUND/SE/GAME/Ivy.wav", 0 },				// SE26	// �c�^��o��
		{ "Data/SOUND/SE/GAME/Seesaw.wav", 0 },				// SE27	// �V�[�\�[
		{ "Data/SOUND/SE/GAME/DiveWater.wav", 0 },			// SE28	// ���򍞂�
		{ "Data/SOUND/SE/GAME/Waterflow000.wav", 0 },		// SE29	// ����
		{ "Data/SOUND/SE/GAME/Waterflow001.wav", 0 },		// SE30	// ����2
		{ "Data/SOUND/SE/GAME/River.wav", 0 },				// SE31	// ��(��)
		{ "Data/SOUND/SE/GAME/Collapse.wav", 0 },			// SE32	// �X�e�[�W����
		{ "Data/SOUND/SE/GAME/Rain.wav", 0 },				// SE33	// �J
		{ "Data/SOUND/SE/GAME/Bird000.wav", 0 },			// SE34	// ��
		{ "Data/SOUND/SE/GAME/Bird001.wav", 0 },			// SE35	// ��2
		{ "Data/SOUND/SE/GAME/Bird002.wav", 0 },			// SE36	// ��3
		{ "Data/SOUND/SE/GAME/Insect.wav", 0 },				// SE37	// ��
		{ "Data/SOUND/SE/GAME/catch.wav", 0 },				// SE38	// ��
		{ "Data/SOUND/SE/GAME/fall.wav", 0 },				// SE39	// ��
	};

protected:
};

#endif