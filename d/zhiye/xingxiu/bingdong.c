//bingdong.c 冰洞
//cre by sohu@xojh

#include <ansi.h>
inherit ROOM;
int do_sa(string arg);

void create()
{
        set("short", HIW"冰洞"NOR);
        set("long", @LONG
这是一个小冰洞，进入冰洞后视野顿时为之一开，洞高约有两人高
四周方圆约有十丈左右的样子，甚是开阔。洞深处似乎有白晶晶的东西
在蠕动，仔细一看却有一无所有。此洞内寒气入骨，乃是天山深处的极
寒之地。
LONG
        );
        set("exits", ([
          "out" : __DIR__"shanao",
       //   "northwest" : __DIR__"tsroad1",
        ]));

        set("indoors", 1);

        set("coor/x",-10);
		set("coor/y",50);
		set("coor/z",0);
		setup();
}
void init()
{
	object me=this_player();
	add_action("do_search","search");
	add_action("do_sa","sa");
	add_action("do_fang","fang");
	add_action("do_ran","ran");
	add_action("do_xiulian","xiulian");
}

//撒硫磺
int do_sa(string arg)
{
	object liuhuang;
	object me=this_player();
	
	if (arg=="硫磺"||arg=="liuhuang"||arg=="liu huang")
	{
		if (!objectp(liuhuang=present("liu huang",me)))
		{
			return notify_fail("你身上没有硫磺！\n");
		}
		message_vision(YEL"$N小心的在地上将硫磺撒成一个圆圈。\n"NOR,me);
		liuhuang->move(environment(me));
		me->set_temp("bingcan/saliuhuang",1);
		return 1;
	}else return notify_fail("你要撒什么？\n");

}
int do_fang(string arg)
{
	object hulu;
	object me=this_player();
	
	if (arg=="青葫芦"||arg=="hulu"||arg=="葫芦")
	{
		if (!objectp(hulu=present("hulu",me)))
		{
			return notify_fail("你身上没有带葫芦！\n");
		}
		message_vision(YEL"$N将葫芦小心翼翼放到硫磺上，葫芦口朝内而放。\n"NOR,me);
		hulu->move(environment(me));
		me->set_temp("bingcan/fanghulu",1);
		return 1;
	}else return notify_fail("你要在地上放什么？\n");

}
int do_search(string arg)
{
	object muding;
	object me=this_player();
	if (!arg ||(arg!="冰蚕"&&arg!="bingcan"))
	{
		return notify_fail("你鬼头鬼脑的在瞎找什么？\n");
	}
	if (me->is_busy())
	{
		return notify_fail("你正在忙碌中，无法继续寻找冰蚕？\n");

	}
	if (!me->query_temp("bingcan/askxiu"))
	{
		return notify_fail("你找了半天，找了一手冰雪软泥。\n");
	}
	if (!objectp(muding=present("shenmu wangding",this_object())))
	{
		return notify_fail("此地没有神木王鼎！\n");
	}
	if (muding->query_temp("dianxiang")<3)
	{
		return notify_fail("神木王鼎没有被点香，不能发挥药效！\n");
	}
	message_vision(HBYEL+HIW"$N见神木王鼎的药香已经被点燃，悄悄地躲在一边观察。\n"NOR,me);

	if (random(me->query("kar"))>25)
	{
		message_vision(HIC"忽然间，$N好像发现冰洞内传来一阵悉悉索索的声音。$N急忙屏住气息，一动不动趴在哪儿!\n"NOR,me);
		me->start_busy(15);
		call_out("do_wait",5+random(10),me);

		
	}else {
		message_vision(HIG"轻烟袅袅，药香飘香冰洞的各个方向。\n"NOR,me);
		
	}
	return 1;
}

