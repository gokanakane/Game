//=============================================================================
//
// �w�i���� [.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "tutorial.h"
#include "fade.h"
#include "input.h"
#include "Tutorial.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_POS_X (0)					   //�w�i����X
#define BG_POS_Y (0)					   //�w�i����Y
#define TUTOTIAL_TEXTUER0 " "
#define TUTOTIAL_TEXTUER "data\\TEXTURE\\Tutorial\\Tutorial204.png"
#define TUTOTIAL_TEXTUER1 "data\\TEXTURE\\Tutorial\\Tutorial001.png"
#define TUTOTIAL_TEXTUER2 "data\\TEXTURE\\Tutorial\\Tutorial002-5.png"
#define MAX_TEX  (4)					   //�e�N�X�`���̖���
#define MAX_ANIM (4)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTutorial[MAX_TEX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;

int g_nCntAnimT;									//�A�j���[�V�����J�E���^�[
int g_nPatturnAnimT;								//�A�j���[�V�����p�^�[��
bool g_bAnimT;										//�A�j���[�V�����̎g�p��7
int g_MoveTex;
//=============================================================================
// �|���S������������[InitPolygon]
//=============================================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	g_nCntAnimT = 0;
	g_nPatturnAnimT = 0;
	g_bAnimT = false;
	g_MoveTex = 0;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TUTOTIAL_TEXTUER0, &g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice, TUTOTIAL_TEXTUER, &g_pTextureTutorial[1]);
	D3DXCreateTextureFromFile(pDevice, TUTOTIAL_TEXTUER1, &g_pTextureTutorial[2]);
	D3DXCreateTextureFromFile(pDevice, TUTOTIAL_TEXTUER2, &g_pTextureTutorial[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, BG_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

																 //rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

													//�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�w�i------------------------------------------------------------
	//�w�i�̍��W�ݒ�
	pVtx[4].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH, BG_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[6].pos = D3DXVECTOR3(BG_POS_X, 400.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH, 400.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	//rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

	//�w�i�e�N�X�`���̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.25f, 1.0f);

	//�L------------------------------------------------------------
	//�w�i�̍��W�ݒ�
	pVtx[8].pos = D3DXVECTOR3(900, 400, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH, 400, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(900, SCREEN_HEIGHT, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�w�i�e�N�X�`���̐ݒ�
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.25f, 1.0f);

	//�����o��------------------------------------------------------------
	//�w�i�̍��W�ݒ�
	pVtx[12].pos = D3DXVECTOR3(100.0f, 400, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(900, 400, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(100.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(900, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[12].rhw = 1.0f;
	pVtx[13].rhw = 1.0f;
	pVtx[14].rhw = 1.0f;
	pVtx[15].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�w�i�e�N�X�`���̐ݒ�
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTutorial->Unlock();

}
//=============================================================================
//�|���S���I������ [UninitPolygon]
//=============================================================================
void UninitTutorial(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

}
//=============================================================================
// �|���S���X�V����[UpdataPolygon]
//=============================================================================
void UpdateTutorial(void)
{
	FADE g_fade;
	g_fade = GetFade();
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//Enter�L�[�������ꂽ
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			SetFade(MODE_GAME);
		}
	}

	if (GetKeyboardTrigger(DIK_D) == true)
	{
		g_MoveTex += 1;
		PlaySound(SOUND_LABEL_SE_SELECT);

	}
	if (GetKeyboardTrigger(DIK_A) == true)
	{
		g_MoveTex -= 1;
		PlaySound(SOUND_LABEL_SE_SELECT);

	}

	g_nCntAnimT++;

	if (rand() % 50 == 0)
	{
		g_bAnimT = true;
	}
	if (g_bAnimT == true)
	{
		if (g_nCntAnimT % 4 == 0)
		{
			g_nPatturnAnimT++;
		}

		if (g_nPatturnAnimT >= MAX_ANIM)
		{
			g_nPatturnAnimT = 0;
			g_bAnimT = false;
		}
	}

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//�L�e�N�X�`�����W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f + (g_MoveTex*0.25f + 1), 0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.25f + (g_MoveTex*0.25f + 1), 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f + (g_MoveTex*0.25f + 1), 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.25f + (g_MoveTex*0.25f + 1), 1.0f);

	pVtx[8].tex = D3DXVECTOR2(g_nPatturnAnimT*0.25f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(g_nPatturnAnimT*0.25f + 0.25f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(g_nPatturnAnimT*0.25f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(g_nPatturnAnimT*0.25f + 0.25f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTutorial->Unlock();


}
//=============================================================================
// �|���S���`�ʏ���[DrawPolygon]
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;


	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutorial[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}

}