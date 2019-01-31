// bee3.c  By River 98/09
//edit by sohu@xojh 增加驱使玉蜂攻击的指令
inherit NPC;
#include <ansi.h>
//#include "bee3.h"
void create()
{
        set_name("蜜蜂", ({ "mi feng", "bee","feng" }) );
        set("race", "野兽");
        set("age", 4);
        set("long", "一只可爱的蜜蜂，野生野长。\n");
        set("attitude", "peaceful");         

        set("str", 20);
        set("con", 30);

        set("limbs", ({  "身体",  "翅膀" , "头部" }) );
        set("verbs", ({ "bite" }) );

        set("combat_exp", 50000);

        set_temp("apply/attack", 35);
        set_temp("apply/damage", 23);
        set_temp("apply/armor", 24);

        setup();
}

