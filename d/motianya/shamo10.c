inherit ROOM; 

#include <ansi.h>
#include <combat_msg.h> 
void create ()
{
  	set ("short", HIY"西域沙漠"NOR);
  	set ("long", @LONG
这里是西域的沙漠隔壁，四壁荒芜，十分炎热，风沙非常的大。
LONG);
        set("outdoors", "motianya");

  	set("exits", ([
  		  "east" : __FILE__,

                "west" : __FILE__,

                "south" : __FILE__,

                "north" : __FILE__,



  		
	]));
        set("objects", ([
		
  		
	]));


	setup(); 
	replace_program(ROOM); 
} 

void init()
{
	object me= this_player();
	/*
	if (random(me->query("kar")) <= 15)
		{
			me->add_condition("liuxue", 2 + random(5));
		tell_object( me, HIY"\n突然一阵狂风卷起飞沙走石，在你的身上划破了几道口子。\n"NOR);
	}
       if (random(me->query("kar")) >= 19)
		{
			me->move(__DIR__"shamo11");
		write(HIC"\n风沙之中你好像找到了点方向，跌跌撞撞的走了过去。\n"NOR);
	}*/
	
		if (random(10) <= 6 )
		{
			me->add_condition("liuxue", 1 + random(1));
			tell_object( me, HIY"\n突然一阵狂风卷起飞沙走石，在你的身上划破了几道口子。\n"NOR);

		}else
		{
			me->move(__DIR__"shamo11");
			write(HIC"\n风沙之中你好像找到了点方向，跌跌撞撞的走了过去。\n"NOR);

		}

}