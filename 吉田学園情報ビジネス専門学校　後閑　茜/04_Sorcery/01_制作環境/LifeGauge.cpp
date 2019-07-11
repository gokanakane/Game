//=============================================================================
//
// 体力ゲージ処理 [LifeGauge.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "GameUi.h"
#include "LifeGauge.h"
#include "playerBase.h"
#include "Input.h"
//=============================================================================
// 静的メンバ変数
//=============================================================================
CLifeGauge::LifeState CLifeGauge::m_State = CLifeGauge::LIFESTATE_NONE;
LPDIRECT3DTEXTURE9 CLifeGauge::m_pTexture = NULL;
int CLifeGauge::m_nMaxLife = 0;

//*****************************************************************************
// ▽class CLifeGauge
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CLifeGauge::CLifeGauge() :CScene2D(5)
{
	m_State = LIFESTATE_NONE;
	m_nMaxLife = CPlayer::GetLife();
	m_fNowLifeGauge = 0.0f;
}
//=============================================================================
// デストラクタ
//=============================================================================
CLifeGauge::~CLifeGauge() {}
//=============================================================================
// 生成処理
//=============================================================================
CLifeGauge *CLifeGauge::Create()
{
	CLifeGauge *pLifeGauge = NULL;
	if (pLifeGauge == NULL)
	{
		pLifeGauge = new CLifeGauge;
		pLifeGauge->Init();
		pLifeGauge->BindTexture(m_pTexture);
		pLifeGauge->SetScene2DLeftCenter(LIFEGAUGEPOS_CENTER, 800.0f, 50.0f);
		pLifeGauge->SetObjtype(CScene::OBJTYPE_UI);
	}
	return pLifeGauge;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLifeGauge::Init(void)
{
	CScene2D::Init();
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CLifeGauge::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CLifeGauge::Update(void)
{
	float nNowLife = float(CPlayer::GetLife());	//Int型の体力をfloatに変換して取得してくる
	m_fNowLifeGauge = nNowLife / m_nMaxLife;	//現在の体力/全体の体力で全体の何％減ったか計算する

												//計算結果をかけてゲージの大きさを調整する。
	SetScene2DLeftCenter(D3DXVECTOR3(LIFEGAUGEPOS_CENTER), 800.0f*m_fNowLifeGauge, 50.0f);

	if (m_fNowLifeGauge <= 0.5f)
	{//体力が50％切ったら
		m_State = LIFESTATE_HALF;
	}
	if (m_fNowLifeGauge <= 0.3f)
	{//体力が30%切ったら
		m_State = LIFESTATE_PINCH;
	}

	switch (m_State)
	{
	case LIFESTATE_NONE:
		m_State = LIFESTATE_MARGIN;
		break;

	case LIFESTATE_MARGIN:
		SetColor(LIFEGAUGECOL_MARGIN);
		break;

	case LIFESTATE_HALF:
		SetColor(LIFEGAUGECOL_HARF);
		break;

	case LIFESTATE_PINCH:
		SetColor(LIFEGAUGECOL_PINTH);
		break;
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CLifeGauge::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CLifeGauge::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, LIFEGAUGE_TEXTURE, &m_pTexture);

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CLifeGauge::UnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
