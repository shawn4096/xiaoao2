inherit ROOM;
void create()
{
	set("short", "������");
	set("long", @LONG
����һ������ɽ�¼�ª�Ĵ����̣�����¯��������յ�һƬͨ�죬�¶�
���ߣ���һ�߽�ȥ�͸е�������ȡ�ǽ�Ƕ��������깤��δ�깤�Ĳ˵�����
����������ذ�ס����׵��һλ������������������ר����־���ڴ�����
LONG
	);
        set("objects",([
                __DIR__"npc/tiejiang" : 1,
        ]));
		set("exits", ([
			"north" : __DIR__"jishi",
		]));

	set("coor/x",150);
  set("coor/y",-220);
   set("coor/z",0);
   set("incity",1);
	setup();
}

