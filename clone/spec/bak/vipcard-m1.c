//modified by action 2009/2/17
#include <ansi.h>

inherit SPEC; 

void create()
{
	set_name (HIW"�����(�¿�)"NOR, ({ "mcard"}));
	set("long","����һ���齣ר�õ�"HBRED"�����ֵ��"NOR"���������������齣����ҽ��г�ֵ("HIY"credit vip"NOR")��\n");

	set("unit","��");
	set_weight(200);
	set("value",3000000);
  set("no_drop",1);	
  set("no_get",1);
	set("degree",1);
	set("no_cun",1);
	set("flag","spec/vipcard");
       set("desc","��ֵһ���¹��VIP,ʹ�ú󷵻� 1000ͨ�� 10�ƽ�");
  set("credit",1200);       
	setup();
}

void init()
{
	add_action("do_credit","credit");
  
}

int do_credit(string arg)
{
	object me=this_player();
	object gold;
	    
	if (!arg)
      		return notify_fail("��Ҫ��ֵʲô?\n");
      		
	if (arg!="vip")
      		return notify_fail("��Ҫ��ֵʲô?\n");     	      		


	if( me->query("registered")<=3 )
		me->set("registered", 3);    
    if (me->query("m-card-vip"))
	{
		write(HIC"ע�⣬��Ϊ�����Ѿ����¿�����ˡ�\n");
		return 1;
	}
	me->delete("freeuser");
	me->set("vip/vip_start_time",time());    
	me->set("vip/vip_time",time());                                       ;
	me->add("vip/vip_time",30*24*3600);
	//me->add("balance",10000);
	me->add("SJ_Credit",100);
	me->set("m-card-vip",1);
	me->set("registered",3);
	write(HIY"\n�㽫"HIW"�����ֵ��"NOR+HIY"���齣�Զ��տ����һˢ\n"NOR);
	
	if (me->query("buyvip"))
	{
		write(HIC"ע�⣬��Ϊ�������¿���������������Ǳ�ȡ����\n");
		me->delete("buyvip");
	}
	if (me->query("y-card-vip"))
	{
		write(HIC"ע�⣬��Ϊ�������¿�����������꿨��Ǳ�ȡ����\n");
		me->delete("y-card-vip");
	}
	
	write(HIW"\����齣ͨ��������ҼǪ����\n"NOR);
	write(HIY"\��Ĵ��������ʰ���ƽ�\n"NOR);
	write(HIW"\n�齣�Զ�ϵͳΪ��������ʮ��Ĺ��VIP��3������������"HIB"time"HIW"�鿴����л���齣��֧�֡�\n"NOR);
	degree();
	return 1;
}	 
