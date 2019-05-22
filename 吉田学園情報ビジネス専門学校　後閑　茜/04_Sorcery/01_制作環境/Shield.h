//=============================================================================
//
// オプション [option.h]
// Author : 
//
//=============================================================================
#ifndef _SHIELD_H_
#define _SHIELD_H_

#include "main.h"
#include "optionBase.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラスの定義(派生)　カーネリアン盾
//*****************************************************************************
class CShield : public COption
{
public:
	typedef enum
	{
		SHIELDSTATE_NONE = 0,
		SHIELDSTATE_DAMAGE,
		SHIELDSTATE_BREAK,
		SHIELDSTATE_MAX
	}ShieldState;

	CShield();
	~CShield();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetDamage(int Damage);
	static bool GetShieldEmergence(void) { return m_bShieldEmergence; }

private:
	int m_nLife;				//盾の耐久
	int m_nCntState;			//色変え
	ShieldState m_state;		//盾の状況
	static bool m_bShieldEmergence;	//盾の使用状況
};

#endif