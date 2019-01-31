//Creat by renlai@xa
inherit F_CLEAN_UP;

#include <ansi.h>
#include <login.h>
#include <mudlib.h>
#include <database.h>

#define SYNTAX  "ָ���ʽ��chvip <vipĳ��> <toĳ��>\n"

int main(object me, string str)
{
	object ob1, where,ob2;
	int point,temp1,temp2;
	string name1,name2, reason;
	mapping note;

	if(!str || !sscanf(str, "%s %s", name1, name2))
		  return notify_fail(SYNTAX);

	if (!objectp(ob1 = LOGIN_D->find_body(name1)))
		  return notify_fail("���...���... ���������?\n");;

	if (!objectp(where = environment(ob1)))
		  return notify_fail("����˲�֪��������Ү... :-( \n");	
	  
    if (!objectp(ob2 = LOGIN_D->find_body(name2)))
		  return notify_fail("���...���... ���������?\n");;

	if (!objectp(where = environment(ob2)))
		  return notify_fail("����˲�֪��������Ү... :-( \n");	
	
	if (!ob1->query("y-card-vip")) return notify_fail("��һ����������������꿨vip�� \n");	
	if (ob2->query("y-card-vip")) return notify_fail("�ڶ������������Ѿ����꿨vip�� \n");
	
	temp1=ob2->query("vip/vip_start_time");
	ob2->set("vip/vip_start_time",ob1->query("vip/vip_start_time"));
    ob1->set("vip/vip_start_time",temp1);
	
	temp2=ob2->query("vip/vip_time");
	ob2->set("vip/vip_time",ob1->query("vip/vip_time"));
	ob1->set("vip/vip_time",temp2);
	
	ob2->set("y-card-vip",1);
	ob2->set("registered", 3);
	
	ob1->delete("y-card-vip");	

	tell_object(ob1,"������Ա��"+ob1->name()+"��"+ob2->name() +"������vip״̬��\n");
    tell_object(ob2,"������Ա��"+ob1->name()+"��"+ob2->name() +"������vip״̬��\n");		
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
ָ���ʽ��chvip <ĳ��A> <ĳ��B>
����������ָ�ĳ��A��vip״̬ת��ĳ��B��ĳ��A��ʧȥvip״̬��
HELP
	);
	return 1;
}
