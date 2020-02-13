//=============================================================================
//
// �e�N�X�`���N���X [texture.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v:
//	�E�O���t�@�C���ɏ����ꂽ����ێ����A�K�v�Ȏ���
//	�@�ǂݍ��񂾏������Ƀe�N�X�`���𐶐�����
//	�E��x�ǂݍ��񂾂��͕̂ێ����Ă����A�ēx�K�v�ɂȂ�������
//	  ���ɂ���e�N�X�`�������̂܂ܓn��
//	�E�e�N�X�`���͊O���t�@�C���ŕύX�ł���ID�ƃ^�O�ŊǗ�����A
//	�@�g�p�҂�ID�������̓^�O�������ɓ���邱�ƂŕK�v�ȃe�N�X�`�����擾����
//	�Enew/delete�Ɣh�����֎~���邽�߁A�R���X�g���N�^�ƃf�X�g���N�^��private�����A
//	�@�N���X��`�̖�����final��t����(�����Ȃ�����!!)
//
//	��::�g�p����Ƃ���main.h��<stdio.h>�ƌx�������������邱��!!
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

class CTexture final	//final = �p�����֎~����\��
{
public:
	//�e�N�X�`���f�[�^�̍\����
	struct TexData
	{
		int	 nID;							//ID
		char TexAddress[256];				//�e�N�X�`���̃A�h���X
		char TexNameTag[256];				//�e�N�X�`���̗���
		LPDIRECT3DTEXTURE9 pTexture;		//�e�N�X�`���̃|�C���^


		//std::find�Ō�������Ƃ��Ɏg����r�֐�
		bool operator == (const int ID)
		{//ID�Ŕ�r
			return (nID == ID);
		}
		bool operator == (const LPCSTR Tag)
		{//�^�O�Ŕ�r
			return (strcmp(TexNameTag, Tag) == 0);
		}
	};


	//�ǂݍ���&�폜
	static HRESULT Load(void);
	static void Unload(void);

	//�e�N�X�`���擾
	static LPDIRECT3DTEXTURE9 GetTexture(const int nID);
	static LPDIRECT3DTEXTURE9 GetTexture(const LPCSTR Tag);

	//����Ă���e�N�X�`����S�J��
	static void ReleaseAll(void);
	//�g��Ȃ��Ȃ����e�N�X�`���̉��
	static void Release(const int nID);
	static void Release(const LPCSTR Tag);

	//�e�N�X�`����
	static int GetTexNum(bool bCreate);
private:

	//�R���X�g���N�^&�f�X�g���N�^ (new/delete���֎~���邽�߂�private�ɓ����)
	CTexture() {};
	~CTexture() {};

	//�����ł̃e�N�X�`�������֐�
	static void Create(LPCSTR address, LPDIRECT3DTEXTURE9 &pTexture);

	//�ϐ�
	static std::vector<TexData> m_TexData;	//�e�N�X�`���f�[�^�̔z��
};

#endif // !_TEXTURE_H_
