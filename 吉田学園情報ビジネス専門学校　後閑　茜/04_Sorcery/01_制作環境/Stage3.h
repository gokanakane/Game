//=============================================================================
//
// ステージ [Stage1.h]
// Author : 
//
//=============================================================================
#ifndef _STAGE3_H_
#define _STAGE3_H_

#include "main.h"
#include "StageBase.h"

//*****************************************************************************
// クラスの定義(派生クラス)
//*****************************************************************************
class CStage3 :public CStage
{
public:
	CStage3();
	~CStage3();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	StageState m_state;

};
#endif