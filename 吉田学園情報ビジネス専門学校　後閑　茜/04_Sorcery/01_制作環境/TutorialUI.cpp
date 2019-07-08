//=============================================================================
//
// チュートリアルUI処理 [TutorialUi.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "uiBase.h"
#include "TutorialUI.h"
#include "playerBase.h"
#include "Input.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CTutorialUi::m_pTexture[MAXTEXTURE_TUTORIALUI] = {};

//*****************************************************************************
// ▽class CTutorialUi
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CTutorialUi::CTutorialUi() :CScene2D(6)
{
	m_Type = TUTORIALUITYPE_NONE;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTutorialUi::~CTutorialUi() {}
//=============================================================================
// 生成処理
//=============================================================================
CTutorialUi *CTutorialUi::Create(CTutorialUi::TutorialUiType type)
{
	CTutorialUi *pTutorialUi = NULL;
	if (pTutorialUi == NULL)
	{
		switch (type)
		{
		case TUTORIALUITYPE_ENTER_OR_A:
			pTutorialUi = new CTutorialUi;
			pTutorialUi->Init();
			pTutorialUi->BindTexture(m_pTexture[0]);
			pTutorialUi->SetScene2D(D3DXVECTOR3(1200.0f, 180.0f, 0.0f), 70.0f, 30.0f);
			pTutorialUi->SetObjtype(CScene::OBJTYPE_UI);
			pTutorialUi->SetType(type);
			break;
		}
	}
	return pTutorialUi;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorialUi::Init(void)
{
	CScene2D::Init();
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CTutorialUi::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CTutorialUi::Update(void)
{
	switch (m_Type)
	{
	case TUTORIALUITYPE_ENTER_OR_A:
		break;
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void CTutorialUi::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CTutorialUi::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TUTORIALTEXTURE_ENTER_OR_A, &m_pTexture[0]);
	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CTutorialUi::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < MAXTEXTURE_TUTORIALUI; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}