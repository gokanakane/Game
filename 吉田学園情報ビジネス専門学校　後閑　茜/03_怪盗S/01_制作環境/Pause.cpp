//=============================================================================
//
// ポーズ処理 [Pause.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "Pause.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEX (5)											 //テクスチャの数
#define PAUSECONRINUE_TEXTUER  "data\\TEXTURE\\Pause\\Continue.png"//読み込むテクスチャ
#define PAUSERETRY_TEXTUER  "data\\TEXTURE\\Pause\\Retry.png"		//読み込むテクスチャ
#define PAUSEQUIT_TEXTUER  "data\\TEXTURE\\Pause\\Quit.png"		//読み込むテクスチャ
#define PAUSE_TEXTUER "data\\TEXTURE\\Tutorial\\Tutorial001.png"			//読み込むテクスチャ
#define PAUSEMASK_TEXTURE " "
#define PAUSEBG_POS_X (630)								  //ポーズ背景左上X
#define PAUSEBG_POS_Y (180)								   //ポーズ背景左上Y
#define PAUSEBG_WIDTH (990)									//ポーズ背景の幅
#define PAUSEBG_HEIGHT (580)								    //ポーズ背景高さ
#define PASUSE_WIDTH (110.0f)								//ロゴの間隔
#define MAX_MENU (3)										//選択肢の数
#define MAX_ANIMATION (4)									//アニメーションパターン
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexPause(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_TEX] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;
PAUSESTATE g_PauseMode;
COLORSTATE g_PauseColor;
Pause g_Pause;
int g_nSelectManu;

