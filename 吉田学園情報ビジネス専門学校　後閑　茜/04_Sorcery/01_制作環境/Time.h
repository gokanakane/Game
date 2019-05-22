//=============================================================================
//
// �V�[��2D�|���S������ [scene2d.h]
// Author : 
//
//=============================================================================
#ifndef _TIME_H
#define _TIME_H

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TIME (3)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;
//*****************************************************************************
// �N���X�i�h���j
//*****************************************************************************
class CTime : public CScene
{
public:
	typedef enum
	{//���Ԃ̏��
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
