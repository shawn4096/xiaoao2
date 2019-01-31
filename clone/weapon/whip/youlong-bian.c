// zisong-bian.c 紫松鞭
// Created by Numa@Sj 1999-11-23

#include <weapon.h>
#include <ansi.h>

inherit WHIP;
inherit F_UNIQUE;

void create()
{
        set_name(HIG"游龙鞭"NOR,({ "youlong bian", "whip","bian" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "条");
                set("value", 1);
                set("unique", 1);
                set("rigidity", 5);
                set("material", "bamboo");
                set("weapon_prop/parry", 5);
                set("treasure",1);
                set("wield_neili", 700);
                set("wield_maxneili", 1200);
                set("wield_str", 23);
                set("long", "这是一条由特殊天蚕丝所做成的鞭子，上面镶满了宝石，精光发亮。\n");
                set("unwield_msg", "$N一背身，缓缓将$n盘回腰间。\n");
                set("wield_msg", "$N从腰间小心翼翼的抽出一条$n握在手中。\n");
        }
        init_whip(50);
        setup();
}
