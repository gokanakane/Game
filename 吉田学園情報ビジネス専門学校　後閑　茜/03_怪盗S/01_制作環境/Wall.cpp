//=============================================================================
//
// ステージ壁処理 [Wall.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "ItemGetUI.h"
#include "Item.h"
#include "sound.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall[MAX_WALL] = {};	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall[MAX_WALLTEX] = {};			//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffWall[MAX_WALL] = {};		//インデックスバッファへのポインタ
Wall g_Wall[MAX_WALL];
int g_nCntLockWall;

//=============================================================================
// 初期化処理
//=============================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_Wall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCnt].bUse = false;
		g_Wall[nCnt].Heidth = 0;
		g_Wall[nCnt].Width = 0;
		g_Wall[nCnt].VertexStage = 0;
		g_Wall[nCnt].IndexStage = 0;
		g_Wall[nCnt].PolygonStage = 0;
		g_Wall[nCnt].nTexType = 0;
	}
	g_nCntLockWall = 0;

	//四辺---------------------------------
	SetWall(13, 1, D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),0);
	SetWall(13, 1, D3DXVECTOR3(550.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 0);
	SetWall(13, 1, D3DXVECTOR3(-50.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f), 0);
	SetWall(13, 1, D3DXVECTOR3(600.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	
	//下----------------------------------
	SetWall(10, 1, D3DXVECTOR3(100.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(150.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(50.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(100.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(550.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(550.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(550.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(400.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(100.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(50.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(0.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);

	//中----------------------------------
	SetWall(2, 1, D3DXVECTOR3(0.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(150.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(8, 1, D3DXVECTOR3(50.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(500.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(500.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(500.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(200.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(100.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(500.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(450.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(4, 1, D3DXVECTOR3(250.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);

	//上----------------------------------
	SetWall(7, 1, D3DXVECTOR3(150.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(550.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(200.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(450.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(50.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(50.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(100.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(200.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(400.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(2, 1, D3DXVECTOR3(450.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(1, 1, D3DXVECTOR3(500.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);
	SetWall(3, 1, D3DXVECTOR3(400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 0);

	//檻の壁----------------------------------
	SetWall(2, 1, D3DXVECTOR3(200.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(300.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(150.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(2, 1, D3DXVECTOR3(300.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(250.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 5);//扉C
	SetWall(1, 1, D3DXVECTOR3(400.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(400.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 5);//扉A
	SetWall(2, 1, D3DXVECTOR3(300.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(2, 1, D3DXVECTOR3(250.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(300.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(350.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 5);//扉B
	SetWall(1, 1, D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(250.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 5);//扉D
	SetWall(2, 1, D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), 4);
	SetWall(2, 1, D3DXVECTOR3(350.0f, 0.0f, -350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(250.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	SetWall(1, 1, D3DXVECTOR3(350.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	SetWall(2, 1, D3DXVECTOR3(300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);


	MakeVertexWall(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWall(void)
{
	for (int nCnt = 0; nCnt < MAX_WALLTEX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureWall[nCnt] != NULL)
		{
			g_pTextureWall[nCnt]->Release();
			g_pTextureWall[nCnt] = NULL;
		}
	}
	// 頂点バッファの開放
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_pVtxBuffWall[nCnt] != NULL)
		{
			g_pVtxBuffWall[nCnt]->Release();
			g_pVtxBuffWall[nCnt] = NULL;
		}
		//インデックスバッファの破棄
		if (g_pIdxBuffWall[nCnt] != NULL)
		{
			g_pIdxBuffWall[nCnt]->Release();
			g_pIdxBuffWall[nCnt] = NULL;
		}
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス


	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (nCnt >= 4)
		{
			// レンダーステートの設定
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// 裏面をカリング
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

		}
		if (g_Wall[nCnt].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Wall[nCnt].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCnt].rot.y, g_Wall[nCnt].rot.x, g_Wall[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Wall[nCnt].mtxWorld, &g_Wall[nCnt].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCnt].pos.x, g_Wall[nCnt].pos.y, g_Wall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Wall[nCnt].mtxWorld, &g_Wall[nCnt].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCnt].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall[nCnt], 0,
				sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffWall[nCnt]);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall[g_Wall[nCnt].nTexType]);
			// ステージ1の描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_Wall[nCnt].VertexStage,	  //頂点数
				0,
				g_Wall[nCnt].PolygonStage);//ポリゴン数
		}
	
		// レンダーステートの設定
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
		//αテストの無効化
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	}

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//頂点情報へのポインタ
	WORD*pIdx;		//インデックスデータへのポインタ
	int nCntIdx;	//インデックスのカウンター

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, WALL_TEXTUER, &g_pTextureWall[0]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEXTUER1, &g_pTextureWall[1]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEXTUER2, &g_pTextureWall[2]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEXTUER3, &g_pTextureWall[3]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEXTUER4, &g_pTextureWall[4]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEXTUER5, &g_pTextureWall[5]);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		// 頂点バッファを生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_Wall[nCnt].VertexStage * MAX_WALL,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffWall[nCnt],
			NULL);

		//インデックスバッファの生成
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_Wall[nCnt].IndexStage*MAX_WALL,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,		//16bit確保する
			D3DPOOL_MANAGED,
			&g_pIdxBuffWall[nCnt],
			NULL);


		// 頂点情報の設定----------------------------------------
		//頂点をロックして頂点データへのポインタを取得
		g_pVtxBuffWall[nCnt]->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntz = 0; nCntz <= g_Wall[nCnt].Heidth; nCntz++)
		{//縦
			for (int nCntx = 0; nCntx <= g_Wall[nCnt].Width; nCntx++)
			{//横
				//頂点座標を設定
				pVtx[0].pos = D3DXVECTOR3(-WALLVTX_X + (WALLVTX_X * nCntx), WALLVTX_Y - (WALLVTX_Y * nCntz), 0.0f);

				//法線の設定（中の数字を全部足して1.0(-1.0)になる）
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//頂点カラーを設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//テクスチャの設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f * nCntx), 0.0f + (1.0f * nCntz));

				pVtx += 1;
			}
		}
		//頂点バッファのアンロック
		g_pVtxBuffWall[nCnt]->Unlock();

		// インデックス情報の設定----------------------------------------
		//インデックスバッファをロックしてインデックスバッファデータへのポインタを取得
		g_pIdxBuffWall[nCnt]->Lock(0, 0, (void**)&pIdx, 0);

		nCntIdx = 0;//インデックスカウンターの初期化

		for (int nCntIdx_Z = 0; nCntIdx_Z < g_Wall[nCnt].Heidth; nCntIdx_Z++)
		{//Z軸
			for (int nCntIdx_X = 0; nCntIdx_X <= g_Wall[nCnt].Width; nCntIdx_X++, nCntIdx++)
			{//X軸（Idxも一緒に数える）
				pIdx[0] = (g_Wall[nCnt].Width + 1) + nCntIdx;		//(横幅+1)+Idxカウント
				pIdx[1] = nCntIdx;									//Idxカウントの数
				pIdx += 2;											//ニコイチで進める

			//横幅の端まで到達した　&&　縦幅のカウントが縦幅-1より小さい
				if (nCntIdx_X == g_Wall[nCnt].Width && nCntIdx_Z < g_Wall[nCnt].Heidth - 1)
				{
					pIdx[0] = nCntIdx;									//Idxカウントの数
					pIdx[1] = (g_Wall[nCnt].Width + 1) + nCntIdx + 1;	//(横幅+1)+Idxカウント+1
					pIdx += 2;											//ニコイチで進める
				}
			}
		}
		//インデックスバッファのアンロック
		g_pIdxBuffWall[nCnt]->Unlock();
	}

	//頂点座標を設定
	//pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	//pVtx[2].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	//pVtx[3].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	//pVtx[8].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

	////頂点座標を設定
	//pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 1.0f);
	//pVtx[2].pos = D3DXVECTOR3(0.0f, 2.0f);
	//pVtx[3].pos = D3DXVECTOR3(1.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(1.0f, 1.0f);
	//pVtx[5].pos = D3DXVECTOR3(1.0f, 2.0f);
	//pVtx[6].pos = D3DXVECTOR3(2.0f, 0.0f);
	//pVtx[7].pos = D3DXVECTOR3(2.0f, 1.0);
	//pVtx[8].pos = D3DXVECTOR3(2.0f, 2.0f);

	//インデックスの設定
	//pIdx[0] = 3;
	//pIdx[1] = 0;

	//pIdx[2] = 4;
	//pIdx[3] = 1;

	//pIdx[4] = 5;
	//pIdx[5] = 2;

	//pIdx[6] = 2;
	//pIdx[7] = 6;

	//pIdx[8] = 6;
	//pIdx[9] = 3;

	//pIdx[10] = 7;
	//pIdx[11] = 4;

	//pIdx[12] = 8;
	//pIdx[13] = 5;


}

//=============================================================================
// ステージ1の配置
//=============================================================================
void SetWall(int Width, int Heidth, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int TexType)
{
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_Wall[nCnt].bUse == false)
		{
			g_Wall[nCnt].Heidth = Heidth;
			g_Wall[nCnt].Width = Width;
			g_Wall[nCnt].pos = pos;
			g_Wall[nCnt].rot = rot;
			g_Wall[nCnt].nTexType = TexType;

			//Vtx,Index,Polygonの計算
			g_Wall[nCnt].VertexStage = (Width + 1) * (Heidth + 1);
			g_Wall[nCnt].IndexStage = (Width * Heidth) * 2 + (4 * (Heidth - 1)) + 2;
			g_Wall[nCnt].PolygonStage = (Width * Heidth * 2) + (4 * (Heidth - 1));
			g_Wall[nCnt].bUse = true;

			if (nCnt >= 4)
			{
				// ベクトル計算のために壁のベクトル（下）を取得
				if (rot.y == 0)
				{//回っていない
					g_Wall[nCnt].aPos[0] = D3DXVECTOR3(-50.0f + pos.x, 0.0f, pos.z + 10.0f);
					g_Wall[nCnt].aPos[1] = D3DXVECTOR3(-50.0f + pos.x + (50.0f*Width), 0.0f, pos.z + 10.0f);
					g_Wall[nCnt].aPos[2] = D3DXVECTOR3(-50.0f + pos.x + (50.0f*Width), 0.0f, pos.z - 10.0f);
					g_Wall[nCnt].aPos[3] = D3DXVECTOR3(-50.0f + pos.x, 0.0f, pos.z - 10.0f);
				}
				else
				{//回っている
					g_Wall[nCnt].aPos[0] = D3DXVECTOR3(pos.x - 10.0f, 0.0f, 50.0f + pos.z);
					g_Wall[nCnt].aPos[1] = D3DXVECTOR3(pos.x + 10.0f, 0.0f, 50.0f + pos.z);
					g_Wall[nCnt].aPos[2] = D3DXVECTOR3(pos.x + 10.0f, 0.0f, 50.0f + pos.z + (-50.0f*Width));
					g_Wall[nCnt].aPos[3] = D3DXVECTOR3(pos.x - 10.0f, 0.0f, 50.0f + pos.z + (-50.0f*Width));

				}
			}
			else
			{
				g_Wall[nCnt].aPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Wall[nCnt].aPos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Wall[nCnt].aPos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Wall[nCnt].aPos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			}

		break;
		}
	}
}
//=============================================================================
// 横向きの壁あたり判定（プレイヤー）
//=============================================================================
void CollisionWall_WIDTH_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[MAX_WALL];		//あたり判定の計算結果
	Player*pPlayer = GetPlayer();

	for (int nCnt = 4; nCnt < MAX_WALL; nCnt++)
	{//壁の枚数
		if (g_Wall[nCnt].bUse == true)
		{//壁が出ている
			if (g_Wall[nCnt].rot.y == 0.0f)
			{//回っていない壁
				if (g_Wall[nCnt].aPos[0].x < pPlayer->pos.x &&
					g_Wall[nCnt].aPos[1].x > pPlayer->pos.x)
				{//壁の範囲
					if (g_Wall[nCnt].pos.z > posOld->z)
					{//前から当たった

						//ベクトル計算
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[2] - g_Wall[nCnt].aPos[3];
						g_Wall[nCnt].VecC = pPlayer->pos - g_Wall[nCnt].aPos[2];

						//あたり判定計算
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pPlayer->pos.z = g_Wall[nCnt].aPos[2].z - pPlayer->vtxMax.z + 5.0f;
							break;
						}
					}
					else if (g_Wall[nCnt].pos.z < posOld->z)
					{//後ろから当たった

						//ベクトル計算
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[0] - g_Wall[nCnt].aPos[1];
						g_Wall[nCnt].VecC = pPlayer->pos - g_Wall[nCnt].aPos[0];

						//あたり判定計算
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pPlayer->pos.z = g_Wall[nCnt].aPos[0].z - pPlayer->vtxMax.z + 5.0f;
							break;
						}

					}
				}
			}
		}
	}
}
//=============================================================================
// 縦向き壁あたり判定（プレイヤー）
//=============================================================================
void CollisionWall_HEIDTH_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[MAX_WALL];		//あたり判定の計算結果
	Player*pPlayer = GetPlayer();
	ItemUI*pItemUI = GetItemUI();

	for (int nCnt = 4; nCnt < MAX_WALL; nCnt++)
	{//壁の枚数
		if (g_Wall[nCnt].bUse == true)
		{//壁が出ている
			if (g_Wall[nCnt].rot.y != 0.0f)
			{//回っている
				if (g_Wall[nCnt].aPos[1].z > pPlayer->pos.z &&
					g_Wall[nCnt].aPos[2].z < pPlayer->pos.z)
				{//壁の範囲
					if (g_Wall[nCnt].pos.x < posOld->x)
					{//右から当たった

					 //ベクトル計算
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[1] - g_Wall[nCnt].aPos[2];
						g_Wall[nCnt].VecC = pPlayer->pos - g_Wall[nCnt].aPos[1];

						//あたり判定計算
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							if (g_Wall[nCnt].nTexType == 5)
							{
								if (pItemUI->bUse == true)
								{
									g_Wall[nCnt].bUse = false;
									PlaySound(SOUND_LABEL_SE_OAPNDOOR);
									g_nCntLockWall++;

								}
							}
							pPlayer->pos.x = g_Wall[nCnt].aPos[1].x - pPlayer->vtxMin.x - 5.0f;
							break;
						}
					}
					if (g_Wall[nCnt].pos.x > posOld->x)
					{//左から当たった

					 //ベクトル計算
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[3] - g_Wall[nCnt].aPos[0];
						g_Wall[nCnt].VecC = pPlayer->pos - g_Wall[nCnt].aPos[3];

						//あたり判定計算
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							if (g_Wall[nCnt].nTexType == 5)
							{
								if (pItemUI->bUse == true)

								{
									g_Wall[nCnt].bUse = false;
									PlaySound(SOUND_LABEL_SE_OAPNDOOR);
									g_nCntLockWall++;

								}
							}
							pPlayer->pos.x = g_Wall[nCnt].aPos[3].x + pPlayer->vtxMin.x + 5.0f;
							break;
						}
					}
				}
			}
		}
	}
	if (g_nCntLockWall == 4)
	{
		DeleteItemGetUI(0);
		g_nCntLockWall = 0;
	}

}
//=============================================================================
// 横向きの壁あたり判定（敵）
//=============================================================================
bool CollisionWall_WIDTH_ENE(D3DXVECTOR3 *pos, D3DXVECTOR3 aPos, D3DXVECTOR3 *posOld,D3DXVECTOR3 *rot)
{//aPos == 比べる用
	float VecLine[MAX_WALL];		//あたり判定の計算結果
	bool bLand;

	for (int nCnt = 4; nCnt < MAX_WALL; nCnt++)
	{//壁の枚数
		if (g_Wall[nCnt].bUse == true)
		{//壁が出ている

			bLand = false;
			
			if (g_Wall[nCnt].rot.y == 0.0f)
			{//回っていない壁

				if (g_Wall[nCnt].aPos[0].x < aPos.x &&
					g_Wall[nCnt].aPos[1].x > aPos.x)
				{//壁の範囲
					if (g_Wall[nCnt].pos.z > posOld->z)
					{//前から当たった

					 //ベクトル計算
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[2] - g_Wall[nCnt].aPos[3];
						g_Wall[nCnt].VecC = aPos - g_Wall[nCnt].aPos[2];

						//あたり判定計算
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							rot->y = 0.0f;
							bLand = true;
							break;
						}
					}
					else if (g_Wall[nCnt].pos.z < posOld->z)
					{//後ろから当たった

					 //ベクトル計算
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[0] - g_Wall[nCnt].aPos[1];
						g_Wall[nCnt].VecC = aPos - g_Wall[nCnt].aPos[0];

						//あたり判定計算
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							rot->y = D3DX_PI;
							bLand = true;
							break;
						}
					}
				}
			}
		}
	}
	return bLand;

}
//=============================================================================
// 縦向きの壁あたり判定（敵）
//=============================================================================
bool CollisionWall_HEIDTH_ENE(D3DXVECTOR3 *pos, D3DXVECTOR3 aPos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *rot)
{
	float VecLine[MAX_WALL];		//あたり判定の計算結果
	bool bLand;

	for (int nCnt = 4; nCnt < MAX_WALL; nCnt++)
	{//壁の枚数
		if (g_Wall[nCnt].bUse == true)
		{//壁が出ている

			bLand = false;

			if (g_Wall[nCnt].rot.y != 0.0f)
			{//回っている
				if (g_Wall[nCnt].aPos[1].z > aPos.z &&
					g_Wall[nCnt].aPos[2].z < aPos.z)
				{//壁の範囲
					if (g_Wall[nCnt].pos.x < posOld->x)
					{//右から当たった

					 //ベクトル計算
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[1] - g_Wall[nCnt].aPos[2];
						g_Wall[nCnt].VecC = aPos - g_Wall[nCnt].aPos[1];

						//あたり判定計算
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							rot->y = D3DX_PI * -0.5f;
							bLand = true;
							break;
						}
					}
					if (g_Wall[nCnt].pos.x > posOld->x)
					{//左から当たった

					 //ベクトル計算
						g_Wall[nCnt].VecA = g_Wall[nCnt].aPos[3] - g_Wall[nCnt].aPos[0];
						g_Wall[nCnt].VecC = aPos - g_Wall[nCnt].aPos[3];

						//あたり判定計算
						VecLine[nCnt] = (g_Wall[nCnt].VecA.z*g_Wall[nCnt].VecC.x) - (g_Wall[nCnt].VecA.x*g_Wall[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							rot->y = D3DX_PI * 0.5f;
							bLand = true;
							break;
						}
					}
				}
			}
		}
	}

	return bLand;
}

//=============================================================================
// ステージ1の取得
//=============================================================================
Wall*GetWall(void)
{
	return &g_Wall[0];
}