// xuegu.c 
// sohu 
inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "��ѩ��");
	set("long", @LONG
�˵���һ���޴��ѩ�ȡ������䣬���»�ѩ���겻����ѩ��
�ϸ�����һ����ĺ�������Ϊ�⻬�����꺮�䵼�±��㲻�ϵ�
�ӣ��������Ͽ��Է������ߡ����Ͽ�ȥ��ɽ�´���һ����ʯ(yan)��
�����ƺ�����Ӱ��
LONG);
	set("exits", ([
		"east" : __FILE__,
		"south" : __FILE__,
		"west" : __FILE__,
		"north" : __DIR__"xuegu1",
	]));
     set("item_desc", ([
                "yan": "�����и�ͻ������ʯ���ƺ�����(jump)����ȥ��\n",
                "��ʯ":  "�����и�ͻ������ʯ���ƺ�����(jump)����ȥ��\n",
        ]) );

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
    if( arg == "up")
    {
		if(me->query_skill("dodge")<150) 
		{
			message_vision(HIC"\n$N����һ��������������ѩ�ȣ�ȴͻȻ���ַ��ɽ�ߣ�ȴ���˻�����\n"NOR,me);
			return 1;
		}
		if (!(room = find_object("d/xueshan/xuegu2")))
			room = load_object("d/xueshan/xuegu2");
		if(!room)
		{ 
			tell_object(me,HIR"\n��������ô�������ֶ�����ԭ��!\n");
			log_file("quest/LCHJ", sprintf("%s(%s)ȱ��xuegu2.c�ļ���\n", me->name(1),me->query("id")) );	
		}
		else
		{
			message_vision(HIC"$N��׼һ������ͻ�����ʯ������һ�������߸�Ծ��˳������ʯ��΢һ�������漴����ѩ�ȡ�\n"NOR, me);
			me->move(room);
			me->delete_temp("quest/outxuegu");//
			me->start_busy(1);
            tell_room(environment(me),HIC"\nֻ��һ����Ӱ���������ԭ����"+me->name()+"��ѩ������������\n"NOR, ({me}));                       
		}
	
		return 1;
	}

	
}