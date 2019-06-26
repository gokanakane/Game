//=============================================================================
//
// �Ǐ��� [Explosion.cpp]
// Author : ��Ո�
//
//=============================================================================
#include "explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EXPLOSION_TEXTUER "data\\TEXTURE\\Effect\\explosion000.png"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;//�e�N�X�`���ւ̃|�C���^
Explosion g_Explosion[MAX_EXPLOSION];					//�ǂ̍ő吔
//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		g_Explosion[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCnt].nCntAnim = 0;
		g_Explosion[nCnt].nPatturnAnim = 0;
		g_Explosion[nCnt].bUse = false;

	}

	MakeVertexExplosion(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == true)
		{
			g_Explosion[nCnt].nCntAnim++;
			if ((g_Explosion[nCnt].nCntAnim % 3) == 0)//��莞�Ԃ��o��
			{
				//�p�^�[�����X�V
				g_Explosion[nCnt].nPatturnAnim++;
			}

			pVtx[0].tex = D3DXVECTOR2((g_Explosion[nCnt].nPatturnAnim*0.125f) + 0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_Explosion[nCnt].nPatturnAnim*0.125f) + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_Explosion[nCnt].nPatturnAnim*0.125f) + 0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_Explosion[nCnt].nPatturnAnim*0.125f) + 0.125f, 1.0f);

			if (g_Explosion[nCnt].nPatturnAnim >= 8)
			{
				g_Explosion[nCnt].bUse = false;
				g_Explosion[nCnt].nPatturnAnim = 0;
			}
		}

		pVtx += 4;

	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffExplosion->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;				//�v�Z�p�}�g���b�N�X
	int nCntExplosion;

	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//z�e�X�g
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_Explosion[nCntExplosion].bUse == true)
		{

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Explosion[nCntExplosion].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_Explosion[nCntExplosion].mtxWorld._11 = mtxView._11;
			g_Explosion[nCntExplosion].mtxWorld._12 = mtxView._21;
			g_Explosion[nCntExplosion].mtxWorld._13 = mtxView._31;
			g_Explosion[nCntExplosion].mtxWorld._21 = mtxView._12;
			g_Explosion[nCntExplosion].mtxWorld._22 = mtxView._22;
			g_Explosion[nCntExplosion].mtxWorld._23 = mtxView._32;
			g_Explosion[nCntExplosion].mtxWorld._31 = mtxView._13;
			g_Explosion[nCntExplosion].mtxWorld._32 = mtxView._23;
			g_Explosion[nCntExplosion].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Explosion[nCntExplosion].pos.x, g_Explosion[nCntExplosion].pos.y, g_Explosion[nCntExplosion].pos.z);
			D3DXMatrixMultiply(&g_Explosion[nCntExplosion].mtxWorld, &g_Explosion[nCntExplosion].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Explosion[nCntExplosion].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0,
				sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);

			// �ǂ̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntExplosion * 4,
				2);
		}
	}
	//���e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//z�e�X�g
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTUER, &g_pTextureExplosion);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	// ���_���̐ݒ�
	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, -10.0f, 0.0f);

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
	g_pVtxBuffExplosion->Unlock();

}
//=============================================================================
// �ǂ̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos)
{
	int nCnt;
					
	for (nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == false)
		{
			g_Explosion[nCnt].pos = pos;

			g_Explosion[nCnt].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
			g_Explosion[nCnt].bUse = true;
			break;
		}
	}
}