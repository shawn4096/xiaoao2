#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	  set("short", HIC"�����"NOR);
	  set("long",@long
����������ɽ�ϵ�һ�����ۣ�������һ���Ҷ���顰����ۡ�������
�־�˵�ǲ����������޲�ϲ���֣��ں�ɽ�п�������ôһ�����ۣ���Ϊ����
���ϻ���ĵ����������ã�������֮�ز��ַǳ��򵥣�ֻ�м��Ŵ���������
��ʹ�ã������￾�Ż�
ů���ġ�
long);
	  set("exits",([
            "east" : __DIR__"bainiushan",
          ]));

		  set("indoors", "����");
          set("sleep_room",1);
		  set("objects",([
			"kungfu/class/kunlun/fengxifan" : 1,
		]));

          setup();
}
