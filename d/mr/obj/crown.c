// cloth3.c

#include <armor.h>
#include <ansi.h>

inherit HEAD;

void create()
{
	set_name(HIY "�Ͻ��" NOR, ({ "zijin guan", "crown" , "guan"}) );
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "����һ��ɢ���ŵ���ɫ�ʹڣ��ɴ��������ɣ�һ�����������Զ֮�\n");
		set("unit", "��");
		set("material", "gold");
        set("value",1000000);
		set("armor_prop/armor", 50 );
		set("wear_msg","$N��$n�������ͷ�ϡ�\n");
		set("remove_msg","$N��$n��ͷ��ժ��������\n");
	}
	setup(); 
}
