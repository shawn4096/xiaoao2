// Room: /u/xdd/gumu/ztm.c
// Modify By river 98/08
inherit ROOM;
#include <ansi.h>
int do_fail(object me);
int do_escape(object ob,object att);

void create()
{
     set("short",HIG"中天门"NOR);
     set("long", @LONG
此地已是全真的中天门，一块高大的牌坊耸立于半山的开阔地上，全真教
的俗事道士于此发符传道，故此处已是香火缭绕，不少善男信女诚心供奉，修
道宁心。
LONG        );

     set("outdoors","古墓");

     set("exits", ([
         "southdown" : __DIR__"jlg",
         "westdown" : __DIR__"shanlu3",
     ]));
   set("shouwei",2);
   set("coor/x",0);
   set("coor/y",-10);
   set("coor/z",40);
   setup();
}


int init()
{
	object me=this_player();
	object fbroom;
	if (me->query_temp("qz/shouwei/askyin") && !me->query_temp("qz/shouwei/finish")) 
	{
          fbroom= new("/u/anger/ztmfb");//进入fb
          fbroom->set("backroom","/d/gumu/ztm");//返回路径
          fbroom->set("leader",me);//保存队长		  
		  me->set_temp("fbroom",fbroom);//记录副本
		  message_vision(HIC"$N一阵恍惚，仔细一看却没发现什么。\n"NOR,me);
		  message_vision(HIC"$N忽然想起自己的守卫(shouwei)古墓的任务来，不由精神一振。\n"NOR,me);
          me->move(fbroom);		  
	}	
}