//=============================================================================
//
// �J�������� [camera.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

class C3DCharactor;

#define ANGLE_MOVE  (0.03f) //�J�����p�x�̈ړ���
#define CAMERA_POSR_COEFFICIENT (0.40f) 	//�J���������_�̌W��
#define CAMERA_POSV_COEFFICIENT (0.35f)	    //�J�������_�̌W��

#define CAMERA_ROT_COEFFICIENT (0.20f)		//�J�����p�x�̌W��

#define CAMERA_POS_INTERVAL (20.0f)			//�J�����̒����_�̈ʒu


//===================================================================
// �N���X�̒�`
//===================================================================
class CCamera
{
public:
	typedef enum
	{
		TYPE_FPS,		//��l��(PosV�Ǐ]�APosR��])
		TYPE_TPS,		//�O�l��(PosR�Ǐ]�APosV��])
		TYPE_TOPVIEW,	//���J����
		TYPE_SPECTOR,	//���R(�Œ薳��,PosV��Rot��PosR�����܂�)
	}CAMERA_TYPE;

	CCamera();
	~CCamera();

	void Set(CAMERA_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	/*Get*/
	D3DXVECTOR3 GetPosV(void) { return m_posV; };
	D3DXVECTOR3 GetPosR(void) { return m_posR; };
	D3DXVECTOR3 GetRotation(void) { return m_rot; };
	float GetLength(void) { return m_fLength; };
	D3DVIEWPORT9 GetViewPort(void) { return m_ViewPort; };
	CAMERA_TYPE GetType(void) { return m_Type; };
	/*Set*/
	//SPECTOR�p
	void SetPosV(D3DXVECTOR3 posV) { m_posV = posV; };
	void SetPosR(D3DXVECTOR3 posR) { m_posR = posR; };
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; };

	//FPS,TPS�p
	void SetPosVDest(D3DXVECTOR3 posVDest) { m_posVdest = posVDest; };
	void SetPosRDest(D3DXVECTOR3 posRDest) { m_posRdest = posRDest; };
	void SetRotationDest(D3DXVECTOR3 rotDest) { m_rotDest = rotDest; };

	//����
	void SetLength(float fLength) { m_fLength = fLength; };

	void SetViewPort(D3DVIEWPORT9 ViewPort) { m_ViewPort = ViewPort; };
	void SetViewPort(int X, int Y, int Width, int Height, float MinZ = 0.0f, float MaxZ = 1.0f)
	{
		m_ViewPort.X = X;
		m_ViewPort.Y = Y;
		m_ViewPort.Width = Width;
		m_ViewPort.Height = Height;
		m_ViewPort.MinZ = MinZ;
		m_ViewPort.MaxZ = MaxZ;
	};

	void SetLockOnChara(C3DCharactor* pChara) { m_pLockOnChara = pChara; };
	void SetHomingChara(C3DCharactor* pChara) { m_pHomingChara = pChara; };
	void SetCameraAngle(float fAngle) { m_fCameraAngle = fAngle; };

private:
	D3DXVECTOR3 m_posV;		//���_
	D3DXVECTOR3 m_posVdest;	//�ڕW�̎��_
	D3DXVECTOR3 m_posR;		//�����_
	D3DXVECTOR3 m_posRdest; //�ڕW�̒����_
	D3DXVECTOR3 m_vecU;		//������x�N�g��
	D3DXVECTOR3 m_rot;		//�p�x
	D3DXVECTOR3 m_rotDest;	//�ڕW�̊p�x

	float m_fLength;	//PosV����PosR�܂ł̋���

	D3DXMATRIX m_mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X

	D3DVIEWPORT9 m_ViewPort;	//�r���[�|�[�g
	float m_fCameraAngle;		//�J�����p

	CAMERA_TYPE m_Type;			//�J�����̃^�C�v
	C3DCharactor* m_pLockOnChara;	//posR�Ń��b�N�I�����Ă���L�����̃|�C���^(NULL�Ȃ烍�b�N�I�����ĂȂ����)
	C3DCharactor* m_pHomingChara;	//posV�ŒǏ]����L�����̃|�C���^(NULL�Ȃ�Ǐ]�Ȃ�)

	D3DXVECTOR3 m_ORGposV;		//���_
	D3DXVECTOR3 m_ORGposR;		//�����_
	D3DXVECTOR3 m_ORGvecU;		//������x�N�g��
	D3DXVECTOR3 m_ORGrotDest;	//�ڕW�̊p�x

};
#endif // !_CAMERA_H_
