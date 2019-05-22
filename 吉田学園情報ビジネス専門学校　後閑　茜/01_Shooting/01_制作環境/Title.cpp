//=============================================================================
//
// �^�C�g������ [Title.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Title.h"
#include"input.h"
#include "fade.h"
#include"sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_TEXTUER "data\\TEXTURE\\BG01.png" //�ǂݍ��ރe�N�X�`��
#define TITLE_TEXTUER1 "data\\TEXTURE\\press_enter.png" //�ǂݍ��ރe�N�X�`��
#define TITLE_TEXTUER2 "data\\TEXTURE\\Title.png" //�ǂݍ��ރe�N�X�`��
#define TITLE_POS_X (0)					   //�^�C�g������X
#define TITLE_POS_Y (0)					   //�^�C�g������Y
#define TITLE_WIDTH (SCREEN_WIDTH)			   //�^�C�g���̕�
#define TITLE_HEIGHT (SCREEN_HEIGHT)		   //�^�C�g������
#define MAX_TEX (3)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;

//=============================================================================
// �^�C�g������������[InitTitle]
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTUER,&g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTUER1, &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTUER2, &g_pTextureTitle[2]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffTitle, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx,0);

		//�^�C�g���w�i�̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�^�C�g���w�i�F�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j

		//�^�C�g���w�i�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//-------------------------------------------------------
		//�^�C�g�����S�̍��W�ݒ�
		pVtx[4].pos = D3DXVECTOR3(TITLE_POS_X+400, 500, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[5].pos = D3DXVECTOR3(TITLE_WIDTH-400, 500, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[6].pos = D3DXVECTOR3(TITLE_POS_X+400, TITLE_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[7].pos = D3DXVECTOR3(TITLE_WIDTH-400, TITLE_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		//rhw�̐ݒ�
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//�^�C�g�����S�F�ݒ�
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j

		//�^�C�g�����S�e�N�X�`���̐ݒ�
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

		//-------------------------------------------------------
		//�^�C�g�����S�̍��W�ݒ�
		pVtx[8].pos = D3DXVECTOR3(TITLE_POS_X+300 , 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[9].pos = D3DXVECTOR3(TITLE_WIDTH-300,0.0f , 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[10].pos = D3DXVECTOR3(TITLE_POS_X+300, 400.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[11].pos = D3DXVECTOR3(TITLE_WIDTH-300, 400.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

																		 //rhw�̐ݒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//�^�C�g�����S�F�ݒ�
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j

		//�^�C�g�����S�e�N�X�`���̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);




	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitle->Unlock();

}
//=============================================================================
//�^�C�g���I������ [UninitTitle]
//=============================================================================
void UninitTitle(void)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
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

	//Enter�L�[�������ꂽ
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{			
		PlaySound(SOUND_LABEL_SE_DECIDE);

		if (g_fade != FADE_OUT)
		{
			//���[�h�ݒ�
			SetFade(MODE_TUTORIAL);
		}
	}
}
//=============================================================================
// �^�C�g���`�ʏ���[DrawTitle]
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;
	//�f�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);

		//�^�C�g���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}

}