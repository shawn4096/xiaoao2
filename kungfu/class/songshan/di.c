// di.c ��ɽ�ɵ��Ĵ����� ����
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
int ask_job();
string ask_fangqi();
string ask_gongji();
string ask_rupai();

inherit F_MASTER;


void create()
{
        set_name("����", ({ "di xiu", "di", "xiu" }));
        set("long", "����һ����׳�ĺ��ӣ�����������ͽ�ܡ�\n");
		set("nickname", "��ɽһ��");

        set("gender", "����");
        set("age", 30);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 23);
        set("int", 23);
        set("con", 23);
        set("dex", 24);
        set("unique", 1);

        set("max_qi", 8500);
        set("max_jing", 3000);
        set("eff_jingli", 3000);
        set("jiali", 120);
        set("combat_exp", 1700000);
        set("shen", -70000);
		set_skill("songyang-jue", 120);

		set_skill("force", 200);
		set_skill("hanbing-zhenqi", 200);
		set_skill("dodge", 200);
		set_skill("zhongyuefeng", 200);
		set_skill("hand", 200);
		set_skill("songyang-shou", 200);
		set_skill("parry", 200);
		//set_skill("whip", 200);
		//set_skill("songyang-bian", 200);
		set_skill("literate", 160);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songyang-shou");
		//map_skill("whip", "songyang-bian");

		prepare_skill("hand", "songyang-shou");

		create_family("��ɽ��", 4, "����");

		set("class", "songshan");
		set("inquiry", ([
			"����" :(: ask_job :),
			"���ɹ���" :(: ask_gongji :),
			"������ɽ" :(: ask_rupai :),

			"����" :(: ask_fangqi :),
			"��ɽ��" : "������ɽ������������֮�ף�������ſ��������ƽʦ��ѧ�޷���Ҳ������ɳ�콭ʦ��ѧ����\n",
			"��������" : "������������������֮�������޴󣬿������֡��䵱���⡣����һ�����޽������Ǻ��ĵ��Ӳ�����\n",
			"������" : "���������ǵ������ˣ�������ɲ⡣\n",
		]) );
		setup();
		carry_object(ARMOR_D("changpao1"))->wear();
		//carry_object(BINGQI_D("changjian"))->wield();
}

string ask_rupai()
{
	int i;
	object me=this_player();
	if (me->query("family/family_name")=="��ɽ��")
	{
		command("say ���Ѿ���Ϊ�Ҵ���ɽ���ӣ���ɧ����������\n");
		return "���ģ�\n";
	}
	if (me->query("family"))
	{
		command("say ����������϶Ҳ̫���˰ɣ�\n");
		command("say �������ң�\n");
		return "���ɻ���أ���\n";
	}
	if (me->query("combat_exp")>5000)
	{
		command("say ����ɽҪ�Ϸ���ϸ������ô�ߵľ���ֵ����̽��ô����\n");
		return "�����ǣ���Ȼ���ɻ���أ���\n";
	}
	command("say ��Ȼ�������Ҵ���ɽ����Ҫ�ȿ�����ı��֣����˵������\n");
	command("say �������������칤�����Ұ�����ȥ������ϵף����Ƿ���İ��Ž����ļ�ϸ��\n");
//	me->set("family/family_name","��ɽ��");
	me->set("party/join",1);
	command("say �����������޷���̨���������ľ���ȥ�Ἰ��ʯͷ��\n");
	
	return "�ߣ�����ɽ�ؽ���Ϊ����֮�ף�\n";

}

//#include "app4.h";
string ask_gongji()
{
	int i;
	object me=this_player();
	if (me->query("family/family_name")!="��ɽ��" && !me->query("party/join"))
	{
		command("say ����������϶Ҳ̫���˰ɣ�\n");
		command("say �������ң�\n");
		return "���ɻ���أ���\n";
	}

	i=me->query("party/gongji");

	command("say "+me->query("name")+"�����������й���Ϊ"+chinese_number(i)+"�㹱��ֵ��\n");
	
	return "�����Ŭ��������ɽ�ؽ���Ϊ����֮�ף�\n";

}

int ask_job()
{
	object me = this_player();
    if (me->query("family")&&me->query("family/family_name")!="��ɽ��")
	{
		
       command("say �㲻������ɽ���ӣ���������Ъ��ȥ�ɣ�\n");
       command("sneer");
       return 1;
    }
	if (!me->query("party/join"))
	{
		command("say ���ʹ���ͬ����������ô��\n");
		return 1;
	}
    if (me->query("combat_exp") >= 100000
		&&me->query("job_time/��ɽ��ʯ")<100)
	{
		command("say ��Ĺ����Ѿ��ܸ��ˣ�������ȥ�Ҷ�û���ӡ�\n");
		return 1;
	}
	if (me->query_temp("ss_qs/asked"))
	{
		command("say ��ղŲ����ʹ�������ô����ȥ��\n");
		return 1;
	}
	if (me->query_condition("job_busy")){
		command("say ����ͷ�����������°ɣ���һ�������ɣ�\n");
		return 1;
	}
	
	me->set_temp("ss_qs/asked",1);
	me->apply_condition("job_busy",4);
	message_vision(HIC"����˵���������ٿ�Ӣ�ۻ���Ҫ��������̨��$N��ȥ��ʤ���æ��ʯ��\n"NOR,me);
	return 1;
}
string ask_fangqi()
{
        object me = this_player();

   //     if(me->query("family/family_name")!="��ɽ��")
             // return "�����ɽ�ɵ���,������Ϲ����ʲ��?";
        if(!me->query_temp("ss_qs/asked"))
              return "ʲô��������ʲô����";
        me->delete_temp("ss_qs");
        me->clear_condition("job_busy");
        me->start_busy(1);
        me->apply_condition("job_busy",3+random(3));
        return "�ðɣ������Ъ���ȣ�";
}

void attempt_apprentice(object ob)
{
	if (!ob->query("quest/ss/rumen/pass"))
	{
		command("say ���кεº��ܰ���Ϊʦ��\n");
		command("say ���ֺ�ԭ�ι�����Ϊͽ��\n");
		command("say ����ɽ��Ҫ�ҳϵ���ͽ���㻹���������ҿ��ɣ�\n");
		return;
	}
	if(ob->query("shen") > -10000 ){
		command("say ��ɽ�����Ժ������ƣ�<-100k������������ǻһ���Ͳ����ĺ������������");
		return;
	}
	if(ob->query("shen") > -10000 ){
		command("say ��ɽ�����Ժ������ƣ�<-100k������������ǻһ���Ͳ����ĺ������������");
		return;
	}
	if(ob->query("party/gongji") < 200 ){
		command("say ������ɹ�������200���������ң�");
		return;
	}
	command("say �ðɣ�ʦ����Ҫ�Ҷ�����һЩ������������ɽ���ء�");
	command("recruit " + ob->query("id"));
}
