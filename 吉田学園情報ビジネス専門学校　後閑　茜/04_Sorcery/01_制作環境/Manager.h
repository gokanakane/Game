//=============================================================================
//
// マネージャー処理 [Manager.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_RANK_SCORE (5)	//順位
#define DEFALT_COL_WHITE (D3DXCOLOR(1.0f,1.0f,1.0f,0.0f))
#define DEFALT_COL_BLACK (D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;
class CInputKeyBoard;
class CDirectXInput;
class CTitle;
class CStageSelect;
class CCharactorSelect;
class CTutorial;
class CGame;
class CResult;
class CFade;
class CRanking;
class CSound;
//*****************************************************************************
// マネージャークラス
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_STAGESELECT,
		MODE_CHARACTORSELECT,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_CLEAR,
		MODE_OVER,
		MODE_RANKING,
		MODE_MAX
	}MODE;

	typedef enum
	{//選択ステージの状態
		STAGESELECT_NONE = 0,
		STAGESELECT_STAGE1,
		STAGESELECT_STAGE2,
		STAGESELECT_STAGE3,
		STAGESELECT_STAGE4,
		STAGESELECT_MAX
	}StageSelectState;

	typedef enum
	{//キャラクター選択状態
		CHARACTORSELECT_NONE = 0,
		CHARACTORSTATE_DORAGON,		//ドラグーン
		CHARACTORSTATE_KARNERIAN,	//カーネリアン
		CHARACTORSTATE_VIVIAN,		//ビビアン
		CHARACTORSTATE_AREISTA,		//アレイスタ
		CHARACTORSTATE_RENGE,		//蓮華
		CHARACTORSTATE_LILIY,		//リリィカルト
		CHARACTORSTATE_MAX
	}CHARACTORSELECT_STATE;


	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyBoard *GetInput(void) { return m_pInput; }
	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }
	static CGame *GetGame(void) { return m_pGame; }
	static bool GetFirstTime(void) { return m_bFirstTime; }
	static void SetStageState(StageSelectState select);
	static void SetCharactorSelect(CHARACTORSELECT_STATE select);
	static void SetFirstTime(bool bFirstTime);
	static void SetScore(int nFinishScoer);
	static StageSelectState GetStageSelect(void) { return m_StageSelect; }
	static CHARACTORSELECT_STATE GetCharactorSelect(void) { return m_CharactorSelect; }
	static int GetScore(void) { return m_nScore; }
	
	static CInputKeyBoard *m_pInput;
	static CDirectXInput *m_pDirectInput;
	static int m_nHeighScore[MAX_RANK_SCORE];
	static CHARACTORSELECT_STATE m_RankingCharactor[MAX_RANK_SCORE];

private:
	static MODE m_mode;
	static CRenderer *m_pRenderer;
	static CTitle *m_pTitle;
	static CStageSelect *m_pStageSelect;
	static CCharactorSelect *m_pCharactorSelect;
	static CTutorial *m_pTutorial;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static CRanking *m_pRanking;
	static CFade *m_pFade;
	static CSound *m_pSound;
	static StageSelectState m_StageSelect;
	static CHARACTORSELECT_STATE m_CharactorSelect;
	static bool m_bFirstTime;						//1週目か判定する
	static int m_nScore;
};
#endif
