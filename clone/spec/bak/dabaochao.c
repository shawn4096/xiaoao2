#include <ansi.h>


inherit SPEC;

void create()
{
        set_name (HBRED+HIY"￥书剑大宝货￥"NOR, ({ "da baohuo","baohuo"}));
        set("long","这是一张"HBRED+HIY"书剑笑傲江湖站流通的宝货"NOR"，比宝钞牛逼多了，你可以兑换(exchange)它来增加通宝数量，全国流通哦，但要扣除手续费。\n");

        set("unit","张");
        set_weight(100);
        set("value",3000000);
  
        set("treasure",1);
        set("no_get",1);
        set("degree",1);
        set("flag","spec/baohuo");
        set("rest",2);
        set("desc","￥税后10000TB哦￥。");
  set("credit",11000);                  
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
            
        if (arg!="da baohuo" && arg!="baohuo")
                return notify_fail("你要兑换?\n");
        
        if (!restrict()&& !me->query("buyvip")) {return notify_fail("本周你已经不能使用"+this_object()->query("name")+"了。\n");}
    
        me->add("SJ_Credit", 10000);

 CHANNEL_D->do_channel(this_object(), "rumor", HIC"有人看到" + me->name(1) + "牛哄哄的用了一次"HIY"书剑大宝货"HIC"！\n"NOR);


        write(HIY"你牛逼哄哄地从取款机里取出了10000个书剑通宝，真他娘财大气粗！\n"NOR);
        degree(); 
        return 1;
}       
