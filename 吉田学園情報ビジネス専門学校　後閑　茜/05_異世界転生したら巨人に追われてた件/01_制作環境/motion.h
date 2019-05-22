//=============================================================================
//
// ���[�V�������� [motion.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMotion
{// ���[�V����
public:
	typedef struct
	{// �L�[	
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 rot;		// ����
	}KEY;

	typedef struct
	{// �L�[���
		int nFrame;				// �t���[��
		KEY *aKey;				// �L�[
	}KEY_INFO;

	typedef struct
	{// �A�j���[�V�������
		bool bLoop;				// ���[�v
		int nKeyMax;			// �L�[�ő吔
		int nBrendFrame;		// �u�����h�t���[��
		KEY_INFO *aKeyInfo;		// �L�[���
	}ANIM_INFO;

	CMotion();										// �R���X�g���N�^
	~CMotion();										// �f�X�g���N�^

	HRESULT Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(int nModelMax, ANIM_INFO *AnimInfo, CModel *pModel, D3DXVECTOR3 posParent);	// �X�V����
	void Draw(void);								// �`�揈��

	void SetAnimNum(int nNum) { if (m_nAnimNextNum != nNum) { m_nAnimNextNum = nNum; m_nAnimKeyNextNum = 0; m_nEditBFrame = -1; m_bEditBFrame = false; } }											// �A�j���[�V�����ݒ�
	void SetAnimNum(int nNum, int nKeyNum) { if (m_nAnimNextNum != nNum) { m_nAnimNextNum = nNum; m_nAnimKeyNextNum = nKeyNum; m_nEditBFrame = -1; m_bEditBFrame = false; } }						// �A�j���[�V�����ݒ�i�X�^�[�g�L�[�ݒ�L�[�j
	void SetAnimNum(int nNum, int nKeyNum, int nBFrame) { if (m_nAnimNextNum != nNum) { m_nAnimNextNum = nNum; m_nAnimKeyNextNum = nKeyNum; m_nEditBFrame = nBFrame; m_bEditBFrame = true; } }		// �A�j���[�V�����ݒ�i�X�^�[�g�L�[�ݒ�L�[�A�u�����h�t���[���ꎞ�ύX�j
	void SetAnimNumrot(int nNum, int nKeyNum) { m_nAnimNextNum = nNum; m_nAnimKeyNextNum = nKeyNum; m_bSetrot = true; }																				// �A�j���[�V���������ݒ�i�L�[�̊p�x����j
	int GetAnimNum(void) { return m_nAnimNum; }			// �A�j���[�V�����擾
	int GetAnimKeyNum(void) { return m_nAnimKeyNum; }	// �L�[�擾
	int GetCntFrame(void) { return m_nCntFrame; }		// �t���[���擾
	void SetStop(bool bStop) { m_bAnimStop = bStop; }	// �A�j���[�V������~

private:
	int					m_nCntFrame;					// �t���[���J�E���^
	int					m_nEditBFrame;					// �u�����h�t���[���J�E���^
	bool				m_bEditBFrame;					// �u�����h�t���[���ύX
	bool				m_bSetrot;						// �����w��

	bool				m_bAnimStop;					// ��~
	bool				m_bAnimChange;					// �؂�ւ�
	int					m_nAnimNum;						// �A�j���[�V����
	int					m_nAnimNextNum;					// ���A�j���[�V����
	int					m_nAnimKeyNextNum;				// �L�[
	int					m_nAnimKeyNum;					// ���L�[

protected:

};

#endif