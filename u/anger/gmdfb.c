// gmdfb.c  ����������

// ���Χ������������ by renlai
inherit FBROOM;
#include <ansi.h>
void create()
{ 
       set("short",HIR"������-����"NOR);
       set("long", "
    ����������̹����������ߵ�����Ϳɿ��������ʺ�ɫ���֡����̣����֣�\n"+
"ؤ�������������Ḷ̌��������������ɣ���ؤ�����������ɡ���������\n"+
"��˹�̴ܽ�����ԭ���аٶ������ʷ�ˡ�����ʼ�ն��Է�Ԫ����������ȥ��\n"+
"��������Ϊ���ѵ���ּ������������̫�����½�������ݹݬ���룬��ʹ����\n"+
"�����ɳ�Ϊħ�̡�������һ���ɫ����Ĵ��졣���������䳡���ϱ��Ǿ�ľ��\n"+
"�����ڵء���ʱȴ�������ѽ������������̽�������Χ��,������һ��ս(up)���̸��֡�\n\n"HIR"\t\t\t��    ��    ��\n\n"NOR);	
        
		set("backroom","/d/mingjiao/gmd");
        set("quest",1);
		set("no_sleep_room",1);
		set("no_quit", 1);
        set("outdoors", "����");		
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
	
	if(present("mingjiao jiaozhong", environment(me)))
	{
		write("���˻�û��ܣ�����������?\n");	
		return 1;
	}
	if (me->query_temp("gmd_up"))
	{
		write("��Ҫ�ż����ȵ�һ�°ɡ�\n"); 	
		return 1;
	}
	
	if (me->query_temp("gmd_job/enter") ){	 	
        me->apply_condition("gmd_job", 3);
        me->set_temp("gmd_up", 1);			
		message_vision(BLU "���Ȼ���һ����˭����ս������\n" NOR, me);	
	}
	else
	{
		write("Χ��֮�ƻ�û׼�����ء�\n");	
	}
	return 1;	
}

