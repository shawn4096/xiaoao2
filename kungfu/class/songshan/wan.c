// wan.c ��ɽ�ɵ��Ĵ����� ���ƽ
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("���ƽ", ({ "wan daping", "wan", "daping" }));
        set("nickname", "ǧ����");
        set("long", "���ǵ˰˹���ͽ�ܣ�����λ������ߵĻ������ӡ�\n");
        set("gender", "����");
        set("age", 29);
        set("per", 20);
        set("attitude", "heroism");
        set("class", "songshan");
        set("shen_type", -1);
        set("str", 26);
        set("int", 20);
        set("con", 23);
        set("dex", 23);
        set("unique", 1);

        set("max_qi", 1500);
        set("max_jing", 1000);
        set("eff_jingli", 1000);
        set("jiali", 20);
        set("combat_exp", 650000);
        set("shen", -6500);
		
		set_skill("songyang-jue", 90);
		set_skill("whip", 200);
		set_skill("songyang-bian", 200);

		set_skill("force", 200);
		set_skill("hanbing-zhenqi", 200);
		set_skill("dodge", 200);
		set_skill("zhongyuefeng", 200);
		set_skill("hand", 200);
		set_skill("songyang-shou", 200);
		set_skill("parry", 200);
		//set_skill("sword", 100);
		//set_skill("songshan-jian", 100);
		set_skill("literate", 50);
		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songshan-jian");
		map_skill("whip", "songyang-bian");
		prepare_skill("hand", "songyang-shou");
		set("chat_chance_combat", 10);
		set("chat_msg_combat", ({
			(: perform_action, "whip.luan" :),
			(: perform_action, "hand.junji" :),
			(: exert_function, "juhan" :),
		}));
		create_family("��ɽ��", 4, "����");
		setup();
		set("inquiry", ([
			"��а����" : "���º�����ɳ�콭ʦ���ڸ�����¡�\n",
			//"��а����" : "������������������֮�������޴󣬿������֡��䵱���⡣\n",
		]) );
		carry_object(ARMOR_D("changpao1"))->wear();
		carry_object(BINGQI_D("changbian"))->wield();
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
	if(ob->query("party/gongji") < 100 ){
		command("say ������ɹ�������1000���������ң�");
		return;
	}
	/*if(ob->query_skill("hanbing-zhenqi",1) < 100 ){
		command("say ��ĺ�������̫���ˣ�����120�������ң�");
		return;
	}*/
	if(ob->query("shen") > -10000 ){
		command("say ��ɽ�����Ժ������ƣ�<-100k������������ǻһ���Ͳ����ĺ������������");
		return;
	}
	command("say �ðɣ�ʦ����Ҫ�Ҷ�����һЩ������������ɽ���ء�");
	command("recruit " + ob->query("id"));
}
