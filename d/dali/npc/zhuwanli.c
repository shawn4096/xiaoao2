//by cool 98.3.25
// 不能和wd,xs job一起做。River@SJ 2000.7.19

inherit NPC;
#include <ansi.h>
#include <get_place.h>
#include <mudlib.h>
inherit F_MASTER;

int check(object ob);
string ask_job();
string ask_fangqi();
string ask_diao();

void create()
{
	set_name("褚万里", ({ "zhu wanli","zhu","wanli" }));
	set("title", "大理国镇南王府家将");
	set("gender", "男性");
	set("age", 33);
	set("str", 27);
	set("dex", 26);
	set("long", "这人身穿军服，腰上插着一根软索，英气逼人。\n");
	set("combat_exp", 4500000);
	set("shen_type", 1);
	set("attitude", "peaceful");
	set("no_bark",1);
	set_skill("unarmed", 350);
	set_skill("force", 350);
	set_skill("whip", 350);
	set_skill("dodge", 350);
	set_skill("parry", 350);

    set_skill("cuff",350);
        set_skill("duanjia-quan",350);
        set_skill("tianlong-xiang",350);
        set_skill("qiantian-yiyang",350);
        set_skill("qingxu-bian",350);
        map_skill("parry", "qingxu-bian");
        map_skill("dodge", "tianlong-xiang");
        map_skill("cuff","duanjia-quan");
        map_skill("force", "qiantian-yiyang");
        map_skill("whip", "qingxu-bian");
        prepare_skill("cuff","duanjia-quan");

	set_temp("apply/attack", 70);
	set_temp("apply/defense", 70);
	set_temp("apply/armor", 70);
	set_temp("apply/damage", 20);
    create_family("天龙寺", 15 , "俗家弟子");

	set("max_qi", 9000);
	set("neili", 9000);
	set("max_neili", 9000);
	set("jiali", 120);
	set("inquiry", ([
		"送信" : (: ask_job :),
		"job" : (: ask_job :),
		"放弃" : (: ask_fangqi :),
		"fangqi" : (: ask_fangqi :),
		"钓字诀" : (: ask_diao :),

	]));

	setup();
	carry_object(BINGQI_D("ruansuo"))->wield();
	carry_object(ARMOR_D("junfu"))->wear();
}
string ask_diao()
{
	object me;
	me=this_player();
	if (me->query("int") <25){
		command ("say 清虚鞭法钓字诀需要极高悟性，你悟性不足25，将与此项绝技无缘。");
		return "";
	}
	if (me->query("family/family_name")!="天龙寺" ){
		command ("say 你非我天龙寺弟子了，我不能再收你了！");
		return "";
	}
	if (me->query("tls") && me->query("family/family_name")=="天龙寺" ){
		command ("say 你已经是天龙寺出家弟子了，学这杀生的功夫作甚？！");
		return "";
	}
	if (me->query_skill("qingxu-bian",1)<200){
		command ("say 你的清虚鞭法不足200，说了你也不懂？！");
		return "";
	}
	command("say 既然你对这门武功有缘，我就跟你说下其来源。\n");
	command("say 这门功夫我也不熟悉，但我知道谁最擅长。\n");
	command("say 跟随一灯大师修炼的四大弟子中渔人非常擅长此技能，你去找他即可。\n");
	me->set_temp("quest/tls/askzhu",1);
	return "这位前辈脾气古怪，你要尽量满足他的要求！\n";
}
void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping fam = ob->query("family");
	if (ob->query("gender") == "女性"){
		command ("say 这位小姑娘，本王府不收女徒，你还是请回吧。");
		return;
	}
	if (ob->query("tls") && fam["family_name"]=="天龙寺" ){
		command ("say 你已经是天龙寺出家弟子了，我不能再收你了！");
		return;
	}
	if(ob->query("int") < 25){
		command("say 学我大理段家武功悟性奇高，依我看" + RANK_D->query_respect(ob) + "的悟性不足25，资质似乎不宜修习？");
		return;
	}
	if ((int)ob->query("shen") < 100000){
		command ("say  我大理段氏乃堂堂正派，依我看" + RANK_D->query_respect(ob) +"正神不足10k，不适合入我大理段氏。");
		return;
	}
	if ( fam && fam["master_name"] == "段正淳"){
		command("shake");
		command("say "+RANK_D->query_respect(ob)+"已拜镇南王为师，"+RANK_D->query_self(me)+"怎敢再收你为徒？");
		return;
	}
	if( fam && fam["master_name"] == "段正明"){
		command("haha");
		command("say "+RANK_D->query_respect(ob)+"已是皇上身前的侍卫，"+RANK_D->query_self(me)+"怎敢再收你为徒？");
		return;
	}
    if( fam && fam["family_name"!="天龙寺"] ){
		command("sigh ");
		command("say "+RANK_D->query_respect(ob)+"你不是我天龙寺俗家弟子，怎敢再收你为徒？");
		return;
	}
	if ((int)ob->query_skill("duanjia-quan", 1) < 200 ){
		command("say 我不收练功不勤之人，你还是多练练你的段家拳到200吧。");
		return;
	}
    if( (int)me->query("family/generation")<15){
		command("sigh ");
		command("say "+RANK_D->query_respect(ob)+"你已经有前辈名师教导，怎敢再收你为徒？");
		return;
	}
	command("smile");
	command("say 很好，" + RANK_D->query_respect(ob) + "只要肯为我大理多做事，他日必定能有所成就。");
	command("recruit " + ob->query("id") );
	ob->set("title","大理国镇南王府管家");
	return;
}


