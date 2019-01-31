// shuzhi.c 小树枝 For hubo quest by lsxk@hsbbs 2007/7/20
#include <ansi.h>

inherit SPEC; 

void create()
{
    set_name (HIC"小树枝"NOR, ({ "xiao shuzhi"}));
    set("long",HIY"这是一根普通的小树枝,小孩子们都喜欢用它来在地上画画(hua).\n"NOR);

    set("unit","根");
	set_weight(100);
	set("value",3000000);
	
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("treasure",1);
    set("degree",1);
    set("flag","spec/shuzhi");
    set("rest",3);
    set("desc","据说是老顽童自创武功时用过的东西!");
    set("credit",300);
	setup();
}

void init()
{
    add_action("do_hua","hua");
  
}

int do_hua(string arg)
{
	object me=this_player();
	
	    
    if (arg!="fangyuan" && arg!="方圆"){
              message_vision(HIW"$N像小孩子一样"HIC"小树枝"HIW"在地上画着叉叉.无聊极了....\n"NOR,me);
              return 1;
    }
      	
	if (!restrict()&& !me->query("buyvip")) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}

    me->set_temp("sj_credit/quest/public/hubo",1);
    message_vision(HIR"$N心血来潮,将"HIC"小树枝"HIR"折成两枝,左手拿一枝画方,右手拿一枝画圆,竟然画出了一个正方和一个浑圆!\n"+
    HIY"虽然,正方是$N的右手画出来的,而圆却是$N的左手画出来的......\n"NOR,me);
    message_vision(HIG"$N生气地撅了撅嘴,一把就将小树枝远远地仍了出去!\n"NOR,me);
	degree();
	return 1;
}	 
