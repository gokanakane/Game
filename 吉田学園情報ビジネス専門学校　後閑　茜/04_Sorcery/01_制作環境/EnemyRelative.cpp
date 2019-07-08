//=============================================================================
//
// �{�X���ő��G���� [EnemyRelative.cpp]
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
#include "enemyRelative.h"
#include "playerBase.h"
#include "scoreBase.h"
#include "Explosion.h"
#include "StageBase.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================

//*****************************************************************************
// ��class CEnemyRelative
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyRelative::CEnemyRelative()
{
	m_fMoveSpeed = 0;
	m_nCntAnim = 0;
	m_nPatturnAnim = 0;
	m_fTexAnim = 0.0f;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyRelative::~CEnemyRelative() {}
//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemyRelative::Init(void)
{
	CEnemy::Init();
	m_fMoveSpeed = 2.0f;
	switch (CManager::GetStageSelect())
	{
	case CManager::STAGESELECT_STAGE1:
		m_fTexAnim = 0.0f;
		break;
	case CManager::STAGESELECT_STAGE2:
		m_fTexAnim = 0.25f;
		break;
	case CManager::STAGESELECT_STAGE3:
		m_fTexAnim = 0.5f;
		break;
	case CManager::STAGESELECT_STAGE4:
		m_fTexAnim = 0.75f;
		break;
	}
	return S_OK;
}
//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemyRelative::Uninit(void)
{
	CEnemy::Uninit();
}
//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemyRelative::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPos();
	m_nCntAnim++;

	pos.x -= m_fMoveSpeed;

	CScene2D::SetPos(pos);

	if (pos.x < 50.0f + DEFOLT_SIZE)
	{
		this->m_EnemyState = ENEMYSTATE_DEATH;
		CPlayer *pPlayer = CPlayer::GetPlayer();
		pPlayer->CPlayer::SetDamage(MAX_LIFE / 8);
	}
	/* �A�j���[�V���� */
	if (m_nCntAnim % 10 == 0)
	{
		m_nPatturnAnim++;
		SetCharaAnim(m_nPatturnAnim, m_fTexAnim);

		if (m_nPatturnAnim >= 4)
		{
			m_nPatturnAnim = 0;
		}
	}

	CEnemy::Update();
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemyRelative::Draw(void)
{
	CEnemy::Draw();
}