//=============================================================================
//
// �w�i���� [Ui.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "optionBase.h"
#include "shield.h"
#include "playerBase.h"
#include "bullet.h"
#include "Explosion.h"
#include "enemyBase.h"
#include "scoreBase.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
bool CShield::m_bShieldEmergence = false;

//*****************************************************************************
// ��class CShield
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShield::CShield()
{
	m_nLife = 0;
	m_nCntState = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShield::~CShield() {}
//=============================================================================
// ����������
//=============================================================================
HRESULT CShield::Init(void)
{
	m_nLife = 3;
	m_bShieldEmergence = true;

	COption::Init();
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CShield::Uninit(void)
{
	COption::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CShield::Update(void)
{
	CPlayer*pPlayer = CPlayer::GetPlayer();
	D3DXVECTOR3 pos = pPlayer->GetPos();

	SetPos(D3DXVECTOR3(pos.x + 60.0f, pos.y, 0.0f));

	switch (m_state)
	{
	case SHIELDSTATE_NONE:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_bShieldEmergence = true;
		break;

	case SHIELDSTATE_DAMAGE:
		SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		if (m_nLife <= 0)
		{
			m_state = SHIELDSTATE_BREAK;
		}
		else
		{
			m_nCntState--;
			if (m_nCntState <= 0)
			{
				m_state = SHIELDSTATE_NONE;
			}
		}
		break;

	case SHIELDSTATE_BREAK:
		m_bShieldEmergence = false;
		this->Uninit();
		break;
	}
	COption::Update();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CShield::Draw(void)
{
	COption::Draw();
}
//=============================================================================
// ���̃_���[�W����
//=============================================================================
void CShield::SetDamage(int Damage)
{
	m_nLife -= Damage;
	m_nCntState = 5;
	m_state = SHIELDSTATE_DAMAGE;
	if (m_nLife <= 0)
	{
		m_state = SHIELDSTATE_BREAK;
	}
}
