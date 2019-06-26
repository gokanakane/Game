//=============================================================================
//
// �|�[�Y���� [Pause.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "Pause.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEX (5)											 //�e�N�X�`���̐�
#define PAUSECONRINUE_TEXTUER  "data\\TEXTURE\\Pause\\Continue.png"//�ǂݍ��ރe�N�X�`��
#define PAUSERETRY_TEXTUER  "data\\TEXTURE\\Pause\\Retry.png"		//�ǂݍ��ރe�N�X�`��
#define PAUSEQUIT_TEXTUER  "data\\TEXTURE\\Pause\\Quit.png"		//�ǂݍ��ރe�N�X�`��
#define PAUSE_TEXTUER "data\\TEXTURE\\Tutorial\\Tutorial001.png"			//�ǂݍ��ރe�N�X�`��
#define PAUSEMASK_TEXTURE " "
#define PAUSEBG_POS_X (630)								  //�|�[�Y�w�i����X
#define PAUSEBG_POS_Y (180)								   //�|�[�Y�w�i����Y
#define PAUSEBG_WIDTH (990)									//�|�[�Y�w�i�̕�
#define PAUSEBG_HEIGHT (580)								    //�|�[�Y�w�i����
#define PASUSE_WIDTH (110.0f)								//���S�̊Ԋu
#define MAX_MENU (3)										//�I�����̐�
#define MAX_ANIMATION (4)									//�A�j���[�V�����p�^�[��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPause(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_TEX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;
PAUSESTATE g_PauseMode;
COLORSTATE g_PauseColor;
Pause g_Pause;
int g_nSelectManu;

