//���¸��� by renlai

#include <ansi.h>

inherit FBROOM;

void create()
{
        set("short", HIM"������-����"NOR);
        set("long", @LONG
�������ڣ�������Ӱ�´£�ÿһ���ж���������Ѳ�飬����
���ж���ʮ�����ţ�������һ����һ���������ϵ�ʯ��(up)��
LONG);
        //set("outdoors", "����");
		set("backroom","/d/was/was");
        set("quest",1);
		set("no_sleep_room",1);
		set("no_quit", 1);		
        
		
   setup();
}
#include "fuben.h";

int do_up()
{
	object me=this_player();
	
	if (me->is_busy())
	{
		write("����æ���ء�\n");	
		return 1;
	}
	
	if (me->is_fighting()) 
	{
		write("����ûɱ��������?\n");	
		return 1;
	}
	
	if(present("menggu wushi", environment(me)))
	{
		write("����ûɱ��������?\n");	
		return 1;
	}
	if (me->query_temp("was_up"))
	{
		write("��Ҫ������Ѳ����ʿ���ȵ�һ�°ɡ�\n"); 	
		return 1;
	}
	
	if (me->query_temp("was_job/enter") ){	 	
        me->apply_condition("was_job", 3);
        me->set_temp("was_up", 1);			
		message_vision(BLU "��������˿��أ��������¥����ȥ��\n" NOR, me);	
	}
	else
	{
		write("�㻹û�����ء�\n");	
	}
	return 1;	
}