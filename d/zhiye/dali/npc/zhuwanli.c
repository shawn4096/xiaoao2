//by cool 98.3.25
// ���ܺ�wd,xs jobһ������River@SJ 2000.7.19

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
	set_name("������", ({ "zhu wanli","zhu","wanli" }));
	set("title", "��������������ҽ�");
	set("gender", "����");
	set("age", 33);
	set("str", 27);
	set("dex", 26);
	set("long", "���������������ϲ���һ��������Ӣ�����ˡ�\n");
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
    create_family("������", 15 , "�׼ҵ���");

	set("max_qi", 9000);
	set("neili", 9000);
	set("max_neili", 9000);
	set("jiali", 120);
	set("inquiry", ([
		"����" : (: ask_job :),
		"job" : (: ask_job :),
		"����" : (: ask_fangqi :),
		"fangqi" : (: ask_fangqi :),
		"���־�" : (: ask_diao :),

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
		command ("say ����޷����־���Ҫ�������ԣ������Բ���25��������������Ե��");
		return "";
	}
	if (me->query("family/family_name")!="������" ){
		command ("say ����������µ����ˣ��Ҳ����������ˣ�");
		return "";
	}
	if (me->query("tls") && me->query("family/family_name")=="������" ){
		command ("say ���Ѿ��������³��ҵ����ˣ�ѧ��ɱ���Ĺ�����������");
		return "";
	}
	if (me->query_skill("qingxu-bian",1)<200){
		command ("say �������޷�����200��˵����Ҳ��������");
		return "";
	}
	command("say ��Ȼ��������书��Ե���Ҿ͸���˵������Դ��\n");
	command("say ���Ź�����Ҳ����Ϥ������֪��˭���ó���\n");
	command("say ����һ�ƴ�ʦ�������Ĵ���������˷ǳ��ó��˼��ܣ���ȥ�������ɡ�\n");
	me->set_temp("quest/tls/askzhu",1);
	return "��λǰ��Ƣ���Ź֣���Ҫ������������Ҫ��\n";
}
void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping fam = ob->query("family");
	if (ob->query("gender") == "Ů��"){
		command ("say ��λС�������������Ůͽ���㻹����ذɡ�");
		return;
	}
	if (ob->query("tls") && fam["family_name"]=="������" ){
		command ("say ���Ѿ��������³��ҵ����ˣ��Ҳ����������ˣ�");
		return;
	}
	if(ob->query("int") < 25){
		command("say ѧ�Ҵ���μ��书������ߣ����ҿ�" + RANK_D->query_respect(ob) + "�����Բ���25�������ƺ�������ϰ��");
		return;
	}
	if ((int)ob->query("shen") < 100000){
		command ("say  �Ҵ���������������ɣ����ҿ�" + RANK_D->query_respect(ob) +"������10k�����ʺ����Ҵ�����ϡ�");
		return;
	}
	if ( fam && fam["master_name"] == "������"){
		command("shake");
		command("say "+RANK_D->query_respect(ob)+"�Ѱ�������Ϊʦ��"+RANK_D->query_self(me)+"����������Ϊͽ��");
		return;
	}
	if( fam && fam["master_name"] == "������"){
		command("haha");
		command("say "+RANK_D->query_respect(ob)+"���ǻ�����ǰ��������"+RANK_D->query_self(me)+"����������Ϊͽ��");
		return;
	}
    if( fam && fam["family_name"!="������"] ){
		command("sigh ");
		command("say "+RANK_D->query_respect(ob)+"�㲻�����������׼ҵ��ӣ�����������Ϊͽ��");
		return;
	}
	if ((int)ob->query_skill("duanjia-quan", 1) < 200 ){
		command("say �Ҳ�����������֮�ˣ��㻹�Ƕ�������Ķμ�ȭ��200�ɡ�");
		return;
	}
    if( (int)me->query("family/generation")<15){
		command("sigh ");
		command("say "+RANK_D->query_respect(ob)+"���Ѿ���ǰ����ʦ�̵�������������Ϊͽ��");
		return;
	}
	command("smile");
	command("say �ܺã�" + RANK_D->query_respect(ob) + "ֻҪ��Ϊ�Ҵ�������£����ձض��������ɾ͡�");
	command("recruit " + ob->query("id") );
	ob->set("title","��������������ܼ�");
	return;
}


