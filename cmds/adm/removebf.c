//Creat by renlai@xa
inherit F_CLEAN_UP;

#include <ansi.h>
#include <login.h>
#include <mudlib.h>
#include <database.h>

#define SYNTAX  "指令格式：removebf <某人>\n"

int main(object me, string str)
{
	object ob, where;	
	string name, reason;
	

	if(!str || !sscanf(str, "%s", name))
		  return notify_fail(SYNTAX);

	if (!objectp(ob = LOGIN_D->find_body(name)))
		  return notify_fail("这个...这个... 有这个人吗?\n");;

	if (!objectp(where = environment(ob)))
		  return notify_fail("这个人不知道在哪里耶... :-( \n");		  
	
	if (base_name(ob) == "/d/xiangyang/leitai/npc/leitaiuser")
		return notify_fail(ob->name() + "这人是比武擂台Clone出来的，等下吧。\n");
	
	ob->add_busy(-999);
	ob->set_heart_beat(1);
	ob->clear_condition("job_busy");

	tell_room(where, MAG"天空中飘落一个美貌仙女，轻轻抚摸下"+ob->query("name")+MAG"的头,消除了"+ob->query("name")+"身上的异常状态。\n"NOR, ob);
	
	tell_object(ob, "管理人员已经帮你解除所有异常状态。\n"
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
指令格式：removebf <某人> 
你可以用这个指令给玩家消除异常状态。
HELP
	);
	return 1;
}
