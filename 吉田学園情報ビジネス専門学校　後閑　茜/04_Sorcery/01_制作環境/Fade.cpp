//=============================================================================
//
// フェード処理 [fade.h]
// Author : Akane Gokan
//
//=============================================================================
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CFade::m_pTexture = NULL;
CFade::FADEMODE CFade::m_fade = CFade::FADE_NONE;
CManager::MODE CFade::m_modeNext = CManager::MODE_TITLE;
D3DXCOLOR CFade::m_colFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
LPDIRECT3DVERTEXBUFFER9 CFade::m_pVtxBuff = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CFade::CFade() : CScene(7)
{
	m_fade = FADE_NONE;
	m_modeNext = CManager::MODE_MAX;
	m_colFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);			//黒い画面

	m_pScene2D = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade() {}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFade::Init(void)
{
	VERTEX_2D * pVtx;
	LPDIRECT3DDEVICE9 pDevice = NULL;
	CRenderer *pRenderer = CManager::GetRenderer();

	CScene::SetObjtype(CScene::OBJTYPE_FADE);
	CFade::m_fade = FADE_IN;
	CFade::m_modeNext = CManager::MODE_TITLE;
	CFade::m_colFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);			//黒い画面

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの座標設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//ポリゴンの色設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	if (m_pScene2D == NULL)
	{
		m_pScene2D = new CScene2D;
		m_pScene2D->Init();
		m_pScene2D->BindTexture(m_pTexture);
		m_pScene2D->SetScene2D(D3DXVECTOR3(980.0f, 650.0f, 0.0f), 300.0f, 50.0f);
		m_pScene2D->SetObjtype(CScene::OBJTYPE_FADE);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFade::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D * pVtx;			//頂点情報へのポインタ

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{	//フェードイン状態
			m_colFade.a -= 0.03f;				//画面を透明にする
			if (m_colFade.a <= 0.0f)
			{
				m_colFade.a = 0.0f;
				m_fade = FADE_NONE;			//何もしていない状態にする
			}
		}
		else if (m_fade == FADE_OUT)
		{	//フェードアウト状態
			m_colFade.a += 0.03f;				//画面を不透明にする
			if (m_colFade.a >= 1.0f)
			{
				m_colFade.a = 1.0f;
				m_fade = FADE_IN;					//フェードイン状態

				//モードの設定
				CManager::SetMode(m_modeNext);
			}
		}

		//頂点バッファをロックし、頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//ポリゴンの色設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colFade.a);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colFade.a);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colFade.a);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colFade.a);

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}

	if (m_pScene2D != NULL)
	{
		m_pScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_colFade.a));
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;							//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();		//レンダリングクラスの取得

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
							0,
							2);
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Draw();
	}

}
//=============================================================================
// フェードの設定
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_colFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CFade::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	D3DXCreateTextureFromFile(pDevice, FADETEXTURE_NOWLOADING, &m_pTexture);
	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CFade::UnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}