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
#include "RankingScore.h"
#include "time.h"
#include "ranking.h"
#include "fade.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================

//*****************************************************************************
// ▽class CRankingScore
//*****************************************************************************
//=============================================================================
// コンストラクタ
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
// デストラクタ
//=============================================================================
CRankingScore::~CRankingScore() {}
//=============================================================================
// スコアの初期化処理
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
// スコアの終了処理
//=============================================================================
void CRankingScore::Uninit(void)
{
	//m_apNumberを破棄（ポリゴンが破棄されただけでScore自体は破棄されていない）
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
// スコアの更新処理
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
// スコアの描画処理
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
// ランキングの設定
//=============================================================================
void CRankingScore::SetHighScore(int nScore)
{
	int nNum = 100000000;
	int nNum2 = 10000000;
	int nScore1 = 0;
	int pTime = CTime::GetTime();

	//スコア計算
	nScore1 = nScore;

	for (int nRank = 0; nRank < MAX_RANK_SCORE; nRank++)
	{//順位
		if (CManager::m_nHeighScore[nRank] < nScore1)
		{
			//スコアのソート
			m_nNewRank = nRank;
			g_nRankingScore = CManager::m_nHeighScore[nRank];
			CManager::m_nHeighScore[nRank] = nScore1;

			//キャラクターのソート
			m_NewCharaSort = CManager::m_RankingCharactor[nRank];
			CManager::m_RankingCharactor[nRank] = CManager::GetCharactorSelect();

			for (int nRankCnt = nRank + 1; nRankCnt < MAX_RANK_SCORE; nRankCnt++)
			{
				//スコアのソート
				g_nScore2 = CManager::m_nHeighScore[nRankCnt];
				CManager::m_nHeighScore[nRankCnt] = g_nRankingScore;
				g_nRankingScore = g_nScore2;

				//キャラクターのソート
				m_CharaSort = CManager::m_RankingCharactor[nRankCnt];
				CManager::m_RankingCharactor[nRankCnt] = m_NewCharaSort;
				m_NewCharaSort = m_CharaSort;
			}
			break;
		}
	}

	for (int nRank = 0; nRank < MAX_RANK_SCORE; nRank++)
	{//順位
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			g_aRankingScoreData[nRank][nCntNum] = (CManager::m_nHeighScore[nRank] % nNum) / nNum2;	//格納する数字を計算
			m_apNumber[nRank][nCntNum]->SetNumber(g_aRankingScoreData[nRank][nCntNum]);

			//桁数を１桁減らす
			nNum = nNum / 10;
			nNum2 = nNum2 / 10;

			if (nCntNum == MAX_DIGIT - 1)
			{//初期化する
				nNum = 100000000;
				nNum2 = 10000000;
			}
		}
	}

	//マネージャー側のスコアを初期化
	CManager::SetScore(0);
}
