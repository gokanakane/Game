//=============================================================================
//
// タイマー処理 [time.cpp]
// Author : keisuke komatsu
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "point.h"
#include "number.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "scene2D.h"
#include "tutorial.h"
#include "sceneBillboard.h"
#include "time.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define CENTER_WIDTH		(SCREEN_WIDTH / 2)				// Xの中心座標
#define TIMER_SPACE			(10.0f)							// 数字と数字の間のサイズ(ゲーム時間)
#define TIMER_POSITION_Y	(70.0f)							// タイマーのY座標(ゲーム時間)
#define POWER_X				(10)
#define POINT_POS_1P_ONE	(D3DXVECTOR3(1203.0f, 682.0f, 0.0f))	// 順位の位置(1Pだけの場合)
#define POINT_POS_2P_ONE	(D3DXVECTOR3(835.0f, 60.0f, 0.0f))	// 制限時間の位置(1Pだけの場合)
#define POINT_POS_3P_ONE	(D3DXVECTOR3(1035.0f, 60.0f, 0.0f))	// 制限時間の位置(1Pだけの場合)
#define POINT_POS_4P_ONE	(D3DXVECTOR3(1235.0f, 60.0f, 0.0f))	// 制限時間の位置(1Pだけの場合)
#define POINT_POS_2P_TWO	(D3DXVECTOR3(155.0f, 430.0f, 0.0f))	// 制限時間の位置(2 〜 4画面だけの場合)
#define POINT_POS_4P_TWO	(D3DXVECTOR3(1235.0f, 430.0f, 0.0f))// 制限時間の位置(2 〜 4画面だけの場合)

#define WAIT_TIME_END		(180)							// 待ち時間
#define MAX_POINT			(99)							// 最大数
#define DEFAULT_SIZE		(D3DXVECTOR3(10.0f, 15.0f, 0.0f))		// デフォルトのサイズ (数字)
#define	MAX_SIZE			(D3DXVECTOR3(25.0f, 30.0f, 0.0f))		// 最大のサイズ (数字)
#define CONFIRM_TIME		(30)							// 確定演出の時間
//=============================================================================
//	静的メンバ変数
//=============================================================================

//=============================================================================
// 生成処理
//=============================================================================
CPoint *CPoint::Create(int nID, int nNumPlayer, TYPE_CHARACTER type)
{
	CPoint *pPoint = NULL;

	//NULLチェック
	if (pPoint == NULL)
	{//動的確保
		pPoint = new CPoint;

		//NULLチェック
		if (pPoint != NULL)
		{
			pPoint->m_type = type;		// 種類を代入
			pPoint->m_nNumPlayer = nNumPlayer;		// 人数を取得
			pPoint->m_nID = nID;
			pPoint->PointPostion();		// ポイントの位置まとめ
			//初期化処理
			pPoint->Init();
			pPoint->UIPosition(nID);		// UIの設定
		}
	}

	return pPoint;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPoint::CPoint(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nPointNum = 1;
	m_bStart = false;
	m_pIcon = NULL;
	m_nID = 0;
	m_nWinNum = 0;
	m_nCountNum = 0;
	m_nCntbConfirm = CONFIRM_TIME - 1;
	m_type = TYPE_NONE;
	m_bSizeChange = false;
	m_bChangeFlag = false;
	m_bColChange = false;
	m_bFlag = false;
	m_bRankChangeFlag = false;
	m_bFlag001 = true;
	m_pRank = NULL;
	m_pCrown = NULL;
	m_bConfirmFlag = false;
	m_RnakSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCntPoint = 0; nCntPoint < MAX_POINT_NUM; nCntPoint++)
	{
		m_apNumber[nCntPoint] = NULL;
	}

	for (int nCntVision = 0; nCntVision < MAX_PLAYER; nCntVision++)
	{
		m_bDrawVision[nCntVision] = false;
	}

}

