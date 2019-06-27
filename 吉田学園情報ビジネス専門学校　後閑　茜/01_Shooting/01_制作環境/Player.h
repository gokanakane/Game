//=============================================================================
//
// DirectX���^���� [Player.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PLAYER_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _PLAYER_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAXPLAYER_LIFE (3)//�ő�̗�
#define PLAYER_TEXTUER "data\\TEXTURE\\Charactor\\player000_a.png" //�ǂݍ��ރe�N�X�`��
#define PLAYER_MOVE (6.0f)							  //�v���C���[�̈ړ���

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{//�񋓌^
	PLAYERSTATE_APPEAR = 0,//�o�����,�i0�j
	PLAYERSTATE_NOMAL, //�ʏ��ԁi1�j
	PLAYERSTATE_DAMAGE,	  //�_���[�W��ԁi2�j
	PLAYERSTEAT_DEATH,//�G�̎��S��ԁi3�j
	PLAYERSTATE_MAX		  //�G�̏�Ԃ̑����i4�j

}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	PLAYERSTATE state;//�v���C���[�̏�
	int nCntState;
	int nLife;
	bool bDisp;//�\�����邩���Ȃ���

}Player;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

Player *GetPlayer(void);
void HitPlayer(int nDamage);

#endif
