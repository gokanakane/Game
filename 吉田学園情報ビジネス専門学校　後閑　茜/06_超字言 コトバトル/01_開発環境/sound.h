//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*********************************************************************
//�T�E���h�N���X�̒�`
//*********************************************************************
//��{�N���X
class CSound
{
public:
	// �T�E���h�t�@�C��
	typedef enum //���x���Ɛ��ƕ��т𑵂���
	{
		SOUND_LABEL_BGM_TITLE = 0,		// �^�C�g��
		SOUND_LABEL_BGM_SELECT,			// �Z���N�g
		SOUND_LABEL_BGM_TUTORIAL,		// �`���[�g���A��
		SOUND_LABEL_BGM_CHARACTERSELECT,// �L�����N�^�[�Z���N�g
		SOUND_LABEL_BGM_STAGESELECT,	// �X�e�[�W�Z���N�g
		SOUND_LABEL_BGM_GAME000,		// �Q�[��[�@�B�X�e�[�W]
		SOUND_LABEL_BGM_GAME001,		// �Q�[��[�V��X�e�[�W]
		SOUND_LABEL_BGM_GAME002,		// �Q�[��[�n�`�X�e�[�W]
		SOUND_LABEL_BGM_RANKING,		// �����L���O

		SOUND_LABEL_SE_BULLET000,		// �e�Ƃ̏Փˉ�[�m�b�N�o�b�N��]
		SOUND_LABEL_SE_BULLET001,		// �e�Ƃ̏Փˉ�[�X�s�[�h]
		SOUND_LABEL_SE_BULLET002,		// �e�Ƃ̏Փˉ�[���˕Ԃ�]
		SOUND_LABEL_SE_BULLET003,		// �e�Ƃ̏Փˉ�[�ђ�]

		SOUND_LABEL_SE_GETTEXT000,		// �����擾��[1�����ڎ擾]
		SOUND_LABEL_SE_GETTEXT001,		// �����擾��[2�����ڎ擾]
		SOUND_LABEL_SE_GETTEXT002,		// �����擾��[3�����ڎ擾]

		SOUND_LABEL_SE_STEP,			// �X�e�b�v
		SOUND_LABEL_SE_PAUSEOPEN,		// �|�[�Y���������ۂ̉�
		SOUND_LABEL_SE_PAUSECLOSE,		// �|�[�Y�I�����ۂ̉�

		SOUND_LABEL_SE_CURTAIN,			// �J�[�e���̉�
		SOUND_LABEL_SE_SWITCHON,		// �X�C�b�`��������ON
		SOUND_LABEL_SE_SWITCHOFF,		// �X�C�b�`��������OFF

		SOUND_LABEL_SE_POINTUP,			// �|�C���g�A�b�v
		SOUND_LABEL_SE_POINTDOWN,		// �|�C���g�_�E��

		SOUND_LABEL_SE_SELECT00,		// ���艹
		SOUND_LABEL_SE_SELECT01,		// �L�����Z�����h���h��
		SOUND_LABEL_SE_SELECT02,		// �I����
		SOUND_LABEL_SE_SELECT03,		// �L�����N�^�[�I����
		SOUND_LABEL_SE_SELECT04,		// �Q�[���X�^�[�g

		SOUND_LABEL_VOICE_TITLECALL00,		//�^�C�g���R�[��
		SOUND_LABEL_VOICE_TITLECALL01,		//�^�C�g���R�[��2
		SOUND_LABEL_VOICE_SELECT_DOG,		//�L�����I�����@��
		SOUND_LABEL_VOICE_SELECT_BEAR,		//�L�����I�����@�F
		SOUND_LABEL_VOICE_SELECT_CAT,		//�L�����I�����@�L
		SOUND_LABEL_VOICE_SELECT_RABBIT,	//�L�����I�����@�e
		SOUND_LABEL_VOICE_DOG_ATTACK00,		//���@�U���{�C�X
		SOUND_LABEL_VOICE_DOG_ATTACK01,		//���@�U���{�C�X
		SOUND_LABEL_VOICE_DOG_DAMAGE00,		//���@��e�{�C�X
		SOUND_LABEL_VOICE_BEAR_ATTACK00,	//�F�@�U���{�C�X
		SOUND_LABEL_VOICE_BEAR_ATTACK01,	//�F�@�U���{�C�X
		SOUND_LABEL_VOICE_BEAR_DAMAGE00,	//�F�@��e�{�C�X
		SOUND_LABEL_VOICE_CAT_ATTACK00,		//�L�@�U���{�C�X
		SOUND_LABEL_VOICE_CAT_ATTACK01,		//�L�@�U���{�C�X
		SOUND_LABEL_VOICE_CAT_DAMAGE00,		//�L�@��e�{�C�X
		SOUND_LABEL_VOICE_RABBIT_ATTACK00,	//�e�@�U���{�C�X
		SOUND_LABEL_VOICE_RABBIT_ATTACK01,	//�e�@�U���{�C�X
		SOUND_LABEL_VOICE_RABBIT_DAMAGE00,	//�e�@��e�{�C�X
		SOUND_LABEL_VOICE_DOG_VICTORY,		//���@�D���R�����g
		SOUND_LABEL_VOICE_BEAR_VICTORY,		//�F�@�D���R�����g
		SOUND_LABEL_VOICE_CAT_VICTORY,		//�L�@�D���R�����g
		SOUND_LABEL_VOICE_RABBIT_VICTORY,	//�e�@�D���R�����g

		SOUND_LABEL_SE_GAMESTART00,	//�R�g�o�g��
		SOUND_LABEL_SE_GAMESTART01,	//�X�^�[�g
		SOUND_LABEL_SE_GAMEEND,		//�����܂�


		SOUND_LABEL_SE_TITLE,		// �^�C�g��

		SOUND_LABEL_SE_EXPLOSION, //����

		// �������f���̖��O
		SOUND_LABEL_WORDVOICE_KURUMA,		// �����
		SOUND_LABEL_WORDVOICE_MAIKU,		// �܂���
		SOUND_LABEL_WORDVOICE_TUKUE,		// ����
		SOUND_LABEL_WORDVOICE_PURIN,		// �Ղ��
		SOUND_LABEL_WORDVOICE_NAIHU,		// �Ȃ���
		SOUND_LABEL_WORDVOICE_RINGO,		// ���
		SOUND_LABEL_WORDVOICE_ENOGU,		// ���̂�
		SOUND_LABEL_WORDVOICE_TAIYA,		// ������
		SOUND_LABEL_WORDVOICE_TAIKO,		// ������
		SOUND_LABEL_WORDVOICE_KOIN,			// ������

		SOUND_LABEL_WORDVOICE_SUIKA,		// ������
		SOUND_LABEL_WORDVOICE_TARAI,		// ���炢
		SOUND_LABEL_WORDVOICE_YAKAN,		// �₩��
		SOUND_LABEL_WORDVOICE_IKARI,		// ������
		SOUND_LABEL_WORDVOICE_IKADA,		// ������
		SOUND_LABEL_WORDVOICE_SAIHU,		// ������
		SOUND_LABEL_WORDVOICE_KARUTA,		// ���邽
		SOUND_LABEL_WORDVOICE_KAMERA,		// ���߂�
		SOUND_LABEL_WORDVOICE_KOEDA,		// ������
		SOUND_LABEL_WORDVOICE_ITIGO,		// ������
		SOUND_LABEL_WORDVOICE_TAMAGO,		// ���܂�
		SOUND_LABEL_WORDVOICE_RANNSU,		// ���


		SOUND_LABEL_WORDVOICE_KADAN,		// ������
		SOUND_LABEL_WORDVOICE_KATANA,		// ������
		SOUND_LABEL_WORDVOICE_MARUTA,		// �܂邽
		SOUND_LABEL_WORDVOICE_TURARA,		// ���
		SOUND_LABEL_WORDVOICE_DANGO,		// ����
		SOUND_LABEL_WORDVOICE_MAKURA,		// �܂���
		SOUND_LABEL_WORDVOICE_KUNAI,		// ���Ȃ�
		SOUND_LABEL_WORDVOICE_SAKANA,		// ������

		SOUND_LABEL_WORDVOICE_KAZAN,		// ������
		SOUND_LABEL_WORDVOICE_NASUKA,		// �Ȃ���
		SOUND_LABEL_WORDVOICE_TANKU,		// ����
		SOUND_LABEL_WORDVOICE_YAGURA,		// �₮��
		SOUND_LABEL_WORDVOICE_ZAISU,		// ������
		SOUND_LABEL_WORDVOICE_KONGA,		// ����
		SOUND_LABEL_WORDVOICE_DAISU,		// ������
		SOUND_LABEL_WORDVOICE_TAKARA,		// ������
		SOUND_LABEL_WORDVOICE_GARASU,		// ���炷
		SOUND_LABEL_WORDVOICE_RINGU,		// ���

		SOUND_LABEL_WORDVOICE_KUSUMA,		// ������
		SOUND_LABEL_WORDVOICE_SAZAE,		// ������
		SOUND_LABEL_WORDVOICE_TAIRU,		// ������
		SOUND_LABEL_WORDVOICE_RAISU,		// �炢��
		SOUND_LABEL_WORDVOICE_MANGA,		// �܂�
		SOUND_LABEL_WORDVOICE_HUIGO,		// �ӂ���
		SOUND_LABEL_WORDVOICE_NAMAKO,		// �Ȃ܂�
		SOUND_LABEL_WORDVOICE_KONBU,		// �����
		SOUND_LABEL_WORDVOICE_RAITI,		// �炢��
		SOUND_LABEL_WORDVOICE_MASUKU,		// �܂���

		SOUND_LABEL_WORDVOICE_MEKABU,		// �߂���
		SOUND_LABEL_WORDVOICE_KUSURI,		// ������
		SOUND_LABEL_WORDVOICE_KAIGA,		// ������
		SOUND_LABEL_WORDVOICE_IKURA,		// ������
		SOUND_LABEL_WORDVOICE_MENKO,		// �߂�
		SOUND_LABEL_WORDVOICE_MEISU,		// �߂���
		SOUND_LABEL_WORDVOICE_SARAI,		// ���炢
		SOUND_LABEL_WORDVOICE_INKU,			// ����
		SOUND_LABEL_WORDVOICE_ZAIRU,		// ������
		SOUND_LABEL_WORDVOICE_INARI,		// ���Ȃ�

		SOUND_LABEL_WORDVOICE_GAKUHU,		// ������
		SOUND_LABEL_WORDVOICE_TAITU,		// ������
		SOUND_LABEL_WORDVOICE_KAERU,		// ������
		SOUND_LABEL_WORDVOICE_HURAGU,		// �ӂ炮
		SOUND_LABEL_WORDVOICE_SAIN,			// ������
		SOUND_LABEL_WORDVOICE_TAIMA,		// ������
		SOUND_LABEL_WORDVOICE_SAKURA,		// ������
		SOUND_LABEL_WORDVOICE_KAYAKU,		// ���₭
		SOUND_LABEL_WORDVOICE_IRUI,			// ���邢
		SOUND_LABEL_WORDVOICE_KOTATU,		// ������

		SOUND_LABEL_WORDVOICE_KUKUI,		// ������
		SOUND_LABEL_WORDVOICE_TAKOSU,		// ������
		SOUND_LABEL_WORDVOICE_SARADA,		// ���炾
		SOUND_LABEL_WORDVOICE_MENMA,		// �߂��
		SOUND_LABEL_WORDVOICE_RATAKO,		// ���炱
		SOUND_LABEL_WORDVOICE_KAMEN,		// ���߂�
		SOUND_LABEL_WORDVOICE_IHUKU,		// ���ӂ�
		SOUND_LABEL_WORDVOICE_HUSUMA,		// �ӂ���
		SOUND_LABEL_WORDVOICE_TANSU,		// ����
		SOUND_LABEL_WORDVOICE_NAMEKO,		// �Ȃ߂�

		SOUND_LABEL_WORDVOICE_IRUKA,		// ���邩
		SOUND_LABEL_WORDVOICE_ITII,			// ������
		SOUND_LABEL_WORDVOICE_KANNA,		// �����
		SOUND_LABEL_WORDVOICE_IEI,			// ������
		SOUND_LABEL_WORDVOICE_MEDAMA,		// �߂���
		SOUND_LABEL_WORDVOICE_SUDATI,		// ������
		SOUND_LABEL_WORDVOICE_RINSU,		// ���
		SOUND_LABEL_WORDVOICE_RANPU,		// ����
		SOUND_LABEL_WORDVOICE_SANGO,		// ����
		SOUND_LABEL_WORDVOICE_SUMAI,		// ���܂�

		SOUND_LABEL_WORDVOICE_KUKURI,		// ������
		SOUND_LABEL_WORDVOICE_KORUKU,		// ���邭
		SOUND_LABEL_WORDVOICE_NAHUDA,		// �Ȃӂ�
		SOUND_LABEL_WORDVOICE_SURUME,		// �����
		SOUND_LABEL_WORDVOICE_SUZUME,		// ������
		SOUND_LABEL_WORDVOICE_TITAN,		// ������
		SOUND_LABEL_WORDVOICE_YASAI,		// �₳��
		SOUND_LABEL_WORDVOICE_HUMEN,		// �ӂ߂�
		SOUND_LABEL_WORDVOICE_MAGUMA,		// �܂���
		SOUND_LABEL_WORDVOICE_KANAGU,		// ���Ȃ�

		SOUND_LABEL_WORDVOICE_SARAME,		// �����
		SOUND_LABEL_WORDVOICE_KAMASU,		// ���܂�
		SOUND_LABEL_WORDVOICE_TATARA,		// ������
		SOUND_LABEL_WORDVOICE_SUKAN,		// ������
		SOUND_LABEL_WORDVOICE_���Ԃ�,		// ���Ԃ�
		SOUND_LABEL_WORDVOICE_SUZURI,		// ������
		SOUND_LABEL_WORDVOICE_KAIKO,		// ������
		SOUND_LABEL_WORDVOICE_MEDAKA,		// �߂���

		SOUND_LABEL_1_PLAYER,				// 1�Z���N�g
		SOUND_LABEL_2_PLAYER,				// 2�Z���N�g
		SOUND_LABEL_3_PLAYER,				// 3�Z���N�g
		SOUND_LABEL_4_PLAYER,				// 4�Z���N�g

		SOUND_LABEL_AREYOUREADY,			// AREYOUREDY

		SOUND_LABEL_PLAYSELECT,				// �v���C�Z���N�g
		SOUND_LABEL_CREDIT,					// �N���W�b�g
		SOUND_LABEL_TITLEBACK,				// �^�C�g���ɖ߂�

		SOUND_LABEL_MACHINESTAGE,				// �@�B�X�e�[�W-
		SOUND_LABEL_NATURESTAGE,				// ���R�X�e�[�W-

		SOUND_LABEL_MAX
	} SOUND_LABEL;
	// �p�����[�^�\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	float GetVolume(SOUND_LABEL label);						// ���ʂ̎擾
	void SetVolume(SOUND_LABEL label, float fVolume);		// ���ʂ̐ݒ�

protected:
	IXAudio2				*m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice	*m_pMasteringVoice = NULL;						// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX] = {};			// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX] = {};			// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX] = {};				// �I�[�f�B�I�f�[�^�T�C�Y
    // �e���f�ނ̃p�����[�^ ���x���Ɛ��ƕ��т𑵂���
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/TITLE.wav", -1 },			// �^�C�g��
		{ "data/BGM/SELECT.wav", -1 },			// �Z���N�g
		{ "data/BGM/TUTORIAL.wav", -1 },		// �`���[�g���A��
		{ "data/BGM/CHARACTERSELECT.wav", -1 },	// �L�����N�^�[�Z���N�g
		{ "data/BGM/STAGESELECT.wav", -1 },		// �X�e�[�W�Z���N�g
		{ "data/BGM/GAME000.wav", -1 },			// �Q�[��[�@�B�X�e�[�W]
		{ "data/BGM/GAME000.wav", -1 },			// �Q�[��[�V��X�e�[�W]
		{ "data/BGM/GAME000.wav", -1 },			// �Q�[��[�n�`�X�e�[�W]
		{ "data/BGM/RANKING.wav", -1 },			// �����L���O

