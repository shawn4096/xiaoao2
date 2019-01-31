// /d/xingxiu/npc/ding.c 
// ding.c ������
// Update by caiji@SJ 8/8/2000

#include <ansi.h>
#include <get_place.h>

#include <jobround.h>
#include <job_mul.h>


#define TIME_TICK (time()*60)
//#include "/d/xingxiu/npc/ding.h"


inherit NPC;
inherit F_MASTER;

string *drugs = ({"/obj/yao","/obj/yao1","/obj/yao","/obj/yao2","/obj/yao","/obj/yao3","/obj/yao",});
int give_reward(object me);
int give_drug();
string ask_job5();
string ask_pantu();
string ask_job4();
string ask_job5_times();

string ask_fail();
int check(object ob);
string ask_job3();
string ask_job();
string ask_times();
string ask_san();
string ask_gou();
string ask_pay();
int ask_hgdf();
int ask_finish();

string ask_zhuihun();
void create()
{
	set_name("������", ({ "ding chunqiu", "ding" }));
	set("nickname", "�����Ϲ�");
	set("long",
	"�����ɿ�ɽ��ʦ������ԭ������ʿ���ʹ���������Ϲֶ����\n"
	"����ɫ������ͷ���ˣ���������ף�ͯ�պ׷���\n"
	"�������ͼ���е���������һ�㡣\n");
	set("gender", "����");
	set("age", 60);
	set("per", 24);
	set("attitude", "friendly");
	set("no_bark",1);
	set("shen_type", -1);
	set("str", 40);
	set("int", 27);
	set("con", 40);
	set("dex", 32);
	set("max_qi", 80000);
	set("max_jing", 5000);
	set("eff_jingli", 3500);
	set("max_neili", 30000);
	set("jiali", 250);
	set("combat_exp", 15000000);
	set("unique", 1);
	set("quest/xx/hgdf/powerup",1);
    set("quest/xx/tsz/luanpifeng/pass",1);
	set("quest/xx/tsz/zhuihun/pass",1);
	set("shen", -200000);
	set("xx/zhg/pass",1);

	set_skill("force", 551);
	set_skill("huagong-dafa", 551);
	set_skill("dodge", 500);
	set_skill("zhaixingshu", 500);
	set_skill("strike", 551);
	set_skill("chousui-zhang", 551);
	set_skill("parry", 500);
	set_skill("claw", 500);
	set_skill("sanyin-zhua", 500);
	set_skill("staff", 500);
	set_skill("tianshan-zhang", 500);
	set_skill("literate", 250);
    set_skill("poison", 300);
    //set_skill("hook", 500);
    //set_skill("zhuihun-gou", 500);
	map_skill("force", "huagong-dafa");
	map_skill("hook", "zhuihun-gou");
	map_skill("dodge", "zhaixingshu");
	map_skill("strike", "chousui-zhang");
	map_skill("parry", "chousui-zhang");
	map_skill("claw", "sanyin-zhua");
	map_skill("staff", "tianshan-zhang");
	prepare_skill("strike", "chousui-zhang");
	prepare_skill("claw", "sanyin-zhua");
	create_family("������", 1, "��ɽ��ʦ");
	set("inquiry", ([
		 "��ҩ" : (: give_drug :),
		 "����" : (: ask_job :),
	    //   "��Цɢ" : (: ask_san :),
	   //"��Ц��ңɢ" : (: ask_san :),
		"pantu" : (: ask_pantu :),
	    "�����" : (: ask_job4 :),
	    "duchonggu" : (: ask_job4 :),
		  //"��ͽ": (: ask_job5 :),
		"��ͽ": (: ask_pantu :),
		"����": (: ask_fail :),
		"fail": (: ask_fail :),
	    "�����󷨰���": (: ask_hgdf :),
	  //  "ɱ��ͽ����": (: ask_job5_times :),
	    "���": (: ask_finish :),
	    "׷���������": (: ask_zhuihun :),

	     "��ľ����" : "���͵���ͷ����㡣",
		 "ľ��" : "ץ���������õġ�",
	]));

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: exert_function, "huadu" :),
		(: exert_function, "huajing" :),
		(: perform_action, "strike.huoqiu" :),
		(: perform_action, "strike.chousui" :),
		(: perform_action, "strike.yinhuo" :),
		(: perform_action, "strike.biyan" :),
	}));

	set("drug_count",15);
	set("class", "taoist");

	set_temp("apply/damage", 20);
	set_temp("apply/defense", 70);
	set_temp("apply/armor", 60);
	setup();

	if (clonep()) {
		UPDATE_D->get_cloth(this_object());
		add_money("gold", 2);
	}
}

int prevent_learn(object me,object weapon)
{
	mapping myfam;
	object ob;
	int shen;
	ob=this_player();
	myfam = (mapping)ob->query("family");
	if(!myfam || (myfam["family_name"] != "������")) return 0;
	if(!ob->is_apprentice_of(this_object())) return 0;
	
	shen = ob->query("shen");
	if(shen > -1000 && shen < 0)
	{
		command("say ����ô��ģ�������һ��İ׵���Ϣ��");
		return 1;
	}
	else if(shen >= 0 && shen < 100000)
	{
		command("say ���ۣ���ҺͰ׵����˽��ͣ���������ǲ��ǣ�");
		return 1;
	}
	else if(shen >= 100000){
		command("say �㾹�ҺͰ׵����˽��ͣ������������ȥ�ɣ�");
		command("expell " + ob->query("id"));
		return 1;
	}
	return 0;
}

