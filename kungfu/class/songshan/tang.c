// tang.c ��ɽ�ɵ��������� ��Ӣ��
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
string ask_job();
string ask_fangqi();

void create()
{
        set_name("��Ӣ��", ({ "tang yinge", "tang", "yinge" }));
        set("nickname", HIC"����̫��"NOR);
		set("title","��������");
        set("long", "����һ�����������ߣ�������������ʦ�ܡ�\n��˵�����书���ߣ������主���Ļ�������ɽ��ʦү��\n");
        set("gender", "����");
        set("age", 45);
        set("per", 20);
        set("attitude", "heroism");
		set("class", "songshan");
        set("shen_type", -1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("unique", 1);

        set("max_qi", 13000);
        set("max_jing", 4000);
        set("eff_jingli", 4000);
        set("jiali", 100);
        set("combat_exp", 4500000);
        set("shen", -15000);
		set_skill("songyang-jue", 120);

		set_skill("force", 350);
		set_skill("hanbing-zhenqi", 350);
		set_skill("dodge", 360);
		set_skill("zhongyuefeng", 360);
		set_skill("hand", 350);
		set_skill("songyang-shou", 350);
		set_skill("parry", 350);
		set_skill("sword", 350);
		set_skill("songshan-jian",350);
		set_skill("literate", 100);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songshan-jian");
		map_skill("sword", "songshan-jian");

		prepare_skill("hand", "songyang-shou");
		create_family("��ɽ��", 3, "����");
		set("chat_chance_combat", 10);
		set("chat_msg_combat", ({
					(: perform_action, "sword.feiwu" :),
					(: perform_action, "hand.junji" :),
					//(: perform_action, "hand." :),
					(: exert_function, "hanbing" :),
			}));
		set("inquiry", ([
			"��̽" :(: ask_job :),
			//"���ɹ���" :(: ask_gongji :),
			//"������ɽ" :(: ask_rupai :),

			"����" :(: ask_fangqi :),
			"��ɽ��" : "������ɽ������������֮�ף�������ſ��������ƽʦ��ѧ�޷���Ҳ������ɳ�콭ʦ��ѧ����\n",
			"��������" : "������������������֮�������޴󣬿������֡��䵱���⡣����һ�����޽������Ǻ��ĵ��Ӳ�����\n",
			"������" : "���������ǵ������ˣ�������ɲ⡣\n",
		]) );
			setup();
			carry_object(ARMOR_D("changpao1"))->wear();
			carry_object(BINGQI_D("changjian"))->wield();
			add_money("gold", 1);
}
//�䵱�����֡���ɽ����ɽ����ɽ�������¡�ؤ������ɡ��һ����������ɡ�ȫ���

string ask_job()
{
	object me,ob;
	string type;
	me=this_player();
	if (me->query("family/family_name")!="��ɽ��")
		return "�㲻����ɽ�ɵ��ӣ�����������\n";
	if (!me->query("quest/ss/dichuan"))
		return "�����ɽ���ĵ��ӣ��������⹤����\n";
	if (me->query("combat_exp")<200)
		return "��ľ��鲻��2m,�޷�����ô���յ�����";
	command("pat "+me->query("id"));
	
	tell_object(me,"����������������磬���������ƻ�������������֮�ƣ�"+me->query("name")+"������һ��,����ȥ��̽һ����\n");
	command("say �������Ƚ�Σ�գ������Ǽ���֮���޷�������������\n");
	//type=random(2)?͵��:̽��;
	//��һ������ȥ���ŷ���͵����Ϣ
	//�ڶ�����Ȼ�������ʾ�����˵ı��֣�Ȼ��ɱ�������������ơ�
	ob=new("d/songshan/obj/songyang_ling");
	ob->move(this_object());
	ob->set("owner",me->query("id"));
	
	me->set_temp("ss/jxjob/start",1);
	me->apply_condition("ssjianxi_job",10);
	
	switch (random(1))
	{
		case 0:
			ob->set_temp("ss/jxjob/party","������");
			me->set_temp("ss/jxjob/party","������");
			ob->set_temp("ss/jxjob/place","/d/shaolin/xctang");
			me->set_temp("ss/jxjob/place","/d/shaolin/xctang");
			tell_object(me,me->query("name")+"�������ɷ�����ʦ���Ƶ�����䵱����������߶�����ͼ���������ɡ�\n");
			tell_object(me,me->query("name")+"��������������ȥ������ʦס����̽һ�������ܷ���ʲô�쳣��\n");
			message_vision(HIY"$NҪ��ס������쳣�㶨Ҫ��̽��������������ң��������ͣ�\n"NOR,me);
			me->set_temp("apply/title","�����ɵ���ʮ�������");
			break;
		case 1:
			ob->set_temp("ss/jxjob/party","��ɽ��");
			me->set_temp("ss/jxjob/party","��ɽ��");
			ob->set_temp("ss/jxjob/place","/d/huashan/zhengqi");
			me->set_temp("ss/jxjob/place","/d/huashan/zhengqi");
			tell_object(me,me->query("name")+"����ɽ������Ⱥ��α�������Ƶ��ȥ�������͸���һ������ͼ���������ɡ�\n");
			tell_object(me,me->query("name")+"��������������ȥ����Ⱥס����̽һ�������ܷ���ʲô�쳣��\n");
			message_vision(HIY"$N������쳣�㶨Ҫ��̽��������������ң��������ͣ�\n"NOR,me);
			break;
	}
	tell_object(me,"��������һ���������ƣ�����ȥҲ�ñ�����ݣ���������ϸ��¼���ϣ������������ң�\n");
	
	ob->move(me);
	return "һ·��Σ�����أ�һ��ҪС��������\n";
}
