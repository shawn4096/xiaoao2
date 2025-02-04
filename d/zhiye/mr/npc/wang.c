// /u/beyond/mr/npc/wang.c 王夫人
// this is made by beyond
// update 1997.6.29
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string ask_job();
int ask_ok();

void create()
{
        set_name("王夫人",({"wang furen","wang","furen"}));
        set("gender", "女性");
        set("rank_info/respect", "夫人");
        set("title","曼佗罗山庄主");
        set("long", 
              "她就是曼佗罗山庄的主人，她看上去虽以四十有加，但风韵尤存。\n");
        set("age", 40);
        set("attitude", "friendly");
        set("no_bark",1);
        set("shen_type", 0);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 27);

        set("combat_exp", 180000);

        set_skill("dodge",200);
        set_skill("force", 200);
        set_skill("shenyuan-gong", 200);
        set_skill("yanling-shenfa", 200);
        set_skill("parry", 200);
        //set_skill("murong-jianfa", 100);
        set_skill("literate", 200);
        //set_skill("sword", 100);
        //set_skill("finger", 100);
        //set_skill("canhe-zhi", 100);
        set_skill("strike", 200);
        set_skill("xingyi-zhang", 200);
       
        map_skill("force", "shenyuan-gong");
        map_skill("dodge", "yanling-shenfa");
        map_skill("strike", "xingyi-zhang");
       // map_skill("finger", "canhe-zhi");
        map_skill("parry", "murong-jianfa");
       // map_skill("sword", "murong-jianfa");    
     //   prepare_skill("finger", "canhe-zhi");
        prepare_skill("strike", "xingyi-zhang");
        
        setup();
        carry_object(__DIR__"obj/shoe")->wear();
        carry_object(__DIR__"obj/red_silk")->wear();
        carry_object(__DIR__"obj/skirt")->wear();
        create_family("姑苏慕容",3,"弟子");
        set("inquiry", ([
            "name" : "我就是曼佗罗山庄的主人，见到我难道没有什么表示吗？\n",
            "here" : "这里是曼佗罗山庄的庄院之所在，此处名为云锦楼？\n",
            "rumors" : "最近我那表亲慕容博不幸仙逝了。\n",
            "王语嫣" : "语嫣是我的宝贝女儿，你可别想打她的主意。\n",
            "慕容复" : "慕容复是我那不成器的侄儿，练就了以彼之道还施彼身的绝技，名震江湖。\n",
            "娘缳玉洞" : "娘缳玉洞是我曼佗罗山庄的藏书之处，一般人是别想进去了。\n",
            "曼佗罗山庄" : "这里就是曼佗罗山庄，我就是这里的主人。\n",
            "还施水阁" : "那是燕子坞的秘密之所在，不过还施水阁的藏书比那里可是多的多呀。\n",       
            "job" : (: ask_job :),
            "ok"  : (: ask_ok :),
       ]));
       
}

string ask_job()
{
        mapping fam;
        object me = this_player();
        
        if (!(fam = me->query("family")) || fam["family_name"] != "姑苏慕容") // 必须是慕容派弟子
               return RANK_D->query_respect(me) +
               "与本派素无来往，不知此话从何谈起？";

        if(me->query_condition("mrhua_job") ||
         me->query_condition("job_busy"))
               return "我正在美容，你过一会再来吧。\n";       
               
        if ((int)me->query("combat_exp") > 1000000 && me->query("mr/qinchuan"))
               return "你已经出徒了，以后可以不用来了。\n";
               
        if (me->query_temp("mrhua")||me->query_temp("yanpopo"))
               return "你不是已经领了工作么，还不快去做！\n";
               
        me->set_temp("mrhua",1);
        me->set_temp("yanpopo",1);
        me->apply_condition("mrhua_job",random(5) + 6);
        me->apply_condition("job_busy", 6);
        return "庄门口的茶花最近开的不盛，该好好照料一下了，你去找严婆婆，听她安排吧。\n";
}

int ask_ok()
{
        object me = this_player();
        int exp, pot, gold;
        
        if(me->query_temp("mark/还了")){                             
                exp = 100+random(50);

                if(me->query_temp("killke"))
					exp = exp + exp / 2;

                pot = exp /5 +random(exp/10);
                
				gold = (random(30)+ 5)*100;
                                 
                me->add("potential",pot);
                me->add("combat_exp",exp);

                MONEY_D->pay_player(me, gold);
                
				if (!me->query("mr/qinchuan")
					&&random(me->query("kar"))>27 
					&& random(me->query("jobs/浇花"))>400)
				{

					message_vision("\n\n$N微微一笑，对$n说道，看你如此辛苦为慕容世家效力，经过考核我正式通知你成为门派的核心亲传弟子。\n",this_object(),me);
					command("chat 从今日起，"+me->query("name")+"将成为我慕容世家的核心嫡传弟子，还望江湖各位同道多加照顾!\n");
					me->set("mr/qinchuan",1);
					me->set("title","慕容世家嫡传弟子");
				}

               // if(me->query("potential") > me->query("max_pot"))
				//me->add("potential", me->query("max_pot"));
                me->add("jobs/浇花",1);
                tell_object(me,HIW"你被奖励了：\n" + 
                       chinese_number(exp) + "点实战经验\n" +
                       chinese_number(pot) + "点潜能\n"+
                       chinese_number(gold/100)+"两白银。\n"NOR);
                
				me->delete_temp("mark/还了");
                me->delete_temp("mrhua");
                me->delete_temp("yanpopo");

                me->delete_temp("killke");     /**/ 
                

		log_file("job/jiaohua",sprintf("%8s%-10s慕容种花任务得%3d经验，%2d潜能，目前经验：%d。\n",
			me->name(1), "("+geteuid(me)+")",exp,pot,me->query("combat_exp")), me);
         }
         return 1;
}

void attempt_apprentice(object ob)
{
        command("say 嗯，看你还是个学武的料，我就收下你吧！");
        command("recruit " + ob->query("id"));
        ob->set("title","姑苏慕容第四代弟子");
}
