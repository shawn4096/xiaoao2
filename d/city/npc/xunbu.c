// xunbu.c 巡捕

#include <ansi.h>
inherit NPC;
string ask_me();

void create()
{
	set_name("张召重", ({ "zhang zhaozhong", "zhang", "xunbu", "zhaozhong"}));
	set("title", HIC"朝廷正九品捕头"+HIR"火云判官"NOR);
	set("gender", "男性");
	set("age", random(20) + 30);
	set("str", 35);
	set("dex", 30);
    set("int", 30);
	set("con", 30);
	set("long", "他是江湖曾经的传奇，他出身名门武当派，曾一夜间灭了连环十八寨的黑道，名震江湖。\n");
	set("combat_exp", 10000000);
	set("shen_type", 1);
	set("attitude", "peaceful");

	set_skill("sword",550);
	set_skill("force", 550);
	set_skill("cuff", 550);
	set_skill("dodge", 550);
	set_skill("parry", 550);
	set_skill("literate", 500);
	set_skill("taiji-jian", 550);
	set_skill("yinyun-ziqi", 550);
	set_skill("tiyunzong", 550);
	set_skill("taiji-quan", 550);

	map_skill("force", "yinyun-ziqi");
	map_skill("parry","taiji-quan");
	map_skill("dodge","tiyunzong");
	map_skill("cuff","taiji-quan");
	map_skill("sword","taiji-jian");
	prepare_skill("cuff", "taiji-quan");

	set_temp("apply/attack", 70);
	set_temp("apply/defense", 70);
	set_temp("apply/armor", 70);
	set_temp("apply/damage", 50);

	set("max_qi", 45000);
	set("max_jingli", 12000);	
	set("eff_jingli", 12000);
	set("max_jing", 12000);
	set("eff_jing", 12000);

	set("neili", 59000);
	set("max_neili", 30000);
	set("jiali", 250);
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
                (: exert_function, "yinyun" :),
                (: perform_action, "cuff.dongjing" :),
                (: perform_action, "sword.chan" :),
                (: perform_action, "cuff.an" :),
                (: perform_action, "cuff.yinyang" :),
                (: perform_action, "cuff.gangrou" :),
                (: perform_action, "sword.sanhuan" :),
                (: perform_action, "cuff.zhannian" :),
                (: perform_action, "sword.lian" :),
				(: perform_action, "sword.raozhi" :),

                (: perform_action, "cuff.luanhuan" :),
                (: perform_action, "cuff.ji" :)
        }));

	set("inquiry", ([
		"通缉犯"  : (: ask_me :),
	]));

	setup();
	carry_object(BINGQI_D("zhujian"))->wield();
	carry_object(ARMOR_D("ruanxue2"))->wear();
	carry_object(ARMOR_D("armor"))->wear();
	if (clonep()) call_out("randommove", 10);
}

