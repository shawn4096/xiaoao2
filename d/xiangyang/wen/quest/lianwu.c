//by daidai

inherit ROOM;
#include <ansi.h>
#define QUESTJINSHE "quest/金蛇剑法/"

void create()
{
        set("short",HIG "练武场" NOR);
        set("long", @LONG
这是温家堡的练武场，一块空荡荡的场地。
LONG);
        set("exits", ([ 
          "out" : "/d/xiangyang/wen/damen",

]));
            set("quest",1);
        setup();
}
void init()
{
  object me,wen1, wen2, wen3, wen4, wen5;
  me = this_player();
  if (me->query_temp(QUESTJINSHE+"start_kill")
         && !me->query_condition("killer")
         && !me->query(QUESTJINSHE+"pass")
         && !me->query(QUESTJINSHE+"over"))
  {
   
     wen1=new(__DIR__"npc/wenfangshan");
     wen1->set("kill_id",me->query("id"));
     wen1->move(environment(me));      
     wen2=new(__DIR__"npc/wenfangwu");
     wen2->set("kill_id",me->query("id"));
     wen2->move(environment(me));        
     wen3=new(__DIR__"npc/wenfangshi");
     wen3->set("kill_id",me->query("id"));
     wen3->move(environment(me));    
     wen4=new(__DIR__"npc/wenfangda");
     wen4->set("kill_id",me->query("id"));
     wen4->move(environment(me));    
     wen5=new(__DIR__"npc/wenfangyi");
     wen5->set("kill_id",me->query("id"));
     wen5->move(environment(me));    
     remove_call_out("killme");
     call_out("killme", 3, me);        
    }      
}
void killme(object me)
{
      if(!me) return;

  if (me->query_temp(QUESTJINSHE+"start_kill")
                 &&!me->query_condition("killer")
                  &&!me->query_temp(QUESTJINSHE+"over") )//增加一个标记（原来的有点乱了）
   
  {

  }  
}
int valid_leave(object me, string dir)
{
       if (me->is_fighting())
                return notify_fail(RED"\n温家五老大声喝道：哪里走。一把拦住你，你竟然无法离开。\n"NOR);
       if (present("heiyi ren",this_object()))
                return notify_fail(RED"\n温家五老大声喝道：哪里走。一把拦住你，你竟然无法离开。\n"NOR);
                if(me->query_condition("killer")) 
                          return notify_fail(RED"\n怎么进来的？？这里等wiz吧。\n"NOR);
           if ( me->query_temp(QUESTJINSHE+"kill")
               && me->query_temp(QUESTJINSHE+"have_kill")){
              me->delete_temp(QUESTJINSHE+"start_kill");
              me->delete_temp(QUESTJINSHE+"kill"); 
              me->delete_temp(QUESTJINSHE+"have_kill");              
    
              }
        return ::valid_leave(me, dir);
}


