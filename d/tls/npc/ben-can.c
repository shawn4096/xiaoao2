//cool@SJ,990605
//bencan.c
//inherit F_MASTER;
inherit NPC;

void create()
{
	set_name("���δ�ʦ", ({ "bencan dashi","bencan","dashi"}) );
        set("nickname", "Ĳ������ɮ");
        set("long", "һλ�����ü����ɮ����һϮ��˿ľ�����ġ�
����Ŀ��࣬�Ǳ����ɵ�ʦ�ܡ�\n");
	set("gender", "����" );
        set("attitude", "friendly");
	set("class", "bonze");
	set("age", 65);
	set("shen_type", 1);
	set("str", 40);
	set("int", 23);
	set("con", 36);
	set("dex", 23);
	set("unique", 1);
	set("per",24);
    create_family("������", 13, "����");

	set("qi", 22500);
	set("max_qi", 22500);
        set("eff_jingli", 6000);
	set("jing", 6500);
	set("jingli", 6000);
	set("max_jing", 6000);
	set("neili", 20000);
	set("max_neili", 20000);
	set("jiali", 200);
	set("combat_exp", 9400000);
	set("score",100);
    set("liumai-shenjian/shaoze",1);
    set("env/liumai","shaoze");
	set_skill("force", 450);
	set_skill("qiantian-yiyang", 450);
	set_skill("dodge", 450);
    set_skill("duanjia-quan", 450);
	set_skill("tianlong-xiang", 450);
	set_skill("parry", 455);
	set_skill("finger", 450);
    set_skill("cuff", 450);
	set_skill("yiyang-zhi", 450);
	//set_skill("kurong-changong", 460);
	set_skill("buddhism", 200);
    set_skill("liumai-shenjian", 30);
	set_skill("literate", 180);
    set_skill("medicine", 110);
	
	map_skill("force", "qiantian-yiyang");
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yiyang-zhi");
    map_skill("cuff", "duanjia-quan");
	map_skill("finger", "yiyang-zhi");
	prepare_skill("finger","yiyang-zhi");
    set("chat_chance_combat", 60);
    set("chat_msg_combat",({ 
            (: exert_function, "yiyang" :),
			(: exert_function, "jingxin" :),
			(: exert_function, "liao" :),
        }));
      
        
        setup();
        carry_object("/d/tls/obj/nianzhu")->wear();
        carry_object("/d/tls/obj/jiasha")->wear();
        carry_object("/d/tls/obj/sengxie")->wear();
}
#include "ben.h";
void init()
{
	::init();
		add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");
}

int do_kill(string arg)
{
        object me, ob,ob2;
        me = this_player();
        ob2 = this_object();

        if (!arg) return 0;
        ob = present(arg, environment(me));
        if (ob == this_object() || ob == me) return 0;
        if (!ob || !ob->is_character()) return 0;

	    if (ob->query("family/family_name") == "������") {
                if (me->query("family/family_name") == "������") {
                        message_vision(ob2->name()+"��$N�����ȵ��������˽�ɱ������ô���Լ���ͬ�Ŷ�ɱ����\n", me);
                }
                else {
                        message_vision(ob2->name()+"��$N�����ȵ����󵨿�ͽ����Ȼ�����������ף�\n", me);
                        kill_ob(me);
                }
                me->set("vendetta/������", 1);
                return 1;
        }
        return 0;
}
