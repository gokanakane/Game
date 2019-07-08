//=============================================================================
//
// アレイスタ処理 [Areista.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _AREISTA_H_
#define _AREISTA_H_

#include "main.h"
#include "playerBase.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;

//*****************************************************************************
// クラス（派生）アレイスタ
//*****************************************************************************
class CAreista : public CPlayer
{
public:
	CAreista();
	~CAreista();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nCntSkillTime;
};
#endif