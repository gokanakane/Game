//=============================================================================
//
// �w�i���� [TitleBG.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _TITLEBG_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _TITLEBG_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLEBG_TEXTUER "data\\TEXTURE\\BG\\TitleBG00.png" //�ǂݍ��ރe�N�X�`��
#define TITLEBG_TEXTUER1 "data\\TEXTURE\\Title\\TitlePC.png" //�ǂݍ��ރe�N�X�`��

#define TITLEBG_POS_X (0)						//�^�C�g������X
#define TITLEBG_POS_Y (0)						//�^�C�g������Y
#define TITLEBG_WIDTH (SCREEN_WIDTH)			//�^�C�g���̕�
#define TITLEBG_HEIGHT (SCREEN_HEIGHT)			//�^�C�g������
#define MAX_TEX (2)

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXCOLOR col;
	int nCntAnim;	//�A�j���[�V�����J�E���^�[
	int PatternAnim;//�A�j���[�V�����p�^�[��

}BGAnim;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTitleBG(void);
void UninitTitleBG(void);
void UpdateTitleBG(void);
void DrawTitleBG(void);

#endif
