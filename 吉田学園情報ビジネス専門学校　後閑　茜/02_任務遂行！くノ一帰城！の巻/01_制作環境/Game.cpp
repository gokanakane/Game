//=============================================================================
//
// ゲーム処理 [Game.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "Player.h"
#include "bg.h"
#include "Game.h"
#include "enemy.h"
#include "bow.h"
#include "score.h"
#include "fade.h"
#include "input.h"
#include "time.h"
#include "Item.h"
#include "Block.h"
#include "Pause.h"
#include "migawari.h"
#include "sound.h"
#include "Life.h"
#include "Door.h"
#include "Explosion.h"
#include "InterFase.h"
#include "mist.h"

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
	InitDoor();//ドアの初期化処理
	InitPlayer();//プレイヤーの初期化
	InitBlock();//ブロックの初期化
	InitItem();//アイテムの初期化
	InitEnemy();//敵の初期化処理
	InitBow(); //弓の初期化
	InitMigawari();//身代わりの初期化処理
	InitInterFase();//インターフェース初期化処理
	InitScore();//スコアの初期化
	InitLife();//ライフの初期化処理
	InitTime();//タイムの初期化
	InitExplosion();
	InitMist();
	InitPause();//ポーズの初期化処理
	
	

	//ブロックの設置

		SetBlock(D3DXVECTOR3(150.0f, 680.0f, 0.0f), 1000, 50.0f, 0, 0);

	//敵の足場（左）
		SetBlock(D3DXVECTOR3(0, 180.0f, 0.0f), 100, 50.0f, 2, 0);
		SetBlock(D3DXVECTOR3(0, 360.0f, 0.0f), 100, 50.0f, 2, 0);
		SetBlock(D3DXVECTOR3(0, 540.0f, 0.0f), 100, 50.0f, 2, 0);
	//敵の配置（左）
		SetEnemy(D3DXVECTOR3(40, 180.0f, 0.0f),1);
		SetEnemy(D3DXVECTOR3(40, 360.0f, 0.0f),1);
		SetEnemy(D3DXVECTOR3(40, 540.0f, 0.0f),1);

	//敵の足場（右）
		SetBlock(D3DXVECTOR3(1200, 180.0f, 0.0f), 100, 50.0f, 2, 0);
		SetBlock(D3DXVECTOR3(1200, 360.0f, 0.0f), 100, 50.0f, 2, 0);
		SetBlock(D3DXVECTOR3(1200, 540.0f, 0.0f), 100, 50.0f, 2, 0);
	//敵の足場（右）
		SetEnemy(D3DXVECTOR3(1240, 180.0f, 0.0f),0);
		SetEnemy(D3DXVECTOR3(1240, 360.0f, 0.0f), 0);
		SetEnemy(D3DXVECTOR3(1240, 540.0f, 0.0f), 0);

	//足場
		SetBlock(D3DXVECTOR3(570, 170, 0.0f), 100, 50.0f, 0, 0);//巻物
		SetBlock(D3DXVECTOR3(200, 500, 0.0f), 100, 50.0f, 0, 0);
		SetBlock(D3DXVECTOR3(950, 440, 0.0f), 100, 50.0f, 0, 0);
		SetBlock(D3DXVECTOR3(200, 150, 0.0f), 100, 50.0f, 0, 0);
		SetBlock(D3DXVECTOR3(700, 200, 0.0f), 100, 50.0f, 0, 0);
		SetBlock(D3DXVECTOR3(900, 280, 0.0f), 100, 50.0f, 1, -1);
		SetBlock(D3DXVECTOR3(300, 380, 0.0f), 100, 50.0f, 3, -1);

	//アイテムの設置
		SetItem(D3DXVECTOR3(620, 130, 0.0f),3);
		SetItem(D3DXVECTOR3(200, 470, 0.0f), rand()%3);
		SetItem(D3DXVECTOR3(250, 470, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(300, 470, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(210, 120, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(250, 120, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(290, 120, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(330, 200, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(330, 250, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(350, 300, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(970, 410, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(1000, 380, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(1040, 410, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(910, 500, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(910, 560, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(910, 620, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(850, 650, 0.0f), rand() % 3);

		//ドア
		SetDoor(D3DXVECTOR3(620, 680, 0));
}
//=============================================================================
//ゲーム終了処理 [UninitGame]
//=============================================================================
void UninitGame(void)
{
	UninitBG();//背景の終了処理
	UninitDoor();//ドアの終了処理
	UninitPlayer();//プレイヤーの終了処理
	UninitBlock();//ブロックの終了処理
	UninitItem();//アイテムの終了処理
	UninitEnemy();//敵の終了処理
	UninitBow();//弓の終了処理
	UninitMigawari();//身代わりの終了処理
	UninitInterFase();//インターフェースの終了処理
	UninitScore();//スコアの終了処理
	UninitLife();//ライフの終了処理
	UninitTime();//タイムの終了処理
	UninitExplosion();
	UninitMist();
	UninitPause();//ポーズの終了処理

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
			UpdateDoor();//ドアの更新処理
			UpdatePlayer();//プレイヤーの更新処理
			UpdateBlock();//ブロックの更新処理
			UpdateItem();//アイテムの更新処理
			UpdateEnemy();//敵の更新処理
			UpdateBow();//弓の更新処理
			UpdateMigawari();//身代わりの更新処理
			UpdateInterFase();//インターフェースの更新処理
			UpdateScore();//スコアの更新処理
			UpdateLife();//ライフの更新処理
			UpdateTime();//タイムの更新処理
			UpdateExplosion();
			UpdateMist();
		}
	else
	{
		UpdatePause();//ポーズの更新処理
	}
}
//=============================================================================
// ゲーム描写処理[DrawGame]
//=============================================================================
void DrawGame(void)
{
	DrawBG();//背景の描画処理
	DrawBlock();//ブロックの描画処理
	DrawDoor();//ドアの描画処理
	DrawPlayer();//プレイヤーの描画処理
	DrawEnemy();//敵の描画処理
	DrawBow();//弓の描画処理
	DrawItem();//アイテムの描画処理
	DrawMigawari();//身代わりの描画処理
	DrawInterFase();//インターフェースの描画処理
	DrawScore();//スコアの描画処理
	DrawLife();//ライフの描画処理
	DrawTime();//タイムの描画処理
	DrawExplosion();
	DrawMist();

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