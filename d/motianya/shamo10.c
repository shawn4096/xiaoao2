inherit ROOM; 

#include <ansi.h>
#include <combat_msg.h> 
void create ()
{
  	set ("short", HIY"����ɳĮ"NOR);
  	set ("long", @LONG
�����������ɳĮ���ڣ��ıڻ��ߣ�ʮ�����ȣ���ɳ�ǳ��Ĵ�
LONG);
        set("outdoors", "motianya");

  	set("exits", ([
  		  "east" : __FILE__,

                "west" : __FILE__,

                "south" : __FILE__,

                "north" : __FILE__,



  		
	]));
        set("objects", ([
		
  		
	]));


	setup(); 
	replace_program(ROOM); 
} 

void init()
{
	object me= this_player();
	/*
	if (random(me->query("kar")) <= 15)
		{
			me->add_condition("liuxue", 2 + random(5));
		tell_object( me, HIY"\nͻȻһ��������ɳ��ʯ����������ϻ����˼������ӡ�\n"NOR);
	}
       if (random(me->query("kar")) >= 19)
		{
			me->move(__DIR__"shamo11");
		write(HIC"\n��ɳ֮��������ҵ��˵㷽�򣬵���ײײ�����˹�ȥ��\n"NOR);
	}*/
	
		if (random(10) <= 6 )
		{
			me->add_condition("liuxue", 1 + random(1));
			tell_object( me, HIY"\nͻȻһ��������ɳ��ʯ����������ϻ����˼������ӡ�\n"NOR);

		}else
		{
			me->move(__DIR__"shamo11");
			write(HIC"\n��ɳ֮��������ҵ��˵㷽�򣬵���ײײ�����˹�ȥ��\n"NOR);

		}

}