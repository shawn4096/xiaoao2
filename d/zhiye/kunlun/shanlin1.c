// shanlin1.c (kunlun)

#include <ansi.h>
#include <room.h>

inherit ROOM;
int do_jump(string arg);
void create()
{
	 set("short", "��ɼ��");
	 set("long",@long
����һƬ�����޾��Ĵ��̵����֣����ܵ���ɼ(yunshan)�����ľ�ɡ������
������֦Ѿ��ֻ©�°߰ߵ��ϸ�����Ӱ������ʮ���ľ�������ȸҲ�ٷ�����ֻż��
������Զ���ļ���������
long);
	 set("exits",([
                "west" : __DIR__"shanlin2",
                "northeast" : __DIR__"jiuqulang2",
                "southeast" : __DIR__"shanlin3",
         ]));

	 set("objects",([
		__DIR__"obj/da-shugan.c" :  1,
		__DIR__"obj/xiao-shuzhi.c" :  1,
	 ]));
     set("item_desc", ([
                "yunshan" : "�ܼ������е���ɼ������ֱ���ʡ�\n�������У��̲�ס������tiao/jump����ȥ�����羰��\n"]));

         set("outdoors", "����");
         setup();
}

void init()
{
	add_action("do_jump","jump");
	add_action("do_jump","tiao");
}

int do_jump(string arg)
{
	object me=this_player();

	int level, jinglicost;

	level = me->query_skill("dodge", 1);
	if (!arg||arg!="yunshan")
		return notify_fail("��Ҫ����ʲô��\n");
	
	jinglicost = level / 3 + random(level / 3);
	
	if (me->query("jingli") <= jinglicost)
	{
			write("��̫���ˣ���ЪЪ�ɣ�\n");
			return 1;
	}
		me->receive_damage("jingli", jinglicost);
	if (level < 30) {
			write("���������ƣ�����ɼ����Ծȥ����ϧ�Ļ����Ṧ����30��,�ż⻹��һЩ���ܹ�����\n");
			return 1;
		}
	
		if (level < 120) 
		{
			message_vision("$N���˿�������������ɼ��辴�Ծȥ��״�����࣬�������ݡ�\n", me);
			me->improve_skill("dodge", me->query_int() / 3);
		}
		else
			message_vision("$N΢һ�˾���˫�ŷ�������ƮƮԾ����ɼ��辣���Ļ����Ṧ�Ѿ��޷�����ˡ�\n", me);
		return 1;
}