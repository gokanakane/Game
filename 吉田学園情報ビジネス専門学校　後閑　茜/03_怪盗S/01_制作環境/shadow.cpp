//=============================================================================
//
// �e���� [Shadow.cpp]
// Author : ��Ո�
//
//=============================================================================
#include "shadow.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;//�e�N�X�`���ւ̃|�C���^
Shadow g_Shadow[MAX_SHADOW];			   //�e�̏��

//=============================================================================
// ����������
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	for (int nCnt1 = 0; nCnt1 < MAX_SHADOW; nCnt1++)
	{
		g_Shadow[nCnt1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCnt1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCnt1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Shadow[nCnt1].bUse = false;

	}

	MakeVertexShadow(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP,
							D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND,
							D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,
							D3DBLEND_ONE);
	//z�e�X�g
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Shadow[nCnt].g_mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCnt].rot.y, g_Shadow[nCnt].rot.x, g_Shadow[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Shadow[nCnt].g_mtxWorld, &g_Shadow[nCnt].g_mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCnt].pos.x, g_Shadow[nCnt].pos.y, g_Shadow[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Shadow[nCnt].g_mtxWorld, &g_Shadow[nCnt].g_mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCnt].g_mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0,
				sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

		if (g_Shadow[nCnt].bUse == true)
		{
			// �e�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);
		}
	}

	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP,
							D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,
							D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,
							D3DBLEND_INVSRCALPHA);
	//z�e�X�g
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, SHADOW_TEXTUER, &g_pTextureShadow);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// ���_���̐ݒ�
	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

		//�@���̐ݒ�i���̐�����S��������1.0�ɂȂ�j
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[��ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�f�[�^�̃|�C���^���S���炷
		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();

}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			g_Shadow[nCntShadow].pos = D3DXVECTOR3(pos.x, 0.0f, pos.z);
			g_Shadow[nCntShadow].rot = rot;
			g_Shadow[nCntShadow].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			g_Shadow[nCntShadow].bUse = true;

			break;
		}

	}
	return nCntShadow;
}

//=============================================================================
// �e�̈ʒu�̐ݒ菈��
//=============================================================================
void SetPositionShadow(int IdxShadow, D3DXVECTOR3 pos)
{
	if (g_Shadow[IdxShadow].bUse == true)
	{
		g_Shadow[IdxShadow].pos = D3DXVECTOR3(pos.x, 0.0f, pos.z);

	}
}
//=============================================================================
// �e�̏�������
//=============================================================================
void DeleteShadow(int nIdxShadow)
{
	g_Shadow[nIdxShadow].bUse = false;
}
