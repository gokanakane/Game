//=============================================================================
//
// リザルトスコア処理 [ResultScore.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "scene.h"
#include "scoreBase.h"
#include "ResultScore.h"
#include "time.h"
#include "ranking.h"
#include "fade.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================

//*****************************************************************************
// ▽class CResultScore
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CResultScore::CResultScore()
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}
	m_col = DEFALT_COL_WHITE;
	m_Alpha = 0.1f;
}
//=============================================================================
// デストラクタ
//=============================================================================
CResultScore::~CResultScore() {}
//=============================================================================
// スコアの初期化処理
//=============================================================================
HRESULT CResultScore::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create();
		m_apNumber[nCnt]->SetPos(D3DXVECTOR3(750.0f, 470.0f, 0.0f), nCnt, 30.0f, 60.0f);
		m_apNumber[nCnt]->SetCol(m_col);
		m_nScoreData[nCnt] = 0;
	}

	SetLastScore(CManager::GetScore());
	return S_OK;
}

//=============================================================================
// スコアの終了処理
//=============================================================================
void CResultScore::Uninit(void)
{
	//最終スコアをマネージャーに渡しておく
	CManager::SetScore(m_nScore);

	//m_apNumberを破棄（ポリゴンが破棄されただけでScore自体は破棄されていない）
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();

			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = NULL;
		}
	}
}
//=============================================================================
// スコアの更新処理
//=============================================================================
void CResultScore::Update(void)
{
	m_col.a += m_Alpha;
	if (m_col.a >= 1.0f)
	{
		m_col.a = 1.0f;
	}
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->Update();
		m_apNumber[nCnt]->SetNumber(m_nScoreData[nCnt]);
		m_apNumber[nCnt]->SetCol(m_col);
	}
}
//=============================================================================
// スコアの描画処理
//=============================================================================
void CResultScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}
//=============================================================================
// 最終スコアの表示
//=============================================================================
void CResultScore::SetLastScore(int nScore)
{
	int nNum = 100000000;	//スコアの桁数+1桁
	int nNum1 = 10000000;	//スコアの桁数

	m_nScore = nScore;

	/*格納する数字を計算*/
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_nScoreData[nCnt] = (m_nScore % nNum) / nNum1;

		//桁数を１桁減らす
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}

}