//=============================================================================
//
// ボス敵処理 [EnemyBoss.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "Input.h"
#include "scene2D.h"
#include "game.h"
#include "bullet.h"
#include "enemyBase.h"
#include "enemyBoss.h"
#include "playerBase.h"
#include "scoreBase.h"
#include "Explosion.h"
#include "StageBase.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================

//*****************************************************************************
// ▽class CEnemyBoss
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyBoss::CEnemyBoss()
{
	m_nNumEnemyBoss++;
	m_nCntAnim = 0;
	m_nPatturnAnim = 0;
	m_state = BOSSENEMYLIFESTATE_NONE;
}
//=============================================================================
// デストラクタ
//=============================================================================
CEnemyBoss::~CEnemyBoss() {}
//=============================================================================
// 敵の初期化処理
//=============================================================================
HRESULT CEnemyBoss::Init(void)
{
	CEnemy::Init();
	return S_OK;
}
//=============================================================================
// 敵の終了処理
//=============================================================================
void CEnemyBoss::Uninit(void)
{
	m_nNumEnemyBoss--;
	CEnemy::Uninit();
}
//=============================================================================
// 敵の更新処理
//=============================================================================
void CEnemyBoss::Update(void)
{
	switch (m_state)
	{
	case BOSSENEMYLIFESTATE_NONE:
		if (rand() % 130 == 0)
		{//ランダムのタイミングで弾を発射
			CBullet::Create(m_pos, CBullet::BULLETTYPE_ENEMY, -BULLET_MOVE);
		}
		if (this->m_nLife <= this->m_nMaxLife / 2)
		{
			m_state = BOSSENEMYLIFESTATE_HALF;
		}
		break;
	case BOSSENEMYLIFESTATE_HALF:
		if (rand() % 100 == 0)
		{//ランダムのタイミングで弾を発射
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 20.0f, 0.0f), CBullet::BULLETTYPE_ENEMY, -BULLET_MOVE);
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, 0.0f), CBullet::BULLETTYPE_ENEMY, -BULLET_MOVE);

		}
		break;
	}
	m_nCntAnim++;
	/* アニメーション */
	if (m_nCntAnim % 10 == 0)
	{
		m_nPatturnAnim++;
		SetAnimX(2, 1, m_nPatturnAnim);

		if (m_nPatturnAnim >= 2)
		{
			m_nPatturnAnim = 0;
		}
	}
	if (rand() % 150 == 0)
	{//ランダムのタイミングで眷属召喚
		CEnemy::Create(D3DXVECTOR3(m_pos.x, float(rand() % 500 + 200), 0.0f), CEnemy::ENEMYTYPE_RELATIVE, 1);
	}

	CEnemy::Update();
}
//=============================================================================
// 敵の描画処理
//=============================================================================
void CEnemyBoss::Draw(void)
{
	CEnemy::Draw();
}