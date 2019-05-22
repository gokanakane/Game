//=============================================================================
//
// �e���� [Migawari.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _MIGAWARI_H_
#define _MIGAWARI_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MIGAWARI_MAX_LIFE (5)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{//�񋓌^
	MIGAWARISTATE_NOMAL = 0, //�ʏ��ԁi0�j
	MIGAWARISTATE_DAMAGE,	  //�_���[�W��ԁi1�j
	MIGAWARISTATE_DEATH,	  //���S
	MIGAWARISTATE_MAX		  //�G�̏�Ԃ̑����i2�j

}MigawariState;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posold;	//�O��̈ʒu
	D3DXVECTOR3 move;	//�ړ�
	MigawariState state;//�g����̏��
	int nCntState;		//��Ԃ̊Ǘ�
	int type;			//���
	int nLife;			//�ϋv�l
	bool bUse;			//�g���Ă��邩�ǂ���

}Migawari;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMigawari(void);
void UninitMigawari(void);
void UpdateMigawari(void);
void DrawMigawari(void);
void HitMigawari(int nDamage);
void SetMigawari(D3DXVECTOR3 pos,int Type);

Migawari*GetMigawari(void);
#endif
