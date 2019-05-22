//=============================================================================
//
// �V�[��2D�|���S������ [scene2d.h]
// Author : 
//
//=============================================================================
#ifndef _SCENE2D_H
#define _SCENE2D_H

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_SIZE (15.0f)
//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X�i�h���j
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 3);
	~CScene2D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D*Create(void);
	void SetScene2D(D3DXVECTOR3 pos, float sizeW, float sizeH);
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void);
	void BindTexture(LPDIRECT3DTEXTURE9 Texture);
	void SetScroll(int nCnt,float fSpeed);
	void SetAlpha(D3DXCOLOR col);
	void SetColor(D3DXCOLOR col);
	void SetAnimX(int MaxPattarn, int MaxPattarnY, int nPattarn);	//X���ł݈̂ړ�����A�j���[�V����
	void SetAnimY(int MaxPattarn, int MaxPattarnY, int nPattarn);	//Y���ł݈̂ړ�����A�j���[�V����
	void SetCharaAnim(int nPattarn, float TexsliceY);
	void SetSize(float sizeW, float sizeH);
	void SetScene2DLeftCenter(D3DXVECTOR3 pos, float sizeW, float sizeH);//���𒆐S���W�ɂ���|���S���̈ʒu�ݒ�
	void SetRotation(float sizeW, float sizeH, float Angle);

protected:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

private:
	D3DXVECTOR3	m_pos;				// �|���S���̈ʒu�A��]
	int m_TexNum;
	float m_fWidth, m_fHeight, m_fAngle, m_fLenge;		//�����A�c���A�p�x�A����
};

#endif
