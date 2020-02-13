//=============================================================================
//
// �^�C�g������ [title.h]
// Author : �ڍ� ������/Akane Gokan
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"
#include<time.h>

//�O���錾
class CScene2D;

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_TITLEPOLYGON (10)											// �g�p����|���S���̍ő吔
#define BG_HUMAN_SIZE_W (230.0f)										// �w�i(�l��)�̉����傫��
#define COL_DEFAULT (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))					// �F:�f�t�H���g
#define COL_DEFAULT_TRANSPARENT (D3DXCOLOR(1.0f,1.0f,1.0f,0.0f))		// �F:����
#define COL_PRODUCTION_HUMAN (D3DXCOLOR(1.0f,1.0f,1.0f,0.8f))			// �w�i(�l��)�̕ύX��̐F
#define POS_DEFOLT (D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))	// ��ʂ̒��S���W
#define TITLEROGO_CORRECTION (28.0f)									// �^�C�g�����S�̔������l

//�N���X�i�V�[��2D�̔h���N���X�j
class CTitle
{
public:
	CTitle();
	~CTitle();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void InitpScene2D(void);		//�|�C���^�̏���������
	void UninitpScene2D(void);		//�|�C���^�̏I������
	void SetScene2D(void);			//2D�|���S���̏����ݒ�
	void Production(void);			//���o
	bool MoveBGCharactor(int Num);	//�w�i�ړ�����
	void HumanProductionPos(void);	//�X�L�b�v�������̈ʒu�ύX����
	void Flash(void);				//�t���b�V��
	void SparkProduction(void);		//�X�p�[�N�̉��o
	void PressProduction(void);		//�v���X�{�^���̉��o����
	bool TitleScaling(int Num);		//�^�C�g�����o
	static CTitle *Create(void);

private:
	//�|���S���̎��
	typedef enum
	{
		POLYGONTYPE_BALANCEBOY = 0,	//�o�����X�j�q
		POLYGONTYPE_REACHGIRL,		//���[�`���q
		POLYGONTYPE_POWORBOY,		//�p���[�j�q
		POLYGONTYPE_SPEEDGIRL,		//�X�s�[�h���q
		POLYGONTYPE_KOTOMON,		//�R�g����
		POLYGONTYPE_SPARK,			//�Ή�
		POLYGONTYPE_ROGO_MAIN,		//�^�C�g�����S�F���C��
		POLYGONTYPE_ROGO_SUB,		//�^�C�g�����S�F�T�u
		POLYGONTYPE_FLASH,			//�t���b�V��
		POLYGONTYPE_PRESSBUTTON		//�v���X�{�^��
	}POLYGON_TYPE;

	// ���o�̏��
	typedef enum
	{
		PRODUCTIONSTATE_NONE = 0,
		PRODUCTIONSTATE_START,		// ���o�̊J�n
		PRODUCTIONSTATE_MOVE_B,		//�o�����X�j�q�ړ�
		PRODUCTIONSTATE_MOVE_R,		//���[�`���q�ړ�
		PRODUCTIONSTATE_MOVE_P,		//�p���[�j�q�ړ�
		PRODUCTIONSTATE_MOVE_S,		//�X�s�[�h���q�ړ�
		PRODUCTIONSTATE_FLASH,		//�t���b�V���̊J�n
		PRODUCTIONSTATE_TITLE_SUB,	//�T�u�^�C�g���̉��o
		PRODUCTIONSTATE_TITLE_MAIN,	//���C���^�C�g���̉��o
		PRODUCTIONSTATE_FINISH		// �S�Ẳ��o���I��

	}PRODUCTIONSTATE;

	//�t���b�V���̏��
	typedef enum
	{
		FLASHSTATE_NONE = 0,
		FLASHSTATE_START,	// �t���b�V���̊J�n
		FLASHSTATE_FADEOUT,	//�t���b�V���̃t�F�[�h�A�E�g
		FLASHSTATE_FINISH	// �t���b�V���̏I��

	}FLASHSTATE;

	CScene2D* m_pScene2D[MAX_TITLEPOLYGON];	//�V�[��2D�̃|�C���^
	/* ���o�S�̕ϐ� */
	PRODUCTIONSTATE m_ProductionState;		//���o�̏��
	FLASHSTATE m_FlashSate;					//�t���b�V���̏��
	bool m_bProductionSkip,m_FlashSkip;		//���o�X�L�b�v���ꂽ��/�t���b�V���X�L�b�v�������ۂ�

	/* �t���b�V���ϐ� */
	int m_nCntFadeTime;						//�t���b�V���̃t�F�[�h����
	float m_fCntFade,m_fAlpha;				//�t���b�V���̃J�E���^�[/�t���b�V����alpha�l

	/* �Ήԕϐ� */
	float m_fChangeSparkMove;				//�ΉԂ̈ړ�����J�E���^�[
	float m_fSparkX;						//�ΉԂ̈ړ��ʂ��v��

	/* �v���X�{�^���ϐ� */
	int m_nCntFlashPress;					//�_�Ŏ��Ԃ��Ǘ�����J�E���^�[
	float m_fPressAlpha;					//�_�ł�alpha�l
	bool m_bPressMode;						//�v���X�̏�ԊǗ�

	/* �^�C�g�����S�ϐ� */
	float m_fTitleScal;						//�g�k�̃T�C�Y

	//�^�C�g���R�[��
	bool m_bTitleCall;						//�^�C�g���R�[���t���O
	bool m_bSubTitleCall;
	int  m_nTitleCallCnt;					//�R�[���̃^�C�~���O

#ifdef _DEBUG
	int nCntFadeTime = 0;
#endif
};
#endif