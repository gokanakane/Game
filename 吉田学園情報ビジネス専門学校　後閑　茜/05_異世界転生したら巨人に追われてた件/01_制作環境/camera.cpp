//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "camera.h"			// �w�i
#include "manager.h"		// �}�l�[�W���[
#include "input.h"			// ����
#include "renderer.h"		// �����_���[
#include "title.h"			// �^�C�g��
#include "game.h"			// �Q�[��
#include "titlelogo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^									(public)	*** CCamera ***
//=============================================================================
CCamera::CCamera()
{
	m_posV			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���ݎ��_
	m_posVDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ڕW���_
	m_posR			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���ݒ����_
	m_posRDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ڕW�����_
	m_vecU			= D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// ������x�N�g��
	m_fDistance		= 0.0f;										// ����

	m_bSetDest		= false;									// SetDest�g�p
	m_nCntSetDest	= 0;										// SetDest�J�E���g
	m_nLimitSetDest = 0;										// SetDest�I��
	m_posVDiff		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);;			// ���_����
	m_posRDiff		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);;			// �����_����
	m_rotDiff		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);;			// �p�x����
	m_fDistanceDiff = 0.0f;										// ��������
}

//=============================================================================
// �f�X�g���N�^										(public)	*** CCamera ***
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// ����������										(public)	*** CCamera ***
//=============================================================================
HRESULT CCamera::Init(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_posV			= posV;										// ���ݎ��_
	m_posVDest		= posV;										// �ڕW���_
	m_posR			= posR;										// ���ݒ����_
	m_posRDest		= posR;										// �ڕW�����_
	m_rot			= D3DXVECTOR3(0.0f, D3DX_PI - atan2f(posR.x - posV.x, posR.z - posV.z), 0.0f);		// �p�x
	m_fDistance		= (float)abs((long)(m_posV.z - m_posR.z));	// ����

	m_bSetDest		= false;									// SetDest�g�p
	m_nCntSetDest	= 0;										// SetDest�J�E���g
	m_nLimitSetDest = 0;										// SetDest�I��
	m_posVDiff		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);;			// ���_����
	m_posRDiff		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);;			// �����_����
	m_rotDiff		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);;			// �p�x����
	m_fDistanceDiff = 0.0f;										// ��������

	for (int nCount = 0; nCount < CPOSDEST_MAX; nCount++)
	{// �J�E���g
		m_bSetEnd[nCount] = false;								// �ݒ�I��
	}

	return S_OK;
}

//=============================================================================
// �I������											(public)	*** CCamera ***
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �X�V����											(public)	*** CCamera ***
//=============================================================================
void CCamera::Update(void)
{
	CManager::MODE pMode = CManager::GetMode();
	int nData = CTitleLogo::GetData();

	if (pMode == CManager::MODE_TITLE)
	{
		if (nData == 1)
		{
			m_posV = D3DXVECTOR3(50.0f, 230.0f, -500.0f);
			m_posR = D3DXVECTOR3(50.0f, 170.0f, 0.0f);
			m_posVDest.x = 0.0f;
			m_posRDest.x = 0.0f;
		}
		else
		{
			m_posVDest.x += 2.0f;
			m_posRDest.x += 2.0f;
		}

	}

#ifdef _DEBUG
	if (CManager::GetInputKeyboard()->GetPress(DIK_I) == true)
	{
		m_posVDest.z += 5.0f;
		m_posRDest.z += 5.0f;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_K) == true)
	{
		m_posVDest.z -= 5.0f;
		m_posRDest.z -= 5.0f;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_J) == true)
	{
		m_posVDest.x -= 5.0f;
		m_posRDest.x -= 5.0f;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_L) == true)
	{
		m_posVDest.x += 5.0f;
		m_posRDest.x += 5.0f;
	}

	if (CManager::GetInputKeyboard()->GetPress(DIK_Q) == true)
	{
		m_rot.y -= 0.02f;
		m_posVDest.x = m_posR.x + sinf(m_rot.y) * m_fDistance;
		m_posVDest.z = m_posR.z + cosf(m_rot.y) * m_fDistance;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_E) == true)
	{
		m_rot.y += 0.02f;
		m_posVDest.x = m_posR.x + sinf(m_rot.y) * m_fDistance;
		m_posVDest.z = m_posR.z + cosf(m_rot.y) * m_fDistance;
	}

	// ���_�㉺��]
	if (CManager::GetInputKeyboard()->GetPress(DIK_T) == true)
	{
		m_posV.y += 5.0f;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_G) == true)
	{
		m_posV.y -= 5.0f;
	}

	// �����_�㉺��]
	if (CManager::GetInputKeyboard()->GetPress(DIK_Y) == true)
	{
		m_posR.y += 5.0f;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_H) == true)
	{
		m_posR.y -= 5.0f;
	}
