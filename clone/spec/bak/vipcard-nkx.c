//modified by action 2009/2/17
#include <ansi.h>

inherit SPEC; 

void create()
{
	set_name (HIW"贵宾卡(续年卡)"NOR, ({ "ycard"}));
	set("long","这是一张书剑专用的"HBRED"贵宾充值卡"NOR"，他可以用来给书剑的玩家续一年("HIY"credit vip"NOR")。\n");

	set("unit","张");
	set_weight(200);
	set("value",3000000);
  set("no_drop",1);	
  set("no_get",1);
	set("degree",1);
	
	set("no_cun",1);
	set("flag","spec/vipcard");
        set("desc","续一年的贵宾VIP,仅标示身份而已。\n");
  set("credit",10000);       
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

    me->delete("freeuser");
	me->set("registered", 3);    
	me->set("vip/vip_start_time",time());    
	me->set("vip/vip_time",time());       

	me->add("vip/vip_time",365*24*3600);
	//me->add("SJ_Credit",12000);
	//me->add("balance",10000000);
	me->set("y-card-vip",1);
	write(HIY"\n你将"HIW"贵宾充值卡"NOR+HIY"往书剑自动收款机里一刷\n"NOR);
	
	if (me->query("buyvip"))
	{
		write(HIC"注意，因为现在是年卡，所以你的终身标记被取消了\n");
		me->delete("buyvip");
	}
	if (me->query("m-card-vip"))
	{
		write(HIC"注意，因为现在是年卡，所以你的月卡标记被取消了\n");
		me->delete("m-card-vip");
	}
      //  write(HIY"\你的书剑通宝增加了一万两千个。\n"NOR);
        //write(HIY"\n你的银行存款增加了壹千两。\n"NOR);
	write(HIW"\n书剑自动系统为您增加三百六十五天的贵宾VIP，目前等级为"HIR"四"HIW",请输入"HIB"time"HIW"查看，感谢的对书剑的支持。\n"NOR);
	degree();
	return 1;
}	 
