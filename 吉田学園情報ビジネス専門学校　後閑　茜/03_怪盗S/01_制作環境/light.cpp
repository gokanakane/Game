//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_Ligth[MAX_LIGHT];

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir[MAX_LIGHT];				//�ݒ�����x�N�g��

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		// ���C�g���N���A����
		ZeroMemory(&g_Ligth[nCnt], sizeof(D3DLIGHT9));
		// ���C�g�̎�ނ�ݒ�
		g_Ligth[nCnt].Type = D3DLIGHT_DIRECTIONAL;

	}


	// ���C�g�̊g�U����ݒ�
	g_Ligth[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Ligth[1].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	g_Ligth[2].Diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);


	// ���C�g�̕����̐ݒ�[0]
	vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir[0], &vecDir[0]);//���K��
	g_Ligth[0].Direction = vecDir[0];


	// ���C�g�̕����̐ݒ�[1]
	vecDir[1] = D3DXVECTOR3(-0.5f, 0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir[1], &vecDir[1]);//���K��
	g_Ligth[1].Direction = vecDir[1];



	// ���C�g�̕����̐ݒ�[2]
	vecDir[2] = D3DXVECTOR3(0.8f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir[2], &vecDir[2]);//���K��
	g_Ligth[2].Direction = vecDir[2];

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		// ���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &g_Ligth[nCnt]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}

}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{

}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{

}

