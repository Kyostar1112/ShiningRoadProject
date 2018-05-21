#ifndef FILE_H_
#define FILE_H_
#include <iostream>
#include <Shlwapi.h>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include"MyMacro.h"

enum Extension
{
	Txt = 0,	//�e�L�X�g�t�@�C��.
	Csv,		//Csv�t�@�C��.
	x,			//X�t�@�C��.
	png,		//png�t�@�C��.
	Error,		//�G���[.
};
struct FileSet
{
	std::string					sPath;			//�t�@�C���p�X.
	Extension					en_Extension;	//�g���q����p.
	std::vector<std::string>	sDataAry;		//�f�[�^�̔z��.
	int							iLineMax;		//�z��̍ő吔.
};
class clsFile
{
public:
	clsFile();
	~clsFile();

	//�ŏ��ɒʂ���.
	void Init(const char* fileName);

	//�t�@�C����������.
	void Write(char* FilePath_A, char* FilePath);

	//�t�@�C����������.
	void Write(char* FilePath, int NewLine = NULL);

	//�t�@�C����������.
	template<typename T>
	void Write(char* FilePath, std::vector<T> DataAry);

	//�t�@�C���Ǎ�.
	void Read();

	//�t�@�C�����J��.
	void Open(HWND hWnd){
		ShellExecute(hWnd, NULL, m_Data.sPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}

	//�z��̍ő吔.
	int GetDataArrayNumMax(){
		return m_Data.iLineMax;
	}

	//�g���q���ǂꂩ.
	Extension GetExtension(){
		return m_Data.en_Extension;
	}

	//��΃p�X��Ԃ���.
	std::string GetFilePath(){
		return m_Data.sPath;
	}

	//�Q�ƂŕԂ���.
	template<class T>
	void GetDataArray(T* Data, int Array_Num)
	{
		std::stringstream is;
		T tmp;
		is.str(m_Data.sDataAry[Array_Num]);
		is >> tmp;
		*Data = tmp;
		is.clear(std::stringstream::goodbit);
	}

	//�l�n��.
	template<class T>
	std::vector<T> GetDataArray()
	{
		std::stringstream is;
		vector<T> tmp;
		for (size_t i = 0; i < m_Data.sDataAry.size(); i++)
		{
			is.str(m_Data.sDataAry[i]);
			tmp.push_back(is);
			is.clear(std::stringstream::goodbit);
		}
		return Tmp;
	}

	//int�Œl�n��.
	int iGetDataArray(int ArrayNum)
	{
		std::stringstream is;
		int tmp;
		is.str(m_Data.sDataAry[ArrayNum]);
		is >> tmp;
		is.clear(std::stringstream::goodbit);
		return tmp;
	}

private:

	//������u��.
	std::string ReplaceString
		(
		  std::string String1   //�u�������Ώ�.
		, std::string String2   //�u����������e.
		, std::string String3   //�����Ώ�.
		, std::string String4 = "NULL"  //��̌����ΏۂƂ̊Ԃ�����.
		);								//�Ȃ����NULL

	//�w��̕����ŕ��������؂�.
	template <typename List>
	void split(const std::string& s, const std::string& delim, List& result);

	//�f�[�^�̋敪��.
	void FileDataSplit(std::string Data);

	//�g���q���f.
	void ExtensionJudgment();

	//�t�@�C���̃f�[�^.
	FileSet	m_Data;
};

#endif //#ifndef FILE_H_