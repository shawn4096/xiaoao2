#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "Ⱥ��Ժ");
        set("long", @LONG
�˴��Ǻ����Ǵ��������Ⱥ��Ժ�ӣ�������������һյС�������
Ժ����һƬ˿��ͻ�Ц֮�����м��ּ����Ų�ö��������־ƣ�
�������ϸ账����һƬ��ƽ�����ϰ��������١�
LONG );
	set("objects", ([
		//__DIR__"npc/feiyan" : 1,
		"/d/hmy/npc/qufeiyan" : 1,

	]));

	set("exits", ([
		"south" : __DIR__"hengyang11",
		"north" : __DIR__"qunyuyuan",

	]));	

	set("no_fight", 1);
	//set("sleep_room", 1);

	setup();
		
}	

void init()
{
	tell_object(this_player(), HIW "\n��һ�߽�Ⱥ��Ժ��һ���񻷱�����·������"
                                   "�ķ紵�á����������졣\n\n" NOR);	
}

