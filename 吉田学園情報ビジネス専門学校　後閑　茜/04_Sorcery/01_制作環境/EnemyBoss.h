//=============================================================================
//
// �{�X�G���� [EnemyBoss.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _ENEMYBOSS_H_
#define _ENEMYBOSS_H_

#include "main.h"
#include "enemyBase.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X�@�{�X�G
//*****************************************************************************
class CEnemyBoss : public CEnemy
{
public:
	typedef enum
	{
		BOSSENEMYLIFESTATE_NONE = 0,
		BOSSENEMYLIFESTATE_HALF,
		BOSSENEMYLIFESTATE_MAX
	}BossEnemyState;

	CEnemyBoss();
	~CEnemyBoss();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	BossEnemyState m_state;
	int m_nCntAnim, m_nPatturnAnim;
};
#endif