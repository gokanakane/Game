//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "scene.h"
#include "scene2D.h"
#include "Input.h"
#include "title.h"
#include "StageSelect.h"
#include "CharactorSelect.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "sound.h"
#include "scoreBase.h"

//*****************************************************************************
// グローバル変数/静的メンバ変数
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyBoard *CManager::m_pInput = NULL;
CDirectXInput *CManager::m_pDirectInput = NULL;
CTitle *CManager::m_pTitle = NULL;
CStageSelect *CManager::m_pStageSelect = NULL;
CCharactorSelect *CManager::m_pCharactorSelect = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CRanking *CManager::m_pRanking = NULL;
CFade *CManager::m_pFade = NULL;
CSound *CManager::m_pSound = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;
CManager::StageSelectState CManager::m_StageSelect = StageSelectState::STAGESELECT_NONE;
CManager::CHARACTORSELECT_STATE CManager::m_CharactorSelect = CManager::CHARACTORSELECT_NONE;
bool CManager::m_bFirstTime = false;
int CManager::m_nScore = 0;
int CManager::m_nHeighScore[MAX_RANK_SCORE] = {40000,35000,30000,20000,10000};
CManager::CHARACTORSELECT_STATE CManager::m_RankingCharactor[MAX_RANK_SCORE] = {	CManager::CHARACTORSTATE_DORAGON,
																					CManager::CHARACTORSTATE_DORAGON,
																					CManager::CHARACTORSTATE_DORAGON,
																					CManager::CHARACTORSTATE_DORAGON,
																					CManager::CHARACTORSTATE_DORAGON };
//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager() {}
//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager() {}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd, bool bWindow)
{

	/* レンダラーの生成 */
	if (m_pRenderer == NULL)
	{
		//レンダリングクラスの生成
		m_pRenderer = new CRenderer;
		// 初期化処理
		m_pRenderer->Init(hWnd, TRUE);
	}

	CFade::Load();

	/* 入力の生成 */
	if (m_pInput == NULL)
	{
		m_pInput = new CInputKeyBoard;
		m_pInput->Init(hInstance, hWnd);
	}
	/* コントローラーの生成 */
	if (m_pDirectInput == NULL)
	{
		m_pDirectInput = new CDirectXInput;
		m_pDirectInput->Init(hInstance, hWnd);
	}

	if (m_pFade == NULL)
	{
		m_pFade = new CFade;
		m_pFade->Init();
	}

	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
		m_pSound->Init(hWnd);
	}

	SetMode(m_mode);
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	CFade::UnLoad();

	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	
	//フェードの開放
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		m_pFade = NULL;
	}

	//インプットの開放
	if (m_pInput != NULL)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = NULL;
	}
	//コントローラーの開放
	if (m_pDirectInput != NULL)
	{
		m_pDirectInput->Uninit();
		delete m_pDirectInput;
		m_pDirectInput = NULL;
	}

	//レンダラーの開放
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//シーンの解放
	CScene::ReleaseAll();
}
//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	//キーボードの更新処理
	if (m_pInput != NULL)
	{
		m_pInput->Update();
	}

	//コントローラーの更新処理
	if (m_pDirectInput != NULL)
	{
		m_pDirectInput->Update();
	}

	//レンダラーの更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;

	case MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Update();
		}
		break;

	case MODE_CHARACTORSELECT:
		if (m_pCharactorSelect != NULL)
		{
			m_pCharactorSelect->Update();
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Update();
		}
		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;

	case MODE_CLEAR:
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	case MODE_OVER:
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;

	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Update();
		}
		break;
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	//レンダラーの描画処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Draw();
		}
		break;

	case MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Draw();
		}
		break;

	case MODE_CHARACTORSELECT:
		if (m_pCharactorSelect != NULL)
		{
			m_pCharactorSelect->Draw();
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Draw();
		}
		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Draw();
		}
		break;

	case MODE_CLEAR:
		if (m_pResult != NULL)
		{
			m_pResult->Draw();
		}
		break;
	case MODE_OVER:
		if (m_pResult != NULL)
		{
			m_pResult->Draw();
		}
		break;

	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Draw();
		}
		break;
	}

	if (m_pFade != NULL)
	{
		m_pFade->Draw();
	}
}
//=============================================================================
// モードの取得
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Uninit();
			delete m_pStageSelect;
			m_pStageSelect = NULL;
		}
		break;

	case MODE_CHARACTORSELECT:
		if (m_pCharactorSelect != NULL)
		{
			m_pCharactorSelect->Uninit();
			delete m_pCharactorSelect;
			m_pCharactorSelect = NULL;
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;

	case MODE_CLEAR:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;

	case MODE_OVER:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;

	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;
	}

	//現在のモードに切り替え
	m_mode = mode;

	//新しい画面モードの初期化設定
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = new CTitle;
			m_pTitle->Init();
		}
		break;

	case MODE_STAGESELECT:
		if (m_pStageSelect == NULL)
		{
			m_pStageSelect = new CStageSelect;
			m_pStageSelect->Init();
		}
		break;

	case MODE_CHARACTORSELECT:
		if (m_pCharactorSelect == NULL)
		{
			m_pCharactorSelect = new CCharactorSelect;
			m_pCharactorSelect->Init();
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = new CTutorial;
			m_pTutorial->Init();
		}
		break;

	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = new CGame;
			m_pGame->Init();
		}
		break;

	case MODE_CLEAR:
		if (m_pResult == NULL)
		{
			m_pResult = new CResult;
			m_pResult->Init();
		}
		break;

	case MODE_OVER:
		if (m_pResult == NULL)
		{
			m_pResult = new CResult;
			m_pResult->Init();
		}
		break;

	case MODE_RANKING:
		if (m_pRanking == NULL)
		{
			m_pRanking = new CRanking;
			m_pRanking->Init();
		}
		break;
	}
}
//=============================================================================
// 選択ステージの設定
//=============================================================================
void CManager::SetStageState(StageSelectState select)
{
	m_StageSelect = select;
}
//=============================================================================
// 選択キャラの設定
//=============================================================================
void CManager::SetCharactorSelect(CHARACTORSELECT_STATE select)
{
	m_CharactorSelect = select;
}
//=============================================================================
// 初回判定の設定
//=============================================================================
void CManager::SetFirstTime(bool bFirstTime)
{
	m_bFirstTime = bFirstTime;
}
//=============================================================================
// 最終スコアの設定
//=============================================================================
void CManager::SetScore(int nFinishScoer)
{
	m_nScore = nFinishScoer;
}