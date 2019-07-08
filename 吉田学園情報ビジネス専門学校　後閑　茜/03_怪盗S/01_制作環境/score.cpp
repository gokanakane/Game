//=============================================================================
//
// スコア処理 [score.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore[MAX_SCORETEX] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// 頂点バッファへのポインタ
int g_nScore;										// スコア
int g_aScoreData[MAX_SCORE];

//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;
	// スコアの初期化
	g_nScore = 0;

	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		g_aScoreData[nCnt] = 0;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_SCORE,		// ファイルの名前
								&g_pTextureScore[0]);	// テクスチャへのポインタ
													// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_SCORE1,		// ファイルの名前
		&g_pTextureScore[1]);	// テクスチャへのポインタ


	// 頂点情報の作成
	MakeVertexScore(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORETEX; nCnt++)
	{
		// テクスチャの開放
		if (g_pTextureScore[nCnt] != NULL)
		{
			g_pTextureScore[nCnt]->Release();
			g_pTextureScore[nCnt] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	int nCnt;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aScoreData[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aScoreData[nCnt] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aScoreData[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aScoreData[nCnt] * 0.1f), 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffScore->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_SCORE+1; nCnt++)
	{
		if (nCnt < MAX_SCORE)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureScore[0]);
		}
		else
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureScore[1]);

		}
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt * 4,
			2);
	}

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	int nCnt;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_SCORE+1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{		
		// 頂点情報を設定	
		pVtx[0].pos = D3DXVECTOR3(900.0f +(45 * nCnt), 0.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(950.0f +(45 * nCnt), 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(900.0f +(45 * nCnt), 50.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(950.0f +(45 * nCnt), 50.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}
	// 頂点情報を設定	
	pVtx[0].pos = D3DXVECTOR3(750.0f, 0.0f, 0.0f);//一つ目の頂点の場所指定
	pVtx[1].pos = D3DXVECTOR3(900.0f, 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[2].pos = D3DXVECTOR3(750.0f, 50.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[3].pos = D3DXVECTOR3(900.0f, 50.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

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


	//頂点バッファのアンロック
	g_pVtxBuffScore->Unlock();

}

//=============================================================================
// スコアの加算
//=============================================================================
void AddScore(int nValue)
{
	int nCnt;
	int nNum = 100000000;
	int nNum1 = 10000000;

	g_nScore += nValue;

	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		g_aScoreData[nCnt] = g_nScore % nNum / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}
//=============================================================================
// スコアの取得
//=============================================================================
int GetScore(void)
{
	return g_nScore;
}
