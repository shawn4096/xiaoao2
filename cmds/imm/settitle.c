// settitle.c (Mon  09-04-95)
// creat by renlai
inherit F_CLEAN_UP;
#include <ansi.h>
#include <login.h>
#include <mudlib.h>
#include <database.h>



#define SYNTAX  "指令格式：settitle <某人> <头衔>\n" 
int main(object me, string str)
{
	string name, newtitle;
	object ob, where;
	object obj;
	
	
	
	if(!str || !sscanf(str, "%s %s", name, newtitle))
		  return notify_fail(SYNTAX);
	/*
	if( !str ) {
		write(sprintf(BOLD "%s" NOR "%s\n", RANK_D->query_rank(me), me->short(1)));
		return 1;
	}*/
	/*if( str == "none") {
		me->delete("title");
		write("您的title已经被删除了。\n");
		write(sprintf(BOLD "%s" NOR "%s\n", RANK_D->query_rank(me), me->short(1)));
		return 1;
	}*/
	
	if (!objectp(ob = LOGIN_D->find_body(name)))
		  return notify_fail("这个...这个... 有这个人吗?\n");;

	if (!objectp(where = environment(ob)))
		  return notify_fail("这个人不知道在哪里耶... :-( \n");		  
	
	newtitle = replace_string(newtitle, "$BLK$", BLK);
	newtitle = replace_string(newtitle, "$RED$", RED);
	newtitle = replace_string(newtitle, "$GRN$", GRN);
	newtitle = replace_string(newtitle, "$YEL$", YEL);
	newtitle = replace_string(newtitle, "$BLU$", BLU);
	newtitle = replace_string(newtitle, "$MAG$", MAG);
	newtitle = replace_string(newtitle, "$CYN$", CYN);
	newtitle = replace_string(newtitle, "$WHT$", WHT);
	newtitle = replace_string(newtitle, "$HIR$", HIR);
	newtitle = replace_string(newtitle, "$HIG$", HIG);
	newtitle = replace_string(newtitle, "$HIY$", HIY);
	newtitle = replace_string(newtitle, "$HIB$", HIB);
	newtitle = replace_string(newtitle, "$HIM$", HIM);
	newtitle = replace_string(newtitle, "$HIC$", HIC);
	newtitle = replace_string(newtitle, "$HIW$", HIW);
	newtitle = replace_string(newtitle, "$NOR$", NOR);
	if( strlen(strip(newtitle)) > 40 )
		return notify_fail("你的title太长了，想一个短一点的、响亮一点的。\n");
	ob->set("title", newtitle + NOR);
	ob->set("mytitle/quest/spectitle",newtitle + NOR);
	write(sprintf(BOLD "%s" NOR "%s\n", RANK_D->query_rank(ob), ob->short(1)));
	
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式: settitle id newtitle
 
设置头衔,颜色参考color。

HELP );
	return 1;
}
