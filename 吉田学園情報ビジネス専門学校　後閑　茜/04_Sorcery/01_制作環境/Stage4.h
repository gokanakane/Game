//=============================================================================
//
// �X�e�[�W [Stage1.h]
// Author : 
//
//=============================================================================
#ifndef _STAGE4_H_
#define _STAGE4_H_

#include "main.h"
#include "StageBase.h"

//*****************************************************************************
// �N���X�̒�`(�h���N���X)
//*****************************************************************************
class CStage4 :public CStage
{
public:
	CStage4();
	~CStage4();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	StageState m_state;

};
#endif#pragma once
