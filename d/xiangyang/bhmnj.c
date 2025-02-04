// /d/xiangyang/bhmnj.c 白虎门内街
// Lklv Modify 2001.9.22

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "白虎门内街");
        set("long", @LONG
这里是襄阳城的西门——白虎门内的一条街道。举目望去，道路两旁的建
筑都很低矮凌乱，不成章法。但是却很热闹。走在这条小街上，耳旁总会不时
传来一阵阵喧闹嘈杂的人声。
LONG
        );
        set("outdoors", "襄阳");
        set("xyjob", 1);
        set("exits", ([
                "west" : __DIR__"baihumen",
                "east" : __DIR__"xjie",
                "north" : __DIR__"bcx4",
                "south" : __DIR__"xcx1",
        ]));

        set("objects", ([
		NPC_D("guanfu/bing") : 2,
        ]));
        set("incity",1);
	setup();
}

void init()
{
    object me = this_player();
    object ob;

    if(!me->query("quest/hsjf/fy5")
      ||!me->query("quest/hsjf/fy5/meet_killers")
      ||me->query("quest/hsjf/fy5/location")!="bhmnj"
      ||me->query("quest/hsjf/fy5/yanlian")!="pass"
      ||me->query("quest/hsjf/fy5/kill_killer_pass")
      ||me->query("quest/hsjf/fy5/exp")+100000>(int)me->query("combat_exp")
      ||me->query("quest/hsjf/fy5/time")+43200>time())
        return;

    me->start_busy(5);//触发Quest,防止player继续走动. by lsxk@hsbbs /2007/9/1
    call_out("fengyi5_killer",2,me);
    ob = new("/d/huashan/npc/fy5_npc_target");
    ob->set("escape_id",me->query("id"));
    ob->move(environment(me));
    return;
}

int fengyi5_killer(object me)
{
    object ob;

    message_vision(HIY"$N走到这里,发现一个蒙面之人恶狠狠地盯着一位书生模样的人!\n"
                     +"只听那位书生颤抖的道：“在下这点银子可是要为家中老母看病\n"
                     +"的啊,如给了你,你叫我如何对得起一个‘孝’字?”\n\n"
                  +HIW"但听那蒙面之人道:“老子管你孝还是不孝，乖乖的把钱交出来，\n"
                  +HIW"大爷我就饶你一命，要不然，哼哼。。。\n\n"
                  +HIC"那书生依旧紧握手中钱袋，脸上却显出了一丝恐惧。只见那蒙面\n"
                  +HIC"之人正欲上前动手抢夺，你当下气愤之极，立喝一声：“大胆！\n"
                  +HIC"光天化日之下，竟然当中抢劫，还有没有王法了？”\n\n"
                  +HIM"那蒙面之人瞪了$N一眼道：“王法？老子就是王法！你少管闲事，\n"
                  +HIM"要不然有你好看！”\n\n"
                  +HIR"$N已愤怒之极，鼓足内力一声长啸：“蒙面恶人，你倒是敢动他\n"
                  +HIR"一动！”，当下摆出了对阵姿势！\n\n"
                  +HIG"那蒙面之人，显然已被激怒，喝道：“既然这么想死，那我就成\n"
                  +HIG"全你！”说罢，飞身上来和你斗在了一起！\n"NOR,me);

    me->set("quest/hsjf/fy5/time",time());
    me->set("quest/hsjf/fy5/exp",(int)me->query("combat_exp"));
    ob = new("/d/huashan/npc/fy5_npc");
    ob->move(environment(me));
    me->apply_condition("fy5_killers",3);
    log_file("quest/fengyi5", sprintf(HIM"有凤来仪5Quest记录：%s(%s)开始"HIW"挑战"HIM"蒙面恶人。经验%d。"NOR, me->name(1),me->query("id"),me->query("combat_exp")) );
    return 1;
}
