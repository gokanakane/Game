//=============================================================================
//
// �L�����Z���N�g�̏��� [CharaSelect.h]
// Author : �ڍ�������/��Ո�
//
//=============================================================================
#ifndef _CHARASELECT_H_
#define _CHARASELECT_H_

#include "scene.h"
#include "PlayerNumSelect.h"
#include "player.h"

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CPlayer;
class CFade;
class CManager;
class CCharaSelCursol;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER				(4)
#define MAX_CHARASELECT			(5)
#define MAX_CHARASELTEX			(16)

class CCharaSelect
{
public:
	CCharaSelect();
	~CCharaSelect();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCharaSelect *Create(void);

	/* �I�΂�Ă邩�̏�� */
	typedef enum
	{
		SELECTSTATE_NONE = 0,
		SELECTSTATE_FLASH,
		SELECTSTATE_SELECT,
		SELECTSTATE_NOSELECT
	}SELECT_STATE;

	bool GetCardPro(void) { return m_bCharaCard; }															//�J�[�h�̉��o�̃t���O
	bool GetConf(void) { return m_bConf; }																	//�m��̃t���O
	bool collision(int operation, CPlayer::PLAYER_TYPE type);												//�����蔻��
	void SelectProduction(int nNum, SELECT_STATE &Sel, SELECT_STATE &Selold, CPlayer::PLAYER_TYPE type);	//���o����
	void CharaSelTex(int nNum, SELECT_STATE Sel, CPlayer::PLAYER_TYPE &type);								//�e�N�X�`�����W�Ǘ�
	void DecisionCharactor(CFade *pFade, CManager *pManager, int operation);								//�J�ڑO�̐ݒ�
	bool collisionBackMode(int operation);																	//���[�h�߃|���S���Ƃ����蔻��
	void SetBackModeTex(void);																				//�߂�|���S���̍��W�ݒ�
	void SetPlayerWindowChara(int operation, CPlayer::PLAYER_TYPE type);									//�J�[�\�����������Ă���ꏊ�ŃE�B���h�E�ɃL�������o��
	void SetWindowCharaDraw(int nNum, bool bDraw);
	void SetBackMode(int nId,bool bBack) { m_bBackModeColl[nId] = bBack; }												//�߂郂�[�h�̐ݒ�
	bool GetBackMode(int nId) { return m_bBackModeColl[nId]; }
private:
	/* �|���S���̎�� */
	typedef enum
	{
		CHARASEL_POLYGONTYPE_BG = 0,		//�w�i
		CHARASEL_POLYGONTYPE_BAND_L,		//�сF��
		CHARASEL_POLYGONTYPE_BAND_R,		//�сF�E
		CHARASEL_POLYGONTYPE_BACKMODE,		//�߂�
		CHARASEL_POLYGONTYPE_MASK1,			//�}�X�NPL_1
		CHARASEL_POLYGONTYPE_MASK2,			//�}�X�NPL_2
		CHARASEL_POLYGONTYPE_MASK3,			//�}�X�NPL_3
		CHARASEL_POLYGONTYPE_MASK4,			//�}�X�NPL_4
		CHARASEL_POLYGONTYPE_PLUI_CHARA1,	//�I���L�������e�v���C���[�̃E�B���h�E�ɕ\��:PL_1
		CHARASEL_POLYGONTYPE_PLUI_CHARA2,	//�I���L�������e�v���C���[�̃E�B���h�E�ɕ\��:PL_2
		CHARASEL_POLYGONTYPE_PLUI_CHARA3,	//�I���L�������e�v���C���[�̃E�B���h�E�ɕ\��:PL_3
		CHARASEL_POLYGONTYPE_PLUI_CHARA4,	//�I���L�������e�v���C���[�̃E�B���h�E�ɕ\��:PL_4
		CHARASEL_POLYGONTYPE_MAX			//�ő吔

	}CHARASEL_POLYGONTYPE;
	/* �m��̉��o */
	typedef enum
	{
		CONFPRODUCTION_NONE = 0,	//�������Ȃ�
		CONFPRODUCTION_MOVE_START,	//�ړ��J�n
		CONFPRODUCTION_MOVE,		//�ړ�
		CONFPRODUCTION_MOVE_END,	//�ړ��I��
		CONFPRODUCTION_MAX

	}CONFPRODUCTION_STATE;

