//modified by action 2009/2/17
#include <ansi.h>

inherit SPEC; 

void create()
{
	set_name (HIW"�����(���꿨)"NOR, ({ "ycard"}));
	set("long","����һ���齣ר�õ�"HBRED"�����ֵ��"NOR"���������������齣�������һ��("HIY"credit vip"NOR")��\n");

	set("unit","��");
	set_weight(200);
	set("value",3000000);
  set("no_drop",1);	
  set("no_get",1);
	set("degree",1);
	
	set("no_cun",1);
	set("flag","spec/vipcard");
        set("desc","��һ��Ĺ��VIP,����ʾ��ݶ��ѡ�\n");
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
      		return notify_fail("��Ҫ��ֵʲô?\n");
      		
	if (arg!="vip")
      		return notify_fail("��Ҫ��ֵʲô?\n");     	      		

    me->delete("freeuser");
	me->set("registered", 3);    
	me->set("vip/vip_start_time",time());    
	me->set("vip/vip_time",time());       

	me->add("vip/vip_time",365*24*3600);
	//me->add("SJ_Credit",12000);
	//me->add("balance",10000000);
	me->set("y-card-vip",1);
	write(HIY"\n�㽫"HIW"�����ֵ��"NOR+HIY"���齣�Զ��տ����һˢ\n"NOR);
	
	if (me->query("buyvip"))
	{
		write(HIC"ע�⣬��Ϊ�������꿨��������������Ǳ�ȡ����\n");
		me->delete("buyvip");
	}
	if (me->query("m-card-vip"))
	{
		write(HIC"ע�⣬��Ϊ�������꿨����������¿���Ǳ�ȡ����\n");
		me->delete("m-card-vip");
	}
      //  write(HIY"\����齣ͨ��������һ����ǧ����\n"NOR);
        //write(HIY"\n������д��������Ҽǧ����\n"NOR);
	write(HIW"\n�齣�Զ�ϵͳΪ������������ʮ����Ĺ��VIP��Ŀǰ�ȼ�Ϊ"HIR"��"HIW",������"HIB"time"HIW"�鿴����л�Ķ��齣��֧�֡�\n"NOR);
	degree();
	return 1;
}	 
