//=============================================================================
//
// ���U���g���� [result.h]
// Author : �ڍ�������/��Ո�
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"
#include "player.h"
#include "meshField.h"
#include "SelectMenu.h"
//=============================================================================
// �O���錾
//=============================================================================
class CPlayer;
class CNumber;
class CScene2D;
class CCharaBase;
class CSpotLight;
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PLAYER (4)
#define MAX_POINT (2)
#define MAX_MODEL (4)			//�ϋq�Ȃ̐�
#define MAX_AUDIENCE (27)		//�ϋq�S�̂̐�
#define MAX_STADIUMSTEP (3)		//�ϋq�Ȃ̒i��
#define MAX_CURTAIN		(2)		// �J�[�e��
//========================================
// �N���X�̒�`
//========================================
class CResult : public CScene
{
public:

	typedef struct
	{
		int nId;
		int nNumRank;
		int nPoint;
		CPlayer::PLAYER_TYPE type;
		CCharaBase::CHARACTOR_MOVE_TYPE Movetype;
	}CharaSet;

	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshField *GetMeshField(void) { return m_pMeshField; }			// �n�ʂ̎擾
	static void SetRanking(int nNumPlayer, int nId,CPlayer::PLAYER_TYPE type, CCharaBase::CHARACTOR_MOVE_TYPE typeM, int nPoint);
	static void SetCharaSelect(int PlNum, CPlayer::PLAYER_TYPE type) { m_type[PlNum] = type; }
	void TexPoint(int nPlayer, int nPoint);
	static CPlayer *GetPlayer(int nNumPlayer = 0) { return (nNumPlayer < MAX_PLAYER && nNumPlayer >= 0) ? m_pPlayer[nNumPlayer] : m_pPlayer[0]; }		// �v���C���[�̎擾

private:
	/* �|���S���̎�� */
	typedef enum
	{
		RESULTTYPE_WINDOW = 0,	//�E�B���h�E
		RESULTTYPE_CALLOUT_1,	//�����o���F1��
		RESULTTYPE_CALLOUT_2,	//�����o���F2��
		RESULTTYPE_CALLOUT_3,	//�����o���F3��
		RESULTTYPE_CALLOUT_4,	//�����o���F4��
		RESULTTYPE_MAX			//�ő吔
	}STAGESELECTTYPE;

	/* �G�t�F�N�g�̃t�F�[�h */
	typedef enum
	{
		EFFECTPRO_NONE = 0,
		EFFECTPRO_PATTURN1,
		EFFECTPRO_PATTURN2,
		EFFECTPRO_MAX
	}EFFECTPRO_STATE;

	/* 2D�̉��o */
	typedef enum
	{
		PRODUCTION_NONE = 0,
		PRODUCTION_START,				// �J�n
		PRODUCTION_FALL_WINDOW,			// �g�~��
		PRODUCTION_FADERANK,			// ���ʃt�F�[�h�C��
		PRODUCTION_FALL_ICON,			// �A�C�R���~��
		PRODUCTION_TURN_STAND,			// �A�C�R����](�������Ă�)
		PRODUCTION_TURN,				// �A�C�R����]�i��������ԁ��\�j
		PRODUCTION_TURN_TABLE,			// �A�C�R����](�\���S�J��)
		PRODUCTION_TURN_FADEPLNUM,		// �v���C���[�i���o�[�t�F�[�h
		PRODUCTION_COLLOUT_EXPANSION,	// �|�C���g�g��\��
		PRODUCTION_FADEPOINT,			// �|�C���g��\��
		PRODUCTION_FINISH,				// �I��
		PRODUCTION_MAX					// �ő�l
	}PRODUCTION;

	/* �}�X�N�̉��o */
	typedef enum
	{
		MASKPRODUCION_NONE = 0,
		MASKPRODUCION_OPEN,
		MASKPRODUCION_CLOSE,
		MASKPRODUCION_MAX
	}MASKPRODUCION;