//=============================================================================
// デストラクタ
//=============================================================================
CPoint::~CPoint() {}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPoint::Init(void)
{
	int nTexData = 0;
	m_nTotalPoint = 0;
	m_nPointNum = PowerCalculation(m_nTotalPoint);

	for (int nCntPoint = 0; nCntPoint < MAX_POINT_NUM; nCntPoint++)
	{	// ポイント初期設定
		m_apNumber[nCntPoint] = new CBillNumber;
		m_apNumber[nCntPoint]->Init(D3DXVECTOR3((m_pos.x - TIMER_SPACE * nCntPoint), m_pos.y + 50.0f, m_pos.z));
		m_apNumber[nCntPoint]->SetPos(D3DXVECTOR3((m_pos.x - TIMER_SPACE * nCntPoint), m_pos.y + 50.0f, 0.0f));
		m_apNumber[nCntPoint]->SetSize(DEFAULT_SIZE);
		m_apNumber[nCntPoint]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		m_fPosOld = m_apNumber[nCntPoint]->GetPos().y;
	}

	// 数字のテクスチャ設定
	TexPoint(nTexData);

	if (m_type == TYPR_PLAYER)
	{
		// 順位ロゴの位置
		RankPos();
	}

	SetObjType(OBJTYPE_POINT);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPoint::Uninit(void)
{
	for (int nCntPoint = 0; nCntPoint < MAX_POINT_NUM; nCntPoint++)
	{	// タイマーの破棄
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->Uninit();
			m_apNumber[nCntPoint] = NULL;
		}
	}


	if (m_pRank != NULL) { m_pRank->Uninit(); m_pRank = NULL; }

	if (m_pCrown != NULL) { m_pCrown->Uninit(); m_pCrown = NULL; }

	if (m_pIcon != NULL)
	{
		m_pIcon->Uninit();
		m_pIcon = NULL;
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPoint::Update(void)
{
	//現在のモードの取得
	CManager::MODE GameMode = CManager::GetMode();
	DebugKey();		// デバック用

	if ((GameMode == CManager::MODE_GAME) || (GameMode == CManager::MODE_TUTORIAL))
	{//制限時間
	 //ゲーム
		int nTexData = 0;
		// 数字のテクスチャ設定
		TexPoint(nTexData);

		// ポイント増減時の変化
		SizeChange();

		PointPostion();	// ポイントの位置更新

		ChangeRank();	// 順位切替時の演出処理

		if (m_nWinNum == 3) { if (m_pCrown != NULL) { m_pCrown->Uninit(); m_pCrown = NULL; } }
		else if (m_nWinNum != 3)
		{
			if (m_pCrown != NULL)
			{
				m_pCrown->SetTexture(D3DXVECTOR2((0.333f * m_nWinNum), 0.0f), D3DXVECTOR2(0.333f + (m_nWinNum * 0.333f), 1.0f));
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPoint::Draw(void)
{
	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->Draw();
		}
	}

	if (m_pIcon != NULL)
	{
		//m_pIcon->Draw();
	}
}

//=============================================================================
// タイマーのTexture管理
//=============================================================================
void CPoint::TexPoint(int nTexData)
{
	nTexData = m_nTotalPoint;

	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{// テクスチャに反映
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->SetNumber(nTexData);
			nTexData /= 10;
		}
	}
}
//=============================================================================
// タイム加算処理
//=============================================================================
void CPoint::AddPoint(int nPoint)
{
	if (m_nTotalPoint < MAX_POINT)
	{
		m_nTotalPoint += nPoint;
	}

	if (MAX_POINT < m_nTotalPoint) { m_nTotalPoint = MAX_POINT; }
	m_nPointNum = PowerCalculation(m_nTotalPoint);
	m_bSizeChange = true;
	m_bFlag = false;
	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{// テクスチャに反映
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
}
//=============================================================================
// タイム減算処理
//=============================================================================
void CPoint::SubtractionPoint(int nPoint)
{
	if (m_nTotalPoint < MAX_POINT)
	{
		m_nTotalPoint -= nPoint;
	}

	if (0 > m_nTotalPoint) { m_nTotalPoint = 0; }
	m_nPointNum = PowerCalculation(m_nTotalPoint);
	m_bSizeChange = true;
	m_bFlag = true;
	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{// テクスチャに反映
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		}
	}
}

//=============================================================================
// べき乗の計算
//=============================================================================
int CPoint::PowerCalculation(int nData)
{
	int nNum = 1;
	int nPower = (int)std::pow(POWER_X, nNum);
	int nDataNum = nData;
	while ((nDataNum / nPower) != 0)
	{
		nNum++;
		nPower = (int)std::pow(POWER_X, nNum);		// べき乗する(二乗や三乗など)
		if (nNum >= MAX_POINT_NUM) { nNum = MAX_POINT_NUM; }
	}
	m_nCount = nNum - 1;
	if (m_nCount < 0) { m_nCount = 0; }
	return nNum;
}

//=============================================================================
// 時間の管理
//=============================================================================
void CPoint::TimeManagement(void)
{

}
//=============================================================================
// デバック用
//=============================================================================
void CPoint::DebugKey(void)
{

}

//=============================================================================
// UIの位置設定
//=============================================================================
void CPoint::UIPosition(int nID)
{
	char *cName[MAX_PLAYER] = { "キャラ(バランス)", "キャラ(パワー)", "キャラ(スピード)", "キャラ(リーチ)" };
	D3DXVECTOR3 posIcon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posNumber = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posBg = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 sizeIcon = D3DXVECTOR3(40.0f, 30.0f, 0.0f);		// アイコンのサイズ
	D3DXVECTOR3 sizeNumber = D3DXVECTOR3(60.0f, 20.0f, 0.0f);	// 何Pかのサイズ
	D3DXVECTOR3 sizeBg = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CScene2D *pNumber = NULL;
	CScene2D *pBg = NULL;

	// 人数が指定数内 かつ プレイヤーIDが指定した番号の場合
	if (m_nNumPlayer != 2 && nID == 0)
	{
		// 1画面の位置
		if (m_nNumPlayer == 1)
		{
			//位置
			posIcon = D3DXVECTOR3(56.0f, 49.0f, 0.0f);
			posNumber = D3DXVECTOR3(85.0f, 79.0f, 0.0f);
			posBg = D3DXVECTOR3(83.0f, 79.0f, 0.0f);

			//大きさ
			sizeIcon = D3DXVECTOR3(80.0f, 70.0f, 0.0f);
			sizeNumber = D3DXVECTOR3(60.0f, 30.0f, 0.0f);
			sizeBg = D3DXVECTOR3(42.0f, 26.0f, 0.0f);
		}
		//3・4プレイ時
		else if (m_nNumPlayer == 3 || m_nNumPlayer == 4)
		{
			//位置
			posIcon = D3DXVECTOR3(42.0f, 34.0f, 0.0f);
			posNumber = D3DXVECTOR3(58.0f, 54.0f, 0.0f);
			posBg = D3DXVECTOR3(54.0f, 52.0f, 0.0f);


			//大きさ
			sizeIcon = D3DXVECTOR3(57.0f, 47.0f, 0.0f);
			sizeNumber = D3DXVECTOR3(56.0f, 35.0f, 0.0f);
			sizeBg = D3DXVECTOR3(39.0f, 24.0f, 0.0f);

		}
	}
	else if (nID == 1 && m_nNumPlayer == 3 || nID == 1 && m_nNumPlayer == 4)
	{
		// 3画面・4画面　2Ｐの位置
		posIcon = D3DXVECTOR3(685.0f, 34.0f, 0.0f);
		posNumber = D3DXVECTOR3(699.0f, 54.0f, 0.0f);
		posBg = D3DXVECTOR3(698.0f, 52.0f, 0.0f);


		//大きさ
		sizeIcon = D3DXVECTOR3(57.0f, 47.0f, 0.0f);
		sizeNumber = D3DXVECTOR3(54.0f, 35.0f, 0.0f);
		sizeBg = D3DXVECTOR3(39.0f, 24.0f, 0.0f);

	}
	else if (nID == 2 && m_nNumPlayer == 3 || nID == 2 && m_nNumPlayer == 4)
	{
		// 3画面・4画面 3Pの位置
		posIcon = D3DXVECTOR3(41.0f, 400.0f, 0.0f);
		posNumber = D3DXVECTOR3(54.0f, 420.0f, 0.0f);
		posBg = D3DXVECTOR3(54.0f, 418.0f, 0.0f);

		//大きさ
		sizeIcon = D3DXVECTOR3(57.0f, 47.0f, 0.0f);
		sizeNumber = D3DXVECTOR3(55.0f, 35.0f, 0.0f);
		sizeBg = D3DXVECTOR3(39.0f, 24.0f, 0.0f);

	}
	else if  (nID == 3 && m_nNumPlayer == 4)
	{
		// 4画面　4Pの位置
		posIcon = D3DXVECTOR3(685.0f, 400.0f, 0.0f);		//　アイコン
		posNumber = D3DXVECTOR3(699.0f, 421.0f, 0.0f);		//　ナンバー
		posBg = D3DXVECTOR3(699.0f, 418.0f, 0.0f);			//　バック

		// 大きさ
		sizeIcon = D3DXVECTOR3(57.0f, 47.0f, 0.0f);
		sizeNumber = D3DXVECTOR3(54.0f, 35.0f, 0.0f);
		sizeBg = D3DXVECTOR3(39.0f, 23.0f, 0.0f);
	}

	// 2画面
	else if (m_nNumPlayer == 2 && nID == 0)
	{
		//　1P
		posIcon = D3DXVECTOR3(190.0f, 42.0f, 0.0f);
		posNumber = D3DXVECTOR3(212.0f, 68.0f, 0.0f);
		posBg = D3DXVECTOR3(212.0f, 68.0f, 0.0f);

		//大きさ
		sizeIcon = D3DXVECTOR3(70.0f, 60.0f, 0.0f);
		sizeNumber = D3DXVECTOR3(60.0f, 25.0f, 0.0f);
		sizeBg = D3DXVECTOR3(41.0f, 25.0f, 0.0f);
	}
	else if (nID == 1 && m_nNumPlayer == 2)
	{
		// 2画面 2P
		posIcon = D3DXVECTOR3(190.0f, 406.5f, 0.0f);
		posNumber = D3DXVECTOR3(212.0f, 432.0f, 0.0f);
		posBg = D3DXVECTOR3(212.0f, 432.0f, 0.0f);

		//大きさ
		sizeIcon = D3DXVECTOR3(70.0f, 60.0f, 0.0f);
		sizeNumber = D3DXVECTOR3(55.0f, 25.0f, 0.0f);
		sizeBg = D3DXVECTOR3(41.0f, 25.0f, 0.0f);
	}

	if (m_type != CPoint::TYPE_CPU)
	{
		if (pBg == NULL)
		{	// 背景
			pBg = new CScene2D(4, CScene2D::OBJTYPE_SCENE2D);
			pBg->Init(posBg);									// 位置
			pBg->SetWidthHeight(sizeBg.x, sizeBg.y);			// サイズ
			pBg->SetCol(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.8f));		// 色
		}

		// キャラクターアイコンのロゴ
		if (m_pIcon == NULL)
		{
			int nIDIcon = 0;
			CPlayer::PLAYER_TYPE type;
			if (CGame::GetPlayer(nID) != NULL)
			{
				nIDIcon = CGame::GetPlayer(nID)->GetPlayerType();
				type = CGame::GetPlayer(nID)->GetPlayerType();
			}
			m_pIcon = CScene2D::Create(posIcon, "RANKCHARA_ICON", 3);
			m_pIcon->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / MAX_PLAYER)*(int)type), D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*(int)type)));
			m_pIcon->SetWidthHeight(sizeIcon.x, sizeIcon.y);
			m_pIcon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pIcon->SetObjType(OBJTYPE_SCENE2D);
		}

		// キャラクター番号の設定  (プレイ人数 : PLAYER_NUM2)
		pNumber = CScene2D::Create(posNumber, "RANK&PLNUM", 5);
		pNumber->SetWidthHeight(sizeNumber.x, sizeNumber.y);
		pNumber->SetTex(D3DXVECTOR2(0.5f, nID * 0.25f), D3DXVECTOR2(1.0f, (nID * 0.25f) + 0.25f));
		pNumber->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (m_type == CPoint::TYPE_CPU)
	{	// CPUの場合
		nID = 4;					// 自分の番号を5番に指定
	}
}

