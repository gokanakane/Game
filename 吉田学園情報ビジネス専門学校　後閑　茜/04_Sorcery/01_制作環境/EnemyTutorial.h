//=============================================================================
//
// �`���[�g���A���p�G���� [EnemyTutorial.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _ENEMYTUTORIAL_H_
#define _ENEMYTUTORIAL_H_

#include "main.h"
#include "enemyBase.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X�@�`���[�g���A���p
//*****************************************************************************
class CEnemyTutorial : public CEnemy
{
public:
	CEnemyTutorial();
	~CEnemyTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int m_nCntAnim, m_nPatturnAnim;
};
#endif