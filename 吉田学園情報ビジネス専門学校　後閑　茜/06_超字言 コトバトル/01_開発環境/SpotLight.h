//=============================================================================
//
// �X�|�b�g���C�g���� [SpotLignt.h]
// Author : ��Ձ@��
//
//=============================================================================
#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include "main.h"
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SPOTLIGHT_DEFFUSE (D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//�X�|�b�g���C�g�����˂���f�B�t���[�Y�F
#define SPOTLIGHT_SPECULAR (D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//���ʐF
#define SPOTLIGHT_AMBIENT (D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//����
#define SPOTLIGHT_DIRECTION (D3DXVECTOR3(0.0f,-1.0f, 0.0f))		//����
#define SPOTLIGHT_FALLOFF (1.0f)								//�t�H�[���I�t��

//========================================
// �N���X�̒�`
//========================================
//=====================
// �X�|�b�g���C�g�N���X
//=====================
class CSpotLight : public CLight
{
public:
	CSpotLight();
	~CSpotLight();
	void Init(void);
	void Uninit(void);
	void Update(void);

	static CSpotLight *Create(int nNum, D3DXVECTOR3 pos, D3DXVECTOR3 Dir, D3DXCOLOR Diffuse, D3DXCOLOR Ambient, D3DXCOLOR Specular, float fAttenuation0, float fAttenuation1, float fAttenuation2, float fRange, float fFalloff, float fTheta, float fPhi, bool bSwitch = true);
	void SetLightEnable(int nNum, bool bEnable);
	void SpotLightDelete(void) { CLight::Init(); }

private:
	bool m_bEnable;
	/* �ݒ菈�� */
	void SettingLight(int nNum,D3DXVECTOR3 pos, D3DXVECTOR3 Dir, D3DXCOLOR Diffuse, D3DXCOLOR Ambient, D3DXCOLOR Specular, float fAttenuation0, float fAttenuation1, float fAttenuation2, float fRange, float fFalloff, float fTheta, float fPhi, bool bSwitch);
};
#endif