// heijian.c
//ʯ��ר���� 

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
	set_name(HIW"�׽�"NOR,({ "bai jian", "jian", "sword" }) );
	set_weight(8000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��"HIW"�׽�"NOR"��ͨ�巺�׹⣬�˺ڰ�˫��������ר����\n������ɭ�����뼡������Ȼ��һ�ں�����ϡ��������\n"NOR);
		set("value", 1);
		set("rigidity", 5);
		set("sharpness", 5);
		set("unique", 1);
		set("treasure", 1);
		set("material", "steel");
		set("weapon_prop/parry", 20);
		set("wield_neili", 500);
		set("wield_maxneili", 800);
		set("wield_str", 25);
		set("wield_msg", HIM"����$N�ӳ������֣�$n"HIM"������һĨ�к硣\n"NOR);
		set("unwield_msg", HIY"$N��һ�У�$n"HIY"�û���һ�����磬���ƹ��ư׺װ���ʧ�ˡ�\n" NOR);
	}
	init_sword(130);
	setup();
}