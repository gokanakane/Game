//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "Tutorialbg.h"
#include "Item.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTutorialBG[MAX_TUTORIALBGTEX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialBG = NULL;
int g_nCntTutorialBG = 0;
TutorialCol g_Col;
TutorialCol g_Col2;
TutorialCol g_Col3;

int nTimeTutlial;

D3DXCOLOR FadeOut;
D3DXCOLOR FadeIN;
TutorialState state;
//=============================================================================
// �|���S������������[InitPolygon]
//=============================================================================
void InitTutorialBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	nTimeTutlial = 0;
	state = TUTORIALSTATE_NONE;
	FadeOut = D3DXCOLOR(1.0f, 1.0f,1.0f,0.0f);
	FadeIN = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);;

	g_Col.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Col.nChangeArpha = -0.01f;

	g_Col2.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_Col2.nChangeArpha = 0.01f;

	g_Col3.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_Col3.nChangeArpha = 0.01f;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TUTOTIALTEXTUER, &g_pTextureTutorialBG[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TUTOTIALTEXTUER1, &g_pTextureTutorialBG[1]);
	D3DXCreateTextureFromFile(pDevice, BG_TUTOTIALTEXTUER2, &g_pTextureTutorialBG[2]);
	D3DXCreateTextureFromFile(pDevice, BG_TUTOTIALTEXTUER3, &g_pTextureTutorialBG[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TUTORIALBGTEX, 
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffTutorialBG, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx,0);

		//�w�i�̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(BG_POS_X, -20, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, -20, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(BG_POS_X, 300, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 300, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

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

		//�������1---------------------------------
		//�w�i�̍��W�ݒ�
		pVtx[4].pos = D3DXVECTOR3(300, 15, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[5].pos = D3DXVECTOR3(1000, 15, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[6].pos = D3DXVECTOR3(300, 200, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[7].pos = D3DXVECTOR3(1000, 200, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

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

		//�������2-------------------------------
		//�w�i�̍��W�ݒ�
		pVtx[8].pos = D3DXVECTOR3(300, 40, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[9].pos = D3DXVECTOR3(1000, 40, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[10].pos = D3DXVECTOR3(300, 190, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[11].pos = D3DXVECTOR3(1000, 190, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		 //rhw�̐ݒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//�w�i�F�ݒ�
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);//��ڂ̒��_�̐F�w��i�E���j

		//�w�i�e�N�X�`���̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�������2-------------------------------
		//�w�i�̍��W�ݒ�
		pVtx[12].pos = D3DXVECTOR3(900, 300, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[13].pos = D3DXVECTOR3(SCREEN_WIDTH, 300, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[14].pos = D3DXVECTOR3(900, 400, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[15].pos = D3DXVECTOR3(SCREEN_WIDTH, 400, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

													//rhw�̐ݒ�
		pVtx[12].rhw = 1.0f;
		pVtx[13].rhw = 1.0f;
		pVtx[14].rhw = 1.0f;
		pVtx[15].rhw = 1.0f;

		//�w�i�F�ݒ�
		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

														 //�w�i�e�N�X�`���̐ݒ�
		pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTutorialBG->Unlock();

}
//=============================================================================
//�|���S���I������ [UninitPolygon]
//=============================================================================
void UninitTutorialBG(void)
{
	for (int nCnt = 0; nCnt < MAX_TUTORIALBGTEX; nCnt++)
	{//�e�N�X�`���̔j��
		if (g_pTextureTutorialBG[nCnt] != NULL)
		{
			g_pTextureTutorialBG[nCnt]->Release();
			g_pTextureTutorialBG[nCnt] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorialBG != NULL)
	{
		g_pVtxBuffTutorialBG->Release();
		g_pVtxBuffTutorialBG = NULL;
	}

}

//=============================================================================
// �|���S���X�V����[UpdataPolygon]
//=============================================================================
void UpdateTutorialBG(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^
	nTimeTutlial++;
	
	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx, 0);

	g_Col3.col.a += g_Col3.nChangeArpha;

	if (g_Col3.col.a <= 0.0f || g_Col3.col.a >= 1.0f)
	{
		g_Col3.nChangeArpha *= -1.0f;
	}

	if (nTimeTutlial > 180)
	{
		g_Col.col.a += g_Col.nChangeArpha;
		g_Col2.col.a += g_Col2.nChangeArpha;

		if (g_Col.col.a <= 0.0f || g_Col.col.a >= 1.0f)
		{
			if (g_Col2.col.a <= 0.0f || g_Col2.col.a >= 1.0f)
			{
				g_Col.nChangeArpha *= -1.0f;
				g_Col2.nChangeArpha *= -1.0f;

				nTimeTutlial = 0;
			}
		}
	}

	//�w�i�F�ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col.col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col.col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col.col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col.col.a);//��ڂ̒��_�̐F�w��i�E���j

	//�w�i�F�ݒ�
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col2.col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col2.col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col2.col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col2.col.a);//��ڂ̒��_�̐F�w��i�E���j

															 //�w�i�F�ݒ�
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col3.col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col3.col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col3.col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Col3.col.a);//��ڂ̒��_�̐F�w��i�E���j


	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTutorialBG->Unlock();


}
//=============================================================================
// �|���S���`�ʏ���[DrawPolygon]
//=============================================================================
void DrawTutorialBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TUTORIALBGTEX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutorialBG[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}
}