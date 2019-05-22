//**************************************************************
//
//				背景の処理[bg.h]
//				Auther : Shun Yokomichi
//
//**************************************************************
#include "scene3d.h"
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "game.h"
#include "player.h"

//**************************************************************
//				マクロ定義
//**************************************************************
#define BG_TEXTURENAME000	"data/TEXTURE/game/BG001.jpg"			//読み込むテクスチャ000

//**************************************************************
//				静的メンバ変数
//**************************************************************
LPDIRECT3DTEXTURE9 CBg::m_pTexture = NULL;

//**************************************************************
//				背景の生成
//**************************************************************
CBg *CBg::Create()
{
	CBg *pBg = NULL;	// ポインタの生成

	// シーンの生成
	if (pBg == NULL)
	{
		pBg = new CBg;
		if (pBg != NULL)
		{
			pBg->Init();
		}
	}

	return pBg;
}

//**************************************************************
//				読み込むテクスチャ
//**************************************************************
HRESULT CBg::Load(void)
{
	// デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	CManager::MODE pMode = CManager::GetMode();				// モードの取得

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME000, &m_pTexture);
	
	return S_OK;
}

//**************************************************************
//				開放するテクスチャ
//**************************************************************
void CBg::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	
}

//**************************************************************
//		コンストラクタ
//**************************************************************
CBg::CBg() : CScene(PRIORITY_BG, OBJTYPE_BG)
{
	// デフォルト値
	m_mvoetex_x = 0.0f;
}

//**************************************************************
//		デストラクタ
//**************************************************************
CBg::~CBg()
{

}

//**************************************************************
//		初期化処理
//**************************************************************
HRESULT CBg::Init(void)
{
	CManager::MODE pMode = CManager::GetMode();

	m_pScene = new CScene3D(PRIORITY_BG, OBJTYPE_BG);
	if (m_pScene != NULL)
	{
		m_pScene->SetInitAll(D3DXVECTOR3(0.0f, 300.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1000.0f, 300.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CScene3D::SCENE3DTYPE_BILLBOARD);		// 初期値設定
		m_pScene->Init();
		m_pScene->BindTexture(m_pTexture);
	}

	return S_OK;
}

//**************************************************************
//		終了処理
//**************************************************************
void CBg::Uninit(void)
{
	if (m_pScene != NULL)
	{	// NULLじゃない場合
		m_pScene->Uninit();
		m_pScene = NULL;
	}
	

	CScene::SetDeath();		// 死亡フラグ
}

//**************************************************************
//		更新処理
//**************************************************************
void CBg::Update(void)
{
	CManager::MODE pMode = CManager::GetMode();	

	if (pMode == CManager::MODE_TITLE)
	{
		m_mvoetex_x += 0.0008f;

		m_pScene->Setpos(D3DXVECTOR3(CManager::GetCamera()->GetPosVDest().x, m_pScene->Getpos().y, m_pScene->Getpos().z));
		m_pScene->SetTex(1, 0, D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(m_mvoetex_x, 0.0f));
	}
	else if (pMode == CManager::MODE_GAME)
	{
		if (CManager::GetCamera()->GetPosVDest().x - 2.0f <= CGame::GetPlayer()->Getpos().x)
		{
				m_mvoetex_x += 0.0004f;
		}
	
		m_pScene->Setpos(D3DXVECTOR3(CManager::GetCamera()->GetPosVDest().x, m_pScene->Getpos().y, m_pScene->Getpos().z));
		m_pScene->SetTex(1, 0, D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(m_mvoetex_x, 0.0f));
	}
}

//**************************************************************
//		描画処理
//**************************************************************
void CBg::Draw(void)
{
	m_pScene->Draw();
}