//=============================================================================
// ポイントの位置設定
//=============================================================================
void CPoint::PointPostion()
{
	CPlayer *pPlayer = NULL;
	D3DXVECTOR3 PlayerPos = {};

	// 位置設定
	if (CManager::GetMode() == CManager::MODE_GAME) { pPlayer = CGame::GetPlayer(m_nID); }
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL) { pPlayer = CTutorial::GetPlayer(m_nID); }


	if (pPlayer != NULL)
	{
		PlayerPos = pPlayer->GetPosition();
		m_pos = D3DXVECTOR3(PlayerPos.x + (5 * m_nCount), PlayerPos.y + 50.0f, PlayerPos.z);

		if (m_pCrown == NULL)
		{
			m_pCrown = CSceneBillBoard::Create(D3DXVECTOR3(PlayerPos.x, PlayerPos.y + 80.0f, PlayerPos.z), 20.0f, 30.0f, "crown");
			m_pCrown->SetTexture(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2((0.333f*1), 1.0f));
			m_pCrown->SetObjType(CSceneBillBoard::OBJTYPE_CROWN);
		}

		if (m_pCrown != NULL)
		{
			m_pCrown->Setpos(D3DXVECTOR3(PlayerPos.x, PlayerPos.y + 80.0f, PlayerPos.z ));
		}
	}

	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{
		if (m_apNumber[nCntPoint] != NULL)
		{	// 位置設定
			m_apNumber[nCntPoint]->SetPos(D3DXVECTOR3((m_pos.x - TIMER_SPACE * nCntPoint), m_pos.y, m_pos.z));
		}
	}
}

