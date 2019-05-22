//=============================================================================
//
// ステージベース[Stage.h]
// Author : 
//
//=============================================================================
#ifndef _STAGEBASE_H_
#define _STAGEBASE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMYPOS_INITIAL (SCREEN_WIDTH + DEFOLT_SIZE)
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
class CEnemy;

//*****************************************************************************
// クラスの定義
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
	static void SetBossEmergence(bool bEmergence) { m_bBossEmergence = bEmergence; }//ステージにボスが出現しているかのフラグ

protected:
	static CBg *m_pBg;
	static bool m_bBossEmergence;

private:
	
};
#endif // !_STAGE_H_
