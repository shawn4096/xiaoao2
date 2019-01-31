inherit ROOM;

void create()
{
        set("short", "花径小路");
        set("long", @LONG
这里是后山上的小路。这条小路好象不是人工刻意修出来
的，也许只是以前的采药人踩多了，现出这样一条小路来。两旁
开满了各种野花，花香阵阵，风送花香，极为幽静。		
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "southeast" : __DIR__"huajing3",
				"northwest" : __DIR__"huajing1",               
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
