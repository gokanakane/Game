//=============================================================================
//
// �t�H���g���� [font.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _FONT_H_
#define _FONT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "manager.h"	// �}�l�[�W���[
#include "scene.h"		// �V�[��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MESSAGE		(1024)

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFont
{// �t�H���g
public:
	typedef enum
	{// �t�H���g�ԍ�
		FONTNUM_COMMAND = 0,
		FONTNUM_LOG,
		FONTNUM_DATA,
		FONTNUM_DEBUG,
		FONTNUM_TEST,
		FONTNUM_MAX
	}FONTNUM;

	typedef enum
	{// �Z�b�g�^�C�v
		SETTYPE_NEW = 0,
		SETTYPE_ADD,
		SETTYPE_LOG,
		SETTYPE_MAX
	}SETTYPE;

	CFont();						// �R���X�g���N�^
	~CFont();						// �f�X�g���N�^

	static CFont *Create(int nHeight, int nWidth, int nWeight, RECT rect, UINT uFormat, D3DXCOLOR col);		// �N���G�C�g

	static void ReleaseAll(void);				// �S�j��
	static void DrawAll(void);					// �S�`��

	static bool GetDispAll(void) { return m_bDispAll; }			// �t�H���g�`��

	static void SetMessageData(CScene::OBJTYPE objType, SETTYPE nSetType, char *aMessage, ...);		// �����ݒ�
	static void *GetMessageData(CScene::OBJTYPE objType) { return m_MessageData[objType]; }

	HRESULT Init(int nHeight, int nWidth, int nWeight, RECT rect, UINT uFormat, D3DXCOLOR col);				// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	void SetMessage(SETTYPE nSetType, char *aMessage, ...);		// �����ݒ�
	char *GetMessage(void) { return m_Message; }				// �����擾

	void SetDisp(bool bDisp) { m_bDisp = bDisp; }
	bool GetDisp(void) { return m_bDisp; }

private:
	static CFont *m_apFont[FONTNUM_MAX];		// �V�[��
	static bool m_bDispAll;						// �\��
	static char m_MessageData[CScene::OBJTYPE_MAX][MAX_MESSAGE];

	int m_nID;									// ID�ԍ�
	LPD3DXFONT	m_pFont = NULL;					// �t�H���g�ւ̃|�C���^

	bool m_bDisp;								// �\��
	char m_Message[MAX_MESSAGE];
	RECT m_rect;
	UINT m_uFormat;
	D3DXCOLOR m_col;

protected:
	void Release(void);							// �J������

};

#endif