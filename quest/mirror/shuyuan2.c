// Room: /d/city/shuyuan2.c
// This is a room made by roommaker. write by Fan. :)
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", "朱熹的寝室");
	set("long", @LONG
朱熹一向过着简朴的生活，这里除了一张床以外，唯一值钱的
只有一个书架了。
LONG
	);
    set("objects", ([
]));

	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"shuyuan",
]));
	setup();

}
  void init() 
  { 
       add_action("no_action", "shot");
       add_action("no_action", "array");
 } 
 int no_action(string str) 
{
       write(HIY"别乱来！！！ \n"NOR); 
       return 1; 
} 
//是镜像
int is_mirror() { return 1; }
