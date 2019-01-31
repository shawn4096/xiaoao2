// nroad6.c
// Modified by Java Apr.27 1998

#include <ansi.h>
inherit ROOM;
int do_yandu(string arg);
void create()
{
        set("short","静修室");
        set("long",@LONG
血刀门的参禅领悟之地，地上的蒲团上盘坐了不少修炼的僧人
姿势怪异，但从太阳穴坟起的状况看，显然均都修炼有成之辈，内力
深厚之辈。墙上纵横交错无数的刻痕，显然是高手以刀在墙上雕刻了
些人行图画(picture)，很多入门弟子在此研读。
LONG );
        set("exits",([
                "west"   : __DIR__"cave",
                "north" : __DIR__"shufang",
			    "east" : __DIR__"chucangshi",
		]));
//       set("objects",([            
				
       // ]));
	 	set("item_desc", ([
			"picture" : HIR"		血刀经---入门篇"NOR
						+CYN"\n\n\n那是一个人形图案，一个精瘦干枯的裸体男子，一手指天，一手指地\n"
							+"面目极是诡异，旁边注满了五颜六色的怪字，形若蝌蚪，或红或绿\n"
							+"你瞧着图中男子，见他钩鼻深目，曲发高额，不似中土人物，形\n"
							+"貌甚是古怪，而怪异之中，更似蕴藏着一股吸引之力，令人不由自\n"
							+"主地心旌摇动，神不守舍。。。。。。。。。。。。。。。。。。\n"NOR
							+"\n\n\n\n末尾刻着["HIR"血刀老祖"NOR"] 四个大字。\n"NOR,
		]));
        setup();
        //replace_program(ROOM);
}

void init()
{

	add_action("do_yandu","yandu");
}

int do_yandu(string arg)
{
	object me;
	mapping fam;
	me=this_player();

	if (!arg||arg!="图画")
	{
		return notify_fail("你要观看什么内容？\n");
	}
	if (me->query("class")!="huanxi"&&!me->query("qest/xuedao/shoujie"))
	{
		return notify_fail("此地乃是血刀门精修之地，你鬼鬼祟祟来此难道要偷窃血刀门武学么？\n");
	}
	
	if (me->query("family/family_name") != "血刀门")
		return notify_fail( RANK_D->query_respect(me) + "这是人家血刀门不传之密。\n");

	if( (string)me->query("gender") == "无性" )
		return notify_fail("施主身体残缺，虽说佛祖普渡众生，可是我血刀门完全靠那玩意，.……\n");

	if (arg == "图画"){		
			if(me->query("potential", 1) < 1)
				return notify_fail("你的潜能没了，不能再继续修习了\n");
			if(!(fam = me->query("family")) || fam["family_name"] != "血刀门")
				return notify_fail("你不是血刀门弟子，如何能领悟血刀门的高深武功？\n");
			if(me->query("gender") == "无性")
				return notify_fail("你无根无性，阴阳不调，难以领会高深的血刀经神功。\n");
			if(me->is_busy() || me->is_fighting())
				return notify_fail("你正忙着哪！\n");
			if(me->query("jing") < 25 )
				return notify_fail("你的精神很差, 该先去休息一会. \n");           
			if(me->query_skill("force", 1) < 20)
				return notify_fail("你的基本内功太低，无法研习更高级的内功。\n");        
			//if(me->query_skill("xuedao-jing", 1) < 30)
				//return notify_fail("你的血刀经等级太低，无法领悟墙上的文字。\n");
            if(me->query_skill("xuedao-jing", 1) > 100)
 				return notify_fail("你的血刀经神功精进一层，可以去找门中高手请教高深武功了。\n");
	
				write("你开始研习墙上的奇怪图形，忽觉真气在奇经八脉间窜动不已。\n");
				me->receive_damage("jing",(int) 150/me->query("int"));
                me->improve_skill("xuedao-jing", me->query_int() + random((int)me->query_int() * 5 / 3));

				me->add("potential", -1);
			return 1;

		
		
	}
	return notify_fail("你要研习什么？\n");


}