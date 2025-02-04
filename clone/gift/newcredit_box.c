// credit_box.c  通宝箱  By lsxk@hsbbs 2007/7/19 流通通宝，收取30%手续费。。
// 修改手续费，WTO贸易减少10%税务 By server
//加入日志记录,方便查询 by lsxk@hsbbs 2007/7/29

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW"通宝箱"NOR, ({"tongbao xiang", "xiang"}));
        set("long",
               "这是只可以存取书剑通宝的特殊箱子,你可以通过如下命令来操作：\n"+
               HIG"\n    查看箱子内的通宝数量: "HIR"chakan tongbao xiang\n"+
               HIG"    存通宝: "HIR"cun <数量> 通宝 in tongbao xiang\n"+
               HIG"    取通宝: "HIR"qu <数量> 通宝 from tongbao xiang\n"NOR);
       set("unit", "只");
        set("weight", 10);
       set("treasure", 1);
       set("unique", 1);
}

void init()
{
    add_action("do_qu","qu");
    add_action("do_cun","cun");
    add_action("do_check","chakan");
}

int do_check(string arg)
{
    int i;
    i = (int)this_object()->query("SJ_Credit");

    if (!arg) return 0;
    if (arg!="tongbao xiang" && arg!="xiang") return 0;
    if (!i) return notify_fail("通宝箱里好象啥东西都没有。\n");

    return notify_fail(HIY"通宝箱里好象有"+HIW+chinese_number(i)+HIY+"个书剑通宝。\n"NOR);
}

int do_qu(string arg)
{
    int i,credit_stored,p_credit;
    string str;
    object ob = this_object();
    object me = this_player();
    credit_stored = (int)ob->query("SJ_Credit");
    p_credit= (int)me->query("SJ_Credit");

    if (!arg) return notify_fail("你要取什么?\n");

    if( !sscanf(arg, "%d 通宝 from %s",i,str) )
        return notify_fail("你要从哪里取什么东西?\n");

    if(str!="tongbao xiang" && str!="xiang")
        return notify_fail("你要从哪里取东西?\n");

    if(!credit_stored)
        return notify_fail("你以为你是魔法师啊，凭空取通宝？\n");

    if(i>credit_stored)
        return notify_fail("里面有这么多通宝么？\n");

    if(i<=0)
        return notify_fail("你睡醒了么？时间还早，在去睡睡！\n");

    ob->add("SJ_Credit",-i);
    me->add("SJ_Credit",i*8/10);

    log_file( "static/CREDIT_BOX_LOG",sprintf(HIG"%s(%s) 之前:%d个通宝 | 取出:%d个通宝 | 损失:%d个通宝 | 现有:%d个通宝."NOR, me->name(), me->query("id"), p_credit, i, i/5, (int)me->query("SJ_Credit")));

    message_vision(HIG"$N伸手在$n"HIG"里掏了几下，竟然掏出了"+HIR+chinese_number(i*8/10)+HIG+"个"+HIW+"书剑通宝"HIG"！\n"+
                "但是$N却沮丧的发现有"+HIM+chinese_number(i-i*8/10)+HIG+"个"+HIW+"书剑通宝"HIG"被卡在了缝里，掏不出来了。\n"NOR,me,ob);

    return 1;
}

int do_cun(string arg)
{
    int i, j;
    string str;
    object ob = this_object();
    object me = this_player();

    if(!me->query("SJ_Credit"))
        return notify_fail("哇塞，你现在的通宝好多哦。。。\n");

    j = (int)me->query("SJ_Credit");

    if (!arg) return notify_fail("你要存什么?\n");

    if( !sscanf(arg, "%d 通宝 in %s",i,str) )
        return notify_fail("你要把什么东西存进哪里?\n");

    if(str!="tongbao xiang" && str!="xiang")
        return notify_fail("你要存到哪里去了?\n");

    if(i<=0)
        return notify_fail("你睡醒了么？时间还早，在去睡睡！\n");

    if(i>j)
        return notify_fail("你有这么多通宝么？\n");

    message_vision(HIC"只见$N偷偷摸摸地从身上摸出"HIY+chinese_number(i)+HIC"个"HIW"书剑通宝"HIC"，放"+
                  "进了$n"HIC"。\n"NOR,me,ob);
   me->add("SJ_Credit",-i);
   ob->add("SJ_Credit",i);

    log_file( "static/CREDIT_BOX_LOG",sprintf(HIR"%s(%s) 之前:%d个通宝 | 存入:%d个通宝 | 现有:%d个通宝."NOR, me->name(), me->query("id"), j, i, (int)me->query("SJ_Credit")));

   return 1;
}