		{ "data/SE/bullet000.wav", 0 },			// �e�Ƃ̏Փˉ�[�m�b�N�o�b�N��]
		{ "data/SE/bullet001.wav", 0 },			// �e�Ƃ̏Փˉ�[�X�s�[�h]
		{ "data/SE/bullet002.wav", 0 },			// �e�Ƃ̏Փˉ�[���˕Ԃ�]
		{ "data/SE/bullet003.wav", 0 },			// �e�Ƃ̏Փˉ�[�ђ�]

		{ "data/SE/gettext000.wav", 0 },		// �����擾��[1�����ڎ擾]
		{ "data/SE/gettext001.wav", 0 },		// �����擾��[2�����ڎ擾]
		{ "data/SE/gettext002.wav", 0 },		// �����擾��[3�����ڎ擾]

		{ "data/SE/step.wav", 0 },				// �X�e�b�v
		{ "data/SE/pause_open.wav", 0 },		// �|�[�Y���������ۂ̉�
		{ "data/SE/pause_close.wav", 0 },		// �|�[�Y�I�����ۂ̉�

		{ "data/SE/Curtain.wav", 0 },		// �J�[�e��
		{ "data/SE/switchon.wav", 0 },		// �X�C�b�`��������ON
		{ "data/SE/switchoff.wav", 0 },		// �X�C�b�`��������OFF