int do_wait(object me)
{
		object obj;
		int j;
		j=me->query_skill("force",1);
		message_vision(HIW"忽然$N只听得响声大作，颇异寻常。异声中夹杂着一股中人欲呕的腥臭，$N屏息不动\n"+
						"只见长草分开，一条白身黑章的大蟒蛇蜿蜒游至，蟒蛇头作三角形，头顶上高高生了\n"+
						"一个凹凹凸凸的肉瘤。北方蛇虫本少，这蟒昆如些异状，更是众所未见。蟒蛇游到木\n"+
						"鼎之旁，绕鼎团团转动，这蟒蛇身长二丈，粗逾手臂，如何钻得进木鼎之中？但闻到\n"+
						"香料及木鼎气息，一颗巨头住用去撞那鼎。\n"NOR,me);
			
			obj=new("/d/sld/npc/dushe");
		    obj->set("combat_exp", me->query("combat_exp")*2);
		    obj->set("max_qi", me->query("max_qi")*4);
		    obj->set("eff_qi", me->query("max_qi")*4);
		    obj->set("qi", me->query("max_qi")*4);
		    obj->set("max_jing", me->query("max_jing"));
		    obj->set("jing", me->query("max_jing"));
		    obj->set("eff_jing", me->query("eff_jing"));
		    obj->set("eff_jingli", me->query("eff_jingli"));
		    obj->set("max_neili", me->query("max_neili"));
		    obj->set("jing", me->query("max_jing"));
		    obj->set("jingli", me->query("max_jingli"));
		    obj->set("neili", me->query("max_neili")*3/2);
		    obj->set("jiali", 200);
		    obj->set("str", me->query("str")*2);
		    obj->set("con", me->query("con")*2);
		    obj->set("dex", me->query("dex")*2);
		    obj->set("int", me->query("int")*2);
		    obj->set_skill("unarmed",j +random(50));
		    obj->set_skill("force",j + random(50));
		    obj->set_skill("dodge",j + random(50));
		    obj->set_skill("parry",j + random(50));
			obj->set("no_get",1);
		    obj->move(environment(me));
		    obj->set_leader(me);
		    obj->kill_ob(me);
		    message_vision(RED"$N一口咬向$n！\n"NOR,obj,me);
			me->start_busy(1);
			return 1;
}

int do_ran(string arg)
{
	object obj;
	object me=this_player();
	if (arg!="蛇血") return notify_fail("你要点燃什么？\n");
	if (me->query_temp("bingcan/ranshexue"))
	{
		return notify_fail("你方才刚刚点燃了蛇血，过会再燃，不行就quit从来。\n");
	}
	if (objectp(obj=present("corpse",environment(me)))&&obj->query("kill_by")==me)
	{
		message_vision(HIC"$N将这条毒蛇杀死后将其血引入到神木王鼎之中，在药香的引导下，发出一股奇异的香味。\n"NOR,me);
		me->set_temp("bingcan/ranshexue",1);
		me->start_busy(8);
		call_out("bingcan_come",3+random(5),me);
		return 1;
	}
	else {
		//message_vision(HIC"$N将这条毒蛇杀死后将其血引入到神木王鼎之中，在药香的引导下，发出一股奇异的香味。\n"NOR,me);
		return notify_fail("有蛇么，是你杀死的么，还放蛇血？\n");
	}
}
int bingcan_come(object me)
{
	object obj,hulu;
	message_vision(HIR"便在此时，忽觉得一阵寒风袭体，只见西角上一条火线烧了过来，顷刻间便浇到了面前。\n"
						"一到近处，乍得清楚原来不是火线，却是草丛中有什么东西爬过来，青草遇到，立变枯焦，\n"
						"同时寒乞越来越盛。$N退后了几步，只见草丛枯焦的黄线移向木鼎，却是一条亮晶晶的"+HIW"蚕虫"HIR"。\n"NOR,me);
	message_vision(HIG"\n\n这蚕虫纯白如玉，微带青色，比寻常蚕儿大了一倍有余，便似一条蚯蚓，身子透明直如水晶\n"+
						"那水晶蚕儿迅速异常的爬上神木王鼎，一路向上爬行，便如一条炽热的炭火一般，在神木王鼎\n"+
						"的脊梁上子上烧出了一条焦线，钻入蟒蛇头旁的毒囊，吮吸毒液，顷刻间身子便胀大了不少，\n"+
						"远远瞧去，就像是一个水晶瓶中装满了青紫色的汁液。\n"NOR,me);
	if (!me->query_temp("bingcan/saliuhuang")||!me->query_temp("bingcan/fanghulu")||!objectp(present("hulu",environment(me)))||!objectp(present("liu huang",environment(me))))
	{
		message_vision(HIY"\n\n冰蚕非常警觉，看到有人在附近，立即窜回洞中。\n$N无论如何也没找到它！\n"NOR,me);
		me->delete_temp("bingcan");
		return 1;
	}
	message_vision(HIG"冰蚕急忙回转，但已经落入到$N提前布置的硫磺药环之中，左冲右突，不得出口。\n眼见一个葫芦口正好对着它，冰蚕倏的一声钻入到那个葫芦中去。\n"NOR,me);
	obj=new("d/xingxiu/obj/bingcan");
	
	//obj->move(environment(me));

	hulu=present("hulu",environment(me));
	hulu->set("bingcan",1);
	obj->move(hulu);
	me->set_temp("bingcan/bingcanok",1);
	me->set("quest/xx/csz/bingcan/hulu",1);

	return 1;
}
//捡起葫芦来

