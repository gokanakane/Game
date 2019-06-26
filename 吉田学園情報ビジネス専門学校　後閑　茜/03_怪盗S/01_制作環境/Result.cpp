//=============================================================================
//
// リザルト処理 [Result.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT_TEXTUER "data\\TEXTURE\\Result\\GameClear001.png" //読み込むテクスチャ
#define RESULT_OVER "data\\TEXTURE\\Object\\Wall008.png" //読み込むテクスチャ
#define RESULT_TEXTUER1 "data\\TEXTURE\\Result\\GameClear000.png" //読み込むテクスチャ
#define RESULT_TEXTUER2 "data\\TEXTURE\\Result\\gameover000.png" //読み込むテクスチャ
#define RESULT_CLIAR "data\\TEXTURE\\BG\\GameClear002.png" //読み込むテクスチャ

#define RESULT_POS_X (0)					   //リザルト左上X
#define RESULT_POS_Y (0)					   //リザルト左上Y
#define RESULT_WIDTH (SCREEN_WIDTH)			   //リザルトの幅
#define RESULT_HEIGHT (SCREEN_HEIGHT)		   //リザルト高さ
#define MAX_OVER_TEX (2)					   //テクスチャの最大数
#define MAX_CLIAR_TEX (3)					   //ゲームクリアのテクスチャ
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_CLIAR_TEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
int g_nCntAnim;
int g_nPatternAnim;
int g_nTimeRisult;
bool bAnimR;

//=============================================================================
// リザルト初期化処理[InitPolygon]
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	GAMESTATE pGame;
	pGame = GetGameState();

	g_nCntAnim = 0;
	g_nPatternAnim = 0;
	g_nTimeRisult = 0;
	bAnimR = false;


	if (pGame == GAMESTATE_CLEAR)
	{//ゲームクリアだったら
		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, RESULT_CLIAR, &g_pTextureResult[0]);
		D3DXCreateTextureFromFile(pDevice, RESULT_TEXTUER, &g_pTextureResult[1]);
		D3DXCreateTextureFromFile(pDevice, RESULT_TEXTUER1, &g_pTextureResult[2]);

	}
	else if (pGame == GAMESTATE_OVER)
	{
		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice, RESULT_OVER, &g_pTextureResult[0]);
		D3DXCreateTextureFromFile(pDevice, RESULT_TEXTUER2, &g_pTextureResult[1]);

	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_CLIAR_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);


	//-----------リザルト文字------------
	if (pGame == GAMESTATE_OVER)
	{
		//リザルト背景の座標設定
		pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

																	 //rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//リザルト背景色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

														//リザルト背景テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//リザルトの座標設定
		pVtx[4].pos = D3DXVECTOR3(150.0f, 100.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[5].pos = D3DXVECTOR3(1100.0f, 100.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[6].pos = D3DXVECTOR3(150.0f, 400.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[7].pos = D3DXVECTOR3(1100.0f, 400.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

		//rhwの設定
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//リザルト色設定
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

		//リザルトテクスチャの設定
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	}

	if (pGame == GAMESTATE_CLEAR)
	{//ゲームクリアだったら
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(0.0f, RESULT_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

																	 //rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//リザルト背景色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

														//リザルト背景テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	 //リザルト背景の座標設定
		pVtx[4].pos = D3DXVECTOR3(500.0f, 200.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[5].pos = D3DXVECTOR3(RESULT_WIDTH, 200.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[6].pos = D3DXVECTOR3(500.0f, RESULT_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[7].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

																	 //rhwの設定
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//リザルト背景色設定
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

														//リザルト背景テクスチャの設定
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.25f, 1.0f);

	 //リザルトの座標設定
		pVtx[8].pos = D3DXVECTOR3(0, 0, 0.0f);//一つ目の頂点の場所指定
		pVtx[9].pos = D3DXVECTOR3(780, 0, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[10].pos = D3DXVECTOR3(0, 280, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[11].pos = D3DXVECTOR3(780, 280, 0.0f);//三つ目の頂点の場所指定（右回り）

		 //rhwの設定
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//リザルト色設定
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

		//リザルトテクスチャの設定
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

	}

	//頂点バッファのアンロック
	g_pVtxBuffResult->Unlock();

}
//=============================================================================
//リザルト終了処理 [UninitPolygon]
//=============================================================================
void UninitResult(void)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_CLIAR_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureResult[nCnt] != NULL)
		{
			g_pTextureResult[nCnt]->Release();
			g_pTextureResult[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

}

//=============================================================================
// リザルト更新処理[UpdataPolygon]
//=============================================================================
void UpdateResult(void)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ
	FADE g_fade = GetFade();
	GAMESTATE pGame = GetGameState();
	g_nTimeRisult++;

	if (pGame == GAMESTATE_CLEAR)
	{
		if (rand() % 50 == 0)
		{
			bAnimR = true;
		}
		if (bAnimR == true)
		{
			g_nCntAnim++;
			if (g_nCntAnim % 7 == 0)
			{
				g_nPatternAnim++;

			}
			if (g_nPatternAnim == 4)
			{
				g_nPatternAnim = 0;
				bAnimR = false;
			}
		}
		//頂点をロックして頂点データへのポインタを取得
		g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

		//リザルト背景テクスチャの設定
		pVtx[4].tex = D3DXVECTOR2(g_nPatternAnim*0.25f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(g_nPatternAnim*0.25f + 0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(g_nPatternAnim*0.25f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(g_nPatternAnim*0.25f + 0.25f, 1.0f);

		//頂点バッファのアンロック
		g_pVtxBuffResult->Unlock();


	}

	//Enterキーが押された
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFade(MODE_RANKING);
		}
	}
	if (g_nTimeRisult > 600)
	{
		if (g_fade != FADE_OUT)
		{
			//モード設定
			SetFade(MODE_RANKING);
		}

	}

}
//=============================================================================
// リザルト描写処理[DrawPolygon]
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;

	GAMESTATE pGame;
	pGame = GetGameState();

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	if (pGame == GAMESTATE_CLEAR)
	{
		for (nCnt = 0; nCnt < MAX_CLIAR_TEX; nCnt++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureResult[nCnt]);

			//リザルトの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);

		}

	}

	else
	{
		for (nCnt = 0; nCnt < MAX_OVER_TEX; nCnt++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureResult[nCnt]);

			//リザルトの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);

		}
	}
}