//=============================================================================
//
// �Q�[������ [game.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include "player.h"
#include "tube.h"
#include "meshField.h"
//�O���錾
class CPlayer;
class CTube;
class CPoint;
class CSetWord;
class CWall;
class CStageSelect;
class CPause;
//=============================================================================
// �}�N����`
//=============================================================================
//********************************
// 1��ʎ��̓��̈ʒu
//********************************
#define WORD_TUBE001_POS_1P		(D3DXVECTOR3(160.0f, 590.0f, 0.0f))		// 2��ʎ�(1P)�̈ʒu
#define WORD_SIZE_001			(D3DXVECTOR2(225.0f, 170.0f))			// 2��ʎ��̃T�C�Y

//********************************
// 2��ʎ��̓��̈ʒu
//********************************
#define WORD_TUBE002_POS_1P		(D3DXVECTOR3(250.0f, 268.0f, 0.0f))		// 2��ʎ�(1P)�̈ʒu
#define WORD_TUBE002_POS_2P		(D3DXVECTOR3(250.0f, 633.0f, 0.0f))		// 2��ʎ�(2P)�̈ʒu
#define WORD_SIZE_002			(D3DXVECTOR2(150.0f, 120.0f))			// 2��ʎ��̃T�C�Y

//********************************
// 3��ʎ��̓��̈ʒu
//********************************
#define WORD_TUBE003_POS_1P		(D3DXVECTOR3(120.0f, 268.0f, 0.0f))		// 3��ʎ�(1P)�̈ʒu
#define WORD_TUBE003_POS_2P		(D3DXVECTOR3(770.0f, 268.0f, 0.0f))		// 3��ʎ�(2P)�̈ʒu
#define WORD_TUBE003_POS_3P		(D3DXVECTOR3(120.0f, 633.0f, 0.0f))		// 3��ʎ�(3P)�̈ʒu

//********************************
// 4��ʎ��̓��̈ʒu
//********************************
#define WORD_TUBE004_POS_1P		(D3DXVECTOR3(120.0f, 268.0f, 0.0f))		// 4��ʎ�(1P)�̈ʒu
#define WORD_TUBE004_POS_2P		(D3DXVECTOR3(770.0f, 268.0f, 0.0f))		// 4��ʎ�(2P)�̈ʒu
#define WORD_TUBE004_POS_3P		(D3DXVECTOR3(120.0f, 633.0f, 0.0f))		// 4��ʎ�(3P)�̈ʒu
#define WORD_TUBE004_POS_4P		(D3DXVECTOR3(770.0f, 633.0f, 0.0f))		// 4��ʎ�(4P)�̈ʒu

#define MAX_PLAYER (4)
#define MAX_STAGE	(3)			// �X�e�[�W�̍ő吔
#define MAX_STAGECOUNT	(3)		// �e�X�e�[�W�̐�

#define MAX_WALLGAME	(12)		// �ǂ̍ő吔


//�N���X�i�V�[��2D�̔h���N���X�j
class CGame
{
public:
	CGame();
	~CGame();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadChara(void);
	static CGame *Create(void);

	void WordCreate(void);	// �����̐����̊Ǘ�
	void SetStage(int nNumState,int nCntState);	// �X�e�[�W�̐���
	void SetCreateWord(void);

	void RankingUpdata(void);	// ���ʂ̓���ւ�

	// �擾�̊֐�
	static CPlayer *GetPlayer(int nNumPlayer = 0) { return (nNumPlayer < MAX_PLAYER && nNumPlayer >= 0) ? m_pPlayer[nNumPlayer] : m_pPlayer[0]; }		// �v���C���[�̎擾
	static CTube *GetTube(int nNum);		// �����̉���UI�̎擾
	static CMeshField *GetMeshField(void) { return m_pMeshField; }			// �n�ʂ̎擾
	static CPoint *GetPoint(int nNum) { return m_pPoint[nNum]; }			// �|�C���g�̎擾
	static CSetWord *GetWordCreate(void) { return m_pWordCreate; }			// �����o���̎擾
	int GetChangeNum(void) { return m_nChangeNum; }
	static void SetCharaSelect(int PlNum, CPlayer::PLAYER_TYPE type) { m_type[PlNum] = type; }
	static int GetNumStage(void) { return m_nNumStage; }
	static CPlayer::PLAYER_TYPE GetPlayerType(int nNumPlayer = 0) { return m_type[nNumPlayer]; }
	static void bStageSet(bool bStageSet) { m_bStageSet = bStageSet; };
	static bool GetbStageSet(void) { return m_bStageSet; };

private:
	void CameraSetting(int nNum);		// �l���ɉ������J��������
	void PlayerSetting(int nNum);		// �l���ɉ������v���C���[����
	void TubeSetting(int nNum);			// �l���ɉ��������̐���
	void SetPointFrame(int nNum);		// �l���ɉ������|�C���g�̐���
	static CPlayer *m_pPlayer[MAX_PLAYER];
	static CTube *m_apTube[MAX_PLAYER];
	static CPoint *m_pPoint[MAX_PLAYER];
	static CMeshField *m_pMeshField;
	static CWall *m_pWall;
	static bool m_bStageSet;
	static CPause* m_pPause;

	static CSetWord *m_pWordCreate;
	static CPlayer::PLAYER_TYPE m_type[MAX_PLAYER];
	char *m_pcStageName[MAX_STAGE][MAX_STAGECOUNT];		// �X�e�[�W�̖��O�ۊ�
	char *m_pcStageNameWord[MAX_STAGE][MAX_STAGECOUNT];	// �X�e�[�W�̖��O�ۊ�
	int m_nChangeNum;
	static int m_nNumStage;
};
#endif