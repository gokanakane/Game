//=============================================================================
//
// シーン2Dポリゴン処理 [scene2d.h]
// Author : 
//
//=============================================================================
#ifndef _TIME_H
#define _TIME_H

#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TIME (3)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;
//*****************************************************************************
// クラス（派生）
//*****************************************************************************
class CTime : public CScene
{
public:
	typedef enum
	{//時間の状態
		TIMESTATE_NONE=0,
		TIMESTATE_NORMAL,
		TIMESTATE_END,
		TIMESTATE_MAX
	}TimeState;

	CTime();
	~CTime();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTime*Create(void);
	static void AddTime(void);
	void SetTime(int nTime);
	static int GetTime(void) { return m_nTime; }

private:
	CNumber *m_apNumber[MAX_TIME];
	static int m_nTime;
	static int m_nTimeData[MAX_TIME];
	static TimeState m_Timestate;
};

#endif
