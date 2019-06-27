//=============================================================================
//
// �A�C�e������ [Item.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "Game.h"
#include "Player.h"
#include "Item.h"
#include "score.h"
#include "time.h"
#include "sound.h"
#include "Door.h"
#include "Explosion.h"

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItem[MAX_ITEMTEX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
ITEM g_aItem[MAX_ITEM];				//�A�C�e���̏��
int g_NumItem;

//=============================================================================
// ����������
//=============================================================================
void InitItem(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �A�C�e���̏��̏�����
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aItem[nCntItem].nCntAnim = 0;
		g_aItem[nCntItem].nPatternAnim = 0;
		g_aItem[nCntItem].nType = 0;
		g_aItem[nCntItem].bUse = false;
		g_NumItem = 0;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTUER, &g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTUER1, &g_pTextureItem[1]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTUER2, &g_pTextureItem[2]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTUER3, &g_pTextureItem[3]);


	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
								D3DUSAGE_WRITEONLY, 
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffItem,
								NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//�O�ڂ̒��_�̐F�w��i�E���j

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���炷
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffItem->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	int nCnt;
	// �e�N�X�`���̊J��
	//�e�N�X�`���̔j��
	for (nCnt = 0; nCnt < MAX_ITEMTEX; nCnt++)
	{
		if (g_pTextureItem[nCnt] != NULL)
		{
			g_pTextureItem[nCnt]->Release();
			g_pTextureItem[nCnt] = NULL;
		}

	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	Player*pPlayer;
	pPlayer = GetPlayer();
	
	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)//�A�C�e�����g�p����Ă���ꍇ
		{
			if (g_aItem[nCntItem].nType == 2)
			{
				//�J�E���^�[���Z
				g_aItem[nCntItem].nCntAnim++;

				if ((g_aItem[nCntItem].nCntAnim % 8) == 0)//��莞�Ԃ��o��
				{
					//�p�^�[�����X�V
					g_aItem[nCntItem].nPatternAnim++;
				}

				//�e�N�X�`���摜�̍X�V
				pVtx[0].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim % COIN_PATTERN) * 0.25f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim % COIN_PATTERN) * 0.25f + 0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim % COIN_PATTERN) * 0.25f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim % COIN_PATTERN) * 0.25f + 0.25f, 1.0f);
			}
			else if (g_aItem[nCntItem].nType == 1 || g_aItem[nCntItem].nType == 3)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			}
			//�ʒu�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 25, g_aItem[nCntItem].pos.y - 30, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 25, g_aItem[nCntItem].pos.y - 30, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 25, g_aItem[nCntItem].pos.y + 30, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 25, g_aItem[nCntItem].pos.y + 30, 0.0f);

		}
		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)//�A�C�e�����g�p����Ă���
		{	
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntItem,
				2);
		}
	}
}

//=============================================================================
// �A�C�e���̐ݒ菈��
//=============================================================================
void SetItem(D3DXVECTOR3 pos,int Type)
{
	int nCntItem;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^


	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
 	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			//���_����ݒ�
			g_aItem[nCntItem].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 25,g_aItem[nCntItem].pos.y + 30, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(25 + g_aItem[nCntItem].pos.x, 30 + g_aItem[nCntItem].pos.y, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[2].pos = D3DXVECTOR3(25 + g_aItem[nCntItem].pos.x, 30 + g_aItem[nCntItem].pos.y, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[3].pos = D3DXVECTOR3(25 + g_aItem[nCntItem].pos.x, 30 + g_aItem[nCntItem].pos.y, 0.0f);//����̒��_X�̏ꏊ�w��

			g_aItem[nCntItem].nCntAnim = 0;
			g_aItem[nCntItem].nPatternAnim = 0;

			//�e�N�X�`���摜�̍X�V
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_aItem[nCntItem].nType = Type;
			g_aItem[nCntItem].bUse = true;
			g_NumItem++ ;
			break;
		}
		pVtx += 4;//�Y���̈ʒu�܂Ői�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �A�C�e���̂����蔻��[CollsionItem]
//=============================================================================
bool CollsionItem(D3DXVECTOR3 *pPos)
{
	ITEM*pItem;
	int nCntItem;
	Door*pDoor;
	bool bLand = false;

	pItem = GetItem();
	pDoor = GetDoor();
	
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			bLand = false;

			if (pItem->pos.x > pPos->x - 50
				&& pItem->pos.x < pPos->x + 50 + 10
				&& pItem->pos.y > pPos->y - 50 - 50
				&& pItem->pos.y < pPos->y + 90)
			{
				PlaySound(SOUND_LABEL_SE_HIT000);
				if (g_aItem[nCntItem].nType == 0)
				{
					SetExplosion(D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, 0.0f),
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	
					AddScore(100);
					DeleteItem(nCntItem);
					bLand = true;

				}
				else if (g_aItem[nCntItem].nType == 1)
				{
					SetExplosion(D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, 0.0f),
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					AddScore(300);
					DeleteItem(nCntItem);
					bLand = true;
				}
				else if (g_aItem[nCntItem].nType == 2)
				{
					SetExplosion(D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, 0.0f),
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					AddScore(500);
					DeleteItem(nCntItem);
					bLand = true;
				}
				else if (g_aItem[nCntItem].nType == 3)
				{
					SetExplosion(g_aItem[nCntItem].pos, g_aItem[nCntItem].col);
					SetExplosion(pDoor->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					AddScore(800);
					DeleteItem(nCntItem);
					pDoor->state = DOORSTATE_OPENSTART;
					bLand = true;
					PlaySound(SOUND_LABEL_SE_DOOR);

				}
			}
		}
	}
	return bLand;
}

//=============================================================================
// �A�C�e���̏���[DeleteItem]
//=============================================================================
void DeleteItem(int nCnt)
{
	g_aItem[nCnt].bUse = false;
	g_NumItem--;
}
//=============================================================================
// �A�C�e���̎擾[GetItem]
//=============================================================================
ITEM*GetItem(void)
{
	return &g_aItem[0];
}
