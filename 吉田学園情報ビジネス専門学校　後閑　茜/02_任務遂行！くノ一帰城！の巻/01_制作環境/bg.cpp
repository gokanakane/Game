//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "bg.h"

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

		//�w�i�̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(BG_POS_X, 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_WIDTH, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_WIDTH, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

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

		//-----------------�_
		//�w�i�̍��W�ݒ�
		pVtx[4].pos = D3DXVECTOR3(0, 100, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[5].pos = D3DXVECTOR3(BG_WIDTH, 100, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[6].pos = D3DXVECTOR3(0, 400, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[7].pos = D3DXVECTOR3(BG_WIDTH, 400, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

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
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

		//-----------------���
		////�w�i�̍��W�ݒ�
		//pVtx[8].pos = D3DXVECTOR3(0, 500, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		//pVtx[9].pos = D3DXVECTOR3(BG_WIDTH, 500, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		//pVtx[10].pos = D3DXVECTOR3(0, BG_WIDTH, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		//pVtx[11].pos = D3DXVECTOR3(BG_WIDTH, BG_WIDTH, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		//											   //rhw�̐ݒ�
		//pVtx[8].rhw = 1.0f;
		//pVtx[9].rhw = 1.0f;
		//pVtx[10].rhw = 1.0f;
		//pVtx[11].rhw = 1.0f;

		////�w�i�F�ݒ�
		//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		//pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		//pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		//pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

		////�w�i�e�N�X�`���̐ݒ�
		//pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);


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
	pVtx[4].tex = D3DXVECTOR2(0.0f + (g_nCntBG*(0.001f + 1)), 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[5].tex = D3DXVECTOR2(1.0f + (g_nCntBG*(0.001f + 1)), 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[6].tex = D3DXVECTOR2(0.0f + (g_nCntBG*(0.001f + 1)), 1.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[7].tex = D3DXVECTOR2(1.0f + (g_nCntBG*(0.001f + 1)), 1.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

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