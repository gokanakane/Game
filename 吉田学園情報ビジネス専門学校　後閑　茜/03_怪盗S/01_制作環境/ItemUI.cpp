//=============================================================================
//
// �^�C������ [ItemUI.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "ItemUI.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexItemUI(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItemUI[MAX_ITEMUITEX] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUI = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
//=============================================================================
// ����������
//=============================================================================
void InitItemUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ITEMUI1, &g_pTextureItemUI[0]);
	D3DXCreateTextureFromFile(pDevice,TEXTURE_ITEMUI,&g_pTextureItemUI[1]);	


	// ���_���̍쐬
	MakeVertexItemUI(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitItemUI(void)
{
	for (int nCnt = 0; nCnt < MAX_ITEMUITEX; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureItemUI[nCnt] != NULL)
		{
			g_pTextureItemUI[nCnt]->Release();
			g_pTextureItemUI[nCnt] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItemUI != NULL)
	{
		g_pVtxBuffItemUI->Release();
		g_pVtxBuffItemUI = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItemUI(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItemUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffItemUI, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_HEIGTH; nCnt++)
	{
		if (nCnt < 4)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItemUI[1]);
		}
		else
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItemUI[0]);

		}
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt * 4,
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexItemUI(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_HEIGTH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemUI,
		NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItemUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHeigth = 0; nCntHeigth < MAX_HEIGTH - 1; nCntHeigth++)
	{
		// ���_����ݒ�	
		pVtx[0].pos = D3DXVECTOR3(1135.0f, 180.0f + (130.0f * nCntHeigth), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1250.0f, 180.0f + (130.0f * nCntHeigth), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1135.0f, 300.0f + (130.0f * nCntHeigth), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1250.0f, 300.0f + (130.0f * nCntHeigth), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�F
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

		
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}
	// ���_����ݒ�	
	pVtx[0].pos = D3DXVECTOR3(1100.0f, 130.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 130.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1100.0f, 180.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 180.0f, 0.0f);

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


	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffItemUI->Unlock();

}
