//颂摩崖副本 by renlai

#include <ansi.h>

inherit FBROOM;

void create()
{
        set("short", HIM"颂摩崖-副本"NOR);
        set("long", @LONG
颂摩崖又名黄龙碑。周围山势陡峭，两山对峙，一泓中流，两峡旁有潭，
渊深莫测。俗传有黄龙自潭飞出，因名黄龙潭。潭左侧摩崖成碑。汉隶真迹，
笔触遒劲，刀刻有力，记叙了开天井道的过程。往东南是仇池山，往西则是
石门。
LONG);
        set("outdoors", "副本");
		set("backroom","/d/xingxiu/silk3");
        set("quest",1);
		set("no_sleep_room",1);
		set("no_quit", 1);
        
   setup();
}
#include "fuben.h";

//不能用init函数