string ask_fangqi()
{
	object ob = this_player();
	object obj;
	int i;
	string site;

	if (!ob->query_temp("dali_songxin"))
		return RANK_D->query_respect(ob) +"你并没有领了送信的任务，说什么放弃啊？";

	i = ob->query_temp("songxin/time") - ob->query_condition("dali_songxin");
	if ( i > 10 )	i = 10;
	ob->apply_condition("job_busy", 11-i);
	ob->delete_temp("dali_songxin");
	ob->clear_condition("dali_songxin");
	ob->delete_temp("letter_steal");
	ob->delete_temp("zuji");
	ob->delete_temp("songxin_zuji");
	ob->delete_temp("songxin");
	ob->clear_condition("job_busy");
	//ob->clear_condition("dali_songxin");
//	ob->clear_condition(0);/////////////////is temp

	if(objectp(obj = present("secret letter", ob)))
		destruct(obj);
        	site = lower_case(INTERMUD_MUD_NAME);
        	//不同site,扣除的奖励不同
        	if (site=="sh" || site=="sh2")
	{
		ob->add("combat_exp", -(20+random(20)));
	}
	else
	{
		ob->add("combat_exp", -(20+random(20)));		
	}
	return "既然"+ RANK_D->query_respect(ob) +"做不了，也就罢了。";
}

