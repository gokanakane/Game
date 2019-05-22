//=============================================================================
//
// �w�i���� [Pause.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PAUSE_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _PAUSE_H_

#include "main.h"
#include "Game.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	PAUSESTATE_NONE = 0,
	PAUSESTATE_CONTINUE,
	PAUSESTATE_RETRY,
	PAUSESTATE_QUIT,
	PAUSESTATE_MAX
} PAUSESTATE;
typedef enum
{
	PAUSESTATECOLOR_NONE = 0,
	PAUSESTATECOLOR_CONTINUE,
	PAUSESTATECOLOR_RETRY, 
	PAUSESTATECOLOR_QUIT,
	CONTINUSTATE_MAX

} COLORSTATE;

typedef struct
{
	bool bAnim;			//�A�j���[�V������
	D3DXVECTOR3 pos;	//�ʒu
	float CntMove;		//�ړ��ʂ̃J�E���^�[
	float ChengeMove;	//�ړ���
	int CntAnim;		//�A�j���[�V�����J�E���^�[
	int PatturnAnim;	//�A�j���[�V�����p�^�[��

}Pause;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
#endif
