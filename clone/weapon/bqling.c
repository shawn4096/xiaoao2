/*
 tie-ling.c 铁令
 by snowman@SJ 18/02/2000

*/

#include <weapon.h>
#include <ansi.h>

inherit F_DAGGER;
inherit COMBINED_ITEM;
inherit F_UNIQUE;
inherit F_EQUIP;

void set_amount(int v)
{
        object owner = environment();
        if (v >= 0) {
                set("weapon_prop/damage", v * (int)query("base_damage"));
                set("rigidity", v * query("base_rigidity"));
                if (query("equipped") && objectp(owner)) {
                        owner->set_temp("apply/damage", query("weapon_prop/damage") );
                }
        }
        ::set_amount(v);
}

void add_amount(int v) { set_amount((int)query_amount()+v); }

void create()
{
        set_name(HIC"精制铁令"NOR, ({ "tie ling","ling" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("base_unit", "块");
                set("base_weight", 1000);
                set("long", BLU"这是一对精致的铁令，上面黑漆漆的看不清楚有什么字样，看来年代久远。\n"NOR);
                set("value", 140000);
                set("material", "steel"); 
                set("base_damage", 20);
                set("rigidity", 1);
                set("base_rigidity", 1);
                set("wield_msg", "$N「唰」的一声抽出一柄精制铁令握在手中。\n");
                set("unwield_msg", "$N趁人不注意，将两块铁令收了起来。\n");
        }
        set_amount(2);
        init_dagger(50);
        setup();
}

int wield() 
{
        object me = environment();

        if (!userp(me)) return ::wield();
        if (living(me) && !me->query_skill("shenghuo-lingfa", 1)){
                message_vision("$N拿出"+name()+"看了看，却搞不懂怎么使用这个东西。\n", me);
                return 0;
        }           
        if( query_amount() > 2 ){
                message_vision("$N拿出"+name()+"看了看，却搞不懂怎么同时使用它。\n", me);
                return 0;
        }    
        if (query_amount() > 1){
                if (me->query_skill("shenghuo-lingfa", 1) < 80 || me->query_int() < 30){
                        message_vision("$N拿出"+name()+"看了看，却搞不懂怎么用它。\n", me);
                        return 0;
                }
        }
        if(!query("weapon_prop/damage")) return 0;
        return ::wield();
}
