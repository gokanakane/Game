//=============================================================================
//
// �ʏ�G���� [EnemyNormal.cpp]
// Author : 
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
#include "enemyNormal.h"
#include "playerBase.h"
#include "scoreBase.h"
#include "Explosion.h"
#include "StageBase.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================

//*****************************************************************************
// ��class CEnemyNormal
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyNormal::CEnemyNormal()
{
	m_fMoveSpeed = 0;
	m_nCntAnim = 0;
	m_nPatturnAnim = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyNormal::~CEnemyNormal() {}
//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemyNormal::Init(void)
{
	CEnemy::Init();
	m_nNumEnemyNormal++;
	m_fMoveSpeed = 2.0f;

	return S_OK;
}
//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemyNormal::Uninit(void)
{
	m_nNumEnemyNormal--;

	if (m_nNumEnemyNormal == 0)
	{
		CStage::SetBossEmergence(true);
	}
	CEnemy::Uninit();
}
//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemyNormal::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPos();
	m_nCntAnim++;

	pos.x -= m_fMoveSpeed;

	CScene2D::SetPos(pos);

	if (rand() % 150 == 0)
	{//�����_���̃^�C�~���O�Œe�𔭎�
		CBullet::Create(m_pos, CBullet::BULLETTYPE_ENEMY, -BULLET_MOVE);
	}

	if (pos.x < 50.0f + DEFOLT_SIZE)
	{
		this->m_EnemyState = ENEMYSTATE_DEATH;
		CPlayer *pPlayer = CPlayer::GetPlayer();
		pPlayer->CPlayer::SetDamage(MAX_LIFE / 5);
	}
	/* �A�j���[�V���� */
	if (m_nCntAnim % 10 == 0)
	{
		m_nPatturnAnim++;
		SetAnimX(NORMALENEMY_MAXANIM, 1, m_nPatturnAnim);

		if (m_nPatturnAnim >= NORMALENEMY_MAXANIM)
		{
			m_nPatturnAnim = 0;
		}
	}
	CEnemy::Update();
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemyNormal::Draw(void)
{
	CEnemy::Draw();
}