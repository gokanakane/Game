//=============================================================================
//
// プレイヤー処理 [Player.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "Game.h"
#include "Player.h"
#include "input.h"
#include "Block.h"
#include "Item.h"
#include "Door.h"
#include "bow.h"
#include "migawari.h"
#include "Life.h"
#include "score.h"


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;
Player g_Player;
//=============================================================================
// プレイヤー初期化処理[InitPlayer]
//=============================================================================
void InitPlayer(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3(500, 620, 0.0f);
	g_Player.posold = D3DXVECTOR3(0, 0, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nLife = MAXPLAYER_LIFE;
	g_Player.nPatternAnim = 0;
	g_Player.nCntAnim = 0;
	g_Player.nCntState = 0;
	g_Player.nDirectionMove = 0;
	g_Player.CntColor = 0;
	g_Player.ChengeColor = 0;
	g_Player.bJump = false;
	g_Player.bDisp = true;
	g_Player.bWalk = false;
	g_Player.state = PLAYERSTATE_NOMAL;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTUER, &g_pTexturePlayer);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer, NULL);


	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);


	//プレイヤーの大きさの座標設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//プレイヤーの色設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//一つ目の頂点の色指定（右回り）
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);//二つ目の頂点の色指定（右回り）
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//頂点バッファのアンロック
	g_pVtxBuffPlayer->Unlock();

}

//=============================================================================
//プレイヤー終了処理 [UninitPolygon]
//=============================================================================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================
// プレイヤー更新処理[UpdataPolygon]
//=============================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	switch (g_Player.state)
	{
	case PLAYERSTATE_APPEAR:
		break;
	case PLAYERSTATE_NOMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		g_Player.nCntState--;
		if (g_Player.nCntState <= 0)
		{
			g_Player.state = PLAYERSTATE_NOMAL;
			//頂点をロックして頂点データへのポインタを取得
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

		//頂点バッファのアンロック
			g_pVtxBuffPlayer->Unlock();
		}
		break;

	case PLAYERSTEAT_DEATH:
		SetGameState(GAMESTATE_OVER);
		g_Player.state = PLAYERSTATE_NOMAL;
		break;
	}

	g_Player.nCntAnim++; //アニメーションカウンターの加算
	g_Player.posold = g_Player.pos; //前回の位置を保存

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Player.bDisp == true)
	{
		//左に動かす
		if (GetKeyboardPress(DIK_A) == true)
		{//Dを押した
			g_Player.bWalk = true;
			g_Player.nDirectionMove = 1;
			g_Player.move.x -= PLAYER_MOVE;

			if ((g_Player.nCntAnim % 8) == 0)
			{//一定時間が経過
			 //パターンを更新
				g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % PLAYER_PATTERN;

				pVtx[0].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.75f);
				pVtx[3].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.75f);

				if (g_Player.nPatternAnim %PLAYER_PATTERN == 0)
				{
					g_Player.nPatternAnim = 0;
				}
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Dを押した
			g_Player.bWalk = true;
			g_Player.nDirectionMove = 0;
			g_Player.move.x += PLAYER_MOVE;

			if ((g_Player.nCntAnim % 8) == 0)
			{//一定時間が経過
				//パターンを更新
				g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % PLAYER_PATTERN;

				pVtx[0].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.75f);
				pVtx[1].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.75f);
				pVtx[2].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 1.0f);

				if (g_Player.nPatternAnim %PLAYER_PATTERN == 0)
				{
					g_Player.nPatternAnim = 0;
				}
			}
		}
		else
		{
			g_Player.bWalk = false;
		}

		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{//ジャンプ
			if (g_Player.bJump == false)
			{//空中ジャンプ防止
				g_Player.move.y = -45.0f;
				g_Player.move.x += 0.1f;
				g_Player.bJump = true;
			}
		}

		if (GetKeyboardTrigger(DIK_W) == true)
		{//身代わり設置

			if (rand() % 100 == 0)
			{
				SetMigawari(g_Player.pos, 1);
			}
			else
			{
				SetMigawari(g_Player.pos, 0);
			}
		}

		g_Player.move.y += 3.5;//重力加算

		if (g_Player.pos.y > SCREEN_HEIGHT)
		{//穴に落ちた
			g_Player.state = PLAYERSTEAT_DEATH;
			g_Player.bDisp = false;
		}

		//位置の更新
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		//減速
		g_Player.move.x += (0.0f - g_Player.move.x);

		//移動ループ(X軸)
		if (g_Player.pos.x < 0.0f)
		{//右端まで行った
			g_Player.pos.x = SCREEN_WIDTH;
		}

		else if (g_Player.pos.x > SCREEN_WIDTH)
		{//左端まで行った
			g_Player.pos.x = 0;
		}

		if (g_Player.bWalk == false)
		{
			if (g_Player.nDirectionMove == 0)
			{//右向きの静止アニメ
				if ((g_Player.nCntAnim % 8) == 0)
				{//一定時間が経過

				 //パターンを更新
					g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % PLAYER_PATTERN;

					pVtx[0].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.25f);
					pVtx[1].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.25f);
					pVtx[2].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.5f);
					pVtx[3].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.5f);
					if (g_Player.nPatternAnim % PLAYER_PATTERN == 0)
					{
						g_Player.nPatternAnim = 0;
					}
				}

			}
			else if (g_Player.nDirectionMove == 1)
			{//左向きの静止アニメ
				if ((g_Player.nCntAnim % 8) == 0)
				{//一定時間が経過
				 //パターンを更新
					g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % PLAYER_PATTERN;

					pVtx[0].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.25f);
					pVtx[3].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.25f);

					if (g_Player.nPatternAnim % PLAYER_PATTERN == 0)
					{
						g_Player.nPatternAnim = 0;
					}
				}
			}
		}

		//ジャンプアニメーション
		if (g_Player.bJump == true)
		{
			if (g_Player.nDirectionMove == 0)
			{//右向き
				pVtx[0].tex = D3DXVECTOR2(0.25f, 0.75f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.75f);
				pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

			}
			else if (g_Player.nDirectionMove == 1)
			{//左向き
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.75f);
				pVtx[3].tex = D3DXVECTOR2(0.25f, 0.75f);
			}
		}


		//ブロックのあたり判定
		if (CollisionBlock(&g_Player.pos, &g_Player.posold, &g_Player.move) == true)
		{
			g_Player.bJump = false;
		}
		else
		{
			if (g_Player.bJump == false)
			{
				g_Player.bJump = true;
			}
		}

		CollsionItem(&g_Player.pos);
		CollisionDoor(&g_Player.pos);
	}

	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - 50, g_Player.pos.y - 100, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + 50, g_Player.pos.y - 100, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - 50, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + 50, g_Player.pos.y, 0.0f);

	//頂点バッファのアンロック
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// プレイヤー描写処理[DrawPolygon]
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	if (g_Player.bDisp == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
	}

}

//=============================================================================
// プレイヤーのダメージ処理
//=============================================================================
void HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;
	SetLife(g_Player.nLife);

	if (g_Player.nLife == 0)
	{
		g_Player.state = PLAYERSTEAT_DEATH;
		g_Player.nCntState = 60;
		g_Player.bDisp = false;

	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCntState = 5;//ダメージ状態の時間

		VERTEX_2D *pVtx;// 頂点情報の作成
						
		//頂点バッファをロック
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//三つ目の頂点の色指定（右回り）

		// 頂点バッファをアンロックする
		g_pVtxBuffPlayer->Unlock();

	}

}

//=============================================================================
// プレイヤーの取得[GetPlayer]
//=============================================================================
Player*GetPlayer(void)
{
	return &g_Player;
}
