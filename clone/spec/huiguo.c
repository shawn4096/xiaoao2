//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (HIM"�ڹ�����"NOR, ({ "sarira"}));
	set("long","����һ����������Ħ���"HIM"ָ��������"NOR"����˵�������ڹ�("HIY"pray sarira"NOR")�����˻ڹ����¡�\n");

	set("unit","��");
	set_weight(100);
	set("value",3000000);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);
	set("degree",1);
	set("flag","spec/sarira");
        set("rest",1);
	set("desc","����ϴ�ĸ��档");
        set("credit",5000);
	
	setup();
}

void init()
{
	add_action("do_pray","pray");
  
}

int do_pray(string arg)
{
	object me=this_player();
	    
	if (!arg)
      		return notify_fail("��Ҫ�ڹ�ʲô?\n");
      		
	if (arg!="sarira")
      		return notify_fail("��Ҫ�ڹ�ʲô?\n");
      	
      	if (me->query("shen")>0)
      		return notify_fail("�㲻���Ѿ�ϴ�ĸ�����?\n");
      		
      	if (!restrict()) {return notify_fail("�������Ѿ�����ʹ��"+this_object()->query("name")+"�ˡ�\n");}   


	me->set("shen",100);
	me->apply_condition("job_busy",40);// 15���� ����Ƶ�������л�
	
	write(HIY"���"HIM"�ڹ�����"HIY"��������ڶ�ǰ��ĬĬ����������Ĵ����ʧ......\n"NOR);
	write(HIW"������Լ�������������ˡ�\n"NOR);
	degree();
	return 1;
}	 
