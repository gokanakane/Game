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
#define RANKING_TEXTURE "data\\TEXTURE\\Ranking000.png" //ランキング文字
#define RANKING_TEXTURE0 "　" //背景
#define RANKING_TEXTURE1 "data\\TEXTURE\\Dot.png"		//ドット（スクロール）
#define RANKING_TEXTURE2 "data\\TEXTURE\\Ranking001.png"//順位
#define RANKING_TEXTURE3 "data\\TEXTURE\\Ranking002.png"//怪盗
#define RANKING_TEXTURE4 "data\\TEXTURE\\Ranking003.png"//ペンダント（アニメーション）
#define Ranking_POS_X (300)					   //タイトル左上X
#define Ranking_POS_Y (500)					   //タイトル左上Y
#define Ranking_WIDTH (SCREEN_WIDTH)			   //タイトルの幅
#define Ranking_HEIGHT (SCREEN_HEIGHT)		   //タイトル高さ
#define MAX_TEX (6)
#define MAX_ANIM (4)							//アニメーションパターン
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRanking[MAX_TEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;
int g_nAlphaRogo;
int g_nCntTitleRanking;			//フェード時間
int g_PatternAnimRank;
int g_CntAnimRank;
int g_nCntMoveTex;
//=============================================================================
// タイトル初期化処理[InitRanking]
//=============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	g_nCntTitleRanking = 0;
	g_PatternAnimRank = 0;
	g_CntAnimRank = 0;
	g_nCntMoveTex = 0;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE0, &g_pTextureRanking[0]);
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE1, &g_pTextureRanking[1]);
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE, &g_pTextureRanking[2]);
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE2, &g_pTextureRanking[3]);
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE4, &g_pTextureRanking[4]);
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE3, &g_pTextureRanking[5]);

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
	pVtx[0].col = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);//二つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);//三つ目の頂点の色指定（右回り）

													//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//---ドット-------------------------
	//座標設定
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一つ目の頂点の場所指定
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[6].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

																 //rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//色設定
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);//一つ目の頂点の色指定（右回り）
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);//二つ目の頂点の色指定（右回り）
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);//三つ目の頂点の色指定（右回り）
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);//三つ目の頂点の色指定（右回り）

													//テクスチャの設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//---RANKING-------------------------
		//座標設定
	pVtx[8].pos = D3DXVECTOR3(100.0f, 50, 0.0f);//一つ目の頂点の場所指定
	pVtx[9].pos = D3DXVECTOR3(600.0f, 50, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[10].pos = D3DXVECTOR3(100.0f, 150, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[11].pos = D3DXVECTOR3(600.0f, 150, 0.0f);//三つ目の頂点の場所指定（右回り）

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

	//---順位-------------------------
	//座標設定
	pVtx[12].pos = D3DXVECTOR3(0.0f, 180, 0.0f);//一つ目の頂点の場所指定
	pVtx[13].pos = D3DXVECTOR3(220.0f, 180, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[14].pos = D3DXVECTOR3(0.0f, 700, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[15].pos = D3DXVECTOR3(220.0f, 700, 0.0f);//三つ目の頂点の場所指定（右回り）

	//rhwの設定
	pVtx[12].rhw = 1.0f;
	pVtx[13].rhw = 1.0f;
	pVtx[14].rhw = 1.0f;
	pVtx[15].rhw = 1.0f;

	//色設定
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

	//テクスチャの設定
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);

	//---怪盗-------------------------
	//座標設定
	pVtx[16].pos = D3DXVECTOR3(700.0f, 0.0f, 0.0f);//一つ目の頂点の場所指定
	pVtx[17].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[18].pos = D3DXVECTOR3(700.0f, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[19].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

												  //rhwの設定
	pVtx[16].rhw = 1.0f;
	pVtx[17].rhw = 1.0f;
	pVtx[18].rhw = 1.0f;
	pVtx[19].rhw = 1.0f;

	//色設定
	pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
	pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

													 //テクスチャの設定
	pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);

	//---お宝-------------------------
	//座標設定
	pVtx[20].pos = D3DXVECTOR3(770.0f, 190.0f, 0.0f);//一つ目の頂点の場所指定
	pVtx[21].pos = D3DXVECTOR3(970.0f, 190.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[22].pos = D3DXVECTOR3(770.0f, 390.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[23].pos = D3DXVECTOR3(970.0f, 390.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

																  //rhwの設定
	pVtx[20].rhw = 1.0f;
	pVtx[21].rhw = 1.0f;
	pVtx[22].rhw = 1.0f;
	pVtx[23].rhw = 1.0f;

	//色設定
	pVtx[20].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[21].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
	pVtx[22].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	pVtx[23].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

													 //テクスチャの設定
	pVtx[20].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[21].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[22].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[23].tex = D3DXVECTOR2(0.25f, 1.0f);


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
	VERTEX_2D*pVtx;//頂点情報へのポインタ
	FADE g_fade;
	g_fade = GetFade();
	g_nCntTitleRanking++;
	g_CntAnimRank++;
	g_nCntMoveTex++;

	if (g_CntAnimRank % 17 == 0)
	{
		g_PatternAnimRank++;
	}
	if (g_PatternAnimRank >= MAX_ANIM)
	{
		g_PatternAnimRank = 0;
	}
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
	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[4].tex = D3DXVECTOR2(0.0f + (-g_nCntMoveTex*0.001f + 1), 0.0f);
	pVtx[5].tex = D3DXVECTOR2(5.0f + (-g_nCntMoveTex*0.001f + 1), 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f + (-g_nCntMoveTex*0.001f + 1), 5.0f);
	pVtx[7].tex = D3DXVECTOR2(5.0f + (-g_nCntMoveTex*0.001f + 1), 5.0f);

	//猫テクスチャ座標の設定
	pVtx[20].tex = D3DXVECTOR2(g_PatternAnimRank*0.25f, 0.0f);
	pVtx[21].tex = D3DXVECTOR2(g_PatternAnimRank*0.25f + 0.25f, 0.0f);
	pVtx[22].tex = D3DXVECTOR2(g_PatternAnimRank*0.25f, 1.0f);
	pVtx[23].tex = D3DXVECTOR2(g_PatternAnimRank*0.25f + 0.25f, 1.0f);

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
