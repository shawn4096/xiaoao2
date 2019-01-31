
#include <ansi.h>
#include <armor.h>

inherit WAIST;

#include "token.h"

void create()
{	
	set_name(HIR"��������"NOR, ({ "jade" }) );
	set_weight(100);
	set("long","��һ���ü�Ϊ������"HIR"��ϼ��"NOR"�Ƴ�����,��������һ�����������������ɷ\n�����ı�����һ������:\n");;
	set("unit", "��");
	set("value", 3000000);
	set("no_get",1);
	set("no_drop",1);
	set("armor_type", "token_waist");
	set("armor_prop/armor",15+random(20));
	set("armor_prop/parry",15+random(20));
	set("armor_prop/dodge",15+random(20));
	setup();

}

void init()
{
	add_action("do_discard","discard");
	token_reload();
}