//=============================================================================
//
// Gฬแลฎ [EnemyRelative.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _ENEMYRELATIVE_H_
#define _ENEMYRELATIVE_H_

#include "main.h"
#include "enemyBase.h"

//*****************************************************************************
// }N่`
//*****************************************************************************

//*****************************************************************************
// NX@{XฬแลฎG
//*****************************************************************************
class CEnemyRelative : public CEnemy
{
public:
	CEnemyRelative();
	~CEnemyRelative();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	float m_fMoveSpeed, m_fTexAnim;
	int m_nCntAnim, m_nPatturnAnim;
};
#endif