// By River@SJ 2001/9  

inherit ROOM;

void create()
{
        set("short", "大驿道");
        set("long", @LONG
你走在一条尘土飞扬的大驿道上。四周人来人往。挑担子的行商，赶着大
车的马夫，出关做买卖的的商贩，熙熙攘攘，非常热闹。不时还有两三骑快马从身
边飞驰而过，扬起一路尘埃。道路两旁是整整齐齐的杨树林。
    此处已近永登，四处可见正在巡逻的官兵，看来还是不要在这里惹事。
LONG
        );
        set("outdoors", "沧州");
        set("exits", ([ 
                "southeast" : __DIR__"nroad2",
                "northwest" : "/d/lanzhou/yongdeng",				
        ]));

        setup();
}
