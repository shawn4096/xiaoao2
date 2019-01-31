//Created by Redhat@Sjmud 2009/4/7

inherit ROOM;
#include <ansi.h>
#define QUESTDIR "quest/射雕英雄传/"
#define QUESTDIR1 "quest/射雕英雄传/风雪惊变/"

void create()
{
	set("short", GRN "前院" NOR);
	set("long",@long
这里是杨铁心家的前院，院子由篱笆和竹子编成的栅栏，院子里放着一个铁犁，显得格外苍凉。
long);
  set("outdoors", "牛家村");
	set("exits",([
		"north" : __DIR__"yangjia",
		"south" : __DIR__"njroad3",
	]));
    set("quest",1);
	set("no_fight", 1);
	setup();
}
/*
int valid_leave(object me, string dir)
{
    if (dir == "north" && !me->query(QUESTDIR+"over"))
          return notify_fail(RED"没有主人的允许你不可以去人家家里。\n"NOR);
        if(dir == "north" &&me->query_condition("killer")) 
   		          return notify_fail(RED"没有主人的允许你不可以去人家家里。\n"NOR);
    return ::valid_leave(me, dir);
}*/

void init()
{
  object me;
  me = this_player();
  
 //正线，且杀了西村口的宋兵

  if (me->query(QUESTDIR+"start")
	 &&!me->query(QUESTDIR1+"over")
	 &&me->query(QUESTDIR1+"yestongyin")
     &&me->query_temp(QUESTDIR1+"jiuyuan"))
  {
     tell_object(me,YEL"只听得众兵丁齐声叫喊：“捉拿反贼，莫让反贼逃了！””\n"NOR); 
     tell_object(me,YEL"忽听一名宋兵武将在哪儿高声叫道：“郭啸天、杨铁心两名反贼，快快出来受缚纳命。”\n"NOR);       
     me->start_busy(3);
	 remove_call_out("goyangjia");
     call_out("goyangjia", 3, me);   
	 me->delete_temp(QUESTDIR1+"jiuyuan");
     write(CYN"\n你不由感到十分好奇，你停了下来，静静倾听。\n"NOR);
  } 
  
		add_action("do_save", "save");
		add_action("do_quit", "quit");
}
/*
void greeting(object me)
{
    int shen;
    if(!me) return;
    if(!present(me,this_object())) return;
    if(me->query(QUESTDIR+"start")) return;
     shen = me->query("shen");
    if(shen <0) tell_object(me,HIR"只听门内一个深沉浑厚的声音传来：看你一身邪气，还请离开！\n"NOR);
    else tell_object(me,HIR"只听门内一个深沉浑厚的声音传来：这位少侠，还请离开！\n"NOR);
}
*/
void goyangjia(object me)
{
  if(!me) return;
  //离开即为失败
  if(!present(me,this_object()))
  {
      tell_object(me,HIY"你擅自离开牛家村杨家前院，错过了精彩的一幕。\n"NOR);
        log_file("quest/SheDiao", sprintf("%s(%s)初进牛家村杨家前院，却擅自离开，失败。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
     me->delete_temp(QUESTDIR+"start");
	 me->delete_temp(QUESTDIR1);
     return;
	}
	
     tell_object(me,YEL"\n你听到杨铁心低说道：“官家不知为了何事，竟来污害良民。跟官府是辩不清楚的，咱们只好逃命。\n但你别慌，凭我这杆枪，定能保你冲出重围。”\n"NOR); 
	 tell_room(environment(me), YEL+me->name()+"一想大侠杨铁心要突受危难，猛然冲进杨家去救杨铁心！\n" NOR, ({me}));
        log_file("quest/SheDiao", sprintf("%s(%s)初进牛家村杨家前院。经验%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	 me->delete_temp(QUESTDIR1+"jiuyuan");
	 me->delete_temp(QUESTDIR1+"killsongbing");
	 me->set_temp(QUESTDIR1+"helpyangtiexin",1);
	 me->start_busy(1);

	 me->move(__DIR__"yangjia");  
}
int do_save()
{
	write("这里不准存盘！\n");
	return 1;
}
int do_quit()
{
	write("这里不准退出！\n");
	return 1;
}

