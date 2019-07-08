//=============================================================================
//
// �^�C�g�����S���� [TitleRogo.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _TITLEROGO_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _TITLEROGO_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLEROGO_TEXTUER "data\\TEXTURE\\Title\\TitleBG1.png" //�ǂݍ��ރe�N�X�`��
#define TITLEROGO_TEXTUER1 "data\\TEXTURE\\Title\\Title001.png" //�ǂݍ��ރe�N�X�`��
#define TITLEROGO_TEXTUER2 "data\\TEXTURE\\UI\\PRESS_ENTER.png" //�ǂݍ��ރe�N�X�`��
#define TITLEROGO_TEXTUER3 "data\\TEXTURE\\Title\\Title002.png" //�ǂݍ��ރe�N�X�`��

#define TITLEROGO_POS_X (300)					   //�^�C�g������X
#define TITLEROGO_POS_Y (500)					   //�^�C�g������Y
#define TITLEROGO_WIDTH (SCREEN_WIDTH)			   //�^�C�g���̕�
#define TITLEROGO_HEIGHT (SCREEN_HEIGHT)		   //�^�C�g������
#define MAX_TITLEROGOTEX (4)
#define MAX_ANIMATION (4)

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
