//flowray 2005.6.20
#include <ansi.h>


inherit SPEC; 

void create()
{
	set_name (MAG"��Ӣ֮��"NOR, ({ "ebook","book"}));
	set("long","����һ�������Ⱥ����͸����һ��"MAG"��Ӣ֮��"NOR"���Ķ�("HIY"read"NOR")����������ٳɳ���\n");

	set("unit","��");
	set_weight(100);
	set("value",3000);
    set("treasure",1);

	set("degree",1);
	if (this_player()->query("buyvip"))	
		set("rest",2);
	else 
		set("rest",1);
	set("no_give",1);
    set("no_drop",1);
	set("no_get",1);
	set("no_steel",1);
	set("flag","spec/ebook");
    set("desc","һ��ʱ���ھ���ӳɡ�");
    set("credit",1000);
	setup();
}

void init()
{
	add_action("do_read","read");
  
}

int do_read(string arg)
{
	object me=this_player();
	    
	if (!arg)
      		return notify_fail("��Ҫ��ʲô��?\n");
      		
	if (arg !="ebook")
			return notify_fail("eee��Ҫ��ʲô?\n"+arg);
      	
    
    if (!restrict()) 
	{
		return notify_fail("�������Ѿ�����ʹ��"+this_object()->query("name")+"�ˡ�\n");
	}   

	
	if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);

		else
                me->add_condition("db_exp", 10000);
	
	write(HIY"��ϸϸ�Ķ�"HIC"��Ӣ֮��"HIY"��������,��ʲô�����°빦����\n"NOR);

	degree();
	
	return 1;
}	 
