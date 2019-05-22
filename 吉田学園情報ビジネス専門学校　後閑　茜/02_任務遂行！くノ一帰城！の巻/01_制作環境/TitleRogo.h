//=============================================================================
//
// �w�i���� [TitleRogo.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _TITLEROGO_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _TITLEROGO_

#include "main.h"
//*****************************************************************************
// �\����
//*****************************************************************************
typedef enum
{
	ROGO_NONE = 0,		// �������Ă��Ȃ����
	ROGO_FLASH,			// ENTER���͏��
	ROGO_MAX
} RogoState;

typedef struct
{
	D3DXCOLOR col;
	int nCntAnim;	//�A�j���[�V�����J�E���^�[
	int nPatturnAnim;//�A�j���[�V�����p�^�[��
	float nChangeArpha;//�����x�ύX
	bool bAnim;

}RogoAnim;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTitleRogo(void);
void UninitTitleRogo(void);
void UpdateTitleRogo(void);
void DrawTitleRogo(void);

RogoState*GetState(void);
#endif
