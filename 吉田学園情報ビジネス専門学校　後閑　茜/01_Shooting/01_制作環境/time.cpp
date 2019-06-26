//=============================================================================
//
// �X�R�A���� [Time.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "time.h"
#include "Game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIME "data\\TEXTURE\\UI\\number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_TIME (2)
#define TIME_RIMIT (60*30)									//��������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int g_nTime;										// ��������
int g_aTimeData[MAX_TIME];
TIMESTATE g_Timestate = TIMESTATE_NONE;				//�^�C���̏��

//=============================================================================
// ����������
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// �������Ԃ̏�����
	g_nTime = TIME_RIMIT;
	AddTime();
	g_Timestate = TIMESTATE_NOMAL;

	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		g_aTimeData[nCnt] = 0;

	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TIME,		// �t�@�C���̖��O
								&g_pTextureTime);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexTime(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTime(void)
{
	int nCnt;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	switch (g_Timestate)
	{
	case TIMESTATE_NOMAL:
		break;

	case TIMESTATE_END:
		g_nTime = 0;
		g_Timestate = TIMESTATE_NONE;
		SetGameState(GAMESTATE_OVER);
		break;
	}

	if (g_Timestate == TIMESTATE_NOMAL)
	{
		g_nTime--;

		if ((g_nTime % 60) == 0)
		{
			AddTime();

			//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

			for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aTimeData[nCnt] * 0.1f), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aTimeData[nCnt] * 0.1f), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aTimeData[nCnt] * 0.1f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aTimeData[nCnt] * 0.1f), 1.0f);

				//�Y���̈ʒu�܂Ői�߂�
				pVtx += 4;
			}
			//���_�o�b�t�@�̃A�����b�N
			g_pVtxBuffTime->Unlock();
			if (g_nTime == 0)
			{
				g_Timestate = TIMESTATE_END;
			}

		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt * 4,
			2);

	}

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	int nCnt;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{		
		// ���_����ݒ�	
		pVtx[0].pos = D3DXVECTOR3(590.0f +(40 * nCnt), 5.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(640.0f +(40 * nCnt), 5.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(590.0f +(40 * nCnt), 75.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(640.0f +(40 * nCnt), 75.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�F
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTime->Unlock();

}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddTime(void)
{
	int nCnt;
	int nNum = 100;
	int nNum1 = 10;
	int nTime;

	nTime = g_nTime/60 ;

	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		g_aTimeData[nCnt] = (nTime % nNum) / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}