		{ "data/SE/pointup.wav", 0 },		// �|�C���g�A�b�v
		{ "data/SE/pointupdown.wav", 0 },	// �|�C���g�_�E��

		{ "data/SE/Select1.wav", 0 },	// ���艹
		{ "data/SE/Select2.wav", 0 },	// �L�����Z����
		{ "data/SE/Select3.wav", 0 },	// �I����
		{ "data/SE/Select4.wav", 0 },	// �L�����N�^�[�I����
		{ "data/SE/Select5.wav", 0 },	// �Q�[���X�^�[�g

		{ "data/VOICE/titlecall000.wav", 0 },		//�^�C�g���R�[��
		{ "data/VOICE/titlecall001.wav", 0 },		//�^�C�g���R�[��2
		{ "data/VOICE/dog_select.wav", 0 },			//�L�����I�����@��
		{ "data/VOICE/bea_select.wav", 0 },			//�L�����I�����@�F
		{ "data/VOICE/cat_select.wav", 0 },			//�L�����I�����@�L
		{ "data/VOICE/rabit_select.wav", 0 },		//�L�����I�����@�e
		{ "data/VOICE/dog_atk000.wav", 0 },			//���@�U���{�C�X
		{ "data/VOICE/dog_atk001.wav", 0 },			//���@�U���{�C�X
		{ "data/VOICE/dog_damege.wav", 0 },			//���@��e�{�C�X
		{ "data/VOICE/bea_atk000.wav", 0 },			//�F�@�U���{�C�X
		{ "data/VOICE/bea_atk001.wav", 0 },			//�F�@�U���{�C�X
		{ "data/VOICE/bea_damege.wav", 0 },			//�F�@��e�{�C�X
		{ "data/VOICE/cat_atk000.wav", 0 },			//�L�@�U���{�C�X
		{ "data/VOICE/cat_atk001.wav", 0 },			//�L�@�U���{�C�X
		{ "data/VOICE/cat_damege.wav", 0 },			//�L�@��e�{�C�X
		{ "data/VOICE/rabit_atk000.wav", 0 },		//�e�@�U���{�C�X
		{ "data/VOICE/rabit_atk001.wav", 0 },		//�e�@�U���{�C�X
		{ "data/VOICE/rabit_damege.wav", 0 },		//�e�@��e�{�C�X
		{ "data/VOICE/dog_victory.wav", 0 },		//���@�D��
		{ "data/VOICE/bea_victory.wav", 0 },		//�F�@�D��
		{ "data/VOICE/cat_victory.wav", 0 },		//�L�@�D��
		{ "data/VOICE/rabit_victory.wav", 0 },		//�e�@�D��

