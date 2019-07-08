//=============================================================================
//
// �e���� [bullet.cpp]
// Author :Gokan Akane
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "main.h"
#include "Player.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "sound.h"
#include "fade.h"


//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet[2] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];	//�e�̏��
int g_nPatternAnimB;
int g_nCntAnimB;

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{	
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].bUse = false;
	}


	g_nCntAnimB = 0;
	g_nPatternAnimB = 0;

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, BULLET_TEXTUER, &g_pTextureBullet[0]);
		D3DXCreateTextureFromFile(pDevice, BULLET_TEXTUER1, &g_pTextureBullet[1]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET, 
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffBullet, 
								NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
	g_pVtxBuffBullet->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	int nCnt;
		// �e�N�X�`���̊J��
	for (nCnt = 0; nCnt < MAX_BULLET_TYPE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBullet[nCnt] != NULL)
		{
			g_pTextureBullet[nCnt]->Release();
			g_pTextureBullet[nCnt] = NULL;
		}

	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	int nCntEnemy;
	Enemy*pEnemy;

	g_nCntAnimB++;

	if ((g_nCntAnimB % 10) == 0)//��莞�Ԃ��o��
	{
		g_nPatternAnimB = (g_nPatternAnimB + 1) % BULLET_PATTERN;		//�p�^�[�����X�V
	}

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
 	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{	//�e���g�p����Ă���
		if (g_aBullet[nCntBullet].bUse == true)//�e���g�p����Ă���ꍇ
		{//���_�����X�V
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x -20, g_aBullet[nCntBullet].pos.y - 20, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 20, g_aBullet[nCntBullet].pos.y - 20, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 20, g_aBullet[nCntBullet].pos.y + 20, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 20, g_aBullet[nCntBullet].pos.y + 20, 0.0f);

			pVtx[0].tex = D3DXVECTOR2((g_nPatternAnimB % 4) * 0.25f, (g_nPatternAnimB / 4)*0.5f);
			pVtx[1].tex = D3DXVECTOR2((g_nPatternAnimB % 4) * 0.25f + 0.2f, (g_nPatternAnimB / 4)*0.5f);
			pVtx[2].tex = D3DXVECTOR2((g_nPatternAnimB % 4) * 0.25f, (g_nPatternAnimB / 4)* 0.5f + 0.5f);
			pVtx[3].tex = D3DXVECTOR2((g_nPatternAnimB % 4) * 0.25f + 0.2f, (g_nPatternAnimB / 4)*0.5f + 0.5f);

			
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{//PL�̒e
				//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f),20.0f,30);
				//�G�̎擾
				pEnemy = GetEnemy();

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)//�G���g���Ă���
					{//�G�ƒe����������
						if (g_aBullet[nCntBullet].pos.x > pEnemy->pos.x - 50
							&& g_aBullet[nCntBullet].pos.x < pEnemy->pos.x + 50
							&& g_aBullet[nCntBullet].pos.y > pEnemy->pos.y - 50
							&& g_aBullet[nCntBullet].pos.y < pEnemy->pos.y + 50)
						{
							HitEnemy(nCntEnemy, 1);
							AddScore(4000);
							PlaySound(SOUND_LABEL_SE_HIT000);
							g_aBullet[nCntBullet].bUse = false;//�g�p���ĂȂ���Ԃɂ���
						}

					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_EMEMY)
			{//�G�̒e
				Player*pPlayer;

				//�v���C���[�̎擾
				pPlayer = GetPlayer();

				//PL�ƒe����������
				if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - 50
					&& g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + 50
					&& g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - 50
					&& g_aBullet[nCntBullet].pos.y < pPlayer->pos.y + 50)
				{
					HitPlayer(1);
					PlaySound(SOUND_LABEL_SE_HIT001);
					g_aBullet[nCntBullet].bUse = false;//�g�p���ĂȂ���Ԃɂ���
				}
			}

			//��莞�Ԍo��
			g_aBullet[nCntBullet].nLife--;
			
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f), 50.0f, 30);
				//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		
		pVtx += 4;//�Y���̈ʒu�܂Ői�߂�
	}
		//���_�o�b�t�@�̃A�����b�N
 		g_pVtxBuffBullet->Unlock();
		
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	// �|���S���̕`��
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].type == BULLETTYPE_EMEMY)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet[1]);

		}
		else
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet[0]);

		}


		if (g_aBullet[nCntBullet].bUse == true)//�e���g�p����Ă���
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBullet,
				2);
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,int Life)
{
	int nCntBullet;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			PlaySound(SOUND_LABEL_SE_SHOT);

			g_aBullet[nCntBullet].pos = pos;
			//���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos.x + 0,pos.y+ 0, 0.0f);//��ڂ̒��_�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(pos.x + 20,pos.y + 0, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[2].pos = D3DXVECTOR3(pos.x + 0, pos.y + 20, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[3].pos = D3DXVECTOR3(pos.x + 20, pos.y + 20, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].bUse = true;
			g_aBullet[nCntBullet].nLife = Life;
			g_aBullet[nCntBullet].type = type;
			break;
		}
		pVtx += 4;//�Y���̈ʒu�܂Ői�߂�

	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();
}

