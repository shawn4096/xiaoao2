// heixuezhen.c
// By sohu@xojhu 2014

#include <weapon.h>
#include <ansi.h>
inherit COMBINED_ITEM;
#include "/inherit/item/embed.h"
inherit THROWING;
inherit F_UNIQUE;

#define player_use "yes"

void create()
{
	set_name(HIB"��Ѫ����" NOR, ({ "heixue shenzhen", "zhen" ,"needle", "shenzhen", }));
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һö���������з�����ϸ�룬��ɢ���������ȳ�����һ����֪������ι�о綾��\n"+
			"������������ش���������ʿ����ɥ���ĺ�Ѫ���롣\n");
		set("unit", "��");
		set("no_sell", 1);
		set("value", 200);
		set("base_unit", "ö");
		set("base_weight", 100);
		set("material", "steel");
		set("damage", 20);
		set("poison", "heixue_poison");
		set("embed", 1);
	}
	set_amount(100);
	init_throwing(50);
	setup();
}

void init()
{
	add_action("action", "throw");
}
/*
int action()
{
	object me = this_player();
	object ob = this_object();

	if( !living(me) ) {
		write("���齣��������������Ū�����ģ�\n");
		return 1;
	}

	if( me->query("family/family_name") != "��Ĺ��" && player_use == "no" ) {
		write("��Ĺ�ɵ�"+ob->name()+"�ɲ�����ô��ʹ��С�ı��˵��Լ�����\n");
		return 1;
	}

	if( me->query("family/family_name") != "��Ĺ��" ) {
		if( wizardp(me) ) tell_object(me, "��ܵ�ù��ϵͳ���Զ�ɾ��"+ob->name()+"�Ķ��ԡ�\n");
		ob->delete("poison");
		ob->set("long", "�����������ϸ��ë���Ľ��룬���ɻƽ��ĳɾ��֣������β����\n"+
                            "��Һ��������ȻϸС������ƽ���أ�����ʱ�Կɼ�Զ����������Ч���Ѿ��������ˡ�\n");
	} else {
		if( wizardp(me) ) tell_object(me, "���������ϵͳ�Զ�������"+ob->name()+"�Ķ��ԡ�\n");
		ob->set("poison", "bee_poison");
		set("long", "�����������ϸ��ë���Ľ��룬���ɻƽ��ĳɾ��֣������β����\n"+
			"��Һ��������ȻϸС������ƽ���أ�����ʱ�Կɼ�Զ��\n");
	}
	return 0;
}
*/