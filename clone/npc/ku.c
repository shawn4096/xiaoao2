#include <ansi.h>
#include <job_mul.h>
inherit NPC;
string ask_job();
string ask_finish();
void create()
{
        set_name("苦头陀",({"ku toutuo", "ku"}));
        set("long", "一个长发披肩的头陀，身材魁伟，满面横七竖八的都是刀疤，本来相貌已全不可辨。\n");
        set("age", 56);
        set("attitude", "peaceful");
        set("shen", -10000);
        set("str", 26);
        set("per", 28);
        set("int", 29);
        set("con", 27);
        set("dex", 30);
        set("max_qi", 3500);
        set("max_jing", 2200);
        set("eff_jingli", 2500);
        set("jiali", 80);
        set("combat_exp", 1500000);
        set("unique", 1);

        set_skill("sword",170);
        set_skill("dodge",170);
        set_skill("force", 170);
        set_skill("blade",170);
        set_skill("literate",150);
        set_skill("hand",170);
        set_skill("strike",170);
        set_skill("hanbing-mianzhang",170);
        set_skill("yingzhua-shou",170);
        set_skill("piaoyi-shenfa", 170);
        set_skill("shenghuo-shengong", 170);
        set_skill("lieyan-dao",170);
        set_skill("liehuo-jian",170);
        set_skill("parry", 170);

        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("sword", "liehuo-jian");
        map_skill("parry", "liehuo-jian");
        map_skill("blade", "lieyan-dao");
        map_skill("hand", "yingzhua-shou");
        map_skill("strike", "hanbing-mianzhang");
        prepare_skill("strike", "hanbing-mianzhang");
        prepare_skill("hand","yingzhua-shou");

        set("inquiry", ([
                 "营救" : (: ask_job :),
                 "脱险" : (: ask_finish :),
        ]));
        setup();
        carry_object(BINGQI_D("blade"))->wield();
        carry_object("/d/mingjiao/obj/white-cloth")->wear();
}

int check_ip(object *team)
{
        int i, j;
        for (i = 0;i < sizeof(team);i ++)
                for (j = i + 1;j < sizeof(team);j ++)
                        if (team[i] && query_ip_number(team[i]) == query_ip_number(team[j]))
                                return 0;
        return 1;
}
void reset_room(int num)
{
        int i;
        for (i = 1;i <= 13;i ++)
        {
                "/cmds/app/update"->main(this_object(), "/d/jingcheng/wanan-si/baota-" + i);
                ("/d/jingcheng/wanan-si/baota-" + i)->setup_shouwei(num + random(3));
        }
}

