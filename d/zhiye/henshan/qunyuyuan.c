#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",HIC"Ⱥ��Ժ����"NOR);
        set("long", @LONG
�˴��Ǻ����Ǵ��������Ⱥ��Ժ���ᣬ��Ϊ���˺͹�����
ר�����õģ����ڰڷ���һ�Ŵ��Ĵ������������˺��ı�
�죬������������ݻ����������ͷǳ������
LONG );
	set("objects", ([
		//__DIR__"npc/feiyan" : 1,
		//__DIR__"npc/qufeiyan" : 1,

	]));

	set("exits", ([
		"south" : __DIR__"lingyinge",
				//"south" : __DIR__"hengyang11",

	]));	

	//set("no_fight", 1);
	set("sleep_room", 1);

	setup();
		
}	
