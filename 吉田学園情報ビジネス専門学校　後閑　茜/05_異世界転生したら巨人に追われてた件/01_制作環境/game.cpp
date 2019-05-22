//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "game.h"			// ゲーム
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "sound.h"			// サウンド
#include "input.h"			// 入力
#include "camera.h"			// カメラ
#include "fade.h"			// フェード
#include "meshfield.h"		// メッシュフィールド
#include "meshriver.h"		// メッシュリバー
#include "player.h"			// プレイヤー
#include "block.h"			// ブロック
#include "item.h"			// アイテム
#include "minimap.h"		// ミニマップ
#include "time.h"			// タイム
#include "bg.h"				// ゲーム背景
#include "ui.h"				// ui
#include "life.h"			// ライフ
#include "score.h"			// スコア
#include "ranking.h"		// ランキング
#include "effect.h"			// エフェクト
#include "item.h"			// アイテム
#include "itemicon.h"		// アイテムアイコン
#include "enemy.h"			// 敵
#include "3dobject.h"		// 3D背景オブジェクト
#include "wall.h"			// 壁
#include "start.h"			// スタート

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SOUND_SECOND	(120)		// 秒の最大
#define SOUND_SECOND		(120)		// 秒の最大から足す秒

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CMeshField *CGame::m_pMeshField[m_MeshFieldMax] = { NULL };
CMeshRiver *CGame::m_pMeshRiver[m_MeshRiverMax] = { NULL };
CGame::MODEGAME CGame::m_game = MODE_NONE;

//=============================================================================
// コンストラクタ									(public)	*** CGame ***
//=============================================================================
CGame::CGame()
{
	for (int nCountb = 0; nCountb < TEXT_OBJ_MAX; nCountb++)
	{//	テキストのオブジェクトの種類
		m_textState[nCountb].nCnter = NULL;
		for (int nCount = 0; nCount < OBJ_MAX; nCount++)
		{//	テキストの中身の初期化
			m_textState[nCountb].nType[nCount] = NULL;
			m_textState[nCountb].ncolType[nCount] = NULL;
			m_textState[nCountb].pos[nCount] = {};
			m_textState[nCountb].size[nCount] = {};
			m_textState[nCountb].bUse[nCount] = false;
		}
	}
}

//=============================================================================
// デストラクタ										(public)	*** CGame ***
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ロード処理							(public)	*** CBullet ***
//=============================================================================
HRESULT CGame::Load(void)
{
	return S_OK;
}

//=============================================================================
// アンロード処理								(public)	*** CBullet ***
//=============================================================================
void CGame::Unload(void)
{

}

