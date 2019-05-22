//=============================================================================
//
// �e���� [Bow.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "Game.h"
#include "bow.h"
#include "main.h"
#include "Player.h"
#include "score.h"
#include "sound.h"
#include "fade.h"
#include "migawari.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BOW		(120)		// �e�̍ő吔
#define BOW_TEXTUER "data\\TEXTURE\\bow.png"
#define BOW_TEXTUER1 "data\\TEXTURE\\bow001.png"

#define POS_Y (620)
#define BOW_MOVE (1.0f)
#define BOW_PATTERN		(5)
#define MAX_BOW_TYPE (2)
#define MAX_TEX (2)
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBow[MAX_TEX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBow = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Bow g_aBow[MAX_BOW];	//�e�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBow(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBow;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for (nCntBow = 0; nCntBow < MAX_BOW; nCntBow++)
	{
		g_aBow[nCntBow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBow[nCntBow].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBow[nCntBow].type = 0;
		g_aBow[nCntBow].nLife = 0;
		g_aBow[nCntBow].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BOW_TEXTUER, &g_pTextureBow[0]);
	D3DXCreateTextureFromFile(pDevice, BOW_TEXTUER1, &g_pTextureBow[1]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBow,
		NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBow = 0; nCntBow < MAX_BOW; nCntBow++)
	{
		//���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�F�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���炷
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBow->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitBow(void)
{
	int nCnt;
		// �e�N�X�`���̊J��
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBow[nCnt] != NULL)
		{
			g_pTextureBow[nCnt]->Release();
			g_pTextureBow[nCnt] = NULL;
		}

	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBow != NULL)
	{
		g_pVtxBuffBow->Release();
		g_pVtxBuffBow = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBow(void)
{
	Player*pPlayer;
	Migawari*pMigawari;

	int nCntBow;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//�擾
	pPlayer = GetPlayer();
	pMigawari = GetMigawari();

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBow = 0; nCntBow < MAX_BOW; nCntBow++)
	{	//�e���g�p����Ă���
		if (g_aBow[nCntBow].bUse == true)//�e���g�p����Ă���ꍇ
		{//���_�����X�V
				//PL�ƒe����������
				if (pPlayer->bDisp == true)
				{
					if (pPlayer->state != PLAYERSTATE_APPEAR)
					{
						if (g_aBow[nCntBow].pos.x > pPlayer->pos.x - 50
							&& g_aBow[nCntBow].pos.x < pPlayer->pos.x + 50
							&& g_aBow[nCntBow].pos.y > pPlayer->pos.y - 100
							&& g_aBow[nCntBow].pos.y < pPlayer->pos.y)
						{
							HitPlayer(1);
							PlaySound(SOUND_LABEL_SE_HIT000);
							g_aBow[nCntBow].bUse = false;//�g�p���ĂȂ���Ԃɂ���
						}

					//�g����ƒe�̓����蔻��
					if (pMigawari->bUse == true)
					{
						if (g_aBow[nCntBow].pos.x > pMigawari->pos.x - 50
							&& g_aBow[nCntBow].pos.x < pMigawari->pos.x + 50
							&& g_aBow[nCntBow].pos.y > pMigawari->pos.y - 100
							&& g_aBow[nCntBow].pos.y < pMigawari->pos.y)
						{
							HitMigawari(1);
							PlaySound(SOUND_LABEL_SE_HIT000);
							g_aBow[nCntBow].bUse = false;//�g�p���ĂȂ���Ԃɂ���
						}

					}

				}

				g_aBow[nCntBow].nLife--;
				if (g_aBow[nCntBow].nLife == 0)
				{
					g_aBow[nCntBow].move.y += 5.5;
					g_aBow[nCntBow].move.x = 0;
					if (g_aBow[nCntBow].pos.x > SCREEN_WIDTH)
					{
						g_aBow[nCntBow].bUse = false;
					}
				}

				g_aBow[nCntBow].pos += g_aBow[nCntBow].move;
			}
			pVtx[0].pos = D3DXVECTOR3(g_aBow[nCntBow].pos.x - 20, g_aBow[nCntBow].pos.y - 20, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBow[nCntBow].pos.x + 20, g_aBow[nCntBow].pos.y - 20, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBow[nCntBow].pos.x - 20, g_aBow[nCntBow].pos.y + 20, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBow[nCntBow].pos.x + 20, g_aBow[nCntBow].pos.y + 20, 0.0f);

			pVtx += 4;//�Y���̈ʒu�܂Ői�߂�
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBow->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBow;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBow, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	// �|���S���̕`��
	for (nCntBow = 0; nCntBow < MAX_BOW; nCntBow++)
	{
		if (g_aBow[nCntBow].bUse == true)//�e���g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBow[g_aBow[nCntBow].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBow,
				2);
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBow(D3DXVECTOR3 pos, D3DXVECTOR3 move,int type)
{
	int nCntBow;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBow->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBow = 0; nCntBow < MAX_BOW; nCntBow++)
	{
		if (g_aBow[nCntBow].bUse == false)
		{
			PlaySound(SOUND_LABEL_SE_SHOT);

			g_aBow[nCntBow].pos = pos;
			//���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos.x - 20, pos.y - 20, 0.0f);//��ڂ̒��_�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(pos.x + 20, pos.y - 20, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[2].pos = D3DXVECTOR3(pos.x - 20, pos.y + 20, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[3].pos = D3DXVECTOR3(pos.x + 20, pos.y + 20, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

			g_aBow[nCntBow].move = move;
			g_aBow[nCntBow].type = type;
			g_aBow[nCntBow].nLife = 190;
			g_aBow[nCntBow].bUse = true;
			break;
		}
		pVtx += 4;//�Y���̈ʒu�܂Ői�߂�

	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBow->Unlock();
}
//=============================================================================
// �e�̎擾
//=============================================================================
Bow*GetBow(void)
{
	return &g_aBow[0];
}
