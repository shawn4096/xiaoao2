// Npc: /kungfu/class/shaolin/xuan-bei.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

string ask_me();
string ask_cibei();
void create()
{
	set_name("������ʦ", ({
		"xuanbei dashi",
		"xuanbei",
		"dashi",
	}));
	set("long",
		"����һλ�����ü����ɮ����һϮ��˿�ػ����ġ���������ߣ�\n"
		"��������񣬶��Ÿ��ʣ�˫ĿտȻ����\n"
	);

    set("no_get",1);
	set("nickname", "��ĦԺ����");
	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 70);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 20000);
	set("max_jing", 8000);
	set("neili", 30000);
	set("max_neili", 2000);
	set("jiali", 200);
	set("combat_exp", 9500000);
	set("score", 500000);

	set_skill("force", 450);
	set_skill("yijin-jing", 450);
	set_skill("dodge", 450);
	set_skill("shaolin-shenfa", 450);
	set_skill("hand", 450);
	set_skill("claw", 450);
	set_skill("blade", 450);
	set_skill("sword", 450);
	set_skill("parry", 450);
	set_skill("qianye-shou", 450);
	set_skill("longzhua-gong", 450);
	set_skill("cibei-dao", 450);
	set_skill("damo-jian", 450);
	set_skill("finger", 450);
	set_skill("yizhi-chan", 450);
	set_skill("buddhism", 150);
	set_skill("literate", 150);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("hand", "qianye-shou");
	map_skill("claw", "longzhua-gong");
	map_skill("blade", "cibei-dao");
	map_skill("sword", "damo-jian");
	map_skill("parry", "yizhi-chan");
	map_skill("finger", "yizhi-chan");
	

	prepare_skill("finger", "yizhi-chan");
	prepare_skill("claw", "longzhua-gong");
    set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
		(: perform_action, "finger.wofo" :),
	    (: perform_action, "finger.qiankun" :),
		(: perform_action, "claw.lianhuan" :),
		(: exert_function, "jingang" :),
	}));
	create_family("������", 36, "����");

	set("inquiry", ([
		"������": (:ask_me:),
		"�ȱ�������": (:ask_cibei:)
	]));

	setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void du1(object ob)
{
	object du;

	say("�����ǰһ����һ����С����Ӱ���˽�����\n");
	du=new("/kungfu/class/shaolin/du-nan2");
	du->move(environment());
	EMOTE_D->do_emote(du, "buddhi", query("id"));
	command("buddhi " + du->query("id"));
}
 
void charse_du(object ob)
{
	new("/d/shaolin/npc/xiao-bei")->move(environment());
	say("Сɳ�����˽�����\nСɳ�ֶ���������ʦ˵�������ѳ���������Ѷ���Ͼ͵���\n");
	call_out("du1", 20, ob);
}

string ask_me()
{
	mapping skill;
	string *skl;
	object ob = this_player(), tmp;
	int i;

	if (present("du nan", environment())) {
		command("? " + ob->query("id"));
		return "���ѳ��ϲ�����������";
	}
	if (ob->query_temp("pending/waitdu"))
		return "��ʦ�����ĵȺ�Ƭ�̡�";

	if (ob->query("family/family_name") != "������") {
		command("sneer " + ob->query("id"));
		return "��֪����";
	}

    if (ob->query("pass_xin"))
        return "�㲻���Ѿ�ͨ���������ϵĿ�������";
	if (ob->query("passdu"))
		return "�㲻���Ѿ�ͨ���˶��Ѵ�ʦ�Ŀ�������\n";

	if (ob->query("family/generation") != 37) {
		return "�������ڽ�շ�ħȦ������ޡ�";
	}
	skill = ob->query_skills();
    if (!skill) return RANK_D->query_respect(ob) + "���书��ǿ���⣬������ǿ�Լ���";
	skl = keys(skill);
	i = sizeof(skl);
    if (i < 8) return RANK_D->query_respect(ob) + "���书��ǿ���⣬������ǿ�Լ���";
	while (i--) {
		if (skill[skl[i]] < 120 && skl[i] != "medicine")
			return RANK_D->query_respect(ob) + "�Ƿ���" + CHINESE_D->chinese(skl[i]) + "�϶���Щ����";
	}
	if ((tmp = present("xiao shami", environment()))) {
		ob->set_temp("pending/waitdu", 1);
		command("nod");
		say("������ʦ�������Сɳ�ֶ��Ｘ�䡣\nСɳ�ֿ첽���˳�ȥ��\n");
		destruct(tmp);
		call_out("charse_du", 20, ob);
		return "�ðɣ�" + RANK_D->query_respect(ob) + "�����Ժ�һ�ᡣ";
	}
	return "�����ӷ�Сɳ�ֲ��ڣ������ʱ�������ɡ�";
}

void attempt_apprentice(object ob)
{
	object me; 
	mapping ob_fam, my_fam;
	string name;

	me = this_object();
	my_fam  = me->query("family");

	name = ob->query("name");

	if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "������")
	{
		command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
		return;
	}

	if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "������") 
	{
		command("say " + RANK_D->query_respect(ob) + "���׼ҵ��ӣ�����������ѧ�ա�");
		return;
	}
/*
	if ( ob_fam["generation"] <= my_fam["generation"] )
	{
		command("say " + RANK_D->query_respect(ob) + "��ƶɮ����ҵ� !");
		return;
	}
*/
	if ( ob_fam["generation"] <= (my_fam["generation"] + 1) )
	{
		command("say " + ob_fam["master_name"] + "��ͽ����ô�ܵ���������ˣ������� !");
		command("recruit " + ob->query("id"));
	}
	else
	{
		command("say " + RANK_D->query_respect(ob) + "���㱲�ݲ��ϣ�����Խ����ʦ��");
		return;
	}

	return;
}

string ask_cibei()
{
	object me=this_player();
	if (me->query("family/family_name")!="������")
	{
		command("say �ҷ�ȱ����㲻���������е��ӣ�����������\n");
		return "�ȱ������̺��ҷ�ȱ�����,Ψ����ʶ֮��\n";
	}
	if (time()-me->query("quest/sl/cbd/time")<86400)
	{
		command("say �����书��Ҫ���Ƕ���������̫Ƶ���ˣ�\n");
		return "���򰡣�\n";
	}
	if (me->query("quest/sl/cbd/pass"))
	{
		command("say ���Ѿ���ϰ�ɹ��˴ȱ��������⣡\n");
		return "�������Ҵ����ֵĶ���֮�Ű���\n";
	}
	command("say ��ȱ������������־���֮һ������ı������ڴȱ����֡�\n");
	command("say �����ߣ�����Ҳ����Ȼ���гֵ����ʹ���ɱ��֮�ġ�\n");
	command("say ��Ȼ����ɱ��֮�ģ����κν����ȱ�������ҷ�����㣡�\n");
	command("say ���ԣ���ȱ�����Ȼ�������־�������һֱû���������ɡ�\n");
	command("say ���ǣ�����֮�ڣ���һ�����Ĺۺ��е����ȴ��������������ȱ������⡣\n");
	command("say �������������£���˵������������ͯ���е����֡�\n");
	command("say ������ѧ���Ը��������ȱ������⡣\n");
	me->set_temp("cbd/askxuanbei",1);
	return;
}