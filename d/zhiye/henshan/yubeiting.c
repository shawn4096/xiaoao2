inherit ROOM;

void create()
{
        set("short", "御碑亭");
        set("long", @LONG
御碑为重修南岳庙大石碑，高数丈，石碑竖立在重三万八千斤的
大石龟上，龟身雕刻细腻，极为生动。
LONG );
        set("exits", ([ 
               "south"  : __DIR__"zhengchuan",
               "north"  : __DIR__"jiayingmen",
        ]));

        //set("no_clean_up", 0);

       // set("coor/x", 0);
	//set("coor/y", -70);
	//set("coor/z", 0);
	setup();
      //  replace_program(ROOM);
}

void init()
{
	add_action("do_read","read");
}
int do_read(string arg)
{
	object me=this_player();


}