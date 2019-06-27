//=============================================================================
//
// �J�������� [camera.cpp]
// Author : ��Ո�
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "Player.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_Camera;			//�J�����̏��

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	//�\���̂̏�����
	g_Camera.posV = D3DXVECTOR3(400.0f, 100.0f, -200.0f);
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f,D3DX_PI, 0.0f);
	g_Camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.fDistance = 40;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	//float fDesAngle=0;	//�ړI�̊p�x
	//float fMoveAngle=0;	//���݂̊p�x

	Player*pPlayer;
	MODE g_MODE;
	pPlayer = GetPlayer();
	g_MODE = GetMode();
	int nCnt = 0;//�b��

	//g_Camera.posV = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y+50, pPlayer->pos.z+120);
	//g_Camera.posR = pPlayer->pos;

	if (g_MODE == MODE_GAME)
	{
		////�v���C���[���ړ�������Ǐ]
		//if (pPlayer->posOld != pPlayer->pos)
		//{
			//�J�����̒Ǐ]------------------------------------
			//�ړI�̒����_
		g_Camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y) * -pPlayer->move.x;
		g_Camera.posRDest.y = pPlayer->pos.y;
		g_Camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y) * -pPlayer->move.z;

		//�ړI�̎��_
		g_Camera.posVDest.x = pPlayer->pos.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posVDest.y = pPlayer->pos.y + 20.0f;
		g_Camera.posVDest.z = pPlayer->pos.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;

		////�����_
		g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x) * 0.2f;
		g_Camera.posR.y += (g_Camera.posRDest.y - g_Camera.posR.y) * 0.2f;
		g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z) * 0.2f;

		//���_
		g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x) * 0.07f;
		g_Camera.posV.y += (g_Camera.posVDest.y - g_Camera.posV.y) * 0.07f;
		g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z) * 0.07f;
	}
		//	//���Z�b�g--------------------------------
		//	if (GetKeyboardPress(DIK_RETURN) == true)
		//	{
		//		InitCamera();
		//	}
		//}


		//}
		//else
		//{
			//�ړI�̒����_
			//g_Camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y) * -10.0f;
			//g_Camera.posRDest.y = pPlayer->pos.y;
			//g_Camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y) * -10.0f;

			////�ړI�̎��_
			//g_Camera.posVDest.x = pPlayer->pos.x + sinf(g_Camera.rotDest.y) * g_Camera.fDistance;
			//g_Camera.posVDest.y = pPlayer->pos.y + 20.0f;
			//g_Camera.posVDest.z = pPlayer->pos.z + cosf(g_Camera.rotDest.y) * g_Camera.fDistance;

			////�����_
			//g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x) * 0.2f;
			//g_Camera.posR.y += (g_Camera.posRDest.y - g_Camera.posR.y) * 0.2f;
			//g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z) * 0.2f;

			////���_
			//g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x) * 0.07f;
			//g_Camera.posV.y += (g_Camera.posVDest.y - g_Camera.posV.y) * 0.07f;
			//g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z) * 0.07f;
		//	//nCnt++;
		//	//if (nCnt>=120)
		//	//{//2�b�o������


		//	//	nCnt = 0;
		//	//}
		//}


		////�J�����ړ�-----------------------------------
	//	if (GetKeyboardPress(DIK_A) == true)
	//	{//���ړ�
	//		g_Camera.posV.x += sinf(D3DX_PI * -0.5f + g_Camera.rot.y)*CAMERA_MOVR;
	//		g_Camera.posV.z += cosf(D3DX_PI * -0.5f + g_Camera.rot.y)*CAMERA_MOVR;

	//		g_Camera.posR.x = g_Camera.posV.x + sinf(0.0f + g_Camera.rot.y) * g_Camera.fDistance;
	//		g_Camera.posR.z = g_Camera.posV.z + cosf(0.0f + g_Camera.rot.y) * g_Camera.fDistance;
	//	}

	//	if (GetKeyboardPress(DIK_D) == true)
	//	{//�E�ړ�
	//		g_Camera.posV.x += sinf(D3DX_PI * 0.5f + g_Camera.rot.y)* CAMERA_MOVR;
	//		g_Camera.posV.z += cosf(D3DX_PI * 0.5f + g_Camera.rot.y)* CAMERA_MOVR;

	//		g_Camera.posR.x = g_Camera.posV.x + sinf(0.0f + g_Camera.rot.y) * g_Camera.fDistance;
	//		g_Camera.posR.z = g_Camera.posV.z + cosf(0.0f + g_Camera.rot.y) * g_Camera.fDistance;

	//	}

	//	if (GetKeyboardPress(DIK_W) == true)
	//	{//��ړ�
	//		g_Camera.posV.x += sinf(0.0f + g_Camera.rot.y)*CAMERA_MOVR;
	//		g_Camera.posV.z += cosf(0.0f + g_Camera.rot.y)*CAMERA_MOVR;

	//		g_Camera.posR.x = g_Camera.posV.x + sinf(0.0f+ g_Camera.rot.y) * g_Camera.fDistance;
	//		g_Camera.posR.z = g_Camera.posV.z + cosf(0.0f+ g_Camera.rot.y) * g_Camera.fDistance;
	//	}

	//	if (GetKeyboardPress(DIK_S) == true)
	//	{//���ړ�
	//		g_Camera.posV.x += sinf(D3DX_PI+ g_Camera.rot.y)*CAMERA_MOVR;
	//		g_Camera.posV.z += cosf(D3DX_PI+ g_Camera.rot.y)*CAMERA_MOVR;

	//		g_Camera.posR.x = g_Camera.posV.x + sinf(0.0f+ g_Camera.rot.y) * g_Camera.fDistance;
	//		g_Camera.posR.z = g_Camera.posV.z + cosf(0.0f+ g_Camera.rot.y) * g_Camera.fDistance;
	//	}

	//	//���_�ړ�--------------------------------
	//	if (GetKeyboardPress(DIK_Y) == true)
	//	{
	//		g_Camera.posV.x += sinf(0.0f)*CAMERA_MOVR;
	//		g_Camera.posV.y += cosf(0.0f)*CAMERA_MOVR;
	//	}
	//	else if (GetKeyboardPress(DIK_N) == true)
	//	{
	//		g_Camera.posV.x += sinf(D3DX_PI)*CAMERA_MOVR;
	//		g_Camera.posV.y += cosf(D3DX_PI)*CAMERA_MOVR;
	//	}
	//	if (GetKeyboardPress(DIK_Z) == true)
	//	{//������
	//		g_Camera.rot.y += 0.05f;

	//		g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y - D3DX_PI) * g_Camera.fDistance;
	//		g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y - D3DX_PI) * g_Camera.fDistance;

	//	}
	//	else if (GetKeyboardPress(DIK_C) == true)
	//	{//�E����
	//		g_Camera.rot.y -= 0.05f;

	//		g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y - D3DX_PI) * g_Camera.fDistance;
	//		g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y - D3DX_PI) * g_Camera.fDistance;

	//	}

	//	//�����_�ړ�--------------------------------
	//	if (GetKeyboardPress(DIK_T) == true)
	//	{
	//		g_Camera.posR.x += sinf(0.0f)*CAMERA_MOVR;
	//		g_Camera.posR.y += cosf(0.0f)*CAMERA_MOVR;
	//	}
	//	if (GetKeyboardPress(DIK_B) == true)
	//	{
	//		g_Camera.posR.x += sinf(D3DX_PI)*CAMERA_MOVR;
	//		g_Camera.posR.y += cosf(D3DX_PI)*CAMERA_MOVR;
	//	}
	//	if (GetKeyboardPress(DIK_Q) == true)
	//	{
	//		g_Camera.rot.y -= 0.05f;

	//		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
	//		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;

	//	}
	//	if (GetKeyboardPress(DIK_E) == true)
	//	{
	//		g_Camera.rot.y += 0.05f;

	//		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
	//		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;

	//	}
	//}
	if (g_MODE == MODE_TITLE)
	{
		g_Camera.rot.y += 0.01f;

		g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y - D3DX_PI) * g_Camera.fDistance;
		g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y - D3DX_PI) * g_Camera.fDistance;

	}

}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjextion);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjextion,
							D3DXToRadian(45.0f),//����p
							(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,//��ʃT�C�Y�i�䗦�j
							10.0f,//��O�̈ʒu
							1000.0f);//���̈ʒu

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjextion);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_Camera.mtxView, 
						&g_Camera.posV,
						&g_Camera.posR, 
						&g_Camera.posU);
		
	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);

}
//=============================================================================
// �J�����̎擾
//=============================================================================
Camera*GetCamera(void)
{
	return &g_Camera;
}