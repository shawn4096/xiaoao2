//Created by Redhat@Sjmud 2009/4/7

inherit ROOM;
#include <ansi.h>
#define QUESTDIR "quest/���Ӣ�۴�/"
#define QUESTDIR1 "quest/���Ӣ�۴�/��ѩ����/"

void create()
{
	set("short", GRN "ǰԺ" NOR);
	set("long",@long
�����������ļҵ�ǰԺ��Ժ������ʺ����ӱ�ɵ�դ����Ժ�������һ�����磬�Եø��������
long);
  set("outdoors", "ţ�Ҵ�");
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
          return notify_fail(RED"û�����˵������㲻����ȥ�˼Ҽ��\n"NOR);
        if(dir == "north" &&me->query_condition("killer")) 
   		          return notify_fail(RED"û�����˵������㲻����ȥ�˼Ҽ��\n"NOR);
    return ::valid_leave(me, dir);
}*/

void init()
{
  object me;
  me = this_player();
  
 //���ߣ���ɱ������ڵ��α�

  if (me->query(QUESTDIR+"start")
	 &&!me->query(QUESTDIR1+"over")
	 &&me->query(QUESTDIR1+"yestongyin")
     &&me->query_temp(QUESTDIR1+"jiuyuan"))
  {
     tell_object(me,YEL"ֻ�����ڱ��������к�����׽�÷�����Ī�÷������ˣ�����\n"NOR); 
     tell_object(me,YEL"����һ���α��佫���Ķ������е�������Х�졢�����������������������ܸ���������\n"NOR);       
     me->start_busy(3);
	 remove_call_out("goyangjia");
     call_out("goyangjia", 3, me);   
	 me->delete_temp(QUESTDIR1+"jiuyuan");
     write(CYN"\n�㲻�ɸе�ʮ�ֺ��棬��ͣ������������������\n"NOR);
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
    if(shen <0) tell_object(me,HIR"ֻ������һ�����������������������һ��а���������뿪��\n"NOR);
    else tell_object(me,HIR"ֻ������һ���������������������λ�����������뿪��\n"NOR);
}
*/
void goyangjia(object me)
{
  if(!me) return;
  //�뿪��Ϊʧ��
  if(!present(me,this_object()))
  {
      tell_object(me,HIY"�������뿪ţ�Ҵ����ǰԺ������˾��ʵ�һĻ��\n"NOR);
        log_file("quest/SheDiao", sprintf("%s(%s)����ţ�Ҵ����ǰԺ��ȴ�����뿪��ʧ�ܡ�����%d��\n", me->name(1),me->query("id"), me->query("combat_exp")) );
     me->delete_temp(QUESTDIR+"start");
	 me->delete_temp(QUESTDIR1);
     return;
	}
	
     tell_object(me,YEL"\n�����������ĵ�˵�������ټҲ�֪Ϊ�˺��£������ۺ����񡣸��ٸ��Ǳ粻����ģ�����ֻ��������\n�����ţ�ƾ�����ǹ�����ܱ�������Χ����\n"NOR); 
	 tell_room(environment(me), YEL+me->name()+"һ�����������Ҫͻ��Σ�ѣ���Ȼ������ȥ�������ģ�\n" NOR, ({me}));
        log_file("quest/SheDiao", sprintf("%s(%s)����ţ�Ҵ����ǰԺ������%d��\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	 me->delete_temp(QUESTDIR1+"jiuyuan");
	 me->delete_temp(QUESTDIR1+"killsongbing");
	 me->set_temp(QUESTDIR1+"helpyangtiexin",1);
	 me->start_busy(1);

	 me->move(__DIR__"yangjia");  
}
int do_save()
{
	write("���ﲻ׼���̣�\n");
	return 1;
}
int do_quit()
{
	write("���ﲻ׼�˳���\n");
	return 1;
}

