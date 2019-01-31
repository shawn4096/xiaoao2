// shaobing.c
// By sohu@xojh 侠客行

#include <ansi.h>

inherit ITEM;
int do_eat(string arg);
#define XKX_QUEST2 "quest/侠客行/玄铁令/"

void create()
{
	set_name("烧饼", ({ "shao bing", "bing", "shaobing" }) );
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "块");
		set("material", "rice");
		set("long", "一块刚烙好的烧饼，闻起来香喷喷的，甚是诱人。\n");
		set("no_give", 1);
		set("no_drop", 1);
		set("no_steal", 1);
		set("lingpai",1);
		set("no_get",1);
	}
	setup();
}
void init()
{
	//add_action("do_eat","eat");
	add_action("do_eat","yao");
}

int do_eat(string arg)
{
	object me,ob;
	me=this_player();
	if (!arg||arg!="烧饼")
	{
	   return notify_fail("你要吃什么。");
	}
	if (me->query("quest/侠客行/玄铁令/findxtl"))
	{
	   return notify_fail("你已经得到过玄铁令，无需如此费劲。");
	}
	if (me->query_temp("quest/侠客行/玄铁令/helpshi")
		&&this_object()->query("lingpai")
		&&this_object()->query("owner")==me->query("id"))
	{
		message_vision(HIC"你忙碌半天，确实有些饿，拿起烧饼就咬了下去！谁知竟然差点崩了牙齿！\n"NOR,me);
		message_vision(HIC"你拿起那个硬物一看，赫然竟是一枚“玄铁令”！\n"NOR,me);
		
		ob=new("d/motianya/obj/xuantielingpai");
		ob->set("owner",me->query("id"));
		ob->set_temp(XKX_QUEST2+"findxtl",1);
		ob->move(me);
		this_object()->add("lingpai",-1);
		me->set(XKX_QUEST2+"findxtl",1);
		me->delete_temp("quest/侠客行/玄铁令");
		
		message_vision(HBYEL+HIW"$N机缘巧合，发现并得到了谢烟客的玄铁令！\n"NOR,me);
		call_out("leave",1,me);
		return 1;
	}
	message_vision(CYN"你拿起来那个烧饼，吃了几口！\n"NOR,me);
	return 1;

}
int leave()
{
	object min,shi,qigai,me;
	me=this_player();
	if (!me) return;

	message_vision(HIC"这时，忽然一个阴沉的声音说道，“你这个狗杂种，我可是扎到你了！跟我走吧”\n"NOR,me);
	message_vision(HIC"一个清瘦的人影瞬间来到跟前，抓起那个小乞丐，几个起纵间消失不见！\n"NOR,me);
	message_vision(HIC"玄素庄夫妇大吃一惊，喝道，“放下那个孩子！”，随即急忙追赶过去。！\n"NOR,me);

	if (objectp(min=present("min rou",environment(me))))
	{
		if (min)
		{
			destruct(min);
		}
	}
	if (objectp(shi=present("shi qing",environment(me))))
	{
		if (shi)
		{
			destruct(shi);
		}
	}
	if (objectp(qigai=present("xiao qigai",environment(me))))
	{
		if (qigai)
		{
			destruct(qigai);
		}
	}

   return 1;
}