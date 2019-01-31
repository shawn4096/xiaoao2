// deng.c ��ɽ�ɵ��������� �˰˹�
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
int ask_zisong();
inherit F_MASTER;
void create()
{
        set_name("�˰˹�", ({ "deng bagong", "deng", "bagong" }));
        set("nickname", HIC"���"NOR);
        set("long", "����һ�����������ߣ�һ����������ĳ����뻯��\n");
        set("gender", "����");
        set("unique", 1);
        set("age", 45);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("unique", 1);

        set("max_qi", 3000);
        set("max_jing", 2000);
        set("eff_jingli", 2000);
        set("jiali", 50);
        set("combat_exp", 2000000);
        set("eff_neili", 4000);
        set("shen", -15000);
		set_skill("songyang-jue", 180);

		set_skill("literate", 100);
		set_skill("force", 355);
		set_skill("parry", 360);
		set_skill("whip", 400);
		//set_skill("sword", 350);
		set_skill("dodge", 350);
		set_skill("hand", 350);
		set_skill("zhongyuefeng", 350);
		set_skill("songyang-shou", 350);
		set_skill("songyang-bian", 400);
		set_skill("hanbing-zhenqi", 350);
		//set_skill("songshan-jian", 350);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("whip", "songyang-bian");
		map_skill("parry", "songyang-bian");
		//map_skill("sword", "songshan-jian");
		prepare_skill("hand", "songyang-shou");

		create_family("��ɽ��", 3, "����");

		set("class", "sword");
		set("chat_chance_combat", 10);
		set("chat_msg_combat", ({
			(: perform_action, "hand.junji" :),
			(: exert_function, "juhan" :),
		}));
		set("inquiry", ([
			"��ɽ��" : "������ɽ������������֮�ף�\n",
			"��������" : "������������������֮�������޴󣬿������֡��䵱���⡣\n",
			"������" : "���������ǵ������ˣ�������ɲ⡣\n",
			"���ɱ�": (: ask_zisong() :),

		]) );
			setup();
			carry_object(ARMOR_D("changpao1"))->wear();
			carry_object(BINGQI_D("whip"))->wield();
}


int ask_zisong()
{
	object me=this_player();
	//message_vision(HIC""NOR,me);
	if (!me->query_temp("ss/hb_1"))
	{
		command("say ���Ƿ��в�����ͼ������������ɽ���ؼ�ô��\n");
		command("heng ");
		return 1;
	}
	command("sigh ");
	command("say ����ʦ�����������������޷��������������гɡ�\n");
	command("say ����ƾ�����㽭���������Ҿ�ȥѰ��ʦ���������˼���\n");
	command("say ��ʱ�ǳ�ս�����ڴ�����Ͽ����������ס�����Ǳ������������ɱޡ�\n");
	command("say ���һ��С�ģ�Ϊʦ�ֺ������������𣬽�����ر�ʧ�ֵ��䵽�µס�\n");
	command("say ˭Ҫ������Ѱ�һ������ұص���л��������������\n");
	command("say �Ķ��Ƚ����գ�Ҫ��ȥ���ȥ������ʦ�֣�������һ���Ƚ���Ϥ��\n");
	me->set_temp("ss/zsb_3",1);
	return 1;
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
	if(ob->query("party/gongji") < 2000 ){
		command("say ������ɹ�������1000���������ң�");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 200 ){
		command("say ��ĺ�������̫���ˣ�����120�������ң�");
		return;
	}
	if(ob->query("shen") > -100000 ){
		command("say ��ɽ�����Ժ������ƣ�<-100k������������ǻһ���Ͳ����ĺ������������");
		return;
	}
	command("say �ðɣ�ʦ����Ҫ�Ҷ�����һЩ������������ɽ���ء�");
	command("recruit " + ob->query("id"));
}
