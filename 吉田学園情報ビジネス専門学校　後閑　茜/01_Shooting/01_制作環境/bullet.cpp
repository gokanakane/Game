//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author :Gokan Akane
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "main.h"
#include "Player.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "sound.h"
#include "fade.h"


//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet[2] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];	//弾の情報
int g_nPatternAnimB;
int g_nCntAnimB;

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{	
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].bUse = false;
	}


	g_nCntAnimB = 0;
	g_nPatternAnimB = 0;

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, BULLET_TEXTUER, &g_pTextureBullet[0]);
		D3DXCreateTextureFromFile(pDevice, BULLET_TEXTUER1, &g_pTextureBullet[1]);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET, 
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffBullet, 
								NULL);

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
	g_pVtxBuffBullet->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	int nCnt;
		// テクスチャの開放
	for (nCnt = 0; nCnt < MAX_BULLET_TYPE; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureBullet[nCnt] != NULL)
		{
			g_pTextureBullet[nCnt]->Release();
			g_pTextureBullet[nCnt] = NULL;
		}

	}
	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	int nCntEnemy;
	Enemy*pEnemy;

	g_nCntAnimB++;

	if ((g_nCntAnimB % 10) == 0)//一定時間が経過
	{
		g_nPatternAnimB = (g_nPatternAnimB + 1) % BULLET_PATTERN;		//パターンを更新
	}

	//頂点をロックして頂点データへのポインタを取得
 	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{	//弾が使用されている
		if (g_aBullet[nCntBullet].bUse == true)//弾が使用されている場合
		{//頂点情報を更新
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x -20, g_aBullet[nCntBullet].pos.y - 20, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 20, g_aBullet[nCntBullet].pos.y - 20, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 20, g_aBullet[nCntBullet].pos.y + 20, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 20, g_aBullet[nCntBullet].pos.y + 20, 0.0f);

			pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimB % 4) * 0.25f, (g_nPatternAnimB / 4)*0.5f);
			pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimB % 4) * 0.25f + 0.2f, (g_nPatternAnimB / 4)*0.5f);
			pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimB % 4) * 0.25f, (g_nPatternAnimB / 4)* 0.5f + 0.5f);
			pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimB % 4) * 0.25f + 0.2f, (g_nPatternAnimB / 4)*0.5f + 0.5f);

			
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{//PLの弾
				//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f),20.0f,30);
				//敵の取得
				pEnemy = GetEnemy();

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)//敵が使われている
					{//敵と弾が当たった
						if (g_aBullet[nCntBullet].pos.x > pEnemy->pos.x - 50
							&& g_aBullet[nCntBullet].pos.x < pEnemy->pos.x + 50
							&& g_aBullet[nCntBullet].pos.y > pEnemy->pos.y - 50
							&& g_aBullet[nCntBullet].pos.y < pEnemy->pos.y + 50)
						{
							HitEnemy(nCntEnemy, 1);
							AddScore(4000);
							PlaySound(SOUND_LABEL_SE_HIT000);
							g_aBullet[nCntBullet].bUse = false;//使用してない状態にする
						}

					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_EMEMY)
			{//敵の弾
				Player*pPlayer;

				//プレイヤーの取得
				pPlayer = GetPlayer();

				//PLと弾が当たった
				if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - 50
					&& g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + 50
					&& g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - 50
					&& g_aBullet[nCntBullet].pos.y < pPlayer->pos.y + 50)
				{
					HitPlayer(1);
					PlaySound(SOUND_LABEL_SE_HIT001);
					g_aBullet[nCntBullet].bUse = false;//使用してない状態にする
				}
			}

			//一定時間経過
			g_aBullet[nCntBullet].nLife--;
			
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f), 50.0f, 30);
				//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		
		pVtx += 4;//該当の位置まで進める
	}
		//頂点バッファのアンロック
 		g_pVtxBuffBullet->Unlock();
		
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	// ポリゴンの描画
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].type == BULLETTYPE_EMEMY)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet[1]);

		}
		else
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet[0]);

		}


		if (g_aBullet[nCntBullet].bUse == true)//弾が使用されている
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBullet,
				2);
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,int Life)
{
	int nCntBullet;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			PlaySound(SOUND_LABEL_SE_SHOT);

			g_aBullet[nCntBullet].pos = pos;
			//座標の設定
			pVtx[0].pos = D3DXVECTOR3(pos.x + 0,pos.y+ 0, 0.0f);//一つ目の頂点の場所指定
			pVtx[1].pos = D3DXVECTOR3(pos.x + 20,pos.y + 0, 0.0f);//二つ目の頂点の場所指定（右回り）
			pVtx[2].pos = D3DXVECTOR3(pos.x + 0, pos.y + 20, 0.0f);//三つ目の頂点の場所指定（右回り）
			pVtx[3].pos = D3DXVECTOR3(pos.x + 20, pos.y + 20, 0.0f);//三つ目の頂点の場所指定（右回り）

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].bUse = true;
			g_aBullet[nCntBullet].nLife = Life;
			g_aBullet[nCntBullet].type = type;
			break;
		}
		pVtx += 4;//該当の位置まで進める

	}
	//頂点バッファのアンロック
	g_pVtxBuffBullet->Unlock();
}

