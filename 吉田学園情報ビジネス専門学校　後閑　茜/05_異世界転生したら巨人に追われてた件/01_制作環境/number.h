//=============================================================================
//
// �������� [number.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene2d.h"	// �V�[��2D
#include "scene3d.h"	// �V�[��3D

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUMBER2D_SIZE_X	(30)		// �傫���iX)
#define NUMBER2D_SIZE_Y	(30)		// �傫���iY)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CNumber
{// ����
public:
	CNumber();									// �R���X�g���N�^
	~CNumber();									// �f�X�g���N�^

	static HRESULT Load(void);					// ���[�h
	static void Unload(void);					// �A�����[�h

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`�����ւ̃|�C���^

};

class CNumber2D : public CScene2D, CNumber
{// ����2D�i�e�FCScene2D�j
public:
	CNumber2D();								// �R���X�g���N�^
	~CNumber2D();								// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);		// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

private:

protected:

};

class CNumber3D : public CScene3D, CNumber
{// ����3D�i�e�FCScene3D�j
public:
	CNumber3D();								// �R���X�g���N�^
	~CNumber3D();								// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, CScene3D::SCENE3DTYPE screenType);				// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

private:

protected:

};

#endif