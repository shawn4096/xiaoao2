// Room: /u/qingyun/mingjiao/baota0.c
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
string look_qingzhuan();
void create()
{
	set("short", HIR"����һ¥"NOR);
	set("long", @LONG
�����ǹ���������һ¥���������Ĵ󣬵��ϵ��˴��Ѳ������ϣ���Ϊ�ɴ�
����ȥ��¥���Ͻ��Ծ�ľ��ɣ��ƺ�ֻ�Ǽ򵥵Ĵ������ܵ���ש�ϣ���������
�ߣ��˼򵥵Ĵ���������ֳ���ʱ�ĸ߳���������������վ��һ¥��������
�������Ƹߣ��ڴ����ѿ��Կ��������������ľ�ɫ��
LONG);
	set("exits", ([ 
             "out" : __DIR__"baota",
        ]));
	set("item_desc", ([
                "��ש" : (:look_qingzhuan():),
        ]));

	set("coor/x",-290);
  set("coor/y",240);
   set("coor/z",150);
   set("coor/x",-290);
 set("coor/y",240);
   set("coor/z",150);
   setup();
}
int init()
{
	add_action("do_find","find");

}
string look_qingzhuan()
{
	object me=this_player();
	if (!me->query_temp("xinfa/askzhang"))
		return "���������صأ��㵽���ҿ�ʲô��";
	me->set_temp("xinfa/look",1);
	return "����һ����ש�����Ժ���Χ����ש��̫һ��������ϸ��(find)�ǿ��������ġ�\n";


}
int do_find(string arg)
{
	object me=this_player();
	object book;
	if (!arg||arg!="��ש")
		return notify_fail("�㵽���ҷ���ʲô��");

	if (!me->query_temp("xinfa/look"))
	return notify_fail("���������صأ��㵽���ҷ���ʲô��");
	book=new("d/mingjiao/obj/xinfa_book2");
	message_vision(HIC"$N��Ȼ��������п���ש�ǻ�ģ��������������ǿ���ש��������������ڷ���һ���鼮��\n"NOR,me);
	book->move(me);
	me->delete_temp("xinfa");
	return 1;
}