void init()
{
	object me, ob;
	::init();
	ob = this_player();
	me = this_object();

	if(ob->query("job_time/���ް�ҩ"))
	{
		ob->add("job_time/���ް���",ob->query("job_time/���ް�ҩ"));
		ob->delete("job_time/���ް�ҩ");
	}
		
	if (interactive(ob = this_player()) && visible(ob) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_flatter", "flatter");
	add_action("do_xian", "xian");
	//add_action("do_begsan", "begsan");
}

string ask_san()
{

	if((int)this_player()->query("combat_exp") < 200000
	 || (string)this_player()->query("family/family_name") != "������")
		  return "��ƾ��Ҳ��Ҫ��Цɢ��\n";

	if( query("started") != 1 ){
	   set("started", 1);
	   call_out("generate_sxs", 7200);//2 hours
	}

	if((int)this_player()->query_skill("poison", 1) < 200)
		  return "��Ķ����������ߣ��Ҳ����İ���Цɢ�����㡣";

	if((int)this_player()->query_skill("huagong-dafa", 1) < 450)
		  return "��Ļ����󷨻������ߣ��Ҳ����İ���Цɢ�����㡣";

	message_vision("�������$NЦ��������begsan����Ե����Ρ�\n", this_player());
	return "���԰�";
}

void generate_sxs()
{
	remove_call_out("generate_sxs");
	set("available", 1);
}

int do_begsan(string arg)
{
	object me, book;
	me = this_player();

	if( query("available") == 1 && clonep(book = unew(MEDICINE_D("sxs")))){
	  set("available", 0);
	  book -> move(me);
	  message_vision("$N����������Ե����һ����Цɢ���͸����ˡ�\n", me);
	  command("chat "+ me->query("name")+"��Ե���õ��ҵı����Ц��ңɢ����");
	  remove_call_out("generate_sxs");
	  call_out("generate_sxs", 7200);//2 hours
	  return 1;
	}
	return notify_fail("������˵���������Ĳ���ʱ��\n");
}

void greeting(object me)
{
	mapping myfam;
	int shen;

	if(!me || environment(me) != environment(this_object())) return;

	shen = me->query("shen");
        if ( file_name(environment(this_object())) != this_object()->query("startroom")) return;

	if(!myfam = (mapping)me->query("family"))
		command("say ��ǧ����������ɽ, Ī����������������ɣ�");
	else if(myfam["family_name"] != "������" ){
		if(!me->query_temp("xx_job"))
			command("say ��ǧ������������ɽ������Ľ�������ҵ��ʵ°ɣ�");
		else    command("nod " + me->query("id"));
	}

	else if(shen > -1000 && shen < 0)
		command("say ����ô��ģ�������һ��İ׵���Ϣ��");
	else if(shen >= 0 )//&& shen < 100000
		command("say ���ۣ���ҺͰ׵����˽��ͣ���������ǲ��ǣ�");
	else if(shen > 100000){
		command("say �㾹�ҺͰ׵����˽��ͣ������������ȥ�ɣ�");
		command("expell " + me->query("id"));
	}   // I move this to prevent_learn By Ciwei@SJ
	else command("say ��ͽ��������������ô���ˣ�");
	if(me->query("xx_job5_finished"))call_out("give_reward",1,me);
}

void attempt_apprentice(object me)
{
	if(me->query("family/family_name") != "������"
	 && me->query("expell/family_name") != "������"){
		say("���ɶ�"+me->name()+"������\n");
		return;
	}
	if ((int)me->query("shen") > -2000000) {
		command("say ����Խ����Խ��׵������Ե׵ġ������޵Ķ��ĺ��������ĸ��ֵ���û��������������");
		return;
	}
    if (me->query("job_time/����")+me->query("job_time/������ͽ")+me->query("job_time/���ް���") < 1500) {
		command("say ��Ӧ�ö��Ϊ�����ҷֵ��ֵ��ǳ���ǡ�");
		return;
	}
	if(me->query_skill("huagong-dafa",1) < 350){
		command("say ������Ļ����󷨻���������������ȥ����ͽ��ѧѧ�ɡ�");
		return;
	}
	if(!me->query("quest/xx/dichuan")){
		command("say �㲢û��Ϊ�Ҵ��������κι��ף�����������");
		return;
	}
	if( me->query_temp("pending/flatter") ) {
		command("say ����˲������ɷ�����������������㣿");
		return;
	}
	else {
		command("say ���������ɱ������������ʥ����ô������");
		message_vision("�����Ϲ�΢��˫�ۣ������룬һ����$N����(flatter)�����ӡ�\n", me);
		me->set_temp("pending/flatter", 1);
	}

}

int do_flatter(string arg)
{
	object me, ob;
	me = this_player();
	ob = this_object();

	if( !arg ) return notify_fail("��Ҫ�������ɵ�ʲô�Ṧΰ����\n");
	if(me->query_condition("gb_mission") || me->query_condition("gb_busy"))
		return notify_fail("������������л��ӣ����ӵ����ؤ�������˵��\n");
	if(this_player()->query("jing") < 10)
		return notify_fail("��̫���ˣ��ȵ����İɣ�\n");

	switch(random(5)) {
		case 0 : message_vision("\n$N��$n�����޵��������˼�һ����������ѣ�һҡ�������޹⣡\n", me,ob); break;
		case 1 : message_vision("\n$N��$n�����޵����������ɴ���ڶ����������ԣ����������ţ������һ������������֮�أ�\n", me,ob); break;
		case 2 : message_vision("\n$N��$n�����޵�����������������һϯ��������Ī����ֻ����������֣�С�˸��������������ǣ�\n", me,ob); break;
		case 3 : message_vision("\n$N��$n�����޵�������������֮�������������֮�����̹��Ͽ���ٵ����������޵ڶ����������ɵ����£�\n", me,ob); break;
		case 4 : message_vision("\n$N��$n�����޵��������񹦸��������µ�һ��ս�޲�ʤ�����޲��ˣ�\n", me,ob); break;
	}

	message_vision(HIY"$N����������" + arg + "\n"NOR, this_player());
	this_player()->set("jing", 1);
	
	if( strsrch(arg, "��������") >=0 && (strsrch(arg, "�������") >=0
	 && strsrch(arg, "�������") >=0 && strsrch(arg, "�Ž��ޱ�") >=0 )) {
		command("smile");
		command("say �⻹��ࡣ\n");
		if(this_player()->query_temp("pending/flatter")){
			this_player()->delete_temp("pending/flatter");
			command("recruit " + this_player()->query("id"));
			this_player()->set("title", "�����Ϲ���ǰ��ͽ" );
			CHANNEL_D->do_channel(this_player(), "chat",  "�������ɣ�������أ��������Ž��ޱȣ�");
			return 1;
		}
		else{
			command("say �����������ô���������ǰ;������������\n");
			this_player()->set_temp("ding_flatter", 1);
			return 1;
		}
	}
	else command("say û������");
	return 1;
}

int give_drug()
{
	object drug, me, ob;

	me = this_object();
	ob = this_player();

	if(ob->query("family/family_name") == "������" && (ob->query_skill("huagong-dafa", 1) > 100)){
		if(me->query("drug_count") >= 1 && !ob->query_temp("drug_give")){
			add("drug_count", -1);
			drug = new("/d/xingxiu" + drugs[random(sizeof(drugs))] );
			drug->move(ob);
			ob->set_temp("drug_give", 1);
			message_vision("$N��$n���˵�ͷ������$nһС��ҩ�ۡ�\n", me, ob);
			return 1;
		}
		if(ob->query_temp("drug_give"))
			command("say �Ҳ��Ǹ���������");
		else command("say ����������������ʦ���������ˡ�");
		return 1;
	}
	else return 0;
}
//���ɷ��ǣ�

string ask_job()
{
	object me, ob;
	me = this_player();

	if (me->query("family/family_name") == "�䵱��"
	 || me->query("family/family_name") == "������"
	 || me->query("family/family_name") == "������"
	 || me->query("family/family_name") == "ȫ���"
	 || me->query("family/family_name") == "ؤ��"
	 || me->query("family/family_name") == "��ɽ��"
	 || me->query("family/family_name") == "������")
		return "���ǰ׵����Ե׵İɣ���������ҹ���ȥ������";
	if (me->query("combat_exp") < 1000000)
		return "�����������ټӰ����������ܿ�Ϳ���Ϊ�����ҷ����ˡ�";
	if (me->query("job_name") == "���ɷ���")
		return "�����������黹�ã���������Ϊ�ҷ��ǡ�";
	if (me->query("combat_exp") > 4000000)
		return "�����������ʲô��û��Ȥ����������Ϊ�ҷ��ǡ�";
	if (me->query("shen") >= 0 || me->query("shen") > -(me->query("combat_exp")/10))
		return "ͽ������������ĳ��������ڰ�����Щ���㲻��Ҳ�ա�";
	if (interactive(me) && me->query_temp("job_busy"))
		return "��˵Ҫ�����ɷ��ǣ���ô�������﷢����";
	if (interactive(me) && me->query_condition("wait_xx_task"))
		return "�����������黹�ã���������Ϊ�ҷ��ǡ�";
	if (me->query_condition("job_busy"))
		return "�����������黹�ã���������Ϊ�ҷ��ǡ�";

	ob = new("/d/xingxiu/obj/di");
	ob->move(me);
	ob->set("name", BLU"����̵�"NOR);
	ob->set("long", BLU"����Ѷ̵ó��棬ֻ�����ߴ�������ͨ���������Ө�ɰ���\n" NOR);
	ob->set("xx_user", getuid(me));
	me->set_temp("xx_job", 1);
	message_vision("$N�ó�һֻ���ƶ̵ѣ�����$n��\n", this_object(), me);
	return "������������鲻�ѣ�ͽ����Ҫ���Ϊ�ҷ��ǲ��ǣ�\n";
}

void destroying(object obj, object me)
{
	message_vision("$N����$n��ϸ�ض�����һ���������ص��˵�ͷ������¶����Ц�ݡ�\n", me, obj);
	destruct(obj);
}

void dest(object ob)
{
	if (!ob) return;
	if (userp(ob)) command("drop "+ob->parse_command_id_list()[0]);
	else destruct(ob);
}
//�����ױ������
int do_xian(string arg)
{
	object who, me, ob;
	mapping quest;
	who = this_player();
	me = this_object();

	if(who->is_busy() || who->is_fighting())
		return notify_fail("����æ���ء�\n");
	if(me->is_busy() || me->is_fighting())
		return notify_fail("û����������æ����\n");
	if(!arg || !objectp(ob = present(arg, who)))
		return notify_fail("��Ҫ�׸�����ʲô������\n");
	if(!who->query_temp("xx_job"))
		return notify_fail("���������ڵ����黹û����������׶�����\n");

	message_vision(HIY"\n$n�Ϲ��Ͼ��ؽ�"+ob->query("name")+HIY"�ó���˫�����ϣ���Ҫ�׸�$N��\n\n"NOR, me, who);

	if(me->is_busy()) {
		command("say ����æ���أ���ȵȡ�");
		return notify_fail("��������ȵȡ�\n");
	}
	if(!mapp(quest = who->query_temp("quest")) || !quest["id"]){
		command("say ���ø�"+ob->name()+CYN"���Ҹ��"NOR);
		return notify_fail("���ɶ��ⶫ��������Ȥ��\n");
	}
	if ( quest["time"] < TIME_TICK){
		command("say �ţ���ô�òŰ��꣬���ʲôȥ�ˣ����ҹ�һ��ȥ��");
		who->apply_condition("wait_xx_task", 40);
		return notify_fail("���ˣ����������ˡ�\n");
	}
	if(userp(ob)){
		command("stare " + who->query("id"));
		command("say �����üٻ�����ƭ�����ɣ����ҹ���ȥ��");
		message_vision("\n˵��$N����һ�ӣ�һ���ھ��������ͽ�$nɨ�����⣡\n\n", me, who);
		who->move("/d/xingxiu/ryd1");
		message("vision","ֻ����������һ����������"+who->query("name")+"�����¶���ֱ���˳�����ˤ�˸��Ľų��죡\n", environment(who), who);
		who->receive_wound("jing", 200,"�������߷ɶ�ˤ");
		who->receive_wound("qi", 250,"�������߷ɶ�ˤ");
		who->receive_damage("neili", 600);
		who->receive_damage("jingli", 500);
		who->apply_condition("wait_xx_task", 30);
		who->delete_temp("quest");
		who->set_temp("last_id", quest["last_id"]);
		who->start_busy(5);
		return notify_fail("��⣬�����ˣ�\n");
	}
	if(ob->query("name") != quest["name"] || ob->query("id") != quest["id"]) {
		command("hmm " + who->query("id"));
		command("say ���ø�"+ob->query("name")+"����������ʲô�ã�");
		return notify_fail("���������״����ˡ�\n");
	}

	ob->move(me);
	me->start_busy(random(2));
	who->start_busy(2);
	destroying(ob, me);
	call_out("done", 3, who);
	return 1;
}
//�����ױ�����
void done(object me)
{
	int job,x,j;
	job=me->query("job_time/����");
	x=job%50;

	if(!me || environment(me) != environment(this_object())) return;

	command("pat " + me->query("id"));
	command("say ��������Ȼ���ҵ�����������Ҫ�Ķ������Ҿ�ָ��ָ����ɡ�");
	if(me->query("family/family_name") == "������") {
		if(me->query_skill("huagong-dafa",1) < 180)
			me->improve_skill("huagong-dafa", me->query("job_time/����"));
		if(me->query_skill("poison",1) < 180)
			me->improve_skill("poison", me->query("job_time/����"));		
		tell_object(me, "��Ŀǰ�Ѿ�Ϊ���ɷֵ���"+chinese_number(me->query("job_time/����"))+"���ǳ\n");
	}
	tell_object(me, "���������ɵ�ָ�㣬��������˲��٣�\n");
	
	//TASK_D->give_reward(me, me->query_temp("quest"), -1, ABS(me->query("job_time/����")/25),this_object(),"����");
	//GIFT_D->check_count(me,this_object(),"����");
	//me->add("job_time/����", 1);
    //�ص�ת��ɱ��ͽ
	/*
	j = 18;
    if(me->query("m-card-vip")) j =  17;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;

	if( random(job) > 400
	&& x == 0
    && random(me->query_int()) >= 30 
    && random(me->query_str()) >= 30
    && random(me->query("kar")) >=25
	//&& me->query("family/family_name")=="������"
	&& random(j)<3 
	&& !me->query("quest/xx/tsz/zhuihun/pass")){
		command("whisper "+me->query("id")+" �������Ŭ��Ϊ�Ҵ����޲����Ϳ๤�����ҾͰ�׷�깳�������ڸ���ɡ�");
		me->set("quest/xx/zhg/pass", 1);
		log_file("quest/zhuihungou",sprintf("%8s%-10s���������%s�ε�ʱ�򣬴Ӷ������ױ�ʱ��ѧ��׷�깳����\n",
			me->name(1),"("+ capitalize(getuid(me))+")",chinese_number(job)), me);
	}
	*/
	TASKREWARD_D->get_reward(me,"����",-1,0,0,5+random(2),0,0,0,this_object());
	
	
	log_file("job/fenyou",sprintf("%-18s ������JOB���þ��� %d��Ǳ�� %d��\n",
		me->query("name")+"("+getuid(me)+")",
		me->query_temp("quest/exp_reward"), me->query_temp("quest/pot_reward")),me);
        me->set("job_name","���ɷ���");
		me->clear_condition("job_busy");
		me->delete_temp("xx_job");
		return;
	
}

string *exclude_place = ({
	"/d/wuguan/","/d/death/","/d/wizard/","/d/sld/",
});


//ɱ��ͽ����Ϊ����job ,��Ϊ���ˣ����Ӹ���job���Ѷȶ�λ�����䵱��

string ask_job5()
{
	mapping fam;
	object pp,where,target, *living ,me , ob ,partner,*list;
	
	int i,j,busy_time,shen;
	string str,menpai;
	
	me= this_player();
	//if (!me) return 0;

	shen=me->query("shen");

	if(shen > -10000 ) return "���������ɲ���Ҫ������æ��";
//100k ������
	if( me->query("combat_exp") < 100000 )
		return "���ʵս����̫���˵�ɣ�����ȥ�ҿ�ʵ�ڲ�����ģ�\n";

	//if((!pp=me->query("xx/partner")) && me->query("xx/pantu"))
	 //   return "����������һ������󣬸���ȥ�ˣ�\n"+
		 //  "��ֻ�ܷ�����ask ding about ��������ǰ��������ˣ����������ܵ�����ĳͷ���";

//	if( me->query("xx/pantu") && ((time()-(int)me->query("xx/pantu_time"))<(12*60)) )
//		return "�Ҳ��ǽ����"+pp->query("name")+"("+capitalize(pp->query("id"))+")��"+me->query("xx/pantu_place")+"ȥ����Ǹ���ͽ���";

	if(me->query_condition("gb_mission") || me->query_condition("gb_busy"))
		return "������������л��ӣ����ӵ����ؤ�������˵��";

	if( !wizardp(me) && me->query_condition("job_busy") ) {
		command("pat "+(string)me->query("id"));
		    return "������һ��������ȥ��Ϣһ����ɣ�";
	}

	if( me->query("job_name") == "����ɱ��ͽ")
	       return "������һ��������ȥ��Ϣһ����ɣ�";

	me->delete("xx/pantu_busy");

	living = livings();
	for (i=0;i < sizeof(living);i++){
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living)-1) continue;
		if(check(living[j]) ){
			target = living[j];
			str = environment(target)->query("short");
			if (str == "��Ӫ"
			 || str == HIW"����"NOR
			 || str == "��ɮ��"
			 || str == "������"
			 || str == "�ӻ���"
			 || str == "�ܵ�"
			 || str == HIR"������"NOR
			) continue;
			if( get_place(base_name(environment(target)))!="" )
				break;
		}
	}
