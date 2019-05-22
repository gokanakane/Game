//=============================================================================
//
// メイン処理 [scene2D.cpp]
// Author : 
//
//=============================================================================
#include "scene.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"
#include "Pause.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
//bool g_bBool = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_TexNum = 0;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_fAngle = 0.0f;
	m_fLenge = 0.0f;
}
//=============================================================================
// デストラクタ
//=============================================================================
CScene2D::~CScene2D() {}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScene2D::Init(void)
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

	
	// ポリゴンの位置を設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);


	// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの大きさの座標設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//ポリゴンの色設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//オブジェクト（自分自身）の破棄
	Release();
}
//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void) {}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	CScene::OBJTYPE type = CScene::GetObjtype();
	
	if (type == CScene::OBJTYPE_PAUSE)
	{
		bool bPause = CPause::GetPause();

		if (bPause == true)
		{
			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, m_pTexture);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				2);
		}
	}
	else
	{
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
	}
}
//=============================================================================
// 2Dポリゴンの生成
//=============================================================================
CScene2D *CScene2D::Create(void)
{
	CScene2D *pScene = NULL;
	if (pScene == NULL)
	{
		pScene = new CScene2D;
		pScene->Init();
	}

	return pScene;
}
//=============================================================================
// 2Dポリゴンの移動の設定
//=============================================================================
void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	m_pos = pos;

	// 頂点情報を設定
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの大きさの座標設定
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - m_fWidth), (m_pos.y - m_fHeight), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + m_fWidth), (m_pos.y - m_fHeight), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - m_fWidth), (m_pos.y + m_fHeight), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + m_fWidth), (m_pos.y + m_fHeight), 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 2Dポリゴンの移動の取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetPos(void)
{
	return m_pos;
}
//=============================================================================
// 2Dポリゴンの設定
//=============================================================================
void CScene2D::SetScene2D(D3DXVECTOR3 pos, float sizeW, float sizeH)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	m_pos = pos;
	m_fWidth = sizeW;
	m_fHeight = sizeH;

	// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの大きさの座標設定
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - m_fWidth), (m_pos.y - m_fHeight), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + m_fWidth), (m_pos.y - m_fHeight), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - m_fWidth), (m_pos.y + m_fHeight), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + m_fWidth), (m_pos.y + m_fHeight), 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
// 2Dポリゴンの設定（左を中心座標にする）
//=============================================================================
void CScene2D::SetScene2DLeftCenter(D3DXVECTOR3 pos, float sizeW, float sizeH)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	m_pos = pos;
	m_fWidth = sizeW;
	m_fHeight = sizeH;

	// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの大きさの座標設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, (m_pos.y - m_fHeight), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + m_fWidth), (m_pos.y - m_fHeight), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, (m_pos.y + m_fHeight), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + m_fWidth), (m_pos.y + m_fHeight), 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
// テクスチャの割り当て
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}
//=============================================================================
// テクスチャスクロールの処理
//=============================================================================
void CScene2D::SetScroll(int nCnt, float fSpeed)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの大きさの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (nCnt*(fSpeed + 1)), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + (nCnt*(fSpeed + 1)), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (nCnt*(fSpeed + 1)), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + (nCnt*(fSpeed + 1)), 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
// 透明度の設定
//=============================================================================
void CScene2D::SetAlpha(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの更新
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, col.a);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, col.a);//二つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, col.a);//三つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, col.a);//三つ目の頂点の色指定（右回り）

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 色の設定
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

					// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの更新
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);//二つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);//三つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);//三つ目の頂点の色指定（右回り）

	 //頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// テクスチャアニメーション(X区切り)
