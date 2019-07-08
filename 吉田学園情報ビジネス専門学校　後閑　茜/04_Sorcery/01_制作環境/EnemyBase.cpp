//=============================================================================
//
// �G�̊�Տ��� [EnemyBase.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "game.h"
#include "bullet.h"
#include "enemyBase.h"
#include "enemyNormal.h"
#include "EnemyBoss.h"
#include "enemyRelative.h"
#include "EnemyTutorial.h"
#include "abyssgate.h"
#include "scoreBase.h"
#include "Explosion.h"
#include "StageBase.h"
#include "tutorial.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_TEX] = {};
int CEnemy::m_nNumEnemyNormal = 0;
int CEnemy::m_nNumEnemyBoss = 0;
bool CEnemy::m_bFinishGame = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_bFinishGame = false;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Changecol = 0.8f;
	m_nCntState = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy() {}
//=============================================================================
// �G�̐���
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, EnemyType type, int nLife)
{
	CEnemy *pEnemy = NULL;

	switch (type)
	{
	case ENEMYTYPE_NONE:
		break;

	case ENEMYTYPE_NORMAL:
		pEnemy = new CEnemyNormal;
		pEnemy->Init();
		pEnemy->BindTexture(m_pTexture[0]);
		pEnemy->SetScene2D(pos, DEFOLT_SIZE, DEFOLT_SIZE);
		pEnemy->SetEnemyType(ENEMYTYPE_NORMAL);
		pEnemy->SetEnemyState(ENEMYSTATE_NONE);
		pEnemy->SetLife(nLife);
		pEnemy->SetAnimX(3, 1, 0);
		//�I�u�W�F�N�g�̎�ނ̐ݒ�
		pEnemy->SetObjtype(CScene::OBJTYPE_ENEMY);
		break;

	case ENEMYTYPE_BOSS:
		pEnemy = new CEnemyBoss;
		pEnemy->Init();
		pEnemy->BindTexture(m_pTexture[1]);
		pEnemy->SetScene2D(pos, 150.0f, 150.0f);
		pEnemy->SetAnimX(2, 1, 0);
		pEnemy->SetEnemyType(ENEMYTYPE_BOSS);
		pEnemy->SetEnemyState(ENEMYSTATE_NONE);
		pEnemy->SetLife(nLife);
		pEnemy->m_nMaxLife = nLife;
		//�I�u�W�F�N�g�̎�ނ̐ݒ�
		pEnemy->SetObjtype(CScene::OBJTYPE_ENEMY);
		break;

	case ENEMYTYPE_TUTORIAL:
		pEnemy = new CEnemyTutorial;
		pEnemy->Init();
		pEnemy->BindTexture(m_pTexture[0]);
		pEnemy->SetScene2D(pos, DEFOLT_SIZE, DEFOLT_SIZE);
		pEnemy->SetEnemyType(ENEMYTYPE_TUTORIAL);
		pEnemy->SetEnemyState(ENEMYSTATE_EMERGENCE);
		pEnemy->SetAnimX(3, 1, 0);
		pEnemy->SetLife(nLife);
		//�I�u�W�F�N�g�̎�ނ̐ݒ�
		pEnemy->SetObjtype(CScene::OBJTYPE_ENEMY);
		break;

	case ENEMYTYPE_RELATIVE:
		pEnemy = new CEnemyRelative;
		pEnemy->Init();
		pEnemy->BindTexture(m_pTexture[2]);
		pEnemy->SetScene2D(pos, DEFOLT_SIZE, DEFOLT_SIZE);
		pEnemy->SetEnemyType(ENEMYTYPE_RELATIVE);
		pEnemy->SetEnemyState(ENEMYSTATE_EMERGENCE);
		pEnemy->SetLife(nLife);

		switch (CManager::GetStageSelect())
		{
		case CManager::STAGESELECT_STAGE1:
			pEnemy->SetCharaAnim(0, 0.0f);
			break;
		case CManager::STAGESELECT_STAGE2:
			pEnemy->SetCharaAnim(0, 0.25f);
			break;
		case CManager::STAGESELECT_STAGE3:
			pEnemy->SetCharaAnim(0, 0.5f);
			break;
		case CManager::STAGESELECT_STAGE4:
			pEnemy->SetCharaAnim(0, 0.75f);
			break;
		}
		//�I�u�W�F�N�g�̎�ނ̐ݒ�
		pEnemy->SetObjtype(CScene::OBJTYPE_ENEMY);
		break;
	}
	return pEnemy;
}
//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	CScene2D::Init();
	return S_OK;
}
//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemy::Uninit(void)
{
	if (m_bFinishGame == true)
	{
		m_nNumEnemyNormal = 0;
		m_nNumEnemyBoss = 0;
	}

	CScene2D::Uninit();
}
//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemy::Update(void)
{
	m_pos = CScene2D::GetPos();

	/* �G�̏�� */
	switch (m_EnemyState)
	{
	case ENEMYSTATE_NONE:
		break;

	case ENEMYSTATE_DAMAGE:
		m_nLife--;

		if (m_nLife <= 0)
		{
			SetEnemyState(ENEMYSTATE_DEATH);
		}
		else
		{
			m_EnemyState = ENEMYSTATE_NONE;
		}
		break;

	case ENEMYSTATE_DEATH:
		if (m_EnemyType == ENEMYTYPE_BOSS)
		{
			CScore::AddScore(1000);
		}
		if (CManager::GetMode() == CManager::MODE_TUTORIAL)
		{
			CTutorial::SetMake(false);
		}
		this->Uninit();
		break;
	case ENEMYSTATE_EMERGENCE:
		m_nCntState++;
		m_col.a += m_Changecol;
		if (m_col.a <= 0.0f || m_col.a >= 1.0f)
		{
			m_Changecol *= -1;
		}
		SetColor(m_col);
		if (m_nCntState >= 30)
		{
			m_EnemyState = ENEMYSTATE_NONE;
			m_nCntState = 0;
		}
		break;
	}

	/* �I�v�V�����i㩂ƓG�̂����蔻��j */
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{//�I�u�W�F�N�g�̐����m�F�i�I�u�W�F�N�g�̑������m�F����j
		CScene *pScene;
		pScene = CScene::GetScene(3, nCntScene);
		if (pScene != NULL)
		{//�����m�F���ł���
			CScene::OBJTYPE objtype;
			objtype = pScene->GetObjtype();		//�I�u�W�F�N�g�̃^�C�v�������m�F�ł���

			if (objtype == OBJTYPE_ABYSSGATE)
			{//�r�r�A����㩂������炠���蔻��
				CAbyssGate *pAbyssGate = ((CAbyssGate*)pScene);
				D3DXVECTOR3 pos = pAbyssGate->GetPos();

				if (this->m_pos.x > pos.x - 50.0f
					&& this->m_pos.x < pos.x + 50.0f
					&& this->m_pos.y >pos.y - 50.0f
					&& this->m_pos.y < pos.y + 50.0f)
				{//�G��㩂̂����蔻��
					CScore::AddScore(1000);
					CExplosion::Create(pos);	//�����̐���
					pAbyssGate->SetAbyssGateState(CAbyssGate::ABYSSGATESTATE_CATCH);
					this->m_EnemyState = ENEMYSTATE_DEATH;
					break;
				}
			}
		}
	}
}
//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CEnemy::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ENEMY, &m_pTexture[0]);
	switch (CManager::GetStageSelect())
	{
	case CManager::STAGESELECT_STAGE1:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_BOSSENEMY_AIHA, &m_pTexture[1]);
		break;
	case CManager::STAGESELECT_STAGE2:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_BOSSENEMY_WAKATU, &m_pTexture[1]);
		break;
	case CManager::STAGESELECT_STAGE3:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_BOSSENEMY_MAYDAY, &m_pTexture[1]);
		break;
	case CManager::STAGESELECT_STAGE4:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_BOSSENEMY_HEBI, &m_pTexture[1]);
		break;
	}
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ENEMYRELATIVE, &m_pTexture[2]);


	return S_OK;
}
//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CEnemy::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
