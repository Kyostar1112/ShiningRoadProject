#pragma once

#include <string>
#include <vector>

namespace MyFile{
	const int ERR_LINE = -1;
}

//CSV�t�@�C���̓ǂݏ������s���N���X.
class clsFILE
{
public:
	clsFILE();
	~clsFILE();

	//�t�@�C���f�[�^�̌^.
	using FILE_DATA = std::vector< std::vector< std::string > >;

	//----- �ǂݍ��݊֌W -----//.
	//�J���Ȃ�������false���Ԃ�.
	bool Open( const std::string &sFileName );
	void Close();


	//�����������ƃf�[�^���ׂēn��.
	//�������͉��̃��C��( ���s��?�̎w�� ).
	//�������͂��̍s�̉��ڂ̂��?( �J���}��؂� ).
	std::string GetDataString( 
		const int iRow = MyFile::ERR_LINE, 
		const int iCol = MyFile::ERR_LINE ) const;

	int GetDataInt(
		const int iRow, 
		const int iCol ) const;

	float GetDataFloat(
		const int iRow, 
		const int iCol ) const;

	double GetDataDouble(
		const int iRow, 
		const int iCol ) const;


	//���s���邩.
	unsigned int GetSizeRow() const;
	//���̍s�͉��񂠂邩.
	unsigned int GetSizeCol( unsigned int uiRow = 0 ) const;


	//----- �f���o���֌W -----//.
	//CSV�ɓf���o��.
	bool OutPutCsv( const FILE_DATA &data ) const;
	//OutPutCsv�̈����̘g�Â���.
	void CreateFileDataForOutPut( FILE_DATA &Outdata, const int iRow, const int iCol ) const;

private:


	//�t�@�C���ǂݍ��ݎ��Ɏg�p.
	//�����񕪊�( �������̕�����𕪊����ĕԂ� )( �������͋�؂蕶�� ).
	std::vector< std::string > Split( const std::string &sStr, const char cSep ) const;

	//�o�͑O�Ɏg��.
	//�o�͗p������쐬.
	//�A��.Concatenation : �A��
	std::string ConcForOutPut( const FILE_DATA &data ) const;

	//�t�@�C���p�X.
	std::string m_sFileName;

	//�񎟌��z��Ƃ��čl���܂�.
	FILE_DATA m_vvsData;

	bool m_bUsing;//�g�p���Ȃ�true.

};
