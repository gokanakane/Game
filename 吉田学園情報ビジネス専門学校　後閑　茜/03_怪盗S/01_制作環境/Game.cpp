//=============================================================================
//
// �Q�[������ [Game.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "Game.h"
#include "Player.h"
#include "input.h"
#include "Pause.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "Wall.h"
#include "Stage.h"
#include "fade.h"
#include "Obj.h"
#include "time.h"
#include "bullet.h"
#include "explosion.h"
#include "score.h"
#include "Enemy.h"
#include "Item.h"
#include "DisPlay.h"
#include "ItemUI.h"
#include "ItemGetUI.h"
#include "sound.h"

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
	
	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	//���b�V���t�B�[���h�̏���������
	InitStage();

	//�e�̏�����
	InitShadow();

	//�e�̏�����
	InitBullet();

	//���f���̏�����
	InitObj();

	//�f�B�X�v���C���f���̏�����
	InitDisPlay();

	//�A�C�e���̏�����
	InitItem();

	//�v���C���[�̏���������
	InitPlayer();

	//�G�̏���������
	InitEnemy();

	//���b�V���E�H�[���̏���������
	InitWall();

	//�����̏�����
	InitExplosion();

	//�^�C���̏���������
	InitTime();

	//�X�R�A�̏���������
	InitScore();

	//�A�C�e��UI�̏�����
	InitItemUI();

	//�A�C�e���̏�����UI�̏�����
	InitItemGetUI();

	//�|�[�Y�̏�����
	InitPause();

	//�G�̐ݒu
	SetEnemy(D3DXVECTOR3(430.0f, 0.0f, 10.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f), 1, 0);
	SetEnemy(D3DXVECTOR3(330.0f, 0.0f, -130.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f), 1,0);
	SetEnemy(D3DXVECTOR3(130.0f, 0.0f, -520.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f), 1, 0);

	//����
	SetObj(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),0);

	//�A�C�e��
	//a
	SetDisPlay(D3DXVECTOR3(340.0f, 0.0f, -380.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetItem(D3DXVECTOR3(340.0f, 8.0f, -380.0f), 0);

	//b
	SetDisPlay(D3DXVECTOR3(280.0f, 0.0f, -120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
	SetItem(D3DXVECTOR3(280.0f, 8.0f, -120.0f), 1);

	//c
	SetDisPlay(D3DXVECTOR3(280.0f, 0.0f, -480.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
	SetItem(D3DXVECTOR3(280.0f, 8.0f, -480.0f), 2);

	//d
	SetDisPlay(D3DXVECTOR3(220.0f, 0.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetItem(D3DXVECTOR3(220.0f, 8.0f, 20.0f), 3);

	//��
	SetItem(D3DXVECTOR3(480.0f, 0.0f, -280.0f),4);

}
//=============================================================================
//�Q�[���I������ [UninitGame]
//=============================================================================
void UninitGame(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	//���b�V���t�B�[���h�̏I������
	UninitStage();

	//�e�̏I������
	UninitShadow();

	//�e�̏I������
	UninitBullet();

	//���f���̏I������
	UninitObj();

	//�f�B�X�v���C���f���̏I������
	UninitDisPlay();

	//�A�C�e���̏I������
	UninitItem();

	//�v���C���[�̏I������
	UninitPlayer();

	//�G�̏I������
	UninitEnemy();

	//���b�V���E�H�[���̏I������
	UninitWall();

	//�����̏I������
	UninitExplosion();

	//�^�C���̏I������
	UninitTime();

	//�X�R�A�̏I������
	UninitScore();

	//�A�C�e��UI�̏I������
	UninitItemUI();

	//�A�C�e�������󋵂̏I������
	UninitItemGetUI();

	//�|�[�Y�̏I������
	UninitPause();

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
				//��ʁi���[�h�j�̐ݒ�
				SetFade(MODE_RESULT);
				//g_GameState = GAMESTATE_NONE;
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
		
		if (g_GameState == GAMESTATE_NONE)
		{
			// �J�����̍X�V����
			UpdateCamera();

			// ���C�g�̍X�V����
			UpdateLight();

			//���b�V���t�B�[���h�̍X�V����
			UpdateStage();

			//�e�̍X�V����
			UpdateShadow();

			//�o���b�g�̍X�V����
			UpdateBullet();

			//���f���̍X�V����
			UpdateObj();

			//�f�B�X�v���C���f���̍X�V����
			UpdateDisPlay();

			//�A�C�e���̍X�V����
			UpdateItem();

			//�v���C���[�̍X�V����
			UpdatePlayer();

			//�G�̍X�V����
			UpdateEnemy();

			//���b�V���E�H�[���̍X�V����
			UpdateWall();

			//�����̍X�V����
			UpdateExplosion();

			//�^�C���̍X�V����
			UpdateTime();

			//�X�R�A�̍X�V����
			UpdateScore();

			//�A�C�e��UI�̍X�V����
			UpdateItemUI();

			//�A�C�e���擾�󋵂̍X�V����
			UpdateItemGetUI();
		}

	}
	else
	{
		UpdatePause();//�|�[�Y�̍X�V����
	}

	//if (GetKeyboardPress(DIK_H) == true)
	//{//�N���A�f�o�b�N�L�[
	//	SetGameState(GAMESTATE_CLEAR);
	//}
	//if (GetKeyboardPress(DIK_F) == true)
	//{//�I�[�o�[�f�o�b�N�L�[
	//	SetGameState(GAMESTATE_OVER);
	//}

}
//=============================================================================
// �Q�[���`�ʏ���[DrawGame]
//=============================================================================
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	//���b�V���t�B�[���h�̕`�揈��
	DrawStage();

	//�e�̕`�揈��
	DrawShadow();

	//�e�̕`�揈��
	DrawBullet();

	//���f���̕`�揈��
	DrawObj();

	//�f�B�X�v���C���f���̕`�揈��
	DrawDisPlay();
	
	//�A�C�e���̕`�揈��
	DrawItem();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�G�̕`�揈��
	DrawEnemy();

	//���b�V���E�H�[���̕`�揈��
	DrawWall();

	//�����̕`�揈��
	DrawExplosion();

	//�^�C���̍X�V����
	DrawTime();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�A�C�e��UI�̕`�揈��
	DrawItemUI();

	//�A�C�e���̎擾�󋵂̕`�揈��
	DrawItemGetUI();

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