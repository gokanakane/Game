//=============================================================================
//
// リリィカルト通常魔法処理 [Putbullet.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "optionBase.h"
#include "putbullet.h"
#include "playerBase.h"
#include "bullet.h"
#include "Explosion.h"
#include "enemyBase.h"
#include "scoreBase.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
bool CPutBullet::m_bPutBulletEmergence = false;
CPutBullet::PutBulletState CPutBullet::m_state = CPutBullet::PUTBULLETSTATE_NONE;

//*****************************************************************************
// ▽class CPutBullet
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CPutBullet::CPutBullet()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntTime = 0;
	m_state = PUTBULLETSTATE_NONE;
	m_nCntAnim = 0;
	m_nPatturnAnim = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CPutBullet::~CPutBullet() {}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPutBullet::Init(void)
{
	m_nCntTime = 0;
	m_state = PUTBULLETSTATE_NONE;
	m_nCntAnim = 0;
	m_nPatturnAnim = 0;

	COption::Init();
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CPutBullet::Uninit(void)
{
	COption::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CPutBullet::Update(void)
{
	m_pos = CScene2D::GetPos();

	m_nCntAnim++;

	/* アニメーション */
	if (m_nCntAnim % 8 == 0)
	{
		m_nPatturnAnim++;
		SetCharaAnim(m_nPatturnAnim, 0.5f);

		if (m_nPatturnAnim >= MAX_ANIMPATTURM)
		{
			m_nPatturnAnim = 0;
		}
	}

	switch (m_state)
	{
	case PUTBULLETSTATE_NONE:
		m_nCntTime++;
		if (rand() % 130 == 0)
		{//ランダムのタイミングで弾を発射
			CBullet::Create(m_pos, CBullet::BULLETTYPE_PLAYER, BULLET_MOVE);
		}
		if (m_nCntTime >= 600)
		{
			m_state = PUTBULLETSTATE_TIMEUP;
		}
		break;

	case PUTBULLETSTATE_TIMEUP:
		CExplosion::Create(m_pos);
		this->Uninit();
		break;
	}
	COption::Update();
}
//=============================================================================
// 描画処理
//=============================================================================
void CPutBullet::Draw(void)
{
	COption::Draw();
}
