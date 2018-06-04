#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <vector>

namespace MyFile{
	const int ERR_LINE = -1;
}


class clsFILE
{
public:
	clsFILE();
	~clsFILE();

	void Open( const std::string sFileName );
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


private:


	std::string m_sFileName;

	//�񎟌��z��Ƃ��čl���܂�.
	std::vector< std::vector< std::string > > m_vvsData;

	//�����񕪊�( �������̕�����𕪊����ĕԂ� )( �������͋�؂蕶�� ).
	std::vector< std::string > Split( const std::string &sStr, const char cSep ) const;

	bool m_bUsing;//�g�p���Ȃ�true.

};
