 //wine.c 2009 By fengyue
#include <ansi.h>

 
inherit SPEC; 

void create()
{
        set_name (HIG"猴儿酒"NOR, ({ "houer jiu", "jiu" }));
        set("long","这是一坛由山中猴儿采用山中野果酿制的酒，俗称"+HIG"猴儿酒"NOR"，常喝(he)有助于内力的培育。\n");
        set("unit","小坛");
        set_weight(100);
        set("value",3000000);
        set("no_give",1);
        set("no_drop",1);
        set("no_cun",1);
        set("degree",1);
        set("flag","spec/wine");
        set("desc","舒筋活血，气血旺盛。");
        //set("credit",2000);
		setup();
} 
 
void init()
{
        add_action("do_he","he");
   
}
 
int do_he(string arg)
{
        object me=this_player();
        
        if (me->query_temp("wine_power"))  return notify_fail("酗酒有害身体健康！本次登陆你已经不能再多喝了！\n");

		if (arg!="houer jiu" && arg!="jiu")
                 return notify_fail("你要喝什么?\n");
        if (!restrict()) return notify_fail("酗酒有害身体健康！本周你已经不能再多喝了！\n");
        
        me->add_temp("apply/force",100);
		//me->add_temp("apply/dodge",100);
        //me->add_temp("apply/parry",100);
        me->add_temp("apply/damage",100);
		//me->add_temp("apply/damage",100);
        me->add_temp("apply/attack",100);
		me->set("neili",me->query("max_neili")*2-1);

		me->set_temp("wine_power",1);
		write(HIY"你掏出了一小坛"HIG"猴儿酒"HIY"，咕咚咕咚的仰头灌了下去！\n"NOR); 
		write(HIY"只觉一股酒气透四肢百骸，你顿觉精力弥漫，劲气汹涌不绝！\n"NOR); 
        degree();
        return 1;
}    
