// Npc songshan shi.c ʷ�Ǵ�
// Modify by baimo 2000,12,11 for a new job
// shi.c ��ɽ�ɵ��Ĵ����� ʷ�Ǵ�
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
int ask_job();
string ask_fangqi();
inherit F_MASTER;

void create()
{
        set_name("ʷ�Ǵ�", ({ "shi dengda", "shi", "dengda" }));
        set("long", "������������ͽ�ܣ�����λ������ߵĻ������ӡ�\n");
        set("gender", "����");
        set("age", 26);
        set("per", 20);
        set("attitude", "heroism");
        set("class", "songshan");
        set("shen_type", -1);
        set("str", 23);
        set("int", 20);
        set("con", 23);
        set("dex", 23);
        set("unique", 1);

        set("max_qi", 8400);
        set("max_jing", 3000);
        set("eff_jingli", 3000);
        set("jiali", 90);
        set("combat_exp", 2700000);
        set("shen", -70000);
		set_skill("songyang-jue", 120);

    	set_skill("force", 220);
    	set_skill("hanbing-zhenqi", 220);
    	set_skill("dodge", 220);
    	set_skill("zhongyuefeng", 220);
        set_skill("hand", 220);
        set_skill("songyang-shou", 220);
    	set_skill("parry", 220);
    	//set_skill("sword", 220);
    	//set_skill("songshan-jian", 220);
		set_skill("songyang-jue", 120);

    	set_skill("literate", 100);

    	map_skill("force", "hanbing-zhenqi");
    	map_skill("dodge", "zhongyuefeng");
        map_skill("hand", "songyang-shou");
    	map_skill("parry", "songyang-shou");
    	//map_skill("sword", "songshan-jian");
        prepare_skill("hand", "songyang-shou");

    	create_family("��ɽ��", 4, "����");
        set("inquiry", ([
	//	"����" :(: ask_job :),

	//	"����" :(: ask_fangqi :),
		"��ɽ��" : "������ɽ������������֮�ף�\n",
		"��������" : "������������������֮�������޴󣬿������֡��䵱���⡣\n",
		"������" : "���������ǵ������ˣ�������ɲ⡣\n",
	]) );
        setup();
        carry_object(ARMOR_D("changpao1"))->wear();
      //  carry_object(BINGQI_D("changjian"))->wield();
}
//��ʯ����
/*
int ask_job()
{
	object me = this_player();

    if (me->query("family/family_name")!="��ɽ��"&&!me->query_temp("ss/job/qishi") )
	{
		
                command("say �㲻������ɽ���ӣ���������Ъ��ȥ�ɣ�\n");
                command("sneer");
                return 1;
    }
    if (me->query("combat_exp") >= 100000){
		command("say ��Ĺ����Ѿ��ܸ��ˣ�������ȥ�Ҷ�û���ӡ�\n");
		return 1;
	}
	if (me->query_temp("ss_qs/asked")){
		command("say ��ղŲ����ʹ�������ô����ȥ��\n");
		return 1;
	}
	if (me->query_condition("job_busy")){
		command("say ����ͷ�����������°ɣ���һ�������ɣ�\n");
		return 1;
	}
	me->set_temp("ss_qs/asked",1);
	me->apply_condition("job_busy",4);
	message_vision(HIC"ʷ�Ǵ�˵���������ٿ�Ӣ�ۻ���Ҫ��������̨��$N��ȥ��ʤ���æ��ʯ��\n"NOR,me);
	return 1;
}

string ask_fangqi()
{
        object me = this_player();

        if(me->query("family/family_name")!="��ɽ��")
              return "�����ɽ�ɵ���,������Ϲ����ʲ��?";
        if(!me->query_temp("ss_qs/asked"))
              return "ʲô��������ʲô����";
        me->delete_temp("ss_qs");
        me->clear_condition("job_busy");
        me->start_busy(1);
        me->apply_condition("job_busy",3+random(3));
        return "�ðɣ������Ъ���ȣ�";
}*/

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
	if(ob->query("party/gongji") < 1000 ){
		command("say ������ɹ�������1000���������ң�");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 120 ){
		command("say ��ĺ�������̫���ˣ�����120�������ң�");
		return;
	}
	if(ob->query("shen") > -10000 ){
		command("say ��ɽ�����Ժ������ƣ�<-100k������������ǻһ���Ͳ����ĺ������������");
		return;
	}
	command("say �ðɣ�ʦ����Ҫ�Ҷ�����һЩ������������ɽ���ء�");
	command("recruit " + ob->query("id"));
}
