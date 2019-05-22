//*****************************************************************************
//
//				�����L���O�̏���[ranking.cpp]
//				Auther : Shun Yokomichi
//
//*****************************************************************************
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "score.h"			// �X�R�A
#include "number.h"			// ����
#include "ranking.h"		// �����L���O
#include "scene2D.h"		// �V�[��2D
#include "scene.h"			// �V�[��
#include "fade.h"			// �t�F�[�h
#include "input.h"			// ����
#include "rankinglogo.h"	// �����L���O���S
#include "press.h"			// �v���X�{�^��
#include "scene2d.h"		// �V�[��2D
#include "ui.h"
#include "sound.h"

//*****************************************************************************
//		�}�N����`
//*****************************************************************************
#define SIZE_X						(30.0f)		// ����
#define	SIZE_Y						(30.0f)		// �c��
#define POS_X_INTERVAL				(100)		// �����̊Ԋu
#define POS_Y_INTERVAL				(90)		// �c���̊Ԋu
#define TIME						(600)		// �����L���O���I��鎞��
#define RANK_SIZE_X					(55.0f)		// �����N�̕\���̉���
#define RANK_SIZE_Y					(40.0f)		// �����N�̕\���̏c��
#define RANK_SIZE_X_SCAlE			(7.0f)		// �����N�̕\���̉�������
#define RANK_SIZE_Y_SCAlE			(5.0f)		// �����N�̕\���̉�������
#define RANK_BOARD_POS_X			(660.0f)	// �����N��posX
#define RANK_BOARD_POS_Y			(630.0f)	// �����N��posY
#define RANK_BOARD_POS_Y_INTERVAL	(90.0f)		// �����N��posY�̊Ԋu
#define RANK_BOARD_SIZE_X			(440.0f)	// �����N�̃T�C�YX
#define RANK_BOARD_SIZE_Y			(80.0f)		// �����N�̃T�C�YY

//*****************************************************************************
//		�ÓI�����o�ϐ�
//*****************************************************************************
CNumber2D		 *CRanking::m_aRanking[MAX_RANKING][MAX_SCORE] = {};
CRnkingLogo		 *CRanking::m_pLogo[MAX_RANK_LOGO] = {};
CUiPolygon		*CRanking::m_apUi[MAX_RANKING] = {};
int				 CRanking::m_nScore[MAX_RANKING] = { 600, 500, 400, 300, 200 };
int				 CRanking::m_Pattern = 0;
int				 CRanking::m_nNum = MAX_RANKING;

//*****************************************************************************
//		�����L���O�̐���
//*****************************************************************************
CRanking *CRanking::Create(D3DXVECTOR3 pos)
{
	CRanking *pRanking = NULL;	// �|�C���^�̐���

	if (pRanking == NULL)
	{
		pRanking = new CRanking;

		if (pRanking != NULL)
		{
			pRanking->Init(pos);
		}
	}

	return pRanking;
}

//*****************************************************************************
//		�R���X�g���N�^
//*****************************************************************************
CRanking::CRanking()
{
	// �f�t�H���g�l��
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		for (int nCntRanking001 = 0; nCntRanking001 < MAX_SCORE; nCntRanking001++)
		{
			m_aRanking[nCntRanking][nCntRanking001] = NULL;
		}
	}

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_apUi[nCntRanking] = NULL;
	}
}

//*****************************************************************************
//		�f�X�g���N�^
//*****************************************************************************
CRanking::~CRanking() {}