string ask_job()
{
	object me, *living, target, ob, obj;
	int time,i,j;
	string str;

	ob=this_player();
	me=this_object();

	if (!wizardp(ob) && !ob->query_temp("dali_join"))
		return RANK_D->query_respect(ob) +"，你不是本王府随从，此话从何说起？";

	if (ob->query_temp("dali_songxin"))
		return "你不是已经领了送信的任务吗？还不快去做。";

	if (ob->query("job_name") == "大理送信" && !wizardp(ob))
		return "你刚做完大理送信任务，还是去休息一会吧。";

	if (ob->query_condition("dali_songxin") > 0)
		return "现在暂时没有给你的任务，再等"+chinese_number((ob->query_condition("dali_songxin")+5)/6)+"个时辰吧。";

	if( ob->query_condition("job_busy"))
		return "你先去休息一会吧！";

	if (ob->query("combat_exp") < 160000)
		     return ("你的功夫还不够160k啊，送信可是很危险的事，我可不敢交给你这任务。");

	if(ob->query_temp("quest/busy")) //added by tangfeng 与quest冲突
		return "现在我这里没有给你的任务，你还是先处理好你其他事情再说吧。";


	living = livings();
	for (i=0;i < sizeof(living);i++){
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living) -1) continue;
		if(check(living[j]) ){
			target = living[j];
			str = environment(target)->query("short");
			if( str == "武僧堂"
			 || str == HIR"心禅堂"NOR
			 || str =="地下黑拳市"
			 || str == "金刚伏魔圈" ) continue;
			if( get_place(base_name(environment(target)))!="" ) break;
		}
	}

	if( !target )
		return "暂时没有信需要送，你过一会儿再来吧。";

	time = random(10)+ 25;
	ob->delete_temp("songxin_ok");
	ob->delete_temp("dali_songxin_late");
	ob->delete_temp("songxin_zuji");
	ob->set_temp("dali_songxin", 1);
	ob->set_temp("songxin/time", time);
	ob->set_temp("songxin/times", uptime());
	ob->apply_condition("job_busy", time);

	if ( random(3)) {
		ob->apply_condition("dali_songxin", time);
		ob->set_temp("songxin/target_name", target->query("name"));
		ob->set_temp("songxin/area", load_object(target->query("startroom"))->query("short"));
		ob->set_temp("songxin/areab", target->query("startroom"));
		ob->set_temp("songxin/id", target->query("id"));
		ob->set_temp("songxin/where", get_place(ob->query_temp("songxin/areab"))+ob->query_temp("songxin/area"));
		if ( random(3) ) ob->set_temp("songxin/other", 1);
	}
	else {
		ob->apply_condition("dali_songxin", time*9/10+2);
		obj = new("/d/dali/job/sxtarget");
		obj->set("startroom", target->query("startroom"));
		obj->move(environment(target));
		ob->set_temp("songxin/other", 1);
		ob->set_temp("songxin/target_name", obj->query("name"));
		ob->set_temp("songxin/area", load_object(target->query("startroom"))->query("short"));
		ob->set_temp("songxin/areab", target->query("startroom"));
		ob->set_temp("songxin/id", obj->query("id"));
		ob->set_temp("songxin/where", get_place(ob->query_temp("songxin/areab"))+ob->query_temp("songxin/area"));
	}

	switch(random(3)) {
		case 0:{
			command("nod "+ ob->query("id"));
			command("tell "+ ob->query("id")+" 你把这封密函火速送到「"+ob->query_temp("songxin/where")+GRN"」的「"+ob->query_temp("songxin/target_name")+GRN"」手上。");
			break;
		}
		case 1:{
			command("smile "+ ob->query("id"));
			command("tell "+ ob->query("id")+" 我这里正好有封信，你去把它送到「"+ob->query_temp("songxin/where")+GRN"」的「"+ob->query_temp("songxin/target_name")+GRN"」手上。");
			break;
		}
		case 2:{
			command("consider");
			command("tell "+ ob->query("id")+" 你赶紧把它送到「"+ob->query_temp("songxin/where")+GRN"」的「"+ob->query_temp("songxin/target_name")+GRN"」手上。");
			break;
		}
	}
	message_vision("$N交给$n一封密函。\n",me,ob);
	ob=new("/d/dali/job/dali_letter");
	ob->set("ever_owner",getuid(this_player()));
	ob->move(this_player());
	return "路上常有强人出没，务必小心。";
}

string *no_kill_list = ({
	 "mu ren", "jin ren", "yin ren", "zhong shentong", "zhu cong", "shi ren", "huo du","he shiwo"
});

int check(object ob)
{
	object room;
	string room_name, start_room;
//	|| ob->query("chat_chance")

	if (!objectp(ob)
	|| userp(ob)
	|| ob->query("env/invisibility")
	|| ob->query("no_quest")
	|| member_array(ob->query("id"), no_kill_list) != -1
	|| ob->query("race") !="人类"
	|| ob->query("attitude")=="aggressive"
	|| !ob->query("can_speak")
	|| ob->query("have_master")
	|| ob->query("combat_exp") < 20000
	|| !(start_room = ob->query("startroom"))	// add by Yuj@SJ to void job NPC
	|| !objectp(room=environment(ob))
	|| room->query("no_fight")
	|| room->query("quest")
	|| strsrch(room_name = base_name(room), "/d/") != 0
	|| ob->query("lastroom") == room_name && start_room != room_name
	|| start_room[0..5] != room_name[0..5]
	|| strsrch(room_name, "/d/wizard/") == 0
	|| strsrch(room_name, "/d/wuguan/") == 0
	|| strsrch(room_name, "/d/death/") == 0
	|| strsrch(room_name, "/d/mingjiao/bhd/") == 0
	|| strsrch(room_name, "/d/mingjiao/lsd/") == 0
	|| strsrch(room_name, "/d/dali/") == 0
	|| strsrch(room_name, "/d/tls/") == 0
	|| strsrch(room_name, "/d/shaolin/fumoquan") == 0
	|| strsrch(room_name, "/d/group/") == 0
	|| strsrch(room_name, "/d/baituo/") == 0
	|| strsrch(room_name, "/d/tianshan/") == 0
	|| strsrch(room_name, "/d/thd/") == 0 )
		return 0;
	return 1;
}
