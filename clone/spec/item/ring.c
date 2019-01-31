
#include <ansi.h>
#include <armor.h>

inherit FINGER;

#include "token.h"

string t_power(int i)
{
	if( i >= 90 )	return HIM"��ɫ������(����)"NOR;
	if( i >= 70 )	return HIR"��ɫ������(�߼�)"NOR;	
	if( i >= 50 )	return HIY"��ɫ������(�ܺ�)"NOR;
	if( i >= 40 )	return HIC"��ɫ������(����)"NOR;		
	if( i >= 30 )	return HIW"��ɫ������(һ��)"NOR;		

	return "��ֵһ��";
}

void create()
{	
	int i;
	set_name(HIW"�׽����"NOR, ({ "ring" }) );
	set_weight(100);
	set("unit", "��");
	set("value", 3000000);
	set("no_get",1);
	set("no_drop",1);
	set("armor_type", "token_finger");
	set("armor_prop/armor",15+random(20));
	set("armor_prop/parry",15+random(20));
	set("armor_prop/dodge",15+random(20));
	i=this_object()->query("armor_prop/armor")+this_object()->query("armor_prop/parry")+this_object()->query("armor_prop/dodge");
	set("long","һ��"HIW"�׽�"NOR"�ƳɵĽ�ָ,������һ��˶���"HIW"��ʯ"NOR"��ҫ�����˶�Ŀ�Ĺ�ʡ�\n������ο������ۺ�����Ϊ"+t_power(i)+"\n��������Ȧ����һ������:\n");

	//write("i="+i);
	setup();

}

void init()
{
	add_action("do_discard","discard");
	token_reload();
}