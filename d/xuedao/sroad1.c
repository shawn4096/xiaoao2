// sroad1.c
// Modified by Java Apr.27 1998

inherit ROOM;
void create()
{
        set("short","ɽ·");
        set("long",@LONG
�������ǳ�ɽ���룬��ͨ���㡣һ��ɽ·������ɽ�䣬������
�رߺ���ԭ��
LONG );
        set("exits",([
                //"north"  : "/d/city3/nanheqiaos",
                //"north"  : "/d/chengdu/nanheqiaos",
                "westup" : __DIR__"sroad2",
                "southeast" : "/d/xueshan/luofenggang",
        ]));
        set("outdoors", "xuedao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
