//=============================================================================
//
// 敵の眷属処理 [EnemyRelative.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _ENEMYRELATIVE_H_
#define _ENEMYRELATIVE_H_

#include "main.h"
#include "enemyBase.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス　ボスの眷属敵
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