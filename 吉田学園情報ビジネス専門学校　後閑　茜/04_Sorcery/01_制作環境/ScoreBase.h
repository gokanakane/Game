//=============================================================================
//
// スコア基盤処理 [ScoreBase.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _SCOREBASE_H
#define _SCOREBASE_H

#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_DIGIT (8)		//桁数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;
//*****************************************************************************
// クラス（派生）
//*****************************************************************************
class CScore : public CScene
{
public:
	typedef enum
	{//スコアの種類
		SCORETYPE_NONE = 0,
		SCORETYPE_GAME,
		SCORETYPE_RANKING,
		SCORETYPE_RESULT,
		SCORETYPE_MAX
	}ScoreType;

	CScore();
	virtual ~CScore();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static CScore*Create(ScoreType type);
	static void AddScore(int nValue);

protected:
	static int m_nScore;
	static int m_nScoreData[MAX_DIGIT];

private:

};
#endif
