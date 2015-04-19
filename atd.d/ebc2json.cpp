// ebc2json.cpp
#include "common.h"
#include "ebc2json.h"
#include "ebc2json.job.h"
using namespace ebc2json;
void execute::parallel(
	const string &ebc
	, const strings &fdgs
	, const strings &keys
	, const strings &jsons
	, bool looksuffix
)
{
	job::map jj;
	jj.init(fdgs, keys, jsons);
	jj.read(ebc, looksuffix);
}