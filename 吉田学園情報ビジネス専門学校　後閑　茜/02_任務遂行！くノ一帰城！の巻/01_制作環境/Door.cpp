//=============================================================================
//
// �h�A���� [DOOR.cpp]
// Author :Gokan Akane
//
//=============================================================================
#include "Game.h"
#include "fade.h"
#include "input.h"
#include "Player.h"
#include "Door.h"
#include "Explosion.h"

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureDoor = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDoor = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Door g_aDoor;				//�u���b�N�̏��
int nTime;
//=============================================================================
// ����������
//=============================================================================
void InitDoor(void)
{	
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �u���b�N�̏��̏�����
		g_aDoor.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDoor.state = DOORSTATE_CLOSE;
		g_aDoor.bUse = false;
		nTime = 0;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, DOOR_TEXTUER, &g_pTextureDoor);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY, 
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffDoor,
								NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.9f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 0.9f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffDoor->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitDoor(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureDoor != NULL)
	{
		g_pTextureDoor->Release();
		g_pTextureDoor = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffDoor != NULL)
	{
		g_pVtxBuffDoor->Release();
		g_pVtxBuffDoor = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateDoor(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	switch (g_aDoor.state)
	{
	case DOORSTATE_CLOSE:
		break;

	case DOORSTATE_OPENSTART:
		nTime++;

		//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f, 0.9f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.9f);

		//���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffDoor->Unlock();

		if (nTime > 15)
		{
			g_aDoor.state = DOORSTATE_OPEN;

		}
		break;

	case DOORSTATE_OPEN:
		//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.75f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f, 0.9f);
		pVtx[3].tex = D3DXVECTOR2(0.75f, 0.9f);

		
		//���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffDoor->Unlock();
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffDoor, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	if (g_aDoor.bUse == true)//�u���b�N���g�p����Ă���
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureDoor);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
	}
}

//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void SetDoor(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aDoor.bUse == false)
	{
		//���_����ݒ�
		g_aDoor.pos = pos;

		pVtx[0].pos = D3DXVECTOR3(g_aDoor.pos.x - DOOR_WIDTH, g_aDoor.pos.y - DOOR_HEIGTH, 0.0f);//����̒��_X�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(g_aDoor.pos.x + DOOR_WIDTH, g_aDoor.pos.y - DOOR_HEIGTH, 0.0f);//����̒��_X�̏ꏊ�w��
		pVtx[2].pos = D3DXVECTOR3(g_aDoor.pos.x - DOOR_WIDTH, g_aDoor.pos.y , 0.0f);//����̒��_X�̏ꏊ�w��
		pVtx[3].pos = D3DXVECTOR3(g_aDoor.pos.x + DOOR_WIDTH, g_aDoor.pos.y , 0.0f);//����̒��_X�̏ꏊ�w��

		g_aDoor.bUse = true;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffDoor->Unlock();
}
//=============================================================================
//�h�A�̂����蔻��[CollisionDoor]
//=============================================================================
bool CollisionDoor(D3DXVECTOR3 *pPos)//���݂̈ʒu
{
	FADE g_Fade;
	g_Fade = GetFade();
	Player*pPlayer;
	bool bLand = false;

	pPlayer = GetPlayer();
	if (g_aDoor.bUse == true)
	{
		bLand = false;
		if (g_aDoor.state == DOORSTATE_OPEN)
		{
			if (g_aDoor.pos.x > pPos->x - 50
				&& g_aDoor.pos.x < pPos->x + 90
				&& g_aDoor.pos.y > pPos->y - 90
				&& g_aDoor.pos.y-10 < pPos->y)
			{
				if (GetKeyboardPress(DIK_RETURN) == true)
				{
					if (g_Fade != FADE_OUT)
					{
						bLand = true;
						pPlayer->state = PLAYERSTATE_APPEAR;
						SetGameState(GAMESTATE_CLEAR);
					}

				}
			}
		}

	}
	return bLand;
}
//=============================================================================
// �u���b�N�̎擾[GetDoor]
//=============================================================================
Door*GetDoor(void)
{
	return &g_aDoor;
}