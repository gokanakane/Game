//=============================================================================
//
// 通常敵処理 [EnemyNormal.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _ENEMYNORMAL_H_
#define _ENEMYNORMAL_H_

#include "main.h"
#include "enemyBase.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス　通常敵
//*****************************************************************************
class CEnemyNormal : public CEnemy
{
public:
	CEnemyNormal();
	~CEnemyNormal();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	float m_fMoveSpeed;
	int m_nCntAnim, m_nPatturnAnim;
};
#endif