/*
	if (me->query_temp("xx_count") > 50) {
		me->delete_temp("xx_count");
		return "û�к��ʵĴ������ɲ����������";
	}

	if( !target )
		return "��������ô����������һ����ȥ��ɣ����һ���������Ұɡ�";
	
	list = filter_array(users(), (: $1->query("combat_exp")>49999 :));
	
	partner = list[random(sizeof(list))];

	where = environment(partner);
*/
	if ((!environment(partner))
	 || environment(partner)->query("short")=="�һ�Դ"
	 || wizardp(partner)
	 || environment(partner)->query("short")=="����"
	 || environment(partner)->query("short")=="����"
	 || environment(partner)->query("short")=="�����˷�ͥ"
	 || ((string)partner->query("family/family_name") == "��Ĺ��" && partner->query_skill("yunu-xinjing", 1) < 101)
	 || (!interactive(partner))
	 || environment(partner)->query("no_fight")
	 || partner->query_temp("have_partner")
	 || partner->query("combat_exp") < me->query("combat_exp")/ 5
	 || partner == me
	 || partner->query_temp("user_type") == "worker" ){
		me->add_temp("xx_count",1);
		call_out("ask_job5", 0, me);
		return "";
	}
	else {
		if(!fam = (mapping)partner->query("family")) menpai="��ͨ����";
		else menpai=fam["family_name"];

		me->set("xx/pantu",1);
		me->set("xx/partner",partner);

		partner->delete("env/block");
		partner->set_temp("have_partner",1);

		busy_time = 40;
		me->set("xx/pantu_time",time());
		me->apply_condition("job_busy",busy_time);
		me->set("xx/pantu_place",get_place(base_name(environment(target)))+environment(target)->query("short"));
		if(wizardp(me)) tell_object(me,base_name(environment(target)));

		ob = new(__DIR__"pantu3");
		ob->set("xx_target", me);
		ob->set("xx_partner",partner);
		ob->set("xx_place", environment(target));

		if(random(20) != 1) {
			ob->do_copy(me,0);
			me->set("xx/pantu_super",0);
		}
		else {
			ob->do_copy(me,1);
			me->set("xx/pantu_super",1);
		}
		ob->move("/d/xingxiu/caiji_room");
		me->set("xx/pantu_obj",ob);
		command("hmm "+me->query("id"));

		log_file("job/pantu",sprintf("%8s%-10s��%5d������ʼ���ܼ�e��%d��p��%d��exp��%d\n",
			me->name(),"("+me->query("id")+")",me->query("job_time/������ͽ")+1,me->query("xx_jobe"),me->query("xx_jobp"),
			me->query("combat_exp")),me);
		log_file("job/pantu",sprintf("%8s%-10s��%d���������ܼ�e��%d��p��%d��exp��%d\n",
			partner->name(),"("+partner->query("id")+")",me->query("job_time/������ͽ")+1,partner->query("xx_jobe"),partner->query("xx_jobp"),
			partner->query("combat_exp")),me);

		tell_object(partner,HIY+"�������ɶ�������ǧ�ﴫ�������㣬��ȥ��"+me->query("xx/pantu_place")+"���"+HIM+me->name()+HIW+"("+ capitalize(me->query("id")) + ")"+HIY+"���ɱ��ͽ������\n"NOR);
		return "��˵����Ǹ��쵰��"+me->query("xx/pantu_place")+CYN"������û�����"+
			menpai+ partner->name()+"("+ capitalize(partner->query("id")) + ")һ��ȥ��������ͽ�ɡ�";
	}
}

