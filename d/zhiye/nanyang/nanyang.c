// Room: /d/nanyang/nanyang.c
// Lklv Modify 2001.10.10
#include <ansi.h>

inherit ROOM;
#define XKX_QUEST2 "quest/侠客行/玄铁令/"
int do_soushen(string arg);
int do_find(string arg);
int do_help(string arg);
void create()
{
	set("short", "城中心");
	set("long", @LONG
这里便是南阳城中心。当年诸葛先生就住在附近的隆中卧龙岗。南阳府地
界不大，方圆不过数十里。但是因为地处南北的要道上，所以南来北往的各地
客商旅人很多。西面是一家酒楼，本地人口甚少，所以生意不是很兴旺。北面
有条大道直通汝州城。
LONG
	);
	set("outdoors", "南阳");
	set("exits", ([
		"south" : __DIR__"yidao2",
		"north" : __DIR__"yidao3",
		"west" : __DIR__"jiulou1",
				"east" : __DIR__"datiepu",

	]));
	set("objects",([
		__DIR__"npc/xiao-fan" : 1,
		__DIR__"npc/xiao_qigai" : 1,
	]));
	setup();
}

void init()
{
	object me,wu;
	me=this_player();
	
	if (me->query_temp(XKX_QUEST2+"findwu"))
	{
		if (!objectp(wu=present("wu daotong",environment(me))))
		{
			message_vision(HIR"吴道通喝道，“纳命来吧！”\n"NOR,me);
			wu=new("d/nanyang/npc/wudaotong");
			wu->move(environment(me));
		}
		me->add_busy(1);
		wu->kill_ob(me);
		me->kill_ob(wu);
		
		//add_action("do_soushen","soushen");
		//add_action("do_soushen","search");

		me->delete_temp(XKX_QUEST2+"findwu");
		me->set_temp(XKX_QUEST2+"meetwu",1);
	}
		add_action("do_soushen","soushen");
		add_action("do_find","xunzhao");
		add_action("do_help","baohu");

	//要消掉临时，以防反复触发
}

int do_soushen(string arg)
{
	object me,ob,obb,obj;
	me=this_player();
	ob=present("corpse",environment(me));
	if (ob)
		obb=ob->query("kill_by");

	if (!arg||arg!="吴道通的尸体")
	{
		return notify_fail("你要搜谁的身？\n");
	}
	if (!me->query_temp(XKX_QUEST2+"meetwu"))
	{
		return notify_fail("你要到处乱摸什么？\n");
	}
	if (!objectp(ob=present("corpse",environment(me))))
	{
		return notify_fail("你又不是锦衣卫，乱搜什么？\n");
	}
	if (ob->query("name")!="吴道通的尸体"
		&&obb->query("id")!=me->query("id"))
	{
		return notify_fail("这是你杀的尸体么？");
	}
	message_vision(HIC"$N伸手往吴道通的尸体上摸来摸去，除了一个小包裹之外，结果什么也没有找到。\n"NOR,me);
	message_vision(HIC"$N仔细检查了那个吴道通随身的那个小包裹，除了一些碎银子和火石等杂物之外，什么也没有找到。\n"NOR,me);

	message_vision(HIY"\n$N站在那儿想了整个过程，不得其解，难道这吴道通身上没有传说的玄铁令。\n"NOR,me);
	

	//message_vision(HIG"\n\n\$N将方才那一幕彻头彻尾的想了一遍，也没有发现破绽，唯一值得可疑的是那个方才那个烧饼。\n"NOR,me);
	//message_vision(HIC"$N在附近找了半天，也没有发现那个烧饼到底去哪儿了。\n"NOR,me);
	me->set_temp(XKX_QUEST2+"soushen",1);



	message_vision(YEL"\n\n就在这时，忽然听到有人喊道，“且慢！放下你手中的东西，否则我黑风寨将与你没玩！”\n"NOR,me);
	message_vision(YEL"\n\n在街口冲来四个山寨的强盗头子！试图抢夺你手中的东西”\n"NOR,me);
	 me->start_busy(1);

	 obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
	 obj->set_name("周牧", ({ "zhou mu", "zhou", "mu" }) );	 
	 obj->set("title", "黑风寨舵主");
     obj->move(environment(me));
	 obj->kill_ob(me);

	 obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
	 obj->set_name("杨威", ({ "yang wei", "yang", "wei" }) );	 
	 obj->set("title", "黑风寨舵主");
     obj->move(environment(me));
	 obj->kill_ob(me);

	 obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
	 obj->set_name("李冲之", ({ "li chongzhi", "li", "chongzhi" }) );	 
	 obj->set("title", "黑风寨舵主");
     obj->move(environment(me));
	 obj->kill_ob(me);
	 obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
	 obj->set_name("张一峰", ({ "zhang yifeng", "zhang", "yifeng" }) );	 
	 obj->set("title", "黑风寨舵主");
     obj->move(environment(me));
	 obj->kill_ob(me);
	return 1;
}


