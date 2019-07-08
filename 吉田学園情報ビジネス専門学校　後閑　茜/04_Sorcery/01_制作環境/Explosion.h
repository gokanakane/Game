//=============================================================================
//
// �������� [Explosion.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_EXPLOSION "data\\TEXTURE\\Effect\\explosion000.png"
#define MAX_ANIMATION (8)
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// �N���X�i�h���j
//*****************************************************************************
class CExplosion : public CScene2D
{
public:
	CExplosion();
	~CExplosion();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CExplosion *Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	int m_nCntAnim;							//�A�j���[�V�����J�E���^�[
	int m_nPatturnAnim;						//�A�j���[�V�����p�^�[����
};

#endif
