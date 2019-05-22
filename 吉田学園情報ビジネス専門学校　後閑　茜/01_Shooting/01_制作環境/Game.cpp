//=============================================================================
//
// �Q�[������ [Game.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "Player.h"
#include "bg.h"
#include "bullet.h"
#include "Explosion.h"
#include "enemy.h"
#include "Game.h"
#include "score.h"
#include "effect.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "Pause.h"
#include "time.h"
#include "Life.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

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
	InitEnemy();//�G�̏���������
	InitEffect();//�G�t�F�N�g�̏���������
	InitBullet();//�e�̏���������
	InitExplosion();//���e�̏���������
	InitScore();//�X�R�A�̏���������
	InitPlayer();//�v���C���[�̏���������
	InitPause();//�|�[�Y�̏���������
	InitTime();//�������Ԃ̏�����
	InitLife();//���C�t�̏���������

//�G�̔z�u
//�Ō��
	SetEnemy(D3DXVECTOR3(300, 100, 0.0f), 3, -1,10);//�G�̐ݒ�[3]
	SetEnemy(D3DXVECTOR3(400, 100, 0.0f), 0, -1,2);//�G�̐ݒ�[0]
	SetEnemy(D3DXVECTOR3(500, 100, 0.0f), 1, -1,3);//�G�̐ݒ�[1]
	SetEnemy(D3DXVECTOR3(600, 100, 0.0f), 2, -1,4);//�G�̐ݒ�[2]
	SetEnemy(D3DXVECTOR3(700, 100, 0.0f), 3, -1,8);//�G�̐ݒ�[3]
	SetEnemy(D3DXVECTOR3(800, 100, 0.0f), 0, -1,2);//�G�̐ݒ�[0]

//�O���
	SetEnemy(D3DXVECTOR3(400, 150, 0.0f), 3, 1,10);//�G�̐ݒ�[3]
	SetEnemy(D3DXVECTOR3(500, 150, 0.0f), 2, 1,4);//�G�̐ݒ�[2]
	SetEnemy(D3DXVECTOR3(600, 150, 0.0f), 1, 1,3);//�G�̐ݒ�[1]
	SetEnemy(D3DXVECTOR3(700, 150, 0.0f), 0, 1,2);//�G�̐ݒ�[0]
 //����
	SetEnemy(D3DXVECTOR3(400, 200, 0.0f), 0, -1,2);//�G�̐ݒ�[0]
	SetEnemy(D3DXVECTOR3(500, 200, 0.0f), 1, -1,3);//�G�̐ݒ�[1]
	SetEnemy(D3DXVECTOR3(600, 200, 0.0f), 2, -1,4);//�G�̐ݒ�[2]
	SetEnemy(D3DXVECTOR3(700, 200, 0.0f), 3, -1,10);//�G�̐ݒ�[3]
//����
	SetEnemy(D3DXVECTOR3(400, 250, 0.0f), 2, 1,10);//�G�̐ݒ�[0]
	SetEnemy(D3DXVECTOR3(500, 250, 0.0f), 1, 1,4);//�G�̐ݒ�[1]
	SetEnemy(D3DXVECTOR3(600, 250, 0.0f), 0, 1,3);//�G�̐ݒ�[2]
	SetEnemy(D3DXVECTOR3(700, 250, 0.0f), 3, 1,2);//�G�̐ݒ�[3]


}
//=============================================================================
//�Q�[���I������ [UninitGame]
//=============================================================================
void UninitGame(void)
{
	UninitBG();//�w�i�̏I������
	UninitEnemy();//�G�̏I������
	UninitEffect();//�G�t�F�N�g�̏I������
    UninitBullet();//�e�̏I������
	UninitExplosion();//���e�̏I������
	UninitScore();//�X�R�A�̏I������
	UninitPlayer();//�v���C���[�̏I������
	UninitPause();//�|�[�Y�̏I������
	UninitTime();//�������Ԃ̏I������
	UninitLife();//���C�t�̏I������

}

//=============================================================================
// �Q�[���X�V����[UpdataGame]
//=============================================================================
void UpdateGame(void)
{	
	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�YON/OFF
		PlaySound(SOUND_LABEL_SE_PAUSE);
		g_bPause = g_bPause ? false : true;
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
		UpdateEnemy();//�G�̍X�V����
		UpdateEffect();//�G�t�F�N�g�̍X�V����
		UpdateBullet();//�e�̍X�V����
		UpdateExplosion();//���e�̍X�V����
		UpdateScore();//�X�R�A�̍X�V����
		UpdatePlayer();//�v���C���[�̍X�V����
		UpdateTime();//�������Ԃ̍X�V����
		UpdateLife();//���C�t�̍X�V����
	}
	else
	{
		UpdatePause();
	}

}
//=============================================================================
// �Q�[���`�ʏ���[DrawGame]
//=============================================================================
void DrawGame(void)
{
	DrawBG();//�w�i�̕`�ʏ���
	DrawEnemy();//�G�̕`�揈��
	DrawEffect();//�G�t�F�N�g�̕`�揈��
	DrawBullet();//�e�̕`�揈��
	DrawExplosion();//���e�̕`�揈��
	DrawScore();//�X�R�A�̕`�揈��
	DrawPlayer();//�v���C���[�̕`�ʏ���
	DrawTime();//�������Ԃ̕`�揈��
	DrawLife();//���C�t�̏I������

	if (g_bPause == true)
	{
		DrawPause();
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