/*
int give_reward(object me)
{
	int e,p,t,t1,partner,high,myexp,paexp,d,low,e2= 100 + random(51),p2= 20+random(9);

	command("welcome");
	command("say �ܺã���Ϊ�����ɲ���������࣬��Ӧ�úúüν��㡣");
	command("touch "+me->query("id"));

	if(!partner = me->query("xx/partner")){
		me->delete("xx/pantu");
		me->delete("xx_job5_finished");
		me->delete("xx/panntu_place");
		me->apply_condition("job_busy",6);
		me->delete("xx/pantu_time");
		me->delete("xx/pantu_super");
		command("say �����������ɵ��൱���ã��ҷǳ������������Ϊ��");
		command("say �����Ĵ��������ֱ�ӻ���������ȥ�ˣ�");
		command("say ��ֻ�ܷ�����ǰ��������ˣ����������յ�����ĳͷ���");
		return 1;
	}

	myexp=me->query("combat_exp");
	paexp=partner->query("combat_exp");

	high=(myexp>paexp)?myexp:paexp;
	if(high==paexp)low=myexp;
	else low=paexp;
	t1 = ABS(12-(time()-(int)me->query("xx/pantu_time"))/60);
	if(t1<2)t1=2;
	if(t1>5)t1=5;

	d=ABS(high-low);

	e = 180 + random(70);

	if (me->query("xx/pantu_super"))
		e = e * (100+random(50)) / 100;

	if ( e > 500 ) e = 400 + random(100);
	p = e/5 + random(e/10);

	me->delete("xx/pantu");
	me->delete("xx_job5_finished");
	me->delete("xx/panntu_place");
	t = time()-(int)me->query("xx/pantu_time");

	me->delete("xx/pantu_time");
	me->delete("xx/pantu_super");

	me->add("job_time/������ͽ",1);
	me->add("xx_jobe",e);
	me->add("xx_jobp",p);
	me->add("combat_exp",e);
	me->add("potential",p);
	me->set("job_name","����ɱ��ͽ");

	me->clear_condition("job_busy");

	partner->add("combat_exp",e2);
	partner->add("potential",p2);
	partner->add("xx_jobe",e2);
	partner->add("xx_jobp",p2);
	partner->set_temp("have_partner",0);

	if ( (int)me->query("potential", 1) > (int)me->query("max_pot", 1) )
		me->set("potential" , me->query("max_pot", 1) );
	if ( (int)partner->query("potential", 1) > (int)partner->query("max_pot", 1) )
		partner->set("potential" , partner->query("max_pot", 1) );

	if ((string)me->query("family/family_name") == "������"
	   && me->query_skill("poison",1) < 180)
		me->improve_skill("poison", e);

	tell_object(partner,HIC"�㱻������"+CHINESE_D->chinese_number(e2)+"�㾭�飬"+CHINESE_D->chinese_number(p2)+"��Ǳ�ܣ�\n"NOR);
	tell_object(me,HIC"�㱻������"+CHINESE_D->chinese_number(e)+"�㾭�飬"+CHINESE_D->chinese_number(p)+"��Ǳ�ܣ�\n"NOR);

	log_file( "job/pantu",sprintf("%8s%-10s��%5d��������������飺%d��Ǳ�ܣ�%d���ܼ�e��%d��p��%d��exp��%d\n",
		me->name(),"("+me->query("id")+")",me->query("job_time/������ͽ"),e,p,me->query("xx_jobe"),me->query("xx_jobp"),
		me->query("combat_exp")),me);
	log_file( "job/pantu",sprintf("%8s%-10s��%5d�δ���������飺%d��Ǳ�ܣ�%d���ܼ�e��%d��p��%d��exp��%d\n",
		partner->name(),"("+partner->query("id")+")",me->query("job_time/������ͽ"),e2,p2,partner->query("xx_jobe"),partner->query("xx_jobp"),
		partner->query("combat_exp")),me);

	return 1;
}

string ask_job5_times()
{
	object ob = this_player();

	if(!ob->query("job_time/������ͽ"))
		return "�Բ���"+ob->name()+"�������û������������������أ����͸ɰɣ�";
	return ""+ob->name()+"���������ɱ����"+HIY+CHINESE_D->chinese_number((int)ob->query("job_time/������ͽ"))+NOR+"����ͽ��";
}*/
//׽��
string ask_job4()
{
	object me=this_player();
	int shen=me->query("shen");

	if(shen > -10000 ) return "���������ɲ���Ҫ������æ��";
	if( me->query("combat_exp") < 100000 )
		return "���ʵս����̫���˵�ɣ�����ȥ�ҿ�ʵ�ڲ�����ģ�\n";
	if (me->query("family/family_name") !="������"){
		command("? "+ (string)me->query("id"));
		return "�㲻�����޵��ӣ�������������ȡ�\n";
	}
	if( me->query("combat_exp") > 2000000 )
	if (me->query("job_time/����")+me->query("job_time/������ͽ")+me->query("job_time/���ް���") > 500 )
		return "��ľ��鹻���ˣ������ñ���ȥ���ɣ�";

     //   if( me->query("job_name") == "����ץ����")
        	//return "���ץ����ӣ�����ȥ��Ϣ��ɡ�";
	if( me->query_condition("job_busy"))
		return "�㻹æ�Ÿɱ���أ����������ɡ�";
	if(me->query_condition("gb_mission") || me->query_condition("gb_busy"))
		return "������������л��ӣ����ӵ����ؤ�������˵��";

	command("ok "+ (string)me->query("id"));
	me->set_temp("chonggu_allow",1);
	me->set_temp("xx_job4", 1);
	me->set("job_name", "����ץ����");
	me->apply_condition("job_busy", 10);
	return "�ðɣ������ڿ��Խ������ȥ�ˡ�";
}

