//=============================================================================
//
// スコア処理 [bullet.cpp]
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
// 静的メンバ変数
//=============================================================================
int CScore::m_nScoreData[MAX_DIGIT] = {};
int CScore::m_nScore = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore() :CScene(5) { m_nScore = 0; }
//=============================================================================
// デストラクタ
//=============================================================================
CScore::~CScore() {}
//=============================================================================
// スコアの生成
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
// スコアの加算
//=============================================================================
void CScore::AddScore(int nValue)
{
	int nNum = 100000000;	//スコアの桁数+1桁
	int nNum1 = 10000000;	//スコアの桁数

	m_nScore += nValue;

	/*格納する数字を計算*/
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_nScoreData[nCnt] = (m_nScore % nNum) / nNum1;	
		
		//桁数を１桁減らす
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}
