//=============================================================================
//
// �e���� [bullet.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "scene.h"
#include "bullet.h"
#include "playerBase.h"
#include "Explosion.h"
#include "enemyBase.h"
#include "scoreBase.h"
#include "effectBase.h"
#include "optionBase.h"
#include "shield.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
//bool g_bBool = false;
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet()
{
	/* �����o�ϐ��̏����� */
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0; 
	m_moveDirection = 0;
	m_BulletType = BULLETTYPE_NONE;
	m_pEffect = NULL;

	CPlayer *pPlayer = CPlayer::GetPlayer();
	D3DXVECTOR3 pos = pPlayer->GetPos();
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}
//=============================================================================
// �e�̐���
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos,BULLETTYPE type, float direction)
{
	CBullet *pBullet = NULL;

	if (pBullet == NULL)
	{
		pBullet = new CBullet;
		pBullet->Init();
		pBullet->BindTexture(m_pTexture);
		pBullet->SetBullet(pos,80);
		pBullet->m_BulletType = type;
		pBullet->m_moveDirection = direction;
		pBullet->SetObjtype(CScene::OBJTYPE_BULLET);
	}
	return pBullet;
}
//=============================================================================
// �e�̏���������
//=============================================================================
HRESULT CBullet::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �e�̏I������
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �e�̍X�V����
//=============================================================================
void CBullet::Update(void)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife--;

	m_pos = CScene2D::GetPos();

	move.x += m_moveDirection;

	m_pos.x += move.x;
	m_pos.y += move.y;

	//else if (m_BulletType == BULLETTYPE_ENEMY)
	//{
		//�z�[�~���O�e�ł��������
		/*
		CPlayer *pPlayer = CPlayer::GetPlayer();
		D3DXVECTOR3 pos = pPlayer->GetPos();

		//�^���W�F���g��XY���l�����߂�
		pos_x = pos.x - m_pos.x;
		pos_y = pos.y - m_pos.y;

		//�p�x���v�Z
		fAngle = atan2f(pos_x, pos_y);

		//�ړ��ʂ����߂�
		move_x = sinf(fAngle)*3.0f;
		move_y = cosf(fAngle)*3.0f;

		m_pos.x += move_x;
		m_pos.y += move_y;
		*/
		//}
	CScene2D::SetPos(m_pos);
	if (m_BulletType == BULLETTYPE_PLAYER)
	{
		switch (CManager::GetCharactorSelect())
		{
		case CManager::CHARACTORSTATE_DORAGON:
			m_pEffect = CEffect::Create(m_pos, CEffect::EFFECTTYPE_BULLET, EFFECTCOL_DORAGON);
			break;
		case CManager::CHARACTORSTATE_KARNERIAN:
			m_pEffect = CEffect::Create(m_pos, CEffect::EFFECTTYPE_BULLET, EFFECTCOL_KARNERIAN);
			break;
		case CManager::CHARACTORSTATE_VIVIAN:
			m_pEffect = CEffect::Create(m_pos, CEffect::EFFECTTYPE_BULLET, EFFECTCOL_VIVIAN);
			break;
		case CManager::CHARACTORSTATE_AREISTA:
			m_pEffect = CEffect::Create(m_pos, CEffect::EFFECTTYPE_BULLET, EFFECTCOL_AREISTA);
			break;
		case CManager::CHARACTORSTATE_RENGE:
			m_pEffect = CEffect::Create(m_pos, CEffect::EFFECTTYPE_BULLET, EFFECTCOL_RENGE);
			break;
		case CManager::CHARACTORSTATE_LILIY:
			m_pEffect = CEffect::Create(m_pos, CEffect::EFFECTTYPE_BULLET, EFFECTCOL_LILIY);
			break;
		}
	}
	else if (m_BulletType == BULLETTYPE_ENEMY)
	{
		m_pEffect = CEffect::Create(m_pos, CEffect::EFFECTTYPE_BULLET, EFFECTCOL_ENEMY);
	}
	else if (m_BulletType == BULLETTYPE_DRAIN)
	{
		m_pEffect = CEffect::Create(m_pos, CEffect::EFFECTTYPE_BULLET, EFFECTCOL_AREISTA);
	}

	if (m_pos.x >= SCREEN_WIDTH)
	{//��ʊO(�E)
		CExplosion::Create(m_pos);
		Uninit();
	}
	else if (m_pos.x <= 0)
	{//��ʊO(��)
		CExplosion::Create(m_pos);
		Uninit();
	}
	else if (m_nLife <= 0)
	{//�������Ȃ��Ȃ���
		CExplosion::Create(m_pos);
		Uninit();
	}

	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{//�I�u�W�F�N�g�̐����m�F�i�I�u�W�F�N�g�̑������m�F����j
		CScene *pScene;
		pScene = CScene::GetScene(3, nCntScene);
		if (pScene != NULL)
		{//�����m�F���ł���
			CScene::OBJTYPE objtype;
			objtype = pScene->GetObjtype();		//�I�u�W�F�N�g�̃^�C�v�������m�F�ł���

			if (this->m_BulletType == BULLETTYPE_PLAYER)
			{//�v���C���[�̒e
				if (objtype == OBJTYPE_ENEMY)
				{//�G�������炠���蔻�������
					CEnemy *pEnemy = ((CEnemy*)pScene);
					D3DXVECTOR3 pos = pEnemy->GetPos();

					if (m_pos.x > pos.x - 50.0f
						&& m_pos.x < pos.x + 50.0f
						&& m_pos.y >pos.y - 50.0f
						&& m_pos.y < pos.y + 50.0f)
					{//�e�ƓG�̂����蔻��
						if (pEnemy->GetEnemyState() != CEnemy::ENEMYSTATE_EMERGENCE)
						{//�o����Ԃ���Ȃ�������
							CSound::PlaySound(CSound::SOUND_LABEL_SE_HITENE);
							CExplosion::Create(pos);	//�����̐���
							if (pEnemy->GetEnemyType() == CEnemy::ENEMYTYPE_NORMAL)
							{
								CScore::AddScore(100);
							}
							else if (pEnemy->GetEnemyType() == CEnemy::ENEMYTYPE_BOSS)
							{
								CScore::AddScore(500);
							}
							else if (pEnemy->GetEnemyType() == CEnemy::ENEMYTYPE_RELATIVE)
							{
								CScore::AddScore(200);
							}
							pEnemy->SetEnemyState(CEnemy::ENEMYSTATE_DAMAGE);	//�G�̔j��				
							Uninit();											//�e�̔j��
						}
						break;
					}
				}
			}

			if (this->m_BulletType == BULLETTYPE_DRAIN)
			{//�̗͉񕜒e
				if (objtype == OBJTYPE_ENEMY)
				{
					CEnemy *pEnemy = ((CEnemy*)pScene);
					CPlayer *pPlayer = CPlayer::GetPlayer();
					D3DXVECTOR3 pos = pEnemy->GetPos();

					if (m_pos.x > pos.x - 50.0f
						&& m_pos.x < pos.x + 50.0f
						&& m_pos.y >pos.y - 50.0f
						&& m_pos.y < pos.y + 50.0f)
					{//�e�ƓG�̂����蔻��
						CSound::PlaySound(CSound::SOUND_LABEL_SE_DRAIN);
						if (pEnemy->GetEnemyType() == CEnemy::ENEMYTYPE_NORMAL)
						{
							CScore::AddScore(100);
						}
						else if (pEnemy->GetEnemyType() == CEnemy::ENEMYTYPE_BOSS)
						{
							CScore::AddScore(500);
						}
						else if (pEnemy->GetEnemyType() == CEnemy::ENEMYTYPE_RELATIVE)
						{
							CScore::AddScore(200);
						}
						CExplosion::Create(pos);	//�����̐���
						pEnemy->SetEnemyState(CEnemy::ENEMYSTATE_DAMAGE);			//�G�̔j��
						pPlayer->SetRecovery(1);
						Uninit();					//�e�̔j��
						break;
					}
				}
			}
			if (this->m_BulletType == BULLETTYPE_ENEMY)
			{//�G�̒e
				if (objtype == OBJTYPE_PLAYER)
				{//�v���C���[�������炠���蔻�������
					CPlayer *pPlayer = ((CPlayer*)pScene);
					D3DXVECTOR3 pos = pPlayer->GetPos();
					if (pPlayer->GetState() != CPlayer::PLAYERSTATE_INVINCIBLE)
					{
						if (m_pos.x > pos.x - 10.0f
							&& m_pos.x < pos.x + 10.0f
							&& m_pos.y >pos.y - 10.0f
							&& m_pos.y < pos.y + 10.0f)
						{//�e�ƃv���C���[�̂����蔻��
							CSound::PlaySound(CSound::SOUND_LABEL_SE_HITPL);
							CExplosion::Create(pos);	//�����̐���
							if (CManager::GetMode() == CManager::MODE_GAME)
							{//�Q�[���̎������_���[�W����
								pPlayer->SetDamage(1);		//�_���[�W
							}
							Uninit();					//�e�̔j��
							break;
						}
					}
				}

				/* �V�[���h */
				if (objtype == OBJTYPE_SHIELD)
				{//�I�v�V����
					CShield *pShield = ((CShield*)pScene);
					D3DXVECTOR3 pos = pShield->GetPos();
					if (m_pos.x > pos.x - 30.0f
						&& m_pos.x < pos.x + 30.0f
						&& m_pos.y >pos.y - 30.0f
						&& m_pos.y < pos.y + 30.0f)
					{
						CExplosion::Create(pos);	//�����̐���
						pShield->SetDamage(1);	//�_���[�W����
						Uninit();					//�e�̔j��
						break;
					}
				}
			}
		}
	}
}
//=============================================================================
// �e�̕`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void CBullet::SetBullet(D3DXVECTOR3 pos, int nLife)
{
	m_pos = pos;
	m_nLife = nLife;

	SetScene2D(m_pos, BULLET_SIZE, BULLET_SIZE);
}
//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CBullet::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLET, &m_pTexture);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CBullet::UnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}