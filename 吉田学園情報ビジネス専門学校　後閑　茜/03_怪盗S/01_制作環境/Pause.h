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
// �}�N����`
//*****************************************************************************
#define MAX_TEX (5)													 //�e�N�X�`���̐�
#define PAUSECONRINUE_TEXTUER  "data\\TEXTURE\\Pause\\Continue.png"	//�ǂݍ��ރe�N�X�`��
#define PAUSERETRY_TEXTUER  "data\\TEXTURE\\Pause\\Retry.png"		//�ǂݍ��ރe�N�X�`��
#define PAUSEQUIT_TEXTUER  "data\\TEXTURE\\Pause\\Quit.png"			//�ǂݍ��ރe�N�X�`��
#define PAUSE_TEXTUER "data\\TEXTURE\\Tutorial\\Tutorial001.png"	//�ǂݍ��ރe�N�X�`��
#define PAUSEMASK_TEXTURE " "
#define PAUSEBG_POS_X (630)											//�|�[�Y�w�i����X
#define PAUSEBG_POS_Y (180)											//�|�[�Y�w�i����Y
#define PAUSEBG_WIDTH (990)											//�|�[�Y�w�i�̕�
#define PAUSEBG_HEIGHT (580)										//�|�[�Y�w�i����
#define PASUSE_WIDTH (110.0f)										//���S�̊Ԋu
#define MAX_MENU (3)												//�I�����̐�
#define MAX_ANIMATION (4)											//�A�j���[�V�����p�^�[��

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