int do_xiulian(string arg)
{
	object hulu,obj;
	object me=this_player();
    if (!me->query_temp("bingcan/bingcanok"))
    {
		return notify_fail("你要胡乱修炼不怕被冻死！\n");
    }
	if (arg!="冰蚕毒掌")
	{
		return notify_fail("冰蚕乃是剧毒之物，你要修炼什么？\n");
	}
	if (me->query_skill("huagong-dafa",1)<450)
	{
		return notify_fail("你的化功大法功力太弱，不足450，抵抗不住这寒毒侵袭\n");
	}
	if (me->query_skill("poison",1)<200)
	{
		return notify_fail("你的毒计不足200,太弱，抵抗不住这寒毒侵袭\n");
	}
	if (time()-me->query("quest/xx/csz/bingcan/time")<86400)
	{
		return notify_fail("你来的太频繁了，寒毒积累过多，对身体不宜。\n");
	}
	if (me->query("quest/xx/csz/bingcan/pass"))
	{
		me->set("title",HBWHT+HIG"冰蚕毒掌传人"NOR);
		me->set("mytitle/quest/bingcantitle",HBWHT+HIG"冰蚕毒掌传人"NOR);
		return notify_fail("你已经解开这冰蚕毒掌的奥秘了，开什么玩笑\n");
	}
	if (me->query("quest/xx/csz/bingcan/hulu"))
	{
		message_vision(HIC"$N以手指地，骂道，“你怎地如此不守规矩，一个人偷偷出去玩耍？害得老子担心了半天，\n"
							+"生怕你从此不回来了。老子从昆仑山巅万里迢迢的将你带来，你太也不知好歹，不懂老子\n"
							+"对待你一片苦心。这样下去，你还有什么出息，将来自毁前途，谁也不会来可怜你。\n"NOR,me);
		if (!objectp(hulu=present("hulu",me)))
		{
			return notify_fail("你身上没有葫芦装载冰蚕，冰蚕又快速的逃掉了！\n");
		}
		message_vision(HIW"在$N的絮叨之中，忽然一道白光闪过，一条冰蚕又爬到了$N的葫芦中去。\n"NOR,me);
		message_vision(HIW"葫芦表面瞬间结了一层冰,$N捧在手里，冰彻入骨，冻得直打哆嗦。\n"NOR,me);

		hulu->set("bingcan",1);


	}
	if (!objectp(hulu=present("hulu",me))||!hulu->query("bingcan"))
	{
		return notify_fail("你身上没有葫芦或葫芦中的冰蚕已经溜掉!\n");
	}
	message_vision(HIW"$N当下双足一挺，倒转身子，脑袋从胯下钻出，左手抓足，右手伸入葫芦口，突然食指尖上微微一痒\n"+
						"一股寒气优似冰箭，循着手臂，迅速无伦的射入胸膛，$N心中默诵内功口诀，那道寒气果颠真顺着\n"+
						"心中所想的脉络，自指而臂，又自胸腹而至头顶，细线所到之处奇寒彻骨。\n"NOR,me);
	me->receive_wound("jing",2000,"中奇寒毒");
	me->receive_wound("qi",3000,"中奇寒毒");

	me->apply_condition("cold_poison",10);
	me->add_busy(20);
	if (random(me->query("kar"))>23)
	{
		me->set("quest/xx/csz/bingcan/over",1);
		me->delete_temp("bingcan");
		message_vision(HIY"初步修炼打通了神足经，获得初步抵抗冰蚕毒能力，赶紧回去请教游坦之如何运转经脉吧。\n"NOR,me);
	}else {
		message_vision(CYN"\m修炼冰蚕毒失败，继续修炼，再接再厉。\n"NOR,me);
		me->set("quest/xx/csz/bingcan/time",time());
		me->add("quest/xx/csz/bingcan/fail",1);
		me->delete_temp("bingcan");
	}
	return 1;
}

