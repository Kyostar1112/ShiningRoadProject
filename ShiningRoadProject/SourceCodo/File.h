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

	void Open( std::string sFileName );
	void Close();


	//�����������ƃf�[�^���ׂēn��.
	//�������͉��̃��C��( ���s��?�̎w�� ).
	//�������͂��̍s�̉��ڂ̂��?( �J���}��؂� ).
	std::string GetDataString( 
		const int iRow = MyFile::ERR_LINE, 
		const int iCol = MyFile::ERR_LINE );

	int GetDataInt(
		const int iRow, 
		const int iCol );

	float GetDataFloat(
		const int iRow, 
		const int iCol );

	double GetDataDouble(
		const int iRow, 
		const int iCol );


private:


	std::string m_sFileName;
	std::vector< std::vector< std::string > > m_vvsData;

	//�����񕪊��ǂݍ���( �������͋�؂蕶�� ).
	std::vector< std::string > Split( const std::string &sStr, char cSep );

	bool m_bUsing;//�g�p���Ȃ�true.

};
