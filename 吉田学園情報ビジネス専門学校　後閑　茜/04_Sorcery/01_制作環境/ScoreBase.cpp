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
#include "GameScore.h"
#include "RankingScore.h"
#include "ResultScore.h"
#include "time.h"
#include "ranking.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
int CScore::m_nScoreData[MAX_DIGIT] = {};
int CScore::m_nScore = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore() :CScene(5) { m_nScore = 0; }
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore() {}
//=============================================================================
// �X�R�A�̐���
//=============================================================================
CScore *CScore::Create(ScoreType type)
{
	CScore *pScore = NULL;
	
	if (pScore == NULL)
	{
		switch (type)
		{
		case SCORETYPE_GAME:
			pScore = new CGameScore;
			pScore->Init();
			break;
			
		case SCORETYPE_RANKING:
			pScore = new CRankingScore;
			pScore->Init();
			break;
		case SCORETYPE_RESULT:
			pScore = new CResultScore;
			pScore->Init();
		}
	}

	return pScore;
}
//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void CScore::AddScore(int nValue)
{
	int nNum = 100000000;	//�X�R�A�̌���+1��
	int nNum1 = 10000000;	//�X�R�A�̌���

	m_nScore += nValue;

	/*�i�[���鐔�����v�Z*/
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_nScoreData[nCnt] = (m_nScore % nNum) / nNum1;	
		
		//�������P�����炷
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}
