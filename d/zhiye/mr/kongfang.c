// /d/mr/kongfang.c
// by leontt 2000/10/18

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", HIW"�շ���"NOR);
	set("long", @LONG
��������ߵ���һ���շ��������ʲô��û�У���ʱ��������������
�����㲻�ɵĴ���һ�������
LONG);
	set("exits", ([             
		"west" : __DIR__"migong2",
		"out" : __DIR__"didao1",

	]));
	set("objects", ([
                __DIR__"obj/9dan" : 2,
		        __DIR__"obj/guiyuan-dan" : 2,		        
	            __DIR__"obj/qingxin-san" : 2,
                __DIR__"obj/jia" : 1,
		        __DIR__"obj/crown" : 1,
		        __DIR__"obj/hboot" : 1,
		        __DIR__"obj/gbelt" : 1,
		        __DIR__"obj/gfinger" : 1,
              ]));
	setup();
} 
