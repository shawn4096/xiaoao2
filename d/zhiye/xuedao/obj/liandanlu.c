// qinxiu-jiasha.c
 
#include <ansi.h> 
//#include <armor.h> 
 
inherit ITEM; 
 
void create() 
{ 
        set_name( RED "����¯" NOR, ({ "liandan lu", "lu" }) ); 
        set_weight(1000); 
        if( clonep() ) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "��"); 
                set("long", "����һ�����ص�����¯����Ѫ����˽�в�Ʒ�������������Ǵ���¯�з�����\n"); 
                set("value", 100000); 
				set("no_get", 1); 
				set("no_give", 1); 
				set("no_sell", 1); 
                set("material", "steel"); 
                set("armor_prop/armor", 50); 
        } 
        setup(); 
} /*
void init()
{
	add_action("do_open","open");
	add_action("do_cloese","close");
	//add_action("do_jilian","jilian");
	add_action("do_liandan","liandan");

}
int do_open(string arg)
{
	object me;
	me=this_palyer();
	if (!arg||arg!="lu")
	{
		return notify_fail("��Ҫ��ʲô��");
	}
	if (query_temp("open"))
	{
		return nofiy_fail("��¯�Ѿ�����\n");
	}
	this_object()->set_temp("poen",1);
	tell_object(me,"�������¯��\n");
	return 1;
}
int do_close(string arg)
{
	object me;
	me=this_palyer();
	if (!arg||arg!="lu")
	{
		return notify_fail("��Ҫ����ʲô��");
	}
	if (query_temp("close"))
	{
		return nofiy_fail("��¯�Ѿ��Ǻ���\n");
	}
	this_object()->set_temp("close",1);
	tell_object(me,"�㽫����¯�Ǻá�\n");
	return 1;
}

int do_liandan(string arg)
{
	object me;
	me=this_palyer();
	if (!arg)
	{
		return notify_fail("��Ҫ��ʲô��");
	}
	if (arg=="��¶��")
	{
	}
	if (arg=="������")
	{
	}


	if (query_temp("close"))
	{
		return nofiy_fail("��¯�Ѿ��Ǻ���\n");
	}
	this_object()->set_temp("close",1);
	tell_object(me,"�㽫����¯�Ǻá�\n");
	return 1;
}
*/