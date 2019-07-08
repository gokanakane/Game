//=============================================================================
//
// プレイヤー処理 [Player.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "sound.h"
#include "Game.h"
#include "Player.h"
#include "bullet.h"
#include "Explosion.h"
#include "Life.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
VERTEX_2D g_aVetex[4];						//頂点情報を格納する
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;
int g_nCntAnim;								//アニメーションカウンター
int g_nPatternAnim;							//アニメーションパターンNO
Player g_Player;

//=============================================================================
// プレイヤー初期化処理[InitPlayer]
//=============================================================================
void InitPlayer(void)
{	
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//カウンターとパターンNoを初期化
	g_nCntAnim = 0;
	g_nPatternAnim = 0;

	g_Player.pos = D3DXVECTOR3(600, 600, 0.0f);	//プレイヤーの位置
	g_Player.move = D3DXVECTOR3(0, 0, 0.0f);
	g_Player.bDisp = true;
	g_Player.nCntState = 0;
	g_Player.state = PLAYERSTATE_NOMAL;
	g_Player.nLife = MAXPLAYER_LIFE;


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
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - 25, g_Player.pos.y - 25, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + 25, g_Player.pos.y - 25, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - 25, g_Player.pos.y + 25, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + 25, g_Player.pos.y + 25, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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
		g_Player.nCntState--;
		return;
		break;

	}

	//g_nCntAnim++;//カウンターの加算

	//if ((g_nCntAnim % POLYGON_CNTANIM) == 0)//一定時間が経過
	//{
	//	g_nPatternAnim = (g_nPatternAnim + 1) % POLYGON_PATTERN;		//パターンを更新
	//}

	//g_posPolygon += g_movePolygon;


	//左に動かす
	if (GetKeyboardPress(DIK_A) == true)
	{	//任意のキー（A）を押されたか
		if (GetKeyboardPress(DIK_W) == true)
		{	//任意のキー（W）を押されたか
			//加速
			g_Player.move.x += sinf(-D3DX_PI * 0.75f)* PLAYER_MOVE;
			g_Player.move.y += cosf(-D3DX_PI * 0.75f)* PLAYER_MOVE;
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{	//任意のキー（S）を押されたか

			//加速
			g_Player.move.x += sinf(-D3DX_PI * 0.25)* PLAYER_MOVE;
			g_Player.move.y += cosf(-D3DX_PI * 0.25)* PLAYER_MOVE;
		}

		else
		{//Aだけが押された
			//加速
			g_Player.move.x += sinf(D3DX_PI * -0.5)* PLAYER_MOVE;
			g_Player.move.y += cosf(D3DX_PI * -0.5)* PLAYER_MOVE;

		}
	}

	//右に動かす
	else if (GetKeyboardPress(DIK_D) == true)
	{	//任意のキー（D）を押されたか

		if (GetKeyboardPress(DIK_W) == true)
		{	//任意のキー（W）を押されたか
			//加速
			g_Player.move.x += sinf(D3DX_PI*0.75f)* PLAYER_MOVE;
			g_Player.move.y += cosf(D3DX_PI*0.75f)* PLAYER_MOVE;

		}

		else if (GetKeyboardPress(DIK_S) == true)
		{	//任意のキー（S）を押されたか
			//加速
			g_Player.move.x += sinf(D3DX_PI * 0.25)* PLAYER_MOVE;
			g_Player.move.y += cosf(D3DX_PI * 0.25)* PLAYER_MOVE;
		}

		else
		{//Dのみ押された
			//加速
			g_Player.move.x += sinf(D3DX_PI *0.5)* PLAYER_MOVE;
			g_Player.move.y += cosf(D3DX_PI *0.5)* PLAYER_MOVE;
		}
	}

	//上に動かす
	else if (GetKeyboardPress(DIK_W) == true)
	{	//任意のキー（W）を押されたか
		//加速
		g_Player.move.x += sinf(D3DX_PI)* PLAYER_MOVE;
		g_Player.move.y += cosf(D3DX_PI)* PLAYER_MOVE;

	}


	//下に動く
	else if (GetKeyboardPress(DIK_S) == true)
	{//任意のキー（S）を押されたか
		//加速
		g_Player.move.x -= sinf(D3DX_PI)* PLAYER_MOVE;
		g_Player.move.y -= cosf(D3DX_PI)* PLAYER_MOVE;

	}
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -7.0f, 0.0f), BULLETTYPE_PLAYER,60);
		SetBullet(g_Player.pos, D3DXVECTOR3(2.0f, -5.0f, 0.0f), BULLETTYPE_PLAYER,60);
		SetBullet(g_Player.pos, D3DXVECTOR3(-2.0f, -5.0f, 0.0f), BULLETTYPE_PLAYER,60);

	}

	//位置の更新
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;

	//移動範囲(X軸)
	if (g_Player.pos.x <= 25)
	{
		g_Player.pos.x = 25;
	}
	else if (g_Player.pos.x + 25 >= SCREEN_WIDTH)
	{
		g_Player.pos.x = SCREEN_WIDTH - 25;
	}
	//移動範囲(Y軸)
	if (g_Player.pos.y <= 25)
	{
		g_Player.pos.y = 25;
	}
	else if (g_Player.pos.y + 25 >= SCREEN_HEIGHT)
	{
		g_Player.pos.y = SCREEN_HEIGHT - 25;
	}



	//減速
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.4f;
	g_Player.move.y += (0.0f - g_Player.move.y) * 0.4f;

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - 25, g_Player.pos.y - 25, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + 25, g_Player.pos.y - 25, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - 25, g_Player.pos.y + 25, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + 25, g_Player.pos.y + 25, 0.0f);

	//頂点バッファのアンロック
	g_pVtxBuffPlayer->Unlock();


	//頂点をロックして頂点データへのポインタを取得
	//g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ画像の更新
	//pVtx[0].tex = D3DXVECTOR2((g_nPatternAnim % 5) * 0.2f, (g_nPatternAnim / 5)*0.5f);
	//pVtx[1].tex = D3DXVECTOR2((g_nPatternAnim % 5) * 0.2f + 0.2f, (g_nPatternAnim / 5)*0.5f);
	//pVtx[2].tex = D3DXVECTOR2((g_nPatternAnim % 5) * 0.2f, (g_nPatternAnim / 5)* 0.5f + 0.5f);
	//pVtx[3].tex = D3DXVECTOR2((g_nPatternAnim % 5) * 0.2f + 0.2f, (g_nPatternAnim / 5)*0.5f + 0.5f);

}
//=============================================================================
// プレイヤー描写処理[DrawPolygon]
//=============================================================================
void DrawPlayer(void)
{		
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得する
	pDevice = GetDevice();

	if (g_Player.bDisp == true)
	{
		//頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

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

	if (g_Player.nLife <= 0)
	{
		SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_Player.state = PLAYERSTEAT_DEATH;
		g_Player.nCntState = 60;
		g_Player.bDisp = false;
		SetGameState(GAMESTATE_OVER);

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
Player *GetPlayer(void)
{
	return &g_Player;
}