		{ "data/VOICE/gamestart000.wav", 0 },		//�R�g�o�g��
		{ "data/VOICE/gamestart001.wav", 0 },		//�X�^�[�g
		{ "data/VOICE/gameend000.wav", 0 },			//�����܂�


		{ "data/SE/Title.wav", 0 },	// �^�C�g��
		{ "data/SE/Explosion001.wav", 0 },	// ����

		// �������f���� SE
		{ "data/SE/WORDVOICE/00�����.wav", 0 },			//	��
		{ "data/SE/WORDVOICE/10�܂���.wav", 0 },			//	�܂���
		{ "data/SE/WORDVOICE/21����.wav", 0 },			//	����
		{ "data/SE/WORDVOICE/32�Ղ��.wav", 0 },			//	�Ղ��
		{ "data/SE/WORDVOICE/43�Ȃ���.wav", 0 },			//	�Ȃ���
		{ "data/SE/WORDVOICE/54���.wav", 0 },			//	���
		{ "data/SE/WORDVOICE/65���̂�.wav", 0 },			//	���̂�
		{ "data/SE/WORDVOICE/76������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/87������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/97������.wav", 0 },			//	������

		{ "data/SE/WORDVOICE/00������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/11���炢.wav", 0 },			//	���炢
		{ "data/SE/WORDVOICE/22�₩��.wav", 0 },			//	�₩��
		{ "data/SE/WORDVOICE/33������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/44������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/55������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/66���邽.wav", 0 },			//	���邽
		{ "data/SE/WORDVOICE/77���߂�.wav", 0 },			//	���߂�
		{ "data/SE/WORDVOICE/88������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/98������.wav", 0 },			//	������

