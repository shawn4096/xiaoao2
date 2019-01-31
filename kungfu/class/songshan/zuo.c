// zuo.c ������
// Update by looklove at 2000/8/25
// Modify by Looklove for add log_file at 2000/9/1
// Looklove@SJ 2000/10/22 fixed fangqi's bug
// Modified by darken@SJ
// Lklv 2001.10.19 modified
// edit by sohu 2014 12/29
#include <ansi.h>
#include "zuo.h"

inherit NPC;

int do_chaozong();
int do_hanbing();
int do_ask();
int do_cancel();
int do_hanbing();
//int do_chaozong();
int do_hssb();
int do_jueji();
//int think_ssjf();
string ask_times();
string ask_hb();
string ask_grj();



void create()
{
	object ob,ob2,ob3;

	set_name("������", ({ "zuo lengchan", "zuo", "lengchan" }));
	set("nickname", HIR"��������"NOR);
	set("long", "��ɽ�������������ǵ����������˲��������书��Ȼ�����뻯��
		Ϊ���ȸ����ǣ�����ٳ���������һ�ᵽ�������������֣��޲���Ȼ��\n");
	set("gender", "����");
	set("age", 52);
	set("per", 20);
	set("attitude", "heroism");
	set("class", "songshan");
	set("shen_type", -1);
	set("str", 29);
	set("int", 28);
	set("con", 28);
	set("dex", 28);
	set("unique", 1);
	set("no_bark",1);

	set("max_qi", 29500);
	set("max_jing", 8000);
	set("eff_jingli", 8000);
	set("jiali", 200);
	set("combat_exp", 13000000);
	set("shen", -180000);
	set("max_neili", 26000);
	set("neili", 26000);

	set_skill("literate", 220);
	set_skill("songyang-jue", 220);
	set_skill("force", 500);
	set_skill("dodge", 500);
	set_skill("hand", 500);
	set_skill("strike", 500);
	set_skill("parry",500);
	set_skill("sword", 500);
	set_skill("songshan-jian", 500);
	set_skill("songyang-shou", 500);
	set_skill("zhongyuefeng", 500);
	set_skill("hanbing-shenzhang", 500);
	set_skill("hanbing-zhenqi", 500);

	map_skill("force", "hanbing-zhenqi");
	map_skill("dodge", "zhongyuefeng");
	map_skill("hand", "songyang-shou");
	map_skill("parry", "songshan-jian");
	map_skill("sword", "songshan-jian");
	map_skill("strike", "hanbing-shenzhang");
	prepare_skill("strike", "hanbing-shenzhang");
	set("inquiry", ([
		"job": (: do_ask() :),
		"����": (: do_ask() :),
		"cancel": (: do_cancel() :),
		"����": (: do_cancel() :),
		"���": (: ask_hb() :),
		"����": (: ask_times() :),

		"���ս�": (: ask_grj() :),
		"��������": (: do_chaozong() :),
		"��������": (: do_hanbing() :),
        "��ɽʯ��": (: do_hssb() :),
		"��ɽ��������": (: do_jueji() :),

	]));
	create_family("��ɽ��", 3, "������");
	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: perform_action, "sword.longfeng" :),
		(: perform_action, "sword.feiwu" :),
		(: perform_action, "strike.hanbing" :),
		(: exert_function, "juhan" :),
		(: exert_function, "hanbing" :),
	}));
	setup();
	if (clonep()) {
		ob = unew(BINGQI_D("sword/guanri-jian"));
		ob2 = unew(("d/meizhuang/obj/shuaiyitie"));
		ob3 = unew(("d/meizhuang/obj/lingqi"));
		ob2->move(this_object());
		ob3->move(this_object());
		if (!ob) ob = unew(BINGQI_D("gangjian"));
		ob->move(this_object());
		ob->wield();
		carry_object(ARMOR_D("changpao1"))->wear();
		carry_object(MEDICINE_D("tianwang"));
	}
	add_money("gold", 1);
}