#endif // _DEBUG

	if (m_bSetDest == true)
	{// �Z�b�g����
		m_nCntSetDest++;				// �J�E���g

		m_rot.y += (m_rotDiff.y / m_nLimitSetDest);						// ��������

		m_fDistance += (m_fDistanceDiff / m_nLimitSetDest);				// ��������

		// �ʒu����
		m_posRDest.x = m_posV.x - sinf(m_rot.y) * m_fDistance;
		m_posRDest.z = m_posV.z - cosf(m_rot.y) * m_fDistance;
		m_posVDest.x = m_posV.x + (m_posVDiff.x / m_nLimitSetDest);
		m_posVDest.z = m_posV.z + (m_posVDiff.z / m_nLimitSetDest);

		if (m_nCntSetDest == m_nLimitSetDest)
		{// �J�E���g�����E�ɒB������
			m_bSetDest = false;					// FALSE��
			m_bSetEnd[m_nNumDest] = true;		// TRUE��		�I���x��
		}
	}

	// �����͈̔͒���
	if (D3DX_PI < m_rot.y)
	{
		m_rot.y -= (D3DX_PI * 2);
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += (D3DX_PI * 2);
	}

	// �l���
	m_posR.x += (m_posRDest.x - m_posR.x);
	m_posR.z += (m_posRDest.z - m_posR.z);
	m_posV.x += (m_posVDest.x - m_posV.x);
	m_posV.z += (m_posVDest.z - m_posV.z);

	CFont *pFont = CRenderer::GetFont(CFont::FONTNUM_DATA);

	CFont::SetMessageData(CScene::OBJTYPE_CAMERA, CFont::SETTYPE_ADD, "Camera : ���_�@[%.2f, %.2f, %.2f]\n", m_posV.x, m_posV.y, m_posV.z);
	CFont::SetMessageData(CScene::OBJTYPE_CAMERA, CFont::SETTYPE_ADD, "Camera : �����_[%.2f, %.2f, %.2f]\n", m_posR.x, m_posR.y, m_posR.z);
	CFont::SetMessageData(CScene::OBJTYPE_CAMERA, CFont::SETTYPE_ADD, "\n");
}

//=============================================================================
// �`�揈��											(public)	*** CCamera ***
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH
	(
		&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		5000.0f
	);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH
	(
		&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU
	);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=============================================================================
// �����ݒ菈��										(public)	*** CCamera ***
//=============================================================================
void CCamera::SetPosDest(D3DXVECTOR3 posVDest, D3DXVECTOR3 posRDest, float fDistance, int nLimit, int nNumDest)
{
	if (m_bSetDest != true)
	{// �Z�b�g��TRUE�ȊO�̏ꍇ
		m_bSetDest = true;					// TRUE��

		m_nCntSetDest = 0;					// �J�E���g������
		m_nLimitSetDest = nLimit;			// ���E�J�E���g��ݒ�
		m_nNumDest = nNumDest;				// �Z�b�g�ԍ�

		// �����v�Z
		m_posVDiff = posVDest - m_posV;		// �ʒu
		m_posRDiff = posRDest - m_posR;
		//m_rotDiff.y = atan2f(posRDest.z - posVDest.z, posRDest.x - posVDest.x);		// ����
		m_rotDiff.y = atan2f(posRDest.x - posVDest.x, posRDest.z - posVDest.z);

		m_rotDiff.y = D3DX_PI - m_rotDiff.y - m_rot.y;

		// �����͈̔͒��� 
		if (D3DX_PI < m_rotDiff.y)
		{
			m_rotDiff.y -= (D3DX_PI * 2);
		}
		if (m_rotDiff.y < -D3DX_PI)
		{
			m_rotDiff.y += (D3DX_PI * 2);
		}

		m_fDistanceDiff = (float)(abs((long)fDistance) - abs((long)m_fDistance));		// ����
	}
}