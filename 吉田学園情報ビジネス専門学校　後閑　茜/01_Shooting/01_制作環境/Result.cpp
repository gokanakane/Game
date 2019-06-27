//=============================================================================
//
// ���U���g���� [Result.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "Result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_RESULTTEX] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;

//=============================================================================
// ���U���g����������[InitPolygon]
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	GAMESTATE pGame;
	pGame = GetGameState();

	if (pGame == GAMESTATE_CLEAR)
	{//�Q�[���N���A��������
		//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, RESULT_TEXTUER, &g_pTextureResult[0]);
		D3DXCreateTextureFromFile(pDevice, RESULT_TEXTUER1, &g_pTextureResult[1]);
		
	}
	else if (pGame == GAMESTATE_OVER)
	{
		//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, RESULT_OVER, &g_pTextureResult[0]);
		D3DXCreateTextureFromFile(pDevice, RESULT_TEXTUER2, &g_pTextureResult[1]);

	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RESULTTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���U���g�w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	 //rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���U���g�w�i�F�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j

	//���U���g�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//-----------���U���g����------------
	//���U���g�̍��W�ݒ�
	pVtx[4].pos = D3DXVECTOR3(90, 90, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[5].pos = D3DXVECTOR3(1100, 90, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[6].pos = D3DXVECTOR3(90, 500, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[7].pos = D3DXVECTOR3(1100, 500, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	 //rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//���U���g�F�ݒ�
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);//�O�ڂ̒��_�̐F�w��i�E���j

	//���U���g�e�N�X�`���̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffResult->Unlock();

}
//=============================================================================
//���U���g�I������ [UninitPolygon]
//=============================================================================
void UninitResult(void)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_RESULTTEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureResult[nCnt] != NULL)
		{
			g_pTextureResult[nCnt]->Release();
			g_pTextureResult[nCnt] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

}

//=============================================================================
// ���U���g�X�V����[UpdataPolygon]
//=============================================================================
void UpdateResult(void)
{
	FADE g_fade;
	g_fade = GetFade();

	//Enter�L�[�������ꂽ
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);

		if (g_fade != FADE_OUT)
		{
			//���[�h�ݒ�
			SetFade(MODE_TITLE);
		}
	}
}
//=============================================================================
// ���U���g�`�ʏ���[DrawPolygon]
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;
	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (nCnt = 0; nCnt < MAX_RESULTTEX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[nCnt]);

		//���U���g�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt*4,
			2);

	}

}