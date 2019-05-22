//=============================================================================
//
// タイトル処理 [Title.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Title.h"
#include"input.h"
#include "fade.h"
#include"sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_TEXTUER "data\\TEXTURE\\BG01.png" //読み込むテクスチャ
#define TITLE_TEXTUER1 "data\\TEXTURE\\press_enter.png" //読み込むテクスチャ
#define TITLE_TEXTUER2 "data\\TEXTURE\\Title.png" //読み込むテクスチャ
#define TITLE_POS_X (0)					   //タイトル左上X
#define TITLE_POS_Y (0)					   //タイトル左上Y
#define TITLE_WIDTH (SCREEN_WIDTH)			   //タイトルの幅
#define TITLE_HEIGHT (SCREEN_HEIGHT)		   //タイトル高さ
#define MAX_TEX (3)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;

//=============================================================================
// タイトル初期化処理[InitTitle]
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTUER,&g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTUER1, &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTUER2, &g_pTextureTitle[2]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffTitle, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx,0);

		//タイトル背景の座標設定
		pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//タイトル背景色設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）

		//タイトル背景テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//-------------------------------------------------------
		//タイトルロゴの座標設定
		pVtx[4].pos = D3DXVECTOR3(TITLE_POS_X+400, 500, 0.0f);//一つ目の頂点の場所指定
		pVtx[5].pos = D3DXVECTOR3(TITLE_WIDTH-400, 500, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[6].pos = D3DXVECTOR3(TITLE_POS_X+400, TITLE_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[7].pos = D3DXVECTOR3(TITLE_WIDTH-400, TITLE_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

		//rhwの設定
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//タイトルロゴ色設定
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);//一つ目の頂点の色指定（右回り）
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);//二つ目の頂点の色指定（右回り）
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）

		//タイトルロゴテクスチャの設定
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

		//-------------------------------------------------------
		//タイトルロゴの座標設定
		pVtx[8].pos = D3DXVECTOR3(TITLE_POS_X+300 , 0.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[9].pos = D3DXVECTOR3(TITLE_WIDTH-300,0.0f , 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[10].pos = D3DXVECTOR3(TITLE_POS_X+300, 400.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[11].pos = D3DXVECTOR3(TITLE_WIDTH-300, 400.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

																		 //rhwの設定
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//タイトルロゴ色設定
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);//一つ目の頂点の色指定（右回り）
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);//二つ目の頂点の色指定（右回り）
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）

		//タイトルロゴテクスチャの設定
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);




	//頂点バッファのアンロック
	g_pVtxBuffTitle->Unlock();

}
//=============================================================================
//タイトル終了処理 [UninitTitle]
//=============================================================================
void UninitTitle(void)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}

	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}

//=============================================================================
// タイトル更新処理[UpdataTitle]
//=============================================================================
void UpdateTitle(void)
{
	FADE g_fade;
	g_fade = GetFade();

	//Enterキーが押された
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{			
		PlaySound(SOUND_LABEL_SE_DECIDE);

		if (g_fade != FADE_OUT)
		{
			//モード設定
			SetFade(MODE_TUTORIAL);
		}
	}
}
//=============================================================================
// タイトル描写処理[DrawTitle]
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;
	//デイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);

		//タイトルの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}

}