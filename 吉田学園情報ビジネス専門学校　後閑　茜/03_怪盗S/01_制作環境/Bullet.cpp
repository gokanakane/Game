//=============================================================================
//
// �e���� [Bullet.cpp]
// Author : ��Ո�
//
//=============================================================================
#include "Bullet.h"
#include "shadow.h"
#include "input.h"
#include "Stage.h"
#include "explosion.h"
#include "Obj.h"
#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_TEXTUER "data\\TEXTURE\\bullet000.png"
#define BULLET_SPEED (3.0f)
#define MAX_VEC (4)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;//�e�N�X�`���ւ̃|�C���^
Bullet g_Bullet[MAX_BULLET];					//�e�̍ő吔

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		g_Bullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].VecA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].VecC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].bUse = false;
	}

	MakeVertexBullet(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	D3DXVECTOR3 aPos[4];//�x�N�g���v�Z
	float VecLine;		//�����蔻��̌v�Z����

	aPos[0] = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	aPos[1] = D3DXVECTOR3(350.0f, 0.0f, 50.0f);
	aPos[2] = D3DXVECTOR3(350.0f, 0.0f, -350.0f);
	aPos[3] = D3DXVECTOR3(-50.0f, 0.0f, -350.0f);


	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		g_Bullet[nCnt].posOld = g_Bullet[nCnt].pos;
		
		if (g_Bullet[nCnt].bUse == true)
		{
				g_Bullet[nCnt].pos.x -= sinf(g_Bullet[nCnt].rot.y)*BULLET_SPEED;
				g_Bullet[nCnt].pos.z -= cosf(g_Bullet[nCnt].rot.y)*BULLET_SPEED;

				SetPositionShadow(g_Bullet[nCnt].nIdxShadow, g_Bullet[nCnt].pos);

			for (int nCntVec = 0; nCntVec < MAX_VEC; nCntVec++)
			{
				//�x�N�g���v�Z
				g_Bullet[nCnt].VecA = aPos[nCntVec] - aPos[nCntVec + 1];
				g_Bullet[nCnt].VecC = g_Bullet[nCnt].pos - aPos[nCntVec];

				if (nCntVec == MAX_VEC - 1)
				{//�x�N�g���v�Z
					g_Bullet[nCnt].VecA = aPos[nCntVec] - aPos[0];
				}

				//�����蔻��v�Z
				VecLine = (g_Bullet[nCnt].VecA.z*g_Bullet[nCnt].VecC.x) - (g_Bullet[nCnt].VecA.x*g_Bullet[nCnt].VecC.z);

				if (VecLine >= 0)
				{//���������獶��
					g_Bullet[nCnt].bUse = false;
					DeleteShadow(g_Bullet[nCnt].nIdxShadow);
					SetExplosion(g_Bullet[nCnt].pos);
					break;
				}
				if (VecLine <= 0)
				{//����������E��
					g_Bullet[nCnt].bUse = false;
					DeleteShadow(g_Bullet[nCnt].nIdxShadow);
					SetExplosion(g_Bullet[nCnt].pos);

					break;
				}
			}



			////���f���ƒe�̂����蔻��
			//if (CollisionObj1(&g_Bullet[nCnt].pos) == true)
			//{
			//	g_Bullet[nCnt].bUse = false;
			//	DeleteShadow(g_Bullet[nCnt].nIdxShadow);
			//	SetExplosion(g_Bullet[nCnt].pos);

			//}

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;				//�v�Z�p�}�g���b�N�X
	int nCntBullet;


	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Bullet[nCntBullet].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_Bullet[nCntBullet].mtxWorld._11 = mtxView._11;
			g_Bullet[nCntBullet].mtxWorld._12 = mtxView._21;
			g_Bullet[nCntBullet].mtxWorld._13 = mtxView._31;
			g_Bullet[nCntBullet].mtxWorld._21 = mtxView._12;
			g_Bullet[nCntBullet].mtxWorld._22 = mtxView._22;
			g_Bullet[nCntBullet].mtxWorld._23 = mtxView._32;
			g_Bullet[nCntBullet].mtxWorld._31 = mtxView._13;
			g_Bullet[nCntBullet].mtxWorld._32 = mtxView._23;
			g_Bullet[nCntBullet].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCntBullet].pos.x, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_Bullet[nCntBullet].mtxWorld, &g_Bullet[nCntBullet].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCntBullet].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0,
				sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			// �e�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBullet * 4,
				2);
		}
	}
	//���e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTUER, &g_pTextureBullet);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	// ���_���̐ݒ�
	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(-3.0f, 3.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(3.0f, 3.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-3.0f, -3.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(3.0f, -3.0f, 0.0f);

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

		pVtx += 4 ;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();

}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	int nCnt;
					
	for (nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_Bullet[nCnt].bUse == false)
		{
			g_Bullet[nCnt].pos = pos;
			g_Bullet[nCnt].rot = rot;
			g_Bullet[nCnt].bUse = true;

			g_Bullet[nCnt].nIdxShadow = SetShadow(g_Bullet[g_Bullet[nCnt].nIdxShadow].pos,g_Bullet[g_Bullet[nCnt].nIdxShadow].rot);

			break;
		}
	}
}
//=============================================================================
// �e�̎擾
//=============================================================================
Bullet*GetBullet(void)
{
	return &g_Bullet[0];
}