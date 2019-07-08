//=============================================================================
//
// �w�i���� [Title.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _TITLE_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _TITLE_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLEROGO_TEXTUER "data\\TEXTURE\\UI\\Title000.png"			//�ǂݍ��ރe�N�X�`��
#define TITLEROGO_TEXTUER1 "data\\TEXTURE\\UI\\PRESS_ENTER.png"		//�ǂݍ��ރe�N�X�`��
#define TITLEROGO_POS_X (300)										//�^�C�g������X
#define TITLEROGO_POS_Y (500)										//�^�C�g������Y
#define TITLEROGO_WIDTH (SCREEN_WIDTH)								//�^�C�g���̕�
#define TITLEROGO_HEIGHT (SCREEN_HEIGHT)							//�^�C�g������
#define MAX_TEX (2)
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
	float nChangeArpha;//�����x�ύX
	bool bAnim;

}RogoAnim;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif
