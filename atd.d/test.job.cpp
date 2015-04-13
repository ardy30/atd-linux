// test.job.cpp
#include "test.job.h"
job::job(
	  const string &ebc
	, const string &fdg
	, const string &json
)
: todo(0)
, done(0)
{
	path.ebc = ebc;
	path.fdg = fdg;
	path.json = json;
}
job::~job()
{
}
void job::ebcclear()
{
	ofs.open(path.ebc.c_str(), std::ios::binary | std::ios::out);
	ofs.close();
}
void job::ebcopenappend()
{
	ofs.open(path.ebc.c_str(), std::ios::binary | std::ios::app);
}
void job::fdgload()
{
	std::ifstream ifs(path.fdg.c_str(), std::ios::in);
	fdg.loadcobol(ifs);
}
job::map::~map()
{
	//メモリの解放
	for (iterator i = begin(), e = end()
		; i != e; ++i)
	{
		delete i->second;
		erase(i);
	}
}
 