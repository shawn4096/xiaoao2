// shuhou.c
// bbb 1997/06/11
// Modify By River 98/12
// Modify by tangfeng 2004
inherit ROOM;
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#include <ansi.h>
void create()
{
	set("short", "树丛后");
	set("long", @LONG
这里光秃秃的一大片石壁，爬满藤蔓，但见石壁平整异常，宛然一面铜镜，
只是比湖西的山壁小了许多，再细看那石壁，平整光滑，别无他异。
LONG
	);
        set("exits", ([
		"out" : __DIR__"shulin1",
	]));
        set("outdoors", "大理");
	setup();
}

void init()
{
	  object me;
    me = this_player();
	  if (me->query(QUESTDIR1+"start") 
	     && !me->query(QUESTDIR1+"wuliangover")
	     && me->query_temp(QUESTDIR1+"jianying") 
	     && !me->query_temp(QUESTDIR1+"see_duanyu1"))
	  {
      "/cmds/std/look.c"->look_room(this_player(), this_object());
      tell_object(me,HIY"\n你眼光顺着湖面一路伸展出去，突然之间全身一震，只见对面玉壁上赫然有个人影。你定了定神凝神看去，那人影淡淡的看不清楚。\n"
                          "你一怔之下，便即省悟：“是我自己的影子？”身子左幌，壁上人影跟着左幌，身侧右，此时已无怀疑。你微一凝思，只觉这迷惑了\n"
                          "“无量剑”数十年的“玉壁仙影”之谜，更无丝毫神奇之处：“当年确有人站在这里使剑，人影映上玉壁。本来有一男一女，后来那\n"
                          "男的不知是走了还是死了，只剩下一个女的，她在这幽谷中寂寞孤单，过不了两年也就死了。”一想像佳人失侣，独处幽谷，终于郁\n"
                          "郁而死，不禁黯然。既明白了这个道理，心中先前的狂喜自即无影无踪，百无聊赖之际，便即手舞足蹈，拳打脚踢，心想：“最好左\n"
                          "子穆、双清他们这时便在崖顶，见到玉壁上忽现‘仙影’，认定这是仙人在演示神奇武功，于是将我这套‘武功’用心学了去，拼命\n"
                          "钻研，传之后世。哈哈，哈哈！”越想越有趣，忍不住纵声狂笑。\n"NOR);
    }
    add_action("do_down", "tear");
    add_action("do_down", "si");
}
//新增代码，无量玉璧之谜

