//=============================================================================
//
// カーネリアン処理 [Karnerian.h]
// Author :Gokan Akane 
//
//=============================================================================
#ifndef _KARNERIAN_H_
#define _KARNERIAN_H_

#include "main.h"
#include "playerBase.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
//*****************************************************************************
// クラス（派生）カーネリアン
//*****************************************************************************
class CKarnerian : public CPlayer
{
public:
	CKarnerian();
	~CKarnerian();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetSheld(bool Set) { m_bShield = Set; }

private:
	int m_nCntSkillTime;
	static bool m_bShield;
};

#endif
