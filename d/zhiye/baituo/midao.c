#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIR"秘道"NOR);
	set("long", @LONG
这条阴暗的秘道在山腹中曲折延伸，不知通往何处。这里有有一块大
石柱(shizhu)挡着向上的出口，往前走好象可以看见一点亮光。
LONG);
	set("item_desc",([
	"shizhu" : "这是根巨型圆柱，看样子应该可以扳(move)动它。\n",
	]));
	set("exits", ([
	      "west" : __DIR__"midao1",
	]));
	set("objects", ([
                    __DIR__"obj/shentuo_book1" : 1
        ]));

	setup(); 
}

void init()
{
	add_action("do_move","move");
}

int do_move(string arg)
{
	object room, me = this_player();
	
	if( (int)me->is_busy() || me->is_fighting()) 
		return notify_fail("你正忙着呢。\n");
		
	if( !arg || arg!="shizhu" ) return 0;
	
	message("vision","石柱忽然发出轧轧的声音，向一侧缓缓移开，向上露出一个光亮的出口。\n", this_object() );
	set("exits/up", __DIR__"yuanzi4");
	if( room = load_object(__DIR__"yuanzi4") ) {
		 room->set("exits/down", __FILE__);
		 message("vision","石柱忽然发出轧轧的声音，露出一个黑洞洞的洞口。\n",room );
	} 
	remove_call_out("close_door");
	call_out("close_door", 5);
	return 1;
}

void close_door()
{
	object room;
	if( !query("exits/up") ) return;
	message("vision","头顶上忽然发出轧轧的声音，石柱又缓缓地收了回去，阶梯消失了。\n", this_object() );
	if( room = load_object(__DIR__"yuanzi4") ) {
		room->delete("exits/down");
		message("vision", "石柱忽然发出轧轧的声音，缓缓地移回原处，将向下的洞口盖住了。\n", room );
		}
	delete("exits/up");
}
