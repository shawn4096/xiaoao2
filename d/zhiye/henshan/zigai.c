inherit ROOM;

void create()
{
       set("short", "紫盖峰");
        set("long", @LONG
这里便是衡山五峰中的紫盖峰，放眼望去，北方就是衡山五峰中
的最高峰祝融峰，东面临山，由于这里海拔较高，每到春暖花开之时，
山上的积雪便融化汇入紫盖仙洞中，水满则溢，便有了紫盖峰下水莲
洞外的瀑布。
LONG );
	set("exits",([
	       "southdown":__DIR__"shanlu16",
	]));
	/*
        set("objects", ([
                CLASS_D("henshan") + "/xiang" : 1,
        ]));
     */
	set("outdoors","衡山");

     //   set("coor/x", 30);
	//set("coor/y", 40);
	//set("coor/z", 40);
	setup();
	//replace_program(ROOM);
}
