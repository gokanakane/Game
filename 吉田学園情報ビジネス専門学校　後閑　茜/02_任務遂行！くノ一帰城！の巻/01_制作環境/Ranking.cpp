//=============================================================================
//
// �^�C�g���w�i���� [Ranking.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Ranking.h"
#include "RankingScore.h"
#include"input.h"
#include "fade.h"
#include"sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANKING_TEXTURE "data\\TEXTURE\\UI\\Ranking000.png" //�����L���O����
#define RANKING_TEXTURE0 "data\\TEXTURE\\BG\\Sky001.jpg"	//�w�i
#define RANKING_TEXTURE2 "data\\TEXTURE\\UI\\Ranking001.png"//����
#define Ranking_POS_X (300)									//�^�C�g������X
#define Ranking_POS_Y (500)									//�^�C�g������Y
#define Ranking_WIDTH (SCREEN_WIDTH)						//�^�C�g���̕�
#define Ranking_HEIGHT (SCREEN_HEIGHT)						//�^�C�g������
#define MAX_TEX (3)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRanking[MAX_TEX] = {};//�e�N�X�`���ւ̃|�C���^jpg
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;
int g_nAlphaRogo;
int g_nCntTitleRanking;			//�t�F�[�h����
int g_nCntMoveTex;
//=============================================================================
// �^�C�g������������[InitRanking]
//=============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	g_nCntTitleRanking = 0;
	g_nCntMoveTex = 0;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE0, &g_pTextureRanking[0]);
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE, &g_pTextureRanking[1]);
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE2, &g_pTextureRanking[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//---�w�i-------------------------
	//���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	  //rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

													//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//---RANKING-------------------------
		//���W�ݒ�
	pVtx[4].pos = D3DXVECTOR3(300.0f, 50.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[5].pos = D3DXVECTOR3(1000.0f, 50.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[6].pos = D3DXVECTOR3(300.0f, 150.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[7].pos = D3DXVECTOR3(1000.0f, 150.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	//rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//�F�ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

	//�e�N�X�`���̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//---����-------------------------
	//���W�ݒ�
	pVtx[8].pos = D3DXVECTOR3(200.0f, 180.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[9].pos = D3DXVECTOR3(400.0f, 180.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[10].pos = D3DXVECTOR3(200.0f, 700.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[11].pos = D3DXVECTOR3(400.0f, 700.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	//rhw�̐ݒ�
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	//�F�ݒ�
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

	//�e�N�X�`���̐ݒ�
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffRanking->Unlock();

	InitRankingScore();
}
//=============================================================================
//�^�C�g���I������ [UninitRanking]
//=============================================================================
void UninitRanking(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{	//�e�N�X�`���̔j��
		if (g_pTextureRanking[nCnt] != NULL)
		{
			g_pTextureRanking[nCnt]->Release();
			g_pTextureRanking[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	UninitRankingScore();
}

//=============================================================================
// �^�C�g���X�V����[UpdataRanking]
//=============================================================================
void UpdateRanking(void)
{
	FADE g_fade;
	g_fade = GetFade();
	g_nCntTitleRanking++;
	g_nCntMoveTex++;
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//Enter���͂Ń^�C�g���߂�
		if (g_fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�ύX
			SetFade(MODE_TITLE);
		}
	}

	if (g_nCntTitleRanking > 600)
	{//���Ԍo�߂Ń^�C�g���ɖ߂�
		if (g_fade != FADE_OUT)
		{
			SetFade(MODE_TITLE);
		}
	}

	UpdateRankingScore();

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffRanking->Unlock();


}
//=============================================================================
// �^�C�g���`�ʏ���[DrawRanking]
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{	
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRanking[nCnt]);

		//�^�C�g���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);
	}
	DrawRankingScore();
}
