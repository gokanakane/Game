//=============================================================================
//
// 弾処理 [Bow.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "Game.h"
#include "bow.h"
#include "main.h"
#include "Player.h"
#include "score.h"
#include "sound.h"
#include "fade.h"
#include "migawari.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BOW		(120)		// 弾の最大数
#define BOW_TEXTUER "data\\TEXTURE\\bow.png"
#define BOW_TEXTUER1 "data\\TEXTURE\\bow001.png"

#define POS_Y (620)
#define BOW_MOVE (1.0f)
#define BOW_PATTERN		(5)
#define MAX_BOW_TYPE (2)
#define MAX_TEX (2)
//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBow[MAX_TEX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBow = NULL;	// 頂点バッファへのポインタ
Bow g_aBow[MAX_BOW];	//弾の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitBow(void)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBow;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for (nCntBow = 0; nCntBow < MAX_BOW; nCntBow++)
	{
		g_aBow[nCntBow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBow[nCntBow].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBow[nCntBow].type = 0;
		g_aBow[nCntBow].nLife = 0;
		g_aBow[nCntBow].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BOW_TEXTUER, &g_pTextureBow[0]);
	D3DXCreateTextureFromFile(pDevice, BOW_TEXTUER1, &g_pTextureBow[1]);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBow,
		NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffBow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBow = 0; nCntBow < MAX_BOW; nCntBow++)
	{
		//座標の設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);//三つ目の頂点の場所指定（右回り）

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//色の設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);//三つ目の頂点の色指定（右回り）

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つずらす
	}
	//頂点バッファのアンロック
	g_pVtxBuffBow->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBow(void)
{
	int nCnt;
		// テクスチャの開放
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureBow[nCnt] != NULL)
		{
			g_pTextureBow[nCnt]->Release();
			g_pTextureBow[nCnt] = NULL;
		}

	}
	// 頂点バッファの開放
	if (g_pVtxBuffBow != NULL)
	{
		g_pVtxBuffBow->Release();
		g_pVtxBuffBow = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBow(void)
{
	Player*pPlayer;
	Migawari*pMigawari;

	int nCntBow;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//取得
	pPlayer = GetPlayer();
	pMigawari = GetMigawari();

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffBow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBow = 0; nCntBow < MAX_BOW; nCntBow++)
	{	//弾が使用されている
		if (g_aBow[nCntBow].bUse == true)//弾が使用されている場合
		{//頂点情報を更新
				//PLと弾が当たった
				if (pPlayer->bDisp == true)
				{
					if (pPlayer->state != PLAYERSTATE_APPEAR)
					{
						if (g_aBow[nCntBow].pos.x > pPlayer->pos.x - 50
							&& g_aBow[nCntBow].pos.x < pPlayer->pos.x + 50
							&& g_aBow[nCntBow].pos.y > pPlayer->pos.y - 100
							&& g_aBow[nCntBow].pos.y < pPlayer->pos.y)
						{
							HitPlayer(1);
							PlaySound(SOUND_LABEL_SE_HIT000);
							g_aBow[nCntBow].bUse = false;//使用してない状態にする
						}

					//身代わりと弾の当たり判定
					if (pMigawari->bUse == true)
					{
						if (g_aBow[nCntBow].pos.x > pMigawari->pos.x - 50
							&& g_aBow[nCntBow].pos.x < pMigawari->pos.x + 50
							&& g_aBow[nCntBow].pos.y > pMigawari->pos.y - 100
							&& g_aBow[nCntBow].pos.y < pMigawari->pos.y)
						{
							HitMigawari(1);
							PlaySound(SOUND_LABEL_SE_HIT000);
							g_aBow[nCntBow].bUse = false;//使用してない状態にする
						}

					}

				}

				g_aBow[nCntBow].nLife--;
				if (g_aBow[nCntBow].nLife == 0)
				{
					g_aBow[nCntBow].move.y += 5.5;
					g_aBow[nCntBow].move.x = 0;
					if (g_aBow[nCntBow].pos.x > SCREEN_WIDTH)
					{
						g_aBow[nCntBow].bUse = false;
					}
				}

				g_aBow[nCntBow].pos += g_aBow[nCntBow].move;
			}
			pVtx[0].pos = D3DXVECTOR3(g_aBow[nCntBow].pos.x - 20, g_aBow[nCntBow].pos.y - 20, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBow[nCntBow].pos.x + 20, g_aBow[nCntBow].pos.y - 20, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBow[nCntBow].pos.x - 20, g_aBow[nCntBow].pos.y + 20, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBow[nCntBow].pos.x + 20, g_aBow[nCntBow].pos.y + 20, 0.0f);

			pVtx += 4;//該当の位置まで進める
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffBow->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBow;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBow, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	// ポリゴンの描画
	for (nCntBow = 0; nCntBow < MAX_BOW; nCntBow++)
	{
		if (g_aBow[nCntBow].bUse == true)//弾が使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBow[g_aBow[nCntBow].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBow,
				2);
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBow(D3DXVECTOR3 pos, D3DXVECTOR3 move,int type)
{
	int nCntBow;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffBow->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBow = 0; nCntBow < MAX_BOW; nCntBow++)
	{
		if (g_aBow[nCntBow].bUse == false)
		{
			PlaySound(SOUND_LABEL_SE_SHOT);

			g_aBow[nCntBow].pos = pos;
			//座標の設定
			pVtx[0].pos = D3DXVECTOR3(pos.x - 20, pos.y - 20, 0.0f);//一つ目の頂点の場所指定
			pVtx[1].pos = D3DXVECTOR3(pos.x + 20, pos.y - 20, 0.0f);//二つ目の頂点の場所指定（右回り）
			pVtx[2].pos = D3DXVECTOR3(pos.x - 20, pos.y + 20, 0.0f);//三つ目の頂点の場所指定（右回り）
			pVtx[3].pos = D3DXVECTOR3(pos.x + 20, pos.y + 20, 0.0f);//三つ目の頂点の場所指定（右回り）

			g_aBow[nCntBow].move = move;
			g_aBow[nCntBow].type = type;
			g_aBow[nCntBow].nLife = 190;
			g_aBow[nCntBow].bUse = true;
			break;
		}
		pVtx += 4;//該当の位置まで進める

	}
	//頂点バッファのアンロック
	g_pVtxBuffBow->Unlock();
}
//=============================================================================
// 弾の取得
//=============================================================================
Bow*GetBow(void)
{
	return &g_aBow[0];
}
