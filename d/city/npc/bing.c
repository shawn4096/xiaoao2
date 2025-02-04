// bing.c 官兵

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("官兵", ({ "guan bing", "bing" }));
        set("age", 22+random(10));
        set("gender", "男性");
        set("long", "虽然官兵的武艺不能和武林人士相比，可是他们讲究的是人多力量大。\n");
        set("attitude", "peaceful");

        set("str", 24);
        set("dex", 16);
        set("combat_exp", 15000+random(20000));
        set("shen_type", 1);

        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("blade", 40);
        set_skill("force", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 40);

        set("chat_chance_combat", 2);
        set("chat_msg_combat", ({
                "官兵喝道：大胆刁民，竟敢造反不成？\n",
                "官兵喝道：跑得了和尚跑不了庙，你还是快快束手就擒！\n",
        }));
        setup();
        carry_object(BINGQI_D("blade"))->wield();
        carry_object(ARMOR_D("junfu"))->wear();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && living(this_object()) &&
                (int)ob->query_condition("killer")) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 0, ob);
        }
		else if (ob->query("job_time/官府")>=10) {
        message_vision(HIY"官兵大声说道：“向"+ob->query("title")+ob->query("name")+"大人请安!”\n"NOR, ob); 
      }
}

int accept_fight(object me)
{
        command("say 大爷我正想找人杀呐，今天算你倒霉。\n");
        if (!is_killing(me->query("id")))
                me->add_condition("killer", 15);
        kill_ob(me);
        return 1;
}