//=============================================================================
// 順位の位置まとめ
//=============================================================================
void CPoint::RankPos(void)
{
	D3DXVECTOR3 pos = {};

	if (m_pRank == NULL)
	{
		m_pRank = CScene2D::Create(pos, "RANK&PLNUM", 5);
		m_pRank->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.5f ,0.25f));
		m_TexMin = m_pRank->GetTex(0);
		m_TexMax = m_pRank->GetTex(1);
	}

	// 人数が指定数内 かつ プレイヤーIDが指定した番号の場合
	if (m_nNumPlayer != 2 && m_nID == 0)
	{	// 1, 3, 4画面 1Pの位置
		if (m_nNumPlayer == 1)
		{
			pos = POINT_POS_1P_ONE;
			m_RnakSize = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
		}
		if (m_nNumPlayer == 3 || m_nNumPlayer == 4)
		{
			pos = D3DXVECTOR3(POINT_POS_1P_ONE.x / 2 - 15.0f, POINT_POS_1P_ONE.y / 2 -14.0f, POINT_POS_1P_ONE.z);
			m_RnakSize = D3DXVECTOR3(70.0f, 70.0f, 0.0f);
		}
	}
	else if (m_nID == 1 && m_nNumPlayer == 3 || m_nID == 1 && m_nNumPlayer == 4)
	{	// 3画面 2P, 4画面 2Pの位置
		pos = D3DXVECTOR3(POINT_POS_4P_ONE.x - 5.0f, POINT_POS_4P_ONE.y + 270.0f, POINT_POS_4P_ONE.z);
		m_RnakSize = D3DXVECTOR3(70.0f, 70.0f, 0.0f);
	}
	else if (m_nID == 2 && m_nNumPlayer == 3 || m_nID == 2 && m_nNumPlayer == 4)
	{ // 3画面 3P, 4画面 3Pの位置
		pos = D3DXVECTOR3(POINT_POS_2P_TWO.x + 430.0f, POINT_POS_2P_TWO.y + 263.0f, POINT_POS_2P_TWO.z);
		m_RnakSize = D3DXVECTOR3(70.0f, 70.0f, 0.0f);

	}
	else if ( m_nID == 3 && m_nNumPlayer == 4)
	{	// 4画面 4Pの位置
		pos = D3DXVECTOR3(POINT_POS_4P_TWO.x - 4.0f, POINT_POS_4P_TWO.y + 265.0f, POINT_POS_4P_TWO.z);
		m_RnakSize = D3DXVECTOR3(70.0f, 70.0f, 0.0f);
	}

	else if (m_nNumPlayer == 2 && m_nID == 0)
	{	// 2画面 1P
		pos = D3DXVECTOR3(POINT_POS_1P_ONE.x - 120.0f, POINT_POS_1P_ONE.y / 2 - 10, POINT_POS_1P_ONE.z);
		m_RnakSize = D3DXVECTOR3(70.0f, 70.0f, 0.0f);
	}
	else if (m_nID == 1 && m_nNumPlayer == 2)
	{	// 2画面 2P
		pos = D3DXVECTOR3(POINT_POS_2P_TWO.x + 932.0f, POINT_POS_2P_TWO.y + 265, POINT_POS_2P_TWO.z);
		m_RnakSize = D3DXVECTOR3(70.0f, 70.0f, 0.0f);
	}

	if (m_pRank != NULL)
	{
		m_pRank->SetPosition(pos);
		m_pRank->SetWidthHeight(m_RnakSize.x, m_RnakSize.y);
	}
}

