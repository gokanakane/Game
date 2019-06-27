//=============================================================================
//
// �^�C������ [Time.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "Game.h"
#include "time.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime[MAX_TIMETEX] = {};		// �e�N�X�`���ւ̃|�C���^
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
	g_Timestate = TIMESTATE_NOMAL;

	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		g_aTimeData[nCnt] = 0;

	}
	AddTime();


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,TEXTURE_TIME,&g_pTextureTime[0]);	
	D3DXCreateTextureFromFile(pDevice,TEXTURE_TIME2,&g_pTextureTime[1]);

	// ���_���̍쐬
	MakeVertexTime(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{

		// �e�N�X�`���̊J��
		if (g_pTextureTime[nCnt] != NULL)
		{
			g_pTextureTime[nCnt]->Release();
			g_pTextureTime[nCnt] = NULL;
		}

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

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_Timestate)
	{
	case TIMESTATE_NOMAL:
		break;

	case TIMESTATE_END:
		g_nTime = g_nTime;
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
			if (g_nTime == 0)
			{
				g_Timestate = TIMESTATE_END;
			}

		}


		for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aTimeData[nCnt] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aTimeData[nCnt] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aTimeData[nCnt] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aTimeData[nCnt] * 0.1f), 1.0f);

			//�Y���̈ʒu�܂Ői�߂�
			pVtx += 4;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTime->Unlock();

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


	for (nCnt = 0; nCnt < MAX_TIME+1; nCnt++)
	{
		if (nCnt < MAX_TIME)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTime[0]);

		}
		else
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTime[1]);

		}
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
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_TIME+1),
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
		pVtx[0].pos = D3DXVECTOR3(1135.0f +(45 * nCnt), 60.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(1185.0f +(45 * nCnt), 60.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(1135.0f +(45 * nCnt), 120.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(1185.0f +(45 * nCnt), 120.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

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
	// ���_����ݒ�	
	pVtx[0].pos = D3DXVECTOR3(1080.0f , 60.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(1130.0f , 60.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(1080.0f , 120.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(1130.0f, 120.0f, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTime->Unlock();

}

//=============================================================================
// �^�C���̉��Z
//=============================================================================
void AddTime(void)
{
	int nCnt;
	int nNum = 1000;
	int nNum1 = 100;
	int nTime;

	nTime = g_nTime / 60;
	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		g_aTimeData[nCnt] = (nTime % nNum) / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}

}

//=============================================================================
// �Q�[���̐ݒ菈��[SetTime]
//=============================================================================
void SetTimeState(TIMESTATE state)
{
	g_Timestate = state;
}
//=============================================================================
// ���Ԃ̎擾
//=============================================================================
int GetTime(void)
{
	return g_nTime;
}
