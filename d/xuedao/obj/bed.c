// bed.c �ϻ���
// by sohu@xojh
inherit ITEM;
#include <ansi.h>


void create()
{
	set_name(MAG"�ϻ���"NOR,({"hehuan chuang","bed","chuang"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "��ϰ��ϲ��ר�õĺϻ������������˺����ޱ���\nһ��ѩ�׵�Ů����������ſ���ޱ��г���ճյ�Ц�ţ��������֡�\n");
		set("unit", "��");
		set("no_get", 1);
		set("no_drop",1);
		set("no_sell", 1);

		set("value", 100000);
	//	set("remaining", 5);
	//	set("drink_supply", 30);
	}
	setup();
}
