// NPC: /d/huashan/npc/lingshan.c
// Date: Look 99/03/25
// Lklv Modify at 2001.10.18
// ��ҪNPC.�޷�ɱ�� by spiderii@ty
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_me();
string ask_sword();
void create()
{
	set_name("����ɺ", ({ "yue lingshan", "yue", "lingshan" }));
	set("long",
"��ɽ��������Ⱥ�ͷ���������İ�Ů������������������а����С���ߣ�\n"
"��ɽ�������˽�������Сʦ�á���\n");
	set("nickname", "Сʦ��");
	set("rank_info/respect", "Сʦ��");
	set("gender", "Ů��");
	set("age", 19);
	set("attitude", "friendly");
	set_max_encumbrance(1000000);
	set("shen_type", 1);
	set("str", 22);
	set("int", 25);
	set("con", 23);
	set("dex", 28);
	set("per", 30);
	set("unique", 1);
	set("no_get", 1);
	set("job_npc", 1);

	set("max_qi",6700);
	set("max_jing",4600);
	set("neili",6000);
	set("max_neili",6000);
	set("eff_jingli", 4600);
	set("jiali", 150);
	set("combat_exp", 3020000);
	set("score", 5000);

	set_skill("sword",  280);
	set_skill("dodge",  280);
	set_skill("force",  280);
	set_skill("parry",  280);
	set_skill("literate",280);
	set_skill("chongling-jian", 280);
	set_skill("huashan-jianfa", 280);
	set_skill("huashan-shenfa", 280);
	set_skill("huashan-qigong",280);
	set_skill("poyu-quan",280);
	set_skill("cuff",280);

	map_skill("force", "huashan-qigong");
	map_skill("cuff", "poyu-quan");
	map_skill("parry", "huashan-jianfa");
	map_skill("sword", "huashan-jianfa");
	map_skill("dodge", "huashen-shenfa");

	prepare_skill("cuff", "poyu-quan");
	create_family("��ɽ��", 14, "����");
	
	set("inquiry", ([
		"��������" : (: ask_me :),
		"��ˮ��" : (: ask_sword :),
	]));

	setup();
	carry_object(BINGQI_D("sword/sword"))->wield();
	carry_object(ARMOR_D("armor/cloth"))->wear();
}

void heart_beat()
{
	::heart_beat();

	clear_conditions_by_type("poison");
	if( !is_fighting() && living(this_object()))
		reincarnate();
}
string ask_sword()
{
	object sword,me;
	
	me =this_player();
	sword =present("bishui jian", me);
		
	if (!sword )
		return "�ú�����ȥ�ɣ�û�²�Ҫɧ��Сʦ�ã�\n";
	if (me->query_temp("quest/huashan/zixia/zixia2"))
	{
       me->set_temp("quest/huashan/bishuijian",1);
	   return "����ɺ��ɫ������˵��,'�Դ��ϴα���ʦ���ӵ�ɽ��������Ҳû�м�������'��";
	};
	return "����ɺ���������˼���ø�ɶ��ɶȥ�ɡ�\n";

}
 