//=============================================================================
// ポーズ初期化処理[InitPolygon]
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	g_nSelectManu = 0;
	g_PauseMode = PAUSESTATE_NONE;
	g_PauseColor = PAUSESTATECOLOR_NONE;

	g_Pause.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Pause.CntMove = 0.0f;
	g_Pause.ChengeMove = 0.1f;
	g_Pause.PatturnAnim = 0;
	g_Pause.CntAnim = 0;
	g_Pause.bAnim = false;

	MakeVertexPause(pDevice);


}
//=============================================================================
//ポーズ終了処理 [UninitPolygon]
//=============================================================================
void UninitPause(void)
{	
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTexturePause[nCnt] != NULL)
		{
			g_pTexturePause[nCnt]->Release();
			g_pTexturePause[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

}

//=============================================================================
// ポーズ更新処理[UpdataPolygon]
//=============================================================================
void UpdatePause(void)
{
	FADE g_Fade;
	g_Fade = GetFade();
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	g_Pause.CntAnim++;

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	if (rand() % 100 == 0)
	{
		g_Pause.bAnim = true;
	}

	if (g_Pause.bAnim == true)
	{
		if (g_Pause.CntAnim % 4 == 0)
		{
			g_Pause.PatturnAnim++;
		}

		//ねこテクスチャの設定
		pVtx[4].tex = D3DXVECTOR2(g_Pause.PatturnAnim*0.25f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(g_Pause.PatturnAnim*0.25f + 0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(g_Pause.PatturnAnim*0.25f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(g_Pause.PatturnAnim*0.25f + 0.25f, 1.0f);

		if (g_Pause.PatturnAnim >= MAX_ANIMATION)
		{
			g_Pause.PatturnAnim = 0;
			g_Pause.bAnim = false;
		}
	}

	//セレクト
	if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectManu = (g_nSelectManu + 1) % 3;
	}

	if (GetKeyboardTrigger(DIK_UP) == true)
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectManu = (g_nSelectManu + 2) % 3;
	}

	
	//メニュー選択後の処理
	if (g_nSelectManu == 0)
	{
		//色管理
		g_PauseColor = PAUSESTATECOLOR_CONTINUE;

		//選択肢のアニメーションaa
		if (g_Pause.CntMove >= 1 || g_Pause.CntMove <= -1)
		{
			g_Pause.ChengeMove *= -1.0f;//折り返し
		}

		g_Pause.CntMove += g_Pause.ChengeMove;
		g_Pause.pos.y += g_Pause.CntMove;


		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				g_PauseMode = PAUSESTATE_CONTINUE;
			}
		}
	}
	
	if (g_nSelectManu == 1)
	{
		//色管理
		g_PauseColor = PAUSESTATECOLOR_RETRY;

		//選択肢のアニメーション
		if (g_Pause.CntMove >= 1 || g_Pause.CntMove <= -1)
		{
			g_Pause.ChengeMove *= -1.0f;//折り返し
		}

		g_Pause.CntMove += g_Pause.ChengeMove;
		g_Pause.pos.y += g_Pause.CntMove;


		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				g_PauseMode = PAUSESTATE_RETRY;
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}
	}

	if (g_nSelectManu == 2)
	{
		//色管理
		g_PauseColor = PAUSESTATECOLOR_QUIT;

		//選択肢のアニメーションaa
		if (g_Pause.CntMove >= 1 || g_Pause.CntMove <= -1)
		{
			g_Pause.ChengeMove *= -1.0f;//折り返し
		}

		g_Pause.CntMove += g_Pause.ChengeMove;
		g_Pause.pos.y += g_Pause.CntMove;


		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				g_PauseMode = PAUSESTATE_QUIT;
			}
		}
	}

	switch (g_PauseColor)
	{
	case PAUSESTATECOLOR_NONE:
		break;

	case PAUSESTATECOLOR_CONTINUE:
		//背景色設定(Continue選択中)------------------------------------
		//Continue
		pVtx[8].pos = D3DXVECTOR3(380.0f, 150.0f + g_Pause.pos.y, 0.0f);//一つ目の頂点の場所指定
		pVtx[9].pos = D3DXVECTOR3(660.0f, 150.0f + g_Pause.pos.y, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[10].pos = D3DXVECTOR3(380.0f, 270.0f + g_Pause.pos.y, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[11].pos = D3DXVECTOR3(660.0f, 270.0f + g_Pause.pos.y, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//Retry
		pVtx[12].pos = D3DXVECTOR3(380.0f, 300.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[13].pos = D3DXVECTOR3(660.0f, 300.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[14].pos = D3DXVECTOR3(380.0f, 420.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[15].pos = D3DXVECTOR3(660.0f, 420.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		//Quit
		pVtx[16].pos = D3DXVECTOR3(380.0f, 450.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[17].pos = D3DXVECTOR3(660.0f, 450.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[18].pos = D3DXVECTOR3(380.0f, 570.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[19].pos = D3DXVECTOR3(660.0f, 570.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		break;

	case PAUSESTATECOLOR_RETRY:
		//背景色設定(Retry選択中)------------------------------------
		//Continue
		pVtx[8].pos = D3DXVECTOR3(380.0f, 150.0f,0.0f);//一つ目の頂点の場所指定
		pVtx[9].pos = D3DXVECTOR3(660.0f, 150.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[10].pos = D3DXVECTOR3(380.0f, 270.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[11].pos = D3DXVECTOR3(660.0f, 270.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		//Retry
		pVtx[12].pos = D3DXVECTOR3(380.0f, 300.0f + g_Pause.pos.y, 0.0f);//一つ目の頂点の場所指定
		pVtx[13].pos = D3DXVECTOR3(660.0f, 300.0f + g_Pause.pos.y, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[14].pos = D3DXVECTOR3(380.0f, 420.0f + g_Pause.pos.y, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[15].pos = D3DXVECTOR3(660.0f, 420.0f + g_Pause.pos.y, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//Quit
		pVtx[16].pos = D3DXVECTOR3(380.0f, 450.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[17].pos = D3DXVECTOR3(660.0f, 450.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[18].pos = D3DXVECTOR3(380.0f, 570.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[19].pos = D3DXVECTOR3(660.0f, 570.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		break;


	case PAUSESTATECOLOR_QUIT:
		//背景色設定(Quit選択中)------------------------------------
		//Continue
		pVtx[8].pos = D3DXVECTOR3(380.0f, 150.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[9].pos = D3DXVECTOR3(660.0f, 150.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[10].pos = D3DXVECTOR3(380.0f, 270.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[11].pos = D3DXVECTOR3(660.0f, 270.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		//Retry
		pVtx[12].pos = D3DXVECTOR3(380.0f, 300.0f, 0.0f);//一つ目の頂点の場所指定
		pVtx[13].pos = D3DXVECTOR3(660.0f, 300.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[14].pos = D3DXVECTOR3(380.0f, 420.0f, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[15].pos = D3DXVECTOR3(660.0f, 420.0f, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		//Quit
		pVtx[16].pos = D3DXVECTOR3(380.0f, 450.0f + g_Pause.pos.y, 0.0f);//一つ目の頂点の場所指定
		pVtx[17].pos = D3DXVECTOR3(660.0f, 450.0f + g_Pause.pos.y, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[18].pos = D3DXVECTOR3(380.0f, 570.0f + g_Pause.pos.y, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[19].pos = D3DXVECTOR3(660.0f, 570.0f + g_Pause.pos.y, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		break;
	}
	//頂点バッファのアンロック
	g_pVtxBuffPause->Unlock();


	switch (g_PauseMode)
	{
	case PAUSESTATE_CONTINUE:
		g_PauseMode = PAUSESTATE_NONE;
		SetPause(false);
		break;

	case PAUSESTATE_RETRY:
		g_PauseMode = PAUSESTATE_NONE;
		SetFade(MODE_GAME);
		break;

	case PAUSESTATE_QUIT:
		g_PauseMode = PAUSESTATE_NONE;
		SetFade(MODE_TITLE);
		break;	

	}

}
//=============================================================================
// ポーズ描写処理[DrawPolygon]
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePause[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexPause(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, PAUSEMASK_TEXTURE, &g_pTexturePause[0]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTUER, &g_pTexturePause[1]);
	D3DXCreateTextureFromFile(pDevice, PAUSECONRINUE_TEXTUER, &g_pTexturePause[2]);
	D3DXCreateTextureFromFile(pDevice, PAUSERETRY_TEXTUER, &g_pTexturePause[3]);
	D3DXCreateTextureFromFile(pDevice, PAUSEQUIT_TEXTUER, &g_pTexturePause[4]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause, NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//----------マスク-----------
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一つ目の頂点の場所指定
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

																 //rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//ポーズ背景色設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//一つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//一つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//一つ目の頂点の色指定（右回り）

													//ポーズ背景テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//猫背景の座標設定
	pVtx[4].pos = D3DXVECTOR3(PAUSEBG_POS_X, PAUSEBG_POS_Y, 0.0f);//一つ目の頂点の場所指定
	pVtx[5].pos = D3DXVECTOR3(PAUSEBG_WIDTH, PAUSEBG_POS_Y, 0.0f);//二つ目の頂点の場所指定（右回り）
	pVtx[6].pos = D3DXVECTOR3(PAUSEBG_POS_X, PAUSEBG_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）
	pVtx[7].pos = D3DXVECTOR3(PAUSEBG_WIDTH, PAUSEBG_HEIGHT, 0.0f);//三つ目の頂点の場所指定（右回り）

																   //rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//ポーズ背景色設定
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）

													//ポーズ背景テクスチャの設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.25f, 1.0f);

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//コンテニュー座標設定
		pVtx[8].pos = D3DXVECTOR3(380, 150 + (150.0f * nCnt), 0.0f);//一つ目の頂点の場所指定
		pVtx[9].pos = D3DXVECTOR3(660, 150 + (150.0f * nCnt), 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[10].pos = D3DXVECTOR3(380, 270 + (150.0f * nCnt), 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[11].pos = D3DXVECTOR3(660, 270 + (150.0f * nCnt), 0.0f);//三つ目の頂点の場所指定（右回り）

		 //rhwの設定
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//背景色設定
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）

														 //背景テクスチャの設定
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

	}
	//頂点バッファのアンロック
	g_pVtxBuffPause->Unlock();


}