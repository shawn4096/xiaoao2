// le.c ��ɽ�ɵ��������� �ֺ�
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_here();
int ask_idea();
int ask_yy();
int ask_yy2();
void create()
{
        set_name("�ֺ�", ({ "le hou", "le", "hou" }));
        set("nickname", HIC"��������"NOR);
        set("long", "���˰������֣���Ƥ���ף���ʮ������ͣ���ɽ�ɵ�һ�����֡�\n");
        set("gender", "����");
        set("age", 46);
        set("per", 17);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 29);
        set("int", 23);
        set("con", 23);
        set("dex", 23);
        set("unique", 1);

        set("max_qi", 13000);
        set("max_jing", 5000);
        set("eff_jingli", 5000);
        set("jiali", 150);
        set("combat_exp", 6400000);
        set("shen", -130000);
	
		set_skill("songyang-jue", 160);

		set_skill("force", 400);
		set_skill("hanbing-zhenqi", 400);
		set_skill("dodge", 400);
		set_skill("zhongyuefeng", 400);
		set_skill("hand", 480);
		set_skill("songyang-shou", 480);
		set_skill("parry", 400);
		set_skill("sword", 400);
		set_skill("songshan-jian", 400);
		set_skill("literate", 200);
		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songyang-shou");
		map_skill("sword", "songshan-jian");
		prepare_skill("hand", "songyang-shou");
		create_family("��ɽ��", 3, "����");
		set("inquiry", ([
					"here": (: ask_here() :),
					"����": (: ask_idea() :),
					"��������": (: ask_yy() :),
				   // "�������־���": (: ask_yy2() :),
					"��������": (: ask_yy2() :),
			"��ɽ��" : "������ɽ������������֮�ף�\n",
			"��������" : "������������������֮�������޴󣬿������֡��䵱���⡣\n",
			"������" : "���������ǵ������ˣ�������ɲ⡣\n",
		]) );
			set("chat_chance_combat", 60);
			set("chat_msg_combat", ({
				(: perform_action, "hand.yinyang" :),
				(: perform_action, "hand.junji" :),
				(: exert_function, "hanbing" :),
				(: exert_function, "juhan" :),
			}));
			setup();
			carry_object(ARMOR_D("changpao1"))->wear();
}

int ask_here()
{
	object me = this_player();

	if (!me->query_temp("ss/zsb_3") || me->query_skill("dodge")<250){
		command("say �����Ǵ�����Ͽ���˴������ն�"+RANK_D->query_respect(me)+"����ò�Ҫ�ڴ˾�����\n����Ļ����Ṧ����250����ȥҲ����Ȼ��\n");
		return 1;
	}
	me->delete_temp("ss/zsb_3");
	me->set_temp("ss/zsb_4",1);
	command("say �����Ǵ�����Ͽ���˴������ն񣬹ȵ��溮�ޱȣ�������ʦ����һ�����ɱ޴��������ȥ��Ҳû���һ�����");
	command("whisper "+me->query("id")+" ������ҵ���һ������������ȥ����֪"+RANK_D->query_respect(me)+"��Ըǰ����");
	command("whisper "+me->query("id")+" ���������£��ȵ��溮�ޱȣ��㵱С��Ϊ�ϡ�\n");
	return 1;
}

int ask_idea()
{
	object me = this_player();

	if (!me->query_temp("ss/zsb_4")){
		command("? " + me->query("id"));
		return 1;
	}
	if (me->query_skill("dodge") < 450){
		command("say "+RANK_D->query_respect(me)+"������Ṧ��Ϊ̫����������¹ȡ�");
		return 1;
	}
	if (me->query_skill("force") < 450){
		command("say "+RANK_D->query_respect(me)+"��Ͽ���ں����쳣�������������ں����࿹�⡣");
		return 1;
	}
	if (me->query("con") < 40){
		command("say "+RANK_D->query_respect(me)+"��Ͽ���ں����쳣����������ǲ���40,����������ں����࿹�⡣");
		return 1;
	}
	me->delete_temp("ss/zsb_4");
	me->set_temp("ss/zsb_5",1);
	command("whisper "+me->query("id")+" ����ɽ����֦��������ֻ��Ҫ�Ҽ�֦��֦����������Ϳ����¹��ˡ�");
	return 1;
}