void attempt_apprentice(object ob)
{
	if(ob->query("shen") > -2000000){
		command("say �����Ʋ�������Ⱥ������α���ӣ����ǰ����ǵ�ٵ�ѧ����һ�°�(��-2m)��\n");
		return;
	}
	if (!ob->query("quest/ss/dichuan"))
	{
		command("say ����δ��õմ�������ݣ������Ͽ�ȥ�ڹ���\n");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 350 ){
		command("say ����书��������죬�ٻ�ȥ�����ɡ�");
		return;
	}

    if(ob->query("job_time/��ɽ") < 300) {

	    command("say ���Դ�������������͵��ˣ����������ҵ���������Ϊʦ������300��������˵");
		return;
    }
	if (ob->query("family/master_id")=="zuo lengchan")
	{
		command("say ���Ѿ�����Ϊʦ�ˣ�������ɶ��\n");
		ob->set("title", HIC"���������״�����"NOR);
		return;

	}
    command("say �ã���������Щ������������Դ����书�������㻹�����");
	command("recruit " + ob->query("id"));
	ob->set("title", HIC"���������״�����"NOR);
}

void init()
{
	object ob;
	ob = this_player();

	::init();
	if( interactive(ob = this_player()) && !is_fighting() && !is_busy()
	   && ob->query_temp("quest/family") == "��ɽ��"
	   && ob->query_temp("quest/type") == "��") {
		remove_call_out("greeting");
		call_out("greeting", 2, ob);
	}
}

void greeting(object me)
{
	object target, ob;
	mapping quest;

	if( !me || environment(me) != environment() || !living(me)) return;

	if (!mapp(quest = me->query_temp("quest")) || quest["type"] != "��"
	|| !stringp(quest["id"])) return;

	command("nod "+me->query("id"));

	ob = this_object();

	if(objectp(target=present(quest["id"], environment(me)))
	  && target->query_temp("songshan_job") == me
	  && living(target)){
		me->add_busy(2);
		target->set_leader(0);
		command("haha");
		command("touch "+target->query("id"));
		command("say "+target->name()+"����������ɽ���ֶ���һ����������������");
		call_out("done", 3, target, me, quest, 1);
		return;
	}
}

void done(object target, object me, mapping quest, int i)
{
       int count,exp,pot;

       if(me && i >= 0){
		if(target){
			message_vision("\n$N��ͷ����"+me->name()+"�����޲���������ָ�������У��͵��ǳ����ļ�����ɣ�\n", target, me);
			tell_room( environment(me), target->name() + "��" + me->name()+ "����С����˵��Щ����\n", ({ me, target }) );
			// give rewards.
			TASK_D->give_reward(me, me->query_temp("quest"), -1, ABS(me->query("job_time/��ɽ")/100) , this_object(), "��ɽ" );
			me->add("job_time/��ɽ", 1);
			//GIFT_D->check_count(me,this_object(),"��ɽ");
			if (random(me->query("job_time/��ɽ"))>800&&random(me->query("kar"))>25 && !me->query("quest/ss/dichuan") && me->query("family/family_name")=="��ɽ��")
			{
				message_vision("$N��"+me->query("job_time/��ɽ")+"����ɽ���������л�����������Ͽɣ����㵱�����ĵ��ӿ�����\n",me);
				me->set("title",YEL"���������մ�����"NOR);
				me->set("quest/ss/dichuan",1);
			}
			if (me->query("quest/ss/dichuan"))
			{
				
				me->set("title",YEL"���������մ�����"NOR);
			}
			if ( me->query("family/family_name") == "��ɽ��"
			&& me->query_skill("hanbing-zhenqi",1))
				me->improve_skill("hanbing-zhenqi",me->query("int")*2);
							
			count = me->query("job_time/��ɽ");
			
			if (count<1) count=1;
			pot= me->query_temp("quest/pot_reward");
			exp= me->query_temp("quest/exp_reward");
			
			log_file("job/songshan",sprintf("%8s%-10s��%4d����ɽ����������%3d�㾭�飬%2d��Ǳ�ܣ����飺%d\n",
				me->name(),"("+me->query("id")+")",count,exp,pot,me->query("combat_exp")),me);
			
			me->delete_temp("quest");
			me->delete_temp("songshan_job");
			me->clear_condition("job_busy");
			me->set("job_name", "��ɽ����");
			tell_room(environment(target), target->query("name")+"��Ц��������֪�͵��Ӵ����µ��᷿��Ϣȥ�ˡ�\n", ({target}));
			if(target->return_home()){
				target->delete_temp("songshan_job");
				target->delete_temp("last_lost_to");
				target->clear_condition("songshan_busy");
				target->set("chat_chance", target->query("chat_c"));
				if(!target->query_temp("location"))
				target->delete("location");
				target->set_leader(0);
				target->reincarnate();
			}
			else destruct(target);
		}
	}
	else if(target){
		tell_room(environment(target), target->query("name")+"��Ц��������֪�͵��Ӵ����µ��᷿��Ϣȥ�ˡ�\n", ({target}));
		destruct(target);
	}
}

