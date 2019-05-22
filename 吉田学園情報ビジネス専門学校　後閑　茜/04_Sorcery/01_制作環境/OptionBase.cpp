//=============================================================================
//
// 背景処理 [Ui.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "optionBase.h"
#include "shield.h"
#include "abyssgate.h"
#include "putbullet.h"
#include "playerBase.h"
#include "bullet.h"
#include "Explosion.h"
#include "enemyBase.h"
#include "scoreBase.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 COption::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
COption::COption() {}
//=============================================================================
// デストラクタ
//=============================================================================
COption::~COption() {}
//=============================================================================
// 生成処理
//=============================================================================
COption *COption::Create(OptionType type,D3DXVECTOR3 pos)
{
	COption *pOption = NULL;

	switch (type)
	{
	case OPTIONTYPE_SHIELD:
		pOption = new CShield;
		pOption->Init();
		pOption->SetScene2D(D3DXVECTOR3(pos.x + 60.0f, pos.y, 0.0f), 30.0f, 30.0f);
		pOption->BindTexture(m_pTexture);
		pOption->SetObjtype(CScene::OBJTYPE_SHIELD);
		pOption->SetCharaAnim(0,0.0f);
		break;

	case OPTIONTYPE_ABYSSGATE:
		pOption = new CAbyssGate;
		pOption->Init();
		pOption->SetScene2D(pos, 30.0f, 30.0f);
		pOption->BindTexture(m_pTexture);
		pOption->SetObjtype(CScene::OBJTYPE_ABYSSGATE);
		pOption->SetCharaAnim(0, 0.25f);
		break;

	case OPTIONTYPE_PUTBULLET:
		pOption = new CPutBullet;
		pOption->Init();
		pOption->SetScene2D(pos, 30.0f, 30.0f);
		pOption->BindTexture(m_pTexture);
		pOption->SetObjtype(CScene::OBJTYPE_PUTBULLET);
		pOption->SetCharaAnim(0, 0.5f);
		break;
	}

	return pOption;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT COption::Init(void)
{
	CScene2D::Init();
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void COption::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void COption::Update(void)
{
	CScene2D::Update();
}
//=============================================================================
// 描画処理
//=============================================================================
void COption::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT COption::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	D3DXCreateTextureFromFile(pDevice, TEXTURE_OPTION_SHIELD, &m_pTexture);

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void COption::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