		{ "data/SE/WORDVOICE/01���܂�.wav", 0 },			//	���܂�
		{ "data/SE/WORDVOICE/12���.wav", 0 },			//	���
		{ "data/SE/WORDVOICE/23������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/34������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/45�܂邽.wav", 0 },			//	�܂邽
		{ "data/SE/WORDVOICE/56���.wav", 0 },			//	���
		{ "data/SE/WORDVOICE/67����.wav", 0 },			//	����
		{ "data/SE/WORDVOICE/78�܂���.wav", 0 },			//	�܂���
		{ "data/SE/WORDVOICE/89���Ȃ�.wav", 0 },			//	���Ȃ�
		{ "data/SE/WORDVOICE/99������.wav", 0 },			//	������

		{ "data/SE/WORDVOICE/02������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/13�Ȃ���.wav", 0 },			//	�Ȃ���
		{ "data/SE/WORDVOICE/24����.wav", 0 },			//	����
		{ "data/SE/WORDVOICE/35�₮��.wav", 0 },			//	�₮��
		{ "data/SE/WORDVOICE/46������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/57����.wav", 0 },			//	����
		{ "data/SE/WORDVOICE/68������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/79������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/90���炷.wav", 0 },			//	���炷
		{ "data/SE/WORDVOICE/100���.wav", 0 },			//	���

		{ "data/SE/WORDVOICE/03������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/14������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/25������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/36�炢��.wav", 0 },			//	�炢��
		{ "data/SE/WORDVOICE/47�܂�.wav", 0 },			//	�܂�
		{ "data/SE/WORDVOICE/58�ӂ���.wav", 0 },			//	�ӂ���
		{ "data/SE/WORDVOICE/69�Ȃ܂�.wav", 0 },			//	�Ȃ܂�
		{ "data/SE/WORDVOICE/80�����.wav", 0 },			//	�����
		{ "data/SE/WORDVOICE/91�炢��.wav", 0 },			//	�炢��
		{ "data/SE/WORDVOICE/101�܂���.wav", 0 },			//	�܂���

		{ "data/SE/WORDVOICE/04�߂���.wav", 0 },			//	�߂���
		{ "data/SE/WORDVOICE/15������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/26������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/37������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/48�߂�.wav", 0 },			//	�߂�
		{ "data/SE/WORDVOICE/59�߂���.wav", 0 },			//	�߂���
		{ "data/SE/WORDVOICE/70���炢.wav", 0 },			//	���炢
		{ "data/SE/WORDVOICE/81����.wav", 0 },			//	����
		{ "data/SE/WORDVOICE/92������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/102���Ȃ�.wav", 0 },			//	���Ȃ�

