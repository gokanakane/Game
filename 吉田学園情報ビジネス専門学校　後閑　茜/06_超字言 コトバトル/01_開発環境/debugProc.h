//=============================================================================
//
// �f�o�b�N�\������ [debugProc.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"
#include <string>

//========================================
// �N���X�̒�`
//========================================
//=====================
// �J�����N���X
//=====================
class CDebugProc
{
public:
	CDebugProc();		// �R���X�g���N�^
	~CDebugProc();		// �f�X�g���N�^

	void Init(void);
	void Uninit(void);

	static void Print(char *fmt, ...);				// �f�o�b�N�\��
	static void ReleseStr(void);					// �f�o�b�N�\��������
	static void Draw(void);

private:
	static LPD3DXFONT m_pFont;			// �t�H���g�ւ̃|�C���^

	static std::string m_strDebug;		//�f�o�b�N�\���p������
};

#endif