//=============================================================================
//
// �I�v�V���� [option.h]
// Author : 
//
//=============================================================================
#ifndef _OPTIONBASE_H_
#define _OPTIONBASE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_OPTION_SHIELD "data\\TEXTURE\\Option\\Option000.png"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class COption :public CScene2D
{
public:
	typedef enum
	{
		OPTIONTYPE_NONE = 0,
		OPTIONTYPE_SHIELD,		//�J�[�l���A����
		OPTIONTYPE_ABYSSGATE,	//�r�r�A���ޗ���
		OPTIONTYPE_PUTBULLET,	//�����B�J���g�ݒu�e
		OPTIONTYPE_BEAM,		//�@�؃r�[��
		OPTIONTYPE_MAX
	}OptionType;


	COption();
	~COption();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	static COption *Create(OptionType type, D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void UnLoad(void);

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`���ւ̃|�C���^

};
#endif