int ask_yy()
{
	object me = this_player();

	if (!me->query("family") || me->query("family/family_name") != "��ɽ��"){
		command("say "+RANK_D->query_respect(me)+"�������ҵľ��������������ɵġ�");
		return 1;
	}
	
	if (time()-me->query("quest/ss/sys/yinyang/time")<86400){
		command("say "+RANK_D->query_respect(me)+"��������̫�ڷ��ˡ�\n");
		return 1;
	}
	if (me->query_skill("songyang-shou",1) < 250){
			command("say "+RANK_D->query_respect(me)+"���������ֵĹ���̫����<250������������ѧ�ᣡ\n");
			return 1;
	}
	if (me->query_skill("hanbing-zhenqi",1) < 250){
			command("say "+RANK_D->query_respect(me)+"���㺮�������Ĺ���̫����<250������������ѧ�ᣡ\n");
			return 1;
	}
	command("say "+RANK_D->query_respect(me)+"���ҵĴ������־������ǿ��������书��һ�����ģ�\n");
	me->set_temp("ss/yy1",1);
	return 1;
}

int ask_yy2()
{
	object me = this_player();
	object ob = this_object();
	int i,j;
	j = 20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	i=random(j);
	
	if (!me->query_temp("ss/yy1")){
		command("say "+RANK_D->query_respect(me)+"��������Ե�޹ʣ�����ʲô��˼��\n");
		return 1;
	}

	if (!me->query("quest/ss/sys/yingyang/pass")){
		if (me->query_skill("songyang-shou",1) < 250){
			command("say "+RANK_D->query_respect(me)+"���������ֵĹ���̫����<250������������ѧ�ᣡ\n");
			return 1;
		}
		message_vision("$N��$n��������˵�˼��仰��\n",ob,me);
		if (i<4
			&&random(me->query("kar"))>23)
		{
			tell_object(me,HIY"�ֺ��漴�������ֵľ���Ϥ���������㣬������ѧ���˴������֣�\n"NOR);
			me->set("quest/ss/sys/yinyang/pass",1);
			me->set("quest/ss/sys/yingyang/time",time());

			log_file("quest/sysyinyang", sprintf("�ɹ���%8s(%8s) ����������������ʧ��%d�κ󣬽⿪�����֡����飺%d��\n", me->name(1),me->query("id"),me->query("quest/ss/sys/fail"),me->query("combat_exp")) );
			//return 1;
		}else {

			tell_object(me,HIG"�ֺ���Ȼ���ڸ���ܶ���ϣ����㻹��̫���������ˣ�����ʧ�ܣ�\n"NOR);

			log_file("quest/sysyinyang", sprintf("ʧ�ܣ�%8s(%8s) ����������������ʧ��%d�Ρ����飺%d��\n", me->name(1),me->query("id"),me->query("quest/ss/sys/fail"),me->query("combat_exp")) );
			me->add("quest/ss/sys/yinyang/fail",1);
			me->set("quest/ss/sys/yinyang/time",time());

		}
		me->delete_temp("ss/yy1");
		return 1;
	}
	else{
		command("say "+RANK_D->query_respect(me)+"�����Ѿ������˴������־����ľ�����ѽ��\n");
		return 1;
	}
}

void attempt_apprentice(object ob)
{
	if (!ob->query("quest/ss/rumen/pass"))
	{
		command("say ����ͨ������ʦ�ܵĿ�����˵��\n");
		command("say ���кεº��ܰ���Ϊʦ��\n");
		command("say ���ֺ�ԭ�ι�����Ϊͽ��\n");
		command("say ����ɽ��Ҫ�ҳϵ���ͽ���㻹���������ҿ��ɣ�\n");
		return;
	}
	if (ob->query("family/family_name")!="��ɽ��")
	{
		command("say һ�����ǹ������֮ͽ��Ϊ�ε��ˣ�\n");
		return;
	}
	if(ob->query("party/gongji") < 5000 ){
		command("say ������ɹ�������5000���������ң�");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 300 ){
		command("say ��ĺ�������̫���ˣ�����300�������ң�");
		return;
	}
	if(ob->query_skill("songyang-shou",1) < 300 ){
		command("say ���������̫���ˣ�����300�������ң�");
		return;
	}
	if(ob->query("family/generation") <4){
		command("say ���Ѿ�����ʦ��Ϊʦ�ˣ��ҿɲ������㣡");
		return;
	}
	if(ob->query("shen") > -1000000 ){
		command("say ��ɽ�����Ժ������ƣ�<-1m������������ǻһ���Ͳ����ĺ������������");
		return;
	}
	command("say �ðɣ�ʦ����Ҫ�Ҷ�����һЩ������������ɽ���ء�");
	command("recruit " + ob->query("id"));
}
