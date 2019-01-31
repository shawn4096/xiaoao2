// Room: /d/huashan/jinshe/obj/datiehe.c
// Date: Look 99/03/25

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("大铁盒" , ({ "tie he", "box" }) );
        set_weight(3000);
        set_max_encumbrance(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", "这是一个两尺来高的铁盒子，上面满是了泥土。\n");
                set("value", 1000);
                set("material", "steel");
                set("no_get",1);
                set("no_drop",1);
                set("amount",30);
                }
        setup();
}

int is_container() { return 1; }

void init()
{
        add_action("do_open", "open");
        add_action("do_move", "move");
}

int do_open(string arg)
{
        object me = this_player();
        object ob;

    if (me->query_temp("open") && geteuid(me) != "yueying")
          return notify_fail("你已经打开盒子了\n");   
    if (!arg || (arg != "box" && arg != "tie he"))
       {
        return notify_fail("你想打开什么？\n");
        return 1;
       }
    else
    {  
    if (!present("jia xin",me) && me->query("quest/jinshe2/xin"))
    {
          ob=unew(__DIR__"jiaxin");
          if (random(20)> 20) {
                        write("你打开铁盒，发现里面空空的什么也没有。\n");
                        write(HIG"看来有人已经取走了里面的东西,你还是改天再来吧.\n"NOR);
        me->set_temp("open",1);
                  return 1;
                 }
        ob->move(me);
        write(HIC"你轻开铁匣，发现里面平平整整放着一封书信,你连忙拣了起来。\n"NOR);
        
        me->set_temp("open",1);
        return 1;       
      }
    if (!present("xin jian",me))
       {
        write("你轻开铁匣，突然掉落了一张信笺，你急忙把它捡起。\n");
        ob=new(__DIR__"xinjian1");
        me->set_temp("mark/open",1);
        me->set_temp("open",1);
        ob->move(me);
        return 1;
       }
        write("你打开铁盒，发现里面空空的什么也没有。\n");
        return 1;
    }
}
int do_move(string arg)
{
        object me = this_player();
        object ob;
        if ( !arg || arg != "anceng" )
        return notify_fail("你要干什麽？\n");
        if (!(int)me->query_temp("mark/open") && !(int)me->query_temp("mark/xin"))
         return notify_fail("你要做什麽？\n");
        
                write("你小心翼翼打开暗层.......\n");
                if (random(10) > 8 || me->query("env/debug")){
                                          ob=unew(__DIR__"jinshezhui");
                                          if ( ob ){
                                                         ob->move(me);
                                                         me->delete_temp("mark/open");
                                                         me->delete_temp("mark/xin");
                                                         write(HIY"赫然发现,一柄金光闪闪的蛇型锥放在里面,看起来很值钱的样子,你开心极了,连忙把它揣进怀里\n"NOR);
       this_player()->set_temp("quest/金蛇剑法/金蛇锥",1);
       this_player()->set_temp("quest/金蛇掌法/start",1); //开始标记by daidai
                                                     return 1;
                                                    }
                                          else return 1;
                                          }          
                          
        message_vision(RED"$N突然看见几道寒光扑面，大叫一声，一阵抽搐。\n"NOR, me);
        me->delete_temp("mark/open"); 
        me->unconcious();
        return 1;
}

