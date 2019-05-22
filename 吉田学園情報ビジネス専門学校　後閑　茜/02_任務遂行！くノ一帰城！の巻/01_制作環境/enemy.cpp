//=============================================================================
//
// �G���� [enemy.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "enemy.h"
#include "Game.h"
#include "bow.h"
#include "fade.h"
#include "sound.h"
#include "Player.h"
#include "migawari.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(4)									// �G�̎��
#define ENEMY_TEXTURE		"data\\TEXTURE\\enemy000.png"		//�G�̃e�N�X�`���̖��O
#define ENEMY_TEXTURE1		"data\\TEXTURE\\enemy001.png"		//�G�̃e�N�X�`���̖��O0

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEnemy[MAX_TYPE_ENEMY] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];										//�G�̏��
int g_nNumEnemy;												//�G�̑���
int g_nPatternAnimE;
int g_nCntAnimE;

//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;// ���_���̍쐬
	int nCntEnemy;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		g_aEnemy[nCntEnemy].nCntState = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_nNumEnemy = 0;
	}

	g_nCntAnimE = 0;
	g_nPatternAnimE = 0;

	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE, &g_pTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE1, &g_pTextureEnemy[1]);

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���炷
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureEnemy[nCntTex] != NULL)
		{
			g_pTextureEnemy[nCntTex]->Release();
			g_pTextureEnemy[nCntTex] = NULL;
		}
	}

		// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;// ���_���̍쐬
	float pos_x;	//X�̒���
	float pos_y;	//Y�̒���
	float fAngle;	//�p�x
	float move_x;	//X�̈ړ���
	float move_y;	//Y�̈ړ���
	Player*pPlayer;
	Migawari*pMigawari;

	pPlayer = GetPlayer();
	pMigawari = GetMigawari();

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NOMAL:
				/*[�ʏ�̏���]*/
				if (rand() % 350 == 0)
				{
					if (pMigawari->bUse == false)
					{
						//�^���W�F���g��XY���l�����߂�
						pos_x = pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x;
						pos_y = pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y;

						//�p�x���v�Z
						fAngle = atan2f(pos_x, pos_y);

						//�ړ��ʂ����߂�
						move_x = sinf(fAngle)*3.0f;
						move_y = cosf(fAngle)*3.0f;

						if (g_aEnemy[nCntEnemy].nType == 0)
						{
							SetBow(g_aEnemy[nCntEnemy].pos,
								D3DXVECTOR3(move_x, move_y, 0.0f),
								0);
						}
						else if (g_aEnemy[nCntEnemy].nType == 1)
						{
							SetBow(g_aEnemy[nCntEnemy].pos,
								D3DXVECTOR3(move_x, move_y, 0.0f),
								1);
						}

					}
					else
					{
						//�^���W�F���g��XY���l�����߂�
						pos_x = pMigawari->pos.x - g_aEnemy[nCntEnemy].pos.x;
						pos_y = pMigawari->pos.y - g_aEnemy[nCntEnemy].pos.y;

						//�p�x���v�Z
						fAngle = atan2f(pos_x, pos_y);

						//�ړ��ʂ����߂�
						move_x = sinf(fAngle)*3.0f;
						move_y = cosf(fAngle)*3.0f;

						if (g_aEnemy[nCntEnemy].nType == 0)
						{
							SetBow(g_aEnemy[nCntEnemy].pos,
								D3DXVECTOR3(move_x, move_y, 0.0f),
								0);
						}
						else if (g_aEnemy[nCntEnemy].nType == 1)
						{
							SetBow(g_aEnemy[nCntEnemy].pos,
								D3DXVECTOR3(move_x, move_y, 0.0f),
								1);
						}
					}
				}
				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCntState--;
				if (g_aEnemy[nCntEnemy].nCntState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;

					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
				}
				break;
			}
			//���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 30, g_aEnemy[nCntEnemy].pos.y - 90, 0.0f);//��ڂ̒��_�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 30, g_aEnemy[nCntEnemy].pos.y - 90, 0.0f);;//��ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 30, g_aEnemy[nCntEnemy].pos.y , 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 30, g_aEnemy[nCntEnemy].pos.y , 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		}
		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//�G���g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEnemy * 4,
				2);
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos,int nType)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//���_����ݒ�
			g_aEnemy[nCntEnemy].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y - 80, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y - 80, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y , 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y , 0.0f);//����̒��_X�̏ꏊ�w��

			g_aEnemy[nCntEnemy].bUse = true;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = 2;
			g_aEnemy[nCntEnemy].nCntState = 0;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
			g_nNumEnemy++;

			break;
		}
		pVtx += 4;//�Y���̈ʒu�܂Ői�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}
//=============================================================================
// �G�̃_���[�W����
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		g_aEnemy[nCntEnemy].bUse = false;
		g_nNumEnemy--;
		if (g_nNumEnemy <= 0)
		{//�S�ł���
			SetGameState(GAMESTATE_CLEAR);			
		}
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCntState = 5;//�_���[�W��Ԃ̎���

		VERTEX_2D *pVtx;// ���_���̍쐬
		//���_�o�b�t�@�����b�N
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntEnemy * 4);

		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		
		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();

	}

}

//=============================================================================
// �G�̎擾
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}
