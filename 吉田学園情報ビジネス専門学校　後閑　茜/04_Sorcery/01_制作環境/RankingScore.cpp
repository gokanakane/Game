//=============================================================================
//
// �X�R�A���� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "scene.h"
#include "scoreBase.h"
#include "RankingScore.h"
#include "time.h"
#include "ranking.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================

//*****************************************************************************
// ��class CRankingScore
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRankingScore::CRankingScore()
{
	for (int nCntRank = 0; nCntRank < MAX_RANK_SCORE; nCntRank++)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			m_apNumber[nCntRank][nCntDigit] = NULL;
			g_aRankingScoreData[nCntRank][nCntDigit] = 0;
		}
	}

	g_nScore2 = 0;
	g_nRankingScore = 0;
	m_nNewRank = 5;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRankingScore::~CRankingScore() {}
//=============================================================================
// �X�R�A�̏���������
//=============================================================================
HRESULT CRankingScore::Init(void)
{
	for (int nCntRank = 0; nCntRank < MAX_RANK_SCORE; nCntRank++)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			m_apNumber[nCntRank][nCntDigit] = CNumber::Create();
			m_apNumber[nCntRank][nCntDigit]->Init();
			m_apNumber[nCntRank][nCntDigit]->SetPos(D3DXVECTOR3(550.0f, 200.0f + (100.0f*nCntRank), 0.0f), nCntDigit, 30.0f, 50.0f);
		}
	}
	SetHighScore(CManager::GetScore());

	return S_OK;
}

//=============================================================================
// �X�R�A�̏I������
//=============================================================================
void CRankingScore::Uninit(void)
{
	//m_apNumber��j���i�|���S�����j�����ꂽ������Score���͔̂j������Ă��Ȃ��j
	for (int nCntRank = 0; nCntRank < MAX_RANK_SCORE; nCntRank++)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			if (m_apNumber[nCntRank][nCntDigit] != NULL)
			{
				m_apNumber[nCntRank][nCntDigit]->Uninit();

				delete m_apNumber[nCntRank][nCntDigit];
				m_apNumber[nCntRank][nCntDigit] = NULL;
			}
		}
	}
}
//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CRankingScore::Update(void)
{
	int nColR = rand() % 10 + 1;
	float fColR = nColR *0.1f;

	for (int nCntRank = 0; nCntRank < MAX_RANK_SCORE; nCntRank++)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			if (m_nNewRank < 5)
			{
				m_apNumber[m_nNewRank][nCntDigit]->SetCol(D3DXCOLOR(1.0f, fColR, fColR, 1.0f));
			}
			m_apNumber[nCntRank][nCntDigit]->Update();
		}
	}
}
//=============================================================================
// �X�R�A�̕`�揈��
//=============================================================================
void CRankingScore::Draw(void)
{
	for (int nCntRank = 0; nCntRank < MAX_RANK_SCORE; nCntRank++)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			m_apNumber[nCntRank][nCntDigit]->Draw();
		}
	}
}
//=============================================================================
// �����L���O�̐ݒ�
//=============================================================================
void CRankingScore::SetHighScore(int nScore)
{
	int nNum = 100000000;
	int nNum2 = 10000000;
	int nScore1 = 0;
	int pTime = CTime::GetTime();

	//�X�R�A�v�Z
	nScore1 = nScore;

	for (int nRank = 0; nRank < MAX_RANK_SCORE; nRank++)
	{//����
		if (CManager::m_nHeighScore[nRank] < nScore1)
		{
			//�X�R�A�̃\�[�g
			m_nNewRank = nRank;
			g_nRankingScore = CManager::m_nHeighScore[nRank];
			CManager::m_nHeighScore[nRank] = nScore1;

			//�L�����N�^�[�̃\�[�g
			m_NewCharaSort = CManager::m_RankingCharactor[nRank];
			CManager::m_RankingCharactor[nRank] = CManager::GetCharactorSelect();

			for (int nRankCnt = nRank + 1; nRankCnt < MAX_RANK_SCORE; nRankCnt++)
			{
				//�X�R�A�̃\�[�g
				g_nScore2 = CManager::m_nHeighScore[nRankCnt];
				CManager::m_nHeighScore[nRankCnt] = g_nRankingScore;
				g_nRankingScore = g_nScore2;

				//�L�����N�^�[�̃\�[�g
				m_CharaSort = CManager::m_RankingCharactor[nRankCnt];
				CManager::m_RankingCharactor[nRankCnt] = m_NewCharaSort;
				m_NewCharaSort = m_CharaSort;
			}
			break;
		}
	}

	for (int nRank = 0; nRank < MAX_RANK_SCORE; nRank++)
	{//����
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			g_aRankingScoreData[nRank][nCntNum] = (CManager::m_nHeighScore[nRank] % nNum) / nNum2;	//�i�[���鐔�����v�Z
			m_apNumber[nRank][nCntNum]->SetNumber(g_aRankingScoreData[nRank][nCntNum]);

			//�������P�����炷
			nNum = nNum / 10;
			nNum2 = nNum2 / 10;

			if (nCntNum == MAX_DIGIT - 1)
			{//����������
				nNum = 100000000;
				nNum2 = 10000000;
			}
		}
	}

	//�}�l�[�W���[���̃X�R�A��������
	CManager::SetScore(0);
}
