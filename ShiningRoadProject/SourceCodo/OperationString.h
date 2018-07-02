#ifndef OPERATION_STRING_H_
#define OPERATION_STRING_H_

#include <string>
#include <sstream>

//�����񑀍�N���X.
class clsOPERATION_STRING
{
public:
	clsOPERATION_STRING();
	~clsOPERATION_STRING();


	//�����ƘA��.
	//�A�� : consolidated.
	std::string ConsolidatedNumber( const std::string& s, const int				num ) const;
	std::string ConsolidatedNumber( const std::string& s, const unsigned int	num ) const;
	std::string ConsolidatedNumber( const std::string& s, const short			num	) const;
	std::string ConsolidatedNumber( const std::string& s, const unsigned short	num ) const;
	std::string ConsolidatedNumber( const std::string& s, const char			num ) const;
	std::string ConsolidatedNumber( const std::string& s, const unsigned char	num	) const;


	//�}���`�o�C�g������( char* )���烏�C�h�o�C�g������( wchat_t* )���쐬.
	//wchar_t�^�������new���Ă���̂ŁA�g�p��͕K��delete[]���邱��.
	wchar_t* CreateWcharPtrFromCharPtr( const char *c );

	//���C�h�o�C�g������( wchat_t* )����}���`�o�C�g������( char* )���쐬.
	//char�^�������new���Ă���̂ŁA�g�p��͕K��delete[]���邱��.
	char* CreateCharPtrFromWcharPtr( const wchar_t *wc );

private:

	//�����ƘA��.
	//�A�� : consolidated.
	template<class T>
	std::string ConsolidatedNumberProduct( std::string s, const T num ) const
	{
		ostringstream ss;
		ss << static_cast<int>( num );//�����𕶎����( int����Ȃ��Ǝ��̂��N���邳 ).

		s += ss.str();

		return s;
	};

		
};

#endif//#ifndef OPERATION_STRING_H_