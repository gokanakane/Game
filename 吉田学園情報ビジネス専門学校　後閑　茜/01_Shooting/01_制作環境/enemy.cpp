//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "enemy.h"
#include "Game.h"
#include "bullet.h"
#include "Explosion.h"
#include "fade.h"
#include "sound.h"
#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(4)												// 敵の種類
#define ENEMY_TEXTURE0		"data\\TEXTURE\\Charactor\\enemy000_a.png"		//敵のテクスチャの名前0
#define ENEMY_TEXTURE1		"data\\TEXTURE\\Charactor\\enemy001_a.png"		//敵のテクスチャの名前1
#define ENEMY_TEXTURE2		"data\\TEXTURE\\Charactor\\enemy002_a.png"		//敵のテクスチャの名前2
#define ENEMY_TEXTURE3		"data\\TEXTURE\\Charactor\\enemy003_a.png"		//敵のテクスチャの名前3
#define PLAYER_PATTERN		(2)

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEnemy[MAX_TYPE_ENEMY] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// 頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];										//敵の情報
int g_nNumEnemy;												//敵の総数
int g_nPatternAnimE;
int g_nCntAnimE;

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;// 頂点情報の作成
	int nCntEnemy;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		g_aEnemy[nCntEnemy].nCntState = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].Cntmove = 0;
		g_aEnemy[nCntEnemy].ChengeMove = 0;
		g_nNumEnemy = 0;
	}

	g_nCntAnimE = 0;
	g_nPatternAnimE = 0;

	// テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE0, &g_pTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE1, &g_pTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE2, &g_pTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE3, &g_pTextureEnemy[3]);


	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
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
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つずらす
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// テクスチャの開放
	for (nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		//テクスチャの破棄
		if (g_pTextureEnemy[nCntTex] != NULL)
		{
			g_pTextureEnemy[nCntTex]->Release();
			g_pTextureEnemy[nCntTex] = NULL;
		}
	}

		// 頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;// 頂点情報の作成
	float pos_x;	//Xの長さ
	float pos_y;	//Yの長さ
	float fAngle;	//角度
	float move_x;	//Xの移動量
	float move_y;	//Yの移動量
	Player*pPlayer;

	pPlayer = GetPlayer();

	g_nCntAnimE++;//カウンターの加算

	//頂点バッファをロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	if ((g_nCntAnimE % 50) == 0)//一定時間が経過
	{
		g_nPatternAnimE = (g_nPatternAnimE + 1) % PLAYER_PATTERN;		//パターンを更新
	}

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nCntEnemy].Cntmove > 80 || g_aEnemy[nCntEnemy].Cntmove < -80)
			{
				g_aEnemy[nCntEnemy].ChengeMove *= -1;//折り返し
			}

			g_aEnemy[nCntEnemy].Cntmove += g_aEnemy[nCntEnemy].ChengeMove;
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].ChengeMove;

			//座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);//一つ目の頂点の場所指定
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);;//二つ目の頂点の場所指定（右回り）
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);//三つ目の頂点の場所指定（右回り）
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);//三つ目の頂点の場所指定（右回り）

			//テクスチャ画像の更新
			pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimE * 0.5f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimE * 0.5f + 0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimE * 0.5f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimE * 0.5f + 0.5f, 1.0f);
			if (pPlayer->pos.x > g_aEnemy[nCntEnemy].pos.x - 50
				&& pPlayer->pos.x < g_aEnemy[nCntEnemy].pos.x + 50
				&& pPlayer->pos.y > g_aEnemy[nCntEnemy].pos.y - 50
				&& pPlayer->pos.y < g_aEnemy[nCntEnemy].pos.y + 50)
			{
				HitEnemy(nCntEnemy, g_aEnemy[nCntEnemy].nLife);
				HitPlayer(MAXPLAYER_LIFE);
				PlaySound(SOUND_LABEL_SE_HIT000);
				pPlayer->bDisp = false;//使用してない状態にする
				g_aEnemy[nCntEnemy].bUse = false;//使用してない状態にする
			}

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NOMAL:
				/*[通常の処理]*/
				if (rand() % 150 == 0)
				{
					Player*pPlayer;
					//プレイヤーの取得
					pPlayer = GetPlayer();
					if (pPlayer->bDisp == true)
					{
						//タンジェントのXY数値を求める
						pos_x = pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x;
						pos_y = pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y;

						//角度を計算
						fAngle = atan2f(pos_x, pos_y);

						//移動量を求める
						move_x = sinf(fAngle)*3.0f;
						move_y = cosf(fAngle)*3.0f;

						SetBullet(g_aEnemy[nCntEnemy].pos,
							D3DXVECTOR3(move_x, move_y, 0.0f),
							BULLETTYPE_EMEMY,
							110);
					}

				}
				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCntState--;
				if (g_aEnemy[nCntEnemy].nCntState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;

					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
				}
				break;
			}
		}
		//該当の位置まで進める
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//敵が使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEnemy * 4,
				2);
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType, int ChengeMove,int Life)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//頂点情報を設定
			g_aEnemy[nCntEnemy].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);//左上の頂点Xの場所指定
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);//左上の頂点Xの場所指定
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);//左上の頂点Xの場所指定
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);//左上の頂点Xの場所指定

			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].bUse = true;
			g_aEnemy[nCntEnemy].nLife = Life;
			g_aEnemy[nCntEnemy].nCntState = 0;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
			g_aEnemy[nCntEnemy].Cntmove = 0;				//移動量のカウンター
			g_aEnemy[nCntEnemy].ChengeMove = ChengeMove;	//移動量
			g_nNumEnemy++;

			break;
		}
		pVtx += 4;//該当の位置まで進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}
//=============================================================================
// 敵のダメージ処理
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_aEnemy[nCntEnemy].bUse = false;
		g_nNumEnemy--;
		if (g_nNumEnemy <= 0)
		{//全滅した
			SetGameState(GAMESTATE_CLEAR);			
		}
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCntState = 5;//ダメージ状態の時間

		VERTEX_2D *pVtx;// 頂点情報の作成
		//頂点バッファをロック
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntEnemy * 4);

		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		
		// 頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();

	}

}

//=============================================================================
// 敵の取得
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}