		{ "data/SE/WORDVOICE/05������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/16������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/27������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/38�Ղ炮.wav", 0 },			//	�Ղ炮
		{ "data/SE/WORDVOICE/49������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/60������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/71������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/82���₭.wav", 0 },			//	���₭
		{ "data/SE/WORDVOICE/93���邢.wav", 0 },			//	���邢
		{ "data/SE/WORDVOICE/103������.wav", 0 },			//	������

		{ "data/SE/WORDVOICE/06������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/17������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/28���炾.wav", 0 },			//	���炾
		{ "data/SE/WORDVOICE/39�߂��.wav", 0 },			//	�߂��
		{ "data/SE/WORDVOICE/50���炱.wav", 0 },			//	���炱
		{ "data/SE/WORDVOICE/61���߂�.wav", 0 },			//	���߂�
		{ "data/SE/WORDVOICE/72���ӂ�.wav", 0 },			//	���ӂ�
		{ "data/SE/WORDVOICE/83�ӂ���.wav", 0 },			//	�ӂ���
		{ "data/SE/WORDVOICE/94����.wav", 0 },			//	����
		{ "data/SE/WORDVOICE/104�Ȃ߂�.wav", 0 },			//	�Ȃ߂�

		{ "data/SE/WORDVOICE/07���邩.wav", 0 },			//	���邩
		{ "data/SE/WORDVOICE/18������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/29�����.wav", 0 },			//	�����
		{ "data/SE/WORDVOICE/40������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/51�߂���.wav", 0 },			//	�߂���
		{ "data/SE/WORDVOICE/62������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/73���.wav", 0 },			//	���
		{ "data/SE/WORDVOICE/84����.wav", 0 },			//	����
		{ "data/SE/WORDVOICE/95����.wav", 0 },			//	����
		{ "data/SE/WORDVOICE/105���܂�.wav", 0 },			//	���܂�

		{ "data/SE/WORDVOICE/08������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/19���邭.wav", 0 },			//	���邭
		{ "data/SE/WORDVOICE/30�Ȃӂ�.wav", 0 },			//	�Ȃӂ�
		{ "data/SE/WORDVOICE/41�߂���.wav", 0 },			//	�����
		{ "data/SE/WORDVOICE/52������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/63������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/74�₳��.wav", 0 },			//	�₳��
		{ "data/SE/WORDVOICE/85�ӂ߂�.wav", 0 },			//	�ӂ߂�
		{ "data/SE/WORDVOICE/96�܂���.wav", 0 },			//	�܂���
		{ "data/SE/WORDVOICE/106���Ȃ�.wav", 0 },			//	���Ȃ�

		{ "data/SE/WORDVOICE/09�����.wav", 0 },			//	�����
		{ "data/SE/WORDVOICE/20���܂�.wav", 0 },			//	���܂�
		{ "data/SE/WORDVOICE/31������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/42������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/53���Ԃ�.wav", 0 },			//	���Ԃ�
		{ "data/SE/WORDVOICE/64������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/75������.wav", 0 },			//	������
		{ "data/SE/WORDVOICE/86�߂���.wav", 0 },			//	�߂���

		{ "data/SE/SELECTVOICE/1�l�v���C.wav", 0 },			//	1�l�v���C
		{ "data/SE/SELECTVOICE/2�l�v���C.wav", 0 },			//	2�l�v���C
		{ "data/SE/SELECTVOICE/3�l�v���C.wav", 0 },			//	3�l�v���C
		{ "data/SE/SELECTVOICE/4�l�v���C.wav", 0 },			//	4�l�v���C

		{ "data/SE/SELECTVOICE/areyouready.wav", 0 },		//	areyouready
		{ "data/SE/SELECTVOICE/�v���C�l���I��.wav", 0 },	//	�v���C�l���I��
		{ "data/SE/SELECTVOICE/�N���W�b�g.wav", 0 },		//	�N���W�b�g
		{ "data/SE/SELECTVOICE/�^�C�g���ɖ߂�.wav", 0 },	//	�^�C�g���ɖ߂�

		{ "data/SE/SELECTVOICE/�@�B�X�e�[�W.wav", 0 },	//	�@�B�X�e�[�W
		{ "data/SE/SELECTVOICE/�V��X�e�[�W.wav", 0 },	//	���R�X�e�[�W



	};
};
#endif
