//=============================================================================
//
// �g���菈�� [migawari.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "migawari.h"
#include "bow.h"
#include "Player.h"
#include "sound.h"
#include "Block.h"
#include "Explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MIGAWARI_TEXTUER "data\\TEXTURE\\Migawari000.png"
#define MIGAWARI_TEXTUER1 "data\\TEXTURE\\Migawari001.png"
#define POS_Y (620)
#define MIGAWARI_MOVE (1.0f)
#define MIGAWARI_PATTERN		(5)
#define MAX_MIGAWARI_TYPE (2)
#define MAX_TEX (2)
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureMigawari[MAX_TEX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMigawari = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Migawari g_aMigawari;	//�g����̏��

//=============================================================================
// ����������
//=============================================================================
void InitMigawari(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �g����̏��̏�����
		g_aMigawari.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMigawari.posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMigawari.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMigawari.state = MIGAWARISTATE_NOMAL;
		g_aMigawari.nCntState = 0;
		g_aMigawari.bUse = false;
		g_aMigawari.type = 0;
		g_aMigawari.nLife = MIGAWARI_MAX_LIFE;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MIGAWARI_TEXTUER, &g_pTextureMigawari[0]);
	D3DXCreateTextureFromFile(pDevice, MIGAWARI_TEXTUER1, &g_pTextureMigawari[1]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMigawari,
		NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMigawari->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMigawari->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitMigawari(void)
{

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureMigawari[nCnt] != NULL)
		{
			g_pTextureMigawari[nCnt]->Release();
			g_pTextureMigawari[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMigawari != NULL)
	{
		g_pVtxBuffMigawari->Release();
		g_pVtxBuffMigawari = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMigawari(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMigawari->Lock(0, 0, (void**)&pVtx, 0);
		switch (g_aMigawari.state)
		{
		case MIGAWARISTATE_NOMAL:
			break;

		case MIGAWARISTATE_DAMAGE:
			g_aMigawari.nCntState--;
			if (g_aMigawari.nCntState <= 0)
			{
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

				g_aMigawari.state = MIGAWARISTATE_NOMAL;

			}
			break;

		case MIGAWARISTATE_DEATH:
			g_aMigawari.bUse = false;
 			g_aMigawari.state = MIGAWARISTATE_NOMAL;
			break;

		}

		if (g_aMigawari.bUse == true)
		{
			g_aMigawari.posold = g_aMigawari.pos; //�O��̈ʒu��ۑ�

			g_aMigawari.move.y += 3.5;//�d�͉��Z

			//�ʒu�̍X�V
			g_aMigawari.pos.x += g_aMigawari.move.x;
			g_aMigawari.pos.y += g_aMigawari.move.y;

			CollisionBlock(&g_aMigawari.pos, &g_aMigawari.posold, &g_aMigawari.move);

			pVtx[0].pos = D3DXVECTOR3(g_aMigawari.pos.x - 40, g_aMigawari.pos.y - 90, 0.0f);//��ڂ̒��_�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(g_aMigawari.pos.x + 40, g_aMigawari.pos.y - 90, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[2].pos = D3DXVECTOR3(g_aMigawari.pos.x - 40, g_aMigawari.pos.y, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[3].pos = D3DXVECTOR3(g_aMigawari.pos.x + 40, g_aMigawari.pos.y, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMigawari->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMigawari(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffMigawari, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	// �|���S���̕`��
	// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMigawari[g_aMigawari.type]);

		if (g_aMigawari.bUse == true)//�g���肪�g�p����Ă���
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				2);
		}
}

//=============================================================================
// �g����̐ݒ菈��
//=============================================================================
void SetMigawari(D3DXVECTOR3 pos, int Type)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMigawari->Lock(0, 0, (void**)&pVtx, 0);

		if (g_aMigawari.bUse == false)
		{
			PlaySound(SOUND_LABEL_SE_MIGAWARI);

			g_aMigawari.pos = pos;
			//���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos.x - 40, pos.y - 90, 0.0f);//��ڂ̒��_�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(pos.x + 40,pos.y - 90, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[2].pos = D3DXVECTOR3(pos.x - 40, pos.y, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[3].pos = D3DXVECTOR3(pos.x + 40, pos.y, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

			g_aMigawari.state = MIGAWARISTATE_NOMAL;
			g_aMigawari.nCntState = 0;
			g_aMigawari.bUse = true;
			g_aMigawari.type = Type;
			g_aMigawari.nLife = MIGAWARI_MAX_LIFE;
		}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMigawari->Unlock();
}
//=============================================================================
// �g����̃_���[�W
//=============================================================================
void HitMigawari(int nDamage)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	g_aMigawari.nLife -= nDamage;

	if (g_aMigawari.nLife == 0)
	{
		SetExplosion(g_aMigawari.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_aMigawari.state = MIGAWARISTATE_DEATH;
	}

	else
	{
		g_aMigawari.state = MIGAWARISTATE_DAMAGE;
		g_aMigawari.nCntState = 5;

		//���_�o�b�t�@�����b�N
		g_pVtxBuffMigawari->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffMigawari->Unlock();

	}

}
//=============================================================================
// �g����̐ݒ菈��
//=============================================================================
Migawari*GetMigawari(void)
{
	return &g_aMigawari;
}