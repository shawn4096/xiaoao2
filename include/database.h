// database.h

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <mudlib.h>

nosave string DB_HOST       = "localhost";
nosave string DB_USER       = "root";
nosave string DB_NAME       = "bbs";

nosave string WEB_DB_HOST   = "localhost";
nosave string WEB_DB_USER   = "cqmud";
nosave string WEB_DB_NAME   = "discuz";

nosave int ROW_LIMIT        = 10;

#define BBS_FORUMS			"forums"
#define BBS_THREADS			"threads"
#define BBS_POSTS			"posts"
#define BBS_MEMBERS			"members"

#endif
