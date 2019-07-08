//=============================================================================
//
// ���C������ [main.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"					 //�`�揈���ɕK�v�i�ꗗ�j
#define  DIRECTINPUT_VERSION (0x0800)//�r���h�x���Ώ��p
#include "dinput.h"					 //���͏����ɕK�v
#include "xaudio2.h"				 //�T�E���h�����ŕK�v

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")  //�`�揈���ɕK�v�i�o�C�i���j
#pragma comment(lib,"d3dx9.lib") //[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")//DirectX�R���|�[�l���g�i���i�j�̎g�p�ɕK�v
#pragma comment(lib,"winmm.lib")//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)		// �E�C���h�E�̍���
#define FVF_VERTEX_2D ( D3DFVF_XYZRHW| D3DFVF_DIFFUSE|D3DFVF_TEX1) //���_�t�H�[�}�b�g�E�e�N�X�`�����W

#define CLASS_NAME		"WindowClass"		// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME		"�C�����s�I���m��A��I�̊�"	// �E�C���h�E�̖��O(�L���v�V������)
#define MAX_VERTEX_DATA (4)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{//�񋓌^
	MODE_TITLE = 0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_RESULT,
	MODE_RANKING,
	MODE_MAX
}MODE;

typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;		//1.0f�ŌŒ�
	D3DCOLOR col;	//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W

}VERTEX_2D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif