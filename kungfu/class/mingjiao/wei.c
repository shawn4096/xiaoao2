// NPC wei.c 韦一笑
// Modify By River@SJ 99.06
// been job_npc
// Update By lsxk@hsbbs 2007/7/18   增加道具提高解九阳几率

#include <ansi.h>
#include <job_mul.h>

inherit NPC;
inherit F_MASTER;
string *drugs = ({
	MEDICINE_D("sanhuang"),
	MEDICINE_D("huiyang"),
	MEDICINE_D("yuling"),
	MEDICINE_D("yuzhen"),
	MEDICINE_D("tianwang"),
});

string ask_dichuan();
string ask_jueji();

void destroy(object ob);
void create()
{
	set_name("韦一笑",({"wei yixiao","wei","yixiao"}));
	set("title","明教护教法王");
	set("nickname",GRN"青翼蝠王"NOR);
	set("long", "他是明教的四大护法之一的青翼蝠王。\n"+
		"他身材高大，形如竹杆，生就一身好轻功。\n");
	set("age", 51);
	set("attitude", "peaceful");
	set("shen", -12000);
	set("str", 26);
	set("int", 26);
	set("con", 25);
	set("dex", 45);        

	set("max_qi", 30000);
	set("max_jing", 12000);
	set("eff_jingli", 12000);
	set("jiali", 170);
	set("combat_exp", 6400000);
	set("unique", 1);
	
	set("job_npc",1);

	set_skill("strike",400); 
	set_skill("literate",250);
	set_skill("dodge",500);
	set_skill("force", 400);
	set_skill("piaoyi-shenfa", 500);
	set_skill("hanbing-mianzhang",400);
	set_skill("shenghuo-shengong", 400);
	set_skill("parry", 400);
	map_skill("force", "shenghuo-shengong");
	map_skill("dodge", "piaoyi-shenfa");
	map_skill("strike", "hanbing-mianzhang");
	map_skill("parry", "hanbing-mianzhang");
	prepare_skill("strike","hanbing-mianzhang");
	set("inquiry", ([
		"嫡传弟子"  : (: ask_dichuan :),
		"青翼绝技"  : (: ask_jueji :),

	]));
	create_family("明教", 36, "法王");
	set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
		(: perform_action, "strike.xixue":),
		(: perform_action, "strike.mianzhang":),
		(: perform_action, "strike.hanbing":),
			(: exert_function, "shenghuo":),
	}));
	setup();
	carry_object("/d/mingjiao/obj/yel-cloth")->wear();
}

void init()
{
	::init();
        add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");
}
string ask_dichuan()
{
	object me=this_player();
	if (me->query("quest/mj/dichuan"))
	{
		command("pat "+me->query("id"));
		command("say 你已经是我大明教嫡传弟子了，好好干吧，毕竟我们是第一大教。\n");
		me->set("title","大明教嫡传弟子");
		return "圣火不灭，明教不绝!";
	}else {
		command("angry "+me->query("id"));
		command("say 你已经巡逻这么久了还没有出嫡传，是不是在偷懒？\n");
		command("say 人生多祈福，好人自有好报？\n");
		command("say 赶紧去巡逻吧。\n");
		return "我要告诉你个大秘密，巡逻其实还有隐情。。。。\n";
	}


}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping fam = ob->query("family");
        mapping my_fam = me->query("family");
        if(!fam || fam["family_name"] != "明教"){
                command("say "+RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return;
        }
        if(fam["master_name"] == "张无忌"){
                command("haha");
                command("say "+RANK_D->query_respect(ob)+"已是教主亲传弟子，"+RANK_D->query_self(me)+"怎敢再收你为徒？"); 
                return;
        }
        if (fam["generation"] == my_fam["generation"]){
                command("shake");
                command("say "+RANK_D->query_respect(ob)+"已拜光明使为师，"+RANK_D->query_self(me)+"怎敢再收你为徒？");
                return;
        }        
        if ((int)ob->query_skill("shenghuo-shengong", 1) < 200) {
                command("say 要学更为高深的武功，必须有高深的内功修为，不到200级不要来找我。"); 
                command("say " + RANK_D->query_respect(ob)+"是否还应该在圣火神功上多下点功夫？");
                return;
        }        
        if ((int)ob->query_skill("dodge",1) < 200) {
                command("say 想学我的轻功身法，必须有一定的轻功基础，不到200级不要来找我。");
                command("say 在轻功方面，" + RANK_D->query_respect(ob)+"是否还做得不够？");
                return;
        }
        command("say 嗯，看你还是个学武的料，我就收下你吧！");
        command("say 多谢明尊敝佑，让我明教又得一良材，为康扶正义，把我明教发扬光大吧。");
        command("recruit " + ob->query("id"));
        ob->set("title", GRN"明教青翼蝠王属下教众"NOR);
}

int accept_object(object who, object ob,object me)
{
   int exp,job,pot,bonus,gold, i, j =0, k, x, p;
	object* ppl;

	me = this_object();
	if(ob->query("name") != "巡逻令" || ob->query("id") != "xunluo ling") {
		command("? "+who->query("id"));  
		return 0;
	}
	if(ob->query("owner") != who->query("id") && ! wizardp(who)){
		command("say 哼，你这是从哪偷来的？");
		call_out("destroy", 1, ob);  
		return 1;
	}
	if(!ob->query("task_ok") && ! wizardp(who)){
		command("say 这令牌你还是先拿给殷无禄吧。");
		command("pat "+who->query("id"));  
		return 0;
	}
	if(!who->query_condition("mj_xunluo") && ! wizardp(who)){
		command("say 这么长时间，你都干吗去了？");
		command("disapp "+who->query("id"));
		call_out("destroy", 1, ob);  
		return 1;
	}
	command("nod");
	command("say 愿我明尊座下所有弟子都如此勤奋向上！");
	bonus = who->query_temp("mj/attacker1");
	if(bonus > 7) bonus = 7;
        exp = 1200 + random(200) + bonus * 100;

		exp=exp/2;
			job = who->query("job_time/明教");
	if(job< (who->query("job_time/明教巡逻")+who->query("job_time/明教守卫")) ){
		who->set("job_time/明教",(who->query("job_time/明教巡逻")+who->query("job_time/明教守卫")));
		job = who->query("job_time/明教");
	}
	//这里是原来的  就是要用这个
	//job = who->query("job_time/明教巡逻");
	gold = job/50 + random(job/50);

	if( gold < 1) gold = 1;
	if( gold > 15) gold = 14 + random(3);

	if (who->query("combat_exp") > 2000000)	exp = random(100) + bonus * 50+100;//稍微给一点
	
	exp = who->add_exp_combat(exp,this_object(),"明教巡逻");	
	//who->add("job_time/明教巡逻", 1);
	//GIFT_D->check_count(who,this_object(),"明教巡逻");
	//who->add("combat_exp", exp);
	
	if (who->query("combat_exp") > 2000000)
		pot = 100 + random(60);
	else
		pot= exp/5 + random(exp/10);

	who->add("potential", pot);
	p = who->query("mingjiao_job");
	if ( p > 0 ) {
		who->add("job_time/明教", p);
		who->delete("mingjiao_job");
	}
	who->add("job_time/明教", 1);	
	who->delete_temp("mj/attacker1");
	who->delete_temp("mj/over");
	if(who->query("potential") > who->query("max_pot")) 
		who->set("potential", who->query("max_pot"));
	MONEY_D->pay_player(who, gold * 10000);
	message_vision("\n$N给了$n一些"HIY"黄金"NOR"。\n"NOR,this_object(),who);
	command("whisper "+who->query("id")+" 你辛苦了，这些金子拿去好好快活一番吧。");
	job += 1;
	tell_object(who,"你已经为明教完成"+chinese_number(job)+"次工作了，再好好努力吧。\n");
	log_file("job/xunshan",sprintf("%8s%-10s第%4d次明教任务奖励经验%4d，潜能%3d，现在经验%d。\n",
		who->name(1),"("+who->query("id")+")",job,exp,pot,who->query("combat_exp")), who);
	call_out("destroy", 1, ob);
	i = sizeof(ppl);
	//该任务调整为需要解开圣火令法
	while(i--) {
		//if (userp(ppl[i]) && !wizardp(ppl[i]) && ppl[i]->query("jiuyang/wei"))
		if (userp(ppl[i]) && !wizardp(ppl[i]) && ppl[i]->query("lingfa/wei"))
		j++;
	}
   if ( who->query("combat_exp",1 ) > 2000000 && job > 400) //Update By lsxk 明教这里初期任务次数没怎么补偿，skills又调整过了，所以降低要求
		x = job%20;
	else 
		x = job%50;

	if ( wizardp(who))
		tell_object(who,sprintf("x = %d\n", x ));

   if(me->query_temp("sj_credit/quest/mj/shlf")){
       k=20;
       me->delete_temp("sj_credit/quest/shlf");
   }
   else k=30;

// if(!QUEST_D->questing(who,1,0,1)) k=60;
    
	if (random(who->query("job_time/明教"))>400 && random(who->query("kar"))>25 && !who->query("quest/mj/dichuan"))
	{
		message_vision(HIC"$N嘿嘿奸笑几声，对$n说道：“真不愧是我看好的人啊，好了可怜的娃，经过长时间的考验。\n张教主让我告诉你，你已经为我大明教的核心弟子中的一员了.”\n"NOR,this_object(),who);
		who->set("title","大明教嫡传弟子");
		who->set("quest/mj/dichuan",1);
	}
	if( random(job) > 400
	&& x == 0
    && random(who->query_int()) >= k
    && random(who->query_dex()) >= k
    && random(who->query("kar")+ who->query("pur")+ who->query("per")) >= 2*k
	//&& j < 100
	&& random(9+j)> j
	&& !who->query("quest/mj/shlf/wei")){
		command("whisper "+who->query("id")+" 看你如此努力为明教不辞劳苦工作，你快去张教主那里一次，他应该有重要的事情要告诉你。");
		who->set("quest/mj/shlf/wei", 1);
		log_file("quest/shenhuolingfa",sprintf("%8s%-10s明教任务第%s次的时候，从韦一笑处，听到有关圣火令法的传闻。\n",
			who->name(1),"("+ capitalize(getuid(who))+")",chinese_number(job)), who);
	}
	return 1;
}

