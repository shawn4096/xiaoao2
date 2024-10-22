// /d/city/npc/wenfangda
// by daidai 加入金蛇quest相关
inherit NPC;
#include <ansi.h>
string ask_quest(); 
void create()
{
        set_name("温方达", ({ "wen fangda", "wen", "fangda" }));
        set("title", "温家五老");
        set("long", 
        "他就是温家五老的老大温方达。\n"
        "一个精瘦的老者，一双眼睛露出狡猾的目光。\n");
        set("gender", "男性");
        set("age", 66);
        set("attitude", "friendly");
        set("shen", -10000);
        set("str", 35);
        set("int", 30);
        set("con", 25);
        set("dex", 27);

        set("max_qi", 8000);
        set("eff_jingli", 4800);
        set("max_jing", 4800);
        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 170);
        set("combat_exp", 5000000);
         

        set_skill("force", 350);
        set_skill("yijin-jing", 350);
        set_skill("dodge", 350);

        set_skill("shaolin-shenfa", 350);
        set_skill("cuff", 350);
        set_skill("wenjia-daofa", 360);
        set_skill("parry", 350);
        set_skill("blade", 350);
        set_skill("wenjia-quan", 350);
        set_skill("literate", 110);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "wenjia-quan");
        map_skill("parry", "wenjia-daofa");
        map_skill("blade", "wenjia-daofa");
        prepare_skill("cuff", "wenjia-quan");

        set("inquiry", ([
                "金蛇郎君" : (: ask_quest:),
                "夏雪宜" : (: ask_quest:),
        ]));

        setup(); 
        carry_object(ARMOR_D("cloth"))->wear();
        carry_object("/clone/weapon/blade1")->wield();
}

string ask_quest()
{
        object me, ob, room;
        me = this_player();
        ob = this_object();

        if(me->query("quest/金蛇剑法/pass"))    
        { 
           // 解了quest还来问 找抽！！ by daidai
           call_out("outwuguan",1,me);
           return "你是怎么知道这个奸贼的？";
        }
        if(!me->query_temp("quest/金蛇剑法/start" ))
        {
           command("heng");
           return "那是我温家堡的仇人！";
        }
        message_vision(HIG"$N脸上露出异样的神色。\n"NOR, ob);
        command("look "+me->query("id"));
        command("sigh");
        command("say 这么说你就是金蛇奸贼的传人了，来报仇了？");
         message_vision(HIC"$N一摆手：“跟我来吧。”带着$n向练武场走去。\n"NOR, ob, me);
        
        me->set_temp("quest/金蛇剑法/start_kill",1);
        me->delete_temp("quest/金蛇剑法/start");
//         me->move("/d/xiangyang/wen/quest/lianwu");
// 为了避免有多个玩家同时解quest by daidai
         room=new("/d/xiangyang/wen/quest/lianwu");
        me->move(room);
        return "哼......";
}
void outwuguan(object me)
{
        object ob=this_object();
        object *inv;
        if(!me) return;
        command("ah");
        command("say 你是金蛇郎君那个奸贼的传人！来人啊！给我杀了这厮！");
        message_vision(HIR"只见一群家丁挥舞兵器向$N冲杀而来，$N落荒而逃。\n"NOR, me);
        inv = filter_array(deep_inventory(me), (: userp :));
        if( sizeof(inv))
                inv->move(environment(ob));
        me->move("/d/xiangyang/ncx3");
}

