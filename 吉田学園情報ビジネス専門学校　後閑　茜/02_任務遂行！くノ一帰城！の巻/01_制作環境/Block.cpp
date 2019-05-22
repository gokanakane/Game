//=============================================================================
//
// �������� [Block.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "input.h"
#include "main.h"
#include "Player.h"
#include "block.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEX	(5)
#define BLOCK_MOVE (3.0f) //�u���b�N�̈ړ���
#define PLAYER_POS_X (25.0f)	//�v���C���[��Pos.x
#define PLAYER_POS_Y (90.0f)	//�v���C���[��Pos.y

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_TEX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Block g_aBlock[MAX_BLOCK];				//�u���b�N�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBlock(void)
{	
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �u���b�N�̏��̏�����
	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].bLand = false;
		g_aBlock[nCntBlock].nType = 0;
		g_aBlock[nCntBlock].ChengeMove = 0;
		g_aBlock[nCntBlock].Cntmove = 0;

	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTUER, &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTUER1, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTUER2, &g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTUER3, &g_pTextureBlock[3]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTUER4, &g_pTextureBlock[4]);


	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
								D3DUSAGE_WRITEONLY, 
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffBlock,
								NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
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

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBlock->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitBlock(void)
{
	int nCnt;
	
	for (nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBlock[nCnt] != NULL)
		{
			g_pTextureBlock[nCnt]->Release();
			g_pTextureBlock[nCnt] = NULL;
		}

	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBlock(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (g_aBlock[nCnt].bUse == true)
		{
			if (g_aBlock[nCnt].nType == 1)
			{
				if (g_aBlock[nCnt].Cntmove > 80 || g_aBlock[nCnt].Cntmove < -80)
				{
					g_aBlock[nCnt].ChengeMove *= -1;//�܂�Ԃ�
				}
				g_aBlock[nCnt].Cntmove += g_aBlock[nCnt].ChengeMove;
				g_aBlock[nCnt].pos.x += g_aBlock[nCnt].ChengeMove;

			}

			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x, g_aBlock[nCnt].pos.y, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x + g_aBlock[nCnt].fWidth, g_aBlock[nCnt].pos.y, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x, g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x + g_aBlock[nCnt].fWidth, g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight, 0.0f);//����̒��_X�̏ꏊ�w��
		}
		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBlock->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)//�u���b�N���g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBlock,
				2);
		}
	}
}

//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType, int ChengeMove)
{
	int nCntBlock;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
 	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			//���_����ݒ�
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].pos = pos;

			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);//����̒��_X�̏ꏊ�w��

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(5.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(5.0f, 1.0f);

			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bLand = false;
			g_aBlock[nCntBlock].bUse = true;
			g_aBlock[nCntBlock].Cntmove = 0;
			g_aBlock[nCntBlock].ChengeMove = ChengeMove;
			break;
		}
		pVtx += 4;//�Y���̈ʒu�܂Ői�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBlock->Unlock();
}
//=============================================================================
// �u���b�N�̂����蔻��[CollisionBlock]
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)//���݂̈ʒu�A�O��̈ʒu�A�ړ���
{
	bool bLand = false; //���n���Ă��邩
	int nCnt;

	for (nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (g_aBlock[nCnt].bUse == true)
		{//�u���b�N�̎g�p��
			g_aBlock[nCnt].bLand = false;
			if (pPosold->x + PLAYER_POS_X > g_aBlock[nCnt].pos.x
				&& pPos->x - PLAYER_POS_X < g_aBlock[nCnt].pos.x + g_aBlock[nCnt].fWidth)
			{//�u���b�N�͈̔�(����)
			 //�㔻��
				if (pPosold->y <= g_aBlock[nCnt].pos.y
					&&pPos->y >= g_aBlock[nCnt].pos.y)
				{//�O��̈ʒu���u���b�N������,���݈ʒu���u���b�N�������i�߂荞�񂾁j
					g_aBlock[nCnt].bLand = true;
					bLand = true;
					pPos->y = g_aBlock[nCnt].pos.y;
					pMove->y = 0.0f;
				}

				//�ړ��u���b�N�̏㔻��
				if (g_aBlock[nCnt].bLand == true)
				{//����Ă���
					if (g_aBlock[nCnt].nType == 1)
					{//���ړ�
						g_aBlock[nCnt].bLand = true;
						bLand = true;
						pPos->x = pPos->x + g_aBlock[nCnt].ChengeMove;
						pMove->y = 0.0f;
					}

					if (g_aBlock[nCnt].nType == 3)
					{//���鏰
						g_aBlock[nCnt].bLand = true;
						bLand = true;
						pPos->x = pPos->x + g_aBlock[nCnt].ChengeMove;
						pMove->y = 0.0f;
						pMove->x += g_aBlock[nCnt].ChengeMove;
					}
				}

				//������
				if (pPosold->y > g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight + 100
					&& pPos->y < g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight + 100)
				{//�O��̈ʒu���u���b�N������,���݈ʒu���u���b�N������i�߂荞�񂾁j
					g_aBlock[nCnt].bLand = true;
					bLand = true;
					pPos->y = g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight + 100;
					pMove->y = 0.0f;
				}

				//������
				if (g_aBlock[nCnt].bLand == false)
				{//�w�肷��u���b�N�̏�ɍڂ��Ă��Ȃ�
					if (pPosold->y > g_aBlock[nCnt].pos.y
						&& pPos->y < g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight)
					{//�ǔ���
						g_aBlock[nCnt].bLand = true;
						bLand = true;
						pPos->x = pPosold->x;
						pMove->x = 0.0f;
					}

					if (g_aBlock[nCnt].nType == 1)
					{//���ړ��u���b�N
						if (pPosold->y > g_aBlock[nCnt].pos.y
							&& pPos->y - PLAYER_POS_Y < g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight)
						{//�ǔ���
							g_aBlock[nCnt].bLand = true;
							bLand = true;
							pPos->x = pPosold->x + g_aBlock[nCnt].ChengeMove;
							pMove->x = 0.0f;
						}
					}
					if (g_aBlock[nCnt].nType == 3)
					{//���ړ��u���b�N
						if (pPosold->y > g_aBlock[nCnt].pos.y
							&& pPos->y - PLAYER_POS_Y < g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight)
						{//�ǔ���
							g_aBlock[nCnt].bLand = true;
							bLand = true;
							pPos->x = pPosold->x;
							pMove->x = 0.0f;
						}
					}

				}
			}
		}
	}
	return bLand;
}
//=============================================================================
// �u���b�N�̎擾[GetBlock]
//=============================================================================
Block*GetBlock(void)
{
	return &g_aBlock[0];
}