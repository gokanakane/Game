//=============================================================================
//
// タイトル背景処理 [Ranking.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Ranking.h"
#include "RankingScore.h"
#include"input.h"
#include "fade.h"
#include"sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RANKING_TEXTURE "data\\TEXTURE\\UI\\Ranking000.png" //ランキング文字
#define RANKING_TEXTURE0 "data\\TEXTURE\\BG\\Sky001.jpg"	//背景
#define RANKING_TEXTURE2 "data\\TEXTURE\\UI\\Ranking001.png"//順位
#define Ranking_POS_X (300)									//タイトル左上X
#define Ranking_POS_Y (500)									//タイトル左上Y
#define Ranking_WIDTH (SCREEN_WIDTH)						//タイトルの幅
#define Ranking_HEIGHT (SCREEN_HEIGHT)						//タイトル高さ
#define MAX_TEX (3)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRanking[MAX_TEX] = {};//テクスチャへのポインタjpg
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;
int g_nAlphaRogo;
int g_nCntTitleRanking;			//フェード時間
int g_nCntMoveTex;
//=============================================================================
// タイトル初期化処理[InitRanking]
//=============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	g_nCntTitleRanking = 0;
	g_nCntMoveTex = 0;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE0, &g_pTextureRanking[0]);
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE, &g_pTextureRanking[1]);
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE2, &g_pTextureRanking[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//---背景-------------------------
	//座標設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一つ目の頂点の場所指定
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

	  //rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//色設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

													//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//---RANKING-------------------------
		//座標設定
	pVtx[4].pos = D3DXVECTOR3(300.0f, 50.0f, 0.0f);//一つ目の頂点の場所指定
	pVtx[5].pos = D3DXVECTOR3(1000.0f, 50.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[6].pos = D3DXVECTOR3(300.0f, 150.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[7].pos = D3DXVECTOR3(1000.0f, 150.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

	//rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//色設定
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

	//テクスチャの設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//---順位-------------------------
	//座標設定
	pVtx[8].pos = D3DXVECTOR3(200.0f, 180.0f, 0.0f);//一つ目の頂点の場所指定
	pVtx[9].pos = D3DXVECTOR3(400.0f, 180.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[10].pos = D3DXVECTOR3(200.0f, 700.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[11].pos = D3DXVECTOR3(400.0f, 700.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

	//rhwの設定
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	//色設定
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

	//テクスチャの設定
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffRanking->Unlock();

	InitRankingScore();
}
//=============================================================================
//タイトル終了処理 [UninitRanking]
//=============================================================================
void UninitRanking(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{	//テクスチャの破棄
		if (g_pTextureRanking[nCnt] != NULL)
		{
			g_pTextureRanking[nCnt]->Release();
			g_pTextureRanking[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	UninitRankingScore();
}

//=============================================================================
// タイトル更新処理[UpdataRanking]
//=============================================================================
void UpdateRanking(void)
{
	FADE g_fade;
	g_fade = GetFade();
	g_nCntTitleRanking++;
	g_nCntMoveTex++;
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//Enter入力でタイトル戻る
		if (g_fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード変更
			SetFade(MODE_TITLE);
		}
	}

	if (g_nCntTitleRanking > 600)
	{//時間経過でタイトルに戻る
		if (g_fade != FADE_OUT)
		{
			SetFade(MODE_TITLE);
		}
	}

	UpdateRankingScore();

	//頂点バッファのアンロック
	g_pVtxBuffRanking->Unlock();


}
//=============================================================================
// タイトル描写処理[DrawRanking]
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{	
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRanking[nCnt]);

		//タイトルの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}
	DrawRankingScore();
}