int accept_object(object who, object obj)
{
	int times;
	object ling,me,sword;
	ling =present("ling pai", who);
	me = this_player();
    
	sword = present("bishui jian", who);

	if (me->query_temp("quest/huashan/bishuijian")&& obj->query("id")=="bishui jian")
	{
		me->set_temp("quest/huashan/zixia3",1);
		write(HIY"����ɺ���˵α����������ƺ�����ĺøд�����\n"NOR);
		write(HIC"$N�ѱ�ˮ���͸���Сʦ�ã���������֮�ʣ���ʹ���������������Ȼص���Ϣ������һ����\n"NOR);
		obj->move(this_object());
		destruct(obj);
		me->delete_temp("quest/huashan/bishuijian");		
		return 1;
	}
//��Ǹ��˱�ˮ��

	if (! obj->query_temp("mmr") 
	 && !obj->is_corpse()
	 && obj->query("id") != "shouji") {
		command("say �ⶫ����Ҫ��û�á�");
		return 0;
	}
	if (!ling )
		return notify_fail("��������أ�\n");
	if (!who->query_temp("hs/jobji"))
		return notify_fail("�㻹û����������ô������̳�ˣ�\n");
	if ((int)ling->query_temp("mmr", 1) != who->query("id"))
		return notify_fail("���������������ưɣ�\n");
	if ((int)ling->query_temp("done", 1) > 1 )
		return notify_fail("�����ô��������ˣ���Ͻ���ȥ�����ɡ�\n");
	if (!who->query_temp("hs/have"))
		return notify_fail("�㻹û��ȥ�Ҷ�������ô������̳�ˣ�\n");
	if (obj->query_temp("mmr")) {
		if ( obj->query_temp("mmr", 1) != who->query("id") )
                	return notify_fail("���˺���δ�ڻ�ɽΪ����������\n");
	}
	if (obj->query_temp("faint_by") != who && obj->query("kill_by") != who )
		return notify_fail("���˺�������ɱ�İɣ�\n");

	if ( obj->query("victim_user") )
		return notify_fail("��������ɻ���أ�û��ô���ף�\n");

	times = ling->query_temp("done", 1);
	write("����ɺ�����������д����һ�� "+CHINESE_D->chinese_number(times+1)+" �֡�\n", who);

	if (!obj->is_corpse() && obj->query("id") != "shouji" ){
		command("say " + "�ðɣ���Ѷ������ڼ�̨�������ͷ����ģ�����֮ʿ������֮��ᰲϢ�ˡ�\n");
		who->set_temp("jitan", 1);
	}
	else {
		command("say " + "�һ�ɽ�ɲ�ϲ��ɱ��" + RANK_D->query_respect(who) + "�´β�����˺��¶����ˡ�\n");
		ling->add_temp("done", 1);
	}
	if( (int)ling->query_temp("done", 1) == 1 )
		command("say " + "��һ����ʽ��������Ϳ���ȥʦ�����︴���ˡ�\n");
	//me->set_max_encumbrance(10000000);
	who->start_busy(random(3));
	who->delete_temp("hs/have");
	call_out("destroying", 1, obj);
	return 1;
}

void destroying(object obj,object me)
{
	if (!obj) return;
	destruct(obj);
	return;
}

string ask_me()
{
	object ling,me;
	
	me =this_player();
	ling =present("ling pai", me);
		
	if (!ling )
		return "��������أ�\n";
	if (!me->query_temp("hs/jobji"))
		return "�㻹û����������ô������̳�ˣ�\n";
	if ((int)ling->query_temp("mmr", 1) != me->query("id"))
		return "���������������ưɣ�\n";
	if ((int)ling->query_temp("done", 1) > 1 )
		return "�����ô��������ˣ���Ͻ���ȥ�����ɡ�\n";
	if (!ling->query_temp("done", 1))
		return "��ʲôҲû�ɰ���\n";
	if (me->query_temp("hs/have"))
		return "�㻹û��ȥ�Ҷ�������ô������̳�ˣ�\n";
	if (me->query_temp("hs/robot"))
		return "�㻹����ȥ������\n";
	//ɱ��һ��
	me->set_temp("hs/robot",1);
	return "��Ȼ��ˣ�����ͻ�ȥ�����ɣ�";
}
void die()
{
	object ob;
	if (!query_temp("living"))
	{
		ob = new("/d/huashan/npc/lingshan");
		ob->move("/d/huashan/jitan");
	}
	::die();
}

void attempt_apprentice(object ob)
{
        mapping fam;
		if ( ob->query("fengset")) {
		command("say �㲻���Ѿ����˽��ڵ�ǰ��Ϊʦ��ô��");
		return;
		}
		        if(ob->query("quest/huashan")=="����"){
                command("heng");
                command("say �ߺߣ����ڵ��������뿪��ɽ�������ǻ�ɽ�ɵ��ӣ�����������ѵ���������������֮λ��");
                return;
        }
        if( (string)ob->query("gender") != "Ů��" ) {
                command ("say �Բ�����ֻ��Ů���ӡ�");
                return;
        }
		
        if ((int)ob->query("shen") < 10000) {
		command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϣ�û������10k�������ҡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) + "�Ƿ����ò�����");
		return;
        }
		command("xixi");
        command("say �ף������СŮ����Ҿ��������ˡ�");
        command("recruit " + ob->query("id"));
	    ob->set("title","��ɽ�������״�����");
        ob->set("quest/huashan","����");
        return;
}
