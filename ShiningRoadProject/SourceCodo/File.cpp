#include "File.h"

//文字列を数値にしようとしないかのチェックで使う.
#include <cctype>
#include <algorithm>

#include <sstream>
#include <fstream>
#include <iostream>
#include <assert.h>

using namespace std;

const unsigned int uiRESERVE_SIZE_ROW = 64;//ベクターの初期最大サイズ( 行 ).
const unsigned int uiRESERVE_SIZE_COL = 16;//ベクターの初期最大サイズ( 行のカンマ区切りの数 ).

const char cDELIMITER = ',';//区切り文字.
	
const string sERROR = "THIS_IS_ERROR";//エラー用文字列.

//初期化用データ作成( プッシュバック用 ).
const vector<string> vsINIT_LINE;


clsFILE::clsFILE() :
	m_bUsing( false )
{
}

clsFILE::~clsFILE()
{
	Close();
}


void clsFILE::Open( const string sFileName )
{
	assert( !m_bUsing );//使用中にopenするな.

	m_sFileName = sFileName;

	//メモリ確保.
	m_vvsData.reserve( uiRESERVE_SIZE_ROW );

	//ファイルを開く.
	ifstream ifs( m_sFileName );
	{
		//openチェック.
		if( !ifs ){
			cout << "ひらけなかったよ" << endl;
			cin.get();
			return;
		}

		string sBuff;//仮のデータ.
		unsigned int uiIndexRow = 0;//何行目かを表す変数( index ).
		//一行づつファイルすべてを読み込む.
		while( true )
		{
			//ファイルの終端まで来たら終了.
			if( ifs.eof() ){
				break;
			}
			
			m_vvsData.push_back( vsINIT_LINE );					//一行増やす.
			m_vvsData[uiIndexRow].reserve( uiRESERVE_SIZE_COL );//メモリ確保.
			
			getline( ifs, sBuff );					//仮のデータに一行を突っ込む.
			m_vvsData[uiIndexRow].push_back( "" );	//本データにさっき作った仮データを突っ込む猶予を作る.
			m_vvsData[uiIndexRow][0] = sBuff;		//突っ込む.
			m_vvsData[uiIndexRow] = Split( m_vvsData[uiIndexRow][0], cDELIMITER );//一行として突っ込んだデータを区切り文字を基準に分解する.

			//余分なメモリをポイする.
			m_vvsData[uiIndexRow].shrink_to_fit();

			uiIndexRow ++;
		}
	}

	//余分なメモリをポイする.
	m_vvsData.shrink_to_fit();

	m_bUsing = true;
}


void clsFILE::Close()
{
	for( unsigned int i=0; i<m_vvsData.size(); i++ ){
		m_vvsData[i].clear();
		m_vvsData[i].shrink_to_fit();
	}
	m_vvsData.clear();
	m_vvsData.shrink_to_fit();

	m_bUsing = false;
}



string clsFILE::GetDataString( const int iRow, const int iCol ) const
{
	if( !m_bUsing ){
		assert( m_bUsing );//使用中じゃなければアサート.
		return sERROR;
	}
	//範囲内?.
	if( iRow >= static_cast<int>( m_vvsData.size() ) ){
		return sERROR;
	}
	for( unsigned int i=0; i<m_vvsData.size(); i++ ){
		if( iCol >= static_cast<int>( m_vvsData[i].size() ) ){
			return sERROR;
		}
	}
	//マイナスははじく( かつエラー値ではない ).
	if( iRow < 0 && iRow != MyFile::ERR_LINE ){	
		return sERROR;
	}
	if( iCol < 0 && iCol != MyFile::ERR_LINE ){	
		return sERROR;
	}

	//全文を返す.
	if( iRow == MyFile::ERR_LINE ){
		string sData;
		//全文連結.
		for( unsigned int i=0; i<m_vvsData.size(); i++ ){
			for( unsigned int j=0; j<m_vvsData[i].size(); j++ ){
				sData += m_vvsData[i][j];
			}
		}
		return sData;
	}

	//指定行を返す.
	if( iCol == MyFile::ERR_LINE ){
		string sData;
		//一行連結.
		for( unsigned int i=0; i<m_vvsData[iRow].size(); i++ ){
			sData += m_vvsData[iRow][i];
		}
		return sData;
	}

	//指定部分を返す.
	return m_vvsData[iRow][iCol];
}

int clsFILE::GetDataInt(
	const int iRow, 
	const int iCol ) const
{
	string sBuff = GetDataString( iRow, iCol );//文字列取得.	

	//「すべてが数字」ではない || エラーならば.
	if( !all_of( sBuff.cbegin(), sBuff.cend(), isdigit ) ||
		sBuff == sERROR )
	{
		//エラーを返す.
		return MyFile::ERR_LINE;
	}

	int iNum = stoi( sBuff );	//文字列を数字にする.
	return iNum;
}

float clsFILE::GetDataFloat(
	const int iRow, 
	const int iCol ) const
{
	string sBuff = GetDataString( iRow, iCol );//文字列取得.	

	//「すべてが数字」ではない || エラーならば.
	if( !all_of( sBuff.cbegin(), sBuff.cend(), isdigit ) ||
		sBuff == sERROR )
	{
		//エラーを返す.
		return static_cast<float>( MyFile::ERR_LINE );
	}

	float fNum = stof( sBuff );	//文字列を数字にする.
	return fNum;
}

double clsFILE::GetDataDouble(
	const int iRow, 
	const int iCol ) const
{
	string sBuff = GetDataString( iRow, iCol );//文字列取得.	

	//「すべてが数字」ではない || エラーならば.
	if( !all_of( sBuff.cbegin(), sBuff.cend(), isdigit ) ||
		sBuff == sERROR )
	{
		//エラーを返す.
		return static_cast<double>( MyFile::ERR_LINE );
	}

	double dNum = stod( sBuff );	//文字列を数字にする.
	return dNum;
}


//何行あるか.
unsigned int clsFILE::GetSizeRow()
{
	return m_vvsData.size();
}

//その行は何列あるか.
unsigned int clsFILE::GetSizeCol( unsigned int uiRow )
{
	//範囲外は許さない.
	if( uiRow >= m_vvsData.size() ) return 0;
	return m_vvsData[uiRow].size();
}


//文字列分割( 第一引数の文字列を分割して返す )( 第二引数は区切り文字 ).
vector< string > clsFILE::Split( const std::string &sStr, const char cSep ) const
{
	vector< string > vsOut;
	stringstream ss( sStr );
	string sBuff;

	//多めにメモリを取っておく.
	vsOut.reserve( uiRESERVE_SIZE_COL );

	//引数にした文字を区切りとして分割する.
	while( std::getline( ss, sBuff, cSep ) ){
		vsOut.push_back( sBuff );
	}

	//余分なメモリをポイする.
	vsOut.shrink_to_fit();

	return vsOut;
}

