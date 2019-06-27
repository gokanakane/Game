//=============================================================================
//
// �Q�[������ [Game.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "Player.h"
#include "bg.h"
#include "Game.h"
#include "enemy.h"
#include "bow.h"
#include "score.h"
#include "fade.h"
#include "input.h"
#include "time.h"
#include "Item.h"
#include "Block.h"
#include "Pause.h"
#include "migawari.h"
#include "sound.h"
#include "Life.h"
#include "Door.h"
#include "Explosion.h"
#include "InterFase.h"
#include "mist.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
GAMESTATE g_GameState;	//�Q�[���̏��
int g_nCntGameState;	//�󋵊Ǘ��J�E���^�[
bool g_bPause;			//�|�[�Y�����ǂ���

//=============================================================================
// �Q�[������������[InitGame]
//=============================================================================
void InitGame(void)
{

	g_GameState = GAMESTATE_NONE;//�ʏ�ɐݒ�
	g_nCntGameState = 0;
	g_bPause = false;

	InitBG();//�w�i�̏���������
	InitDoor();//�h�A�̏���������
	InitPlayer();//�v���C���[�̏�����
	InitBlock();//�u���b�N�̏�����
	InitItem();//�A�C�e���̏�����
	InitEnemy();//�G�̏���������
	InitBow(); //�|�̏�����
	InitMigawari();//�g����̏���������
	InitInterFase();//�C���^�[�t�F�[�X����������
	InitScore();//�X�R�A�̏�����
	InitLife();//���C�t�̏���������
	InitTime();//�^�C���̏�����
	InitExplosion();
	InitMist();
	InitPause();//�|�[�Y�̏���������
	
	

	//�u���b�N�̐ݒu

		SetBlock(D3DXVECTOR3(150.0f, 680.0f, 0.0f), 1000, 50.0f, 0, 0);

	//�G�̑���i���j
		SetBlock(D3DXVECTOR3(0, 180.0f, 0.0f), 100, 50.0f, 2, 0);
		SetBlock(D3DXVECTOR3(0, 360.0f, 0.0f), 100, 50.0f, 2, 0);
		SetBlock(D3DXVECTOR3(0, 540.0f, 0.0f), 100, 50.0f, 2, 0);
	//�G�̔z�u�i���j
		SetEnemy(D3DXVECTOR3(40, 180.0f, 0.0f),1);
		SetEnemy(D3DXVECTOR3(40, 360.0f, 0.0f),1);
		SetEnemy(D3DXVECTOR3(40, 540.0f, 0.0f),1);

	//�G�̑���i�E�j
		SetBlock(D3DXVECTOR3(1200, 180.0f, 0.0f), 100, 50.0f, 2, 0);
		SetBlock(D3DXVECTOR3(1200, 360.0f, 0.0f), 100, 50.0f, 2, 0);
		SetBlock(D3DXVECTOR3(1200, 540.0f, 0.0f), 100, 50.0f, 2, 0);
	//�G�̑���i�E�j
		SetEnemy(D3DXVECTOR3(1240, 180.0f, 0.0f),0);
		SetEnemy(D3DXVECTOR3(1240, 360.0f, 0.0f), 0);
		SetEnemy(D3DXVECTOR3(1240, 540.0f, 0.0f), 0);

	//����
		SetBlock(D3DXVECTOR3(570, 170, 0.0f), 100, 50.0f, 0, 0);//����
		SetBlock(D3DXVECTOR3(200, 500, 0.0f), 100, 50.0f, 0, 0);
		SetBlock(D3DXVECTOR3(950, 440, 0.0f), 100, 50.0f, 0, 0);
		SetBlock(D3DXVECTOR3(200, 150, 0.0f), 100, 50.0f, 0, 0);
		SetBlock(D3DXVECTOR3(700, 200, 0.0f), 100, 50.0f, 0, 0);
		SetBlock(D3DXVECTOR3(900, 280, 0.0f), 100, 50.0f, 1, -1);
		SetBlock(D3DXVECTOR3(300, 380, 0.0f), 100, 50.0f, 3, -1);

	//�A�C�e���̐ݒu
		SetItem(D3DXVECTOR3(620, 130, 0.0f),3);
		SetItem(D3DXVECTOR3(200, 470, 0.0f), rand()%3);
		SetItem(D3DXVECTOR3(250, 470, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(300, 470, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(210, 120, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(250, 120, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(290, 120, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(330, 200, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(330, 250, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(350, 300, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(970, 410, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(1000, 380, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(1040, 410, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(910, 500, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(910, 560, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(910, 620, 0.0f), rand() % 3);
		SetItem(D3DXVECTOR3(850, 650, 0.0f), rand() % 3);

		//�h�A
		SetDoor(D3DXVECTOR3(620, 680, 0));
}
//=============================================================================
//�Q�[���I������ [UninitGame]
//=============================================================================
void UninitGame(void)
{
	UninitBG();//�w�i�̏I������
	UninitDoor();//�h�A�̏I������
	UninitPlayer();//�v���C���[�̏I������
	UninitBlock();//�u���b�N�̏I������
	UninitItem();//�A�C�e���̏I������
	UninitEnemy();//�G�̏I������
	UninitBow();//�|�̏I������
	UninitMigawari();//�g����̏I������
	UninitInterFase();//�C���^�[�t�F�[�X�̏I������
	UninitScore();//�X�R�A�̏I������
	UninitLife();//���C�t�̏I������
	UninitTime();//�^�C���̏I������
	UninitExplosion();
	UninitMist();
	UninitPause();//�|�[�Y�̏I������

}

//=============================================================================
// �Q�[���X�V����[UpdataGame]
//=============================================================================
void UpdateGame(void)
{	
	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�YON/OFF
		g_bPause = g_bPause ? false : true;
		PlaySound(SOUND_LABEL_SE_PAUSE);
	}

	if (g_bPause == false)
	{
		switch (g_GameState)
		{
		case GAMESTATE_NOMAL:
			break;

		case GAMESTATE_CLEAR:
			g_nCntGameState++;
			if (g_nCntGameState <= 60)
			{
				//g_GameState = GAMESTATE_NONE;
				//��ʁi���[�h�j�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;

		case GAMESTATE_OVER:
			g_nCntGameState++;
			if (g_nCntGameState <= 60)
			{
				//��ʁi���[�h�j�̐ݒ�
				SetFade(MODE_RESULT);
				//g_GameState = GAMESTATE_NONE;
			}
			break;
		}
			UpdateBG();//�w�i�̍X�V����
			UpdateDoor();//�h�A�̍X�V����
			UpdatePlayer();//�v���C���[�̍X�V����
			UpdateBlock();//�u���b�N�̍X�V����
			UpdateItem();//�A�C�e���̍X�V����
			UpdateEnemy();//�G�̍X�V����
			UpdateBow();//�|�̍X�V����
			UpdateMigawari();//�g����̍X�V����
			UpdateInterFase();//�C���^�[�t�F�[�X�̍X�V����
			UpdateScore();//�X�R�A�̍X�V����
			UpdateLife();//���C�t�̍X�V����
			UpdateTime();//�^�C���̍X�V����
			UpdateExplosion();
			UpdateMist();
		}
	else
	{
		UpdatePause();//�|�[�Y�̍X�V����
	}
}
//=============================================================================
// �Q�[���`�ʏ���[DrawGame]
//=============================================================================
void DrawGame(void)
{
	DrawBG();//�w�i�̕`�揈��
	DrawBlock();//�u���b�N�̕`�揈��
	DrawDoor();//�h�A�̕`�揈��
	DrawPlayer();//�v���C���[�̕`�揈��
	DrawEnemy();//�G�̕`�揈��
	DrawBow();//�|�̕`�揈��
	DrawItem();//�A�C�e���̕`�揈��
	DrawMigawari();//�g����̕`�揈��
	DrawInterFase();//�C���^�[�t�F�[�X�̕`�揈��
	DrawScore();//�X�R�A�̕`�揈��
	DrawLife();//���C�t�̕`�揈��
	DrawTime();//�^�C���̕`�揈��
	DrawExplosion();
	DrawMist();

	if (g_bPause == true)
	{
		DrawPause();//�|�[�Y�̕`�揈��
	}
}

//=============================================================================
// �Q�[���̐ݒ菈��[SetGame]
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_GameState = state;
	g_nCntGameState = 0;

}

//=============================================================================
// �Q�[���̎擾����[SetGame]
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_GameState;
}
//=============================================================================
// �|�[�Y��Ԃ̎擾����[SetGame]
//=============================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}