//=============================================================================
//
// �������� [Explosion.cpp]
// Author :Gokan Akane
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "main.h"
#include "Player.h"
#include "Explosion.h"

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];				//�e�̏��

//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{	
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCntAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTUER, &g_pTextureExplosion);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
								D3DUSAGE_WRITEONLY, 
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffExplosion,
								NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
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
	g_pVtxBuffExplosion->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	// �e�N�X�`���̊J��
	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)//�e���g�p����Ă���ꍇ
		{//�J�E���^�[���Z
			g_aExplosion[nCntExplosion].nCntAnim++;

			if ((g_aExplosion[nCntExplosion].nCntAnim % 3) == 0)//��莞�Ԃ��o��
			{
				//�p�^�[�����X�V
				g_aExplosion[nCntExplosion].nPatternAnim++;
			}

			//���_�����X�V
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 60, g_aExplosion[nCntExplosion].pos.y - 60, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 80,g_aExplosion[nCntExplosion].pos.y - 60, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 60,g_aExplosion[nCntExplosion].pos.y + 80, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 80,g_aExplosion[nCntExplosion].pos.y + 80, 0.0f);//����̒��_X�̏ꏊ�w��

			//�e�N�X�`���摜�̍X�V
			pVtx[0].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.0f,0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f,0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.0f,1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, 1.0f);
			
			if (g_aExplosion[nCntExplosion].nPatternAnim > 8)
			{
				g_aExplosion[nCntExplosion].bUse = false;
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
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	// �|���S���̕`��
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)//�e���g�p����Ă���
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntExplosion,
				2);
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
 	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			//���_����ݒ�
			g_aExplosion[nCntExplosion].pos = pos;
			pVtx[nCntExplosion].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 25,g_aExplosion[nCntExplosion].pos.y + 25, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[nCntExplosion].pos = D3DXVECTOR3(40 + g_aExplosion[nCntExplosion].pos.x, 25 + g_aExplosion[nCntExplosion].pos.y, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[nCntExplosion].pos = D3DXVECTOR3(25 + g_aExplosion[nCntExplosion].pos.x, 40 + g_aExplosion[nCntExplosion].pos.y, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[nCntExplosion].pos = D3DXVECTOR3(40 + g_aExplosion[nCntExplosion].pos.x, 40 + g_aExplosion[nCntExplosion].pos.y, 0.0f);//����̒��_X�̏ꏊ�w��

			//���_���i�F�j�̐ݒ�
			g_aExplosion[nCntExplosion].col = col;
			pVtx[nCntExplosion].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//��ڂ̒��_�̐F�w��i�E���j
			pVtx[nCntExplosion].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//��ڂ̒��_�̐F�w��i�E���j
			pVtx[nCntExplosion].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//�O�ڂ̒��_�̐F�w��i�E���j
			pVtx[nCntExplosion].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);//�O�ڂ̒��_�̐F�w��i�E���j

			g_aExplosion[nCntExplosion].nCntAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;

			//�e�N�X�`���摜�̍X�V
			pVtx[nCntExplosion].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntExplosion].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[nCntExplosion].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[nCntExplosion].tex = D3DXVECTOR2(1.0f, 1.0f);


			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
		pVtx += 4;//�Y���̈ʒu�܂Ői�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

