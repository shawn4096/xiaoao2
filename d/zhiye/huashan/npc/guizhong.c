// /clone/npc/guishuxin
// by dubei
//by daidai 加上quest

#include <ansi.h>
string ask_miji();

inherit FIGHTER;

#define QUESTDIR "quest/华山派/鹰蛇生死搏/"
void create()
{
        set_name("归钟", ({ "gui zhong", "gui" }));
        set("long","他就是名震天下的神拳无敌归辛树的儿子归钟，面色蜡黄，一脸病态，不时的咳嗽两声。\n");
        set("gender", "男性");

        set("age", 30);

        set("attitude", "friendly");
        set("shen", -9500);
        set("str", 35);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 7000);
        set("eff_jingli", 3500);
        set("unique", 1);

        set("max_jing", 2500);
        set("neili", 10000);
        set("max_neili", 8000);
        set("jiali", 150);
        set("combat_exp", 3000000);
        set("per",16);

        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: perform_action, "sword.cangsong" :),
                (: perform_action, "sword.fengyi" :),
                (: perform_action, "sword.kuaijian" :),
                (: perform_action, "sword.lianhuan" :),
                (: perform_action, "sword.luomu" :),
                (: perform_action, "sword.shijiushi" :),
                (: perform_action, "sword.wushuang" :),
        }));

        set_skill("cuff", 220);
        set_skill("sword", 220);
        set_skill("dodge", 220);
        set_skill("parry", 220);
        set_skill("huashan-qigong", 220);
        set_skill("poyu-quan",220);
        set_skill("huashan-jianfa", 200);
        set_skill("huashan-shenfa",200);
        set_skill("literate", 100);
        set_skill("force", 200);

        map_skill("force", "huashan-qigong");
        map_skill("dodge", "huashan-shenfa");
        map_skill("cuff","poyu-quan");
        map_skill("parry", "huashan-jianfa");
        map_skill("sword", "huashan-jianfa");
        prepare_skill("cuff", "poyu-quan");

        create_family("华山派", 11, "弟子");

        set("inquiry", ([
               "回去" : (: ask_miji :),
               "找你回去" : (: ask_miji :),
               "归辛树" : (: ask_miji :),
        ]));

        set("chat_chance", 10);
        set("chat_msg", ({
                (: random_move :)
        }) );
        setup();
        carry_object(ARMOR_D("cloth"))->wear();
        carry_object(ARMOR_D("shoes"))->wear();
       carry_object(BINGQI_D("changjian"))->wield();
        if (clonep())
                call_out("dest", 1000);
}

void dest()
{
        destruct(this_object());
}

void do_lost()
{
        object me,ob;
        me = this_object();
        ob = find_player(me->query_temp("target"));
        if(!ob) return;
          ob->delete_temp(QUESTDIR+"start");    //删除开始标记  
        tell_room(environment(me), "\n"+me->query("name")+"大喊一声：我不玩了！转身几个起落就不见了。\n");
        destruct(me);
}

int checking(object me, object ob)
{
        int ret =  ::checking(me,ob);
        if(!ret) return 0;
        remove_call_out("checking");
        call_out("checking", 1, me, ob);
        if(!living(ob) && living(me) && me->query("jing")>0 && me->query("jingli")>0 && me->query("qi")>0  ){
                remove_call_out("checking");
                        ob->set(QUESTDIR+"time",time());  //失败时间
                ob->set(QUESTDIR+"combat_exp",ob->query("combat_exp")); //打上失败经验 
                ob->delete_temp(QUESTDIR+"start");    //删除开始标记   
                ob->set("qi",100);                                                                                                                                                      //防止玩家意外死亡
                ob->set("jing",100);
                ob->set("jingli",100);
                tell_room(environment(me), "\n"+me->query("name")+"大喊一声：我不玩了！转身几个起落就不见了。\n");
                destruct(me);
                 return 1;
        }
        if(!ob || environment(ob)!= environment(me)){
                remove_call_out("checking");
                 remove_call_out("do_lost");
                 call_out("do_lost",0);
                 return 1;
        }
}

void unconcious()
{
        object me,ob;

        //int i;

        me = this_object();
        ob = find_player(me->query_temp("target"));
        
        if (!ob) {
                destruct(me);
                return;
        }
        if (!present(ob)) {
                        ob->set(QUESTDIR+"time",time());  //失败时间
                ob->set(QUESTDIR+"combat_exp",ob->query("combat_exp")); //打上失败经验 
                ob->delete_temp(QUESTDIR+"start");    //删除开始标记   
                tell_room(environment(me), "\n"+me->query("name")+"大喊一声：我不玩了！转身几个起落就不见了。\n");
                destruct(me);
                return;
        }
        ob->set_temp(QUESTDIR+"归钟/over",1);
        tell_room(environment(me), "\n"+me->query("name")+"大喊一声：我不玩了！！转身几个起落就不见了。\n");       
        destruct(me);
}

void die()
{
        object me,ob;

        me = this_object();
        ob = find_player(me->query_temp("target"));
        if (!ob) {
                destruct(me);
                return;
        }
        if (!present(ob)) {
                ob->set(QUESTDIR+"time",time());  //失败时间
                ob->set(QUESTDIR+"combat_exp",ob->query("combat_exp")); //打上失败经验 
                ob->delete_temp(QUESTDIR+"start");    //删除开始标记   

                tell_room(environment(me), "\n"+me->query("name")+"大喊一声：老子不奉陪了！转身几个起落就不见了。\n");
                destruct(me);
                return;
        }
        
        ob->set_temp(QUESTDIR+"归钟/over",1);
        tell_room(environment(me), "\n"+me->query("name")+"大喊一声：我不玩了！！转身几个起落就不见了。\n");       
        destruct(me);
}


string ask_miji()
{
        object me = this_object();
        object ob = this_player();
        if (!ob->query_temp("guixinshu/ask"))
                return RANK_D->query_respect(ob) + "乱说些什么啊？";


        message_vision(HIC"$N对归钟说道：“前面可是归钟归公子，你父亲让我来找你回去呢，快跟我走吧”。\n"NOR,ob);
        ob->delete_temp("guixinshu/ask");

        remove_call_out("checking");
        call_out("checking", 2, me, ob);
        ::do_kill(ob);
        return "回去？我还没玩够呢，你来和我玩玩吧。。";
}

