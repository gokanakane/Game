//=============================================================================
//
// 爆発処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "scene.h"
#include "bullet.h"
#include "Explosion.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
//bool g_bBool = false;
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosion::CExplosion()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = -1;
	m_nPatturnAnim = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CExplosion::~CExplosion() {}
//=============================================================================
// 爆発の生成
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = NULL;

	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;
		pExplosion->Init();
		pExplosion->BindTexture(m_pTexture);
		pExplosion->SetScene2D(pos, BULLET_SIZE, BULLET_SIZE);
		pExplosion->SetAnimX(8, 1, 0);
	}
	return pExplosion;
}
//=============================================================================
// 爆発の初期化処理
//=============================================================================
HRESULT CExplosion::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// 爆発の終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 爆発の更新処理
//=============================================================================
void CExplosion::Update(void)
{
	//アニメーションカウンター更新
	m_nCntAnim++;

	if ((m_nCntAnim % 3) == 0)
	{//一定時間経過

		m_nPatturnAnim++;

		SetAnimX(8, 1, m_nPatturnAnim);

		if (m_nPatturnAnim >= MAX_ANIMATION)
		{//アニメーションが最後まで行った
			Uninit();
		}
	}
}
//=============================================================================
// 爆発の描画処理
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CExplosion::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EXPLOSION, &m_pTexture);

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CExplosion::UnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}