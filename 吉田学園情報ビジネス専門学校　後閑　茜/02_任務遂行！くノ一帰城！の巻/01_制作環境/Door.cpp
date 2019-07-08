//=============================================================================
//
// ドア処理 [DOOR.cpp]
// Author :Gokan Akane
//
//=============================================================================
#include "Game.h"
#include "fade.h"
#include "input.h"
#include "Player.h"
#include "Door.h"
#include "Explosion.h"

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureDoor = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDoor = NULL;	// 頂点バッファへのポインタ
Door g_aDoor;				//ブロックの情報
int nTime;
//=============================================================================
// 初期化処理
//=============================================================================
void InitDoor(void)
{	
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// ブロックの情報の初期化
		g_aDoor.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDoor.state = DOORSTATE_CLOSE;
		g_aDoor.bUse = false;
		nTime = 0;
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, DOOR_TEXTUER, &g_pTextureDoor);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY, 
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffDoor,
								NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.9f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 0.9f);

	//頂点バッファのアンロック
	g_pVtxBuffDoor->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitDoor(void)
{
	//テクスチャの破棄
	if (g_pTextureDoor != NULL)
	{
		g_pTextureDoor->Release();
		g_pTextureDoor = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffDoor != NULL)
	{
		g_pVtxBuffDoor->Release();
		g_pVtxBuffDoor = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateDoor(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	switch (g_aDoor.state)
	{
	case DOORSTATE_CLOSE:
		break;

	case DOORSTATE_OPENSTART:
		nTime++;

		//頂点をロックして頂点データへのポインタを取得
		g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f, 0.9f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.9f);

		//頂点バッファのアンロック
		g_pVtxBuffDoor->Unlock();

		if (nTime > 15)
		{
			g_aDoor.state = DOORSTATE_OPEN;

		}
		break;

	case DOORSTATE_OPEN:
		//頂点をロックして頂点データへのポインタを取得
		g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.75f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f, 0.9f);
		pVtx[3].tex = D3DXVECTOR2(0.75f, 0.9f);

		
		//頂点バッファのアンロック
		g_pVtxBuffDoor->Unlock();
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffDoor, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	if (g_aDoor.bUse == true)//ブロックが使用されている
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureDoor);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
	}
}

//=============================================================================
// ブロックの設定処理
//=============================================================================
void SetDoor(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aDoor.bUse == false)
	{
		//頂点情報を設定
		g_aDoor.pos = pos;

		pVtx[0].pos = D3DXVECTOR3(g_aDoor.pos.x - DOOR_WIDTH, g_aDoor.pos.y - DOOR_HEIGTH, 0.0f);//左上の頂点Xの場所指定
		pVtx[1].pos = D3DXVECTOR3(g_aDoor.pos.x + DOOR_WIDTH, g_aDoor.pos.y - DOOR_HEIGTH, 0.0f);//左上の頂点Xの場所指定
		pVtx[2].pos = D3DXVECTOR3(g_aDoor.pos.x - DOOR_WIDTH, g_aDoor.pos.y , 0.0f);//左上の頂点Xの場所指定
		pVtx[3].pos = D3DXVECTOR3(g_aDoor.pos.x + DOOR_WIDTH, g_aDoor.pos.y , 0.0f);//左上の頂点Xの場所指定

		g_aDoor.bUse = true;
	}
	//頂点バッファのアンロック
	g_pVtxBuffDoor->Unlock();
}
//=============================================================================
//ドアのあたり判定[CollisionDoor]
//=============================================================================
bool CollisionDoor(D3DXVECTOR3 *pPos)//現在の位置
{
	FADE g_Fade;
	g_Fade = GetFade();
	Player*pPlayer;
	bool bLand = false;

	pPlayer = GetPlayer();
	if (g_aDoor.bUse == true)
	{
		bLand = false;
		if (g_aDoor.state == DOORSTATE_OPEN)
		{
			if (g_aDoor.pos.x > pPos->x - 50
				&& g_aDoor.pos.x < pPos->x + 90
				&& g_aDoor.pos.y > pPos->y - 90
				&& g_aDoor.pos.y-10 < pPos->y)
			{
				if (GetKeyboardPress(DIK_RETURN) == true)
				{
					if (g_Fade != FADE_OUT)
					{
						bLand = true;
						pPlayer->state = PLAYERSTATE_APPEAR;
						SetGameState(GAMESTATE_CLEAR);
					}

				}
			}
		}

	}
	return bLand;
}
//=============================================================================
// ブロックの取得[GetDoor]
//=============================================================================
Door*GetDoor(void)
{
	return &g_aDoor;
}