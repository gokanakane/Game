//=============================================================================
//
// �X�|�b�g���C�g [Spotlight.cpp]
// Author : ��Ձ@��
//
//=============================================================================
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "InputKeyboard.h"
#include "SpotLight.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �X�|�b�g���C�g�N���X�̃R���X�g���N�^
//=============================================================================
CSpotLight::CSpotLight()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSpotLight::~CSpotLight()
{
}
//=============================================================================
// ��������
//=============================================================================
CSpotLight *CSpotLight::Create(int nNum, D3DXVECTOR3 pos, D3DXVECTOR3 Dir, D3DXCOLOR Diffuse, D3DXCOLOR Ambient, D3DXCOLOR Specular, float fAttenuation0, float fAttenuation1, float fAttenuation2, float fRange, float fFalloff, float fTheta, float fPhi, bool bSwitch)
{
	CSpotLight *pSpot = NULL;
	if (pSpot == NULL)
	{
		pSpot = new CSpotLight;
		if (pSpot != NULL)
		{
			pSpot->Init();
			pSpot->SettingLight(nNum,pos, Dir, Diffuse, Ambient, Specular, fAttenuation0, fAttenuation1, fAttenuation2, fRange, fFalloff, fTheta, fPhi, bSwitch);
		}
	}
	return pSpot;
}
//=============================================================================
// �X�|�b�g���C�g�̏���������
//=============================================================================
void CSpotLight::Init(void)
{

}

//=============================================================================
// �X�|�b�g���C�g�̏I������
//=============================================================================
void CSpotLight::Uninit(void)
{
}

//=============================================================================
// �X�|�b�g���C�g�̍X�V����
//=============================================================================
void CSpotLight::Update(void)
{
	CLight::Update();
}
//=============================================================================
// �X�|�b�g���C�g�̐���
//=============================================================================
void CSpotLight::SettingLight(int nNum, D3DXVECTOR3 pos, D3DXVECTOR3 Dir, D3DXCOLOR Diffuse, D3DXCOLOR Ambient, D3DXCOLOR Specular, float fAttenuation0, float fAttenuation1, float fAttenuation2, float fRange, float fFalloff, float fTheta, float fPhi, bool bSwitch)
{
#if 1
	D3DLIGHT9 pLight;		//���C�g�̃|�C���^

	// �f�o�C�X�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL) { pDevice = pRenderer->GetDevice(); }

	 // �X�|�b�g���C�g���N���A����
	ZeroMemory(&pLight, sizeof(D3DLIGHT9));

	// �X�|�b�g���C�g�̎�ނ�ݒ�
	pLight.Type = D3DLIGHT_SPOT;

	// �����̈ʒu��ݒ�
	pLight.Position = pos;

	// �X�|�b�g���C�g�̕����̐ݒ�
	D3DXVECTOR3 vecDir;
	vecDir = Dir;

	D3DXVec3Normalize(&vecDir, &vecDir);				//���K���ɂ���
	pLight.Direction = vecDir;

	//����(����������Ȃ������֊ԐړI�ɓ�������̋���)??
	pLight.Ambient = Ambient;

	// �X�y�L�����[�F(�P�����ʂ��o������)���ʌ�/���ˌ�
	pLight.Specular = Specular;

	// �����̗L��������ݒ�
	pLight.Range = fRange;


	//�X�|�b�g���C�g�̋��x (1��2��0.0f�ɂ��邱�ƂŌ������Ȃ����ɂȂ�)
	pLight.Attenuation0 = fAttenuation0;
	pLight.Attenuation1 = fAttenuation1;
	pLight.Attenuation2 = fAttenuation2;


	// �X�|�b�g���C�g�����˂���f�B�t���[�Y�F��ݒ�(�g�U��)
	pLight.Diffuse = Diffuse;


	// �悭�킩��񂯂ǊJ���҂̑�����1.0f��ݒ肵�Ă�炵��
	pLight.Falloff = fFalloff;

	pLight.Theta = fTheta;	//�����R�[���i�悭����������ꏊ�j
	pLight.Phi = fPhi;		//�O���R�[���i�኱����������ꏊ�j

	SetLight(nNum,pLight);
	pDevice->SetLight(nNum, &pLight);
	pDevice->LightEnable(nNum, bSwitch);
#endif // 0
}
//=============================================================================
// ���̐ݒ�
//=============================================================================
void CSpotLight::SetLightEnable(int nNum, bool bEnable)
{
	D3DLIGHT9 pLight = CLight::GetLight(nNum);
	// �f�o�C�X�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL) { pDevice = pRenderer->GetDevice(); }
	m_bEnable = bEnable;

	pDevice->LightEnable(nNum, m_bEnable);
	pDevice->SetLight(nNum, &pLight);

}