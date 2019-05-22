//=============================================================================
//
// �����L���O���S���� [rankinglogo.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _RANKINGLOGO_H_
#define _RANKINGLOGO_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene2d.h"	// �V�[��2D

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_RANK_LOGO	(6)		// ���S�̍ő吔

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRnkingLogo : public CScene2D
{// �����L���O���S�i�e�FCScene2D�j
public:
	CRnkingLogo();								// �R���X�g���N�^
	~CRnkingLogo();								// �f�X�g���N�^

	static HRESULT Load(void);					// ���[�h
	static void Unload(void);					// �A�����[�h
	static CRnkingLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTexNum);		// ����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);					// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

private:
	float m_fColA;								// �����x�̒���

	//	�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_RANK_LOGO];		// �e�N�X�`�����ւ̃|�C���^
	D3DXVECTOR3 m_size;							// �T�C�Y�̑傫��


protected:

};

#endif