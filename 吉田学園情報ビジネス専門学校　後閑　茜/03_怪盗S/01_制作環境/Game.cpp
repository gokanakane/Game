//=============================================================================
//
// ゲーム処理 [Game.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "Game.h"
#include "Player.h"
#include "input.h"
#include "Pause.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "Wall.h"
#include "Stage.h"
#include "fade.h"
#include "Obj.h"
#include "time.h"
#include "bullet.h"
#include "explosion.h"
#include "score.h"
#include "Enemy.h"
#include "Item.h"
#include "DisPlay.h"
#include "ItemUI.h"
#include "ItemGetUI.h"
#include "sound.h"

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
	
	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	//メッシュフィールドの初期化処理
	InitStage();

	//影の初期化
	InitShadow();

	//弾の初期化
	InitBullet();

	//モデルの初期化
	InitObj();

	//ディスプレイモデルの初期化
	InitDisPlay();

	//アイテムの初期化
	InitItem();

	//プレイヤーの初期化処理
	InitPlayer();

	//敵の初期化処理
	InitEnemy();

	//メッシュウォールの初期化処理
	InitWall();

	//爆発の初期化
	InitExplosion();

	//タイムの初期化処理
	InitTime();

	//スコアの初期化処理
	InitScore();

	//アイテムUIの初期化
	InitItemUI();

	//アイテムの所得状況UIの初期化
	InitItemGetUI();

	//ポーズの初期化
	InitPause();

	//敵の設置
	SetEnemy(D3DXVECTOR3(430.0f, 0.0f, 10.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f), 1, 0);
	SetEnemy(D3DXVECTOR3(330.0f, 0.0f, -130.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f), 1,0);
	SetEnemy(D3DXVECTOR3(130.0f, 0.0f, -520.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f), 1, 0);

	//胸像
	SetObj(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),0);

	//アイテム
	//a
	SetDisPlay(D3DXVECTOR3(340.0f, 0.0f, -380.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(340.0f, 8.0f, -380.0f), 0);

	//b
	SetDisPlay(D3DXVECTOR3(280.0f, 0.0f, -120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
	SetItem(D3DXVECTOR3(280.0f, 8.0f, -120.0f), 1);

	//c
	SetDisPlay(D3DXVECTOR3(280.0f, 0.0f, -480.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
	SetItem(D3DXVECTOR3(280.0f, 8.0f, -480.0f), 2);

	//d
	SetDisPlay(D3DXVECTOR3(220.0f, 0.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetItem(D3DXVECTOR3(220.0f, 8.0f, 20.0f), 3);

	//鍵
	SetItem(D3DXVECTOR3(480.0f, 0.0f, -280.0f),4);

}
//=============================================================================
//ゲーム終了処理 [UninitGame]
//=============================================================================
void UninitGame(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	//メッシュフィールドの終了処理
	UninitStage();

	//影の終了処理
	UninitShadow();

	//弾の終了処理
	UninitBullet();

	//モデルの終了処理
	UninitObj();

	//ディスプレイモデルの終了処理
	UninitDisPlay();

	//アイテムの終了処理
	UninitItem();

	//プレイヤーの終了処理
	UninitPlayer();

	//敵の終了処理
	UninitEnemy();

	//メッシュウォールの終了処理
	UninitWall();

	//爆発の終了処理
	UninitExplosion();

	//タイムの終了処理
	UninitTime();

	//スコアの終了処理
	UninitScore();

	//アイテムUIの終了処理
	UninitItemUI();

	//アイテム所得状況の終了処理
	UninitItemGetUI();

	//ポーズの終了処理
	UninitPause();

}

//=============================================================================
// ゲーム更新処理[UpdataGame]
//=============================================================================
void UpdateGame(void)
{	
	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポーズON/OFF
		g_bPause = g_bPause ? false : true;
		PlaySound(SOUND_LABEL_SE_PAUSE);
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
				//画面（モード）の設定
				SetFade(MODE_RESULT);
				//g_GameState = GAMESTATE_NONE;
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
		
		if (g_GameState == GAMESTATE_NONE)
		{
			// カメラの更新処理
			UpdateCamera();

			// ライトの更新処理
			UpdateLight();

			//メッシュフィールドの更新処理
			UpdateStage();

			//影の更新処理
			UpdateShadow();

			//バレットの更新処理
			UpdateBullet();

			//モデルの更新処理
			UpdateObj();

			//ディスプレイモデルの更新処理
			UpdateDisPlay();

			//アイテムの更新処理
			UpdateItem();

			//プレイヤーの更新処理
			UpdatePlayer();

			//敵の更新処理
			UpdateEnemy();

			//メッシュウォールの更新処理
			UpdateWall();

			//爆発の更新処理
			UpdateExplosion();

			//タイムの更新処理
			UpdateTime();

			//スコアの更新処理
			UpdateScore();

			//アイテムUIの更新処理
			UpdateItemUI();

			//アイテム取得状況の更新処理
			UpdateItemGetUI();
		}

	}
	else
	{
		UpdatePause();//ポーズの更新処理
	}

	//if (GetKeyboardPress(DIK_H) == true)
	//{//クリアデバックキー
	//	SetGameState(GAMESTATE_CLEAR);
	//}
	//if (GetKeyboardPress(DIK_F) == true)
	//{//オーバーデバックキー
	//	SetGameState(GAMESTATE_OVER);
	//}

}
//=============================================================================
// ゲーム描写処理[DrawGame]
//=============================================================================
void DrawGame(void)
{
	// カメラの設定
	SetCamera();

	//メッシュフィールドの描画処理
	DrawStage();

	//影の描画処理
	DrawShadow();

	//弾の描画処理
	DrawBullet();

	//モデルの描画処理
	DrawObj();

	//ディスプレイモデルの描画処理
	DrawDisPlay();
	
	//アイテムの描画処理
	DrawItem();

	//プレイヤーの描画処理
	DrawPlayer();

	//敵の描画処理
	DrawEnemy();

	//メッシュウォールの描画処理
	DrawWall();

	//爆発の描画処理
	DrawExplosion();

	//タイムの更新処理
	DrawTime();

	//スコアの描画処理
	DrawScore();

	//アイテムUIの描画処理
	DrawItemUI();

	//アイテムの取得状況の描画処理
	DrawItemGetUI();

	if (g_bPause == true)
	{
		DrawPause();//ポーズの描画処理
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