int do_find(string arg)
{
	object me,qigai;
	me=this_player();

	if (me->is_fighting()||me->is_busy())
	{
	   return notify_fail("你正在忙碌中。");

	}	
	if (!arg||arg!="玄铁令")
	{
	   return notify_fail("你要寻找什么。\n");

	}
	if (!me->query_temp(XKX_QUEST2+"soushen")) 
	{
	   return notify_fail("你查找了半天，也没发现这个玄铁令到底去哪儿了。");
	}
	if (!objectp(qigai=present("xiao qigai",environment(me))))
	{
		return notify_fail("你查找了半天，也没发现这个玄铁令到底去哪儿了!心中甚是懊恼。\n");
	}
	//等待石清出现
	if (me->query_temp(XKX_QUEST2+"helpshi"))
	{
		message_vision(HIC"$N继续寻找附近可以物件，再次检查了吴道通留下的遗物，结果还是没找到那枚玄铁令！\n"NOR,me);
		message_vision(HIC"$N心中愤怒之际，拿起手中那个小包裹，顺手就想扔出去！\n",me);
		message_vision(HIY"\n\n这时，忽然听到街角有一个温柔的声音响起，“清哥，你看那个孩子像不像我们的坚儿？”\n"NOR,me);

		call_out("sxz_come",3+random(4),me);
		return 1;
	}
	message_vision(HIC"$N正寻找间，忽然发现街头一角有一个小乞丐，蓬头垢面，手里正拿着一个烧饼再吃！\n"NOR,me);
//	message_vision("$N心下大喜，当即迅速朝那个小乞丐冲了过去，刚想！\n",me);
	message_vision(HIY"那个蓬头垢面的小乞丐看了看手中的烧饼，心中甚是不舍，每次都仅仅咬一小口！\n"NOR,me);
	
	me->set_temp(XKX_QUEST2+"findqigai",1);
	return 1;
}
//救护石破天

int do_help(string arg)
{
	object me,ob,wu;
	me=this_player();
	ob=present("xiao qigai",environment(me));

	if (!arg||arg!="小乞丐")
	{
		if (ob)
		{
			ob->die();
		}
		me->delete_temp("quest/侠客行/玄铁令");
		me->set("quest/侠客行/time",time());

		write("小乞丐为吴道通所杀，故事终止。期待下次机会\n");
		return 1;
		
	}
	if (!ob)
	{
				
				//write("小乞丐为吴道通所杀，故事终止。期待下次机会\n");
		me->delete_temp("quest/侠客行/玄铁令");
		me->set("quest/侠客行/time",time());

		return notify_fail("小乞丐意外身亡，故事终止。期待下次机会\n");

	}
	if (!me->query_temp(XKX_QUEST2+"wucome"))
	{
		me->delete_temp("quest/侠客行/玄铁令");
		me->set("quest/侠客行/time",time());

		return notify_fail("吴道通已经死了，故事意外终止。期待下次机会\n");

	}
	
	if (me->query_temp(XKX_QUEST2+"helpshi"))
	{
		//me->set("quest/侠客行/time",time());

		return notify_fail("你已经保护过一次了，故事意外终止。期待下次机会\n");

	}
	me->set("quest/侠客行/time",time());

	message_vision(HIR"$N忽然心有灵感，觉得那个小乞丐肯定是故事线索的关键，当即闪身挡在小乞丐身前，接下了吴道通这记杀招！\n"NOR,me);

	if (!objectp(wu=present("wu daotong",environment(me))))
	{
		wu=new("d/nanyang/npc/wudaotong");
		wu->move(this_object());
		wu->set("combat_exp",me->query("combat_exp")*3/2);
		me->start_busy(1);
		wu->kill_ob(me);
	}
	me->set_temp(XKX_QUEST2+"helpshi",1);
	return 1;
}

