inherit ROOM;

void create()
{
        set("short", "山中地道");
        set("long", @LONG
这里是后山中的一条阴暗小路。这条小路是人工刻意修出来的，
仅容一人穿过，令人意外的是此地道内空气清新，并无任何不适，应
该是有新鲜空气进入此地，地道蜿蜒向上，空气越来越清新。
LONG);
       // set("outdoors", "quanzhen");
        set("exits", ([
                "eastdown" : __DIR__"didao3",
				"up" : __DIR__"guanxing",
              
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
