// Room: /d/city/chmiao.c
//Update By Jpei for Change_body 2011

#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "城隍庙");
        set("long", @LONG
这是扬州城北的城隍庙。庙里平日香客稀少，赶上中秋节、端午节或者庙
会的时候，才会有些香火。堂中放着一个城隍的塑像，上面落满了灰尘，墙角
里有个破蜘蛛网，两只蜘蛛无聊地蹲在上面。
LONG    );
        set("exits", ([
                "east" : __DIR__"beidajie1",
               "up" : __DIR__"qipaishi",
                "northwest" : "/d/wizard/guest_room",
        ]));
        set("no_fight", 1);
        set("no_sleep_room", 1);
        set("objects", ([
                __DIR__"npc/ymonk" : 1,
                __DIR__"obj/box" : 1
        ]));
        setup();
        "/clone/board/wizto_b"->foo();
}

void init()
{
        object env, link_ob, obj;
        
        object me = this_player();
if(!me) return;
        env = environment(me);
       /*
        if (me->query("qiankun/qi") && me->query("qiankun/neili")) {
                 me->set("max_qi",me->query("qiankun/qi"));
                 me->set("max_neili",me->query("qiankun/neili"));
                 me->delete("qiankun/qi");
                 me->delete("qiankun/neili");
        }*/

        me->delete_temp("die_record");

        //试剑山庄洗手状态恢复
        if(me->query("no_pk_recover")){
            tell_object(me,BLINK + HIC"您离开了试剑山庄，系统自动恢复了您的洗手状态！\n"NOR);
            me->set("no_pk",me->query("no_pk_recover"));
            me->delete("no_pk_recover");
        }
        me->clear_condition("sjsz_time");
        add_action("action", ({
                "dazuo",
                "du",
                "exercise",
                "lian",
                "practice",
                "respirate",
                "study",
                "tuna"
        }));


if(me->query_temp("death_relife"))
{
        
        me->delete_temp("death_relife");

"/cmds/app/update"->update_player(me);
}



}

int action()
{
        write("你无法静下心来修炼。\n");
        return 1;
}
/*
int valid_leave(object me, string dir)
 {
	 
     mapping exits = query("exits");
     if (!load_object(exits[dir])->query("xyjob") 
     && me->query_temp("xyjob"))
             return notify_fail("襄阳战事紧急，你还是别去送死了！！\n");
     return ::valid_leave(me, dir);
	 
 }
 */
