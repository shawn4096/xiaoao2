// xuegu.c 
// sohu 
inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "��ѩ��");
	set("long", @LONG
�˵���һ���޴��ѩ�ȡ������䣬���»�ѩ���겻����ѩ��
�ϸ�����һ�㱡���ĺ�������Ϊ�⻬��������Ȳ��ȣ���������
���߼������׵���ѩ���У����յ���ȱ��������
LONG);
	set("exits", ([
		"east" : __FILE__,
		"south" : __FILE__,
		"west" : __DIR__"xuegu",
		"north" : __DIR__"xuegu",
	]));

	set("outdoors", "Ѫ����");

   setup();
}
void init()
{
	object me = this_player();
	add_action("do_jump", ({"jump", "tiao","yue"}));
	
}

int do_jump(string arg)
{
	object room,me = this_player();
	//Ծ�´�ѩ��
    if( arg == "down")
    {
		if (!(room = find_object("/d/xuedao/sxuegu10")))
			room = load_object("/d/xuedao/sxuegu10");
		if(!room)
		{ 
			tell_object(me,HIR"\n��������ô�������ֶ�����ԭ��!\n");
			log_file("quest/LCHJ", sprintf("%s(%s)ȱ��sxuegu10.c�ļ���\n", me->name(1),me->query("id")) );	
			
		}
		message_vision(HIW"$N���ִ˴���������������Ծ������ͷ���£��ȳ��ϣ�����ˮ��������ѩ�У�\n"NOR, me);
		me->move(room);
		me->delete_temp("xd/xdzj");
		me->start_busy(1);
		me->add("neili",-800-random(300));
        tell_room(environment(me),HIC"\nֻ��һ����Ӱ����Ծ��ѩ�У�ԭ����"+me->name()+"����ѩ��!\n"NOR, ({me}));                       
	}

	return 1;
}