// Room: /u/xdd/gumu/ztm.c
// Modify By river 98/08
inherit ROOM;
#include <ansi.h>
int do_fail(object me);
int do_escape(object ob,object att);

void create()
{
     set("short",HIG"������"NOR);
     set("long", @LONG
�˵�����ȫ��������ţ�һ��ߴ���Ʒ������ڰ�ɽ�Ŀ������ϣ�ȫ���
�����µ�ʿ�ڴ˷����������ʴ˴�����������ƣ�����������Ů���Ĺ����
�����ġ�
LONG        );

     set("outdoors","��Ĺ");

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
          fbroom= new("/u/anger/ztmfb");//����fb
          fbroom->set("backroom","/d/gumu/ztm");//����·��
          fbroom->set("leader",me);//����ӳ�		  
		  me->set_temp("fbroom",fbroom);//��¼����
		  message_vision(HIC"$Nһ���㱣���ϸһ��ȴû����ʲô��\n"NOR,me);
		  message_vision(HIC"$N��Ȼ�����Լ�������(shouwei)��Ĺ�������������ɾ���һ��\n"NOR,me);
          me->move(fbroom);		  
	}	
}