string ask_job()
{
        object me = this_player(), *team = me->query_team();
        int i, max, min, total = 0;
        object ob_list = filter_array(children(USER_OB), (: clonep($1) && !wizardp($1) :));
        
        foreach (object user in ob_list)
                if (user->query_temp("was_job"))
                        return "正有人在万安寺内救人，不劳大驾了。\n";
        if (sizeof(team) < 2)
                return "救人之事十分危险，仅凭一人之力恐怕不能胜任。\n";
        if (sizeof(team) > 5)
                return "万安寺内防守极其严密，人数太多更容易暴露。\n";
        if (team[0] != me) 
                return "只有队伍的首领才可以带队救人。\n";
        if (!check_ip(team))
                return "你的队伍有问题，无法给你任务。\n";
                
        max = min = me->query("combat_exp");
        for (i = 0;i < sizeof(team);i ++)
        {
                if (!team[i])
                        return "你的队伍出现了问题，请解散并重新组建。";
                if (!present(team[i]))
                        return "怎么好象人不全啊？" + team[i]->query("name") + "怎么没来？\n";
                if (team[i]->query("combat_exp") < 2000000)
                        return "救人之事十分危险，" + team[i]->query("name") + "恐怕不能胜任。\n";
                if (team[i]->query_condition("was_job"))
                        return "你队伍中的" + team[i]->query("name") + "已经十分辛苦，换其他人吧。\n";
                if (me == team[i])
                        continue;
                if (!interactive(team[i]))
                        return "你还是将" + team[i]->query("name") + "换成其他人吧。\n";
                total += team[i]->query("combat_exp");
                if (team[i]->query("combat_exp") > max)
                        max = team[i]->query("combat_exp"); 
                if (team[i]->query("combat_exp") < min)
                        min = team[i]->query("combat_exp");
        }
        if ((total < 1000000))
                return "救人之事十分危险，恐怕你们不能胜任。\n";
        if (min / (max / 100) < 80)
                return "救人之事十分危险，你们的差距太大了。\n";
        
        command("say 寺内十分危险，务必小心！");
        reset_room(sizeof(team));
        for (i = 0;i < sizeof(team);i ++)
        {
                team[i]->delete_temp("was_job");
                team[i]->set_temp("was_job/asked", 1);
                team[i]->set_temp("was_job/num", sizeof(team));
                team[i]->apply_condition("job_busy", 20);
                team[i]->apply_condition("was_job", 20);
                team[i]->set("job_name", "万安寺救人");
                team[i]->move("/d/jingcheng/wanan-si/wanan-siyuan");
                tell_object(team[i], HIR"你来到宝塔前，发现宝塔已经起火，救人迫在眉睫！\n"NOR);
        }
        return "希望此行一切顺利。\n";
}

string ask_finish()
{
        object me = this_player(), *team = me->query_team();
        int i,j,z,exp,shen,pot,SJCredit;
        
        if (team[0] != me) 
                return "只有队伍的首领才可以完成任务。\n";
                
        if (!check_ip(team))
                return "你的队伍有问题，现在无法完成任务。\n";
       
        for (i = 0;i < sizeof(team);i ++)
        {
                if (!team[i])
                        continue;
                if (!present(team[i]))
                        return "怎么好象人不全啊？" + team[i]->query("name") + "怎么没来？\n";
                if (!interactive(team[i]))
                        return "由于" + team[i]->query("name") + "的问题，你现在无法完成任务。\n";
        }
        for (i = 0;i < sizeof(team);i ++)
        {         

                if (team[i] && team[i]->query_temp("was_job/asked"))
                {	   
		          j = team[i]->query_temp("was_job/floor");
		          z = sizeof(team);
		          exp = j*400/z; // 考虑npc都很猛。提高奖励
		          exp = team[i]->add_exp_combat(exp,"苦头陀","万安寺营救");
		          pot = exp/3+random(exp/10);
		          SJCredit = j/z+j*2;
		          shen = exp/2 + pot/2;
		          team[i]->apply_condition("job_busy", 5);
		          team[i]->apply_condition("was_job", 90);
		          team[i]->add("job_time/万安寺营救",1); // 修改写法，以前是me->
		          team[i]->set("job_name", "万安寺营救");
                        tell_object(team[i],sprintf(HIW"你获得了"+CHINESE_D->chinese_number(exp)+                      
                        "点经验，"+ CHINESE_D->chinese_number(pot)+
                        "点潜能的奖励。\n"+HIR+"\n同时额外获得了"+ CHINESE_D->chinese_number(SJCredit)+"个天涯通宝\n"NOR, team[i]));

			    		team[i]->add( "potential", pot );
		    			team[i]->add("shen", shen );
		    			team[i]->add("SJ_Credit", SJCredit );
		    			log_file("job/was", sprintf("%s %s(%s)%d次万安寺营救任务得到经验%d，潜能%d，通宝%d。\n",
                                  ctime(time())[4..19],team[i]->name(1),team[i]->query("id"),(int)team[i]->query("job_time/万安寺营救"),exp,pot,SJCredit));
        }
                                  team[i]->delete_temp("was_job");
			    		
                }
        return "各位辛苦了，此次任务已经完成，回去休息吧。\n";
}

