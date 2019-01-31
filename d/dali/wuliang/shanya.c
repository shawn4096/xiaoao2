// bbb 1997/06/11
// Modify By River 98/12
// Modify by tangfeng 2004

#include <ansi.h>
int get_object(object ob);
inherit ROOM;
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"

string look_down();
void create()
{
	set("short", "白龙峰");
	set("long", @LONG
走出十余里，你来到无量山主峰的后山，已来到无量剑派禁地，任何外人
不得擅入。这里丛林密布，山石怪异。旁边就是一深不见底的悬崖(cliff)。
LONG
	);
	set("exits", ([
		"northwest" : __DIR__"pubu",
	]));
        set("outdoors", "大理");
        set("objects", ([
           "/d/dali/wuliang/obj/yeguo" : 2,
        ]));

	set("item_desc",([
	   "cliff" : (: look_down :),
	   "down" : "下面白茫茫的什么也看不见。\n"
	]));
	setup();
}

void init()
{
	add_action("do_jump", "tiao");
        add_action("do_jump", "jump");
}

int get_object(object ob)
{
        if(userp(ob))
        return 1;
        return 0;
}

int do_jump(string arg,object *obj)
{
	      object me= this_player();
        if (!arg || (arg !="down" && arg !="cliff")) return 0;
        if(sizeof(obj)){
         message_vision(HIR "$N脚下踩一个空，「啊～～～」发出一声惨叫，向下直坠下去。\n"NOR, me);
         me->receive_wound("qi", 20);
         me->unconcious();
         me->move("/d/dali/shanlu3");
         return 1;
         }
	      if(me->query_condition("killer")) return 0;
        if (me->query(QUESTDIR1+"start") 
           && me->query(QUESTDIR1+"over"))
        {
	       message_vision(HIR "$N脚下踩一个空，「啊～～～」发出一声惨叫，向下直坠下去。\n" 
                            "$N坠下百余丈，撞到崖边一棵古松上，弹了几弹，下坠的巨力却也消了。\n" NOR, me);
         me->move(__DIR__"bankong");
         tell_object(me,HIY"\n你已不是第一次跳跃，看似危险，其实你早看好了方向，你半空一个凌身翻，\n"
                           "抓住古松，再次借力又一个飞身，已经安全到达一棵树顶。你缓缓跃了下来。\n"NOR);
         me->move(__DIR__"banshan1");
	       return 1;
         }
        if ((me->query(QUESTDIR1+"start") && (random((int)me->query("kar")) >8))
        ||(me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"jianying")) 
        || (random((int)me->query("kar")) >20)
        || me->query("marks/xiaoyao")
)
        {
	       message_vision(HIR "$N脚下踩一个空，「啊～～～」发出一声惨叫，向下直坠下去。\n" 
         "$N坠下百余丈，撞到崖边一棵古松上，弹了几弹，下坠的巨力却也消了。\n" NOR, me);
         me->move(__DIR__"bankong");
	       return 1;
         }
         message_vision(HIR "$N脚下踩一个空，「啊～～～」发出一声惨叫，向下直坠下去。\n"NOR, me);          
         me->receive_wound("qi", 20);
         me->unconcious();
         me->move("/d/dali/shanlu3");
         return 1;
}

string look_down()
{
	return  "下面(down)深不可测，根本看不到底，如果你要自杀，这到是个好地方。\n";
}

/*

//晚上，月影出现方可领悟。
int do_look()
{
	object me = this_player();
	mixed *local;
	local = localtime(time() * 60);


	
	if((local[2] < 2 || local[2] >= 23) && me->query("marks/xiaoyao")== "wait2" )
	{
		write(HIC"你一瞥眼间，忽见身畔石壁上隐隐有彩光流动，凝神看去，赫然有一把长剑的影\n"
		         "子。而剑影中更发出彩虹一般的晕光，闪烁流动，游走不定。\n"NOR, me);
        me->set("marks/xiaoyao","wait3");   

	}
	
	if(local[2] >= 2 && local[2] < 4 &&  me->query("marks/xiaoyao")== "wait3" )
	{
		write(HIY"你抬头一看，原来皓月西沉，已经落到了西首峭壁之后，峭壁上有一洞孔，月光\n"
		         "从洞孔彼端照射过来，东空中隐隐有彩光流动。但见宝剑所在洞孔离地高达数十丈，\n"
		         "不由得心下大奇，想要上去看个明白。\n"NOR, me);
		me->delete("marks/xiaoyao");
		me->set("marks/xiaoyao","get_book");

	}

//白天来开始等候
    if(local[2] >= 4 && local[2] < 18 )
		//&&  me->query("marks/xiaoyao")== "gotofind")
	{
        write(HIW"    仰望高崖，白云封谷，东西南北尽是悬崖峭壁，绝无出路。湖畔生着一丛丛的茶花，摇曳生姿。。\n"NOR, me);
        me->set("marks/xiaoyao","wait");
		me->start_busy(2);
	}
	
	if(local[2] >= 18 && local[2] < 21 
		&&  me->query("kar")>27
		&&  me->query("marks/xiaoyao")== "wait" )
	{
		write(HIC"    你站起身来，抬头只见月亮正圆，清光在湖面上便如同镀了一层白银一般，眼\n"
                 "光顺着湖面一路伸展出去，突然全身一震，只见对面玉璧上赫然有个人影在晃动！\n"NOR, me);
       me->set("marks/xiaoyao","wait1");         
	}

	if(local[2] >= 21 && local[2] < 23 &&  me->query("marks/xiaoyao")== "wait1" )
	{
		write(HIM"    你回过身来，只见身边小石壁上也有个人影，只是身形既小，影子也浓的多。登时恍\n"
		         "然大悟：“原来月亮先将我的影子映在这块小石壁上，再映到滆湖的大石壁上，当年确是\n"
		         "有人在这里舞剑，人影映上玉璧 ”。既明白了这个道理，百无聊赖之际，随即手舞足蹈，\n"
		         "拳打脚踢,心想最好现在有人也在崖顶，见到玉璧“仙影”，认定是仙人在演示绝世武功。\n"
		         "越想越是有趣，忍不住纵声大笑。\n"NOR, me);
                 me->set("marks/xiaoyao","wait2");   
	}


}

*/