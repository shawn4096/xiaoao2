// By River 98/12
inherit ROOM;
#include <ansi.h>
#include <room.h>

void create()
{
	set("short", "���");
	set("long", @LONG
����һ�������ܵ�Բ�δ���ɫ�����߶���ȫשľ�ṹ��û�д������ݣ�
ȫ����ʮ�˸�ľ������ʮ��������֧�š���������ĸ���������������һ����
�����в�ʮ������������ʮ�����£���Ȧʮ����������ʮ����ʱ������������
ʮ����������ʮ�ĸ���������ƾ��ɣ�Ԣ�����ء�
LONG);

	set("exits", ([
		"east" : __DIR__"zoulang2",
	]));

	set("coor/x",-320);
  set("coor/y",-410);
   set("coor/z",-20);
   setup();
}