void init()
{
	object ob;

	ob = this_player();
        if (interactive(ob)
        && !environment(ob)->query("no_fight")
        && !ob->query_condition("pk") // ciwei add it 
        && userp(ob)
        && !ob->query_temp("armor/cloth")){
                        message_vision(CYN "$N盯着$n看了几眼睛，突然一下把$n拦住。\n" NOR, this_object(),ob);
                        if (!ob->is_busy())
                        	ob->start_busy(1);
                        ob->add_temp("nude",1);
                        switch ((int)ob->query_temp("nude"))
		       	{
		       		case 1:
		       			command("say 公众场合，不穿衣服，象什么样子啊，下次注意哦！\n");
		       			command("rumor 有人看到" + ob->query("name") + "在大街上裸奔哦。");
		       		break;
		       		case 2:
		       			command("say 公众场合，不穿衣服，象什么样子啊，上次刚和你说过，你当我话是耳边风啊！\n");
		       		break;
		       		case 3:
		       			command("say 公众场合，记得穿衣服，虽然你的身材不错，但也没必要用这种方式展示吧。\n");
		       		break;
		       		case 4:
		       			command("say 公众场合，记得穿衣服，虽然你上次说你的身材不错，多看对我来说也没意思，下回注意了。\n");
		       		break;
		       		case 5:
		       			command("say 你无药可救了，在不穿衣服到处乱窜，我可要采取措施了哦。\n");
		       		break;
		       		
		       		case 6:
		       			command("say 你有权保持沉默，但是你所说的一切都将作为呈堂征供，根据××法第×条，本捕头正式以伤害风化罪逮捕你。\n");
		       			command("rumor " + ob->query("name") + "因为屡次在大街上裸奔，被张巡捕以伤害风化罪逮捕。");
		                        ob->add_busy(1);
		                        ob->move("/d/city/laofang2");
                			ob->set("eff_jing",1);
	       		
		       	}
                
        }
	
	if (!ob->query_condition("killer")) {
		if (query_leader() == ob)
			set_leader(0);
		if (!ob->is_killing(query("id")))
			remove_killer(ob);
	}

	::init();
	if( ob->query_condition("killer") && userp(ob) ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}


void greeting(object ob)
{
	object me;

	me=this_object();
	if (is_fighting()) return;
	if (wizardp(ob)) return;
	if(interactive(ob) && !ob->is_fighting() && ob->query_condition("killer"))
	{
		me->set("killer_name",ob->query("name"));
	    	call_out("do_kill", 0, me, ob);
	}
}

int do_kill(object me,object ob)
{
	if(me->is_fighting()) return 0;
	if (wizardp(ob)) return 0;
	if( objectp(ob) && present(ob, environment(me))
		 && !environment(me)->query("no_fight"))
	{	if (!me->query_temp("marks/杀1")){
			command("look "+ob->query("id"));
			message_vision(CYN "$N对$n说道：杀了人，就要偿命，"
				+RANK_D->query_rude(ob)+"，你赶快受死吧！\n" NOR, me,ob);
			me->set_temp("marks/杀1",1);
		}
		me->set_leader(ob);
		me->kill_ob(ob);
		call_out("checking", 0,  me);
	}

	else
		call_out("waiting", 1, me);
	return 1;
}

int waiting(object me)
{
	object ob;

	if ( objectp(ob) ){
		if (ob->is_ghost()){
			me->delete_temp("marks/杀1");
			call_out("do_back", 1, me);
			return 1;
		}
		else if (me->is_fighting() && present(ob, environment(me))) {
			call_out("checking", 0, me);
			return 1;
		}
	}

	remove_call_out("waiting");
	call_out("waiting", 60, me);
	return 1;
}

int checking(object me)
{
	object ob;

	if (me->is_fighting()){
		call_out("checking", 1, me);
		return 1;
	}
	if( objectp(ob = present("corpse", environment(me)))
	&&ob->query("victim_name") ==me->query("killer_name") ) {
		command("say 唉，终于杀了一个通缉犯，真累呀，还是先回去交差吧。");
		me->delete("killer_name");
		this_object()->delete_temp("marks/杀1");
		call_out("do_back", 1, me);
		return 1;
	}
	call_out("waiting", 0, me);
	return 1;
}

int do_back(object me)
{
	me=this_object();
	message("vision", "巡捕杀气腾腾的离开了。\n",
		environment(), me );
	me->move("/d/city/guangchang");
	message("vision", "巡捕杀气腾腾的走了过来。\n",
		environment(), me );

	me->set_leader(0);
	return 1;
}

void randommove()
{
	call_out("randommove", 10);
	if (living(this_object()) && !is_fighting()) random_move();
}

string ask_me()
{
	object ob=this_player();
	if(ob->query_condition("killer")>0)
		return "哼，通缉犯就是你自已，你还是乖乖的受死吧！";
	if(ob->query("shen")<=-100){
		write("巡捕正盯着你看，不知道打些什么主意。\n");
		return RANK_D->query_respect(this_player()) +
		"，很对不起，不能告诉你，不过我看你样子倒很象通缉犯。";
	}
	if(ob->query("shen")>-100){
		write("巡捕在你耳边悄悄的说道，"+FINGER_D->get_killer());
		message("vision","巡捕悄悄的在"+ob->name()+"耳边说了几句话。\n",
			environment(ob), ({ob}) );
		return "天子犯法，与庶民同罪。杀了人，就要偿命！";
	}
}
