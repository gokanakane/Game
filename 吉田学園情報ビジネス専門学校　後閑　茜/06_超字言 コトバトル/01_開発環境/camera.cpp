//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "camera.h"
#include "InputKeyboard.h"
#include "Manager.h"
#include "renderer.h"
#include "debugProc.h"

#include "charactor.h"
//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_fCameraAngle = 45.0f;
	m_pHomingChara = NULL;
	m_pLockOnChara = NULL;
}
CCamera::~CCamera()
{

}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CCamera::Set(CAMERA_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength)
{
	m_Type = type;		//�^�C�v�̐ݒ�

	m_rot = rot;
	m_fLength = fLength;

	switch (m_Type)
	{
	case CCamera::TYPE_FPS:
		m_posV = pos;
		m_posR = pos + D3DXVECTOR3(sinf(rot.y) * fLength, sinf(rot.x) * fLength, cosf(rot.y) * fLength);
		break;
	case CCamera::TYPE_TPS:
		m_posR = pos;
		m_posV = pos - D3DXVECTOR3(sinf(rot.y) * fLength, sinf(rot.x) * fLength, cosf(rot.y) * fLength);
		m_vecU = D3DXVECTOR3(0.0f,1.0f,0.0f);
		break;
	case CCamera::TYPE_SPECTOR:
		m_posV = pos;
		m_posR = pos;
		break;
	case CCamera::TYPE_TOPVIEW:
		m_posV = pos;
		m_posR = pos;
		break;
	}
}

//=============================================================================
// ����������
//=============================================================================
void CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVdest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRdest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�r���[�|�[�g�����l�ݒ�
	m_ViewPort.X = 0;
	m_ViewPort.Y = 0;
	m_ViewPort.Width = SCREEN_WIDTH;
	m_ViewPort.Height = SCREEN_HEIGHT;
	m_ViewPort.MinZ = 0.0f;
	m_ViewPort.MaxZ = 1.0f;

	m_fLength = 0.0f;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	CInputKeyboard* pInput = CManager::GetInputKeyboard();


	switch (m_Type)
	{
	case TYPE_FPS:
		break;
	case TYPE_TPS:
		if (m_pHomingChara != NULL)
		{
			if (m_pLockOnChara != NULL)
			{
				//�p�x
				//Y
				m_rotDest.y = atan2f(m_pLockOnChara->GetCameraPosR().x - m_pHomingChara->GetCameraPosR().x,
					m_pLockOnChara->GetCameraPosR().z - m_pHomingChara->GetCameraPosR().z) - m_rot.y;

				CUtilityMath::RotateNormarizePI(&m_rotDest.y);
				m_rot.y += m_rotDest.y * CAMERA_ROT_COEFFICIENT;
				CUtilityMath::RotateNormarizePI(&m_rot.y);

				//m_pHomingChara->GetSpin().y = m_rot.y;

				//X
				//m_rot.x = atan2f(m_pLockOnChara->GetCameraPosR().y - m_pHomingChara->GetCameraPosR().y,
				//	m_pLockOnChara->GetCameraPosR().z - m_pHomingChara->GetCameraPosR().z)/* - m_rot.x*/;

				////CUtilityMath::RotateNormarizePI(&m_rotDest.x);
				////m_rot.x += m_rotDest.x * CAMERA_ROT_COEFFICIENT;
				//CUtilityMath::RotateNormarizePI(&m_rot.x);
				m_rot.x = 0.0f;

				//���W
				//D3DXVec3Lerp(&m_posRdest, &m_pLockOnChara->GetCameraPosR(), &m_pHomingChara->GetCameraPosR(), 1.0f);
				m_posRdest = m_pLockOnChara->GetCameraPosR();
				m_posR += (m_posRdest - m_posR) * CAMERA_POSR_COEFFICIENT;
			}
			else
			{
				m_posRdest = m_pHomingChara->GetCameraPosR();
				m_posR += (m_posRdest - m_posR) * CAMERA_POSR_COEFFICIENT;
			}
			m_posVdest = m_pHomingChara->GetCameraPosR() - D3DXVECTOR3(sinf(m_rot.y) * m_fLength,
				-m_fLength,
				cosf(m_rot.y) * m_fLength);

			//m_posVdest = m_pHomingChara->GetCameraPosR() + D3DXVECTOR3((sinf(m_rot.y) * m_fLength)*(sinf(m_rot.x) * m_fLength),
			//	cosf(m_rot.y) * m_fLength,
			//	(sinf(m_rot.y) * m_fLength)*(cosf(m_rot.x) * m_fLength));

			m_posV += (m_posVdest - m_posV) * CAMERA_POSV_COEFFICIENT;
		}

		break;
	case TYPE_SPECTOR:
		break;
	case TYPE_TOPVIEW:
		m_posVdest = m_posR - D3DXVECTOR3(sinf(m_rot.y) * m_fLength,
			sinf(m_rot.x) * m_fLength,
			cosf(m_rot.y) * m_fLength);
		m_posV += (m_posVdest - m_posV) * CAMERA_POSV_COEFFICIENT;
		break;
	}

	//�p�xY�̕␳
	CUtilityMath::RotateNormarizePI(&m_rot.y);


}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	CRenderer* pRenderder = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderder->GetDevice();	// �f�o�C�X�̎擾

	pDevice->SetViewport(&m_ViewPort);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(m_fCameraAngle),
		(float)m_ViewPort.Width / (float)m_ViewPort.Height,
		10.0f,
		10000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);


	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

#ifdef _DEBUG
	CDebugProc::Print("cfff", "Camera.PosV :", m_posV.x, m_posV.y, m_posV.z);
	CDebugProc::Print("cfff","Camera.PosR :", m_posR.x, m_posR.y, m_posR.z);
#endif

}