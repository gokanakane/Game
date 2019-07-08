//=============================================================================
//
// ゲーム処理 [Game.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CScore;
class CPause;
class CUi;
class CStage;
class COption;

//*****************************************************************************
// クラス
//*****************************************************************************
class CGame
{
public:
	typedef enum
	{
		GAMESTATE_NONE = 0, //何もしていない
		GAMESTATE_NORMAL,	//通常
		GAMESTATE_CLEAR,
		GAMESTATE_OVER,
		GAMESTATE_MAX		//最大値
	}GAMESTATE;

	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetGameState(GAMESTATE gamestate);

private:
	static CPlayer *m_pPlayer;
	static CScore *m_pScore;
	static CPause *m_pPause;
	static CUi *m_pUi;
	static CStage *m_pStage;
	static int m_nCntState;
	GAMESTATE m_GameState;
	CManager::StageSelectState m_SelectStage;
	int nCntFade = 0;

};
#endif