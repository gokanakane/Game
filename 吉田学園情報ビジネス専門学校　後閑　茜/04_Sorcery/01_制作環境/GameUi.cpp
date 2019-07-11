//=============================================================================
//
// ゲームUI処理 [GameUi.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "GameUi.h"
#include "LifeGauge.h"
#include "button.h"
#include "TutorialUI.h"
#include "playerBase.h"
#include "Input.h"
#include "time.h"
#include "cutinBase.h"
#include "sound.h"
//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CUi::m_pTexture[MAX_UITEXTURE] = {};
CLifeGauge *CUi::m_pLifeGauge = NULL;
CButton *CUi::m_pButton = NULL;

//*****************************************************************************
// ▽class CUi
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CUi::CUi() :CScene(5) {}
//=============================================================================
// デストラクタ
//=============================================================================
CUi::~CUi() {}
//=============================================================================
// 背景の生成
//=============================================================================
CUi *CUi::Create(void)
{
	CUi *pUi = NULL;

	if (pUi == NULL)
	{
		pUi = new CUi;
		pUi->Init();
	}

	//オブジェクトの種類の設定
	pUi->SetObjtype(CScene::OBJTYPE_UI);

	return pUi;
}
//=============================================================================
// 背景の初期化処理
//=============================================================================
HRESULT CUi::Init(void)
{
	if (m_pLifeGauge == NULL)
	{
		m_pLifeGauge->Create();
	}
	if (m_pButton == NULL)
	{
		m_pButton->Create(BUTTONTYPE_NORMAL);
		//m_pButton->Create(BUTTONTYPE_KIWAME);
	}

	for (int nCnt = 0; nCnt < MAX_UITEXTURE; nCnt++)
	{
		if (nCnt == 0)
		{//運命線
			m_apScene2D[nCnt] = new CScene2D(5);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(50.0f,SCREEN_HEIGHT/2, 0.0f), 5.0f, SCREEN_HEIGHT / 2);
			m_apScene2D[nCnt]->SetColor(DESTINYLINE_COL);
		}
		else if (nCnt == 1)
		{//体力バー
			m_apScene2D[nCnt] = new CScene2D(5);
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(455.0f, 60.0f, 0.0f), 400.0f, 50.0f);
		}
	}
	return S_OK;
}

//=============================================================================
// 背景の終了処理
//=============================================================================
void CUi::Uninit(void)
{
	//m_apScene2Dを破棄（ポリゴンが破棄されただけでUi自体は破棄されていない）
	for (int nCnt = 0; nCnt < MAX_UITEXTURE; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}

	if (m_pLifeGauge != NULL)
	{
		m_pLifeGauge->Uninit();
		m_pLifeGauge = NULL;
	}

	//Uiを破棄
	Release();
}
//=============================================================================
// 背景の更新処理
//=============================================================================
void CUi::Update(void) {}
//=============================================================================
// 背景の描画処理
//=============================================================================
void CUi::Draw(void) {}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CUi::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, NULL, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, UI_HPFREAM, &m_pTexture[1]);

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CUi::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_UITEXTURE; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
