//Creat by renlai@xa
inherit F_CLEAN_UP;

#include <ansi.h>
#include <login.h>
#include <mudlib.h>
#include <database.h>

#define SYNTAX  "ָ���ʽ��removebf <ĳ��>\n"

int main(object me, string str)
{
	object ob, where;	
	string name, reason;
	

	if(!str || !sscanf(str, "%s", name))
		  return notify_fail(SYNTAX);

	if (!objectp(ob = LOGIN_D->find_body(name)))
		  return notify_fail("���...���... ���������?\n");;

	if (!objectp(where = environment(ob)))
		  return notify_fail("����˲�֪��������Ү... :-( \n");		  
	
	if (base_name(ob) == "/d/xiangyang/leitai/npc/leitaiuser")
		return notify_fail(ob->name() + "�����Ǳ�����̨Clone�����ģ����°ɡ�\n");
	
	ob->add_busy(-999);
	ob->set_heart_beat(1);
	ob->clear_condition("job_busy");

	tell_room(where, MAG"�����Ʈ��һ����ò��Ů�����ḧ����"+ob->query("name")+MAG"��ͷ,������"+ob->query("name")+"���ϵ��쳣״̬��\n"NOR, ob);
	
	tell_object(ob, "������Ա�Ѿ������������쳣״̬��\n"
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
ָ���ʽ��removebf <ĳ��> 
����������ָ�����������쳣״̬��
HELP
	);
	return 1;
}
