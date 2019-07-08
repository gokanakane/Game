//=============================================================================
//
// �v���C���[���� [Player.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "sound.h"
#include "Game.h"
#include "Player.h"
#include "bullet.h"
#include "Explosion.h"
#include "Life.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
VERTEX_2D g_aVetex[4];						//���_�����i�[����
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;
int g_nCntAnim;								//�A�j���[�V�����J�E���^�[
int g_nPatternAnim;							//�A�j���[�V�����p�^�[��NO
Player g_Player;

//=============================================================================
// �v���C���[����������[InitPlayer]
//=============================================================================
void InitPlayer(void)
{	
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�J�E���^�[�ƃp�^�[��No��������
	g_nCntAnim = 0;
	g_nPatternAnim = 0;

	g_Player.pos = D3DXVECTOR3(600, 600, 0.0f);	//�v���C���[�̈ʒu
	g_Player.move = D3DXVECTOR3(0, 0, 0.0f);
	g_Player.bDisp = true;
	g_Player.nCntState = 0;
	g_Player.state = PLAYERSTATE_NOMAL;
	g_Player.nLife = MAXPLAYER_LIFE;


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
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - 25, g_Player.pos.y - 25, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + 25, g_Player.pos.y - 25, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - 25, g_Player.pos.y + 25, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + 25, g_Player.pos.y + 25, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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
		g_Player.nCntState--;
		return;
		break;

	}

	//g_nCntAnim++;//�J�E���^�[�̉��Z

	//if ((g_nCntAnim % POLYGON_CNTANIM) == 0)//��莞�Ԃ��o��
	//{
	//	g_nPatternAnim = (g_nPatternAnim + 1) % POLYGON_PATTERN;		//�p�^�[�����X�V
	//}

	//g_posPolygon += g_movePolygon;


	//���ɓ�����
	if (GetKeyboardPress(DIK_A) == true)
	{	//�C�ӂ̃L�[�iA�j�������ꂽ��
		if (GetKeyboardPress(DIK_W) == true)
		{	//�C�ӂ̃L�[�iW�j�������ꂽ��
			//����
			g_Player.move.x += sinf(-D3DX_PI * 0.75f)* PLAYER_MOVE;
			g_Player.move.y += cosf(-D3DX_PI * 0.75f)* PLAYER_MOVE;
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{	//�C�ӂ̃L�[�iS�j�������ꂽ��

			//����
			g_Player.move.x += sinf(-D3DX_PI * 0.25)* PLAYER_MOVE;
			g_Player.move.y += cosf(-D3DX_PI * 0.25)* PLAYER_MOVE;
		}

		else
		{//A�����������ꂽ
			//����
			g_Player.move.x += sinf(D3DX_PI * -0.5)* PLAYER_MOVE;
			g_Player.move.y += cosf(D3DX_PI * -0.5)* PLAYER_MOVE;

		}
	}

	//�E�ɓ�����
	else if (GetKeyboardPress(DIK_D) == true)
	{	//�C�ӂ̃L�[�iD�j�������ꂽ��

		if (GetKeyboardPress(DIK_W) == true)
		{	//�C�ӂ̃L�[�iW�j�������ꂽ��
			//����
			g_Player.move.x += sinf(D3DX_PI*0.75f)* PLAYER_MOVE;
			g_Player.move.y += cosf(D3DX_PI*0.75f)* PLAYER_MOVE;

		}

		else if (GetKeyboardPress(DIK_S) == true)
		{	//�C�ӂ̃L�[�iS�j�������ꂽ��
			//����
			g_Player.move.x += sinf(D3DX_PI * 0.25)* PLAYER_MOVE;
			g_Player.move.y += cosf(D3DX_PI * 0.25)* PLAYER_MOVE;
		}

		else
		{//D�̂݉����ꂽ
			//����
			g_Player.move.x += sinf(D3DX_PI *0.5)* PLAYER_MOVE;
			g_Player.move.y += cosf(D3DX_PI *0.5)* PLAYER_MOVE;
		}
	}

	//��ɓ�����
	else if (GetKeyboardPress(DIK_W) == true)
	{	//�C�ӂ̃L�[�iW�j�������ꂽ��
		//����
		g_Player.move.x += sinf(D3DX_PI)* PLAYER_MOVE;
		g_Player.move.y += cosf(D3DX_PI)* PLAYER_MOVE;

	}


	//���ɓ���
	else if (GetKeyboardPress(DIK_S) == true)
	{//�C�ӂ̃L�[�iS�j�������ꂽ��
		//����
		g_Player.move.x -= sinf(D3DX_PI)* PLAYER_MOVE;
		g_Player.move.y -= cosf(D3DX_PI)* PLAYER_MOVE;

	}
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -7.0f, 0.0f), BULLETTYPE_PLAYER,60);
		SetBullet(g_Player.pos, D3DXVECTOR3(2.0f, -5.0f, 0.0f), BULLETTYPE_PLAYER,60);
		SetBullet(g_Player.pos, D3DXVECTOR3(-2.0f, -5.0f, 0.0f), BULLETTYPE_PLAYER,60);

	}

	//�ʒu�̍X�V
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;

	//�ړ��͈�(X��)
	if (g_Player.pos.x <= 25)
	{
		g_Player.pos.x = 25;
	}
	else if (g_Player.pos.x + 25 >= SCREEN_WIDTH)
	{
		g_Player.pos.x = SCREEN_WIDTH - 25;
	}
	//�ړ��͈�(Y��)
	if (g_Player.pos.y <= 25)
	{
		g_Player.pos.y = 25;
	}
	else if (g_Player.pos.y + 25 >= SCREEN_HEIGHT)
	{
		g_Player.pos.y = SCREEN_HEIGHT - 25;
	}



	//����
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.4f;
	g_Player.move.y += (0.0f - g_Player.move.y) * 0.4f;

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - 25, g_Player.pos.y - 25, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + 25, g_Player.pos.y - 25, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - 25, g_Player.pos.y + 25, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + 25, g_Player.pos.y + 25, 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPlayer->Unlock();


	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	//g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���摜�̍X�V
	//pVtx[0].tex = D3DXVECTOR2((g_nPatternAnim % 5) * 0.2f, (g_nPatternAnim / 5)*0.5f);
	//pVtx[1].tex = D3DXVECTOR2((g_nPatternAnim % 5) * 0.2f + 0.2f, (g_nPatternAnim / 5)*0.5f);
	//pVtx[2].tex = D3DXVECTOR2((g_nPatternAnim % 5) * 0.2f, (g_nPatternAnim / 5)* 0.5f + 0.5f);
	//pVtx[3].tex = D3DXVECTOR2((g_nPatternAnim % 5) * 0.2f + 0.2f, (g_nPatternAnim / 5)*0.5f + 0.5f);

}
//=============================================================================
// �v���C���[�`�ʏ���[DrawPolygon]
//=============================================================================
void DrawPlayer(void)
{		
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	if (g_Player.bDisp == true)
	{
		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

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

	if (g_Player.nLife <= 0)
	{
		SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_Player.state = PLAYERSTEAT_DEATH;
		g_Player.nCntState = 60;
		g_Player.bDisp = false;
		SetGameState(GAMESTATE_OVER);

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
Player *GetPlayer(void)
{
	return &g_Player;
}