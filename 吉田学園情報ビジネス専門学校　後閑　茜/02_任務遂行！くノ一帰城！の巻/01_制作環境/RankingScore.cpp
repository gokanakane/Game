//=============================================================================
//
// ランキングスコア処理 [score.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "RankingScore.h"
#include "score.h"
#include "time.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RANKINGSCORE "data\\TEXTURE\\UI\\number001.png"	// 読み込むテクスチャファイル名
#define MAX_RANKINGSCORE (8)							    //スコアの桁数
#define MAX_RANKINGSCORE_HEIGTH (5)							//スコアの段数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRankingScore = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;		// 頂点バッファへのポインタ
int	g_nHighScore[MAX_RANKINGSCORE_HEIGTH];					// スコア
int	g_nScore2;
int g_nRankingScore;										// ソート用仮置きスコア
int g_aRankingScoreData[MAX_RANKINGSCORE_HEIGTH][MAX_RANKINGSCORE];// １桁に数字を格納する変数
bool bRank = true;

//=============================================================================
// 初期化処理
//=============================================================================
void InitRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_nRankingScore = 0;
	g_nScore2 = 0;

	for (int nRank = 0; nRank < MAX_RANKINGSCORE_HEIGTH; nRank++)
	{//順位
		for (int nCnt = 0; nCnt < MAX_RANKINGSCORE; nCnt++)
		{//桁
			g_aRankingScoreData[nRank][nCnt] = 0;
		}
	}

	if (bRank == true)
	{
		g_nHighScore[0] = 40000;
		g_nHighScore[1] = 35000;
		g_nHighScore[2] = 30000;
		g_nHighScore[3] = 20000;
		g_nHighScore[4] = 10000;

		bRank = false;
	}

	g_nScore2 = 0;
	g_nRankingScore = 0;

	//スコアの取得
	SetHighScore(GetScore());

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						 // デバイスへのポインタ
							TEXTURE_RANKINGSCORE,			// ファイルの名前
							&g_pTextureRankingScore);		// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexRankingScore(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRankingScore(void)
{
	// テクスチャの開放
	if (g_pTextureRankingScore != NULL)
	{
		g_pTextureRankingScore->Release();
		g_pTextureRankingScore = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffRankingScore != NULL)
	{
		g_pVtxBuffRankingScore->Release();
		g_pVtxBuffRankingScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRankingScore(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nRank = 0; nRank < MAX_RANKINGSCORE_HEIGTH; nRank++)
	{//順位
		for (int nCnt = 0; nCnt < MAX_RANKINGSCORE; nCnt++)
		{//桁
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aRankingScoreData[nRank][nCnt] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aRankingScoreData[nRank][nCnt] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aRankingScoreData[nRank][nCnt] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aRankingScoreData[nRank][nCnt] * 0.1f), 1.0f);

			//該当の位置まで進める
			pVtx += 4;
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffRankingScore->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffRankingScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankingScore);

	for (nCnt = 0; nCnt < MAX_RANKINGSCORE * MAX_RANKINGSCORE_HEIGTH; nCnt++)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt * 4,
			2);

	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice)
{
	int nCnt;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANKINGSCORE * MAX_RANKINGSCORE_HEIGTH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingScore,
		NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt1 = 0; nCnt1 < MAX_RANKINGSCORE_HEIGTH; nCnt1++)
	{//段
		for (nCnt = 0; nCnt < MAX_RANKINGSCORE; nCnt++)
		{//桁
			// 頂点情報を設定	
			pVtx[0].pos = D3DXVECTOR3(420.0f + (60 * nCnt), 180.0f + (110.0f * nCnt1), 0.0f);//一つ目の頂点の場所指定
			pVtx[1].pos = D3DXVECTOR3(480.0f + (60 * nCnt), 180.0f + (110.0f * nCnt1), 0.0f);//二つ目の頂点の場所指定（右回り）
			pVtx[2].pos = D3DXVECTOR3(420.0f + (60 * nCnt), 280.0f + (110.0f * nCnt1), 0.0f);//三つ目の頂点の場所指定（右回り）
			pVtx[3].pos = D3DXVECTOR3(480.0f + (60 * nCnt), 280.0f + (110.0f * nCnt1), 0.0f);//三つ目の頂点の場所指定（右回り）

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
	}

	//頂点バッファのアンロック
	g_pVtxBuffRankingScore->Unlock();

}

//=============================================================================
// スコアの加算
//=============================================================================
void SetHighScore(int nScore)
{
	int nCntNum;			//スコアの桁数のカウンター
	int nNum = 100000000;
	int nNum2 = 10000000;
	int nScore1 = 0;
	int pTime = GetTime();

	nScore1 = nScore*(pTime / 60);

	for (int nRank = 0; nRank < MAX_RANKINGSCORE_HEIGTH; nRank++)
	{//順位
		if (g_nHighScore[nRank] < nScore1)
		{
			g_nRankingScore = g_nHighScore[nRank];
			g_nHighScore[nRank] = nScore1;

			for (int nRankCnt = nRank + 1; nRankCnt < MAX_RANKINGSCORE_HEIGTH; nRankCnt++)
			{
				g_nScore2 = g_nHighScore[nRankCnt];
				g_nHighScore[nRankCnt] = g_nRankingScore;
				g_nRankingScore = g_nScore2;
			}
			break;
		}
	}

	for (int nRank = 0; nRank < MAX_RANKINGSCORE_HEIGTH; nRank++)
	{//順位
		for (nCntNum = 0; nCntNum < MAX_RANKINGSCORE; nCntNum++)
		{
			g_aRankingScoreData[nRank][nCntNum] = (g_nHighScore[nRank] % nNum) / nNum2;	//格納する数字を計算

			//桁数を１桁減らす
			nNum = nNum / 10;
			nNum2 = nNum2 / 10;

			if (nCntNum == MAX_RANKINGSCORE - 1)
			{//初期化する
				nNum = 100000000;
				nNum2 = 10000000;
			}
		}
	}
	//スコアの初期化
	InitScore();
}