// shulin1����ľ��
// ��������֮��
//��Ѫ������
// by sohu@xojh
inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", WHT"��ľ��"NOR);
	set("long", @LONG
����һƬ��ľ�֡��Ͱ��Ĺ�ľ�ִ���һ�飬��ʵ����֦��һ�����ɡ
�㸲����Ƭ�͹��ݵأ��������⡣�߰Ѻ�Ļ�ѩ���ڵ��ϣ�һ�Ų���ȥ����
ûϥ�ǡ�
LONG);

	set("exits", ([
		"south" : __FILE__,
		"east" : __DIR__"caodi",
		"west" : __FILE__,
		"north" : __DIR__"shulin2",
	]));

	set("outdoors", "xuedao");

	set("coor/x",40);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}


