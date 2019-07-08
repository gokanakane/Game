//=============================================================================
//
// �������� [Font.h]
// Author : Gokan Akane
//
//=============================================================================
#include "Font.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXFONT g_pFont[MAX_LINE] = {};		//�t�H���g�ւ̃|�C���^
Font g_Font[MAX_LINE];

//*****************************************************************************
// ����������
//*****************************************************************************
void InitFont(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		g_Font[nCnt].font[0] = {};
		g_Font[nCnt].bUse = false;

		//�t�H���g�̐ݒ�
		D3DXCreateFont(pDevice, 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, //�T�C�Y�AX,Y,Z
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont[nCnt]);
	}
}
//*****************************************************************************
// �I������
//*****************************************************************************
void UninitFont(void)
{
	//�t�H���g�̊J��
	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		if (g_pFont[nCnt] != NULL)
		{
			g_pFont[nCnt]->Release();
			g_pFont[nCnt] = NULL;
		}
	}
}
//*****************************************************************************
// �X�V����
//*****************************************************************************
void UpdateFont(void) 
{

}
//*****************************************************************************
// �`�揈��
//*****************************************************************************
void DrawFont(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//X���W�AY���W�AX�`��͈́AY�`��͈�

	//�e�L�X�g�̕`��
	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		if (g_Font[nCnt].bUse == true)
		{
			g_pFont[0]->DrawText(NULL, &g_Font[nCnt].font[0], -1, &rect, DT_LEFT, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		}
	}

}
//*****************************************************************************
// �����̐ݒ�
//*****************************************************************************
void SetFont(char Font[256])
{
	for (int nCnt = 0; nCnt < MAX_LINE; nCnt++)
	{
		if (g_Font[nCnt].bUse == false)
		{
			wsprintf(&g_Font[nCnt].font[0], "%s", &Font[0]);
		
			g_Font[nCnt].bUse = true;
			break;
		}
	}
}
