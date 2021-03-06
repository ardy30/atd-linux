//atd.path.h
#ifndef __atd_path_h__
#define __atd_path_h__
#include "atd.h"
namespace atd {;;
namespace generic { struct notify; } //prototype
//====================================================
//= struct atd::path
//====================================================
struct path : public object
{
	static string dirname(const string &path);
	static string basename(const string &path);
	static string filename(const string &path);//拡張子を除いたファイル名

	//カレントディレクトリ取得
	static string cwd();
	//実行ファイルのフルパス取得
	static string exename();

	//拡張子の変更
	static string remove_extension(const string &path);
	static string rename_extension(const string &path, const string &extension);

	//ファイルもしくはディレクトリの有無
	static bool exists(const string &path);
	//ファイルかどうか
	static bool isfile(const string &path);
	//ディレクトリかどうか
	static bool isdir(const string &path);
	//シンボリックリンクかどうか
	static bool islink(const string &path);

	//ファイルサイズ
	static int64 filesize(const string &path);

	//ディレクトリの作成
	static bool mkdir(const string &path, int mode = 0777);

	//ファイルコピー＆移動
	static bool copy(const string &from, const string &to, bool force = false);
	static bool move(const string &from, const string &to, bool force = false);
	//ファイルの削除
	static bool unlink(const string &path);
	//一時ファイルの作成
	static string mkstemp(const string &prefix);

	//ファイル情報
	struct fileinfo_t 
	{
		int		dev		;/*st_dev;		ファイルがあるデバイスの ID */
		int		ino		;/*st_ino;		inode 番号 */
		int		mode	;/*st_mode;		アクセス保護 */
		int		nlink	;/*st_nlink;	ハードリンクの数 */
		int		uid		;/*st_uid;		所有者のユーザー ID */
		int		gid		;/*st_gid;		所有者のグループ ID */
		int		rdev	;/*st_rdev;		デバイス ID (特殊ファイルの場合) */
		int64	size	;/*st_size;		全体のサイズ (バイト単位) */
		int		blksize	;/*st_blksize;	ファイルシステム I/O でのブロックサイズ */
		int		blocks	;/*st_blocks;	割り当てられた 512B のブロック数 */

		/* Linux 2.6 以降では、カーネルは以下のタイムスタンプ
		   フィールドでナノ秒の精度をサポートしている。
		   Linux 2.6 より前のバージョンでの詳細は
		   下記の「注意」を参照。 */

		datetime atime;/*st_atim  最終アクセス時刻 */
		datetime mtime;/*st_mtim  最終修正時刻 */
		datetime ctime;/*st_ctim  最終状態変更時刻 */

		fileinfo_t();
		void demo(const generic::notify &notify);
	};
	static fileinfo_t fileinfo(const string &path);
};
}//namespace atd
#endif//__atd_path_h__