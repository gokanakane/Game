//=============================================================================
//
// �Z���N�g���Yes���� [Select_Yes.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "Title_Select.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "Font.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTitleSelect[MAX_TEX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleSelect = NULL;
Colstate g_ColState;
int g_nSelectManuT;

//=============================================================================
// ����������[InitPolygon]
//=============================================================================
void InitTitleSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	g_ColState = COLSTATE_GAMESTATE;
	g_nSelectManuT = 0;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLESELECT_TEXTUER, &g_pTitleSelect[0]);
	D3DXCreateTextureFromFile(pDevice, TITLESELECT_TEXTUER1, &g_pTitleSelect[1]);
	//D3DXCreateTextureFromFile(pDevice, TITLESELECT_TEXTUER2, &g_pTitleSelect[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleSelect, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitleSelect->Lock(0, 0, (void**)&pVtx, 0);

	//�I����-------------------------------------------
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(TITLESELECT_POS_X, TITLESELECT_POS_Y + (nCnt * 200.0f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(TITLESELECT_WIDTH, TITLESELECT_POS_Y + (nCnt * 200.0f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(TITLESELECT_POS_X, TITLESELECT_HEIGHT + (nCnt * 200.0f), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(TITLESELECT_WIDTH, TITLESELECT_HEIGHT + (nCnt * 200.0f), 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�w�i�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

		//�w�i�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
		
	}

	////�J�[�\��-------------------------------------------
	////���W�ݒ�
	//pVtx[8].pos = D3DXVECTOR3(100, 500, 0.0f);
	//pVtx[9].pos = D3DXVECTOR3(300, 500, 0.0f);
	//pVtx[10].pos = D3DXVECTOR3(100, 600, 0.0f);
	//pVtx[11].pos = D3DXVECTOR3(300, 600, 0.0f);

	////rhw�̐ݒ�
	//pVtx[8].rhw = 1.0f;
	//pVtx[9].rhw = 1.0f;
	//pVtx[10].rhw = 1.0f;
	//pVtx[11].rhw = 1.0f;

	////�w�i�F�ݒ�
	//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	////�w�i�e�N�X�`���̐ݒ�
	//pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitleSelect->Unlock();

}
//=============================================================================
//�I������ [UninitPolygon]
//=============================================================================
void UninitTitleSelect(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)

	{//�e�N�X�`���̔j��
		if (g_pTitleSelect[nCnt] != NULL)
		{
			g_pTitleSelect[nCnt]->Release();
			g_pTitleSelect[nCnt] = NULL;
		}
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitleSelect != NULL)
	{
		g_pVtxBuffTitleSelect->Release();
		g_pVtxBuffTitleSelect = NULL;
	}

}

//=============================================================================
// �X�V����[UpdataPolygon]
//=============================================================================
void UpdateTitleSelect(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^
	FADE g_Fade = GetFade();

	//�Z���N�g
	if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectManuT = (g_nSelectManuT + 1) % 2;
	}
	
	if (GetKeyboardTrigger(DIK_UP) == true)
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectManuT = (g_nSelectManuT + 1) % 2;
	}

	if (g_nSelectManuT == 0)
	{//�����J�n
		g_ColState = COLSTATE_GAMESTATE;
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				SetFade(MODE_GAME);
			}
		}
	}

	if (g_nSelectManuT == 1)
	{//�`���[�g���A��
		g_ColState = COLSTATE_TUTORIAL;
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				SetFade(MODE_TUTORIAL);
			}
		}
	}


	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitleSelect->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_ColState)
	{
	case COLSTATE_GAMESTATE:
		//�w�i�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		
		break;

	case COLSTATE_TUTORIAL:
		//�w�i�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j

		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

		break;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitleSelect->Unlock();


}
//=============================================================================
// �`�ʏ���[DrawPolygon]
//=============================================================================
void DrawTitleSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleSelect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTitleSelect[nCnt]);

		//�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}
}
