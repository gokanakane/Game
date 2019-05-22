//=============================================================================
//
// ステージ1 [Stage1.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "Stage1.h"
#include "scene2D.h"
#include "bg.h"
#include "enemyBase.h"
#include "game.h"
#include "sound.h"

//*****************************************************************************
// ▽class CStage1
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CStage1::CStage1() {}
//=============================================================================
// デストラクタ
//=============================================================================
CStage1::~CStage1() {}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStage1::Init(void)
{
	CBg::Load();
	CEnemy::Load();

	/* 背景の生成 */
	if (m_pBg == NULL)
	{
		m_pBg = CBg::Create();
	}

	CEnemy::Create(D3DXVECTOR3(ENEMYPOS_INITIAL, 340.0f, 0.0f), CEnemy::ENEMYTYPE_NORMAL, 1);
	CEnemy::Create(D3DXVECTOR3(ENEMYPOS_INITIAL + 400.0f, 260.0f, 0.0f), CEnemy::ENEMYTYPE_NORMAL, 1);
	CEnemy::Create(D3DXVECTOR3(ENEMYPOS_INITIAL + 400.0f, 600.0f, 0.0f), CEnemy::ENEMYTYPE_NORMAL, 1);
	CEnemy::Create(D3DXVECTOR3(ENEMYPOS_INITIAL + 800.0f, 300.0f, 0.0f), CEnemy::ENEMYTYPE_NORMAL, 1);
	CEnemy::Create(D3DXVECTOR3(ENEMYPOS_INITIAL + 1100.0f, 400.0f, 0.0f), CEnemy::ENEMYTYPE_NORMAL, 1);
	CEnemy::Create(D3DXVECTOR3(ENEMYPOS_INITIAL + 1400.0f, 350.0f, 0.0f), CEnemy::ENEMYTYPE_NORMAL, 1);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CStage1::Uninit(void)
{
	CBg::UnLoad();
	CEnemy::UnLoad();

	/* 背景の破棄 */
	if (m_pBg != NULL)
	{
		m_pBg = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void CStage1::Update(void)
{
	switch (m_state)
	{
	case STAGESTATE_NOBOSSEMERGENCE:
		break;

	case STAGESTATE_BOSSEMERGENCE:
		if (CEnemy::GetMaxBossEnemy() <= 0)
		{
			CGame *pGame = CManager::GetGame();
			if (pGame != NULL)
			{
				pGame->SetGameState(CGame::GAMESTATE_CLEAR);
			}
		}
		break;
	}

	if (CEnemy::GetMaxNormalEnemy() <= 0)
	{// 雑魚的全滅
		if (m_bBossEmergence == true)
		{//一体だけ生成するために制限
			m_state = STAGESTATE_BOSSEMERGENCE;
			CEnemy::Create(D3DXVECTOR3(1100.0f, SCREEN_HEIGHT / 2, 0.0f), CEnemy::ENEMYTYPE_BOSS, 50);
			m_bBossEmergence = false;
		}
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void CStage1::Draw(void) {}

