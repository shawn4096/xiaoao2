#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "存道塔顶");
        set("long", @LONG
这里是存道塔的塔顶，塔梯到这里就到了尽头。墙壁上开
着几个窗户(window)，阳光照射进来，房间甚是明亮，此地高
远，空气清新如洗，几个中年道人正捧着书苦苦研读。也有不
少道人在四周翻阅书架(shujia)上的各种武技和道藏经典。
LONG);
        set("exits", ([
                "eastdown" : __DIR__"cundaota3",
        ]));
        set("objects", ([
                __DIR__"npc/zhangjing" : 1,
				__DIR__"obj/dadaojue1" : 1,
				__DIR__"obj/dadaojue2" : 1,
        ]));

        set("item_desc", ([
                "window": HIW "\n窗外白云飘过，似乎你一伸手就可以抓住一片。\n" NOR,
			    "shujia": HIW "\n四周书架上摆满了各种道家经典著作，也夹杂不少武功秘籍。\n" NOR,

        ]));

        set("dj_count",1);
		set("tg_count",1);
		set("ys_count",1);
        setup();
        replace_program(ROOM);
}
int init()
{
	add_action("do_search","search");
	add_action("do_search","find");

}
int do_search(string arg)
{
	object me,ob;
	string msg;
	me=this_player();

	if (!arg)
	{
		return notify_fail("你要搜寻什么？\n");
	}
	if (me->query("family/family_name")!="全真教"||!me->query("quest/qz/dichuan"))
	{
		return notify_fail("你不是全真嫡传弟子来此作甚？\n");
	}
	if (me->query("party/gongji")<500)
	{
		return notify_fail("你的门派贡献值不足500，无法自由兑换门派秘籍！\n");
	}
	if (arg=="shujia")
	{
		msg=HIC"$N在书架上仔细查看，目前书架上存在道学秘籍有：\n"NOR;
		msg=HIC"注意；每次拿去门派秘籍需要门派贡献值500点。\n"NOR;
		if (query("dj_count")>0)
		{
			msg+=MAG"\n<大道诀（第三册）>\n"NOR;
		}
		if (query("tg_count")>0)
		{
			msg+=HIW"\n<同归剑谱>\n"NOR;
		}
		if (query("ys_count")>0)
		{
			msg+=HIG"\n<金关玉锁二十四诀（上册）>\n"NOR;
		}
		message_vision(msg,me);

		return notify_fail("你在书架上认真找寻一番，书籍很多，不知道你想要寻找那本书？\n");
	}
	//同归剑法的quest触发
	me->add("party/gongji",-500);

	if (arg=="同归剑谱")
	{
		if (!me->query("quest/qz/tgjf/pass"))
			return notify_fail("你尚未获得观看同归剑法的机会，抱歉！\n");	
		if (query("tg_count")<1) 
			return notify_fail("同归剑谱这本秘籍已经被人取走了！\n");
		ob=new("d/quanzhen/obj/tonggui_jianpu");
		ob->move(me);
		message_vision(HIC"$N从书架中抽出一本<同归剑谱>，放入怀中！\n"NOR,me);
		add("tg_count",-1);
		return 1;
	}

	if (arg=="大道诀"||arg=="大道诀秘籍"||arg=="秘籍")
	{
		if (query("dj_count")<1) 
			return notify_fail("大道诀这本秘籍已经被人取走了！\n");
		ob=new("d/quanzhen/obj/dadaojue3");
		ob->move(me);
		message_vision(HIC"$N从书架中抽出一本大道诀，放入怀中！\n"NOR,me);
		add("dj_count",-1);
		return 1;
	}
	if (arg=="金关玉锁诀"||arg=="金关玉锁二十四诀")
	{
		if (query("ys_count")<1) 
			return notify_fail("金关玉锁诀这本秘籍已经被人取走了！\n");
		ob=new("d/quanzhen/obj/yusuojue1");
		ob->move(me);
		message_vision(HIC"$N从书架中抽出一本金关玉锁诀，放入怀中！\n"NOR,me);
		add("ys_count",-1);
		return 1;
	}
	return notify_fail("你要搜寻什么书籍？\n");

}