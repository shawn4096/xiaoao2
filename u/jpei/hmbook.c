#include <ansi.h>

inherit SPEC; 

void create()
{
	set_name (HIR"蛤蟆撒尿秘籍"NOR, ({ "hmbook"}));
	set("long",HIR"这是一片皱巴巴的碎纸片，纸片已经泛黄，里面的字已然模糊不清。\n"NOR);

	set("unit","片");
	set_weight(100);
	set("value",3000000);

	set("no_give",1);
	set("no_drop",1);	
	set("no_get",1);
	set("no_cun",1);

	set("degree",1);
	set("flag","spec/suizhi");
	set("rest",10);
	set("desc","传说记录了欧阳锋的蛤蟆撒尿无敌秘籍!");
	set("credit",600);
	setup();
}

void init()
{
	add_action("do_chakan","chakan");
}

int do_chakan(string arg)
{
	mapping fam;
	object me = this_player();
	fam = me->query("family");

	if (arg!="hmbook" )
		return notify_fail("你要查看什么?\n");
	if ( me->query("combat_exp") < 800000)
		return notify_fail("你还是抓紧时间去增加点江湖阅历吧！800K前是没机会的啊！\n");

	if (!restrict()) 
	{ 
		return notify_fail("这辈子你已经不能再使用"+this_object()->query("name")+"了。\n");
	}

	if (me->query_skill("hamagong", 1) > 350 &&
	me->query("oyf_son") &&   
	me->query("oyf/hamagong") == 2 &&
	random((int)me->query("kar")) > 25 && 
	random(me->query("con")) > 22 && 
	me->query("max_neili") > 7500  &&
	me->query("neili") > 15000  &&
	me->query("combat_exp") > 2000000)
	{
		me->add("oyf/hamagong",1);
		me->set("title",HIW"白驼山庄"BLU"西毒"HIW"传人"NOR); 

		write(HIR"纸片上潦草的写道：蛤蟆其实不撒尿的，撒尿的蛤蟆怎么能叫蛤蟆呢，那应该叫蛤蟆精了！ \n"NOR,);
		write(HIR"纸片上潦草的写道：原来如此！原来如此！ \n"NOR,);
		log_file("quest/hama", sprintf("%-18s通过通宝物品得到蛤蟆3机会，富%d。\n",me->name(1)+"("+capitalize(getuid(me))+")", me->query("kar")), me);
		return 1; 
	}	 
         
	write(HIW"你反复查看这张"HIR"碎纸片"HIW"，希望能从上面查到点什么。突然，几个模糊的字的映入你的眼帘——“"HIR"蛤蟆不撒尿怎么能叫蛤蟆呢..."HIW"”!\n"NOR);
	degree();
	return 1;
}
