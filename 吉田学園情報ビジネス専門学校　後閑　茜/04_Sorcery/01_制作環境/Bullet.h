//=============================================================================
//
// �e���� [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_MOVE (10.0f)
#define TEXTURE_BULLET "data\\TEXTURE\\Bullet\\bullet000.png"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CEffect;

//*****************************************************************************
// �N���X�i�h���j
//*****************************************************************************
class CBullet : public CScene2D
{
public:
	typedef enum
	{//�e�̎�ރ^�C�v
		BULLETTYPE_NONE = 0,
		BULLETTYPE_PLAYER,		//�ʏ�e
		BULLETTYPE_DRAIN,		//�z���e
		BULLETTYPE_ENEMY,
		BULLETTYPE_MAX,
	}BULLETTYPE;

	CBullet();
	~CBullet();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos, BULLETTYPE type,float direction);
	void SetBullet(D3DXVECTOR3 pos, int nLife);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;					//���L�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;										//�ʒu
	int m_nLife;											//�e�̔�Ԓ���
	float m_moveDirection;									//�ړ�����
	BULLETTYPE m_BulletType;								//�e�̎��
	CEffect *m_pEffect;										//�G�t�F�N�g
	float m_pos_x, m_pos_y, m_fAngle, m_move_x, m_move_y;	//X�̒����EY�̒����E�p�x�EX�̈ړ��ʁEY�̈ړ���
};

#endif
