//qin.c ��ͨ������

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
	set_name("ľ��",({"mu qin","qin", "muqin"}));
	set_weight(10000);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("unit","��");
		set("value",3000);
		set("material","wood");
		set("unique", 1);
		set("rigidity", 1);
		set("treasure",1);
		set("qinjian",1);
		set("long","����һ����䳣�õ�ľ�������١�\n");
		set("wield_msg",HIY"$N������$n���Դ˰��˼��£��������˵�������\n"NOR);
		set("unwield_msg",HIY"$Nʮָһ��������ҷȻ��ֹ��\n"NOR);
	}
	init_sword(10);
	setup();
}