	/* �L�����I���J�[�h���o���� */
	typedef enum
	{
		CHARACARDPRO_NONE = 0,		//�������ĂȂ�
		CHARACARDPRO_START,			//�J�n
		CHARACARDPRO_MOVE,			//�ړ�
		CHARACARDPRO_TURNOVER_B,	//�Ђ�����Ԃ�(����-���\)
		CHARACARDPRO_FACEUP,		//�\�ʂɂȂ�
		CHARACARDPRO_FINISH,		//�I��
		CHARACARDPRO_MAX

	}CHARACARDPRO_STATE;

	void Initpointer(void);											//�|�C���^�̏�����
	void ScrollMenu(CHARASEL_POLYGONTYPE type, float fScroolSpeed);	//�e�N�X�`���X�N���[������
	void InitCharaSelectPoly(void);									//�|�C���^�̏�����
	bool ConfirmationSelect(void);									//�v���C���[���S���I���������m�F����
	bool collisionConf(int operation);								//�m��|���Ƃ����蔻��
	bool ProductionConf(void);										//�m��|���̉��o
	void FlashConf(void);											//�m��|���̓_��
	void ProductionCard(void);										//�L�����I���J�[�h���o����

	static CScene2D *m_apScene2D[MAX_CHARASELTEX];					//�w�i�n�̃|�C���^
	static CScene2D *m_apSelect2D[MAX_CHARASELECT];					//�I����
	static CScene2D *m_apConfirm2D;									//�m��
	static CCharaSelCursol *m_apCursol[MAX_PLAYER];					//�J�[�\��
	CPlayer::PLAYER_TYPE m_CharaType[MAX_PLAYER];					//�I�΂ꂽ�L�����̎��
	static bool m_bBackModeColl[MAX_PLAYER];									//�߂�|���S���Ɠ������Ă邩�̃t���O

	/* ���o�n�ϐ� */
	int m_nCntScrool, m_CntFlash, m_CntFadeF;						//�X�N���[���̃J�E���^�[/�m�莞�̃t���b�V��/�J�ڂ܂ł̕b���J�E���^�[
	float m_fFlashAlpha[MAX_PLAYER];								//���o�̓����l�Ǘ�
	bool m_bConfProFinish, m_bConfProStart,m_bConf;					//���o���I�������
	static bool m_bCharaCard;										//�J�[�h���o�̃t���O
	bool m_bCnfFlash;												//�m�F�|���̃t���V���J�n
	float m_moveConfPro;											//�m��|���̈ړ�
	CPlayerSelect::SELECTPLAYER *m_PlayerNum;						//�v���C���[�̐l��
	CONFPRODUCTION_STATE m_CnfProState;								//�m��̉��o���
	CHARACARDPRO_STATE m_CharaCardProduction;						//�L�����I���J�[�h�̉��o�̏��
	D3DXVECTOR3 m_CharaCardPro_FinishPos[MAX_CHARASELECT];			//�I���J�[�h�̍ŏI�ʒu
	float m_fCardWidth[MAX_CHARASELECT][2];							//�J�[�h�̕�
	float m_fCharaCardPro_FinishWH[2];								//�I���J�[�h�̍ŏI���ƍ���
	float m_fGaugeSizeX[MAX_PLAYER];								//�߂�Q�[�W�̒�����ۊ�
	float m_fMaxGaugeX[MAX_PLAYER];									//�Q�[�W�̍ő�̒���
	int m_nCounter;

#ifdef _DEBUG
	int nCntFadeTime = 0;
#endif

};
#endif