//=============================================================================
//
// �Ǐ��� [Billboard.cpp]
// Author : ��Ո�
//
//=============================================================================
#include "billboard.h"
#include "shadow.h"
#include "Player.h"
#include "Game.h"
#include "score.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard= NULL;
LPDIRECT3DTEXTURE9 g_pTextureBillboard[MAX_TEX] = {};//�e�N�X�`���ւ̃|�C���^
Billboard g_Billboard[MAX_BILLBOARD];					//�ǂ̍ő吔
//=============================================================================
// ����������
//=============================================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		g_Billboard[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCnt].bUse = false;
		g_Billboard[nCnt].IdxShadow = SetShadow(g_Billboard[g_Billboard[nCnt].IdxShadow].pos, g_Billboard[g_Billboard[nCnt].IdxShadow].rot);
	}


	MakeVertexBillboard(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitBillboard(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_pTextureBillboard[nCnt] != NULL)
		{
			g_pTextureBillboard[nCnt]->Release();
			g_pTextureBillboard[nCnt] = NULL;
		}
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateBillboard(void)
{
	Player*pPlayer;
	pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Billboard[nCnt].bUse == true)
		{
			SetPositionShadow(g_Billboard[nCnt].IdxShadow, g_Billboard[nCnt].pos);
			if (g_Billboard[nCnt].pos.x - 10 <= pPlayer->pos.x
				&&g_Billboard[nCnt].pos.x + 10 >= pPlayer->pos.x
				&&g_Billboard[nCnt].pos.z - 10 <= pPlayer->pos.z 
				&&g_Billboard[nCnt].pos.z + 10 >= pPlayer->pos.z)
			{//�r���{�[�h�̂����蔻��
					g_Billboard[nCnt].bUse = false;
					AddScore(100);
			}

		}
		else
		{
			DeleteShadow(g_Billboard[nCnt].IdxShadow);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;				//�v�Z�p�}�g���b�N�X
	int nCntBillboard;
	//���C�g�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_Billboard[nCntBillboard].bUse == true)
		{

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Billboard[nCntBillboard].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_Billboard[nCntBillboard].mtxWorld._11 = mtxView._11;
			g_Billboard[nCntBillboard].mtxWorld._12 = mtxView._21;
			g_Billboard[nCntBillboard].mtxWorld._13 = mtxView._31;
			g_Billboard[nCntBillboard].mtxWorld._21 = mtxView._12;
			g_Billboard[nCntBillboard].mtxWorld._22 = mtxView._22;
			g_Billboard[nCntBillboard].mtxWorld._23 = mtxView._32;
			g_Billboard[nCntBillboard].mtxWorld._31 = mtxView._13;
			g_Billboard[nCntBillboard].mtxWorld._32 = mtxView._23;
			g_Billboard[nCntBillboard].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCntBillboard].pos.x, g_Billboard[nCntBillboard].pos.y, g_Billboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCntBillboard].mtxWorld, &g_Billboard[nCntBillboard].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCntBillboard].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0,
				sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBillboard[g_Billboard[nCntBillboard].Type]);

			// �ǂ̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBillboard * 4,
				2);
		}
	}
	//���e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//���C�g�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, KEY_TEXTUER, &g_pTextureBillboard[0]);
	D3DXCreateTextureFromFile(pDevice, KEY_TEXTUER1, &g_pTextureBillboard[1]);
	D3DXCreateTextureFromFile(pDevice, KEY_TEXTUER2, &g_pTextureBillboard[2]);
	D3DXCreateTextureFromFile(pDevice, KEY_TEXTUER3, &g_pTextureBillboard[3]);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	// ���_���̐ݒ�
	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

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
	g_pVtxBuffBillboard->Unlock();

}
//=============================================================================
// �ǂ̐ݒ菈��
//=============================================================================
void SetBillboard(D3DXVECTOR3 pos, int Type)
{
	int nCnt;
					
	for (nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Billboard[nCnt].bUse == false)
		{
			g_Billboard[nCnt].pos = pos;
			g_Billboard[nCnt].Type = Type;
			g_Billboard[nCnt].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
			g_Billboard[nCnt].bUse = true;
			break;
		}
	}
}