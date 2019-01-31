
inherit F_CLEAN_UP;

#include <ansi.h>
#include <login.h>
#include <mudlib.h>
#include <database.h>

#define SYNTAX  "指令格式：addtb <某人> <通宝>\n"

int main(object me, string str)
{
	object ob, where;
	int point;
	string name, reason;
	mapping note;

	if(!str || !sscanf(str, "%s %d", name, point))
		  return notify_fail(SYNTAX);

	if (!objectp(ob = LOGIN_D->find_body(name)))
		  return notify_fail("这个...这个... 有这个人吗?\n");;

	if (!objectp(where = environment(ob)))
		  return notify_fail("这个人不知道在哪里耶... :-( \n");		  
	
	if (base_name(ob) == "/d/xiangyang/leitai/npc/leitaiuser")
		return notify_fail(ob->name() + "这人是比武擂台Clone出来的，等下在奖励吧。\n");
	
	ob->add("SJ_Credit",point);

	tell_room(where, MAG"天空中飘落一个美貌仙女，拍了拍"+ob->query("name")+MAG"的头。\n"NOR, ob);

	tell_object(ob, "管理人员给予书剑通宝" + CHINESE_D->chinese_number(point) + "点。\n"
	);
	
	return 1;
}

string query(string arg)
{
	if(arg=="id") //return now_id;
	return "Wizard";
}

int help(object me)
{
	write(@HELP
指令格式：addtb <某人> <通宝数>
你可以用这个指令给玩家通宝。
HELP
	);
	return 1;
}