int sxz_come(object me)
{
	object shi,min;
	
	message_vision(CYN"说话之间，两匹快马疾驰而来，一白一黑，来的真是玄素庄庄主和其夫人！”\n"NOR,me);
	message_vision(CYN"闵柔严重充满了莫名的母爱，对那个小乞丐甚是溺爱，宛如自己的亲生儿子一样！”\n"NOR,me);
	message_vision(CYN"那个小乞丐也是顿生舔犊之情，忍不住喊了声“妈妈”！\n"NOR,me);

	message_vision(HIG"\n\n而玄素庄主石清喝道，“且慢”！\n"NOR,me);
	message_vision(HIG"\n石清说道，“哪位英雄是否可以将方才吴道通手中的物事给我看看？”\n"NOR,me);
    message_vision(HIG"\n你还在犹豫间，石清夫妇立即动手，喝道，“得罪了，看招”\n"NOR,me);


	if (!objectp(shi=present("shi qing",environment(me))))
	{
		shi=new("d/motianya/npc/shiqing");
		shi->set("combat_exp",(int)me->query("combat_exp")*3/2);
		shi->set_skill("shangqing-jian",(int)me->query_skill("force",1)*4/3);

		shi->move(environment(me));
		
	}

	if (!objectp(min=present("min rou",environment(me))))
	{
		min=new("d/motianya/npc/minrou");
		min->set("combat_exp",(int)me->query("combat_exp")*3/2);
		min->set_skill("shangqing-jian",(int)me->query_skill("force",1)*4/3);
		min->move(environment(me));
	}
	shi->kill_ob(me);
	min->kill_ob(me);

	//me->kill_ob(shi);
	me->set_temp(XKX_QUEST2+"killshiqing",1);
	call_out("checking",10+random(5),me,shi,min);
	return 1;
}
int checking(object me,object shi,object min)
{
	if (!me) return 0;
	
	if (!shi)
	{
		me->delete_temp("quest/侠客行/玄铁令");
		me->set("quest/侠客行/time",time());

		return notify_fail("你失手把玄素庄主石清给杀了，石破天对你恨之入骨，故事终止。\n");
	}
	if (!min)
	{
		me->delete_temp("quest/侠客行/玄铁令");
		me->set("quest/侠客行/time",time());

		return notify_fail("你失手把玄素庄夫人闵柔给杀了，石破天对你恨之入骨，故事终止。\n");
	}
	
	message_vision(HIR"\n这时，那个小乞丐喊道，别打了，别打了，你们都是好人！\n"NOR,me);
	message_vision(CYN"小乞丐哭喊道，别打了，别打了，你们都是好人！\n"NOR,me);
	message_vision(CYN"不就是一个烧饼么，别打了，我给你就是了！\n"NOR,me);
	message_vision(HIC"小乞丐嚎啕大哭起来！~~~\n"NOR,me);

	shi->remove_all_enemy();
	shi->start_busy(2);
	min->remove_all_enemy();
	min->start_busy(2);

	me->remove_all_enemy();
	me->start_busy(2);
	me->set_temp(XKX_QUEST2+"haoren",1);
	return 1;
}