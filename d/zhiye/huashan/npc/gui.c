// /clone/npc/guishuxin
// by dubei
//by daidai 加上quest

#include <ansi.h>
string ask_miji();
inherit NPC;
#define QUESTDIR "quest/华山派/鹰蛇生死搏/"
void create()
{
        set_name("归辛树", ({ "gui xinshu", "gui" }));
        set("long","他就是名震天下的归辛树，样子似乎很平常，似乎看不出什么特别的来。\n");
        set("gender", "男性");
        set("nickname", "神拳无敌");
        set("age", 72);

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

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "strike.wuji" :)
        }));

        set_skill("strike", 220);
        set_skill("sword", 220);
        set_skill("dodge", 220);
        set_skill("parry", 220);
        set_skill("hunyuan-zhang", 220);
        set_skill("tiangang-zhang",220);
        set_skill("huashan-jianfa", 200);
        set_skill("huashan-qigong",200);
        set_skill("literate", 100);
        set_skill("force", 200);

        map_skill("force", "huashan-qigong");
        map_skill("dodge", "huashan-shenfa");
        map_skill("strike","hunyuan-zhang");
        map_skill("parry", "tiangang-zhang");
        map_skill("sword", "quanzhen-jianfa");
        prepare_skill("strike", "hunyuan-zhang");

        create_family("华山派", 10, "弟子");

        set("inquiry", ([
               "秘籍残本" : (: ask_miji :),
               "秘籍" : (: ask_miji :),
               "残本" : (: ask_miji :),
        ]));

        setup();
        carry_object(ARMOR_D("cloth"))->wear();
        carry_object(ARMOR_D("shoes"))->wear();
}

string *wheres=({
"/d/hz/baidi",          "/d/hz/baoshuta",               "/d/hz/cuihezhai",
"/d/hz/duanqiao",       "/d/hz/hongyuchi",              "/d/hz/huanglong",
"/d/hz/hubian",         "/d/hz/hupao",          "/d/hz/jiulou",
"/d/hz/tieqiang",               "/d/hz/longjing",               "/d/hz/huanglong",
"/d/hz/yuhuang",                "/d/hz/tianxiang",              "/d/hz/kuahong",
"/d/hz/majiu",          "/d/hz/jinhuazhai",             "/d/hz/yaopu",
"/d/hz/yuquan",                 "/d/hz/longjing",               "/d/hz/zahuopu",
});

string ask_miji()
{
        object me = this_player();
        object ob,room, obj;
        int p, i, exp, y, qi, neili, jingli,jing;

        if (!me->query("family")
         ||  me->query("family/family_name") != "华山派"){
                command("sneer "+ me->query("id"));
                return "本派事物自有本派处理，就不用麻烦你了。";
        }
        if ( me->query_temp(QUESTDIR+"归辛树/over") ){
                command("sneer "+ me->query("id"));
                return RANK_D->query_respect(me) + "还不快回去把秘籍交给师傅？";
        }
        if ( !me->query_temp(QUESTDIR+"start") ){
                command("sneer "+ me->query("id"));
                return RANK_D->query_respect(me) + "是从哪里来的？";
        }
        if ( me->query_temp(QUESTDIR+"归钟/over") ){
                  obj = new("/d/huashan/npc/obj/muxia");
                  obj->set("owner", me->query("id") );
                  obj->move(me);   
                  me->delete_temp(QUESTDIR+"归钟/over");
                  me->delete_temp(QUESTDIR+"start");
                  me->set_temp(QUESTDIR+"归辛树/over", 1);
        command("say 小儿已经回来了，真是多谢了。");
        message_vision("归辛树给$N一个"HIW"木匣"NOR"。\n"NOR,me);
        return "秘籍残本就在着木匣之中，你带回去给我师傅吧。";
                 }

                y = sizeof( filter_array(children("/d/huashan/npc/guizhong"),(:clonep:)));
        if(y > 0)
                return "我正忙着呢，暂时没有空，你过段时间再来吧。";
        p = random(sizeof(wheres));
        room= find_object(wheres[p]);
        if(!objectp(room)) return "我正忙着呢，暂时没有空，你过段时间再来吧！";
        i = me->query("max_pot")-100+random(30);
        exp = me->query("combat_exp");
        qi = me->query("max_qi");
        neili = me->query("max_neili");
        jing = me->query("max_jing");
        jingli = me->query("eff_jingli");
        ob= new("/d/huashan/npc/guizhong");
        ob->set_temp("target", me->query("id") );
// 给归钟设定各项属性

        ob->set("combat_exp", exp );
        ob->set("max_qi", qi );
        ob->set("eff_qi", qi );
        ob->set("qi", qi );
        ob->set("max_jingli", jingli);
        ob->set("eff_jingli", jingli);
        ob->set("max_neili", neili*3/2);
        ob->set("neili", neili*3);
        ob->set("max_jing", jing);
        ob->set_skill("force", i);
        ob->set_skill("dodge", i);
        ob->set_skill("parry", i);
        ob->set_skill("sword", i);
        ob->set_skill("cuff", i);
        ob->set_skill("zixia-gong", i);
        ob->set_skill("huashan-jianfa", i);
        ob->set_skill("huashan-shenfa", i);
        ob->set_skill("poyu-quan", i);

        ob->move(room);
        me->set_temp("guixinshu/ask", 1);
        message_vision(CYN"归辛树露出一脸的为难之色。\n"NOR,me);
        command("say 师傅那本秘籍残本确实在我这里，但是前几天被我儿拿去当枕头了。");
        return "我儿归钟现在杭州游玩，你帮我把他找回来吧。";
}

