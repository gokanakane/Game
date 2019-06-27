//=============================================================================
//
// スコア処理 [Life.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "Life.h"
#include "Player.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		// 頂点バッファへのポインタ
int g_nLife;									   // ダメージカウンター
bool g_bUse[MAXPLAYER_LIFE];

//=============================================================================
// 初期化処理
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// スコアの初期化
	g_nLife = 0;

	for (nCnt = 0; nCnt < MAXPLAYER_LIFE; nCnt++)
	{
		g_bUse[nCnt] = true;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_LIFE,		// ファイルの名前
								&g_pTextureLife);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexLife(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLife(void)
{
	// テクスチャの開放
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLife(void)
{
	int nCnt;
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	
	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAXPLAYER_LIFE; nCnt++)
	{
		if (g_bUse[nCnt] == true)
		{
			// 頂点情報を設定	
			pVtx[0].pos = D3DXVECTOR3(0.0f + (50.0f * (MAXPLAYER_LIFE - nCnt - 1)), 0.0f, 0.0f);//一つ目の頂点の場所指定
			pVtx[1].pos = D3DXVECTOR3(50.0f + (50.0f * (MAXPLAYER_LIFE - nCnt - 1)), 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
			pVtx[2].pos = D3DXVECTOR3(0.0f + (50.0f * (MAXPLAYER_LIFE - nCnt - 1)), 50.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
			pVtx[3].pos = D3DXVECTOR3(50.0f + (50.0f * (MAXPLAYER_LIFE - nCnt - 1)), 50.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		}
		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffLife->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt <= MAXPLAYER_LIFE; nCnt++)
	{
		if (g_bUse[nCnt] == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureLife);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	int nCnt;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXPLAYER_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAXPLAYER_LIFE; nCnt++)
	{		
		// 頂点情報を設定	
		pVtx[0].pos = D3DXVECTOR3(0.0f +(50 * nCnt),0.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(50.0f +(50 * nCnt), 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(0.0f +(50 * nCnt), 50.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(50.0f +(50 * nCnt), 50.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点色
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffLife->Unlock();

}

//=============================================================================
// ライフの設定
//=============================================================================
void SetLife(int nLifeDown)
{
	int nLostLife = 0;
	int nCnt;

	nLostLife = MAXPLAYER_LIFE - nLifeDown;

	for (nCnt = 0; nCnt < nLostLife; nCnt++)
	{
		if (g_bUse[nCnt] == true)
		{
			g_bUse[nCnt] = false;
		}
	}

}
