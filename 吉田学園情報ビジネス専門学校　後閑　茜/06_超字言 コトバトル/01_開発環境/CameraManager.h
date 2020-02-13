//=============================================================================
//
// �J�����Ǘ����� [CameraManager.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//	�E�J�����𕡐����I�z��ŊǗ����AInit��Uninit,Update,SetCamera���ꊇ�ōs���N���X
//	�ECreateCamera���ĂԂ��ƂŃJ�������쐬����(���łɍ쐬����Ă���Ώ������̍X�V�̂ݍs��)
//	�ETexture�N���X��Command�N���X�Ɠ��l��Tag�ŊǗ������
//
//=============================================================================
#ifndef _CAMERA_MANAGER_H_
#define _CAMERA_MANAGER_H_

#include "main.h"
#include "camera.h"

class C3DCharactor;

//===================================================================
// �N���X�̒�`
//===================================================================
class CCameraManager
{
public:
	enum DRAW_PROPERTY
	{
		PROP_DEFAULT = 0, //�ʏ�ݒ�(��ʏ�����)
		PROP_INIT_ZONLY,  //Z�o�b�t�@�̂ݏ�����(����܂ŕ`�悳�ꂽ���̂̏�ɕ`�悳���)
	};

	struct CAMERA_STATE
	{//�J�������̍\����
		CCamera* pCamera;			//�J�����̃|�C���^
		D3DXCOLOR BackgroundColor;	//����������Ƃ��̔w�i�F
		DRAW_PROPERTY Property;		//�`�掞�̐ݒ�
		LPCSTR CameraTag;			//�J�������ʗp�̃^�O

		bool operator == (const LPCSTR Tag)
		{//�^�O��r(�����Ȃ�true)
			return (strcmp(CameraTag, Tag) == 0);
		}
	};


	CCameraManager();
	~CCameraManager();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);

	//�J�����̃Z�b�g
	bool SetCamera(LPCSTR Tag);

	//�J��������
	bool CreateCamera(LPCSTR Tag, CCamera::CAMERA_TYPE type, D3DXVECTOR3 pos,
		D3DXVECTOR3 rot, float fLength,DRAW_PROPERTY prop = PROP_DEFAULT);

	//�J�����̃r���[�|�[�g�ݒ�
	bool SetCameraViewPort(LPCSTR Tag, int X, int Y, int Width, int Height, float MinZ = 0.0f, float MaxZ = 1.0f);

	//�Ǐ]����Ώۂ̐ݒ�
	bool SetCameraHomingChara(LPCSTR Tag, C3DCharactor* pHomingChara);

	//���b�N�I������Ώۂ̐ݒ�
	bool SetCameraLockOnChara(LPCSTR Tag, C3DCharactor* pLockOnChara);

	//�J�����̉�p�̐ݒ�
	bool SetCameraAngle(LPCSTR Tag,float fAngle);

	//�J�����̒����_�ݒ�
	bool SetCameraPosR(LPCSTR Tag,D3DXVECTOR3 posR,bool bLeap);

	//�J�����̒����ݒ�
	bool SetCameraLength(LPCSTR Tag,float fLength);

	//�w�i�F�ݒ�
	bool SetBackGroundColor(LPCSTR Tag, D3DXCOLOR col);

	//�J�����폜
	bool DeleteCamera(LPCSTR Tag);

	//�J�����擾
	CCamera* GetCamera(LPCSTR Tag);

	float GetLength(LPCSTR Tag);
	//���݃Z�b�g���Ă���J�������擾
	static LPCSTR GetCameraName(void) { return m_SetCamera; };

	int GetCameraNum(void) { return m_vecCameraState.size(); };
private:
	CCamera* CameraSearch(LPCSTR Tag);

	void WindowClear(LPDIRECT3DDEVICE9 pDev,DRAW_PROPERTY prop, D3DXCOLOR BG_Color);

	std::vector<CAMERA_STATE> m_vecCameraState;	//�J�������̓��I�z��

	static LPCSTR m_SetCamera;		//���݃Z�b�g���Ă���J�����̖��O
};


#endif // !_CAMERA_MANAGER_H_
