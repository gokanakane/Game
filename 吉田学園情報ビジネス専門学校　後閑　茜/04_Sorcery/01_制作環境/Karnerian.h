//=============================================================================
//
// �J�[�l���A������ [Karnerian.h]
// Author :Gokan Akane 
//
//=============================================================================
#ifndef _KARNERIAN_H_
#define _KARNERIAN_H_

#include "main.h"
#include "playerBase.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
//*****************************************************************************
// �N���X�i�h���j�J�[�l���A��
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