int do_hanbing()
{
	object me=this_player();
	if (me->query("family/family_name") !="��ɽ��")
	{
		command("say �㲻�����ɵ��ӣ�����������\n");
		return 1;
	}
	if (me->query("family/master_name") !="������")
	{
		command("say �㲻���ҵĵ��ӣ�����������\n");
		return 1;
	}
	if (!me->query("quest/ss/dichuan"))
	{
		command("say �㲻���ҳϣ�ֻ���״����Ӳ��ܻ����ɽ�������ڹ��ķ�\n�㻹�����Ҷ�ȥ�����·Ӣ�ۺ��ܰɡ�\n");
		return 1;
	}
	if (me->query_skill("hanbing-zhenqi",1) <450)
	{
		command("say ��ĺ���������δ��ɣ�450����ȥ��Ҳ��������\n");
		return 1;
	}
	if (me->is_busy())
	{
		command("say ������̫æ�ˣ�\n");
		return 1;

	}
	if (me->query("quest/ss/hbzq/pass") )
	{
		command("say ���Ѿ������������ڻ��ͨ��������ȥ�Ƕ��ˡ�\n");
		me->set("title",HBBLU+HIW"������������"NOR);
		return 1;
	}
	if (me->query("con")<40 )
	{
		command("say ���������ǲ���40�����Ǽ��������ɡ�\n");
		return 1;
	}
	if (time()-me->query("quest/ss/hbzq/time")<86400 )
	{
		command("say ������̫Ƶ���ˡ�\n");
		return 1;
	}
	command("pat "+me->query("id"));
	command("look "+me->query("id"));
	command("say ����ɽ���������񹦣�����������һΪ��������,��Ϊ��ɽ������\n");
	command("say ��Ȼ���ʵ��⺮������������������Ĺ������Ҿ͸������������е�һ�������ܡ�\n");
	command("say ���������������������ķ�����Ȼ��Ҫ��ѧ���Ҿ͸����㣬�����Ƿ��������Ե�ˡ�\n");
	command("say Ϊʦ��������ʦү��ˣ��������Ķ������˺��������İ��ء�\n");
	command("say �Ǵ�����֮�����Ǵ�����Ͽ�����һ������У�����Σ�գ�����ȥ������С�ģ�����Ӧ��֮�\n");
	command("say �������ˣ����������ķ�������������㣬��ȥ���԰ɣ��ܷ�ɹ�����������ˡ�\n");
	command("say ���ڵ�ַô���������������.....\n");
	command("consider ");
	command("whisper "+me->query("id"));
	command("look "+me->query("id"));
	me->set_temp("hbzq/askzuo",1);
	/*
	if (me->query("quest/ss/hbzq/thinking"))
	{
		message_vision(HIC"$N����һ�ӣ��Ծ�������$n�͵��ȵ�!\n"NOR,this_object(),me);
		me->move("d/songshan/gudi");

	}*/
	return 1; 
   
}