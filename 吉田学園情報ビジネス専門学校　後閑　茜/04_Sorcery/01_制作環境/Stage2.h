//=============================================================================
//
// �X�e�[�W2 [Stage2.h]
// Author : 
//
//=============================================================================
#ifndef _STAGE2_H_
#define _STAGE2_H_

#include "main.h"
#include "StageBase.h"

//*****************************************************************************
// �N���X�̒�`(�h���N���X)
//*****************************************************************************
class CStage2 :public CStage
{
public:
	CStage2();
	~CStage2();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	StageState m_state;

};
#endif