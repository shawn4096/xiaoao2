// By Spiderii@yt bt物品
#include <ansi.h>
inherit SPEC;
void create()
{
        set_name(HIW"神秘宝盒"NOR, ({ "box","baohe" }) );
        set_weight(10);
                set("unit", "个");
                set("long", "一个神秘的五彩盒子。\n是传说中天神管理员遗落凡间的宝物，它是能给人们带来幸运和厄运的魔力之盒。\n是不是经不起它的诱惑呢，那就快打开（open）它吧。。。\n");
                set("value", 0);
                set("material", "wood");
                set("no_drop", "这样贵重的东西怎么能随便乱丢呢。\n");
                set("no_get", "这样东西不能离开那儿。\n");
                set_weight(100);
                set("value",3000000);
                set("treasure",1);
                set("degree",1);
                set("flag","spec/baohe");
                set("desc","据说打开盒子会有宝玉出现。");
                set("credit",150);    

       setup();
}
void init()
{
        add_action("do_open", "open");
}

int do_open(string arg)
{        
       int i;
       object me = this_player();
       object obj;
       if(arg!="box" && arg!="baohe")
                    return notify_fail("你要打开什么?\n");
       if( me->query("combat_exp") > 4000000
       && random(me->query("kar")) > 25 && random(20) > 15 )
                i = 4;          
        else if( me->query("combat_exp") > 3000000 
        && random(me->query("kar")) > 20 && random(20) > 10 )
                i = 3;
        else if(  me->query("combat_exp") > 1000000
        && random(me->query("kar")) > 15 && random(15) > 15 )
                i = 2;
        else if(  random(me->query("kar")) > 10 )
                i = 1;
        else i = 0;
        obj = new("/d/zhiye/obj/othermaterial");
        if(obj && obj->set_level(5))
        {
                obj->move(this_player());
                message_vision(HIW"$N从宝盒中得到了一"+obj->query("unit")+obj->name()+"。\n\n"NOR,me); 
        }
                destruct(this_object());
                return 1;
                
}
