//=============================================================================
//
// 背景処理 [tutorial.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "main.h"
#include "tutorial.h"
#include "fade.h"
#include "input.h"
#include "bg.h"
#include "Player.h"
#include "Block.h"
#include "Item.h"
#include "Door.h"
#include "TutorialBG.h"
#include "Explosion.h"
#include "migawari.h"
#include "enemy.h"
#include "bow.h"
#include "sound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// ポリゴン初期化処理[InitPolygon]
//=============================================================================
void InitTutorial(void)
{
	InitBG();//背景の初期化処理
	InitDoor();//ドアの初期化処理
	InitBlock();//ブロックの初期化
	InitItem();//アイテムの初期化
	InitEnemy();//敵の初期化処理
	InitBow(); //弓の初期化
	InitPlayer();//プレイヤーの初期化
	InitMigawari();//身代わりの初期化処理
	InitTutorialBG();
	InitExplosion();
	
	SetBlock(D3DXVECTOR3(-100, 680.0f, 0.0f), 1500, 50.0f, 0, 0);

	SetBlock(D3DXVECTOR3(730, 450, 0.0f), 80, 50.0f, 0, 0);//巻物の足場
	SetBlock(D3DXVECTOR3(0, 400, 0.0f), 80, 50.0f, 2, 0);//敵の足場
	SetBlock(D3DXVECTOR3(500, 450, 0.0f), 80, 50.0f, 1, 1);
	SetBlock(D3DXVECTOR3(300, 500, 0.0f), 80, 50.0f, 3, 1);

	SetEnemy(D3DXVECTOR3(25, 400, 0.0f), 1);
	SetItem(D3DXVECTOR3(750, 420, 0.0f), 3);
	SetItem(D3DXVECTOR3(300, 650, 0.0f), 0);
	SetItem(D3DXVECTOR3(400, 650, 0.0f), 1);
	SetItem(D3DXVECTOR3(300, 480, 0.0f), 2);
	SetItem(D3DXVECTOR3(600, 650, 0.0f), 2);

	SetDoor(D3DXVECTOR3(1100, 680, 0));

}
//=============================================================================
//ポリゴン終了処理 [UninitPolygon]
//=============================================================================
void UninitTutorial(void)
{
	UninitBG();//背景の終了処理
	UninitDoor();//ドアの終了処理
	UninitPlayer();//プレイヤーの終了処理
	UninitBlock();//ブロックの終了処理
	UninitItem();//アイテムの終了処理
	UninitEnemy();//敵の終了処理
	UninitBow();//弓の終了処理
	UninitMigawari();//身代わりの終了処理
	UninitTutorialBG();
	UninitExplosion();

}

//=============================================================================
// ポリゴン更新処理[UpdataPolygon]
//=============================================================================
void UpdateTutorial(void)
{
	FADE g_fade;
	g_fade = GetFade();
	Player*pPlayer;
	pPlayer = GetPlayer();

	UpdateBG();//背景の描画処理
	UpdateBlock();//ブロックの描画処理
	UpdateDoor();//ドアの描画処理
	UpdatePlayer();//プレイヤーの描画処理
	UpdateEnemy();//敵の描画処理
	UpdateBow();//弓の描画処理
	UpdateItem();//アイテムの描画処理
	UpdateMigawari();//身代わりの描画処理
	UpdateTutorialBG();
	UpdateExplosion();

	//Enterキーが押された
	if (CollisionDoor(&pPlayer->pos) == true)
	{
		if (g_fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFade(MODE_GAME);
		}
	}

}
//=============================================================================
// ポリゴン描写処理[DrawPolygon]
//=============================================================================
void DrawTutorial(void)
{
	DrawBG();//背景の描画処理
	DrawBlock();//ブロックの描画処理
	DrawDoor();//ドアの描画処理
	DrawPlayer();//プレイヤーの描画処理
	DrawEnemy();//敵の描画処理
	DrawBow();//弓の描画処理
	DrawItem();//アイテムの描画処理
	DrawMigawari();//身代わりの描画処理
	DrawTutorialBG();
	DrawExplosion();
}