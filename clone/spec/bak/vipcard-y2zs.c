//modified by action 2009/2/17
#include <ansi.h>

inherit SPEC; 

void create()
{
	set_name (HIM"�����(ת��������������)"NOR, ({ "vipcard"}));
	set("long","����һ���齣ר�õ�"HBRED"����������ת����"NOR"���������������齣����ҽ��г�ֵ("HIY"credit vip"NOR")��\n");

	set("unit","��");
	set_weight(200);
	set("value",3000000);
	set("no_drop",1);	
	set("no_get",1);
	set("degree",1);
	
	set("no_cun",1);
	set("flag","spec/vipcard");
    set("desc","��ֵһ��Ĺ��VIP,ʹ�ú󷵻�10000ͨ����2000�ƽ�");
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


	me->set("registered", 3); 
	//������
	me->set("buyvip", 1); 
	me->set("vip/vip_start_time",time());    
	me->set("vip/vip_time",time());       

	me->add("vip/vip_time",5*365*24*3600);
	me->add("SJ_Credit",63000);
	me->add("balance",20000000);
	//me->add("balance",20000000);
	//me->set("y-card-vip",1);
	write(HIY"\n�㽫"HIW"����������ת����"NOR+HIY"���齣�Զ��տ����һˢ\n"NOR);
	if (me->query("y-card-vip"))
	{
		write(HIC"ע�⣬��Ϊ������������������꿨��Ǳ�ȡ����\n");
		me->delete("y-card-vip");
	}
	if (me->query("m-card-vip"))
	{
		write(HIC"ע�⣬��Ϊ������������ң���������¿���Ǳ�ȡ����\n");
		me->delete("m-card-vip");
	}
   // write(HIY"\����齣ͨ��������������ǧ����\n"NOR);
    //write(HIY"\n������д�������˷�ǧ����\n"NOR);
	write(HIW"\n�齣�Զ�ϵͳΪ���������õĹ��VIP��Ŀǰ�ȼ�Ϊ"HIR"��"HIW",������"HIB"time"HIW"�鿴����л�Ķ��齣��֧�֡�\n"NOR);
	degree();
	return 1;
}	 