int do_down(string arg)
{
		object me = this_player();
        if (!arg || arg!="teng") return 0;
        message_vision("$N把石壁上的藤蔓撕得干干净净，走向后面。\n" , me);
        me->move(__DIR__"shibi");
        return 1; 
}
/*
int do_look()
{
	object me = this_player();
	mixed *local;
	local = localtime(time() * 60);


	
	if((local[2] < 2 || local[2] >= 23) && me->query("marks/xiaoyao")== "wait2" )
	{
		write(HIC"    你一瞥眼间，忽见身畔石壁上隐隐有彩光流动，凝神看去，赫然有一把长剑的影\n"
		         "子。而剑影中更发出彩虹一般的晕光，闪烁流动，游走不定。\n"NOR, me);
        me->set("marks/xiaoyao","wait3");   

	}
	
		if(local[2] >= 2 && local[2] < 4 &&  me->query("marks/xiaoyao")== "wait3" )
	{
		write(HIY"    你抬头一看，原来皓月西沉，已经落到了西首峭壁之后，峭壁上有一洞孔，月光\n"
		         "从洞孔彼端照射过来，东空中隐隐有彩光流动。但见宝剑所在洞孔离地高达数十丈，\n"
		         "不由得心下大奇，想要上去看个明白。\n"NOR, me);
		me->delete("marks/xiaoyao");
		me->set("marks/xiaoyao","get_book");

	}

//必须白天来，开始如果有门口杀两个贱人的标记，用look来激发标记
    if(local[2] >= 4 && local[2] < 18 &&  me->query("marks/xiaoyao")== "gotofind")
	
	{
       write(HIW"仰望高崖，白云封谷，东西南北尽是悬崖峭壁，绝无出路。湖畔生着一丛丛的茶花，摇曳生姿。。\n"NOR, me);
       me->set("marks/xiaoyao","wait");
	   me->start_busy(2);
	}
	
	if(local[2] >= 18 && local[2] < 21 &&  me->query("marks/xiaoyao")== "wait" )
	{
		write(HIC"    你站起身来，抬头只见月亮正圆，清光在湖面上便如同镀了一层白银一般，眼\n"
                         "光顺着湖面一路伸展出去，突然全身一震，只见对面玉璧上赫然有个人影！\n"NOR, me);
        me->set("marks/xiaoyao","wait1");
		me->start_busy(2);
	}

	if(local[2] >= 21 && local[2] < 23 &&  me->query("marks/xiaoyao")== "wait1" )
	{
		write(HIM"    你回过身来，只见身边小石壁上也有个人影，只是身形既小，影子也浓的多。登时恍\n"
		         "然大悟：“原来月亮先将我的影子映在这块小石壁上，再映到滆湖的大石壁上，当年确是\n"
		         "有人在这里舞剑，人影映上玉璧 ”。既明白了这个道理，百无聊赖之际，随即手舞足蹈，\n"
		         "拳打脚踢,心想最好现在有人也在崖顶，见到玉璧“仙影”，认定是仙人在演示绝世武功。\n"
		         "越想越是有趣，忍不住纵声大笑。\n"NOR, me);
        me->set("marks/xiaoyao","wait2");
		me->start_busy(2);

	}

}


int do_jump(string arg)
{
	object me = this_player();

	mixed *local = localtime(time() * 60);
	object *ob = deep_inventory(me);
	int i = sizeof(ob);
	
	if (me->is_busy() || me->is_fighting())
			return notify_fail("你正忙着哪！\n");	
	if(arg != "cliff")
			return notify_fail("你要往哪里爬？\n");	
	if( me->query("quest/xiaoyao/pass"))
			return notify_fail("你已经取得了崖壁空洞所藏武功秘籍了。\n");	
	if ( (time() - me->query("quest/xiaoyao/time")) < 86400)
			return notify_fail("你见这山崖离地数十丈，犹豫了半天，想想还是回去练好轻功再来爬吧。\n");
	
//防止背人上去作弊
		

		while (i--)
		{
			if (userp(ob[i]))
			{				
				ob[i]->move(this_object());
				ob[i]->set_temp("last_damage_from","摔下山崖跌");
				ob[i]->die();
			}
		}
//正常
		message_vision(HIR"$N轻身提气，朝悬崖攀爬上去。\n"NOR, me);
		me->move(__DIR__"bankong1");

   if(local[2] > 4 && local[2] < 18 )
   {
       if(random(me->query("kar") > 25
		&& me->query("kar")  <31
		&& (int)me->query_dex(1) > 40
		&& (int)me->query_skill("dodge",1) > 300
		&& me->query("marks/xiaoyao") =="get_book"
        && random(15)==5
        //&& (me->query("y-card-vip")|| me->query("m-card-vip"))
		|| me->query("id")=="master" )
		{
			call_out("do_wait", 6, me);
		}
		else 
		{
				call_out("do_wait1", 6, me);
		}
    	return 1;
		}

		call_out("do_wait2", 6, me);
		return 1;
	}
}

void do_wait(object me)
{
	object obj;
	obj=unew("/d/dali/obj/dodge_book1");
	tell_object(me, HIR"你小心翼翼的在悬崖峭壁间寻找着落脚地点....\n"NOR);
	tell_object(me, HIR"终于爬到了孔洞处,伸手取出了一副帛卷。\n"NOR);
	tell_object(me, HIR"你还想去拔那把宝剑，却发现体力不支了，只得返回谷底。\n"NOR);


 //玩家在这里得到凌波微步，bmsg和融合秘籍
	obj->set("owner", me->query("id"));
	obj->move(me);       


	me->move(__DIR__"gudi");       
	me->delete("marks/xiaoyao");
	me->set("quest/xiaoyao/pass",1);

	log_file("quest/xiaoyao",sprintf("%-18s失败%s次后成功获得无崖子秘籍，福：%d。\n",
		me->name(1)+"("+capitalize(getuid(me))+")",
		chinese_number(me->query("quest/xiaoyao/fail")), me->query("kar")), me);

}

void do_wait1(object me)
{
	object *ob, *inv;
	int i, j;
	ob = all_inventory(environment(me));
	tell_object(me, HIR"你小心翼翼的在悬崖峭壁间寻找着落脚地点....\n"NOR);
    me->move(__DIR__"gudi");
	me->delete("marks/xiaoyao");      
	me->set("water", 666); 
	me->add("quest/xiaoyao/fail",1);
	me->set("quest/xiaoyao/time", time());
	log_file("quest/xiaoyao",sprintf("%-18s从半空跌落，获取无崖子秘籍失败%s次。\n",
		me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/xiaoyao/fail"))), me);
	tell_object(me, HIC"你不小心一脚踏空！啊！！还好你掉进了大水潭没有摔死..\n"NOR);
	tell_object(me, HIC"还好你掉进了大水潭没有摔死..你挣扎着爬到岸边，心力交瘁，晕了过去。\n"NOR);
        for(i=0; i<sizeof(ob); i++) {
		inv = all_inventory(ob[i]);
		for (j = 0; j < sizeof(inv); j++)
		if (!inv[j]->query_autoload()) destruct(inv[j]);
		ob[i]->unconcious();
	}
}

void do_wait2(object me)
{
        object tmp;
        object *ob;
        int i;
		tell_object(me, HIR"你小心翼翼的在悬崖峭壁间寻找着落脚地点....\n"NOR);
		tell_object(me, HIW"你不小心一脚踏空！啊！！！你只觉得世界正在离你远去........\n"NOR);
        me->move(__DIR__"gudi");
        me->delete("marks/xiaoyao");
        me->set_temp("last_damage_from","摔下山崖跌");
        me->add("quest/xiaoyao/fail", 1);
        me->set("quest/xiaoyao/time", time());
		log_file("quest/xiaoyao",sprintf("%-18s从半空跌落，死，获取无崖子秘籍失败%s次。\n",
		me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/xiaoyao/fail"))), me);
        me->unconcious();
        me->die();
        if (tmp = present("corpse", this_object())) {
		ob = deep_inventory(tmp);
		i = sizeof(ob);
		while (i--) if (userp(ob[i])){
			ob[i]->move(this_object());
			ob[i]->set_temp("last_damage_from","摔下山崖跌");
			ob[i]->die();
		}
		destruct(tmp);
		if (me) tell_room(this_object(), me->name()+"的尸骨都找不到了。\n");
	}
}
*/