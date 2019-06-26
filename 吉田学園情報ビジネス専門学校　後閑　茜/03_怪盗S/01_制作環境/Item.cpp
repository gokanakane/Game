//=============================================================================
//
// �Ǐ��� [Item.cpp]
// Author : ��Ո�
//
//=============================================================================
#include "Item.h"
#include "shadow.h"
#include "Player.h"
#include "Game.h"
#include "score.h"
#include "ItemGetUI.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ITEM_TEXTURE1 "data\\TEXTURE\\Object\\Item001.png"
#define ITEM_TEXTURE2 "data\\TEXTURE\\Object\\Item002.png"
#define ITEM_TEXTURE3 "data\\TEXTURE\\Object\\Item003.png"
#define ITEM_TEXTURE4 "data\\TEXTURE\\Object\\Item004.png"
#define ITEM_TEXTURE5 "data\\TEXTURE\\Object\\Key004.png"


#define MAX_TEX (5)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexItem(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem= NULL;
LPDIRECT3DTEXTURE9 g_pTextureItem[MAX_TEX] = {};//�e�N�X�`���ւ̃|�C���^
Item g_Item[MAX_ITEM];					//�ǂ̍ő吔
//=============================================================================
// ����������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		g_Item[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCnt].bUse = false;
		g_Item[nCnt].IdxShadow = SetShadow(g_Item[g_Item[nCnt].IdxShadow].pos, g_Item[g_Item[nCnt].IdxShadow].rot);
	}


	MakeVertexItem(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_pTextureItem[nCnt] != NULL)
		{
			g_pTextureItem[nCnt]->Release();
			g_pTextureItem[nCnt] = NULL;
		}
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	Player*pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_Item[nCnt].bUse == true)
		{
			SetPositionShadow(g_Item[nCnt].IdxShadow, g_Item[nCnt].pos);
			if (g_Item[nCnt].pos.x - 10 < pPlayer->pos.x
				&&g_Item[nCnt].pos.x + 10 > pPlayer->pos.x
				&&g_Item[nCnt].pos.z - 10 < pPlayer->pos.z
				&&g_Item[nCnt].pos.z + 10 > pPlayer->pos.z)
			{//�r���{�[�h�̂����蔻��
				g_Item[nCnt].bUse = false;
				DeleteShadow(g_Item[nCnt].IdxShadow);
				g_Item[nCnt].IdxItem = SetItemGetUI(nCnt);
				AddScore(2000);
				PlaySound(SOUND_LABEL_SE_ITEMGET);
			}
		}
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;				//�v�Z�p�}�g���b�N�X
	int nCntItem;

	//���C�g�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Item[nCntItem].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_Item[nCntItem].mtxWorld._11 = mtxView._11;
			g_Item[nCntItem].mtxWorld._12 = mtxView._21;
			g_Item[nCntItem].mtxWorld._13 = mtxView._31;
			g_Item[nCntItem].mtxWorld._21 = mtxView._12;
			g_Item[nCntItem].mtxWorld._22 = mtxView._22;
			g_Item[nCntItem].mtxWorld._23 = mtxView._32;
			g_Item[nCntItem].mtxWorld._31 = mtxView._13;
			g_Item[nCntItem].mtxWorld._32 = mtxView._23;
			g_Item[nCntItem].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Item[nCntItem].pos.x, g_Item[nCntItem].pos.y, g_Item[nCntItem].pos.z);
			D3DXMatrixMultiply(&g_Item[nCntItem].mtxWorld, &g_Item[nCntItem].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCntItem].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffItem, 0,
				sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_Item[nCntItem].Type]);

			// �ǂ̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntItem * 4,
				2);
		}
	}
	//���e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//���C�g�̗L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexItem(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE1, &g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE2, &g_pTextureItem[1]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE3, &g_pTextureItem[2]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE4, &g_pTextureItem[3]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE5, &g_pTextureItem[4]);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	// ���_���̐ݒ�
	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(5.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);

		//�@���̐ݒ�i���̐�����S��������1.0(-1.0)�ɂȂ�j
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[��ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffItem->Unlock();

}
//=============================================================================
// �A�C�e���̐ݒ菈��
//=============================================================================
void SetItem(D3DXVECTOR3 pos, int Type)
{
	int nCnt;

	for (nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		if (g_Item[nCnt].bUse == false)
		{
			g_Item[nCnt].pos = pos;
			g_Item[nCnt].Type = Type;
			g_Item[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Item[nCnt].bUse = true;
			break;
		}
	}
}

//=============================================================================
// �A�C�e���Q�b�gUI�̏���
//=============================================================================
void DeleteItem(int nType)
{
	if (g_Item[nType].bUse == true)
	{
		g_Item[nType].bUse = false;
		SetItemGetUI(nType);
		AddScore(2000);

	}
}
//=============================================================================
// �A�C�e���̎擾
//=============================================================================
Item *GetItem(void)
{
	return &g_Item[0];
}
