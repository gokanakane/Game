//=============================================================================
//
// �X�e�[�W�x�[�X[Stage.h]
// Author : 
//
//=============================================================================
#ifndef _STAGEBASE_H_
#define _STAGEBASE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMYPOS_INITIAL (SCREEN_WIDTH + DEFOLT_SIZE)
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBg;
class CEnemy;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CStage : public CScene
{
public:
	typedef enum
	{
		STAGESTATE_NOBOSSEMERGENCE = 0,
		STAGESTATE_BOSSEMERGENCE,
		STAGESTATE_MAX
	}StageState;

	CStage();
	virtual ~CStage();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void SetBossEmergence(bool bEmergence) { m_bBossEmergence = bEmergence; }//�X�e�[�W�Ƀ{�X���o�����Ă��邩�̃t���O

protected:
	static CBg *m_pBg;
	static bool m_bBossEmergence;

private:
	
};
#endif // !_STAGE_H_
