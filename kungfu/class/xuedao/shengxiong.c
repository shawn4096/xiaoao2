// shengxiong.c 
// by sohu
// ����id
#include <ansi.h>

inherit NPC;
//inherit F_MASTER;

void create()
{
        set_name("ʤ��", ({ "sheng xiong", "shengxiong" ,"sheng","xiong"}));
        set("long",@LONG
����Ѫ���������µĵմ�����֮һ���ڼ����������书������Ϊ���
��������֣�״��������������Ц�ݣ�һ�������޺������ӡ�
LONG
        );
        set("title", HIR "Ѫ�����������µ���" NOR);
        set("gender", "����");
		set("class", "huanxi");
        set("age", 35);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 23200);
        set("eff_jing", 6500);
		set("max_jing",6500);
		set("eff_jingli", 6500);
        set("neili", 23500);
        set("max_neili", 23500);
        set("jiali", 200);
        set("combat_exp", 9400000);
        set("score", 5000);
		set("unique", 1);

        set_skill("huanxi-chan", 150);
        set_skill("literate", 200);
        set_skill("force", 450);
        set_skill("xuedao-jing", 450);
        set_skill("dodge", 450);
        set_skill("xueying-dunxing", 450);
        set_skill("xuedao-daofa", 450);
        set_skill("parry", 450);
        set_skill("strike", 450);
        set_skill("blade", 450);
        set_skill("jingang-liantishu", 450 );

        map_skill("force", "xuedao-jing");
        map_skill("dodge", "xueying-dunxing");
        map_skill("strike", "hongsha-zhang");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");

        prepare_skill("strike","hongsha-zhang");

        create_family("Ѫ����",5, "����");
		set("chat_chance_combat", 65);
		set("chat_msg_combat", ({
			(: perform_action, "blade.chuanxin" :),
			(: perform_action, "blade.liuxing" :),
			(: perform_action, "blade.bafang" :),
			(: perform_action, "blade.chilian" :),
			(: exert_function, "yuxue" :),			
			(: perform_action, "dodge.xueying" :),
		}));
        setup();
        carry_object("/d/xueshan/npc/obj/gongde-jiasha")->wear();
        carry_object(BINGQI_D("xinyuedao"))->wield();        

        add_money("silver",20+random(10));
}

