//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "bg.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
//bool g_bBool = false;
LPDIRECT3DTEXTURE9 CBg::m_pTexture[MAX_TEXTURE] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CBg::CBg():CScene(1)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}
	m_nCntBG = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CBg::~CBg() {}
//=============================================================================
// 背景の生成
//=============================================================================
CBg *CBg::Create(void)
{
	CBg *pBg = NULL;

	if (pBg == NULL)
	{
		pBg = new CBg;
		pBg->Init();
	}

	//オブジェクトの種類の設定
	pBg->SetObjtype(CScene::OBJTYPE_BG);

	return pBg;
}
//=============================================================================
// 背景の初期化処理
//=============================================================================
HRESULT CBg::Init(void)
{
	CManager::MODE mode = CManager::GetMode();

	switch (mode)
	{
	case CManager::MODE_TITLE:
		//背景1枚目
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		break;

	case CManager::MODE_STAGESELECT:
		//背景1枚目
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		break;

	case CManager::MODE_CHARACTORSELECT:
		//背景1枚目
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		break;


	case CManager::MODE_TUTORIAL:
		//背景1枚目
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		
		m_apScene2D[1] = new CScene2D(1);
		m_apScene2D[1]->Init();
		m_apScene2D[1]->BindTexture(m_pTexture[1]);
		m_apScene2D[1]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), SCREEN_WIDTH / 2, 300);
		break;

	case CManager::MODE_GAME:
		//背景1枚目
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

		//背景2枚目
		m_apScene2D[1] = new CScene2D(1);
		m_apScene2D[1]->Init();
		m_apScene2D[1]->BindTexture(m_pTexture[1]);
		m_apScene2D[1]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		m_apScene2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		break;
		
	case CManager::MODE_CLEAR:
		//背景1枚目
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		break;

	case CManager::MODE_OVER:
		//背景1枚目
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		break;

	case CManager::MODE_RANKING:
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		break;
	}

	return S_OK;
}

//=============================================================================
// 背景の終了処理
//=============================================================================
void CBg::Uninit(void)
{
	//m_apScene2Dを破棄（ポリゴンが破棄されただけでbg自体は破棄されていない）
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
		}
	}

	//bgを破棄
	Release();
}
//=============================================================================
// 背景の更新処理
//=============================================================================
void CBg::Update(void)
{
	m_nCntBG++;
	CManager::MODE mode = CManager::GetMode();

	switch (mode)
	{
	case CManager::MODE_TITLE:
		break;

	case CManager::MODE_STAGESELECT:
		break;

	case CManager::MODE_CHARACTORSELECT:
		break;

	case CManager::MODE_TUTORIAL:
		m_apScene2D[0]->SetScroll(m_nCntBG, 0.001f);
		m_apScene2D[1]->SetScroll(m_nCntBG, 0.0015f);
		break;

	case CManager::MODE_GAME:
		m_apScene2D[0]->SetScroll(m_nCntBG, 0.001f);
		m_apScene2D[1]->SetScroll(m_nCntBG, 0.002f);
		break;

	case CManager::MODE_CLEAR:
		break;

	case CManager::MODE_OVER:
		break;

	case CManager::MODE_RANKING:
		break;
	}
}
//=============================================================================
// 背景の描画処理
//=============================================================================
void CBg::Draw(void)
{

}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CBg::Load(void)
{
	CManager::MODE mode = CManager::GetMode();
	CManager::StageSelectState select = CManager::GetStageSelect();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	switch (mode)
	{
	case CManager::MODE_TITLE:
		// テクスチャの生成
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE, &m_pTexture[0]);
		break;

	case CManager::MODE_STAGESELECT:
		// テクスチャの生成
		D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGESELECT, &m_pTexture[0]);
		break;

	case CManager::MODE_CHARACTORSELECT:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CHARACTERSELECT, &m_pTexture[0]);
		break;

	case CManager::MODE_TUTORIAL:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTORIAL, &m_pTexture[0]);
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTORIAL_SCROLL, &m_pTexture[1]);
		break;

	case CManager::MODE_GAME:
		switch (select)
		{
		case CManager::STAGESELECT_STAGE1:
			D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGE1, &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_RAIN, &m_pTexture[1]);
			break;

		case CManager::STAGESELECT_STAGE2:
			D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGE2, &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_SMOKE, &m_pTexture[1]);
			break;

		case CManager::STAGESELECT_STAGE3:
			D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGE3, &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_SMOKE, &m_pTexture[1]);
			break;

		case CManager::STAGESELECT_STAGE4:
			D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGE4, &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_SMOKE, &m_pTexture[1]);
			break;
		}
		break;

	case CManager::MODE_CLEAR:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULT, &m_pTexture[0]);
		break;

	case CManager::MODE_OVER:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULT, &m_pTexture[0]);
		break;

	case CManager::MODE_RANKING:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING, &m_pTexture[0]);
		break;
	}

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CBg::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}