//=============================================================================
// ポイント増減時のサイズ変化
//=============================================================================
void CPoint::SizeChange(void)
{
	if (m_bSizeChange == false) { return; }

	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{
		if (m_apNumber[nCntPoint] != NULL)
		{
			if (m_bSizeChange == true)
			{
				D3DXVECTOR3 size = m_apNumber[nCntPoint]->GetSize();
				D3DXVECTOR3 pos = m_apNumber[nCntPoint]->GetPos();
				D3DXCOLOR col = m_apNumber[nCntPoint]->GetCol();
				float fSizeChangeX = 0.5f;
				float fSizeChangeY = 0.5f;
				float fPosChangeY = 1.0f;
				float fCol = 0.1f;

				if (m_bChangeFlag == false)
				{
					size.x += fSizeChangeX;
					size.y += fSizeChangeY;
					pos.y += fPosChangeY;
				}
				else if (m_bChangeFlag == true)
				{
					size.x -= fSizeChangeX;
					size.y -= fSizeChangeY;
					pos.y -= fPosChangeY;
				}

				if (m_bColChange == false)
				{
					if (m_bFlag == false)
					{
						col.r -= fCol;
						if (col.r < 0.4) { col.r = 0.4f; m_bColChange = true; }
					}
					else if (m_bFlag == true)
					{
						col.b -= fCol;
						if (col.b < 0.4) { col.b = 0.4f; m_bColChange = true; }
					}
				}
				else if (m_bColChange == true)
				{
					if (m_bFlag == false)
					{
						col.r += fCol;
						if (col.r > 1.0) { col.r = 1.0f; m_bColChange = false; }
					}
					else if (m_bFlag == true)
					{
						col.b += fCol;
						if (col.b > 1.0) { col.b = 1.0f; m_bColChange = false; }
					}
				}

				if (size.x > MAX_SIZE.x && size.y > MAX_SIZE.y) { m_bChangeFlag = true; }
				else if (size.x < DEFAULT_SIZE.x && size.y < DEFAULT_SIZE.y) { m_bChangeFlag = false; m_bSizeChange = false; }

				m_apNumber[nCntPoint]->SetSize(size);
				m_apNumber[nCntPoint]->SetCol(col);
			}
		}
	}

	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{
		if (m_apNumber[nCntPoint] != NULL)
		{
			if (m_bSizeChange == false)
			{
				m_apNumber[nCntPoint]->SetPos(D3DXVECTOR3(m_pos.x, m_fPosOld, m_pos.z));
				m_apNumber[nCntPoint]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apNumber[nCntPoint]->SetSize(DEFAULT_SIZE);

			}
		}
	}
}


