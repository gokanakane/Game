//=============================================================================
//
// �^�C�g������ [Title.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "Title.h"
#include "camera.h"
#include "light.h"
#include "Stage.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "Title_Select.h"
#include "Obj.h"
#include "Wall.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
RogoAnim g_Rogo;
RogoState state;
int g_nTimeRogo;
int g_nCntTitleTime;			//�t�F�[�h����
bool g_bSelect;

//=============================================================================
// �^�C�g������������[InitTitle]
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	g_nCntTitleTime = 0;

	InitCamera();
	InitLight();
	InitStage();
	InitWall();
	InitTitleSelect();
	InitObj();

	//����
	SetObj(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);


	g_bSelect = false;

				   //�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLEROGO_TEXTUER, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLEROGO_TEXTUER1, &g_pTextureTitle[1]);

	g_Rogo.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Rogo.nChangeArpha = 0.05f;
	g_Rogo.bAnim = false;
	state = ROGO_NONE;
	g_nTimeRogo = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�^�C�g�����S--------------------------------------------------------
	//�^�C�g���w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(1200.0f, 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(0.0f, 300.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(1200.0f, 300.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�^�C�g���w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

	//�^�C�g���w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//PRESS_ENTRE--------------------------------------------------------
	//�^�C�g���w�i�̍��W�ݒ�
	pVtx[4].pos = D3DXVECTOR3(300.0f, 600.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(1000.0f, 600.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(300.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(1000.0f, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//�^�C�g���w�i�F�ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�^�C�g���w�i�e�N�X�`���̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitle->Unlock();


}
//=============================================================================
//�^�C�g���I������ [UninitTitle]
//=============================================================================
void UninitTitle(void)
{
	UninitCamera();
	UninitLight();
	UninitStage();
	UninitWall();
	UninitTitleSelect();
	UninitObj();

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}

//=============================================================================
// �^�C�g���X�V����[UpdataTitle]
//=============================================================================
void UpdateTitle(void)
{
	FADE g_fade;
	g_fade = GetFade();
	g_nCntTitleTime++;
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	UpdateCamera();
	UpdateLight();
	UpdateStage();
	UpdateWall();
	UpdateObj();

	switch (state)
	{
	case ROGO_NONE:
		if (g_Rogo.col.a <= 0.0f || g_Rogo.col.a >= 1.0f)
		{
			g_Rogo.nChangeArpha *= 1.0f;
		}
		g_Rogo.col.a += g_Rogo.nChangeArpha;

		//���ԂŐ؂�ւ�
		if (g_nCntTitleTime > 600)
		{
			if (g_fade != FADE_OUT)
			{
				SetFade(MODE_RANKING);
			}
		}

		break;

	case ROGO_FLASH:
		g_Rogo.col.a = -0.1f;
		g_bSelect = true;
		break;
	}

	if (g_Rogo.col.a <= 0.0f || g_Rogo.col.a >= 1.0f)
	{
		g_Rogo.nChangeArpha *= -1;
	}
	g_Rogo.col.a += g_Rogo.nChangeArpha;

	//Enter�L�[�������ꂽ
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			state = ROGO_FLASH;
		}
	}

	if (g_bSelect == true)
	{
		UpdateTitleSelect();
	}

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�^�C�g���w�i�F�ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitle->Unlock();


}
//=============================================================================
// �^�C�g���`�ʏ���[DrawTitle]
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�C�X���擾����
	pDevice = GetDevice();

	SetCamera();
	DrawStage();
	DrawWall();
	DrawObj();
	DrawTitleSelect();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);

		//�^�C�g���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}

}