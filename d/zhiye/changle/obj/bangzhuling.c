// bangzhuling.c ���ְ�����
// By sohu@xojh

#include <ansi.h>

inherit ITEM;
object ppl;

void create()
{
	set_name(HIW"������"NOR, ({ "bangzhu ling", "ling" }) );
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "stone");
		set("long", "һ�������֬�������ɵ����ƣ��������Σ����ĵ��һ�����֣�����д�ˡ����ְ���������֡�\n");
		set("value", 0);
		set("treasure",1);
		set("no_drop",1);
		set("no_cun",1);
		set("no_get",1);
		set("no_steal", 1);
	}
	setup();
}
