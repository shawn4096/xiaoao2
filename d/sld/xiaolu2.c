#include <wanted.h>
inherit ROOM;

void create()
{
	set("short", "С��·");
	set("long", @LONG
���������������һ��С·�����������������������ѡ�·
�������ݶ��˲��У�·�߳���Щ���ݣ�����ïʢ����ֻ��
���ڻ����з�����ȥ��һ�󺣷紵������������������
LONG
	);

	set("exits", ([
		"west" : __DIR__"xiaolu1",
		"east" : __DIR__"caodi",
	]));
	set("outdoors", "������");

	setup();
}