	void InitPointer(void);
	void SetPolygon(void);
	void SetModel(void);
	void Set2DUI(int nNum,int nPosNum);
	void RankTex(int nNum, int nRank);
	void PLNumTex(int nNum, int nRank,int nChara, CCharaBase::CHARACTOR_MOVE_TYPE type);
	void SetNumCallout(int nNum, int nIconPos, CCharaBase::CHARACTOR_MOVE_TYPE type);
	void EffectPro(void);
	void SetAudience(void);
	void Production(void);
	void MaskPro(void);

	static CPlayer *m_pPlayer[MAX_PLAYER];
	static CPlayer::PLAYER_TYPE m_type[MAX_PLAYER];
	static CharaSet m_ResultChara[MAX_PLAYER];
	static CMeshField *m_pMeshField;
	static CScene3D *m_apAudience[MAX_AUDIENCE];								//�ϋq
	CScene3D *m_apMask[MAX_CURTAIN];											//�}�X�N
	CSelectMenu *m_pSeletMenu;
	CNumber *m_apNumber[MAX_PLAYER][MAX_POINT];									// �i���o�[�ւ̃|�C���^
	CScene2D *m_apScene2D[RESULTTYPE_MAX];										//���o�n2D�|���S��
	CScene2D *m_apPlayerIcon[MAX_PLAYER];										//�v���C���[�̃A�C�R��
	CScene2D *m_apRanking[MAX_PLAYER];											//����
	CScene2D *m_apPlayerNum[MAX_PLAYER];										//�v���C���[�ԍ�
	CScene2D *m_apEffect[MAX_PLAYER][2];										//�G�t�F�N�g[�v���C���[�l��][�G�t�F�N�g�o����]
	CSceneX *m_apStadium[MAX_MODEL];											//���f���̔z�u
	CSpotLight *m_pSpotLight[MAX_PLAYER];										//�X�|�b�g���C�g
	bool m_bMenu;
	bool m_bMenuCreate;							//���j���[�𐶐��������̃t���O
	bool m_bEffectPro;							//�G�t�F�N�g���o���n�܂��Ă邩�ǂ����t���O
	bool m_bProductin;							//���o�̃t���O
	bool m_bCurtain;
	D3DXVECTOR3 m_RankPos[MAX_PLAYER];			//���ʂ̈ʒu��ۑ�
	D3DXVECTOR3 m_PlayerNumPos[MAX_PLAYER];		//�v���C���[�i���o�[�̈ʒu��ۑ�
	D3DXVECTOR3 m_PlayerIconPos[MAX_PLAYER];	//�A�C�R���̈ʒu��ۑ�
	D3DXVECTOR2 m_RankIconSize[MAX_PLAYER];		//���ʂ̃T�C�Y��ۑ�(X:��,Y:����)
	D3DXVECTOR2 m_PlayerNumSize[MAX_PLAYER];	//�v���C���[�i���o�[�̃T�C�Y��ۑ�(X:��,Y:����)
	D3DXVECTOR2 m_PlayerIconSize[MAX_PLAYER];	//�v���C���[�i���o�[�̃T�C�Y��ۑ�(X:��,Y:����)
	D3DXVECTOR3 m_RankEffect[MAX_PLAYER][2];	//�v���C���[�i���o�[�̈ʒu��ۑ�
	D3DXVECTOR2 m_EffectAlpha;					//�G�t�F�N�g��alpha�l�Ǘ��iX:�G�t�F�N�g�ԍ�0�@Y:�G�t�F�N�g�ԍ�1�j
	EFFECTPRO_STATE m_EffectState;				//�G�t�F�N�g�̏�ԊǗ�
	PRODUCTION m_Production;					//���o
	MASKPRODUCION m_MaskPro;					//�J�[�e���̉��o
	bool		m_bCurtainSound;

	int nCntFadeTime = 0;
};
#endif