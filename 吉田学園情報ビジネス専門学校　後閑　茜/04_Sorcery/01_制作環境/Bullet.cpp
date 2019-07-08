//=============================================================================
//
// 弾処理 [bullet.cpp]
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
// 静的メンバ変数
//=============================================================================
//bool g_bBool = false;
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet()
{
	/* メンバ変数の初期化 */
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0; 
	m_moveDirection = 0;
	m_BulletType = BULLETTYPE_NONE;
	m_pEffect = NULL;

	CPlayer *pPlayer = CPlayer::GetPlayer();
	D3DXVECTOR3 pos = pPlayer->GetPos();
}
//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{

}
//=============================================================================
// 弾の生成
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
// 弾の初期化処理
//=============================================================================
HRESULT CBullet::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// 弾の終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 弾の更新処理
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
		//ホーミング弾できちゃった
		/*
		CPlayer *pPlayer = CPlayer::GetPlayer();
		D3DXVECTOR3 pos = pPlayer->GetPos();

		//タンジェントのXY数値を求める
		pos_x = pos.x - m_pos.x;
		pos_y = pos.y - m_pos.y;

		//角度を計算
		fAngle = atan2f(pos_x, pos_y);

		//移動量を求める
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
	{//画面外(右)
		CExplosion::Create(m_pos);
		Uninit();
	}
	else if (m_pos.x <= 0)
	{//画面外(左)
		CExplosion::Create(m_pos);
		Uninit();
	}
	else if (m_nLife <= 0)
	{//寿命がなくなった
		CExplosion::Create(m_pos);
		Uninit();
	}

	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{//オブジェクトの生存確認（オブジェクトの総数分確認する）
		CScene *pScene;
		pScene = CScene::GetScene(3, nCntScene);
		if (pScene != NULL)
		{//生存確認ができた
			CScene::OBJTYPE objtype;
			objtype = pScene->GetObjtype();		//オブジェクトのタイプが何か確認できる

			if (this->m_BulletType == BULLETTYPE_PLAYER)
			{//プレイヤーの弾
				if (objtype == OBJTYPE_ENEMY)
				{//敵だったらあたり判定をする
					CEnemy *pEnemy = ((CEnemy*)pScene);
					D3DXVECTOR3 pos = pEnemy->GetPos();

					if (m_pos.x > pos.x - 50.0f
						&& m_pos.x < pos.x + 50.0f
						&& m_pos.y >pos.y - 50.0f
						&& m_pos.y < pos.y + 50.0f)
					{//弾と敵のあたり判定
						if (pEnemy->GetEnemyState() != CEnemy::ENEMYSTATE_EMERGENCE)
						{//出現状態じゃなかったら
							CSound::PlaySound(CSound::SOUND_LABEL_SE_HITENE);
							CExplosion::Create(pos);	//爆発の生成
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
							pEnemy->SetEnemyState(CEnemy::ENEMYSTATE_DAMAGE);	//敵の破棄				
							Uninit();											//弾の破棄
						}
						break;
					}
				}
			}

			if (this->m_BulletType == BULLETTYPE_DRAIN)
			{//体力回復弾
				if (objtype == OBJTYPE_ENEMY)
				{
					CEnemy *pEnemy = ((CEnemy*)pScene);
					CPlayer *pPlayer = CPlayer::GetPlayer();
					D3DXVECTOR3 pos = pEnemy->GetPos();

					if (m_pos.x > pos.x - 50.0f
						&& m_pos.x < pos.x + 50.0f
						&& m_pos.y >pos.y - 50.0f
						&& m_pos.y < pos.y + 50.0f)
					{//弾と敵のあたり判定
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
						CExplosion::Create(pos);	//爆発の生成
						pEnemy->SetEnemyState(CEnemy::ENEMYSTATE_DAMAGE);			//敵の破棄
						pPlayer->SetRecovery(1);
						Uninit();					//弾の破棄
						break;
					}
				}
			}
			if (this->m_BulletType == BULLETTYPE_ENEMY)
			{//敵の弾
				if (objtype == OBJTYPE_PLAYER)
				{//プレイヤーだったらあたり判定をする
					CPlayer *pPlayer = ((CPlayer*)pScene);
					D3DXVECTOR3 pos = pPlayer->GetPos();
					if (pPlayer->GetState() != CPlayer::PLAYERSTATE_INVINCIBLE)
					{
						if (m_pos.x > pos.x - 10.0f
							&& m_pos.x < pos.x + 10.0f
							&& m_pos.y >pos.y - 10.0f
							&& m_pos.y < pos.y + 10.0f)
						{//弾とプレイヤーのあたり判定
							CSound::PlaySound(CSound::SOUND_LABEL_SE_HITPL);
							CExplosion::Create(pos);	//爆発の生成
							if (CManager::GetMode() == CManager::MODE_GAME)
							{//ゲームの時だけダメージ処理
								pPlayer->SetDamage(1);		//ダメージ
							}
							Uninit();					//弾の破棄
							break;
						}
					}
				}

				/* シールド */
				if (objtype == OBJTYPE_SHIELD)
				{//オプション
					CShield *pShield = ((CShield*)pScene);
					D3DXVECTOR3 pos = pShield->GetPos();
					if (m_pos.x > pos.x - 30.0f
						&& m_pos.x < pos.x + 30.0f
						&& m_pos.y >pos.y - 30.0f
						&& m_pos.y < pos.y + 30.0f)
					{
						CExplosion::Create(pos);	//爆発の生成
						pShield->SetDamage(1);	//ダメージ処理
						Uninit();					//弾の破棄
						break;
					}
				}
			}
		}
	}
}
//=============================================================================
// 弾の描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// 弾の設定処理
//=============================================================================
void CBullet::SetBullet(D3DXVECTOR3 pos, int nLife)
{
	m_pos = pos;
	m_nLife = nLife;

	SetScene2D(m_pos, BULLET_SIZE, BULLET_SIZE);
}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CBullet::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLET, &m_pTexture);

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CBullet::UnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}