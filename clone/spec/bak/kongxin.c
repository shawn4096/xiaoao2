//flowray 2005.6.16
// By Spiderii@ty 修正效果
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (WHT"空心散"NOR, ({ "kongxin san","kongxin","san"}));
	set("long","这是一包峨眉山秘传的"WHT"空心散"NOR"，所谓"HIW"【无我无他，无相无色，空心静音，涤垢凡尘】"NOR"
你可以服("HIY"fu"NOR")下它解除琐事的困扰。\n");

	set("unit","包");
	set_weight(100);
	set("value",3000000);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);
        set("degree",25);
	set("flag","spec/kongxin");
	set("desc","消除任务繁忙状态。");
        set("rest",200);
        set("credit",20);
	setup();
}

void init()
{
	add_action("do_eat","eat");
	add_action("do_eat","fu");    
}

int do_eat(string arg)
{
	object me=this_player();
	
	if (!arg)
		return notify_fail("你要服用什么?\n");
	    
	if (arg!="kongxin" && arg!="san")
      		return notify_fail("你要服用什么?\n");
      	
	if (!restrict()&& !me->query("buyvip")) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}
    
	if (!me->query_condition("job_busy") )
		return notify_fail("你现在不需要服用空心散。\n");
	
	me->clear_condition("job_busy");
	
	//增加针对一些旧结构的job busy的处理
	me->clear_condition("gb_job_busy");
	me->clear_condition("gumu_job");
	me->clear_condition("hs_job");
	me->clear_condition("lh_job");
	me->clear_condition("mrhua_busy");
	me->clear_condition("mr_job");
	me->clear_condition("sljob");
	me->clear_condition("sl_job_busy");
	me->clear_condition("thd_job");
	me->clear_condition("wd_job");
	me->clear_condition("wait_mr_job");
	me->clear_condition("wait_xx_job");
	me->clear_condition("xs_job");

	
	write("你服下一些"WHT"空心散"NOR"觉得心宁气定,把江湖琐事忘得一干二净!\n");
	degree();
	return 1;
}	 
