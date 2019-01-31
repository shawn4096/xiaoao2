#include <ansi.h>


inherit SPEC;

void create()
{
        set_name (HIY"紫檀宝钞"NOR, ({ "baochao"}));
        set("long","这是一张"HIY"书剑紫檀站流通的宝钞"NOR"，你可以兑换(exchange baochao)它来增加通宝数量，全国流通哦，但要扣除手续费。\n");

        set("unit","张");
        set_weight(100);
        set("value",3000000);
        set("treasure",1); 
        set("degree",1);
        set("flag","spec/baochao");
        set("rest",7);
        set("desc","税后5000TB。");
  set("credit",5500);                  
        setup();
}

void init()
{
        
        add_action("do_duihuan","exchange");    
}

int do_duihuan(string arg)
{
        object me=this_player();
        
        if (!arg)
                return notify_fail("你要兑换什么?\n");
            
        if (arg!="zitan baochao" && arg!="baochao")
                return notify_fail("你要兑换?\n");
        
        if (!restrict()&& !me->query("buyvip")) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}
    
        me->add("SJ_Credit", 5000);

 
        write(HIY"你把宝钞往自动取款机里一插，取出了5000个书剑通宝！\n"NOR);
        degree(); 
        return 1;
}       
