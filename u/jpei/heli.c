//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
        set_name (HIR"�»����"NOR, ({ "gift","he li"}));
        set("long","����һ����̴Master���͵�"HIR"�»����"NOR"����֪��װ��Щʲô����������Բ�(chai gift)��һ��\n");

	set("unit","��");
	set_weight(100);
	set("value",3000);
        set("no_give",1);
        set("no_drop",1);
	set("flag","spec/ebook1");
        set("degree",1);
        set("desc","�»����");
        set("credit",1);
	setup();
}

void init()
{
	add_action("do_read","chai");
  
}

int do_read(string arg)
{
	object me=this_player();
	    
	if (!arg)
      		return notify_fail("��Ҫ��ʲô?\n");
      		
	if (arg!="gift")
      		return notify_fail("��Ҫ��ʲô?\n");
      	
      		
     if(me->query("buyvip")){
                 me->add_condition("db_exp", 1000);
                 me->add_temp("apply/attack",100);
                 me->add_temp("apply/damage",100);
}
 


  	else
                me->add_condition("db_exp", 1000);
	
        write(HIY"���"HIR"����"HIY"һ���������Ȼװ�˰��שͷ�����ɵ����´�ŭ��\n"NOR);

	degree();
	return 1;
}	 
