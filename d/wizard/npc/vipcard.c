//modified by action 2009/2/17
#include <ansi.h>

inherit SPEC; 

void create()
{
	set_name (HIW"贵宾充值卡"NOR, ({ "vipcard"}));
	set("long","这是一张书剑紫檀专用的"HBRED"贵宾充值卡"NOR"，他可以用来给书剑的玩家进行充值("HIY"credit vip"NOR")。\n");

	set("unit","张");
	set_weight(200);
	set("value",3000000);
    set("no_give",1);
    set("no_drop",1);	
    set("no_get",1);
    set("no_cun",1);
	set("degree",1);
	set("flag","spec/vipcard");
    set("desc","可以为你的账号充值一年的贵宾VIP。");
	//set("credit",1000);
    set("SJ_Credit",50000); //临时测试用      
	setup();
}

void init()
{
	add_action("do_credit","credit");
  
}

int do_credit(string arg)
{
	object me=this_player();
	    
	if (!arg)
      		return notify_fail("你要充值什么?\n");
      		
	if (arg!="vip")
      		return notify_fail("你要充值什么?\n");     	      		


	  //me->set("registered", 3);    
      me->set("vip/vip_time",time());
	  me->set("y-card-vip",1);
      me->add("vip/vip_time",365*24*3600);
      me->set("vip/vip_start_time",time());    
      me->set("use_vipcard",1);    
	  write(HIY"\n你将"HIW"贵宾充值卡"NOR+HIY"往书剑自动收款机里一刷\n"NOR);
      write(HIW"\n书剑自动系统为您增加一年的贵宾VIP，请输入"HIB"time"HIW"查看，感谢的对书剑紫檀的支持。\n"NOR);
	  degree();
	return 1;
}	 
