//=============================================================================
//
// ���f���̓ǂݍ��ݏ��� [load.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CLoad
{
public:
	typedef enum // cpp�̂�Ɛ��ƕ��т𑵂���
	{
		//--------------------------------------
		// �w�i���f��
		//--------------------------------------
		MODE_WALL_SMALL = 0,// ��������
		MODE_WALL_BIG,		// �傫����
		MODE_GEAR,			// ����
		MODEL_BOX,			// ��
		MODEL_DODAI,		// �y��
		MODE_DUST,			// �S�~
		MODEL_SAMPLE_PLAYER,// �v���C���[(Sample)
		MODEL_PROPELLER,	// �v���y��
		MODEL_DRAWN_X,		// �h���[��X
		MODEL_DRAWN_Z,		// �h���[��Z
		MODEL_BGFROOR,		// ��
		MODEL_SWITCH,		// �X�C�b�`
		MODEL_PODIUM1,		// �\����1
		MODEL_PODIUM2,		// �\����2
		MODEL_PODIUM3,		// �\����3
		MODEL_PAUL,			// �d�C�|�[��
		MODEL_ALPHAMODEL00,	// ���̌����Ȃ�����ver1
		MODEL_ALPHAMODEL01,	// ���̌����Ȃ�����ver2
		MODEL_Seesaw,		// �V�[�\�[
		MODEL_Bench,		// �x���`
		MODEL_House,		// ��
		MODEL_bridge,		// ��(��)
		MODEL_Grren,		// �Ő�
		MODEL_FSymbol,		// ���� �V���{��
		MODEL_FWall,		// ���� �͂�
		MODEL_Wood,			// ��
		MODEL_Snowfall,		// ����
		MODEL_SnowWalldistortion,		// ���
		MODEL_Telephonepole,		// �d��
		MODEL_KANBAN,		// �Ŕ�(���X�X)
		MODEL_GATE,			// �L���
		MODEL_ORI,			// �B
		MODEL_HASUICO,		// �r���a
		MODEL_ICEFLOOR,		// �X��
		MODEL_FLOOR,		// ��O�n�`
		MODEL_ORI2,			// �B2
		MODEL_BUSH,			// ���ނ�
		MODEL_ITA,			// ��
		MODEL_ITA2,			// ��
		MODEL_KUSA,			// ��
		MODEL_ROCK,			// ��
		MODEL_SNOW,			// ��

		MODEL_STAGEFLOOR,		// �e�X�e�[�W�̏�
		MODEL_STAGEFLOOR001,	// �e�X�e�[�W�̏�
		MODEL_STAGEFLOOR002,	// �e�X�e�[�W�̏�

		MODEL_STAGEOUT,			// �e�X�e�[�W����

		MODEL_RANKINGSTADIUM,	//�����L���O�̃X�^�W�A���w�i

		MODEL_SNOWBUSH,			// �ᑐ�ނ�
		MODEL_POLE2,		    // �|�[��
		MODEL_POLE3,		    // �|�[��
		MODEL_SnowMan,		    // �I���t�X�L�[
		//--------------------------------------
		// �������f��
		//--------------------------------------
		MODEL_CAR0,		// ��0
		MODEL_MIC,		// �}�C�N
		MODEL_DESK,		// ��
		MODEL_PULIN,	// �v����
		MODE_KNIFE,		// �i�C�t
		MODE_APPLE,		// �A�b�v��
		MODE_PALLET,	// �G��
		MODE_TAICO,		// �^�C��
		MODE_WHEEL,		// ����
		MODE_COIN,		// �R�C��
		MODE_SUIKA,		// ������
		MODE_TARAI,		// ���炢
		MODE_POT,		// �₩��
		MODE_IKARI,		// ������
		MODE_IKADA,		// ������
		MODEL_SAIHU,	// ���z
		MODEL_KARUTA,	// ���邽
		MODEL_CAMERA,	// �J����
		MODEL_TWIG,		// ������
		MODEL_STRAWBERRY,// �C�`�S
		MODEL_EGG,		// ���܂�
		MODEL_LANCE,	// �����X
		MODEL_KADANN,	// ������
		MODEL_KATANA,	// ��
		MODEL_LOG,	// �܂邽
		MODEL_ICE,		// ���
		MODEL_DANGO,	// ����
		MODEL_MAKURA,	// �܂���
		MODEL_KUNAI,	// ���Ȃ�
		MODEL_FISH,		// ������
		MODEL_VOLCANO,	// ������
		MODEL_NAZCA,	// �Ȃ���
		MODEL_TANK,		// ����
		MODEL_YAGURA,	// �₮��
		MODEL_CHAIR,	// ������
		MODEL_CONGA,	// ����
		MODEL_DICE,		// ������
		MODEL_TREASURECHEST,	// ������
		MODEL_GRASS,	// �K���X
		MODEL_RING,		// �����O
		MODEL_KUSAYA,	// ������
		MODEL_SAZAE,	// �T�U�G
		MODEL_TILE,		// �^�C��
		MODEL_RICE,		// ���C�X
		MODEL_COMIC,	// �}���K
		MODEL_FUIGO,	// �ӂ���
		MODEL_NAMAKO,	// �i�}�R
		MODEL_SEAWEED,	// �R���u
		MODEL_LAITC,	// �炢��
		MODEL_MASK,		// �}�X�N
		MODEL_MEKABU,	// �߂���
		MODEL_MEDIC,	// ������
		MODEL_KAIGA,	// ������
		MODEL_ikura,	// ������
		MODEL_menko,	// �߂�
		MODEL_Mace,		// �߂���
		MODEL_Sarai,	// ���炢
		MODEL_INK,		// �C���N
		MODEL_Zail,		// ������
		MODEL_Inari,	// ���Ȃ�
		MODE_gakuhu,	// �y��
		MODEL_TAITU,	// �^�C�c
		MODEL_FLAG,		// �J�G��
		MODEL_PLUG,		// �v���O
		MODEL_SING,		// �T�C��
		MODEL_TAIMA,	// �喃
		MODEL_SAKURA,	// �T�N��
		MODEL_KAYAKU,	// �Ζ�

		MODEL_IRUI,		// ���邢 : ���ӂ�
		MODEL_KOTATU,	// ������
		MODEL_KUKUI,	// ������
		MODEL_TAKOSU,	// �^�R�X
		MODEL_SARADA,	// �T���_
		MODEL_MENMA,	// �����}
		MODEL_TARAKO,	// ���炱


		MODEL_HUSUMA,	// �ӂ���
		MODEL_TANCE,	// ����
		MODEL_NAMEKO,	// �Ȃ߂�
		MODEL_DOLPHIN,	// ���邩
		MODEL_ICHII,	// ������
		MODEL_KANNA,	// �����
		MODEL_IEI,		// ������
		MODEL_EYE,		// �߂���

		MODEL_SUDATI,	// ������
		MODEL_RINSE,	// ���
		MODEL_LAMP,		// ����
		MODEL_SANGO,	// ����
		MODEL_SUMAI,	// ���܂�
		MODEL_KUKURI,	// ������
		MODEL_CORK,		// ���邭

		MODEL_NAUDA,	// �Ȃӂ�						
		MODEL_SURUME,	// �����
		MODEL_SUZUME,	// ������


		MODEL_TITAN,	// �`�^��
		MODEL_KANAGU,	// �J�i�O
		MODEL_ZARAME,	// �����
		MODEL_ZUKAN,	// �}��
		MODEL_SUBUTA,	// �|��
		MODEL_SUZURI,	// ������
		MODEL_KAIKO,	// �J�C�R
		MODEL_MAX
	} MODEL;

	CLoad();		// �R���X�g���N�^
	~CLoad();    	// �f�X�g���N�^

	static HRESULT LoadModel(void);
	static void UnloadModel(void);

	static LPD3DXMESH GetMesh(int nIdx);
	static LPD3DXBUFFER GetBuffMat(int nIdx);
	static DWORD GetNumMat(int nIdx);
	static void TextureSetting(int nModel);
	static LPDIRECT3DTEXTURE9 *GetTexture(MODEL Model);

	static void LoadFile(char *pFileName);
	static char *ReadLine(FILE *pFile, char *pDst);	//1�s�ǂݍ���
	static char *GetLineTop(char *pStr);			//�s�̐擪���擾
	static int  PopString(char *pStr, char *pDest);	//�s�̍Ō��؂�̂�

private:
	static LPD3DXMESH		*m_pMesh;			// ���b�V�����i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER		*m_pBuffMat;		// �}�e���A�����ւ̃|�C���^
	static DWORD			*m_nNumMat;			// �}�e���A�����̐�
	static char m_apModelName[MODEL_MAX][256];
	static const char *m_apModelFilename[];
	static int m_nCntModel;
	static int m_nMaxModel;

	static LPDIRECT3DTEXTURE9	*m_pTexture[MODEL_MAX];			// �e�N�X�`���ւ̃|�C���^
};

#endif