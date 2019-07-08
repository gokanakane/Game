//=============================================================================
//
// �|�[�Y���� [Pause.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "Game.h"
#include "fade.h"
#include "input.h"
#include "Pause.h"
#include "PauseBG.h"
#include "PauseContinue.h"
#include "PauseQuit.h"
#include "PauseRetry.h"
#include "sound.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PAUSESTATE g_PauseMode;
int g_nSelectManu;

//=============================================================================
// �|�[�Y����������[InitPolygon]
//=============================================================================
void InitPause(void)
{
	g_nSelectManu = 0;

	InitPauseBG();
	InitPauseContinue();
	InitPauseQuit();
	InitPauseRetry();
}
//=============================================================================
//�|�[�Y�I������ [UninitPolygon]
//=============================================================================
void UninitPause(void)
{
	UninitPauseBG();
	UninitPauseContinue();
	UninitPauseQuit();
	UninitPauseRetry();
}

//=============================================================================
// �|�[�Y�X�V����[UpdataPolygon]
//=============================================================================
void UpdatePause(void)
{
	FADE g_Fade;
	g_Fade = GetFade();

	if (GetKeyboardTrigger(DIK_S) == true)
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectManu = (g_nSelectManu + 1) % 3;
	}

	if (GetKeyboardTrigger(DIK_W) == true)
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectManu = (g_nSelectManu + 2) % 3;
	}

	if (g_nSelectManu == 0)
	{
		SetContinu(CONTINUSTATE_SELECT);
		SetRetry(RETRYSTATE_NOSELECT);
		SetQuit(QUITSTATE_NOSELECT);
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				g_PauseMode = PAUSESTATE_CONTINUE;

			}
		}
	}
	if (g_nSelectManu == 1)
	{
		SetContinu(CONTINUSTATE_NOSELECT);
		SetRetry(RETRYSTATE_SELECT);
		SetQuit(QUITSTATE_NOSELECT);
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				g_PauseMode = PAUSESTATE_RETRY;
			}
		}

	}
	if (g_nSelectManu == 2)
	{
		SetContinu(CONTINUSTATE_NOSELECT);
		SetRetry(RETRYSTATE_NOSELECT);
		SetQuit(QUITSTATE_SELECT);

		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				g_PauseMode = PAUSESTATE_QUIT;
			}
		}

	}

	switch (g_PauseMode)
	{
	case PAUSESTATE_CONTINUE:
		g_PauseMode = PAUSESTATE_NONE;
		SetPause(false);
		break;

	case PAUSESTATE_RETRY:
		g_PauseMode = PAUSESTATE_NONE;
		SetFade(MODE_GAME);
		break;

	case PAUSESTATE_QUIT:
		g_PauseMode = PAUSESTATE_NONE;
		SetFade(MODE_TITLE);
		break;	

	}

	UpdatePauseBG();
	UpdatePauseContinue();
	UpdatePauseQuit();
	UpdatePauseRetry();

}
//=============================================================================
// �|�[�Y�`�ʏ���[DrawPolygon]
//=============================================================================
void DrawPause(void)
{
	DrawPauseBG();
	DrawPauseContinue();
	DrawPauseQuit();
	DrawPauseRetry();
}