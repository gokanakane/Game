//=============================================================================
//
// �Q�[������ [Game.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CScore;
class CPause;
class CUi;
class CStage;
class COption;

//*****************************************************************************
// �N���X
//*****************************************************************************
class CGame
{
public:
	typedef enum
	{
		GAMESTATE_NONE = 0, //�������Ă��Ȃ�
		GAMESTATE_NORMAL,	//�ʏ�
		GAMESTATE_CLEAR,
		GAMESTATE_OVER,
		GAMESTATE_MAX		//�ő�l
	}GAMESTATE;

	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetGameState(GAMESTATE gamestate);

private:
	static CPlayer *m_pPlayer;
	static CScore *m_pScore;
	static CPause *m_pPause;
	static CUi *m_pUi;
	static CStage *m_pStage;
	static int m_nCntState;
	GAMESTATE m_GameState;
	CManager::StageSelectState m_SelectStage;
	int nCntFade = 0;

};
#endif