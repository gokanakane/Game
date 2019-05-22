//=============================================================================
//
// �^�C������ [ItemGetUI.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "ItemGetUI.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_ITEMGET "data/TEXTURE/Item001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ITEMGET1 "data/TEXTURE/Item002.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ITEMGET2 "data/TEXTURE/Item003.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ITEMGET3 "data/TEXTURE/Item004.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ITEMGET4 "data/TEXTURE/Key004.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_TEX (5)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexItemGetUI(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItemGetUI[MAX_TEX] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemGetUI = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
ItemUI g_ItemUI[MAX_TEX];
//=============================================================================
// ����������
//=============================================================================
void InitItemGetUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		g_ItemUI[nCnt].nType = 0;
		g_ItemUI[nCnt].bUse = false;
	}

			// ���_���̍쐬
	MakeVertexItemGetUI(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitItemGetUI(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureItemGetUI[nCnt] != NULL)
		{
			g_pTextureItemGetUI[nCnt]->Release();
			g_pTextureItemGetUI[nCnt] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItemGetUI != NULL)
	{
		g_pVtxBuffItemGetUI->Release();
		g_pVtxBuffItemGetUI = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItemGetUI(void)
{


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItemGetUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffItemGetUI, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_ItemUI[nCnt].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItemGetUI[g_ItemUI[nCnt].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexItemGetUI(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ITEMGET, &g_pTextureItemGetUI[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ITEMGET1, &g_pTextureItemGetUI[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ITEMGET2, &g_pTextureItemGetUI[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ITEMGET3, &g_pTextureItemGetUI[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ITEMGET4, &g_pTextureItemGetUI[4]);


	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemGetUI,
		NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItemGetUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHeigth = 0; nCntHeigth < MAX_TEX; nCntHeigth++)
	{
		// ���_����ݒ�	
		pVtx[0].pos = D3DXVECTOR3(1160.0f, 190.0f + (130.0f * nCntHeigth), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1230.0f, 190.0f + (130.0f * nCntHeigth), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1160.0f, 290.0f + (130.0f * nCntHeigth), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1230.0f, 290.0f + (130.0f * nCntHeigth), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�F
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffItemGetUI->Unlock();

}

//=============================================================================
// �A�C�e���Q�b�gUI�̐ݒ�
//=============================================================================
int SetItemGetUI(int nType)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_ItemUI[nCnt].bUse == false)
		{
			g_ItemUI[nCnt].nType = nType;
			g_ItemUI[nCnt].bUse = true;
			PlaySound(SOUND_LABEL_SE_ITEMGET);

			if (g_ItemUI[nCnt].nType > 3)
			{
				g_ItemUI[nCnt].nIdxItem = nCnt;
			}
			break;
		}
	}
	return nCnt;
}

//=============================================================================
// �A�C�e���Q�b�gUI�̏���
//=============================================================================
void DeleteItemGetUI(int nType)
{
	g_ItemUI[nType].bUse = false;

}

//=============================================================================
// �A�C�e���Q�b�g�̎擾
//=============================================================================
ItemUI*GetItemUI(void)
{
	return &g_ItemUI[0];
}

