//=============================================================================
//
// �^�C�g���w�i���� [TitleBG.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "TitleBG.h"
#include"input.h"
#include "fade.h"
#include"sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLEBG_TEXTUER "data\\TEXTURE\\TitleBG00.png" //�ǂݍ��ރe�N�X�`��
#define TITLEBG_TEXTUER1 "data\\TEXTURE\\TitlePC.png" //�ǂݍ��ރe�N�X�`��

#define TITLEBG_POS_X (0)					   //�^�C�g������X
#define TITLEBG_POS_Y (0)					   //�^�C�g������Y
#define TITLEBG_WIDTH (SCREEN_WIDTH)			   //�^�C�g���̕�
#define TITLEBG_HEIGHT (SCREEN_HEIGHT)		   //�^�C�g������
#define MAX_TEX (2)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitleBG[MAX_TEX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleBG = NULL;
BGAnim g_BGAnim;
int g_nCntTitleBG;

//=============================================================================
// �^�C�g������������[InitTitle]
//=============================================================================
void InitTitleBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLEBG_TEXTUER,&g_pTextureTitleBG[0]);
	D3DXCreateTextureFromFile(pDevice, TITLEBG_TEXTUER1, &g_pTextureTitleBG[1]);

	g_BGAnim.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_BGAnim.nCntAnim = 0;
	g_BGAnim.PatternAnim = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffTitleBG, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitleBG->Lock(0, 0, (void**)&pVtx,0);

		//�^�C�g���w�i�̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(TITLEBG_POS_X, TITLEBG_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(TITLEBG_WIDTH, TITLEBG_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(TITLEBG_POS_X, TITLEBG_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(TITLEBG_WIDTH, TITLEBG_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

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

		//�^�C�g���w�i�̍��W�ݒ�
		pVtx[4].pos = D3DXVECTOR3(500, 220, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[5].pos = D3DXVECTOR3(700, 220, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[6].pos = D3DXVECTOR3(500, 420, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[7].pos = D3DXVECTOR3(700, 420, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		 //rhw�̐ݒ�
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//�^�C�g���w�i�F�ݒ�
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j

		//�^�C�g���w�i�e�N�X�`���̐ݒ�
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.25f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitleBG->Unlock();

}
//=============================================================================
//�^�C�g���I������ [UninitTitle]
//=============================================================================
void UninitTitleBG(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitleBG[nCnt] != NULL)
		{
			g_pTextureTitleBG[nCnt]->Release();
			g_pTextureTitleBG[nCnt] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitleBG != NULL)
	{
		g_pVtxBuffTitleBG->Release();
		g_pVtxBuffTitleBG = NULL;
	}

}

//=============================================================================
// �^�C�g���X�V����[UpdataTitle]
//=============================================================================
void UpdateTitleBG(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	g_nCntTitleBG++;
	g_BGAnim.nCntAnim++;

	if ((g_BGAnim.nCntAnim % 5) == 0)//��莞�Ԃ��o��
	{
		//�p�^�[�����X�V
		g_BGAnim.PatternAnim++;
	}

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitleBG->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i�X�N���[��
	pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nCntTitleBG*(0.008f + 1)), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + (g_nCntTitleBG*(0.008f + 1)), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (g_nCntTitleBG*(0.008f + 1)), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + (g_nCntTitleBG*(0.008f + 1)), 1.0f);

	//����L�����N�^�[
	pVtx[4].tex = D3DXVECTOR2(g_BGAnim.PatternAnim*0.25f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(g_BGAnim.PatternAnim*0.25f + 0.25f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(g_BGAnim.PatternAnim*0.25f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(g_BGAnim.PatternAnim*0.25f + 0.25f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitleBG->Unlock();

}
//=============================================================================
// �^�C�g���`�ʏ���[DrawTitle]
//=============================================================================
void DrawTitleBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitleBG[nCnt]);

		//�^�C�g���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}

}