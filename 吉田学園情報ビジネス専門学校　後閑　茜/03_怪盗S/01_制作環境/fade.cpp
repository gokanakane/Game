//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "fade.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureFade[MAX_FADETEX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	// 頂点バッファへのポインタ
FADE					g_fade;					// フェード状態
MODE					g_modeNext;				// 次のモード
D3DXCOLOR				g_colorFade;			// フェード色
int g_nCntAnimF;								//アニメーションカウンター
int g_nPatturnAnimF;							//アニメーションのパターン
bool g_bAnimF;									//アニメーションの使用状況
//=============================================================================
// 初期化処理
//=============================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//値の初期化
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_nCntAnimF = 0;
	g_nPatturnAnimF = 0;
	g_bAnimF = false;

	// 頂点情報の設定
	MakeVertexFade(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{
	for (int nCnt = 0; nCnt < MAX_FADETEX; nCnt++)
	{
		// テクスチャの開放
		if (g_pTextureFade[nCnt] != NULL)
		{
			g_pTextureFade[nCnt]->Release();
			g_pTextureFade[nCnt] = NULL;
		}

	}

	// 頂点バッファの開放
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)//フェードイン状態
		{
			g_colorFade.a -= 0.03f;
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;//何もしてない状態に
			}
		}

		else if (g_fade == FADE_OUT)//フェードアウト状態
		{
			g_colorFade.a += 0.03f;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;//フェードイン状態に

				//モードの設定
				SetMode(g_modeNext);
			}
		}

		g_nCntAnimF++;

		if (rand() % 50 == 0)
		{
			g_bAnimF = true;
		}
		if (g_bAnimF == true)
		{
			if (g_nCntAnimF % 4 == 0)
			{
				g_nPatturnAnimF++;
			}

			if (g_nPatturnAnimF >= MAX_ANIM)
			{
				g_nPatturnAnimF = 0;
				g_bAnimF = false;
			}
		}
		//頂点をロックして頂点データへのポインタを取得
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//フェード頂点カラーの更新
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);//三つ目の頂点の色指定（右回り）

		 //Now Loading頂点カラーの更新
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//一つ目の頂点の色指定（右回り）
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//二つ目の頂点の色指定（右回り）
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//三つ目の頂点の色指定（右回り）
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//三つ目の頂点の色指定（右回り）

		//猫頂点カラーの更新
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//一つ目の頂点の色指定（右回り）
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//二つ目の頂点の色指定（右回り）
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//三つ目の頂点の色指定（右回り）
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//三つ目の頂点の色指定（右回り）

		//猫テクスチャ座標の設定
		pVtx[8].tex = D3DXVECTOR2(g_nPatturnAnimF*0.25f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(g_nPatturnAnimF*0.25f + 0.25f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(g_nPatturnAnimF*0.25f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(g_nPatturnAnimF*0.25f + 0.25f, 1.0f);

		//頂点バッファのアンロック
		g_pVtxBuffFade->Unlock();

	}

}
//=============================================================================
// タイトル画面
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCnt = 0; nCnt < MAX_FADETEX; nCnt++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureFade[nCnt]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			NUM_POLYGON);

	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	D3DXCreateTextureFromFile(pDevice, LOAD_TEX, &g_pTextureFade[0]);
	D3DXCreateTextureFromFile(pDevice, LOAD_TEX1, &g_pTextureFade[1]);
	D3DXCreateTextureFromFile(pDevice, LOAD_TEX2, &g_pTextureFade[2]);


	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FADETEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//フェード-----------------------------------------------
	// 頂点バッファの情報を設定
	pVtx[0].pos = D3DXVECTOR3(VTX_POS_X, VTX_POS_Y, 0.0f);//一つ目の頂点の場所指定
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, VTX_POS_Y, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[2].pos = D3DXVECTOR3(VTX_POS_X, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	//頂点色
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//二つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	
	//Now Loading-----------------------------------------------
	// 頂点バッファの情報を設定
	pVtx[4].pos = D3DXVECTOR3(700, 600, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(1100, 600, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(700, SCREEN_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(1100, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//テクスチャ座標の設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点色
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//猫-----------------------------------------------
	// 頂点バッファの情報を設定
	pVtx[8].pos = D3DXVECTOR3(1100, 600, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH, 600, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(1100, SCREEN_HEIGHT, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	//テクスチャ座標の設定
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.25f, 1.0f);

	//頂点色
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffFade->Unlock();


}

//=============================================================================
// フェードの設定
//=============================================================================
void SetFade(MODE modeNext)
{
		g_fade = FADE_OUT;
		g_modeNext = modeNext;
		g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=============================================================================
// フェードの取得
//=============================================================================
FADE GetFade(void)
{
	return g_fade;
}

