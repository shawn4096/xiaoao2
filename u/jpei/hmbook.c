#include <ansi.h>

inherit SPEC; 

void create()
{
	set_name (HIR"��������ؼ�"NOR, ({ "hmbook"}));
	set("long",HIR"����һƬ��Ͱ͵���ֽƬ��ֽƬ�Ѿ����ƣ����������Ȼģ�����塣\n"NOR);

	set("unit","Ƭ");
	set_weight(100);
	set("value",3000000);

	set("no_give",1);
	set("no_drop",1);	
	set("no_get",1);
	set("no_cun",1);

	set("degree",1);
	set("flag","spec/suizhi");
	set("rest",10);
	set("desc","��˵��¼��ŷ����ĸ�������޵��ؼ�!");
	set("credit",600);
	setup();
}

void init()
{
	add_action("do_chakan","chakan");
}

int do_chakan(string arg)
{
	mapping fam;
	object me = this_player();
	fam = me->query("family");

	if (arg!="hmbook" )
		return notify_fail("��Ҫ�鿴ʲô?\n");
	if ( me->query("combat_exp") < 800000)
		return notify_fail("�㻹��ץ��ʱ��ȥ���ӵ㽭�������ɣ�800Kǰ��û����İ���\n");

	if (!restrict()) 
	{ 
		return notify_fail("�Ⱳ�����Ѿ�������ʹ��"+this_object()->query("name")+"�ˡ�\n");
	}

	if (me->query_skill("hamagong", 1) > 350 &&
	me->query("oyf_son") &&   
	me->query("oyf/hamagong") == 2 &&
	random((int)me->query("kar")) > 25 && 
	random(me->query("con")) > 22 && 
	me->query("max_neili") > 7500  &&
	me->query("neili") > 15000  &&
	me->query("combat_exp") > 2000000)
	{
		me->add("oyf/hamagong",1);
		me->set("title",HIW"����ɽׯ"BLU"����"HIW"����"NOR); 

		write(HIR"ֽƬ���ʲݵ�д���������ʵ������ģ�����ĸ����ô�ܽи���أ���Ӧ�ýи�󡾫�ˣ� \n"NOR,);
		write(HIR"ֽƬ���ʲݵ�д����ԭ����ˣ�ԭ����ˣ� \n"NOR,);
		log_file("quest/hama", sprintf("%-18sͨ��ͨ����Ʒ�õ����3���ᣬ��%d��\n",me->name(1)+"("+capitalize(getuid(me))+")", me->query("kar")), me);
		return 1; 
	}	 
         
	write(HIW"�㷴���鿴����"HIR"��ֽƬ"HIW"��ϣ���ܴ�����鵽��ʲô��ͻȻ������ģ�����ֵ�ӳ���������������"HIR"��󡲻������ô�ܽи����..."HIW"��!\n"NOR);
	degree();
	return 1;
}
