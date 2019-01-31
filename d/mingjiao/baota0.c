// Room: /u/qingyun/mingjiao/baota0.c
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
string look_qingzhuan();
void create()
{
	set("short", HIR"宝塔一楼"NOR);
	set("long", @LONG
这里是光明宝塔的一楼，虽塔身颇大，但上到此处已不能再上，因为由此
望上去二楼以上皆以巨木组成，似乎只是简单的搭在四周的青砖上，但塔身颇
高，此简单的搭法隐隐的体现出当时的高超建筑技术，虽则站在一楼，但由于
此塔地势高，在此你已可以看到整个光明顶的景色。
LONG);
	set("exits", ([ 
             "out" : __DIR__"baota",
        ]));
	set("item_desc", ([
                "青砖" : (:look_qingzhuan():),
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
		return "此乃明教重地，你到此乱看什么？";
	me->set_temp("xinfa/look",1);
	return "这是一块青砖，明显和周围的青砖不太一样，不仔细看(find)是看不出来的。\n";


}
int do_find(string arg)
{
	object me=this_player();
	object book;
	if (!arg||arg!="青砖")
		return notify_fail("你到此乱翻做什么？");

	if (!me->query_temp("xinfa/look"))
	return notify_fail("此乃明教重地，你到此乱翻做什么？");
	book=new("d/mingjiao/obj/xinfa_book2");
	message_vision(HIC"$N忽然发现左角有块青砖是活动的，于是运起功力将那块青砖慢慢抽出来，在内发现一本书籍。\n"NOR,me);
	book->move(me);
	me->delete_temp("xinfa");
	return 1;
}