//=============================================================================
// �|�[�Y����������[InitPolygon]
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_nSelectManu = 0;
	g_PauseMode = PAUSESTATE_NONE;
	g_PauseColor = PAUSESTATECOLOR_NONE;

	g_Pause.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Pause.CntMove = 0.0f;
	g_Pause.ChengeMove = 0.1f;
	g_Pause.PatturnAnim = 0;
	g_Pause.CntAnim = 0;
	g_Pause.bAnim = false;

	MakeVertexPause(pDevice);


}
//=============================================================================
//�|�[�Y�I������ [UninitPolygon]
//=============================================================================
void UninitPause(void)
{	
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePause[nCnt] != NULL)
		{
			g_pTexturePause[nCnt]->Release();
			g_pTexturePause[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

}

//=============================================================================
// �|�[�Y�X�V����[UpdataPolygon]
//=============================================================================
void UpdatePause(void)
{
	FADE g_Fade;
	g_Fade = GetFade();
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	g_Pause.CntAnim++;

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	if (rand() % 100 == 0)
	{
		g_Pause.bAnim = true;
	}

	if (g_Pause.bAnim == true)
	{
		if (g_Pause.CntAnim % 4 == 0)
		{
			g_Pause.PatturnAnim++;
		}

		//�˂��e�N�X�`���̐ݒ�
		pVtx[4].tex = D3DXVECTOR2(g_Pause.PatturnAnim*0.25f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(g_Pause.PatturnAnim*0.25f + 0.25f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(g_Pause.PatturnAnim*0.25f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(g_Pause.PatturnAnim*0.25f + 0.25f, 1.0f);

		if (g_Pause.PatturnAnim >= MAX_ANIMATION)
		{
			g_Pause.PatturnAnim = 0;
			g_Pause.bAnim = false;
		}
	}

	//�Z���N�g
	if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectManu = (g_nSelectManu + 1) % 3;
	}

	if (GetKeyboardTrigger(DIK_UP) == true)
	{
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelectManu = (g_nSelectManu + 2) % 3;
	}

	
	//���j���[�I����̏���
	if (g_nSelectManu == 0)
	{
		//�F�Ǘ�
		g_PauseColor = PAUSESTATECOLOR_CONTINUE;

		//�I�����̃A�j���[�V����aa
		if (g_Pause.CntMove >= 1 || g_Pause.CntMove <= -1)
		{
			g_Pause.ChengeMove *= -1.0f;//�܂�Ԃ�
		}

		g_Pause.CntMove += g_Pause.ChengeMove;
		g_Pause.pos.y += g_Pause.CntMove;


		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				g_PauseMode = PAUSESTATE_CONTINUE;
			}
		}
	}
	
	if (g_nSelectManu == 1)
	{
		//�F�Ǘ�
		g_PauseColor = PAUSESTATECOLOR_RETRY;

		//�I�����̃A�j���[�V����
		if (g_Pause.CntMove >= 1 || g_Pause.CntMove <= -1)
		{
			g_Pause.ChengeMove *= -1.0f;//�܂�Ԃ�
		}

		g_Pause.CntMove += g_Pause.ChengeMove;
		g_Pause.pos.y += g_Pause.CntMove;


		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				g_PauseMode = PAUSESTATE_RETRY;
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}
	}

	if (g_nSelectManu == 2)
	{
		//�F�Ǘ�
		g_PauseColor = PAUSESTATECOLOR_QUIT;

		//�I�����̃A�j���[�V����aa
		if (g_Pause.CntMove >= 1 || g_Pause.CntMove <= -1)
		{
			g_Pause.ChengeMove *= -1.0f;//�܂�Ԃ�
		}

		g_Pause.CntMove += g_Pause.ChengeMove;
		g_Pause.pos.y += g_Pause.CntMove;


		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				g_PauseMode = PAUSESTATE_QUIT;
			}
		}
	}

	switch (g_PauseColor)
	{
	case PAUSESTATECOLOR_NONE:
		break;

	case PAUSESTATECOLOR_CONTINUE:
		//�w�i�F�ݒ�(Continue�I��)------------------------------------
		//Continue
		pVtx[8].pos = D3DXVECTOR3(380.0f, 150.0f + g_Pause.pos.y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[9].pos = D3DXVECTOR3(660.0f, 150.0f + g_Pause.pos.y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[10].pos = D3DXVECTOR3(380.0f, 270.0f + g_Pause.pos.y, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[11].pos = D3DXVECTOR3(660.0f, 270.0f + g_Pause.pos.y, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//Retry
		pVtx[12].pos = D3DXVECTOR3(380.0f, 300.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[13].pos = D3DXVECTOR3(660.0f, 300.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[14].pos = D3DXVECTOR3(380.0f, 420.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[15].pos = D3DXVECTOR3(660.0f, 420.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		//Quit
		pVtx[16].pos = D3DXVECTOR3(380.0f, 450.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[17].pos = D3DXVECTOR3(660.0f, 450.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[18].pos = D3DXVECTOR3(380.0f, 570.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[19].pos = D3DXVECTOR3(660.0f, 570.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		break;

	case PAUSESTATECOLOR_RETRY:
		//�w�i�F�ݒ�(Retry�I��)------------------------------------
		//Continue
		pVtx[8].pos = D3DXVECTOR3(380.0f, 150.0f,0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[9].pos = D3DXVECTOR3(660.0f, 150.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[10].pos = D3DXVECTOR3(380.0f, 270.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[11].pos = D3DXVECTOR3(660.0f, 270.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		//Retry
		pVtx[12].pos = D3DXVECTOR3(380.0f, 300.0f + g_Pause.pos.y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[13].pos = D3DXVECTOR3(660.0f, 300.0f + g_Pause.pos.y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[14].pos = D3DXVECTOR3(380.0f, 420.0f + g_Pause.pos.y, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[15].pos = D3DXVECTOR3(660.0f, 420.0f + g_Pause.pos.y, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//Quit
		pVtx[16].pos = D3DXVECTOR3(380.0f, 450.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[17].pos = D3DXVECTOR3(660.0f, 450.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[18].pos = D3DXVECTOR3(380.0f, 570.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[19].pos = D3DXVECTOR3(660.0f, 570.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		break;


	case PAUSESTATECOLOR_QUIT:
		//�w�i�F�ݒ�(Quit�I��)------------------------------------
		//Continue
		pVtx[8].pos = D3DXVECTOR3(380.0f, 150.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[9].pos = D3DXVECTOR3(660.0f, 150.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[10].pos = D3DXVECTOR3(380.0f, 270.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[11].pos = D3DXVECTOR3(660.0f, 270.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		//Retry
		pVtx[12].pos = D3DXVECTOR3(380.0f, 300.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[13].pos = D3DXVECTOR3(660.0f, 300.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[14].pos = D3DXVECTOR3(380.0f, 420.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[15].pos = D3DXVECTOR3(660.0f, 420.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		//Quit
		pVtx[16].pos = D3DXVECTOR3(380.0f, 450.0f + g_Pause.pos.y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[17].pos = D3DXVECTOR3(660.0f, 450.0f + g_Pause.pos.y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[18].pos = D3DXVECTOR3(380.0f, 570.0f + g_Pause.pos.y, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[19].pos = D3DXVECTOR3(660.0f, 570.0f + g_Pause.pos.y, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		break;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPause->Unlock();


	switch (g_PauseMode)
	{
	case PAUSESTATE_CONTINUE:
		g_PauseMode = PAUSESTATE_NONE;
		SetPause(false);
		break;

	case PAUSESTATE_RETRY:
		g_PauseMode = PAUSESTATE_NONE;
		SetFade(MODE_GAME);
		break;

	case PAUSESTATE_QUIT:
		g_PauseMode = PAUSESTATE_NONE;
		SetFade(MODE_TITLE);
		break;	

	}

}
//=============================================================================
// �|�[�Y�`�ʏ���[DrawPolygon]
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePause[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPause(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PAUSEMASK_TEXTURE, &g_pTexturePause[0]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTUER, &g_pTexturePause[1]);
	D3DXCreateTextureFromFile(pDevice, PAUSECONRINUE_TEXTUER, &g_pTexturePause[2]);
	D3DXCreateTextureFromFile(pDevice, PAUSERETRY_TEXTUER, &g_pTexturePause[3]);
	D3DXCreateTextureFromFile(pDevice, PAUSEQUIT_TEXTUER, &g_pTexturePause[4]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//----------�}�X�N-----------
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

																 //rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�|�[�Y�w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j

													//�|�[�Y�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�L�w�i�̍��W�ݒ�
	pVtx[4].pos = D3DXVECTOR3(PAUSEBG_POS_X, PAUSEBG_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[5].pos = D3DXVECTOR3(PAUSEBG_WIDTH, PAUSEBG_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[6].pos = D3DXVECTOR3(PAUSEBG_POS_X, PAUSEBG_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[7].pos = D3DXVECTOR3(PAUSEBG_WIDTH, PAUSEBG_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

																   //rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//�|�[�Y�w�i�F�ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

													//�|�[�Y�w�i�e�N�X�`���̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.25f, 1.0f);

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//�R���e�j���[���W�ݒ�
		pVtx[8].pos = D3DXVECTOR3(380, 150 + (150.0f * nCnt), 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[9].pos = D3DXVECTOR3(660, 150 + (150.0f * nCnt), 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[10].pos = D3DXVECTOR3(380, 270 + (150.0f * nCnt), 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[11].pos = D3DXVECTOR3(660, 270 + (150.0f * nCnt), 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		 //rhw�̐ݒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//�w�i�F�ݒ�
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

														 //�w�i�e�N�X�`���̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPause->Unlock();


}