//=============================================================================
//
// �J�����Ǘ����� [CameraManager.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "CameraManager.h"
#include "Manager.h"


#define CAMERANAME_SETCAMERA_NONE "NONE"	//�J�������܂��Z�b�g����ĂȂ�����m_SetCamera�ɓ���镶����
#define BACK_DEFAULT_COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))

LPCSTR CCameraManager::m_SetCamera = CAMERANAME_SETCAMERA_NONE;


//===================================================================
// �R���X�g���N�^&�f�X�g���N�^
//===================================================================
CCameraManager::CCameraManager()
{

}
CCameraManager::~CCameraManager()
{

}

//===================================================================
// ����������
//===================================================================
HRESULT CCameraManager::Init(void)
{
	m_vecCameraState.clear();
	return S_OK;
}

//===================================================================
// �I������
//===================================================================
void CCameraManager::Uninit(void)
{
	for (auto itrCamera = m_vecCameraState.begin(); itrCamera != m_vecCameraState.end(); itrCamera++)
	{
		ObjRelease(itrCamera->pCamera);
	}
}

//===================================================================
// �X�V����
//===================================================================
void CCameraManager::Update(void)
{
	for (auto itrCamera = m_vecCameraState.begin(); itrCamera != m_vecCameraState.end(); itrCamera++)
	{
		if (itrCamera->pCamera != NULL)
		{
			itrCamera->pCamera->Update();
		}
	}
	m_SetCamera = CAMERANAME_SETCAMERA_NONE;
}

//===================================================================
// �J�����ݒ菈��
//===================================================================
bool CCameraManager::SetCamera(LPCSTR Tag)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (result != m_vecCameraState.end())
	{//�J����������`����Ă����
		if(result->CameraTag != m_SetCamera)
		{//���̖��O�̃J�������܂��Z�b�g����Ă��Ȃ����
			if (result->pCamera != NULL)
			{//�J�����|�C���^��NULL�łȂ����
				result->pCamera->SetCamera();
				m_SetCamera = result->CameraTag;

				// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
				WindowClear(pDevice,result->Property,result->BackgroundColor);

				return true;
			}
		}

	}

	return false;
}

//===================================================================
// �J������������
//===================================================================
bool CCameraManager::CreateCamera(LPCSTR Tag, CCamera::CAMERA_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength,DRAW_PROPERTY prop)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (Tag != CAMERANAME_SETCAMERA_NONE)
	{//�J������������̖��O�łȂ����
		if (result == m_vecCameraState.end())
		{//�܂�Tag�Ɠ������O�̃J��������������ĂȂ����
			CAMERA_STATE CameraState;

			if (ObjCreate(CameraState.pCamera))
			{
				CameraState.pCamera->Set(type, pos, rot, fLength);
				CameraState.CameraTag = Tag;
				CameraState.BackgroundColor = BACK_DEFAULT_COLOR;
				CameraState.Property = prop;
				m_vecCameraState.emplace_back(CameraState);

				return true;
			}
		}
		else
		{//���ɃJ��������������Ă����
			result->pCamera->Set(type, pos, rot, fLength);
		}
	}
	return false;
}

//===================================================================
// �J�����̍폜����
//===================================================================
bool CCameraManager::DeleteCamera(LPCSTR Tag)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (result != m_vecCameraState.end())
	{//�J����������`����Ă����
		if (result->pCamera != NULL)
		{
			result->pCamera->Uninit();

			delete result->pCamera;
			result->pCamera = NULL;
		}

		m_vecCameraState.erase(result);
		return true;
	}

	return false;

}

//===================================================================
// �J�����̃r���[�|�[�g�ݒ菈��
//===================================================================
bool CCameraManager::SetCameraViewPort(LPCSTR Tag, int X, int Y, int Width, int Height, float MinZ, float MaxZ)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		pCamera->SetViewPort(X,Y,Width,Height,MinZ,MaxZ);
		return true;
	}

	return false;
}

//===================================================================
// �J�����̒Ǐ]�Ώېݒ菈��
//===================================================================
bool CCameraManager::SetCameraHomingChara(LPCSTR Tag, C3DCharactor* pHomingChara)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		pCamera->SetHomingChara(pHomingChara);
		return true;
	}

	return false;

}

//===================================================================
// �J�����̒����ݒ菈��
//===================================================================
bool CCameraManager::SetCameraLength(LPCSTR Tag, float fLength)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		pCamera->SetLength(fLength);
		return true;
	}

	return false;

}
float CCameraManager::GetLength(LPCSTR Tag)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		return pCamera->GetLength();
	}

	return -10000000000.0f;
}

//===================================================================
// �J�����̒ǐՑΏېݒ菈��
//===================================================================
bool CCameraManager::SetCameraLockOnChara(LPCSTR Tag, C3DCharactor* pLockOnChara)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		pCamera->SetLockOnChara(pLockOnChara);
		return true;
	}

	return false;

}

//===================================================================
// �J�����̉�p�ݒ菈��
//===================================================================
bool CCameraManager::SetCameraAngle(LPCSTR Tag, float fAngle)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		pCamera->SetCameraAngle(fAngle);
		return true;
	}
	return false;
}

//===================================================================
// �J�����̒����_�ݒ菈��
//===================================================================
bool CCameraManager::SetCameraPosR(LPCSTR Tag, D3DXVECTOR3 posR, bool bLeap)
{
	CCamera* pCamera = CameraSearch(Tag);
	if (pCamera != NULL)
	{
		pCamera->SetPosRDest(posR);//�����l�ɒl������
		if (bLeap == false)
		{//���[�v�����鎞�͒���posR�ɂ������
			pCamera->SetPosR(posR);
		}
		return true;
	}
	return false;
}

//===================================================================
// �w�i�F�ݒ菈��
//===================================================================
bool CCameraManager::SetBackGroundColor(LPCSTR Tag, D3DXCOLOR col)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (result != m_vecCameraState.end())
	{//�J����������`����Ă����
		result->BackgroundColor = col;

		return true;
	}

	return false;


}

//===================================================================
// �J�����擾����
//===================================================================
CCamera* CCameraManager::GetCamera(LPCSTR Tag)
{
	return CameraSearch(Tag);
}

//===================================================================
// �J�����擾����
//===================================================================
CCamera* CCameraManager::CameraSearch(LPCSTR Tag)
{
	auto result = std::find(m_vecCameraState.begin(), m_vecCameraState.end(), Tag);

	if (result != m_vecCameraState.end())
	{//�J����������`����Ă����
		return result->pCamera;
	}
	return NULL;
}
//===================================================================
// �E�B���h�E����������
//===================================================================
void CCameraManager::WindowClear(LPDIRECT3DDEVICE9 pDev, DRAW_PROPERTY prop, D3DXCOLOR BG_Color)
{
	switch (prop)
	{
	case PROP_DEFAULT:
		pDev->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), BG_Color, 1.0f, 0);
		break;
	case PROP_INIT_ZONLY:
		pDev->Clear(0, NULL, (D3DCLEAR_ZBUFFER), BG_Color, 1.0f, 0);
		break;
	}


}