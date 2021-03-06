//=============================================================================
//
// ゲームスコア処理 [GameScore.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _GAMESCORE_H
#define _GAMESCORE_H

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
class CGameScore : public CScore
{
public:
	CGameScore();
	~CGameScore();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CNumber *m_apNumber[MAX_DIGIT];
};

#endif