//*****************************************************************************
//		������
//*****************************************************************************
HRESULT CRanking::Init(D3DXVECTOR3 pos)
{
	CManager::MODE pMode = CManager::GetMode();

	CNumber::Load();	//�i���o�[�̓ǂݍ���
	LoadRanking();		//���[�h�����L���O�ǂݍ���
	CRnkingLogo::Load();	// �����L���O���S�̓ǂݍ���
	CUiPolygon::Load();
	int nScore;

	if (pMode == CManager::MODE_RESULT)
	{	// ���U���g���烉���L���O
		CPress::Load();		// �v���X�{�^���̓ǂݍ���

							// �����L���O���̊Ŕ�
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			CUiPolygon::Create(D3DXVECTOR3(RANK_BOARD_POS_X, RANK_BOARD_POS_Y - (nCntRanking * RANK_BOARD_POS_Y_INTERVAL), 0.0f),
				D3DXVECTOR3(RANK_BOARD_SIZE_X, RANK_BOARD_SIZE_Y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);
		}

		// �����L���O
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			nScore = m_nScore[nCntRanking];

			if (nCntRanking == 0)
			{	// �J�E���g��0�̏ꍇ
				m_nSize = 0;
			}
			else if (nCntRanking == 1 || nCntRanking == 2)
			{	// �J�E���g���P�̏ꍇ
				m_nSize = 1;
			}
			else
			{	// �J�E���g���Q�̏ꍇ
				m_nSize = 2;
			}

			for (int nCntRanking001 = 0; nCntRanking001 < MAX_SCORE; nCntRanking001++)
			{
				m_aRanking[nCntRanking][nCntRanking001] = new CNumber2D;
				m_aRanking[nCntRanking][nCntRanking001]->Init(D3DXVECTOR3(pos.x - (nCntRanking001 * POS_X_INTERVAL), pos.y + (nCntRanking * POS_Y_INTERVAL), 0.0f),
					D3DXVECTOR3(SIZE_X - (RANK_SIZE_X_SCAlE * m_nSize), SIZE_Y - (RANK_SIZE_Y_SCAlE * m_nSize), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_aRanking[nCntRanking][nCntRanking001]->SetTex((nScore % 1), 1, D3DXVECTOR2((nScore * 0.1f), 1.0f));
				//�����L���O��ʂŔ��f������
				nScore /= 10;
			}
		}
		// ���S�̐���
		CRnkingLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f), D3DXVECTOR3(300.0f, 100.0f, 0.0f), 0);
		CRnkingLogo::Create(D3DXVECTOR3(330.0f, 260.0f, 0.0f), D3DXVECTOR3(RANK_SIZE_X, RANK_SIZE_Y, 0.0f), 1);
		CRnkingLogo::Create(D3DXVECTOR3(330.0f, 355.0f, 0.0f), D3DXVECTOR3(RANK_SIZE_X - (RANK_SIZE_X_SCAlE * 2), RANK_SIZE_Y - (RANK_SIZE_Y_SCAlE * 1), 0.0f), 2);
		CRnkingLogo::Create(D3DXVECTOR3(330.0f, 450.0f, 0.0f), D3DXVECTOR3(RANK_SIZE_X - (RANK_SIZE_X_SCAlE * 2), RANK_SIZE_Y - (RANK_SIZE_Y_SCAlE * 1), 0.0f), 3);
		CRnkingLogo::Create(D3DXVECTOR3(330.0f, 540.0f, 0.0f), D3DXVECTOR3(RANK_SIZE_X - (RANK_SIZE_X_SCAlE * 3), RANK_SIZE_Y - (RANK_SIZE_Y_SCAlE * 2), 0.0f), 4);
		CRnkingLogo::Create(D3DXVECTOR3(330.0f, 640.0f, 0.0f), D3DXVECTOR3(RANK_SIZE_X - (RANK_SIZE_X_SCAlE * 3), RANK_SIZE_Y - (RANK_SIZE_Y_SCAlE * 2), 0.0f), 5);


		// �v���X�{�^���̐���
		CPress::Create(D3DXVECTOR3(1100.0f, 680.0f, 0.0f), D3DXVECTOR3(250.0f, 130.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 0, 0.0f);

		m_fColA = 1.0f;
	}

	if (pMode == CManager::MODE_TITLE)
	{	// �^�C�g�����̃����L���O�\��

		// �����L���O���̊Ŕ�
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apUi[nCntRanking] = CUiPolygon::Create(D3DXVECTOR3(RANK_BOARD_POS_X, RANK_BOARD_POS_Y - (nCntRanking * RANK_BOARD_POS_Y_INTERVAL), 0.0f),
				D3DXVECTOR3(RANK_BOARD_SIZE_X, RANK_BOARD_SIZE_Y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);
		}

		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			nScore = m_nScore[nCntRanking];

			if (nCntRanking == 0)
			{	// �J�E���g��0�̏ꍇ
				m_nSize = 0;
			}
			else if (nCntRanking == 1 || nCntRanking == 2)
			{	// �J�E���g���P�̏ꍇ
				m_nSize = 1;
			}
			else
			{	// �J�E���g���Q�̏ꍇ
				m_nSize = 2;
			}

			for (int nCntRanking001 = 0; nCntRanking001 < MAX_SCORE; nCntRanking001++)
			{
				m_aRanking[nCntRanking][nCntRanking001] = new CNumber2D;
				m_aRanking[nCntRanking][nCntRanking001]->Init(D3DXVECTOR3(pos.x - (nCntRanking001 * POS_X_INTERVAL), pos.y + (nCntRanking * POS_Y_INTERVAL), 0.0f),
					D3DXVECTOR3(SIZE_X - (RANK_SIZE_X_SCAlE * m_nSize), SIZE_Y - (RANK_SIZE_Y_SCAlE * m_nSize), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_aRanking[nCntRanking][nCntRanking001]->SetTex((nScore % 1), 1, D3DXVECTOR2((nScore * 0.1f), 1.0f));
				//�����L���O��ʂŔ��f������
				nScore /= 10;
			}
		}

		// ���S�̐���
		m_pLogo[0] = CRnkingLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f), D3DXVECTOR3(300.0f, 100.0f, 0.0f), 0);
		m_pLogo[1] = CRnkingLogo::Create(D3DXVECTOR3(330.0f, 260.0f, 0.0f), D3DXVECTOR3(RANK_SIZE_X, RANK_SIZE_Y, 0.0f), 1);
		m_pLogo[2] = CRnkingLogo::Create(D3DXVECTOR3(330.0f, 355.0f, 0.0f), D3DXVECTOR3(RANK_SIZE_X - (RANK_SIZE_X_SCAlE * 2), RANK_SIZE_Y - (RANK_SIZE_Y_SCAlE * 1), 0.0f), 2);
		m_pLogo[3] = CRnkingLogo::Create(D3DXVECTOR3(330.0f, 450.0f, 0.0f), D3DXVECTOR3(RANK_SIZE_X - (RANK_SIZE_X_SCAlE * 2), RANK_SIZE_Y - (RANK_SIZE_Y_SCAlE * 1), 0.0f), 3);
		m_pLogo[4] = CRnkingLogo::Create(D3DXVECTOR3(330.0f, 540.0f, 0.0f), D3DXVECTOR3(RANK_SIZE_X - (RANK_SIZE_X_SCAlE * 3), RANK_SIZE_Y - (RANK_SIZE_Y_SCAlE * 2), 0.0f), 4);
		m_pLogo[5] = CRnkingLogo::Create(D3DXVECTOR3(330.0f, 640.0f, 0.0f), D3DXVECTOR3(RANK_SIZE_X - (RANK_SIZE_X_SCAlE * 3), RANK_SIZE_Y - (RANK_SIZE_Y_SCAlE * 2), 0.0f), 5);

		// �ϐ��̏�����
		m_Pattern = 0;
		m_fColA = 0.0f;
	}

	// �ϐ��̏�����
	m_nTime = 0;


	return S_OK;
}