int ask_hgdf() 
{
	object me = this_player();
	int j;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N��$n����йػ����󷨵��������\n"NOR, me, this_object());
	if(me->query("family/family_name")!="������")
	{
		command("?");
		command("say �㲻�������ɵ��ӣ��ѵ���������ǲ���ɣ�"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	if (!me->query("quest/xx/dichuan"))
	{
		command("say �㲻���������еմ����ӣ��ѵ���������ǲ���ɣ�"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	if(me->query("quest/hgdf/powerup"))
	{
		command("?");
		if (me->query("title")!="�����󷨴���")
		{
			me->set("title",HBBLU+HIY"�����󷨴���"NOR);
			me->set("mytitle/quest/hgdftitle",HBBLU+HIY"�����󷨴���"NOR);
			
		}
		command("say ���Ѿ�ѧ���˻����󷨣��ѵ���������ǲ���ɣ�"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	command("look "+me->query("id"));	
	//��ͨ�������
	
	if(me->query("quest/hgdf/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("quest/hgdf/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�������ɣ�����ɡ�");
		return 1;
	}

	if(me->query_skill("huagong-dafa",1)<450)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ�Ļ����󷨵ȼ����²���450�������������򣬻���ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
	if (!me->query("hgdf/giveheadover"))
	{
		if (!me->query_temp("hgdf/giveheadhs"))
		{
			command("say �����ɽ�����ǲ��񣬷�չ��ͷ���ͣ��а���ͳһ���ִ�ҵ����ȥ�ѻ�ɽ�������������ɱ�ˣ���ͷ������\n");
			command("heng ");
			command("��������ʲô�ֶΣ���֮Ҫ��ͷ������\n");
			return 1;
		}
		if (!me->query_temp("hgdf/giveheadxz"))
		{
			command("say ������չ����ǲ��񣬷�չ��ͷ���ͣ��а���ͳһ���ִ�ҵ����ȥ���������ɱ�ˣ���ͷ������\n");
			command("heng ");
			command("��������ʲô�ֶΣ���֮Ҫ��ͷ������\n");
		//me->delete_temp("hgdf/giveheadhs");
			return 1;
		}
		if (!me->query_temp("hgdf/giveheadtls"))
		{
			command("say ������������ǲ��񣬷�չ��ͷ���ͣ��а���ͳһ���ִ�ҵ����ȥ��һ�ƴ�ʦ����ɱ�ˣ���ͷ������\n");
			command("heng ");
			command("��������ʲô�ֶΣ���֮Ҫ��ͷ������\n");
			return 1;
		}
		if (!me->query_temp("hgdf/giveheadwd"))
		{
			command("say ����䵱�����ǲ��񣬷�չ��ͷ���ͣ��а���ͳһ���ִ�ҵ����ȥ�����������ɱ�ˣ���ͷ������\n");
			command("heng ");
			command("��������ʲô�ֶΣ���֮Ҫ��ͷ������\n");
			return 1;
		}

	}
	
	me->set("quest/hgdf/time",time());
	me->set("quest/hgdf/combat_exp",me->query("combat_exp")); 
	//i= random(20);
    me->delete_temp("hgdf/giveheadhs");
	me->delete_temp("hgdf/giveheadxz");
	me->delete_temp("hgdf/giveheadtls");
	me->delete_temp("hgdf/giveheadwd");
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;

	command("sigh "+me->query("id"));
	command("say �����󷨾��������������ɵ�����书����Ȼ����������Ҿ�˵����������������û����������ˡ�");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	if(random(j)<3 
	   && random(me->query("int"))>40
	   && random(me->query("kar"))>=26)
	{
		tell_object(me,HIY"\n�㰴���������ɵ�ָ�㣬�Ի����󷨵��ռ������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me,HIG"\nһ�ɶ����ӵ��￪ʼ�����������Ͷ���ѭ��һȦ������������¥�������أ������ţ������\n"+
			"���ȫ����ԽתԽ�죬����������뺣֮�ơ����Ȼ�о�ȫ������Ȼ��ͨ��һƬ������ˬ��\n"NOR);
		tell_object(me,HIW"\n�㽫�������ɽ�������ݺ���ǰ�Լ���ѧ�໥ӡ֤���漴�����̲�ס������Ц��\n"NOR);
		tell_object(me,HIC"\n��ϲ������ǧ����࣬���ڽ��������ڻ��ͨ��\n"NOR);
       
		
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("flatter "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("title",HBBLU+HIY"�����󷨴���"NOR);
		me->set("mytitle/quest/hgdftitle",HBBLU+HIY"�����󷨴���"NOR);
		me->set("quest/hgdf/powerup",1);
		log_file("quest/hgdf", sprintf("%8s(%8s) ʧ��%d�γ������򻯹��󷨵ľ������ء�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/hgdf/fail"),j,me->query("combat_exp")) );
	}
	else
	{
		me->add("quest/hgdf/fail",1);
		command("buddha");
		tell_object(me,HIY"�������������ɵ�ָ�㣬��Ȼ��˵�˻����󷨵İ��أ����ǶԻ����󷨵��ռ�����ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/hgdf", sprintf("%8s(%8s) �����󷨰��ؾ�������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/hgdf/fail"),j,me->query("combat_exp")) );
	}

	return 1;
}

int accept_object(object who, object obj)
{
	int job,x,j;
	object obb;
	job=who->query("job_time/����");
	x=job%50;
	
	obb=obj->query("kill_by");

	if (who->query("family/family_name")!="������") return 0;
//ֻ��ɱ�˺󽻸��̵Ѳ���Ч����������ױ��ظ�
	if (obj->query("id")=="duan di"
		&&who->query_temp("quest/type") == "ɱ"
		&&who->query_temp("quest/killover")
		&&who->query_temp("quest/corpse"))
	{
		
		//TASK_D->give_reward(who, who->query_temp("quest"), -1, "������" ,"����");
		who->add("job_time/����", 1);
    
	    TASKREWARD_D->get_reward(who,"����",-1,0,0,5+random(2),0,0,0,this_object());
    
		who->set("job_name","���ɷ���");
		/*log_file("job/fenyou",sprintf("%-18s ������JOB���þ��� %d��Ǳ�� %d��Ŀǰ���飺%d��\n",
			who->query("name")+"("+getuid(who)+")", who->query_temp("quest/exp_reward"),
			who->query_temp("quest/pot_reward"), who->query("combat_exp")),who);
		*/
		who->clear_condition("job_busy");
		who->delete_temp("xx_job");
		who->delete_temp("quest");
		return 1;
	
	}
	///TASK_D->give_reward(me, me->query_temp("quest"), -1); //����by sohu

	
	if (obj->query("id")=="shouji" &&obj->query("name")=="��������׼�" && obb->query("id")==who->query("id"))
	{
		command("say �ô��һ��ͷ­����Ϊ��ɱ���������⹷��������ɽ���ܲ�Ⱶ���ʱ��\n");
		command("laugh ");
		command("chat �������Ҵ��������˻�ɽ���γ�����ﲻ�ٹ�˳���ң�\n");
		who->set_temp("hgdf/giveheadhs",1);
		destruct(obj);
		return 1;
	}
	
	if (obj->query("id")=="shouji" &&obj->query("name")=="������׼�" && obb->query("id")==who->query("id"))
	{
		if (!who->query_temp("hgdf/giveheadhs"))
		{
			command("say ���������ȥɱ�˻�ɽ�����壬��ȥ��ô��\n");
			return 1;
		}
		command("say �ô��һ��ͷ­����Ϊ��ɱ�������⹷���������չ����ܲ�Ⱶ���ʱ��\n");
		command("laugh ");
		command("chat �������Ҵ������������չ����γ�����ﲻ�ٹ�˳���ң�\n");
		who->set_temp("hgdf/giveheadxz",1);
		destruct(obj);
		return 1;
	}
	
	if (obj->query("id")=="shouji" &&obj->query("name")=="һ�ƴ�ʦ���׼�" && obb->query("id")==who->query("id"))
	{
		if (!who->query_temp("hgdf/giveheadxz"))
		{
			command("say ���������ȥɱ�����չ�������ȥ��ô��\n");
			return 1;
		}
		command("say �ô��һ��ͷ­����Ϊ��ɱ��һ���⹷�����������»��ܲ�Ⱶ���ʱ��\n");
		command("laugh ");
		command("chat �������Ҵ������������������γ�����ﲻ�ٹ�˳���ң�\n");
		who->set_temp("hgdf/giveheadtls",1);
		destruct(obj);
		return 1;
	}
	if (obj->query("id")=="shouji" &&obj->query("name")=="��������׼�" && obb->query("id")==who->query("id"))
	{
		if (!who->query_temp("hgdf/giveheadtls"))
		{
			command("say ���������ȥɱ��һ����ͺ¿����ȥ��ô��\n");
			return 1;
		}
		command("say �ô��һ��ͷ­����Ϊ��ɱ���������⹷�������䵱�ɻ��ܲ�Ⱶ���ʱ��\n");
		command("laugh ");
		command("chat �������Ҵ����������䵱���γ�����ﲻ�ٹ�˳���ң�\n");
		who->set_temp("hgdf/giveheadwd",1);
		who->set("hgdf/giveheadover",1);
		destruct(obj);
		return 1;
	}

}


//ask ɱ��ͽ
string ask_pantu()
{
	object me, ob, *living, target;
	string str,str2,title;
	string str_temp;
	object room, oroom, lastroom;
	int i, j, k, a, b,t;
	string * exits,*dirs;
	string far;

	me=this_player();
	str2 = me->query_temp("xx/xx_job_place");
	str_temp = "";

	if (me->query_temp("xx/xx_job") && !me->query_temp("xx/xx_job_place"))
		return "���������Բ��𣬵ص�������������������ɡ�";

	if (me->query("combat_exp") < 100000 )
		return "��λ" + RANK_D->query_respect(me) + "�书δ�ɣ�����ȥ����Ĺ����ɣ�";

	if(me->query_temp("quest/busy")) 
		return "����������û�и���������㻹���ȴ����������������˵�ɡ�";

	if(!wizardp(me)){
		if (me->query("shen")>-10000)
			return "�ߣ�������Լ�һ������������������ʲô��";

		if ( me->query_condition("killer"))
			return "�������ǹٸ�׽�õ�Ҫ�����������������ͽ��";

		if (me->query_temp("xx/xx_job"))
			return "�Ҳ��Ǹ��������������ڵ��ҡ���Ϳ�ȥ�ɣ�";

		if (me->query("job_name") =="������ͽ")
			return "�������������ͽ���񣬻�����ȥ��Ϣһ��ɡ�";

		//if (me->query("shen") < 1 && !wizardp(me) )
			//return RANK_D->query_respect(me) + "�����������������޷������������������";

		if ( me->query_condition("job_busy")){
			if (me->query("job_name")=="������ͽ")
				return "������ʱ��û�й�������ȥ����";
			if( me->query("job_name"))
				return "�������"+me->query("job_name")+"���񣬻�������Ϣһ��ɡ�";
			return "����æ�ű�������ء�";
		}

		if (me->query_condition("xx_job"))
			return "������ʱû���ʺ���Ĺ�����";
  
	}

	ob=new(__DIR__"pantu");
	ob->move(environment(this_object()));
		
	living = livings();
	
	for (i=0;i<sizeof(living);i++)
	{
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living)-1) continue;
		if(check(living[j]) )
		{
			target = living[j];
			room = environment(target);
			if( !mapp(room->query("exits")) || sizeof(room->query("exits"))<1 ) continue;
			if( get_place(base_name(room))!="" ) 
			{
				oroom = room;
				if ( random(10)<3 && target->query("race")=="����" ) {
					j = 0;
					break;
				}

				lastroom = room;
				j = 1+random(4);//�ĵú���Щ:)
				for(k=0;k<j;k++) {
					if (!room->query("exits")) break;
					exits = values(room->query("exits"));
					dirs = keys(room->query("exits"));
					b = sizeof(exits);
					t =0;
					while( (a=random(b))>=0 && b>1 && t<10 ) {
						t++;
						if(!room->valid_leave(ob, dirs[a])) continue;
						if (b==2)
							if ((exits[0]==base_name(lastroom) && exits[1]==base_name(oroom))
							 || (exits[1]==base_name(lastroom) && exits[0]==base_name(oroom)))
								break;
						if (exits[a]==base_name(lastroom) || exits[a]==base_name(oroom)) continue;
						break;
					}
					//write(sprintf("%d\n",t));
					lastroom = room;
					//��ʱ�޸�һ��
					//if(!arrayp(exits)||!exits[a]||!(room = find_object(exits[a])) )
					if(!arrayp(exits)||(sizeof(exits)<(a+1))||!exits[a] || !(oroom = find_object(exits[a])) )
					//	if( !(room = load_object(exits[a])) )
							break;
				}
				if(k<j) continue;
				break;
				}
			
		}
	}

	if( !target || !room )
		return "��ʱû��������Ҫ�������һ��������ɡ�";
    me->set_temp("xx/ob",ob); //�����¼npc���Ա㽫��ɾ��
	me->set_temp("xx/xx_job",1);
	me->set_temp("xx/xx_job_place", get_place(base_name(oroom))+oroom->query("short"));
	me->apply_condition("xx_job",20+random(10));
	me->apply_condition("job_busy",20+random(10));
	command("nod "+me->query("id"));
        
	if (me->query("bonus/������ͽ") >= 10 || !me->query("bonus/������ͽ") || me->query("bonus/������ͽ") < 1)
	{
		if (me->query("bonus/������ͽ") == 10)
			me->set("bonus/������ͽ", 5);
		else
			me->set("bonus/������ͽ", 1);
	}
	else
		me->add("bonus/������ͽ", 1);        

	ob->set_temp("target", me->query("id") );
	ob->setparty(me->query("bonus/������ͽ"),me->query("max_pot")-100,me->query("combat_exp"));
	
	//����ӽ�ȥ״̬
	ob->copy_player(me);//�ȳ�ʼ��npc��Ѫ���������һ�»���	
	
	ob->move(room); 
	title=ob->query("title")+ob->query("family/family_name");
	ob->set("title",title);

	log_file("job/xx_job",sprintf("%s(%s)��ʼ������ɱ��ͽjob,Ŀǰʵս���飺%d\n", me->name(),me->query("id"),me->query("combat_exp")),me);
	str = strip(me->query_temp("xx/xx_job_place"));

	if(wizardp(me) && me->query("env/test")){
		tell_object(me,"Ŀ��Npc�� "+base_name(oroom)+" �Ƶ�-> "+base_name(room)+"    "+room->query("short")+"\n");
		tell_object(me,"Round:"+me->query("bonus/������ͽ")+" !\n");
	}
	if (j)
		far = HIY+"��Χ��Բ"+CHINESE_D->chinese_number(j)+"��֮��"+GRN;
	else
		far = "";

	if (strlen(str)<=1) {
		tell_object(me, GRN"����������Ķ�������˵������˵"+ob->query("title")+HIC+ob->query("name")+GRN"����\n"
			+HIY+ CHINESE_D->font(str) + GRN + far +"���ң�������ȥ����Ѳ��һȦ��\n");
                
	} else
		tell_object(me, GRN"����������Ķ�������˵������˵"+ob->query("title")+GRN+"��"+ob->query("name")+"����"+ me->query_temp("xx/xx_job_place") +GRN + far + "���ң�������ȥ����Ѳ��һȦ��\n");
		//tell_object(me, GRN"����������Ķ�������˵������˵"+ob->query("title")+GRN+ob->query("name")+"����"+ me->query_temp("xx/xx_job_place") +GRN + far + "���ң�������ȥ����Ѳ��һȦ��\n");
        
	if (ob->query("family/family_name")=="������")
		str_temp += GRN"����������Ķ�������˵����"+RANK_D->query_self(this_object())+"��׷�鵽�����������޳�����Ϊ�ó�"HIC+to_chinese(ob->query("f_w_skill"))+GRN"�Ĺ���\n"+
			RANK_D->query_respect(ob)+"���ܽ�����ɱ������Ϊ������ȥһ����Ҳ��Ϊ"+RANK_D->query_self(this_object())+"�ָ��������Ե��м�������\n";
	else {
		str_temp+=GRN"����������Ķ�������˵���������ɵ�������������������"HIY+ob->query("family/family_name")+GRN"��";
		if (random(2)==0)
			str_temp+="��ͽ��";
		else
			str_temp+="���֣�";
		str_temp+= "��Ϊ�ó�"HIC+to_chinese(ob->query("f_w_skill"))+GRN"�Ĺ���\n";
	}

	switch ((int)me->query("bonus/������ͽ"))
	{
		case 6..7:
			str_temp+=GRN"����������Ķ�������˵�������˵��书" + HIC + "��Ϊ�˵�" + GRN + "����ɵ�С�ĶԸ�Ŷ��\n"NOR;
			break;
		case 8..9:
			str_temp+=GRN"����������Ķ�������˵�������˵��书" + HIC + "��������" + GRN + "����ɵ�С��Ӧ����\n"NOR;
			break;
		case 10..11:
			str_temp+=GRN"����������Ķ�������˵�������˵��书" + HIW + "���뻯��" + GRN + "���򲻹��ɲ�Ҫ���ܡ�\n"NOR;
	}	
       		
	tell_object(me, str_temp);
	tell_room( environment(this_object()), this_object()->name() + "��" + me->name() + "����С����˵��Щ����\n", ({ me, this_object() }) );              
	return "���ȥ��أ�һ��С�İ���";
}

int check(object ob)
{
	object room;
	string room_name;

	if(!objectp(ob)
	|| !ob->query("startroom")      
	|| ob->query("env/invisibility")
	|| ob->query("no_quest")
	//|| member_array(ob->query("id"), no_kill_list) != -1
	|| userp(ob)
	|| ob->query("attitude")=="aggressive"
	|| ob->query("have_master")
	|| !objectp(room=environment(ob))
	|| room->query("no_fight")
	|| room->query("quest")
	|| room->query("outdoors") == "���ش��"
	|| room->query("short") == "���º�ȭ��"
	|| room->query("short") == "��ɮ��"
	|| strsrch(room_name = file_name(room),"/d/") != 0                    
	|| strsrch(room_name, "/d/wizard/") == 0
	|| strsrch(room_name, "/d/wuguan/") == 0
	|| strsrch(room_name, "/d/death/") == 0
	|| strsrch(room_name, "/d/mingjiao/lsd/") == 0
	|| strsrch(room_name, "/d/mingjiao/bhd/") == 0
	|| strsrch(room_name, "/d/shaolin/fumoquan") == 0
	//|| strsrch(room_name, "/d/xiaoyao/") == 0
	//|| strsrch(room_name, "/d/quanzhen") == 0
	//|| strsrch(room_name, "/d/menggu/") == 0
	|| strsrch(room_name, "/d/xiakedao/") == 0
	|| strsrch(room_name, "/d/luoyang/") == 0    
	|| strsrch(room_name, "/d/beijing/") == 0
	|| strsrch(room_name, "/d/huashan/hamasuperquest") == 0
	|| strsrch(room_name, "/d/baituo/") == 0)
		return 0;
	return 1;
}


int ask_finish()
{
	int e,shen,count,j,i,time;
	int bo,s,job,x;
	mapping fam;
	object ob,silver;
	ob = this_player();

	job=ob->query("job_time/������ͽ");
	x=job%50;

	if (!ob) return; 

	fam = ob->query("family");
	count = ob->query("job_time/������ͽ",1);

	bo = (int)ob->query("bonus/������ͽ");
	j = ob->query("bonus/������ͽ");

	e = 110*j + random(100);        

	if(e <= 100) e = 100+random(25);
	if(e>=500) e = 400+random(20);
			
	if(ob->query_temp("xx/xx_job_lost2")) {
		command("faint "+ob->query("id"));
		command("say "+ob->name()+"�������ɵ���������"+ob->query_temp("xx/xx_job_lost2_man")+"�Ѿ�������Ƕ����������ˣ�");
		ob->delete_temp("xx/xx_job");
		ob->delete_temp("xx/xx_job_place");
		ob->delete_temp("xx/xx_job_lost2");
		ob->delete_temp("xx/xx_job_lost2_man");
		ob->delete_temp("xx/xx_jobok");
		ob->add("bonus/������ͽ",-3);
		ob->apply_condition("job_busy", 3);
		return 1;
	}
	if(ob->query_temp("xx/xx_job_lost") && !ob->query_temp("xx/xx_jobok") ) {
		command("sigh "+ob->query("id"));
		command("say "+ob->name()+"����ô��ģ���Ȼ���Ƕ��������ˣ�");
		ob->delete_temp("xx/xx_job");
		ob->delete_temp("xx/xx_job_place");
		ob->delete_temp("xx/xx_job_lost");
		ob->delete_temp("xx/xx_jobok");
		ob->add("bonus/������ͽ",-3);
		ob->apply_condition("job_busy", 3);
		return 1;
	}
       
	if(ob->query_temp("xx/xx_jobok") ){        	
		command("thumb "+ob->query("id"));
		command("say �ܺã�ף���������������ȥ��Ϣ��Ϣ�ɣ�");            
		count += 1;
		ob->set("job_name","������ͽ");
		
		ob->delete_temp("xx/xx_job");
		ob->delete_temp("xx/xx_job_place");
		ob->delete_temp("xx/xx_jobok");
		
		if( ob->query("family/family_name")!="�һ���")
			shen = -1;
		else
			shen = 0;

		//�µ����䵱������㷽ʽ�����Ѷ����ӽ�������ģʽ
		switch(bo)
		{
			case 0..5:
				TASKREWARD_D->get_reward(ob,"������ͽ",shen,0,0,1 + random(2),0,0,0,"������");                           
			break;
			case 6..7:
				bo = bo + 6;
				TASKREWARD_D->get_reward(ob,"������ͽ",shen,0,0,bo,0,0,0,"������");                         
			break;
			case 8..9:
				bo = bo + 10;
				TASKREWARD_D->get_reward(ob,"������ͽ",shen,0,0,bo,0,0,0,"������");    
			break;
			case 10..11:
				bo = bo * 2 + 1;
				TASKREWARD_D->get_reward(ob,"������ͽ",shen,0,0,bo,0,0,0,"������");
			break;
			default:
				TASKREWARD_D->get_reward(ob,"������ͽ",shen,0,0,1 + random(2),0,0,0,"������");
			break;
		}
		silver=new("clone/money/silver");
		s=10+random(20);
		silver->set_amount(s);
		silver->move(ob);
		message_vision(CYN"\n������̧��ͷ������$N�ٺ�Ц������������˱��£��������е���Ǯ���㣬����ȥ���ƺ�ȥ�ɣ�\n"NOR,ob);
		message_vision(CYN"������˳�ֵݸ�$N"+chinese_number(s)+CYN"���׻�����"HIW"����"CYN"��\n"NOR,ob);

		

		i = 40 - ob->query_condition("xx_job");
		if (i >= 18)
		{
			ob->apply_condition("job_busy",1);            			
		}
		else ob->apply_condition("job_busy", 3);
		     ob->apply_condition("xx_job",1);
		    
			
				
		// yttlg quest.
		// ����ֵ���� 10M �䵱����������� 2000
		// ��Ե��������� 25 24Сʱһ�� ����������ơ�
		
		time = time() - ob->query("quest/xx/tsz/zhuihun/time");                                           
		


		if (random(ob->query("job_time/������ͽ")) > 2000 
		&& time > 86400
		&& ob->query("combat_exp")>1000000
		&& random(ob->query("kar")) > 27
		&& x==0
		&& random(10)==2
		&& !ob->query_temp("quest/xx/tsz/zhuihun/story")
		&& !ob->query("quest/xx/tsz/zhuihun/pass")
		&& ob->query("family/family_name")=="������") 
		{      
			
			ob->set_temp("quest/xx/tsz/zhuihun/story",1);
			//ob->set("quest/xx/tsz/zhuihun/time", time()); ���ﲻ������ʱ�䣬��Ȼ�޷�����
			log_file("quest/xxzhuihun", sprintf(HIR"%s(%s) ������ɽ�ȷ�׷���������Դ��%d�����飺%d��\n"NOR, ob->name(1),ob->query("id"), ob->query("kar"),ob->query("combat_exp")) );

			command("say "+ob->query("name")+",������Ϊ������Ϊ����֮��,������ճ���Ϊ�ڿ죬���Ծ���������Щ���С�\n");
			command("say ֻ�����ž������������������ף���������������ΪϬ������ʽ�似��\n");
			command("say ������������ɽ�ȷ�׷������ľ��⣬��ô����˭����ĵ��֣�\n");
			command("say ��Ҫ��ʱ����������̣�\n");
		}
		return 1;
	}
	else {
		command("? "+ob->query("id"));
		command("kick "+ob->query("id"));
		command("say "+ob->name()+"����ô��ģ�����û��,�ҿ����ǵ������ˣ�");  
		return 1;
	}
	return 1;
}


string ask_fail()
{
	object ob = this_player();
	if(ob->query_temp("xx/xx_job")){
		ob->delete_temp("xx/xx_job");
		ob->delete_temp("xx/xx_job_place");
		ob->delete_temp("xx/xx_jobok");//����Ҳ�к�wd���Ƶ�bug
		ob->apply_condition("xx_job",10);//����jobbusy
		if (ob->query_temp("xx/ob"))
		{	
	       destruct(ob->query_temp("xx/ob"));
           ob->delete_temp("xx/ob");   
		}


		if (ob->query("bonus/������ͽ")<=5)
		{
			ob->apply_condition("job_busy", 8);
			ob->set("bonus/������ͽ",0); 
			return ob->name()+"����̫����ʧ���ˣ���Ȼ��ô���ɲ��ã������°ɣ�";
		}
		else if (ob->query("bonus/������ͽ")>5)
		{
			ob->apply_condition("job_busy", 4); 
			ob->add("bonus/������ͽ",-3);
			return ob->name()+"���������ȷʵ�Ƚ�����ɣ��´θ���򵥵ģ������°ɣ�";                	
		}
	}
	return ob->name()+"������û��������������Ϲ����ʲôѽ��\n";
}
// ׷������� ����
string ask_zhuihun()
{
	
	object me=this_player();
	
	if (me->query("quest/xx/tsz/zhuihun/pass"))
	{
		 me->set("title",HIB"������ ׷�������"NOR);
		 me->set("mytitle/quest/zhuihuntitle",HIB"������ ׷�������"NOR);
		return "���Ѿ��ڻ��ͨ���ֻ��е�׷������������⡣\n";
	}

	if (!me->query_temp("quest/xx/tsz/zhuihun/story"))
	{
		command("say �ó����������첻�ɻ��ɧ�ű����ɣ�\n");
		return "";
	}
	if (me->query("family/family_name")!="������"||me->query("family/master_name")!="������")
	{
		return "�㲻�������ɵ��ӣ����˹�Ħʲô��\n";
	}
	if (me->query_skill("tianshan-zhang",1)<500)
	{
		command("say �����ɽ�ȷ�������500��,�޷���Ħ����ʲô��\n");
		return "��~��\n";
	}
	
	if (me->query_skill("huagong-dafa",1)<500)
	{
		return "��Ļ����󷨼�����500��,�޷���Ħ����ʲô��\n";
	}
	
	if (me->is_busy())
	{
		return "������æµ�У��԰����꣡\n";
	}

	if (time()-me->query("quest/xx/tsz/zhuihun/time")<86400)
	{
		return "���ֻ�ȫƾ�������Ƶ�������к����档\n";
	}
	command("look "+me->query("id"));
	command("pat "+me->query("id"));
	command("say ��Ȼ������ݻ�Ե���ҾͰ��㣡\n");
	me->start_busy(99);
	me->delete_temp("quest/xx/tsz/zhuihun/story");//ɾ����ʱ��ǣ�����©��
	if (me->query_temp("canwu_zhuihun"))
	{
		return "�����ڲ����У��԰����꣡\n";
	}
	remove_call_out("thinking_zh");
	call_out("thinking_zh",1,me);
	return "�ߣ�\n";
}

int thinking_zh(object me)
{
	int i,j;
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	i=random(j);

	if (me->query("kar")>30) 
	{
	  log_file("quest/bug", sprintf("%s(%s) ����׷�������ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
	}
	if(me->query_temp("canwu_zhuihun")<(10+random(10)))
	{  
	  me->add_temp("canwu_zhuihun",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ��Ħ���ɵ�һ��һʽ������Щ�书�˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n��Ȼ�����ƺ�ץס��һЩ����\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n���������״̬������һƬ�������ƺ�Ҫץס�Ǹ������ˣ�..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ����������ģ������������ƺ���Щ����.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ�����ƿ����..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n��˼άƯ���ڿ��У�����Ӥ����ԡ.������ˬ.\n"NOR);
			break;
		default:tell_object(me,YEL"\n��̾��һ�������������ǲ�����Ч����.\n"NOR);
			break;
	  }
      
	  tell_room(environment(me),HIC"\n"+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));
	  
	  remove_call_out("thinking_zh");
	  call_out("thinking_zh",3+random(3), me);

   } 
   else if (i<3
			&& random(me->query("kar"))>28
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N����������Ц����������˵������ԭ�����������������񼼣���\n"NOR,me); 
		 message_vision(HIR"\n$N ���ֻ����������ɽ�ȷ��еġ�׷������������İ��塣\n"NOR,me); 
        // message_vision(HIY"\n$N`���»����������������������ڵ�����ذ���⡾�������С��İ��أ���\n"NOR,me); 
         log_file("quest/tszzhuihun", sprintf("%s(%s) ���ܳɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�������ɽ�ȷ�֮׷����������İ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xx/tsz/zhuihun/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/xx/tsz/zhuihun/time",time());
		 me->set("quest/xx/tsz/zhuihun/pass",1);
		 me->set("title",HIB"������ ׷�������"NOR);
		 me->set("mytitle/quest/zhuihuntitle",HIB"������ ׷�������"NOR);
		 me->delete_temp("canwu_zhuihun");
		 me->start_busy(1);
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵����������ֻ��е��״���ʲô���İ��أ��������˹��ˡ���\n"NOR,me); 
		 message_vision(HBYEL+HIR"\n�������¶��ֻ�����ʧ�ܣ�\n"NOR,me); 
         log_file("quest/tszzhuihun", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ�����ɽ�ȷ�׷�������������ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xx/tsz/zhuihun/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/xx/tsz/zhuihun/fail",1);
		 me->set("quest/xx/tsz/zhuihun/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_zhuihun");
		 return 1;
   }
	

}