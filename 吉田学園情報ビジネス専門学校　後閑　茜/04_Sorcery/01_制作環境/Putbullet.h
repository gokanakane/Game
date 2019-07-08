//=============================================================================
//
// リリィカルト通常魔法処理 [Putbullet.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _PUTBULLET_H_
#define _PUTBULLET_H_

#include "main.h"
#include "optionBase.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラスの定義(派生)　リリカル設置弾
//*****************************************************************************
class CPutBullet :public COption
{
public:
	typedef enum
	{
		PUTBULLETSTATE_NONE = 0,
		PUTBULLETSTATE_TIMEUP,
		PUTBULLETSTATE_MAX
	}PutBulletState;

	CPutBullet();
	~CPutBullet();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetPutBulletEmergence(bool Use) { m_bPutBulletEmergence = Use; }
	static bool GetPutBulletEmergence(void) { return m_bPutBulletEmergence; }
	static void SetPutBulletState(PutBulletState state) { m_state = state; }

private:
	D3DXVECTOR3 m_pos;
	static PutBulletState m_state;
	static bool m_bPutBulletEmergence;
	int m_nCntTime, m_nCntAnim, m_nPatturnAnim;
};
#endif
