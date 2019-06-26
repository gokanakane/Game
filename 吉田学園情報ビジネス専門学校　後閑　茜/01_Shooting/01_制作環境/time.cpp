//=============================================================================
//
// スコア処理 [Time.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "time.h"
#include "Game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TIME "data\\TEXTURE\\UI\\number000.png"	// 読み込むテクスチャファイル名
#define MAX_TIME (2)
#define TIME_RIMIT (60*30)									//制限時間

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// 頂点バッファへのポインタ
int g_nTime;										// 制限時間
int g_aTimeData[MAX_TIME];
TIMESTATE g_Timestate = TIMESTATE_NONE;				//タイムの状態

//=============================================================================
// 初期化処理
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// 制限時間の初期化
	g_nTime = TIME_RIMIT;
	AddTime();
	g_Timestate = TIMESTATE_NOMAL;

	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		g_aTimeData[nCnt] = 0;

	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_TIME,		// ファイルの名前
								&g_pTextureTime);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexTime(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTime(void)
{
	// テクスチャの開放
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTime(void)
{
	int nCnt;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	switch (g_Timestate)
	{
	case TIMESTATE_NOMAL:
		break;

	case TIMESTATE_END:
		g_nTime = 0;
		g_Timestate = TIMESTATE_NONE;
		SetGameState(GAMESTATE_OVER);
		break;
	}

	if (g_Timestate == TIMESTATE_NOMAL)
	{
		g_nTime--;

		if ((g_nTime % 60) == 0)
		{
			AddTime();

			//頂点をロックして頂点データへのポインタを取得
			g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

			for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aTimeData[nCnt] * 0.1f), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aTimeData[nCnt] * 0.1f), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aTimeData[nCnt] * 0.1f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aTimeData[nCnt] * 0.1f), 1.0f);

				//該当の位置まで進める
				pVtx += 4;
			}
			//頂点バッファのアンロック
			g_pVtxBuffTime->Unlock();
			if (g_nTime == 0)
			{
				g_Timestate = TIMESTATE_END;
			}

		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTime);

	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
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
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	int nCnt;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{		
		// 頂点情報を設定	
		pVtx[0].pos = D3DXVECTOR3(590.0f +(40 * nCnt), 5.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(640.0f +(40 * nCnt), 5.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(590.0f +(40 * nCnt), 75.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(640.0f +(40 * nCnt), 75.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

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

	//頂点バッファのアンロック
	g_pVtxBuffTime->Unlock();

}

//=============================================================================
// スコアの加算
//=============================================================================
void AddTime(void)
{
	int nCnt;
	int nNum = 100;
	int nNum1 = 10;
	int nTime;

	nTime = g_nTime/60 ;

	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		g_aTimeData[nCnt] = (nTime % nNum) / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}
