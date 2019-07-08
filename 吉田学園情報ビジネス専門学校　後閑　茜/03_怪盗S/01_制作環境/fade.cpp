//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "fade.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureFade[MAX_FADETEX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
FADE					g_fade;					// �t�F�[�h���
MODE					g_modeNext;				// ���̃��[�h
D3DXCOLOR				g_colorFade;			// �t�F�[�h�F
int g_nCntAnimF;								//�A�j���[�V�����J�E���^�[
int g_nPatturnAnimF;							//�A�j���[�V�����̃p�^�[��
bool g_bAnimF;									//�A�j���[�V�����̎g�p��
//=============================================================================
// ����������
//=============================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�l�̏�����
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_nCntAnimF = 0;
	g_nPatturnAnimF = 0;
	g_bAnimF = false;

	// ���_���̐ݒ�
	MakeVertexFade(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
	for (int nCnt = 0; nCnt < MAX_FADETEX; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureFade[nCnt] != NULL)
		{
			g_pTextureFade[nCnt]->Release();
			g_pTextureFade[nCnt] = NULL;
		}

	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)//�t�F�[�h�C�����
		{
			g_colorFade.a -= 0.03f;
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;//�������ĂȂ���Ԃ�
			}
		}

		else if (g_fade == FADE_OUT)//�t�F�[�h�A�E�g���
		{
			g_colorFade.a += 0.03f;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�

				//���[�h�̐ݒ�
				SetMode(g_modeNext);
			}
		}

		g_nCntAnimF++;

		if (rand() % 50 == 0)
		{
			g_bAnimF = true;
		}
		if (g_bAnimF == true)
		{
			if (g_nCntAnimF % 4 == 0)
			{
				g_nPatturnAnimF++;
			}

			if (g_nPatturnAnimF >= MAX_ANIM)
			{
				g_nPatturnAnimF = 0;
				g_bAnimF = false;
			}
		}
		//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//�t�F�[�h���_�J���[�̍X�V
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);//�O�ڂ̒��_�̐F�w��i�E���j

		 //Now Loading���_�J���[�̍X�V
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//�O�ڂ̒��_�̐F�w��i�E���j

		//�L���_�J���[�̍X�V
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorFade.a);//�O�ڂ̒��_�̐F�w��i�E���j

		//�L�e�N�X�`�����W�̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(g_nPatturnAnimF*0.25f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(g_nPatturnAnimF*0.25f + 0.25f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(g_nPatturnAnimF*0.25f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(g_nPatturnAnimF*0.25f + 0.25f, 1.0f);

		//���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffFade->Unlock();

	}

}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCnt = 0; nCnt < MAX_FADETEX; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureFade[nCnt]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			NUM_POLYGON);

	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	D3DXCreateTextureFromFile(pDevice, LOAD_TEX, &g_pTextureFade[0]);
	D3DXCreateTextureFromFile(pDevice, LOAD_TEX1, &g_pTextureFade[1]);
	D3DXCreateTextureFromFile(pDevice, LOAD_TEX2, &g_pTextureFade[2]);


	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FADETEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//�t�F�[�h-----------------------------------------------
	// ���_�o�b�t�@�̏���ݒ�
	pVtx[0].pos = D3DXVECTOR3(VTX_POS_X, VTX_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, VTX_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(VTX_POS_X, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	//���_�F
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
	
	//Now Loading-----------------------------------------------
	// ���_�o�b�t�@�̏���ݒ�
	pVtx[4].pos = D3DXVECTOR3(700, 600, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(1100, 600, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(700, SCREEN_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(1100, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�F
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�L-----------------------------------------------
	// ���_�o�b�t�@�̏���ݒ�
	pVtx[8].pos = D3DXVECTOR3(1100, 600, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH, 600, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(1100, SCREEN_HEIGHT, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.25f, 1.0f);

	//���_�F
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffFade->Unlock();


}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void SetFade(MODE modeNext)
{
		g_fade = FADE_OUT;
		g_modeNext = modeNext;
		g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
FADE GetFade(void)
{
	return g_fade;
}