//*****************************************************************************
//		�I������
//*****************************************************************************
void CRanking::Uninit()
{
	CManager::MODE pMode = CManager::GetMode();
	CNumber::Unload();
	CRnkingLogo::Unload();
	if (pMode == CManager::MODE_RANKING)
	{
		CPress::Unload();
	}
	CUiPolygon::Unload();

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		for (int nCntRanking001 = 0; nCntRanking001 < MAX_SCORE; nCntRanking001++)
		{
			if (m_aRanking[nCntRanking][nCntRanking001] != NULL)
			{
				//CScene2D�̏I��
				m_aRanking[nCntRanking][nCntRanking001]->Uninit();
				m_aRanking[nCntRanking][nCntRanking001] = NULL;
			}
		}
	}

	if (pMode == CManager::MODE_TITLE)
	{	// �^�C�g����Ԃ̂�
		for (int nCntLogo = 0; nCntLogo < MAX_RANK_LOGO; nCntLogo++)
		{
			if (m_pLogo[nCntLogo] != NULL)
			{	// CScene2D�̏I����
				m_pLogo[nCntLogo]->Uninit();
				m_pLogo[nCntLogo] = NULL;
			}
		}

		for (int nCntLogo = 0; nCntLogo < MAX_RANKING; nCntLogo++)
		{
			if (m_apUi[nCntLogo] != NULL)
			{	// CScene2D�̏I����
				m_apUi[nCntLogo]->Uninit();
				m_apUi[nCntLogo] = NULL;
			}
		}
	}

	CSound *pSound = CManager::GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_BGM004);

	if (pMode == CManager::MODE_RANKING)
	{
		CScene::ReleaseMode();
	}
}

