//=============================================================================
//
// ゲーム処理 [Game.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "Player.h"
#include "bg.h"
#include "bullet.h"
#include "Explosion.h"
#include "enemy.h"
#include "Game.h"
#include "score.h"
#include "effect.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "Pause.h"
#include "time.h"
#include "Life.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
GAMESTATE g_GameState;	//ゲームの状態
int g_nCntGameState;	//状況管理カウンター
bool g_bPause;			//ポーズ中かどうか

//=============================================================================
// ゲーム初期化処理[InitGame]
//=============================================================================
void InitGame(void)
{
	g_GameState = GAMESTATE_NONE;//通常に設定
	g_nCntGameState = 0;
	g_bPause = false;

	InitBG();//背景の初期化処理
	InitEnemy();//敵の初期化処理
	InitEffect();//エフェクトの初期化処理
	InitBullet();//弾の初期化処理
	InitExplosion();//爆弾の初期化処理
	InitScore();//スコアの初期化処理
	InitPlayer();//プレイヤーの初期化処理
	InitPause();//ポーズの初期化処理
	InitTime();//制限時間の初期化
	InitLife();//ライフの初期化処理

//敵の配置
//最後列
	SetEnemy(D3DXVECTOR3(300, 100, 0.0f), 3, -1,10);//敵の設定[3]
	SetEnemy(D3DXVECTOR3(400, 100, 0.0f), 0, -1,2);//敵の設定[0]
	SetEnemy(D3DXVECTOR3(500, 100, 0.0f), 1, -1,3);//敵の設定[1]
	SetEnemy(D3DXVECTOR3(600, 100, 0.0f), 2, -1,4);//敵の設定[2]
	SetEnemy(D3DXVECTOR3(700, 100, 0.0f), 3, -1,8);//敵の設定[3]
	SetEnemy(D3DXVECTOR3(800, 100, 0.0f), 0, -1,2);//敵の設定[0]

//三列目
	SetEnemy(D3DXVECTOR3(400, 150, 0.0f), 3, 1,10);//敵の設定[3]
	SetEnemy(D3DXVECTOR3(500, 150, 0.0f), 2, 1,4);//敵の設定[2]
	SetEnemy(D3DXVECTOR3(600, 150, 0.0f), 1, 1,3);//敵の設定[1]
	SetEnemy(D3DXVECTOR3(700, 150, 0.0f), 0, 1,2);//敵の設定[0]
 //二列目
	SetEnemy(D3DXVECTOR3(400, 200, 0.0f), 0, -1,2);//敵の設定[0]
	SetEnemy(D3DXVECTOR3(500, 200, 0.0f), 1, -1,3);//敵の設定[1]
	SetEnemy(D3DXVECTOR3(600, 200, 0.0f), 2, -1,4);//敵の設定[2]
	SetEnemy(D3DXVECTOR3(700, 200, 0.0f), 3, -1,10);//敵の設定[3]
//一列目
	SetEnemy(D3DXVECTOR3(400, 250, 0.0f), 2, 1,10);//敵の設定[0]
	SetEnemy(D3DXVECTOR3(500, 250, 0.0f), 1, 1,4);//敵の設定[1]
	SetEnemy(D3DXVECTOR3(600, 250, 0.0f), 0, 1,3);//敵の設定[2]
	SetEnemy(D3DXVECTOR3(700, 250, 0.0f), 3, 1,2);//敵の設定[3]


}
//=============================================================================
//ゲーム終了処理 [UninitGame]
//=============================================================================
void UninitGame(void)
{
	UninitBG();//背景の終了処理
	UninitEnemy();//敵の終了処理
	UninitEffect();//エフェクトの終了処理
    UninitBullet();//弾の終了処理
	UninitExplosion();//爆弾の終了処理
	UninitScore();//スコアの終了処理
	UninitPlayer();//プレイヤーの終了処理
	UninitPause();//ポーズの終了処理
	UninitTime();//制限時間の終了処理
	UninitLife();//ライフの終了処理

}

//=============================================================================
// ゲーム更新処理[UpdataGame]
//=============================================================================
void UpdateGame(void)
{	
	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポーズON/OFF
		PlaySound(SOUND_LABEL_SE_PAUSE);
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		switch (g_GameState)
		{
		case GAMESTATE_NOMAL:
			break;

		case GAMESTATE_CLEAR:
			g_nCntGameState++;
			if (g_nCntGameState <= 60)
			{
				//g_GameState = GAMESTATE_NONE;
				//画面（モード）の設定
				SetFade(MODE_RESULT);
			}
			break;

		case GAMESTATE_OVER:
			g_nCntGameState++;
			if (g_nCntGameState <= 60)
			{
				//画面（モード）の設定
				SetFade(MODE_RESULT);
				//g_GameState = GAMESTATE_NONE;

			}
			break;


		}
		UpdateBG();//背景の更新処理
		UpdateEnemy();//敵の更新処理
		UpdateEffect();//エフェクトの更新処理
		UpdateBullet();//弾の更新処理
		UpdateExplosion();//爆弾の更新処理
		UpdateScore();//スコアの更新処理
		UpdatePlayer();//プレイヤーの更新処理
		UpdateTime();//制限時間の更新処理
		UpdateLife();//ライフの更新処理
	}
	else
	{
		UpdatePause();
	}

}
//=============================================================================
// ゲーム描写処理[DrawGame]
//=============================================================================
void DrawGame(void)
{
	DrawBG();//背景の描写処理
	DrawEnemy();//敵の描画処理
	DrawEffect();//エフェクトの描画処理
	DrawBullet();//弾の描画処理
	DrawExplosion();//爆弾の描画処理
	DrawScore();//スコアの描画処理
	DrawPlayer();//プレイヤーの描写処理
	DrawTime();//制限時間の描画処理
	DrawLife();//ライフの終了処理

	if (g_bPause == true)
	{
		DrawPause();
	}
}

//=============================================================================
// ゲームの設定処理[SetGame]
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_GameState = state;
	g_nCntGameState = 0;

}

//=============================================================================
// ゲームの取得処理[SetGame]
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_GameState;
}
//=============================================================================
// ポーズ状態の取得処理[SetGame]
//=============================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}