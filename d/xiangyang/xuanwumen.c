// /d/xiangyang/xuanwumen.c

#include <ansi.h>
inherit ROOM;
string look_gaoshi();

void create()
{
        set("short", YEL"������"NOR);
        set("long", @LONG
�����Ǿ������������ǵı��ţ���ʱ���ж�����׵�ʿ��������ȥ����
���Խ������������Ͼ��ڣ�����ȥ�ι��������䵱ɽ�����ŵ�ǽ��������һֽ
��ʾ(gaoshi)��
LONG
        );
        set("outdoors", "����");
        set("xyjob", 1);
        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));

        set("objects", ([
                CLASS_D("gaibang/guojing") : 1,
                NPC_D("guanfu/wujiang") : 1,
//                "d/xiangyang/npc/yangguo" : 1,
                NPC_D("guanfu/bing") : 2,
	]));
        set("exits", ([
                "north" : __DIR__"outnroad1",
                "south" : __DIR__"nroad1",
        ]));

	set("incity",1);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n��������ʹ\n���ĵ�\n";
}

/*
 void init()
{
 object me = this_player();

int t;
if(!userp(me)) return;
me->set("env/brf_go",1);

if(me->query("combat_exp")<100000)
      me->apply_condition("db_exp", 1000);
      
      
      
      
if(me->query_skill("taixuan-gong")) {me->delete("taixuan_pass"); 
me->delete_skill("taixuan-gong") ;}
    t = me->query("vip/vip_time") - time();
    if ( t > 20000000)
   me->set("y-card-vip",1);

// if(!me->query("cw_exp"))  me->delete("relife/exp_ext");
me->set("relife/exp_ext",10);
if( me->query("rmb_used")>=500  && !me->query("buyvip/start") ) me->set("buyvip/start",1);
//�Զ�����vip

 tell_object(me,"��Ŀǰ��ʣ"
          + chinese_number(me->query("SJ_Credit"))+"���齣ͨ�������Ѿ��ۼ�������" 
           + chinese_number(me->query("SJ_Credit_Used")) +"���齣ͨ����\n");
 log_file( "static/check_CREDIT",sprintf("%s(%s)  | ʣ��:%s  �ۼ�ʹ��:%s.\n", 
             me->name(),
             me->query("id"),
             chinese_number(me->query("SJ_Credit")),
             chinese_number(me->query("SJ_Credit_Used"))
             ));

}


*/