//=============================================================================
//
// �w�i���� [tutorial.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "main.h"
#include "tutorial.h"
#include "fade.h"
#include "input.h"
#include "bg.h"
#include "Player.h"
#include "Block.h"
#include "Item.h"
#include "Door.h"
#include "TutorialBG.h"
#include "Explosion.h"
#include "migawari.h"
#include "enemy.h"
#include "bow.h"
#include "sound.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �|���S������������[InitPolygon]
//=============================================================================
void InitTutorial(void)
{
	InitBG();//�w�i�̏���������
	InitDoor();//�h�A�̏���������
	InitBlock();//�u���b�N�̏�����
	InitItem();//�A�C�e���̏�����
	InitEnemy();//�G�̏���������
	InitBow(); //�|�̏�����
	InitPlayer();//�v���C���[�̏�����
	InitMigawari();//�g����̏���������
	InitTutorialBG();
	InitExplosion();
	
	SetBlock(D3DXVECTOR3(-100, 680.0f, 0.0f), 1500, 50.0f, 0, 0);

	SetBlock(D3DXVECTOR3(730, 450, 0.0f), 80, 50.0f, 0, 0);//�����̑���
	SetBlock(D3DXVECTOR3(0, 400, 0.0f), 80, 50.0f, 2, 0);//�G�̑���
	SetBlock(D3DXVECTOR3(500, 450, 0.0f), 80, 50.0f, 1, 1);
	SetBlock(D3DXVECTOR3(300, 500, 0.0f), 80, 50.0f, 3, 1);

	SetEnemy(D3DXVECTOR3(25, 400, 0.0f), 1);
	SetItem(D3DXVECTOR3(750, 420, 0.0f), 3);
	SetItem(D3DXVECTOR3(300, 650, 0.0f), 0);
	SetItem(D3DXVECTOR3(400, 650, 0.0f), 1);
	SetItem(D3DXVECTOR3(300, 480, 0.0f), 2);
	SetItem(D3DXVECTOR3(600, 650, 0.0f), 2);

	SetDoor(D3DXVECTOR3(1100, 680, 0));

}
//=============================================================================
//�|���S���I������ [UninitPolygon]
//=============================================================================
void UninitTutorial(void)
{
	UninitBG();//�w�i�̏I������
	UninitDoor();//�h�A�̏I������
	UninitPlayer();//�v���C���[�̏I������
	UninitBlock();//�u���b�N�̏I������
	UninitItem();//�A�C�e���̏I������
	UninitEnemy();//�G�̏I������
	UninitBow();//�|�̏I������
	UninitMigawari();//�g����̏I������
	UninitTutorialBG();
	UninitExplosion();

}

//=============================================================================
// �|���S���X�V����[UpdataPolygon]
//=============================================================================
void UpdateTutorial(void)
{
	FADE g_fade;
	g_fade = GetFade();
	Player*pPlayer;
	pPlayer = GetPlayer();

	UpdateBG();//�w�i�̕`�揈��
	UpdateBlock();//�u���b�N�̕`�揈��
	UpdateDoor();//�h�A�̕`�揈��
	UpdatePlayer();//�v���C���[�̕`�揈��
	UpdateEnemy();//�G�̕`�揈��
	UpdateBow();//�|�̕`�揈��
	UpdateItem();//�A�C�e���̕`�揈��
	UpdateMigawari();//�g����̕`�揈��
	UpdateTutorialBG();
	UpdateExplosion();

	//Enter�L�[�������ꂽ
	if (CollisionDoor(&pPlayer->pos) == true)
	{
		if (g_fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�ݒ�
			SetFade(MODE_GAME);
		}
	}

}
//=============================================================================
// �|���S���`�ʏ���[DrawPolygon]
//=============================================================================
void DrawTutorial(void)
{
	DrawBG();//�w�i�̕`�揈��
	DrawBlock();//�u���b�N�̕`�揈��
	DrawDoor();//�h�A�̕`�揈��
	DrawPlayer();//�v���C���[�̕`�揈��
	DrawEnemy();//�G�̕`�揈��
	DrawBow();//�|�̕`�揈��
	DrawItem();//�A�C�e���̕`�揈��
	DrawMigawari();//�g����̕`�揈��
	DrawTutorialBG();
	DrawExplosion();
}