// By Spiderii@yt bt��Ʒ
#include <ansi.h>
inherit SPEC;
void create()
{
	set_name(HIW"���ر���"NOR, ({ "box","baohe" }) );
	set_weight(10);
	set("unit", "��");
	set("long", "һ�����ص���ʺ��ӡ�\n�Ǵ�˵���������Ա���䷲��ı�������ܸ����Ǵ������˺Ͷ��˵�ħ��֮�С�\n�ǲ��Ǿ����������ջ��أ��ǾͿ�򿪣�open�����ɡ�����\n");
	set("value", 0);
	set("material", "wood");
	set("no_drop", "�������صĶ�����ô������Ҷ��ء�\n");
	set("no_get", "�������������뿪�Ƕ���\n");
	set_weight(100);
	set("value",3000000);
	set("treasure",1);
	set("degree",1);
	set("flag","spec/baohe");
	set("desc","��˵�򿪺��ӻ��б�����֡�");
	set("credit",3000);  

	setup();
}
void init()
{
	add_action("do_open", "open");
}

int do_open(string arg)
{        
	int i,j;
	object me = this_player();
	object obj;
	if (me->query("combat_exp") < 5000000)
	{
		return notify_fail("С���Ӳ�Ҫ�ҿ����\n");
	}
	if(arg!="box" && arg!="baohe")
		return notify_fail("��Ҫ��ʲô?\n");
	i = random(4)?4:5 ;
	obj = new("/clone/zhiye/othermaterial");
	if(obj && obj->set_level(i+1))
	{
		obj->move(this_player());
		message_vision(HIW"$N�ӱ����еõ���һ"+obj->query("unit")+obj->name()+"��\n\n"NOR,me); 
	}
	destruct(this_object());
	return 1;  
}