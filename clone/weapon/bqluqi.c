// luqi.c �������

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIG"�����"NOR,({"luqi qin","luqi","qin"}));
        set_weight(1000);
        if(clonep())
                set_default_object(__FILE__);
        else{
                set("unit","��");
                set("value",1000);
                set("material","bamboo");
               // set("unique", 1);
                set("rigidity", 6);
				set("qinjian",1);
                //set("treasure",1);
				set("value", 260000);
                set("long","�������������ɫ���ɣ�����������������ǧ�����ϵĹ����˵����˾��������\n");
                set("wield_msg",GRN"$N����һ�������������������,�������ϲ��˼��¡�\n"NOR);
                set("unwield_msg",GRN"$N����һת������ͣ��������\n"NOR);
        }
        init_sword(80);
        setup();
}
