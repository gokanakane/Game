//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : Gokan akane
//
//=============================================================================
#include "main.h"
#include "PauseQuit.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PAUSE_TEXTUER  "data\\TEXTURE\\Pause\\pause002.png" //�ǂݍ��ރe�N�X�`��
#define PAUSE_POS_X (280 + 150)					    //�|�[�Y�w�i����X
#define PAUSE_POS_Y (280 - 80)					    //�|�[�Y�w�i����Y
#define PAUSE_WIDTH (640 + 150)					    //�|�[�Y�w�i�̕�
#define PAUSE_HEIGHT (640 - 80)					    //�|�[�Y�w�i����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePauseQuit = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseQuit = NULL;
QUITSTATE g_QuitState;

//=============================================================================
// �|���S������������[InitPolygon]
//=============================================================================
void InitPauseQuit(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	g_QuitState = QUITSTATE_NOSELECT;


	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTUER, &g_pTexturePauseQuit);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, 
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D, 
								D3DPOOL_MANAGED,
								&g_pVtxBuffPauseQuit, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseQuit->Lock(0, 0, (void**)&pVtx,0);

		//�w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y + 240.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y + 240.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(280 + 150, 400 + 240.0f - 80, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(640 + 150, 400 + 240.0f - 80, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

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
	g_pVtxBuffPauseQuit->Unlock();

}
//=============================================================================
//�|���S���I������ [UninitPolygon]
//=============================================================================
void UninitPauseQuit(void)
{

	//�e�N�X�`���̔j��
	if (g_pTexturePauseQuit != NULL)
	{
		g_pTexturePauseQuit->Release();
		g_pTexturePauseQuit = NULL;
	}



	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseQuit != NULL)
	{
		g_pVtxBuffPauseQuit->Release();
		g_pVtxBuffPauseQuit = NULL;
	}

}

//=============================================================================
// �|���S���X�V����[UpdataPolygon]
//=============================================================================
void UpdatePauseQuit(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

				   //���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseQuit->Lock(0, 0, (void**)&pVtx, 0);



	switch (g_QuitState)
	{
	case QUITSTATE_SELECT:
		//�w�i�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		break;

	case QUITSTATE_NOSELECT:
		//�w�i�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		break;


	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPauseQuit->Unlock();


}
//=============================================================================
// �|���S���`�ʏ���[DrawPolygon]
//=============================================================================
void DrawPauseQuit(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseQuit, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePauseQuit);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
}
//=============================================================================
// QUIT�ݒ菈��[DrawPolygon]
//=============================================================================
void SetQuit(QUITSTATE state)
{
	g_QuitState = state;
}
