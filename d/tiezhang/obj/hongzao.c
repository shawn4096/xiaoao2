// hongzao.c �����

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(HIR"�����"NOR, ({"hong zao", "zao"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���ֺ������ִ�Ĵ���档\n");
		set("unit", "��");
		set("value", 30);
		set("food_remaining", 3);
		set("food_supply", 1);
	}
}/*
int init()
{
	add_action("do_chi","eat");

}

int do_chi(string arg)
{
	object zaohe;
	object ob=this_object();
	object me=this_player();
	if (!arg || arg !="zao")
	{
		return notify_fail("��Ҫ��ʲô��\n");
	}
	ob->add("food_remaining",-1);
	if (ob->query("food_remaining")<0)
	{
		zaohe=new("d/tiezhang/obj/zaohe");
		zaohe->move(me);
	}
	return 1;

}*/