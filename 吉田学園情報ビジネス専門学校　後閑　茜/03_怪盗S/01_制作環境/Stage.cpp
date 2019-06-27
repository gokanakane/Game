//=============================================================================
//
// ステージ1処理 [Stage.cpp]
// Author : 後閑茜
//
//=============================================================================
#include "Stage.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexStage(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage[STAGE_SPLIT] = {};	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureStage = NULL;			//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffStage[STAGE_SPLIT] = {};		//インデックスバッファへのポインタ
Stage g_Stage[STAGE_SPLIT];

//=============================================================================
// 初期化処理
//=============================================================================
void InitStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		g_Stage[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Stage[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Stage[nCnt].bUse = false;
		g_Stage[nCnt].Heidth = 0;
		g_Stage[nCnt].Width = 0;
		g_Stage[nCnt].VertexStage = 0;
		g_Stage[nCnt].IndexStage = 0;
		g_Stage[nCnt].PolygonStage = 0;
	}

	SetStageMap(13, 13, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	MakeVertexStage(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStage(void)
{
	//テクスチャの破棄
	if (g_pTextureStage != NULL)
	{
		g_pTextureStage->Release();
		g_pTextureStage = NULL;
	}
	// 頂点バッファの開放
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_pVtxBuffStage[nCnt] != NULL)
		{
			g_pVtxBuffStage[nCnt]->Release();
			g_pVtxBuffStage[nCnt] = NULL;
		}
		//インデックスバッファの破棄
		if (g_pIdxBuffStage[nCnt] != NULL)
		{
			g_pIdxBuffStage[nCnt]->Release();
			g_pIdxBuffStage[nCnt] = NULL;
		}
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateStage(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_Stage[nCnt].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Stage[nCnt].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Stage[nCnt].rot.y, g_Stage[nCnt].rot.x, g_Stage[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Stage[nCnt].mtxWorld, &g_Stage[nCnt].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Stage[nCnt].pos.x, g_Stage[nCnt].pos.y, g_Stage[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Stage[nCnt].mtxWorld, &g_Stage[nCnt].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Stage[nCnt].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffStage[nCnt], 0,
				sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffStage[nCnt]);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureStage);
			// ステージ1の描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_Stage[nCnt].VertexStage,	  //頂点数
				0,
				g_Stage[nCnt].PolygonStage);//ポリゴン数
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexStage(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//頂点情報へのポインタ
	WORD*pIdx;		//インデックスデータへのポインタ
	int nCntIdx;	//インデックスのカウンター

		//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTUER, &g_pTextureStage);
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		// 頂点バッファを生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_Stage[nCnt].VertexStage * STAGE_SPLIT,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffStage[nCnt],
			NULL);

		//インデックスバッファの生成
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_Stage[nCnt].IndexStage*STAGE_SPLIT,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,		//16bit確保する
			D3DPOOL_MANAGED,
			&g_pIdxBuffStage[nCnt],
			NULL);


		// 頂点情報の設定----------------------------------------
		//頂点をロックして頂点データへのポインタを取得
		g_pVtxBuffStage[nCnt]->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntz = 0; nCntz <= g_Stage[nCnt].Heidth; nCntz++)
		{//縦
			for (int nCntx = 0; nCntx <= g_Stage[nCnt].Width; nCntx++)
			{//横
				//頂点座標を設定
				pVtx[0].pos = D3DXVECTOR3(-STAGE_X + (STAGE_X * nCntx), 0.0f, STAGE_Z - (STAGE_Z * nCntz));

				//法線の設定（中の数字を全部足して1.0(-1.0)になる）
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//頂点カラーを設定
				pVtx[0].col = D3DXCOLOR(1.0f , 1.0f, 1.0f, 1.0f);

				//テクスチャの設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f * nCntx), 0.0f + (1.0f * nCntz));

				pVtx += 1;
			}
		}
		//頂点バッファのアンロック
		g_pVtxBuffStage[nCnt]->Unlock();

		////頂点座標を設定
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

		// インデックス情報の設定----------------------------------------
		//インデックスバッファをロックしてインデックスバッファデータへのポインタを取得
		g_pIdxBuffStage[nCnt]->Lock(0, 0, (void**)&pIdx, 0);

		nCntIdx = 0;//インデックスカウンターの初期化

		for (int nCntIdx_Z = 0; nCntIdx_Z < g_Stage[nCnt].Heidth; nCntIdx_Z++)
		{//Z軸
			for (int nCntIdx_X = 0; nCntIdx_X <= g_Stage[nCnt].Width; nCntIdx_X++, nCntIdx++)
			{//X軸（Idxも一緒に数える）
				pIdx[0] = (g_Stage[nCnt].Width + 1) + nCntIdx;		//(横幅+1)+Idxカウント
				pIdx[1] = nCntIdx;									//Idxカウントの数
				pIdx += 2;											//ニコイチで進める

			//横幅の端まで到達した　&&　縦幅のカウントが縦幅-1より小さい
				if (nCntIdx_X == g_Stage[nCnt].Width && nCntIdx_Z < g_Stage[nCnt].Heidth - 1)
				{
					pIdx[0] = nCntIdx;									//Idxカウントの数
					pIdx[1] = (g_Stage[nCnt].Width + 1) + nCntIdx + 1;	//(横幅+1)+Idxカウント+1
					pIdx += 2;											//ニコイチで進める
				}
			}
		}
		//インデックスバッファのアンロック
		g_pIdxBuffStage[nCnt]->Unlock();


		////インデックスの設定
		//pIdx[0] = 3;
		//pIdx[1] = 0;

		//pIdx[2] = 4;
		//pIdx[3] = 1;
		//
		//pIdx[4] = 5;
		//pIdx[5] = 2;
		//
		//pIdx[6] = 2;
		//pIdx[7] = 6;
		//
		//pIdx[8] = 6;
		//pIdx[9] = 3;
		//
		//pIdx[10] = 7;
		//pIdx[11] = 4;
		//
		//pIdx[12] = 8;
		//pIdx[13] = 5;

	}

}
//=============================================================================
// ステージ1の取得
//=============================================================================
Stage*GetStage(void)
{
	return &g_Stage[0];
}

//=============================================================================
// ステージ1の配置
//=============================================================================
void SetStageMap(int Width, int Heidth, D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_Stage[nCnt].bUse == false)
		{
			g_Stage[nCnt].Heidth = Heidth;
			g_Stage[nCnt].Width = Width;
			g_Stage[nCnt].pos = pos;
			g_Stage[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//Vtx,Index,Polygonの計算
			g_Stage[nCnt].VertexStage = (Width + 1) * (Heidth + 1);
			g_Stage[nCnt].IndexStage = (Width * Heidth) * 2 + (4 * (Heidth - 1)) + 2;
			g_Stage[nCnt].PolygonStage = (Width * Heidth * 2) + (4 * (Heidth - 1));
			g_Stage[nCnt].bUse = true;
			break;
		}
	}

}
