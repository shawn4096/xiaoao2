//flowray 2005.6.16
#include <ansi.h>

inherit SPEC;


void create()
{
	set_name (HIY"��ع����"NOR, ({ "wcard","vip card","card"}));
	set("long","��ʾ(show)���Ź����,�������ɵĳ�����ء�\n");

	set("unit","��");
	set_weight(100);
	set("value",3000000);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);
	set("degree",30);
	set("flag","spec/wcard");
	set("rest",30);
	set("desc","���Ե����ϴ�衣");
	set("credit",500);
	setup();
}

void init()
{
	add_action("do_show","show");   
}

int do_show(string str)
{
	object env,me = this_player();
	string path;
	
	if (!restrict()&& !me->query("buyvip")) {return notify_fail("�������Ѿ�����ʹ��"+this_object()->query("name")+"�ˡ�\n");}
	if (!str)
		return notify_fail("��Ҫ��ʾʲô��\n");
    	
	if ( str != "card")
		return notify_fail("��Ҫ��ʾʲô��\n");
    
	env=environment(me);	
	path=file_name(env);
	
	if (path != "/d/changan/qingchi")
		return notify_fail("û����ʲô��,����Ϊ��Ŀ��ܿ�ѽ��\n");
		
	if (me->query_tmp("pay_wash"))
		return notify_fail("СѾ��˵�������㻹�ǿ���ȥϴ��ɣ���\n");
		
	me->set_temp("pay_wash",1);
	write(HIY"���������ó��������СѾ����ǰ���˻Ρ�\n"NOR);
	write("СѾ��˵������ԭ���ǹ�ͼ���,����������\n");
	
	degree();
	
	return 1;
}	 