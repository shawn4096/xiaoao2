//modified by action 2009/2/17
#include <ansi.h>

inherit SPEC; 

void create()
{
	set_name (HIM"贵宾卡(转换荣誉终身贵宾卡)"NOR, ({ "vipcard"}));
	set("long","这是一张书剑专用的"HBRED"荣誉终身贵宾转换卡"NOR"，他可以用来给书剑的玩家进行充值("HIY"credit vip"NOR")。\n");

	set("unit","张");
	set_weight(200);
	set("value",3000000);
	set("no_drop",1);	
	set("no_get",1);
	set("degree",1);
	
	set("no_cun",1);
	set("flag","spec/vipcard");
    set("desc","充值一年的贵宾VIP,使用后返还10000通宝，2000黄金");
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


	me->set("registered", 3); 
	//终身标记
	me->set("buyvip", 1); 
	me->set("vip/vip_start_time",time());    
	me->set("vip/vip_time",time());       

	me->add("vip/vip_time",5*365*24*3600);
	me->add("SJ_Credit",63000);
	me->add("balance",20000000);
	//me->add("balance",20000000);
	//me->set("y-card-vip",1);
	write(HIY"\n你将"HIW"荣誉终身贵宾转换卡"NOR+HIY"往书剑自动收款机里一刷\n"NOR);
	if (me->query("y-card-vip"))
	{
		write(HIC"注意，因为现在是终身，所以你的年卡标记被取消了\n");
		me->delete("y-card-vip");
	}
	if (me->query("m-card-vip"))
	{
		write(HIC"注意，因为现在是终身玩家，所以你的月卡标记被取消了\n");
		me->delete("m-card-vip");
	}
   // write(HIY"\你的书剑通宝增加了七万五千个。\n"NOR);
    //write(HIY"\n你的银行存款增加了贰千两。\n"NOR);
	write(HIW"\n书剑自动系统为您增加永久的贵宾VIP，目前等级为"HIR"五"HIW",请输入"HIB"time"HIW"查看，感谢的对书剑的支持。\n"NOR);
	degree();
	return 1;
}	 