//*****************************************************************************
//		�X�V����
//*****************************************************************************
void CRanking::Update()
{
	CSound *pSound = CManager::GetSound();
	CManager::MODE pMode = CManager::GetMode();

	if (pMode == CManager::MODE_RANKING)
	{	// �����L���O��ԂȂ�
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ����
			if (CManager::GetInputKeyboard()->GetALL(1) || CManager::GetInputXPad()->GetALL(1, 0) == true)
			{// �L�[�{�[�h�iENTER�j����͂����� && �񐔂�3��Ȃ�
				CFade::Create(CManager::MODE_TITLE, CFade::FADE_OUT);
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE001);
			}
		}

		m_nTime++;		// �J�E���^�[�̑���
		if (m_nTime == TIME)
		{	// ���Ԍo�ߌ�
			if (CFade::GetFade() == CFade::FADE_NONE)
			{	// �t�F�[�h���Ă��Ȃ����
				CFade::Create(CManager::MODE_TITLE, CFade::FADE_OUT);	// �^�C�g����
			}
		}

		m_fColA -= 0.2f;		//�@�F�̕ω�

		if (m_fColA <= 0.0f)
		{	// 0.0f�ɂȂ�����
			m_fColA = 1.0f;		// 1.0f�ɖ߂�
		}
		for (int nCntRanking001 = 0; nCntRanking001 < MAX_SCORE; nCntRanking001++)
		{
			if (m_aRanking[m_nNum][nCntRanking001] != NULL && m_nNum <= MAX_RANKING - 1)
			{	// �����N�C�����Ă���ꍇ
				m_aRanking[m_nNum][nCntRanking001]->Setcol(D3DXCOLOR(m_fColA, m_fColA, m_fColA, m_fColA));
			}
		}

	}

	if (pMode == CManager::MODE_TITLE)
	{	// �^�C�g���̏ꍇ
		if (m_Pattern == 0)
		{	// �v���O���O�̏ꍇ
			m_fColA += 0.02f;
			if (m_fColA >= 1.0f)
			{	// �����x��1.0f�ȏ�Ȃ�
				m_fColA = 1.0f;
				m_nTime++;		// �J�E���^�[�̑���

				if (m_nTime >= TIME)
				{	// �w��̎��ԂɂȂ�����
					m_Pattern = 2;
				}
			}
		}
		else if (m_Pattern == 2)
		{	// �t���O���Q�̏ꍇ
			m_fColA -= 0.02f;
			if (m_fColA <= 0.0f)
			{	// �����x��0.0f�ȉ��Ȃ�
				m_Pattern = 1;
			}
		}

		// �����L���O�̕\��(�F�̕ω�)
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			for (int nCntRanking001 = 0; nCntRanking001 < MAX_SCORE; nCntRanking001++)
			{
				if (m_aRanking[nCntRanking][nCntRanking001] != NULL)
				{
					m_aRanking[nCntRanking][nCntRanking001]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColA));
				}
			}
		}

		// ���S�̕\��(�F�̕ω�)
		for (int nCntLogo = 0; nCntLogo < MAX_RANK_LOGO; nCntLogo++)
		{
			if (m_pLogo[nCntLogo] != NULL)
			{
				m_pLogo[nCntLogo]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColA));
			}
		}

		for (int nCntLogo = 0; nCntLogo < MAX_RANK_LOGO; nCntLogo++)
		{
			if (m_apUi[nCntLogo] != NULL)
			{
				m_apUi[nCntLogo]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColA));
			}
		}


	}
}

//*****************************************************************************
//			�`�揈��
//*****************************************************************************
void CRanking::Draw()
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		for (int nCntRanking001 = 0; nCntRanking001 < MAX_SCORE; nCntRanking001++)
		{
			if (m_aRanking[nCntRanking][nCntRanking001] == NULL)
			{	// NULL�Ȃ�
				if (m_aRanking[nCntRanking][nCntRanking001] != NULL)
				{	// NULL����Ȃ��Ȃ�
					m_aRanking[nCntRanking][nCntRanking001]->Draw();

				}
			}
		}
	}
}

//*****************************************************************************
//			�Z�[�u�f�[�^����
//*****************************************************************************
void CRanking::SaveRanking()
{
	CScore *pSocre = NULL;		// �|�C���^����

	int nData;		// �f�[�^����ւ��p
	int nScore;		// ���݂̃X�R�A�ۊ�
	m_nNum = MAX_RANKING;

	nScore = pSocre->GetScore();

	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		if (m_nScore[MAX_RANKING - 1] <= nScore)
		{ // �����N�C������Ȃ�
			m_nNum -= 1;
			m_nScore[MAX_RANKING - 1] = nScore;
		}

		for (int nCount001 = 0; nCount001 < MAX_RANKING - 1; nCount001++)
		{
			for (int nCount002 = nCount001 + 1; nCount002 < MAX_RANKING; nCount002++)
			{
				if (m_nScore[nCount002] > m_nScore[nCount001])
				{	// ���ʂ̓���ւ�
					nData = m_nScore[nCount001];
					m_nScore[nCount001] = m_nScore[nCount002];
					m_nScore[nCount002] = nData;
					m_nNum--;
				}
			}
		}
		break;
	}

	// �t�@�C���̏�������
	FILE *pFile;

	pFile = fopen("data/TEXT/ranking.bin", "wb");

	if (pFile != NULL)
	{
		fwrite(m_aRanking, sizeof(int), MAX_RANKING, pFile);

		fclose(pFile);
	}
}

//*****************************************************************************
//			�ǂݍ��ݏ���
//*****************************************************************************
void CRanking::LoadRanking()
{
	// �ǂݍ���
	FILE *pFile;

	pFile = fopen("data/TEXT/ranking.bin", "rb");

	if (pFile != NULL)
	{
		fread(m_aRanking, sizeof(int), MAX_RANKING, pFile);

		fclose(pFile);
	}
}