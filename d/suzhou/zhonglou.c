inherit ROOM;
void create()
{
        set("short", "钟楼小院");
        set("long", @LONG
这是一座砖木结构的宝塔，塔高七层，塔身作八角形，飞檐
翘翎，檐角上挂满了一串串小铜铃，随风叮叮作响。塔身墙上镂
空雕绘着无数佛陀们的坐像。一个个形态维肖，看来出自名匠之
手。塔底入口处开了一扇拱形的小木门，门扇两侧用彩漆涂绘，
画的是释祖在灵山对诸天众佛讲经时的情形。
LONG
        );

        set("exits", ([
                "east" : __DIR__"lingyansi",
//  "enter" : __DIR__"zhonglou1",
        ]));
             
        set("coor/x",120);
  set("coor/y",-310);
   set("coor/z",30);
   setup();
}

