//*****************************************************************************
//
//				�v���X�{�^���̏���[press.h]
//				Auther : Shun Yokomichi
//
//*****************************************************************************
#ifndef _PRESS_H_
#define _PRESS_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2D.h"		// �V�[��2D

//*****************************************************************************
//		�}�N����`
//*****************************************************************************
#define MAX_TEX_PRESS	(10)		// �ő吔

//*****************************************************************************
//		�N���X��`(�|���S��)
//*****************************************************************************
class CPress : public CScene2D
{
public:
	typedef enum
	{
		TYPE_NONE = 0,		// �����Ȃ����
		TYPE_TRANSPARENCE,	// �s�������瓧��(����)
		TYPE_OPAQUE,		// ��������s����(����)
		TYPE_MANUAL,		// �����I�ɓ����ɂ���4
		TYPE_MAX			// ����
	}TYPE;

	CPress();
	~CPress();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nTex, float rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetType(TYPE type)
	{
		m_type = type;
	}

	void SetTex(int nTex)
	{
		CScene2D::BindTexture(m_pTexture[nTex]);
	}

	// �ÓI�����o�֐�
	static CPress * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nTex, float rot);
	static HRESULT Load(void);	// �ǂݍ��ފ֐�(�e�N�X�`��)
	static void Unload(void);	// �J������֐�(�e�N�X�`��)

private:
	float m_fColA;		// �����x�ۊǗp
	TYPE m_type;		// �����x�̃^�C�v�Ǘ��p

						// �ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX_PRESS];
};

#endif
