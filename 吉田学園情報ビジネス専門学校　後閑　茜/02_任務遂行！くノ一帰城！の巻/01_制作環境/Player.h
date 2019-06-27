//=============================================================================
//
// �v���C���[���� [Player.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PLAYER_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _PLAYER_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAXPLAYER_LIFE (3)
#define PLAYER_MOVE (4.0f)
#define PLAYER_PATTERN (4)
#define PLAYER_TEXTUER "data\\TEXTURE\\Charactor\\player001.png"
#define PLAYER_TEXTUER1 "data\\TEXTURE\\Charactor\\player002.png"

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
	D3DXVECTOR3 pos;	//���݂̈ʒu
	D3DXVECTOR3 posold;	//�O��̈ʒu
	D3DXVECTOR3 move;	//�ړ�
	int nLife;			//�̗�
	int nPatternAnim;	//�A�j���[�V�����p�^�[��
	int nCntAnim;		//�A�j���[�V�����J�E���^�[
	int nCntState;		//�v���C���[�̏�ԃJ�E���^�[
	int nDirectionMove; //0:�E�����@1�F������
	int CntColor;		//�_�ł̃J�E���^
	int ChengeColor;	//�_�ł̓����x
	bool bJump;			//�W�����v�̎g�p��
	bool bDisp;			//�v���C���[�̎g�p��
	bool bWalk;			//���s����
	PLAYERSTATE state;  //�v���C���[�̏��


}Player;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void HitPlayer(int nDamage);
Player*GetPlayer(void);
#endif