//=============================================================================
// 初期化処理										(public)	*** CGame ***
//=============================================================================
HRESULT CGame::Init(void)
{
	ObjectLoad();					//	アイテムのテキスト読み込み

	//	エフェクトのテキストの名前の読み込み
	CEffect::LoadNameEffect();
	CEffect::Load();

	CCamera *pCamera = CManager::GetCamera();		// カメラ取得
	pCamera->SetPos(D3DXVECTOR3(50.0f, 230.0f, -500.0f), D3DXVECTOR3(50.0f, 170.0f, 0.0f));

	CWall::Load();
	CWall::Create(D3DXVECTOR3(3430.0f, -150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 150.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(4450.0f, -150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 150.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(4925.0f, -150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(25.0f, 150.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(6595.0f, -150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(45.0f, 150.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(7615.0f, -150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(55.0f, 150.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(11785.0f, -150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(115.0f, 150.0f, 0.0f));

	CMeshField::Load();			// メッシュフィールド
	m_pMeshField[0] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(110.0f, 0.0f, 15.0f), D3DXVECTOR3(1180.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(2200.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[1] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(28.0f, 0.0f, 15.0f), D3DXVECTOR3(3940, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(460.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[2] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(10.0f, 0.0f, 15.0f), D3DXVECTOR3(4700.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(200.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[3] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(30.0f, 0.0f, 15.0f), D3DXVECTOR3(5750.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(800.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[4] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(23.0f, 0.0f, 15.0f), D3DXVECTOR3(7100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(460.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[5] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(100.0f, 0.0f, 15.0f), D3DXVECTOR3(9670.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(2000.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[6] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(12.0f, 0.0f, 15.0f), D3DXVECTOR3(12020.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(240.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	m_pMeshField[7] = CMeshField::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(40.0f, 0.0f, 15.0f), D3DXVECTOR3(13700.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(800.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CSceneMesh::MESHTEX_NUMSIZE);

	CMeshRiver::Load();			// メッシュリバー
	m_pMeshRiver[0] = CMeshRiver::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(12.0f, 0.0f, 15.0f), D3DXVECTOR3(2320, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(240.0f, 0.0f, 300.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.9f), D3DXVECTOR2(0.5f, 0.5f), CSceneMesh::MESHTEX_NUMSIZE, CMeshRiver::TEXTURE_DORO);

	m_pMeshRiver[1] = CMeshRiver::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(14.0f, 0.0f, 15.0f), D3DXVECTOR3(8240, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(280.0f, 0.0f, 300.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.9f), D3DXVECTOR2(0.5f, 0.5f), CSceneMesh::MESHTEX_NUMSIZE, CMeshRiver::TEXTURE_DORO);

	m_pMeshRiver[2] = CMeshRiver::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(21.0f, 0.0f, 15.0f), D3DXVECTOR3(10500, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(420.0f, 0.0f, 300.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.9f), D3DXVECTOR2(0.5f, 0.5f), CSceneMesh::MESHTEX_NUMSIZE, CMeshRiver::TEXTURE_DORO);

	m_pMeshRiver[3] = CMeshRiver::Create(CSceneMesh::MESHTYPE_FIELD, D3DXVECTOR3(16.0f, 0.0f, 15.0f), D3DXVECTOR3(12580, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(320.0f, 0.0f, 300.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(0.5f, 0.5f), CSceneMesh::MESHTEX_NUMSIZE, CMeshRiver::TEXTURE_RIVER);

	CPlayer::Load();			// プレイヤー
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-400.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	CEnemy::Load();				//	敵
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(-600.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CStart::Load();

	CItem::Load();
	CItemicon::Load();

	CBlock::Load();

	C3Dobject::Load();

	CBg::Load();				// ゲーム背景
	CBg::Create();

	CUiPolygon::Load();			// UI
	CUiPolygon::Create(D3DXVECTOR3(150.0f, 70.0f, 0.0f), D3DXVECTOR3(100.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);		// 枠(体力)
	CUiPolygon::Create(D3DXVECTOR3(950.0f, 70.0f, 0.0f), D3DXVECTOR3(120.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);		// 枠(スコア)
	CUiPolygon::Create(D3DXVECTOR3(1182.0f, 70.0f, 0.0f), D3DXVECTOR3(98.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);		// 枠(タイム)
	CUiPolygon::Create(D3DXVECTOR3(560.0f, 70.0f, 0.0f), D3DXVECTOR3(280.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);		// 枠(ミニマップ)
	CUiPolygon::Create(D3DXVECTOR3(570.0f, 70.0f, 0.0f), D3DXVECTOR3(250.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1);		// ミニマップ
	CUiPolygon::Create(D3DXVECTOR3(1125.0f, 68.0f, 0.0f), D3DXVECTOR3(21.0f, 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);		// 時間
	CUiPolygon::Create(D3DXVECTOR3(100.0f, 70.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4);		// プレイヤー
	CUiPolygon::Create(D3DXVECTOR3(1196.0f, 67.0f, 0.0f), D3DXVECTOR3(17.0f, 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);		// 時間の間の点

	CMinimap::Load();			// ミニマップのプレイヤー & 巨人
	CMinimap::Create(D3DXVECTOR3(330.0f, 70.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CMinimap::TYPE_ENEMY, 1);
	CMinimap::Create(D3DXVECTOR3(330.0f, 70.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CMinimap::TYPE_PLAYER, 0);

	CTime::Create();			// タイム

	CScore::Create();			// スコア

	CLife::Load();				// 体力
	CLife::Create();

	return S_OK;
}

//=============================================================================
// 終了処理											(public)	*** CGame ***
//=============================================================================
void CGame::Uninit(void)
{
	CRanking::SaveRanking();
	CBg::Unload();
	CUiPolygon::Unload();
	CMeshField::Unload();
	CPlayer::Unload();
	CMinimap::Unload();
	CItem::Unload();
	CItemicon::Unload();
	CEffect::Unload();
	CEnemy::Unload();
	CBlock::Unload();
	C3Dobject::Unload();

	for (int nCount = 0; nCount < m_MeshFieldMax; nCount++)
	{
		if (m_pMeshField[nCount] != NULL)
		{// NULL以外の場合
			m_pMeshField[nCount]->Uninit();
			m_pMeshField[nCount] = NULL;
		}
	}

	if (m_pPlayer != NULL)
	{// NULL以外の場合
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	CScene::ReleaseMode();	// モード終了
}

//=============================================================================
// 更新処理											(public)	*** CGame ***
//=============================================================================
void CGame::Update(void)
{
	SetStage();

#ifdef _DEBUG
	if (CFade::GetFade() == CFade::FADE_NONE)
	{// フェードしていない状態
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
		{// キーボード（ENTER）を入力したら
			m_game = MODE_GAMECLEAR;
			CFade::Create(CManager::MODE_RESULT, CFade::FADE_OUT);
		}
	}
#endif // _DEBUG

	int nRand = rand() % SOUND_SECOND + MAX_SOUND_SECOND;
	m_nCounter++;		// カウンターの増加

	if ((m_nCounter % nRand) == 0)
	{	// 環境音番号を決める
		//m_nSoundNum = rand() % 6 + 0;
		PlayES(rand() % 6 + 0);
	}

}

//=============================================================================
// 描画処理											(public)	*** CGame ***
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// テキスト読み込み
//=============================================================================
void CGame::ObjectLoad(void)
{
	FILE *pFile;
	char read[128];
	int nObjTypeCounter = 0;		//	オブジェクトの種類の更新

									//	読み込むテキスト
	pFile = fopen("data/TEXT/object.txt", "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ITEM_MAX") == 0)
		{//	アイテムの必要な数の取得
			fscanf(pFile, "%s%d", &read[0], &m_textState[0].nCnter);
		}
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "BLOCK_MAX") == 0)
		{//	ブロックの必要な数の取得
			fscanf(pFile, "%s%d", &read[0], &m_textState[1].nCnter);
		}
		//---------------------------------------------------------------
		//	アイテムの設定のテキスト上コメントアウト
		//---------------------------------------------------------------
		for (int nCount = 0; nCount < 6; nCount++) 	{ fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_textState[nObjTypeCounter].nCnter;)
		{
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ITEM_SET") == 0)
			{//	文字列がアイテムセットだったら
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	位置の設定
						fscanf(pFile, "%s%f%f%f", &read[0], &m_textState[nObjTypeCounter].pos[nCount].x, &m_textState[nObjTypeCounter].pos[nCount].y, &m_textState[nObjTypeCounter].pos[nCount].z);
					}
					else if (strcmp(&read[0], "SIZE") == 0)
					{//	大きさの設定
						fscanf(pFile, "%s%f%f%f", &read[0], &m_textState[nObjTypeCounter].size[nCount].x, &m_textState[nObjTypeCounter].size[nCount].y, &m_textState[nObjTypeCounter].size[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	種類の設定
						fscanf(pFile, "%s%d", &read[0], &m_textState[nObjTypeCounter].nType[nCount]);
					}
				} while (strcmp(&read[0], "ITEM_END") != 0);
				nCount++;
			}
		}
		//---------------------------------------------------------------
		//	ブロックの設定のテキスト上コメントアウト
		//---------------------------------------------------------------
		for (int nCount = 0; nCount < 31; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		nObjTypeCounter += 1;	//	ブロックオブジェクト
		for (int nCount = 0; nCount < m_textState[nObjTypeCounter].nCnter;)
		{
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "BLOCK_SET") == 0)
			{//	文字列がアイテムセットだったら
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	位置の設定
						fscanf(pFile, "%s%f%f%f", &read[0], &m_textState[nObjTypeCounter].pos[nCount].x, &m_textState[nObjTypeCounter].pos[nCount].y, &m_textState[nObjTypeCounter].pos[nCount].z);
					}
					else if (strcmp(&read[0], "MODELTYPE") == 0)
					{//	種類の設定
						fscanf(pFile, "%s%d", &read[0], &m_textState[nObjTypeCounter].nType[nCount]);
					}
					else if (strcmp(&read[0], "COLTYPE") == 0)
					{//	種類の設定
						fscanf(pFile, "%s%d", &read[0], &m_textState[nObjTypeCounter].ncolType[nCount]);
					}
				} while (strcmp(&read[0], "BLOCK_END") != 0);
				nCount++;
			}
		}
		fclose(pFile);
	}
	FILE *pFile3DOBJ;
	//	読み込むテキスト
	pFile3DOBJ = fopen("data/TEXT/3dobject.txt", "r");
	if (pFile3DOBJ != NULL)
	{
		fscanf(pFile3DOBJ, "%s", &read[0]);
		if (strcmp(&read[0], "3DPORIGON_MAX") == 0)
		{//	ブロックの必要な数の取得
			fscanf(pFile3DOBJ, "%s%d", &read[0], &m_textState[2].nCnter);
		}
		//---------------------------------------------------------------
		//	背景オブジェクトの設定のテキスト上コメントアウト
		//---------------------------------------------------------------
		for (int nCount = 0; nCount < 11; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		nObjTypeCounter += 1;	//	ブロックオブジェクト
		for (int nCount = 0; nCount < m_textState[nObjTypeCounter].nCnter;)
		{
			fscanf(pFile3DOBJ, "%s", &read[0]);
			if (strcmp(&read[0], "3DPORIGON_SET") == 0)
			{//	文字列がアイテムセットだったら
				do
				{
					fscanf(pFile3DOBJ, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	位置の設定
						fscanf(pFile3DOBJ, "%s%f%f%f", &read[0], &m_textState[nObjTypeCounter].pos[nCount].x, &m_textState[nObjTypeCounter].pos[nCount].y, &m_textState[nObjTypeCounter].pos[nCount].z);
					}
					else if (strcmp(&read[0], "SIZE") == 0)
					{//	種類の設定
						fscanf(pFile3DOBJ, "%s%f%f%f", &read[0], &m_textState[nObjTypeCounter].size[nCount].x, &m_textState[nObjTypeCounter].size[nCount].y, &m_textState[nObjTypeCounter].size[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	種類の設定
						fscanf(pFile3DOBJ, "%s%d", &read[0], &m_textState[nObjTypeCounter].nType[nCount]);
					}
				} while (strcmp(&read[0], "3DPORIGON_END") != 0);
				nCount++;
			}
		}
		fclose(pFile3DOBJ);
	}
}

void CGame::SetStage(void)
{
	// カメラ設定
	D3DXVECTOR3 posVDest = CManager::GetCamera()->GetPosVDest();	// 視点取得

	for (int nCount = 0; nCount < m_textState[0].nCnter; nCount++)
	{//	アイテムの設定
		if (m_textState[0].pos[nCount].x < posVDest.x + 1000.0f && m_textState[0].bUse[nCount] == false)
		{
			CItem::Create(m_textState[0].pos[nCount], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_textState[0].size[nCount], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), m_textState[0].nType[nCount]);
			m_textState[0].bUse[nCount] = true;
		}
	}

	for (int nCount = 0; nCount < m_textState[1].nCnter; nCount++)
	{//	ブロックの設定
		if (m_textState[1].pos[nCount].x < posVDest.x + 1000.0f && m_textState[1].bUse[nCount] == false)
		{
			CBlock::Create(m_textState[1].pos[nCount], (CBlock::MODELTYPE)m_textState[1].nType[nCount], (CBlock::COLTYPE)m_textState[1].ncolType[nCount]);
			m_textState[1].bUse[nCount] = true;
		}
	}

	for (int nCount = 0; nCount < m_textState[2].nCnter; nCount++)
	{//	ブロックの設定
		if (m_textState[2].pos[nCount].x < posVDest.x + 1000.0f && m_textState[2].bUse[nCount] == false)
		{
			C3Dobject::Create(m_textState[2].pos[nCount], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_textState[2].size[nCount], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), m_textState[2].nType[nCount]);
			m_textState[2].bUse[nCount] = true;
		}
	}
}

//=============================================================================
// 環境音処理											(public)	*** CGame ***
//=============================================================================
void CGame::PlayES(int nSoundNum)
{
	CSound *pSound = CManager::GetSound();
	if (nSoundNum == 0)
	{	// 風の音
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE022);
		nSoundNum = -1;
	}
	else if (nSoundNum == 1)
	{	// 強風の音
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE023);
		nSoundNum = -1;
	}
	else if (nSoundNum == 2)
	{	//	そよ風の音
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE024);
		nSoundNum = -1;
	}
	else if (nSoundNum == 3)
	{	//	鳥の音
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE034);
		nSoundNum = -1;
	}
	else if (nSoundNum == 4)
	{	//	鳥2の音
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE035);
		nSoundNum = -1;
	}
	else if (nSoundNum == 5)
	{	//	鳥3の音
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE036);
		nSoundNum = -1;
	}
	else if (nSoundNum == 6)
	{	//	虫の音
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE037);
		nSoundNum = -1;
	}
}