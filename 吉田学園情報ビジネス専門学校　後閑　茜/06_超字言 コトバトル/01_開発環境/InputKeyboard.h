//=============================================================================
//
// ���͏��� [inputKeyboard.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
#include"input.h"

//==================================================================
// �}�N����`
//==================================================================
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔

//==================================================================
//	�N���X�̒�`
//==================================================================
//�L�[�{�[�h���̓N���X
class CInputKeyboard : public CInput
{
public:
	typedef struct
	{
		BYTE KeyState;			//�v���X�p�̃L�[���
		BYTE KeyStateTrigger;	//�g���K�[�p�̃L�[���
		BYTE KeyStateRelease;	//�����[�X�p�̃L�[���
		BYTE KeyStateRepeat;	//���s�[�g�p�̃L�[���
		BYTE KeyStateHold;		//�z�[���h�p�̃L�[���
		int nCntRepeatTime;		//���s�[�g�p�̃J�E���^
		int nCntHoldTime;		//�z�[���h�p�̃J�E���^
	}KEYBOARD_STATE;		//�L�[���̍\����

	//�R���X�g���N�^&�f�X�g���N�^
	CInputKeyboard();
	~CInputKeyboard();


	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void    Uninit(void);
	void    Update(void);

	//���͎擾�֐�
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);
	bool GetHold(int nKey);

private:
	KEYBOARD_STATE m_aState[NUM_KEY_MAX];	//�L�[���\����(�L�[����)
};

#endif // !_INPUTKEYBOARD_H_
