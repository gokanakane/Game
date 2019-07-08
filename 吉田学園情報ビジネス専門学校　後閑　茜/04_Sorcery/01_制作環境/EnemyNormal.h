//=============================================================================
//
// �ʏ�G���� [EnemyNormal.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _ENEMYNORMAL_H_
#define _ENEMYNORMAL_H_

#include "main.h"
#include "enemyBase.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X�@�ʏ�G
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