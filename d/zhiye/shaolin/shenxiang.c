// Room: /d/shaolin/shanlu1.c
// Date: YZC 96/01/19

#include <room.h>
inherit ROOM;
#include <ansi.h>
int do_drop();
int do_fang(string arg);
void create()
{
	set("short", "����");
	set("long", @LONG
����һ������Ķ��������������˳��������⿴��ȥ
����һƬ�յ����ġ�
LONG
	);
	setup();
}

void init()
{
	object me = this_player();
	add_action("do_tiao","jump");
	add_action("do_fang","fang");
	add_action("do_drop","drop");

}

int do_tiao(string arg)
{
	object me=this_player();
    if (arg !="down" && arg !="����")
		return notify_fail("��Ҫ���Ķ�����");
	
	tell_object(me,HIC+me->query("name")+"ವ�һ������Ծ�£��������۱���ĵ��ϡ�\n"NOR);
	me->move("d/shaolin/daxiong");
	return 1;

}
int do_drop()
{
	object me=this_player();
	message_vision(HIC"����֮������ʥ֮�أ�����Ϊ���������������ҷţ�\n"NOR,me);
    return 1;

}
int do_fang(string arg)
{
	object baitie;
	object me=this_player();
	
	if (!objectp(baitie=present("bai tie",me)))
		return notify_fail("��Ҫ��ʲô�������ϣ�");

	if (arg !="bai tie")
		return notify_fail("�������񣬲���������Ӷ�����\n");
	
	tell_object(me,HIC+me->query("name")+"�����������İ�����������ͷ���ϣ�ͬʱ�ٺ���Ц������\n"NOR);
	tell_object(me,HIC+me->query("name")+"�����������������������ͺ¿�ǹ��ܵġ�����\n"NOR);
	tell_object(me,HIC+me->query("name")+"��������������ҿ��Ի�ȥ��ʦ���㱨�ˣ�����ʲô�������о�����ȥ�ɡ�\n"NOR);
	me->delete_temp("kl/baihe/jump");
	me->set_temp("kl/baihe/fangxin",1);
	baitie->move("/d/shaolin/shenxiang");
	return 1;

}
