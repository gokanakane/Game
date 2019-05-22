//=============================================================================
//
// �X�e�[�W1 [Stage1.cpp]
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
// ��class CStage1
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStage1::CStage1() {}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStage1::~CStage1() {}
//=============================================================================
// ����������
//=============================================================================
HRESULT CStage1::Init(void)
{
	CBg::Load();
	CEnemy::Load();

	/* �w�i�̐��� */
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
// �I������
//=============================================================================
void CStage1::Uninit(void)
{
	CBg::UnLoad();
	CEnemy::UnLoad();

	/* �w�i�̔j�� */
	if (m_pBg != NULL)
	{
		m_pBg = NULL;
	}
}
//=============================================================================
// �X�V����
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
	{// �G���I�S��
		if (m_bBossEmergence == true)
		{//��̂����������邽�߂ɐ���
			m_state = STAGESTATE_BOSSEMERGENCE;
			CEnemy::Create(D3DXVECTOR3(1100.0f, SCREEN_HEIGHT / 2, 0.0f), CEnemy::ENEMYTYPE_BOSS, 50);
			m_bBossEmergence = false;
		}
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void CStage1::Draw(void) {}

