//=============================================================================
//
// �w�i���� [PauseContinue.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "PauseContinue.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PAUSECONRINUE_TEXTUER  "data\\TEXTURE\\Continue.png" //�ǂݍ��ރe�N�X�`��
#define PAUSE_POS_X (280 + 150)					    //�|�[�Y�w�i����X
#define PAUSE_POS_Y (280 - 80)					    //�|�[�Y�w�i����Y
#define PAUSE_WIDTH (640 + 150)					    //�|�[�Y�w�i�̕�
#define PAUSE_HEIGHT (640 - 80)					    //�|�[�Y�w�i����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePauseContinue = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseContinue = NULL;
CONTINUSTATE g_ContinueState;

//=============================================================================
// �|���S������������[InitPolygon]
//=============================================================================
void InitPauseContinue(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^
	
	g_ContinueState = CONTINUSTATE_SELECT;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PAUSECONRINUE_TEXTUER, &g_pTexturePauseContinue);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseContinue, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseContinue->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i�̍��W�ݒ�
	//�R���e�j���[���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y , 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y , 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(280 + 150, 400 - 80, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(640 + 150, 400 - 80, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

	//�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPauseContinue->Unlock();

}
//=============================================================================
//�|���S���I������ [UninitPolygon]
//=============================================================================
void UninitPauseContinue(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePauseContinue != NULL)
	{
		g_pTexturePauseContinue->Release();
		g_pTexturePauseContinue = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseContinue != NULL)
	{
		g_pVtxBuffPauseContinue->Release();
		g_pVtxBuffPauseContinue = NULL;
	}

}

//=============================================================================
// �|���S���X�V����[UpdataPolygon]
//=============================================================================
void UpdatePauseContinue(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseContinue->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_ContinueState)
	{
	case CONTINUSTATE_SELECT:
		//�w�i�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		break;

	case CONTINUSTATE_NOSELECT:
		//�w�i�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		break;


	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPauseContinue->Unlock();


}
//=============================================================================
// �|���S���`�ʏ���[DrawPolygon]
//=============================================================================
void DrawPauseContinue(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseContinue, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseContinue);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

}
//=============================================================================
// QUIT�ݒ菈��[DrawPolygon]
//=============================================================================
void SetContinu(CONTINUSTATE state)
{
	g_ContinueState = state;
}
