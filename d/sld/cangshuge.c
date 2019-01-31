#include <ansi.h>
inherit ROOM;
string look_miji();

void create()
{
        set("short", "藏书阁");
        set("long", @LONG
这里是神龙教弟子存放门派武技和杂学的藏书地点，楼阁
放置了数个大书架(shujia)，分为药植学、毒药学、武技学、药
理学等秘籍(miji)，有的是购买整理的，有些显然是抢来的。
LONG);
        set("exits", ([
                "south" : __DIR__"tz",
        ]));
        set("objects", ([
            __DIR__"obj/yaoli1" : 1,
			__DIR__"obj/yaoli2" : 1,
			__DIR__"obj/duyaojing" : 1,
        ]));
		set("item_desc",([
				//"石桌" : "桌面上有许多被鞭类武器击打(hit)出来的印迹。\n",
				"miji" : (:look_miji:),
		]));
		set("hook_count1",1);
		set("hook_count2",1);
		set("leg_count",1);
		set("hand_count",1);
		set("dagger_count",1);
        setup();
        replace_program(ROOM);
}
int init()
{
	add_action("do_find",({"find","search"}));
}
string look_miji()
{
	tell_object(this_player(),HIC"武技类秘籍：\n"NOR
		+"	《基本钩法(上册)》\n"
		+"	《神龙腿法精要》\n"
		+"	《刺客匕法要诀》\n"
		+"	《缠丝诀精要》\n"
		+"	《基本钩法(下册)》\n"
		+"注意：可以通过search shujia得到相关秘籍。\n"NOR);
	return "";
}

int do_find(string arg)
{
	object me,ob;
	string msg;
	me=this_player();

	if (!arg)
	{
		return notify_fail("你要搜寻什么？\n");
	}
	if (me->query("family/family_name")!="神龙教")
	{
		return notify_fail("你不是神龙教弟子来此作甚？\n");
	}
	if (me->query("party/gongji")<500)
	{
		return notify_fail("你的门派贡献值不足500，无法自由兑换门派秘籍！\n");
	}
	if (arg=="shujia")
	{
		msg=HIC"$N在书架上仔细查看，目前书架上存在道学秘籍有：\n"NOR;
		msg=HIC"注意；每次拿去门派秘籍需要门派贡献值500点。\n"NOR;
		if (query("hook_count1")>0)
		{
			msg+=MAG"\n<基本钩法上册>\n"NOR;
		}
		if (query("hook_count2")>0)
		{
			msg+=HIW"\n《基本钩法下册》\n"NOR;
		}
		if (query("leg_count")>0)
		{
			msg+=HIG"\n《神龙腿法精要》\n"NOR;
		}
		if (query("dagger_count")>0)
		{
			msg+=HIG"\n《刺客匕法要诀》\n"NOR;
		}
		if (query("hand_count")>0)
		{
			msg+=HIG"\n《缠丝诀精要》\n"NOR;
		}

		message_vision(msg,me);

		return notify_fail("你在书架上认真找寻一番，书籍很多，不知道你想要寻找那本书？\n");
	}
	
	me->add("party/gongji",-500);

	if (arg=="刺客匕法要诀")
	{
		if (query("dagger_count")<1) 
			return notify_fail("刺客匕法要诀这本秘籍已经被人取走了！\n");
		ob=new("d/sld/obj/dagger_book1");
		ob->move(me);
		message_vision(HIC"$N从书架中抽出一本刺客匕法要诀，放入怀中！\n"NOR,me);
		add("dagger_count",-1);
		return 1;
	}
	if (arg=="神龙腿法精要")
	{
		if (query("leg_count")<1) 
			return notify_fail("神龙腿法精要这本秘籍已经被人取走了！\n");
		ob=new("d/sld/obj/leg_book");
		ob->move(me);
		message_vision(HIC"$N从书架中抽出一本神龙腿法精要，放入怀中！\n"NOR,me);
		add("leg_count",-1);
		return 1;
	}
	if (arg=="缠丝诀精要")
	{
		if (query("hand_count")<1) 
			return notify_fail("缠丝诀精要这本秘籍已经被人取走了！\n");
		ob=new("d/sld/obj/hand_book1");
		ob->move(me);
		message_vision(HIC"$N从书架中抽出一本缠丝诀精要，放入怀中！\n"NOR,me);
		add("hand_count",-1);
		return 1;
	}

	if (arg=="基本钩法上册")
	{
		if (query("hook_count1")<1) 
			return notify_fail("基本钩法上册这本秘籍已经被人取走了！\n");
		ob=new("d/sld/obj/hook_book1");
		ob->move(me);
		message_vision(HIC"$N从书架中抽出一本基本钩法上册，放入怀中！\n"NOR,me);
		add("hook_count1",-1);
		return 1;
	}
	if (arg=="基本钩法下册")
	{
		if (query("hook_count2")<1) 
			return notify_fail("基本钩法下册这本秘籍已经被人取走了！\n");
		ob=new("d/sld/obj/hook_book2");
		ob->move(me);
		message_vision(HIC"$N从书架中抽出一本基本钩法下册，放入怀中！\n"NOR,me);
		add("hook_count2",-1);
		return 1;
	}
	
	return notify_fail("你要搜寻什么书籍？\n");

}