//=============================================================================
//
// �G���� [enemy.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ENEMY	(128)	// �G�̍ő吔
#define	MAX_TYPE_ENEMY		(4)												// �G�̎��
#define ENEMY_TEXTURE0		"data\\TEXTURE\\Charactor\\enemy000_a.png"		// �G�̃e�N�X�`���̖��O0
#define ENEMY_TEXTURE1		"data\\TEXTURE\\Charactor\\enemy001_a.png"		// �G�̃e�N�X�`���̖��O1
#define ENEMY_TEXTURE2		"data\\TEXTURE\\Charactor\\enemy002_a.png"		// �G�̃e�N�X�`���̖��O2
#define ENEMY_TEXTURE3		"data\\TEXTURE\\Charactor\\enemy003_a.png"		// �G�̃e�N�X�`���̖��O3
#define PLAYER_PATTERN		(2)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{//�񋓌^
	ENEMYSTATE_NOMAL = 0, //�ʏ��ԁi0�j
	ENEMYSTATE_DAMAGE,	  //�_���[�W��ԁi1�j
	ENEMYSTATE_MAX		  //�G�̏�Ԃ̑����i2�j

}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	int nType;		//���
	ENEMYSTATE state;//�G�̏��
	int nCntState;	//��Ԃ̊Ǘ�
	int nLife;		//�̗�
	int nCnt;
	bool bUse;		//�g�p���Ă��邩�ǂ���
	int Cntmove;	//�G�̈ړ��J�E���^�[
	int ChengeMove;	//�ړ���

}Enemy;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType, int ChengeMove,int Life);
Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif
