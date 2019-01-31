//cool@SJ,990605
// add ansi.h解决报错 by fengyue
#include <ansi.h>
//inherit F_MASTER;
inherit NPC;


void create()
{
	set_name("本观大师", ({ "benguan dashi","benguan","dashi"}) );
        set("nickname", "牟尼堂老僧");
        set("long", "这位白须白眉，枯黄精瘦，身穿一袭金丝木
棉袈裟的老僧便是本因方丈的师兄本观大师。\n");
	set("gender", "男性" );
        set("attitude", "friendly");
	set("class", "bonze");
	set("age", 75);
	set("shen_type", 1);
	set("str", 30);
	set("int", 25);
	set("con", 25);
	set("dex", 28);
    create_family("天龙寺", 13, "弟子");
    set("unique", 1);
	
	set("qi", 25000);
	set("max_qi", 25000);
    set("eff_jingli", 6000);
	set("jing", 6000);
	set("jingli", 6500);
	set("max_jing", 6500);
	set("neili", 20000);
	set("max_neili", 20000);
	set("jiali", 200);
	set("combat_exp", 9500000);
	set("score",0);
	set("liumai-shenjian/zhongchong",1);
    set("env/liumai","zhongchong");

	set_skill("force", 450);
	set_skill("qiantian-yiyang", 450);
	set_skill("dodge", 450);
    set_skill("whip", 450);
    set_skill("cihang-bian",450);
	set_skill("tianlong-xiang", 450);
	set_skill("parry", 450);
    set_skill("finger", 460);
    
    set_skill("yiyang-zhi", 460);
	//set_skill("kurong-changong",100);
	set_skill("buddhism", 200);
    set_skill("liumai-shenjian", 30);
	set_skill("literate", 150);
    set_skill("medicine", 120);
	map_skill("force", "qiantian-yiyang");
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yiyang-zhi");
    //map_skill("whip", "cihang-bian");
	map_skill("finger", "yiyang-zhi");
	prepare_skill("finger","yiyang-zhi");		
    set("chat_chance_combat",60);
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

int do_kill(string arg)
{
        object me, ob,ob2;
        me = this_player();
        ob2 = this_object();

        if (!arg) return 0;
        ob = present(arg, environment(me));
        if (ob == this_object() || ob == me) return 0;
        if (!ob || !ob->is_character()) return 0;

	    if (ob->query("family/family_name") == "天龙寺") {
                if (me->query("family/family_name") == "天龙寺") {
                        message_vision(ob2->name()+"向$N沉声喝道：出家人戒杀生，怎么连自己的同门都杀？！\n", me);
                }
                else {
                        message_vision(ob2->name()+"向$N沉声喝道：大胆狂徒，居然来天龙寺行凶！\n", me);
                        kill_ob(me);
                }
                me->set("vendetta/天龙寺", 1);
                return 1;
        }
        return 0;
}
