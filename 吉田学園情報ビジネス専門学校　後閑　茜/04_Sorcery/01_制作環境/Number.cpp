//=============================================================================
//
// 数字処理 [Number.cpp]
// Author : 
//
//=============================================================================
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "number.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CNumber::CNumber() { m_pVtxBuff = NULL; }
//=============================================================================
// デストラクタ
//=============================================================================
CNumber::~CNumber() {}
//=============================================================================
// 数字の生成
//=============================================================================
CNumber *CNumber::Create()
{
	CNumber *pScene = NULL;
	if (pScene == NULL)
	{
		pScene = new CNumber;
		pScene->Init();
	}

	return pScene;
}

//=============================================================================
// 数字の初期化処理
//=============================================================================
HRESULT CNumber::Init(void)
{
	//デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = GetRenderer()->GetDevice();	/* あんまりよくない */
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);


	// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//数字の大きさの座標設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//数字の色設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 数字の終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
//=============================================================================
// 数字の更新処理
//=============================================================================
void CNumber::Update(void) {}

//=============================================================================
// 数字の描画処理
//=============================================================================
void CNumber::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// 数字の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
//=============================================================================
// テクスチャの設定
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + (nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (nNumber * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (nNumber * 0.1f), 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
// 位置の設定
//=============================================================================
void CNumber::SetPos(D3DXVECTOR3 pos, int nCnt,float SizeX,float SizeY)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定	
	pVtx[0].pos = D3DXVECTOR3(pos.x - SizeX + ((SizeX + 15.0f) * nCnt), pos.y - SizeY, 0.0f);//一つ目の頂点の場所指定
	pVtx[1].pos = D3DXVECTOR3(pos.x + SizeX + ((SizeX + 15.0f) * nCnt), pos.y - SizeY, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[2].pos = D3DXVECTOR3(pos.x - SizeX + ((SizeX + 15.0f) * nCnt), pos.y + SizeY, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[3].pos = D3DXVECTOR3(pos.x + SizeX + ((SizeX + 15.0f) * nCnt), pos.y + SizeY, 0.0f);//三つ目の頂点の場所指定（右回り）

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
// 色の設定
//=============================================================================
void CNumber::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定	
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b,col.a);//一つ目の頂点の場所指定
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b,col.a);//二つ目の頂点の場所指定（右回り）
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b,col.a);//三つ目の頂点の場所指定（右回り）
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b,col.a);//三つ目の頂点の場所指定（右回り）

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CNumber::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NUMBER, &m_pTexture);

	return S_OK;
}
//=============================================================================
// テクスチャのアンロード
//=============================================================================
void CNumber::UnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}