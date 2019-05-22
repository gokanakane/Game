//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER		(2)								// �v���C���[�̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CSound;			// �T�E���h
class CInputKeyboard;	// �L�[�{�[�h
class CInputDIPad;		// DI�p�b�h
class CInputXPad;		// X�p�b�h
class CRenderer;		// �����_���[
class CCamera;			// �J����
class CLight;			// ���C�g
class CTitle;			// �^�C�g��
class CTutorial;		// �`���[�g���A��
class CGame;			// �Q�[��
class CResult;			// ���U���g
class CRanking;			// �����L���O
class CPause;			// �|�[�Y

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CManager
{// �}�l�[�W���[
public:
	typedef enum
	{// ���[�h
		MODE_NONE = 0,	// �������Ă��Ȃ�
		MODE_TITLE,		// �^�C�g��
		MODE_TUTORIAL,	// �`���[�g���A��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_RANKING,	// �����L���O
		MODE_MAX
	}MODE;

	CManager();											// �R���X�g���N�^
	virtual ~CManager();								// �f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// ����������
	virtual void Uninit(void);							// �I������
	virtual void Update(void);							// �X�V����
	virtual void Draw(void);							// �`�揈��

	static CSound *GetSound(void)					{ return m_pSound; }			// �T�E���h�擾
	static CInputKeyboard *GetInputKeyboard(void)	{ return m_pInputKeyboard; }	// �L�[�{�[�h�擾
	static CInputDIPad *GetInputDIPad(void)			{ return m_pInputDIPad; }		// DI�p�b�h�擾
	static CInputXPad *GetInputXPad(void)			{ return m_pInputXPad; }		// X�p�b�h�擾
	static CRenderer *GetRenderer(void)				{ return m_pRenderer; }			// �����_���[�擾
	static CCamera *GetCamera(void)					{ return m_pCamara; }			// �J�����擾
	static CLight *GetLight(void)					{ return m_pLight; }			// ���C�g�擾

	static void SetMode(MODE mode);						// ���[�h�ݒ�
	static MODE GetMode(void) { return m_mode; }		// ���[�h�擾

	static void SetPlayNum(int nPlayerNum) { if (nPlayerNum <= MAX_PLAYER)m_nPlayNum = nPlayerNum; else m_nPlayNum = MAX_PLAYER; }				// �v���C�l��
	static int GetPlayNum(void) { return m_nPlayNum; }	// �v���C�l��

private:
	void DebugFont(void);								// �f�o�b�O�t�H���g

	static MODE m_mode;									// ���[�h

	static CSound *m_pSound;							// �T�E���h
	static CInputKeyboard *m_pInputKeyboard;			// �L�[�{�[�h
	static CInputDIPad *m_pInputDIPad;					// DI�p�b�h
	static CInputXPad *m_pInputXPad;					// X�p�b�h
	static CCamera *m_pCamara;							// �J����
	static CLight *m_pLight;							// ���C�g
	static CRenderer *m_pRenderer;						// �����_���[

	static CTitle *m_pTitle;							// �^�C�g��
	static CGame *m_pGame;								// �Q�[��
	static CTutorial *m_pTutorial;						// �`���[�g���A��
	static CResult	*m_pResult;							// ���U���g
	static CRanking *m_pRanking;						// �����L���O

	static int m_nPlayNum;								// �v���C�l��
	static CPause *m_pPause;
	bool m_bPause;

protected:

};

#endif