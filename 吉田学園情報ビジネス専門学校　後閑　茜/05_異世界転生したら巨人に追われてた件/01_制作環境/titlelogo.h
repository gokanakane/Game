//=============================================================================
//
// �^�C�g�����S���� [titlelogo.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene2d.h"	// �V�[��2D

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LOGO	(2)		// �ő吔

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTitleLogo : public CScene2D
{// �^�C�g�����S�i�e�FCScene2D�j
public:
	typedef enum
	{
		TYPE_NONE = 0,	// �����Ȃ�
		TYPE_LOGO,		// �^�C�g�����S
		TYPE_CREDIT,	// �N���W�b�g
		TYPE_MAX		// ����
	}TYPE;

	CTitleLogo();								// �R���X�g���N�^
	~CTitleLogo();								// �f�X�g���N�^

	static HRESULT Load(void);					// ���[�h
	static void Unload(void);					// �A�����[�h
	static CTitleLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, int nTex);		// ����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);					// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	static int GetPattern(void) { return m_Pattern; };
	static void SetPattern(int nPattern) { m_Pattern = nPattern; };

	static int GetData(void) { return m_nData; };
	static void SetGetData(int nPattern) { m_Pattern = m_nData; };

private:
	static int m_Pattern;
	static int m_nData;
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_LOGO];		// �e�N�X�`�����ւ̃|�C���^
	D3DXVECTOR3 m_size;							// �T�C�Y�̑傫��
	int m_nTime;
	float m_fColA;								// �����x
	TYPE m_type;								// �^�C�v

protected:

};

#endif