//=============================================================================
void CScene2D::SetAnimX(int MaxPattarnX,int MaxPattarnY, int nPattarn)
{//(X区切りでの最大パターン数,Y区切りでの最大パターン数,パターン)

	VERTEX_2D *pVtx;//頂点情報へのポインタ

					// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの更新
	pVtx[0].tex = D3DXVECTOR2((nPattarn % MaxPattarnX) * (1.0f / MaxPattarnX), (1.0f / MaxPattarnY));
	pVtx[1].tex = D3DXVECTOR2((nPattarn % MaxPattarnX) * (1.0f / MaxPattarnX) + (1.0f / MaxPattarnX), (1.0f / MaxPattarnY));
	pVtx[2].tex = D3DXVECTOR2((nPattarn % MaxPattarnX) * (1.0f / MaxPattarnX), (1.0f / MaxPattarnY) + (1.0f / MaxPattarnY));
	pVtx[3].tex = D3DXVECTOR2((nPattarn % MaxPattarnX) * (1.0f / MaxPattarnX) + (1.0f / MaxPattarnX), (1.0f / MaxPattarnY) + (1.0f / MaxPattarnY));

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
// テクスチャアニメーション(Y区切り)
//=============================================================================
void CScene2D::SetAnimY(int MaxPattarnX, int MaxPattarnY,int nPattarn)
{//(X区切りでの最大パターン数,Y区切りでの最大パターン数,パターン)

	VERTEX_2D *pVtx;//頂点情報へのポインタ

					// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの更新
	pVtx[0].tex = D3DXVECTOR2((1.0f / MaxPattarnX),(nPattarn % MaxPattarnY) * (1.0f / MaxPattarnY));
	pVtx[1].tex = D3DXVECTOR2((1.0f / MaxPattarnX) + (1.0f / MaxPattarnX),(nPattarn % MaxPattarnY) * (1.0f / MaxPattarnY));
	pVtx[2].tex = D3DXVECTOR2((1.0f / MaxPattarnX),(nPattarn % MaxPattarnY) * (1.0f / MaxPattarnY) + (1.0f / MaxPattarnY));
	pVtx[3].tex = D3DXVECTOR2((1.0f / MaxPattarnX) + (1.0f / MaxPattarnX),(nPattarn % MaxPattarnY) * (1.0f / MaxPattarnY) + (1.0f / MaxPattarnY));

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// テクスチャアニメーション(キャラ用)
//=============================================================================
void CScene2D::SetCharaAnim(int nPattarn,float TexsliceY)
{//(X区切りでの最大パターン数,Y区切りでの最大パターン数,パターン)

	VERTEX_2D *pVtx;//頂点情報へのポインタ

					// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの更新
	pVtx[0].tex = D3DXVECTOR2((nPattarn % 4) * (1.0f / 4), TexsliceY);
	pVtx[1].tex = D3DXVECTOR2((nPattarn % 4) * (1.0f / 4) + (1.0f / 4), TexsliceY);
	pVtx[2].tex = D3DXVECTOR2((nPattarn % 4) * (1.0f / 4), TexsliceY + (1.0f / 4));
	pVtx[3].tex = D3DXVECTOR2((nPattarn % 4) * (1.0f / 4) + (1.0f / 4), TexsliceY + (1.0f / 4));

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
// ポリゴンサイズ
//=============================================================================
void CScene2D::SetSize(float sizeW, float sizeH)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ


	// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの大きさの座標設定
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - sizeW), (m_pos.y - sizeH), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + sizeW), (m_pos.y - sizeH), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - sizeW), (m_pos.y + sizeH), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + sizeW), (m_pos.y + sizeH), 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
// ポリゴンの回転
//=============================================================================
void CScene2D::SetRotation(float sizeW, float sizeH,float Angle)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	m_fAngle += Angle;									//角度を設定
	m_fLenge = sqrtf(sizeW * sizeW + sizeH * sizeH);	//対角線の計算


	/* 角度修正	※半径を二倍して一周させる */
	if (m_fAngle < -D3DX_PI)
	{
		m_fAngle += D3DX_PI*2.0f;
	}
	if (m_fAngle > D3DX_PI)
	{
		m_fAngle -= D3DX_PI*2.0f;
	}

	// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの大きさの座標設定
	pVtx[0].pos = D3DXVECTOR3((m_pos.x + sinf(m_fAngle+D3DX_PI) * m_fLenge), (m_pos.y + cosf(m_fAngle+D3DX_PI) * m_fLenge), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + sinf(m_fAngle+D3DX_PI*0.5f) * m_fLenge), (m_pos.y + cosf(m_fAngle+D3DX_PI*0.5f) * m_fLenge), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((m_pos.x + sinf(m_fAngle+D3DX_PI*-0.5f) * m_fLenge), (m_pos.y + cosf(m_fAngle+D3DX_PI*-0.5f) * m_fLenge), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + sinf(m_fAngle) * m_fLenge), (m_pos.y + cosf(m_fAngle) * m_fLenge), 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}