//=============================================================================
//
// �e���� [Item.h]
// Author :
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ITEM		(128)		// �e�̍ő吔
#define ITEM_TEXTUER "data\\TEXTURE\\Item000.png"
#define ITEM_TEXTUER1 "data\\TEXTURE\\Item001.png"
#define ITEM_TEXTUER2 "data\\TEXTURE\\Item002.png"
#define ITEM_TEXTUER3 "data\\TEXTURE\\makimono.png"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
//typedef enum
//{//�񋓌^
//	ITEMTYPE_COIN = 0,//�R�C��
//	ITEMTYPE_MAX
//
//}ITEMTYPE;

typedef struct 
{
	D3DXVECTOR3 pos; //�ʒu 
	D3DXVECTOR3 move;//�ړ���
	D3DXCOLOR col;	 //�F
	int nCntAnim;	 //�A�j���[�V�����J�E���^�[
	int nPatternAnim;//�p�^�[��No
	int nType;		//�A�C�e���̃^�C�v
	bool bUse;		 //�g���Ă��邩�ǂ���

}ITEM;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos,int Type);

bool CollsionItem(D3DXVECTOR3 *pPos);
void DeleteItem(int nCnt);
ITEM*GetItem(void);
#endif
