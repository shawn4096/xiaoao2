// azi.c ����
// Update by caiji@SJ 8/27/2000

inherit NPC;
inherit F_MASTER;

string ask_san();
string ask_for(object);
string ask_you();
string ask_tietou();

void create()
{
        set_name("����", ({ "azi", "a zi", "a" ,"zi"}));
        set("nickname", "������Сʦ��");
        set("long", "������Сʦ�á�һ�������µ���ò��Ů�����Ӱ׾���, ����������͸��һ��а����\n");
        set("gender", "Ů��");
        set("age", 15);
        set("attitude", "peaceful");
        set("env/wimpy", 110);
//	set("apprentice", 1);

        set("str", 18);
        set("int", 28);
        set("per", 30);
        set("con", 20);
        set("dex", 24);

        set("max_qi", 8400);
        set("max_jing", 15200);
        set("jiali", 100);
        set("combat_exp", 2000000);
        set("shen", -1000);

        set_skill("force", 220);
        set_skill("huagong-dafa", 220);
        set_skill("dodge", 220);
        set_skill("zhaixingshu", 220);
        set_skill("strike", 220);
        set_skill("chousui-zhang", 220);
        set_skill("parry", 220);
        set_skill("poison", 60);
        set_skill("literate", 80);
        set_skill("claw", 220);
        set_skill("sanyin-zhua", 220);

        map_skill("claw", "sanyin-zhua");
        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixingshu");
        map_skill("strike", "chousui-zhang");
        map_skill("parry", "chousui-zhang");
        prepare_skill("claw", "sanyin-zhua");
        prepare_skill("strike", "chousui-zhang");

        create_family("������", 2, "����");

        set("inquiry", ([
                "������" : "������룬�Ͱ���Ϊʦ��\n",
                "�" : "�Ӷ������ͻ��ߵ���ɽ��ɽ���ȥ��\n",
               // "���޺�" : "ȥ���޺���ʲô������Ϊʦ�͹���ѧ���ˡ�\n",
               // "������" : "����������е���û��ûС�ġ��Ժ�����ɣ�\n",
                //"����" : "��öവ�����ɣ���������г�ͷ֮�ա�\n",
                "����ľ��" : "��ľ�����ŵ���ɽɽ�����ˡ��б������Լ�ȥ�á�\n",
                //"���" : "���ҽ�����嶼��֪���������Ǹ�����ϡ�\n",
                //"����" : "���ʵĿ��������ɣ�\n",
                //"����" : "Ů�����׶��ˣ�����������ϲ�����еĵø��ӰѾ���\n",
                "��ҩ" : (: ask_san :), //add by caiji
				"����ɢ" : (: ask_san :), //add by caiji
				"����" : (: ask_for, "pifeng" :),//add by caiji
				"��̹֮" : (: ask_you:),
				"����" : (: ask_tietou:),
        ]));
        setup();
        set("pifeng_count",6);
        set("san_count",6);
        carry_object("/d/xingxiu/obj/yao");
	//add by caiji        carry_object("/d/xingxiu/obj/qxs");
	carry_object(ARMOR_D("baihu-qiu"))->wear();
}

void attempt_apprentice(object ob)
{
     if(ob->query("shen") > -10000){
		command("say �㿴��ȥ���Ǹ����������ҲŲ��������ء�����10k����������ҡ�");
		return;
     }
	command("hehe " + ob->query("id"));
	ob->set("class","xingxiu");
	command("recruit " + ob->query("id"));
}

string ask_san()
{
        int exp;
        object drug, me, ob;
        mapping fam;

        me = this_object();
        ob = this_player();
        fam = (mapping)ob->query("family");
        exp=ob->query("combat_exp",1);

        if(!fam || exp < 200000 || fam["family_name"] != "������")
                return "��ƾ��Ҳ��Ҫ���޵Ķ��Ž�ҩ��\n";
        if( (int)ob->query_skill("huagong-dafa", 1) < 150 )//....caiji
                return "��Ļ����󷨹���̫ǳ������150������ô���������أ�\n";
        if (!ob->query("quest/xx/dichuan"))
				return "����Ҵ����޵մ����ӣ�����ô���������أ�\n";
		if(me->query("san_count") >= 1 && (!ob->query_temp("san_given"))){
                        me->add("san_count", -1);
                        drug = unew("/d/xingxiu/obj/qxs");
                        if (!clonep(drug)) return "����������������ʦ���������ˡ�\n";
                        drug->move(ob);
                        ob->set_temp("san_given", 1);
                        message_vision("$N��$n���˵�ͷ������$nһС������ɢ��\n", me, ob);
                        return "�Լ��þ����ˣ�ǧ��Ҫ�������ɵ��ӣ�\n";
        }
        if(ob->query_temp("san_given"))
                     return "�Ҳ��Ǹ���������\n";
        return "����������������ʦ���������ˡ�\n";
}

string ask_for(string name)
{
        mapping fam;
        object ob;

        if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
                return RANK_D->query_rude(this_player()) +
                "�ֲ������޵��ӣ�ƾʲô����Ҫ��Ҫ�ǵģ�";

        if (  present(name, this_player()) )
                return RANK_D->query_rude(this_player()) +
                "���������ϲ�����������������������Ҫ�ˣ� ����̰�����У�";
       if (!this_player()->query("quest/xx/dichuan"))
				return "����Ҵ����޵մ����ӣ�����ô���������أ�\n";

        if (query("pifeng_count") < 1)
                return "��Ǹ�������ò���ʱ�������Ѿ������ˡ�";

        ob = new("/d/xingxiu/obj/" + name);
        ob->move(this_player());

        add("pifeng_count", -1);

	message_vision("$N��$nһ��" + ob->query("name") + "��\n",this_object() ,this_player());

        return "����Ǽ��ö�������Ū���ˡ�";
}
string ask_you()
{
	object me=this_player();

	
	command("say ��̹֮���Ҳ�֪��˭����̹֮����ֻ֪����������и�����!\n");
	command("xixi ");
	command("say ����������Ǻ��棬������˼��\n");
	this_player()->set_temp("bingcan/askyou",1);
	return "��̹֮�������ֺ��죡\n";
}
string ask_tietou()
{
	if (!this_player()->query_temp("bingcan/askyou"))
	{
		command("say �������ҵ����ˣ��������������ɶ��\n");
		return "������ɵ��\n";
	}
	command("say �ϸ�������������������ͷ��ɽ���ϣ�����ľ����������ʹ���ҹ��������\n");
	command("xixi ");
	command("say ����������Ǻ��棬������˼��\n");
	this_player()->set_temp("bingcan/asktietou",1);
	return "�������ҵ����ˣ����������Ĳ�����\n";
}