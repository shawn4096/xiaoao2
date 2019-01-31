//Creat by renlai@xa
inherit F_CLEAN_UP;

#include <ansi.h>
#include <login.h>
#include <mudlib.h>
#include <database.h>

#define SYNTAX  "指令格式：chvip <vip某人> <to某人>\n"

int main(object me, string str)
{
	object ob1, where,ob2;
	int point,temp1,temp2;
	string name1,name2, reason;
	mapping note;

	if(!str || !sscanf(str, "%s %s", name1, name2))
		  return notify_fail(SYNTAX);

	if (!objectp(ob1 = LOGIN_D->find_body(name1)))
		  return notify_fail("这个...这个... 有这个人吗?\n");;

	if (!objectp(where = environment(ob1)))
		  return notify_fail("这个人不知道在哪里耶... :-( \n");	
	  
    if (!objectp(ob2 = LOGIN_D->find_body(name2)))
		  return notify_fail("这个...这个... 有这个人吗?\n");;

	if (!objectp(where = environment(ob2)))
		  return notify_fail("这个人不知道在哪里耶... :-( \n");	
	
	if (!ob1->query("y-card-vip")) return notify_fail("第一个参数人物必须是年卡vip。 \n");	
	if (ob2->query("y-card-vip")) return notify_fail("第二个参数人物已经是年卡vip。 \n");
	
	temp1=ob2->query("vip/vip_start_time");
	ob2->set("vip/vip_start_time",ob1->query("vip/vip_start_time"));
    ob1->set("vip/vip_start_time",temp1);
	
	temp2=ob2->query("vip/vip_time");
	ob2->set("vip/vip_time",ob1->query("vip/vip_time"));
	ob1->set("vip/vip_time",temp2);
	
	ob2->set("y-card-vip",1);
	ob2->set("registered", 3);
	
	ob1->delete("y-card-vip");	

	tell_object(ob1,"管理人员将"+ob1->name()+"和"+ob2->name() +"交换了vip状态。\n");
    tell_object(ob2,"管理人员将"+ob1->name()+"和"+ob2->name() +"交换了vip状态。\n");		
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
指令格式：chvip <某人A> <某人B>
你可以用这个指令将某人A的vip状态转给某人B，某人A则失去vip状态。
HELP
	);
	return 1;
}
