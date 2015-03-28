//atd.string.cpp
#include "atd.h"
using namespace atd;
//====================================================
//= struct atd::string
//====================================================
string::string()										: std::string() { }
string::string(const char *that)						: std::string(that) { }
string::string(const std::string &that)					: std::string(that) { }
string::string(int size, char fill)						: std::string(size, fill) { }
string::string(iterator begin, iterator end)			: std::string(begin, end) { }
string::string(const_iterator begin, const_iterator end): std::string(begin, end) { }

string string::format(const char *format, ...)
{
	va_list va;

	//必要バイト数取得
	va_start(va, format);
	string s(::vsnprintf(0, 0, format, va) + 1, 0);
	va_end(va);

	//★vsnprintf()内でva_arg()が呼ばれるので毎回vaをリセットする必要がある
	va_start(va, format);
	::vsnprintf(&s[0], s.size(), format, va);
	va_end(va);

	return s.c_str();
}
string string::enclose(const string &s, const string &left, const string &right)
{
	return left + s + (right.length() ? right : left);
}
strings string::explode(const string &s, const string &delimiter)
{
	strings ss;

	//デリミタが空の場合は対象文字列をそのまま（配列の唯一の要素にして）返す
	if (!delimiter.length())
	{
		return ss.entry(s);
	}

	size_t offset = 0, pos = npos, dlen = delimiter.length();
	const_iterator b = s.begin(), e = s.end();
	while (true)
	{
		//デリミタを検索
		pos = s.find(delimiter, offset);
		
		//見つからなかった残りの文字列を全部登録してループを抜ける
		if (pos == npos)
		{
			ss.push_back(string(b + offset, e));
			break;
		}
		//見つかった位置の直前までの文字列を切り取って配列に登録する
		string s = string(b + offset, b + pos);
		ss.push_back(s);

		//オフセットを進める
		offset = pos;
		offset += dlen;
	}

	//配列を返す
	return ss;
}
//====================================================
//= 型変換
//====================================================
int string::toint(int base) const { return toint(*this, base); }
int64 string::toint64(int base) const { return toint64(*this, base); }
double string::todouble() const { return todouble(*this); }
int string::toint(const string &s, int base)
{
	return ::strtol(s.c_str(), NULL, base);
}
int64 string::toint64(const string &s, int base)
{
	return ::strtoll(s.c_str(), NULL, base);
}
double string::todouble(const string &s)
{
	return ::strtod(s.c_str(), NULL);
}
//====================================================
//= struct atd::strings
//====================================================
strings &strings::entryf(int count, ...)
{
	va_list va;
	va_start(va, count);
	for (int i = 0; i < count; i++)
	{
		push_back(va_arg(va, const char *));
	}
	va_end(va);

	return *this;
}
string strings::implode(const strings &ss, const string &glue)
{
	string s;
	for (const_iterator i = ss.begin(), e = ss.end(); i != e; ++i)
	{
		if (s.length()) s += glue;
		s += *i;
	}
	return s;
}
string strings::implode(const string &glue) const
{
	return implode(*this, glue);
}
