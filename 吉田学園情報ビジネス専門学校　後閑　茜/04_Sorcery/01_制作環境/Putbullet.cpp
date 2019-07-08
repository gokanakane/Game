//=============================================================================
//
// �����B�J���g�ʏ햂�@���� [Putbullet.cpp]
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
// �ÓI�����o�ϐ�
//=============================================================================
bool CPutBullet::m_bPutBulletEmergence = false;
CPutBullet::PutBulletState CPutBullet::m_state = CPutBullet::PUTBULLETSTATE_NONE;

//*****************************************************************************
// ��class CPutBullet
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//=============================================================================
CPutBullet::~CPutBullet() {}
//=============================================================================
// ����������
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
// �I������
//=============================================================================
void CPutBullet::Uninit(void)
{
	COption::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CPutBullet::Update(void)
{
	m_pos = CScene2D::GetPos();

	m_nCntAnim++;

	/* �A�j���[�V���� */
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
		{//�����_���̃^�C�~���O�Œe�𔭎�
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
// �`�揈��
//=============================================================================
void CPutBullet::Draw(void)
{
	COption::Draw();
}