void destroy(object ob)
{
	destruct(ob);
	return;
}

int do_kill(string arg)
{
	object ob,ob2; 
	object me = this_player();
	ob2 = this_object();

	if (!arg) return 0;
	ob = present(arg, environment(me));
	if (ob == this_object() || ob == me) return 0;
	if (!ob || !ob->is_character()) return 0;
        
	if (userp(ob)&& ob->query("family/family_name") == "明教") {
		if (me->query("family/family_name") == "明教") { 
		        message_vision(ob2->name()+"对$N喝道：身为明教弟子，竟然杀自己的同门？我宰了你！\n", me);
                }
                else {
                        message_vision(ob2->name()+"对$N喝道：大胆狂徒，居然敢来明教撒野！\n", me);
                        kill_ob(me);
                }
                me->set("vendetta/明教", 1);
                return 1;
        }
        return 0;
}


string ask_jueji()
{
	object me,ob;
	int i,j,k; 

	me = this_player();
	if (time()-me->query("quest/mj/pysf/time")<86400)
	{
		//command("say 你");
		return "你来的太频繁了，武功最忌讳心气浮躁？？\n";
	}
	if (me->query("family/family_name")!="明教")
	{
		return "你不是明教弟子，来此消遣我么？\n";
	}


	if (me->query("quest/mj/pysf/pass"))
	{
		me->set("title",HIG"青翼蝠王传人"NOR);
		return "你已经解开青翼蝠王轻功绝技了！？\n";
	}
	if (me->query("dex")<33)
	{
		
		return "你先天身法不够33，学不了这门武技？？\n";
	}
	if (me->query_skill("piaoyi-shenfa",1)<500)
	{
		//command("say 你");
		return "你的飘移身法不足500，学不了这门武功？？\n";
	}

	if (!me->query("quest/mj/dichuan"))
	{
		//command("say 你");
		return "你非嫡传，焉能传授你高级武功？？\n";
	}

		command("say 明教高手辈出，五行旗，五散人，四大法王，逍遥二仙的威名俱都名震江湖。\n");
		command("say 每个人都有独特的武功绝技，我最大的本事不是寒冰绵掌而是这飘移身法。\n");

		command("say 你既然如此努力和勤奋，我就传授于你，看你能否领悟了\n");

	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	j=random(j);
	k=me->query("dex");
	if (i>23
	  && j<5
	  && k>30
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIG"\n$N按照韦蝠王的指点，经脉运转不绝，涌泉穴忽然一痛，这奇经八脉的末梢经络豁然打通。”\n"NOR,me); 
		 message_vision(HIC"\n在韦蝠王的指导下，你豁然发现浑身飘然若仙，竟然如此奇妙。”\n"NOR,me); 

         message_vision(HIY"\n$N福至心灵，运转真气在这些新经脉中周转不息。\n忍不住「哈哈哈」仰天大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N经过不断领悟，终于领悟了明教四大法王青翼蝠王这门武林绝顶轻功的奥秘！”\n"NOR,me); 
		 command("chat* laugh "+me->query("id"));
		 command("chat* thumb "+me->query("id"));
		 command("chat* pat "+me->query("id"));
		 command("chat 恭喜大明教弟子"+me->query("id")+"修成飘移身法绝技！\n");
		 log_file("quest/mjpysf", sprintf("%s(%s) 请教韦蝠王后贯通成功！第%d次参悟，机缘巧合下，成功参悟青翼诀的奥秘，随机幸运值：%d,当前随机值：%d,当前悟性值：%d,当前经验：%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/mj/pysf/fail"),
		 i,
		 j,
		 k,
         me->query("combat_exp"),
		 ));

		 me->set("quest/mj/pysf/time",time());
		 me->set("quest/mj/pysf/pass",1);
		 me->set("title",HIG"青翼蝠王传人"NOR);
		 return "佩服佩服！";
     }
	 else {
	     message_vision(HIG"\n$N神情沮丧，自言自语地说道：“看来这青翼诀真是不好解啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HIY"\n参悟青翼诀绝技解密失败！\n"NOR,me); 
         log_file("quest/mjpysf", sprintf("%s(%s) 失败！参悟青翼诀第%d次失败，随机幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/mj/pysf/fail",1),
		 i,
		 j,
		 k,
         me->query("combat_exp"),));        
		 me->add("quest/mj/pysf/fail",1);
		 me->set("quest/mj/pysf/time",time());
		 me->start_busy(2);
		 return "懒得理你，笨到姥姥家去了！\n";
   }
	
}
