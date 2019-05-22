//=============================================================================
//
// 時間処理 [bullet.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "scene.h"
#include "time.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
int CTime::m_nTimeData[MAX_TIME] = {};
int CTime::m_nTime = 0;
CTime::TimeState CTime::m_Timestate = CTime::TIMESTATE_NONE;

//=============================================================================
// コンストラクタ
//=============================================================================
CTime::CTime():CScene(5)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_nTimeData[nCnt] = 0;
		m_apNumber[nCnt] = NULL;
	}
	m_nTime = 0;
	m_Timestate = TIMESTATE_NONE;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTime::~CTime() {}
//=============================================================================
// 時間の生成
//=============================================================================
CTime *CTime::Create(void)
{
	CTime *pTime = NULL;

	if (pTime == NULL)
	{
		pTime = new CTime;
		pTime->Init();
	}

	return pTime;
}
//=============================================================================
// 時間の初期化処理
//=============================================================================
HRESULT CTime::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create();
		m_apNumber[nCnt]->Init();
		m_apNumber[nCnt]->SetPos(D3DXVECTOR3(1150.0f, 100.0f, 0.0f), nCnt,20.0f,20.0f);
		m_nTimeData[nCnt] = 0;
	}

	m_nTime = 0;

	m_Timestate = TIMESTATE_NORMAL;

	AddTime();

	return S_OK;
}

//=============================================================================
// 時間の終了処理
//=============================================================================
void CTime::Uninit(void)
{
	//m_apNumberを破棄（ポリゴンが破棄されただけでTime自体は破棄されていない）
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();

			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = NULL;
		}
	}

	//時間の破棄
	Release();
}
//=============================================================================
// 時間の更新処理
//=============================================================================
void CTime::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_apNumber[nCnt]->Update();
		m_apNumber[nCnt]->SetNumber(m_nTimeData[nCnt]);
	}

	if (m_Timestate == TIMESTATE_NORMAL)
	{
		m_nTime++;

		if ((m_nTime % 60) == 0)
		{
			for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
			{
				AddTime();

				m_apNumber[nCnt]->Update();
			}
		}
	}
}
//=============================================================================
// 時間の描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}
//=============================================================================
// 時間の加算
//=============================================================================
void CTime::AddTime(void)
{
	int nNum = 1000;	//時間の桁数+1桁
	int nNum1 = 100;	//時間の桁数
	int nTime;

	nTime = m_nTime/60;

	/*格納する数字を計算*/
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_nTimeData[nCnt] = (nTime % nNum) / nNum1;
		
		//桁数を１桁減らす
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;

	}
}
//=============================================================================
// 時間の設定
//=============================================================================
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;

}