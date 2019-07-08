//=============================================================================
//
// �e���� [bullet.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET		(128)		// �e�̍ő吔
#define BULLET_TEXTUER "data\\TEXTURE\\UI\\honou.png"
#define BULLET_TEXTUER1 "data\\TEXTURE\\UI\\honou2.png"
#define POS_Y (620)
#define BULLET_MOVE (1.0f)
#define BULLET_PATTERN		(5)
#define MAX_BULLET_TYPE (2)

//*****************************************************************************
// �e�̎��
//*****************************************************************************
typedef enum
{//�񋓌^
	BULLETTYPE_PLAYER = 0,//�v���C���[�̒e
	BULLETTYPE_EMEMY,	 //�G�̒e
	BULLET_MAX
}BULLETTYPE;
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	int nLife; //�e�̎���
	BULLETTYPE type;
	bool bUse;//�g���Ă��邩�ǂ���

}Bullet;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,int Life);

#endif
