// road1.c
// ·1
inherit ROOM;
void create()
{
	set("short","����");
	set("long",@long
����һ���ܳ�������ʯ�����ɵ����ȣ��������ȵ����߷�����������
���ʻ������ȵ������һ���š�
long);
	set("exits",([
	    "east" : __DIR__"slj",
           "west"  : __DIR__"road2",
           "south" : __DIR__"womanws",
		"north" : __DIR__"manws",
]));
	//set("outdoors", "������");
        set("coor/x",510);
  set("coor/y",430);
   set("coor/z",90);
   setup();
}
	    	

int valid_leave(object me, string dir)
{
		if (me->query("killer"))
		{
			return notify_fail("ͨ���������Ҵ���\n");
		}
        if ((me->query("gender") == "Ů��") && dir == "north") 
           return notify_fail("Ů���˼һ��ǲ�Ҫ����ȥ�ĺã�����Ͳ������ż��ˡ�\n");
		if ((me->query("gender") == "����") && dir == "south") 
           return notify_fail("����Ů�˵����ң����أ�\n");
        return ::valid_leave(me, dir);
}