//=============================================================================
// 順位のTEX変更
//=============================================================================
void CPoint::RankLogoTex(int nWinNum)
{
	// 順位の入れ替え確認
	if (m_nWinNum != nWinNum)
	{

		if (m_nWinNum < nWinNum) { m_bConfirmFlag = false; }	 // 順位が下がったら
		else if (m_nWinNum > nWinNum) { m_bConfirmFlag = true; } // 順位が上がったら

		if (m_pRank != NULL)
		{
			//if (m_TexMax == m_pRank->GetTex(1) && m_TexMin == m_pRank->GetTex(0))
			m_bRankChangeFlag = true;	// 順位入れ替わりにフラグをtrueに
			m_bFlag001 = false;

			m_nCntbConfirm = 0;
		}
		m_nWinNum = nWinNum;
	}
}

//=============================================================================
// 順位入れ替わり
//=============================================================================
void CPoint::ChangeRank(void)
{
	if (m_bRankChangeFlag == true)
	{
		if (m_pRank != NULL && m_bFlag001 == false)
		{	// 縮小
			float fSizeDown = 2.0f;
			float fRotZ = 0.4f;
			D3DXVECTOR2 size = D3DXVECTOR2(m_pRank->GetSize(0), m_pRank->GetSize(1));
			float rot = m_pRank->GetRot();

			size.x -= fSizeDown;
			size.y -= fSizeDown;

			rot -= fRotZ;

			if (size.x < 5.0f) { size.x = 5.0f; }
			if (size.y < 5.0f) { size.y = 5.0f; }

			if (size.x <= 5.0f && size.y <= 5.0f) { m_bFlag001 = true; }

			m_pRank->SetWidthHeight(size.x, size.y);
			m_pRank->SetRot(rot);
		}
		else if (m_pRank != NULL && m_bFlag001 == true)
		{	// 拡大
			float fSizeUp = 2.0f;
			float fRotZ = 0.4f;
			D3DXVECTOR2 size = D3DXVECTOR2(m_pRank->GetSize(0), m_pRank->GetSize(1));
			float rot = m_pRank->GetRot();


			if (size.x >= m_RnakSize.x && size.y >= m_RnakSize.y)
			{
				// 順位確定の処理
				ConfirmDirecting(size);
				return;
			}

			m_pRank->SetTex(D3DXVECTOR2(0.0f, 0.0f + (m_nWinNum * 0.25f)), D3DXVECTOR2(0.5f, 0.25f + (m_nWinNum * 0.25f)));
			m_TexMin = m_pRank->GetTex(0);
			m_TexMax = m_pRank->GetTex(1);

			size.x += fSizeUp;
			size.y += fSizeUp;

			rot += fRotZ;

			if (size.x > m_RnakSize.x) { size.x = m_RnakSize.x; }
			if (size.y > m_RnakSize.y) { size.y = m_RnakSize.y; }

			m_pRank->SetWidthHeight(size.x, size.y);
			m_pRank->SetRot(rot);
		}
	}
}

//=============================================================================
// 順位確定
//=============================================================================
void CPoint::ConfirmDirecting(D3DXVECTOR2 size)
{
	m_nCntbConfirm++;
	D3DXVECTOR2 sizeOld = size;

	//sizeOld = D3DXVECTOR2(m_RnakSize.x, m_RnakSize.y);
	if (m_pRank != NULL)
	{
		if (m_nCntbConfirm < 15) { sizeOld.x +=1.0f; sizeOld.y += 1.0f;}
		if (m_nCntbConfirm > 15) { sizeOld.x -= 1.0f; sizeOld.y -= 1.0f; }

		m_pRank->SetWidthHeight(sizeOld.x, sizeOld.y);
	}

	if ((m_nCntbConfirm % CONFIRM_TIME) == 0)
	{	// 順位入れ替わりを可能に
		m_bFlag001 = false;
		m_bRankChangeFlag = false;
	}
}

//=============================================================================
// 描画判定
//=============================================================================
void CPoint::SetVision(int nNumPlayer, bool bFlag)
{
	m_bDrawVision[nNumPlayer] = bFlag;
	//if (m_pCrown != NULL) { m_pCrown->SetDrawFlag(bFlag); }
}