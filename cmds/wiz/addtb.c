
inherit F_CLEAN_UP;

#include <ansi.h>
#include <login.h>
#include <mudlib.h>
#include <database.h>

#define SYNTAX  "ָ���ʽ��addtb <ĳ��> <ͨ��>\n"

int main(object me, string str)
{
	object ob, where;
	int point;
	string name, reason;
	mapping note;

	if(!str || !sscanf(str, "%s %d", name, point))
		  return notify_fail(SYNTAX);

	if (!objectp(ob = LOGIN_D->find_body(name)))
		  return notify_fail("���...���... ���������?\n");;

	if (!objectp(where = environment(ob)))
		  return notify_fail("����˲�֪��������Ү... :-( \n");		  
	
	if (base_name(ob) == "/d/xiangyang/leitai/npc/leitaiuser")
		return notify_fail(ob->name() + "�����Ǳ�����̨Clone�����ģ������ڽ����ɡ�\n");
	
	ob->add("SJ_Credit",point);

	tell_room(where, MAG"�����Ʈ��һ����ò��Ů��������"+ob->query("name")+MAG"��ͷ��\n"NOR, ob);

	tell_object(ob, "������Ա�����齣ͨ��" + CHINESE_D->chinese_number(point) + "�㡣\n"
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
ָ���ʽ��addtb <ĳ��> <ͨ����>
����������ָ������ͨ����
HELP
	);
	return 1;
}
