//=============================================================================
//
// シーン2Dポリゴン処理 [scene2d.h]
// Author : 
//
//=============================================================================
#ifndef _RANKINGSCORE_H
#define _RANKINGSCORE_H

#include "main.h"
#include "scoreBase.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//*****************************************************************************
// クラス（派生）
//*****************************************************************************
class CRankingScore : public CScore
{
public:
	CRankingScore();
	~CRankingScore();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetHighScore(int nScore);

private:
	CNumber *m_apNumber[MAX_RANK_SCORE][MAX_DIGIT];
	int	g_nScore2, g_nRankingScore, g_aRankingScoreData[MAX_RANK_SCORE][MAX_DIGIT], m_nNewRank;
	//ハイスコア、仮置き変数、仮置き変数、一桁目に戻す
	CManager::CHARACTORSELECT_STATE m_CharaSort, m_NewCharaSort;//入れ替え用

	bool bRank = true;
};

#endif