string ask_fangqi()
{
	object ob = this_player();
	object obj;
	int i;
	string site;

	if (!ob->query_temp("dali_songxin"))
		return RANK_D->query_respect(ob) +"�㲢û���������ŵ�����˵ʲô��������";

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
        	//��ͬsite,�۳��Ľ�����ͬ
        	if (site=="sh" || site=="sh2")
	{
		ob->add("combat_exp", -(20+random(20)));
	}
	else
	{
		ob->add("combat_exp", -(20+random(20)));		
	}
	return "��Ȼ"+ RANK_D->query_respect(ob) +"�����ˣ�Ҳ�Ͱ��ˡ�";
}

string ask_job()
{
	object me, *living, target, ob, obj;
	int time,i,j;
	string str;

	ob=this_player();
	me=this_object();

	if (!wizardp(ob) && !ob->query_temp("dali_join"))
		return RANK_D->query_respect(ob) +"���㲻�Ǳ�������ӣ��˻��Ӻ�˵��";

	if (ob->query_temp("dali_songxin"))
		return "�㲻���Ѿ��������ŵ������𣿻�����ȥ����";

	if (ob->query("job_name") == "��������" && !wizardp(ob))
		return "�����������������񣬻���ȥ��Ϣһ��ɡ�";

	if (ob->query_condition("dali_songxin") > 0)
		return "������ʱû�и���������ٵ�"+chinese_number((ob->query_condition("dali_songxin")+5)/6)+"��ʱ���ɡ�";

	if( ob->query_condition("job_busy"))
		return "����ȥ��Ϣһ��ɣ�";

	if (ob->query("combat_exp") < 160000)
		     return ("��Ĺ��򻹲���160k�������ſ��Ǻ�Σ�յ��£��ҿɲ��ҽ�����������");

	if(ob->query_temp("quest/busy")) //added by tangfeng ��quest��ͻ
		return "����������û�и���������㻹���ȴ����������������˵�ɡ�";


	living = livings();
	for (i=0;i < sizeof(living);i++){
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living) -1) continue;
		if(check(living[j]) ){
			target = living[j];
			str = environment(target)->query("short");
			if( str == "��ɮ��"
			 || str == HIR"������"NOR
			 || str =="���º�ȭ��"
			 || str == "��շ�ħȦ" ) continue;
			if( get_place(base_name(environment(target)))!="" ) break;
		}
	}

	if( !target )
		return "��ʱû������Ҫ�ͣ����һ��������ɡ�";

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
			command("tell "+ ob->query("id")+" �������ܺ������͵���"+ob->query_temp("songxin/where")+GRN"���ġ�"+ob->query_temp("songxin/target_name")+GRN"�����ϡ�");
			break;
		}
		case 1:{
			command("smile "+ ob->query("id"));
			command("tell "+ ob->query("id")+" �����������з��ţ���ȥ�����͵���"+ob->query_temp("songxin/where")+GRN"���ġ�"+ob->query_temp("songxin/target_name")+GRN"�����ϡ�");
			break;
		}
		case 2:{
			command("consider");
			command("tell "+ ob->query("id")+" ��Ͻ������͵���"+ob->query_temp("songxin/where")+GRN"���ġ�"+ob->query_temp("songxin/target_name")+GRN"�����ϡ�");
			break;
		}
	}
	message_vision("$N����$nһ���ܺ���\n",me,ob);
	ob=new("/d/dali/job/dali_letter");
	ob->set("ever_owner",getuid(this_player()));
	ob->move(this_player());
	return "·�ϳ���ǿ�˳�û�����С�ġ�";
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
	|| ob->query("race") !="����"
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
