//=============================================================================
//
// �v���C���[���� [Player.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "Game.h"
#include "Player.h"
#include "input.h"
#include "Block.h"
#include "Item.h"
#include "Door.h"
#include "bow.h"
#include "migawari.h"
#include "Life.h"
#include "score.h"


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;
Player g_Player;
//=============================================================================
// �v���C���[����������[InitPlayer]
//=============================================================================
void InitPlayer(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3(500, 620, 0.0f);
	g_Player.posold = D3DXVECTOR3(0, 0, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nLife = MAXPLAYER_LIFE;
	g_Player.nPatternAnim = 0;
	g_Player.nCntAnim = 0;
	g_Player.nCntState = 0;
	g_Player.nDirectionMove = 0;
	g_Player.CntColor = 0;
	g_Player.ChengeColor = 0;
	g_Player.bJump = false;
	g_Player.bDisp = true;
	g_Player.bWalk = false;
	g_Player.state = PLAYERSTATE_NOMAL;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTUER, &g_pTexturePlayer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer, NULL);


	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);


	//�v���C���[�̑傫���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�v���C���[�̐F�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPlayer->Unlock();

}

//=============================================================================
//�v���C���[�I������ [UninitPolygon]
//=============================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================
// �v���C���[�X�V����[UpdataPolygon]
//=============================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	switch (g_Player.state)
	{
	case PLAYERSTATE_APPEAR:
		break;
	case PLAYERSTATE_NOMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		g_Player.nCntState--;
		if (g_Player.nCntState <= 0)
		{
			g_Player.state = PLAYERSTATE_NOMAL;
			//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

		//���_�o�b�t�@�̃A�����b�N
			g_pVtxBuffPlayer->Unlock();
		}
		break;

	case PLAYERSTEAT_DEATH:
		SetGameState(GAMESTATE_OVER);
		g_Player.state = PLAYERSTATE_NOMAL;
		break;
	}

	g_Player.nCntAnim++; //�A�j���[�V�����J�E���^�[�̉��Z
	g_Player.posold = g_Player.pos; //�O��̈ʒu��ۑ�

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Player.bDisp == true)
	{
		//���ɓ�����
		if (GetKeyboardPress(DIK_A) == true)
		{//D��������
			g_Player.bWalk = true;
			g_Player.nDirectionMove = 1;
			g_Player.move.x -= PLAYER_MOVE;

			if ((g_Player.nCntAnim % 8) == 0)
			{//��莞�Ԃ��o��
			 //�p�^�[�����X�V
				g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % PLAYER_PATTERN;

				pVtx[0].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.75f);
				pVtx[3].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.75f);

				if (g_Player.nPatternAnim %PLAYER_PATTERN == 0)
				{
					g_Player.nPatternAnim = 0;
				}
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//D��������
			g_Player.bWalk = true;
			g_Player.nDirectionMove = 0;
			g_Player.move.x += PLAYER_MOVE;

			if ((g_Player.nCntAnim % 8) == 0)
			{//��莞�Ԃ��o��
				//�p�^�[�����X�V
				g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % PLAYER_PATTERN;

				pVtx[0].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.75f);
				pVtx[1].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.75f);
				pVtx[2].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 1.0f);

				if (g_Player.nPatternAnim %PLAYER_PATTERN == 0)
				{
					g_Player.nPatternAnim = 0;
				}
			}
		}
		else
		{
			g_Player.bWalk = false;
		}

		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{//�W�����v
			if (g_Player.bJump == false)
			{//�󒆃W�����v�h�~
				g_Player.move.y = -45.0f;
				g_Player.move.x += 0.1f;
				g_Player.bJump = true;
			}
		}

		if (GetKeyboardTrigger(DIK_W) == true)
		{//�g����ݒu

			if (rand() % 100 == 0)
			{
				SetMigawari(g_Player.pos, 1);
			}
			else
			{
				SetMigawari(g_Player.pos, 0);
			}
		}

		g_Player.move.y += 3.5;//�d�͉��Z

		if (g_Player.pos.y > SCREEN_HEIGHT)
		{//���ɗ�����
			g_Player.state = PLAYERSTEAT_DEATH;
			g_Player.bDisp = false;
		}

		//�ʒu�̍X�V
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		//����
		g_Player.move.x += (0.0f - g_Player.move.x);

		//�ړ����[�v(X��)
		if (g_Player.pos.x < 0.0f)
		{//�E�[�܂ōs����
			g_Player.pos.x = SCREEN_WIDTH;
		}

		else if (g_Player.pos.x > SCREEN_WIDTH)
		{//���[�܂ōs����
			g_Player.pos.x = 0;
		}

		if (g_Player.bWalk == false)
		{
			if (g_Player.nDirectionMove == 0)
			{//�E�����̐Î~�A�j��
				if ((g_Player.nCntAnim % 8) == 0)
				{//��莞�Ԃ��o��

				 //�p�^�[�����X�V
					g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % PLAYER_PATTERN;

					pVtx[0].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.25f);
					pVtx[1].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.25f);
					pVtx[2].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.5f);
					pVtx[3].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.5f);
					if (g_Player.nPatternAnim % PLAYER_PATTERN == 0)
					{
						g_Player.nPatternAnim = 0;
					}
				}

			}
			else if (g_Player.nDirectionMove == 1)
			{//�������̐Î~�A�j��
				if ((g_Player.nCntAnim % 8) == 0)
				{//��莞�Ԃ��o��
				 //�p�^�[�����X�V
					g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % PLAYER_PATTERN;

					pVtx[0].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f, 0.25f);
					pVtx[3].tex = D3DXVECTOR2((g_Player.nPatternAnim % PLAYER_PATTERN) * 0.25f + 0.25f, 0.25f);

					if (g_Player.nPatternAnim % PLAYER_PATTERN == 0)
					{
						g_Player.nPatternAnim = 0;
					}
				}
			}
		}

		//�W�����v�A�j���[�V����
		if (g_Player.bJump == true)
		{
			if (g_Player.nDirectionMove == 0)
			{//�E����
				pVtx[0].tex = D3DXVECTOR2(0.25f, 0.75f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.75f);
				pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

			}
			else if (g_Player.nDirectionMove == 1)
			{//������
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.75f);
				pVtx[3].tex = D3DXVECTOR2(0.25f, 0.75f);
			}
		}


		//�u���b�N�̂����蔻��
		if (CollisionBlock(&g_Player.pos, &g_Player.posold, &g_Player.move) == true)
		{
			g_Player.bJump = false;
		}
		else
		{
			if (g_Player.bJump == false)
			{
				g_Player.bJump = true;
			}
		}

		CollsionItem(&g_Player.pos);
		CollisionDoor(&g_Player.pos);
	}

	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - 50, g_Player.pos.y - 100, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + 50, g_Player.pos.y - 100, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - 50, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + 50, g_Player.pos.y, 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// �v���C���[�`�ʏ���[DrawPolygon]
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	if (g_Player.bDisp == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
	}

}

//=============================================================================
// �v���C���[�̃_���[�W����
//=============================================================================
void HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;
	SetLife(g_Player.nLife);

	if (g_Player.nLife == 0)
	{
		g_Player.state = PLAYERSTEAT_DEATH;
		g_Player.nCntState = 60;
		g_Player.bDisp = false;

	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCntState = 5;//�_���[�W��Ԃ̎���

		VERTEX_2D *pVtx;// ���_���̍쐬
						
		//���_�o�b�t�@�����b�N
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();

	}

}

//=============================================================================
// �v���C���[�̎擾[GetPlayer]
//=============================================================================
Player*GetPlayer(void)
{
	return &g_Player;
}
