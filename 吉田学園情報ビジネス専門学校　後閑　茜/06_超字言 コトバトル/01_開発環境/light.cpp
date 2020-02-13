//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : �ڍ� ������
//
//=============================================================================
#include "light.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "InputKeyboard.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
D3DLIGHT9 CLight::m_light[MAX_LIGHT] = {};
//=============================================================================
// ���C�g�N���X�̃R���X�g���N�^
//=============================================================================
CLight::CLight()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{
}

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void CLight::Init(void)
{
	D3DXVECTOR3 vecDir;

	// �f�o�C�X�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

#if(1)
	// �f�B���N�V�������C�g
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));
	}

	// ���C�g�̎�ނ�ݒ�
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;
	m_light[1].Type = D3DLIGHT_DIRECTIONAL;
	m_light[2].Type = D3DLIGHT_DIRECTIONAL;
	m_light[3].Type = D3DLIGHT_DIRECTIONAL;
	m_light[4].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_light[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	m_light[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
	m_light[3].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	m_light[4].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	m_light[0].Direction = vecDir;

	vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	m_light[1].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.9f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	m_light[2].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.0f, -0.9f, 1.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	m_light[3].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.0f, -0.1f, -1.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	m_light[4].Direction = vecDir;

	if (pDevice != NULL)
	{
		// ���C�g��ݒ肷��
		pDevice->SetLight(0, &m_light[0]);
		pDevice->SetLight(1, &m_light[1]);
		pDevice->SetLight(2, &m_light[2]);
		pDevice->SetLight(3, &m_light[3]);
		pDevice->SetLight(4, &m_light[4]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(0, TRUE);
		pDevice->LightEnable(1, TRUE);
		pDevice->LightEnable(2, TRUE);
		pDevice->LightEnable(3, TRUE);
		pDevice->LightEnable(4, TRUE);
	}
#endif // 1

#if(0)
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{// �|�C���g���C�g
		// ���C�g���N���A����
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_light[nCntLight].Type = D3DLIGHT_POINT;

		// ���C�g�����˂���f�B�t���[�Y�F��ݒ�
		m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �X�y�L�����[�F
		m_light[nCntLight].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//����(���邭�Ȃ�)
		m_light[nCntLight].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �����̈ʒu��ݒ�
		m_light[nCntLight].Position = D3DXVECTOR3(100.0f, 50.0f, -100.0f);

		// ���C�g�̕����̐ݒ�
		//vecDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//D3DXVec3Normalize(&vecDir, &vecDir);				//���K���ɂ���
		//m_light[nCntLight].Direction = vecDir;

		// �����̗L��������ݒ�
		m_light[nCntLight].Range = 300.0f;

		// �悭�킩��񂯂ǊJ���҂̑�����1.0f��ݒ肵�Ă�炵��
		m_light[nCntLight].Falloff = 1.0f;

		//���C�g�̋��x
		m_light[nCntLight].Attenuation0 = 0.5f;
		m_light[nCntLight].Attenuation1 = 0.05f;
		m_light[nCntLight].Attenuation2 = 0.0f;

		m_light[nCntLight].Theta = D3DXToRadian(10.0f);	//�����R�[���i�悭����������ꏊ�j
		m_light[nCntLight].Phi = D3DXToRadian(30.0f);		//�O���R�[���i�኱����������ꏊ�j

															// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
#endif

#if 0
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{// �X�|�b�g���C�g
	 // ���C�g���N���A����
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_light[nCntLight].Type = D3DLIGHT_SPOT;

		// ���C�g�����˂���f�B�t���[�Y�F��ݒ�
		m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �X�y�L�����[�F(�P�����ʂ��o������)??
		m_light[nCntLight].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//����(����������Ȃ������֊ԐړI�ɓ�������̋���)??
		m_light[nCntLight].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �����̈ʒu��ݒ�
		m_light[nCntLight].Position = D3DXVECTOR3(100.0f, 50.0f, -100.0f);

		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		D3DXVec3Normalize(&vecDir, &vecDir);				//���K���ɂ���
		m_light[nCntLight].Direction = vecDir;

		// �����̗L��������ݒ�
		m_light[nCntLight].Range = 800.0f;

		// �悭�킩��񂯂ǊJ���҂̑�����1.0f��ݒ肵�Ă�炵��
		m_light[nCntLight].Falloff = 1.0f;

		//���C�g�̋��x (1��2��0.0f�ɂ��邱�ƂŌ������Ȃ����ɂȂ�)
		m_light[nCntLight].Attenuation0 = 1.0f;
		m_light[nCntLight].Attenuation1 = 0.0f;
		m_light[nCntLight].Attenuation2 = 0.0f;

		m_light[nCntLight].Theta = D3DXToRadian(50.0f);	//�����R�[���i�悭����������ꏊ�j
		m_light[nCntLight].Phi = D3DXToRadian(100.0f);		//�O���R�[���i�኱����������ꏊ�j

															// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		// ���C�g��L���ɂ���
		if (nCntLight == 0)
		{
			pDevice->LightEnable(0, TRUE);
		}
		else if (nCntLight == 1)
		{
			pDevice->LightEnable(1, FALSE);
		}
		else if (nCntLight == 2)
		{
			pDevice->LightEnable(2, FALSE);
		}
	}
#endif // 0


}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void CLight::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �f�o�C�X�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}


	if (pInputKeyboard->GetPress(DIK_NUMPAD1) == true)
	{
		m_light[0].Position.y -= 1.0f;
		m_light[1].Position.y -= 1.0f;
		m_light[2].Position.y -= 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_NUMPAD7) == true)
	{
		m_light[0].Position.y += 1.0f;
		m_light[1].Position.y += 1.0f;
		m_light[2].Position.y += 1.0f;
	}

	if (pInputKeyboard->GetPress(DIK_NUMPAD4) == true)
	{
		m_light[0].Position.x -= 1.0f;
		m_light[1].Position.x -= 1.0f;
		m_light[2].Position.x -= 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_NUMPAD6) == true)
	{
		m_light[0].Position.x += 1.0f;
		m_light[1].Position.x += 1.0f;
		m_light[2].Position.x += 1.0f;
	}

	if (pInputKeyboard->GetPress(DIK_NUMPAD2) == true)
	{
		m_light[0].Position.z -= 1.0f;
		m_light[1].Position.z -= 1.0f;
		m_light[2].Position.z -= 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_NUMPAD8) == true)
	{
		m_light[0].Position.z += 1.0f;
		m_light[1].Position.z += 1.0f;
		m_light[2].Position.z += 1.0f;
	}

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &m_light[0]);
	pDevice->SetLight(1, &m_light[1]);
	pDevice->SetLight(2, &m_light[2]);

}