//=============================================================================
//
// �^�C�g���w�i���� [TitleRogo.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "TitleRogo.h"
#include"input.h"
#include "fade.h"
#include"sound.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitleRogo[MAX_TITLEROGOTEX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleRogo = NULL;
RogoAnim g_Rogo;
RogoState state;
int g_nTimeRogo;

//=============================================================================
// �^�C�g������������[InitTitle]
//=============================================================================
void InitTitleRogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLEROGO_TEXTUER,&g_pTextureTitleRogo[0]);
	D3DXCreateTextureFromFile(pDevice, TITLEROGO_TEXTUER1, &g_pTextureTitleRogo[1]);
	D3DXCreateTextureFromFile(pDevice, TITLEROGO_TEXTUER2, &g_pTextureTitleRogo[2]);
	D3DXCreateTextureFromFile(pDevice, TITLEROGO_TEXTUER3, &g_pTextureTitleRogo[3]);

	g_Rogo.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Rogo.nCntAnim = 0;
	g_Rogo.nPatturnAnim = 0;
	g_Rogo.nChangeArpha = 0.15f;
	g_Rogo.bAnim = false;

	state = ROGO_NONE;

	g_nTimeRogo = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLEROGOTEX,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffTitleRogo, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitleRogo->Lock(0, 0, (void**)&pVtx,0);

		//�^�C�g���w�i�̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(50, 50, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(1200, 50, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(50, 200, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(1200, 200, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

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

		//�藠��----------------------------------------
		pVtx[4].pos = D3DXVECTOR3(750, 100, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[5].pos = D3DXVECTOR3(850, 100, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[6].pos = D3DXVECTOR3(750, 170, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[7].pos = D3DXVECTOR3(850, 170, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	  //rhw�̐ݒ�
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//�^�C�g���w�i�F�ݒ�
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

		//�^�C�g���w�i�e�N�X�`���̐ݒ�
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.25f, 1.0f);

		//PRESS_ENTER----------------------------------------
		pVtx[8].pos = D3DXVECTOR3(400, 600, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[9].pos = D3DXVECTOR3(900, 600, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[10].pos = D3DXVECTOR3(400, 700, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[11].pos = D3DXVECTOR3(900, 700, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		 //rhw�̐ݒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//�^�C�g���w�i�F�ݒ�
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

		//�^�C�g���w�i�e�N�X�`���̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);


		//�C�����s----------------------------------------
		pVtx[12].pos = D3DXVECTOR3(100, 30, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[13].pos = D3DXVECTOR3(450, 30, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[14].pos = D3DXVECTOR3(100, 130, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[15].pos = D3DXVECTOR3(450, 130, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

												   //rhw�̐ݒ�
		pVtx[12].rhw = 1.0f;
		pVtx[13].rhw = 1.0f;
		pVtx[14].rhw = 1.0f;
		pVtx[15].rhw = 1.0f;

		//�^�C�g���w�i�F�ݒ�
		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

														 //�^�C�g���w�i�e�N�X�`���̐ݒ�
		pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitleRogo->Unlock();

}
//=============================================================================
//�^�C�g���I������ [UninitTitle]
//=============================================================================
void UninitTitleRogo(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLEROGOTEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitleRogo[nCnt] != NULL)
		{
			g_pTextureTitleRogo[nCnt]->Release();
			g_pTextureTitleRogo[nCnt] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitleRogo != NULL)
	{
		g_pVtxBuffTitleRogo->Release();
		g_pVtxBuffTitleRogo = NULL;
	}

}

//=============================================================================
// �^�C�g���X�V����[UpdataTitle]
//=============================================================================
void UpdateTitleRogo(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^
	FADE g_fade;
	g_fade = GetFade();

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitleRogo->Lock(0, 0, (void**)&pVtx, 0);

	switch (state)
	{
	case ROGO_NONE:
		break;

	case ROGO_FLASH:

		if (g_Rogo.col.a <= 0.0f)
		{
			g_Rogo.col.a = 1.0f;
			if (g_Rogo.col.a >= 1.0f)
			{
				g_Rogo.col.a = 0.0f;
			}
		}
		g_Rogo.col.a += g_Rogo.nChangeArpha;

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a );//��ڂ̒��_�̐F�w��i�E���j
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a );//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);//�O�ڂ̒��_�̐F�w��i�E���j

		g_nTimeRogo++;

		if (g_nTimeRogo < 30)
		{
			//���[�h�ݒ�
			SetFade(MODE_TUTORIAL);

		}
		break;
	}

	g_Rogo.nCntAnim++;


	if (rand() % 100 == 0)
	{
		g_Rogo.bAnim = true;
	}

	if (g_Rogo.bAnim == true)
	{
		if (g_Rogo.nCntAnim % 4 == 0)
		{
			g_Rogo.nPatturnAnim++;
		}

		//�藠���e�N�X�`���̐ݒ�
		pVtx[4].tex = D3DXVECTOR2(g_Rogo.nPatturnAnim*0.25f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(g_Rogo.nPatturnAnim*0.25f + 0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(g_Rogo.nPatturnAnim*0.25f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(g_Rogo.nPatturnAnim*0.25f + 0.25f, 1.0f);

		if (g_Rogo.nPatturnAnim >= MAX_ANIMATION)
		{
			g_Rogo.nPatturnAnim = 0;
			g_Rogo.bAnim = false;
		}
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

	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Rogo.col.a);//�O�ڂ̒��_�̐F�w��i�E���j

	 //���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitleRogo->Unlock();


}
//=============================================================================
// �^�C�g���`�ʏ���[DrawTitle]
//=============================================================================
void DrawTitleRogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleRogo, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TITLEROGOTEX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitleRogo[nCnt]);

		//�^�C�g���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}

}
//=============================================================================
// ��Ԃ̎擾
//=============================================================================
RogoState*GetState(void)
{
	return &state;
}