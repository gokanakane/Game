//=============================================================================
//
// �^�C�g���t���[������ [titleframe.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _TITLEFRAME_H_
#define _TITLEFRAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene2d.h"	// �V�[��2D

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_FRAME		(2)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTitleFrame : public CScene2D
{// �^�C�g���t���[���i�e�FCScene2D�j
public:
	CTitleFrame();								// �R���X�g���N�^
	~CTitleFrame();								// �f�X�g���N�^

	static HRESULT Load(void);					// ���[�h
	static void Unload(void);					// �A�����[�h
	static CTitleFrame *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float rot, int nTex);		// ����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float rot);					// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

private:
	D3DXVECTOR3 m_movesize;						// �T�C�Y�̑傫���ύX
	D3DXVECTOR3 m_msize;						// �T�C�Y�̑傫���ύX

												// �ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_FRAME];		// �e�N�X�`�����ւ̃|�C���^


protected:

};

#endif