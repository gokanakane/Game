//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "bg.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_TEXTUER1 "data\\TEXTURE\\bg104.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTUER  "data\\TEXTURE\\bg103.png" //�ǂݍ��ރe�N�X�`��
#define BG_POS_X (0)					   //�w�i����X
#define BG_POS_Y (0)					   //�w�i����Y
#define BG_WIDTH (SCREEN_WIDTH)			   //�w�i�̕�
#define BG_HEIGHT (SCREEN_HEIGHT)		   //�w�i����
#define MAX_TEX  (2)					   //�e�N�X�`���̖���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBG[MAX_TEX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;
int g_nCntBG = 0;

//=============================================================================
// �|���S������������[InitPolygon]
//=============================================================================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^
	int nCnt;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTUER, &g_pTextureBG[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTUER1, &g_pTextureBG[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX, 
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffBG, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx,0);

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�w�i�̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�w�i�F�ݒ�
		pVtx[0].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

		//�w�i�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���炷
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBG->Unlock();

}
//=============================================================================
//�|���S���I������ [UninitPolygon]
//=============================================================================
void UninitBG(void)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBG[nCnt] != NULL)
		{
			g_pTextureBG[nCnt]->Release();
			g_pTextureBG[nCnt] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}

}

//=============================================================================
// �|���S���X�V����[UpdataPolygon]
//=============================================================================
void UpdateBG(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	g_nCntBG++;

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

		//�w�i�̍��W�ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f + (-g_nCntBG*(0.001f + 1)));//��ڂ̒��_�̏ꏊ�w��
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f + (-g_nCntBG*(0.001f + 1)));//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f + (-g_nCntBG*(0.001f + 1)));//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f + (-g_nCntBG*(0.001f + 1)));//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBG->Unlock();

}
//=============================================================================
// �|���S���`�ʏ���[DrawPolygon]
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBG[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt * 4,
			2);
	}
}