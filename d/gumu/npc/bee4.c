// bee3.c  By River 98/09
//edit by sohu@xojh ������ʹ��乥����ָ��
inherit NPC;
#include <ansi.h>
//#include "bee3.h"
void create()
{
        set_name("�۷�", ({ "mi feng", "bee","feng" }) );
        set("race", "Ұ��");
        set("age", 4);
        set("long", "һֻ�ɰ����۷䣬Ұ��Ұ����\n");
        set("attitude", "peaceful");         

        set("str", 20);
        set("con", 30);

        set("limbs", ({  "����",  "���" , "ͷ��" }) );
        set("verbs", ({ "bite" }) );

        set("combat_exp", 50000);

        set_temp("apply/attack", 35);
        set_temp("apply/damage", 23);
        set_temp("apply/armor", 24);

        setup();
}

