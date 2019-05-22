//=============================================================================
//
// �J�������� [camera.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCamera
{// �J����
public:
	typedef enum
	{// �J���������ݒ�
		CPOSDEST_TITLE_LOGO = 0,		// �^�C�g�����S
		CPOSDEST_MENU_C,				// ���j���[�J�X�^��
		CPOSDEST_MENU_T,				// ���j���[�^�C�g��
		CPOSDEST_CUSTOM,				// �J�X�^��
		CPOSDEST_MAX
	}CPOSDEST;

	CCamera();												// �R���X�g���N�^
	~CCamera();												// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 posV, D3DXVECTOR3 posR);		// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void SetCamera(void);									// �`�揈��

	void SetPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
	{// �ʒu�ݒ�
		if (m_bSetDest != true)
		{// �����ݒ�
		 // �ʒu�ݒ�
			m_posV = posV;
			m_posVDest = posV;
			m_posR = posR;
			m_posRDest = posR;
			m_rot.y = D3DX_PI - atan2f(posR.x - posV.x, posR.z - posV.z);		// �p�x

																				// �p�x����
			if (D3DX_PI < m_rot.y)
			{
				m_rot.y -= (D3DX_PI * 2);
			}
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += (D3DX_PI * 2);
			}

			m_fDistance = (float)abs((long)(m_posV.z - m_posR.z));				// ����
		}
	}

	bool GetDest(void) { return m_bSetDest; }				// �����ݒ蒆

	void SetPosDest(D3DXVECTOR3 posVDest, D3DXVECTOR3 posRDest, float fDistance, int nLimit, int nNumDest);													// �����ݒ�
	bool GetPosDest(int nNumDest) { bool bSetEnd = m_bSetEnd[nNumDest]; if (m_bSetEnd[nNumDest] == true) m_bSetEnd[nNumDest] = false; return bSetEnd; }		// �����ݒ芮��

	D3DXVECTOR3 GetposV(void) { return m_posV; }			// ���_�擾
	D3DXVECTOR3 GetposR(void) { return m_posR; }			// �����_�擾

	void SetPosVDest(D3DXVECTOR3 posVDest) { m_posVDest = posVDest; }		// ���_�ݒ�
	D3DXVECTOR3 GetPosVDest(void) { return m_posVDest; }					// ���_�擾
	void SetPosRDest(D3DXVECTOR3 posRDest) { m_posRDest = posRDest; }		// �����_�ݒ�
	D3DXVECTOR3 GetPosRDest(void) { return m_posRDest; }					// �����_�擾

private:
	D3DXVECTOR3 m_posV;							// ���_
	D3DXVECTOR3 m_posVDest;						// �ڕW���_
	D3DXVECTOR3 m_posR;							// �����_
	D3DXVECTOR3 m_posRDest;						// �ڕW�����_
	D3DXVECTOR3 m_vecU;							// ������x�N�g��
	D3DXVECTOR3	m_rot;							// �p�x
	float		m_fDistance;					// ����

	bool		m_bSetDest;						// SetDest�g�p
	int			m_nCntSetDest;					// SetDest�J�E���g
	int			m_nLimitSetDest;				// SetDest�I��
	int			m_nNumDest;						// ���
	D3DXVECTOR3 m_posVDiff;						// ���_����
	D3DXVECTOR3 m_posRDiff;						// �����_����
	D3DXVECTOR3 m_rotDiff;						// �p�x����
	float		m_fDistanceDiff;				// ��������

	bool		m_bSetEnd[CPOSDEST_MAX];		// �ݒ�I��

	D3DXMATRIX	m_mtxProjection;				// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	m_mtxView;						// �r���[�}�g���b�N�X

protected:

};

#endif