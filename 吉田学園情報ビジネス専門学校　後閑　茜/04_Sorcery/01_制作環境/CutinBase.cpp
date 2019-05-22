//=============================================================================
//
// カットイン処理 [cutin.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "cutinBase.h"
#include "cutinNormal.h"
#include "cutinKIWAME.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CCutIn::m_pTexture[MAX_CUTINTEX] = {};
//=============================================================================
// コンストラクタ
//=============================================================================
CCutIn::CCutIn() :CScene2D(5)
{
	m_nCntPlayCutImNormal = 0;
	m_nCntPlayCutInKIWAME = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CCutIn::~CCutIn() {}
//=============================================================================
// 背景の生成
//=============================================================================
CCutIn *CCutIn::Create(CutinType type, CManager::CHARACTORSELECT_STATE state)
{
	CCutIn *m_pUi = NULL;

	switch (type)
	{
	case CUTINTYPE_NORMAL:
		if (m_pUi == NULL)
		{
			m_pUi = new CCutInNormal;
			m_pUi->Init();
			m_pUi->BindTexture(m_pTexture[0]);
			m_pUi->SetScene2D(D3DXVECTOR3(1100.0f, 520.0f, 0.0f), 200.0f, 200.0f);
			m_pUi->SetAnimY(1, 6, state - 1);
		}
		break;
	case CUTINTYPE_KIWAME:
		if (m_pUi == NULL)
		{
			m_pUi = new CCutInKIWAME;
			m_pUi->Init();
			m_pUi->BindTexture(m_pTexture[1]);
			m_pUi->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH/2,300.0f, 0.0f), SCREEN_WIDTH / 2, 150.0f);
			m_pUi->SetAnimY(1, 6, state - 1);

		}
		break;
	}

	//オブジェクトの種類の設定
	m_pUi->SetObjtype(CScene::OBJTYPE_UI);

	return m_pUi;
}
//=============================================================================
// 背景の初期化処理
//=============================================================================
HRESULT CCutIn::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// 背景の終了処理
//=============================================================================
void CCutIn::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 背景の更新処理
//=============================================================================
void CCutIn::Update(void)
{
	CScene2D::Update();
}
//=============================================================================
// 背景の描画処理
//=============================================================================
void CCutIn::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CCutIn::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, CUTINTEX_NORMAL, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, CUTINTEX_KIWAME, &m_pTexture[1]);

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CCutIn::UnLoad(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_CUTINTEX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
