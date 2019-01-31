#include <ansi.h>
inherit NPC;

string ask_me();
string ask_yusuo2();
string ask_ankang();

void create()
{
        set_name("�������", ({ "zhangli daozhang", "zhangli", "daozhang" }));
        set("long", @LONG
����һλ��ͺ���ĵ��ˣ��������ܸɣ���ȫ
��̵��Ĵ������г���δ�����ǰ������
�Ƿ�����������ȫ�����µ�����
LONG);

        set("gender", "����");
        set("age", 22);
        set("class", "taoist");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 22);
        set("int", 22);
        set("con", 22);
        set("dex", 22);

        set("qi", 600);
        set("max_qi", 600);
        set("jing", 400);
        set("max_jing", 400);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 0);

        set("combat_exp", 30000);
        set("score", 20000);

        set_skill("force", 60);
        set_skill("xiantian-gong", 50);
        set_skill("sword", 60);
        set_skill("quanzhen-jianfa",60);
        set_skill("dodge", 50);
        set_skill("jinyan-gong", 50);
        set_skill("parry", 60);
        set_skill("unarmed",60);
        set_skill("strike",60);
        set_skill("haotian-zhang", 50);
        set_skill("literate",50);
        set_skill("taoism",40);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
        prepare_skill("strike", "haotian-zhang");

        create_family("ȫ���", 4, "����");

        set("book_count",1);
        set("yusuo_count",1);

        set("inquiry", ([
                "���尲��" :  (: ask_ankang :),
                "���¾�" : (: ask_me :),
				"����������ؼ�" : (: ask_yusuo2 :),
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/grayrobe")->wear();
}
string ask_ankang()
{
        mapping fam;
        object me;
		me=this_player();
        if (! (fam = this_player()->query("family"))
           || fam["family_name"] != "ȫ���")
                return "�����뱾�̺��޹ϸ����⻰�ɽ���Ū�������ˡ�";
		command("say ������ᱳʹ�ȳ����岻̫�ã���˵�Ե����߸�ͻ��Ϊ������\n");
		command("say ˭Ҫ�Ǹ���Ū�����Ҹж�������\n");
		me->set_temp("book/askzhangli",1);
        return "������ʹ��ˣ����������˰�!\n";

}
string ask_me()
{
        mapping fam;
        object ob,me;
		me=this_player();

        if (! (fam = this_player()->query("family"))
           || fam["family_name"] != "ȫ���")
                return "�����뱾�̺��޹ϸ����⻰�ɽ���Ū�������ˡ�";
        if (!me->query("quest/qz/dichuan"))
                return "��Ǻ��ĵմ����ӣ�������������";
  
		if (!me->query_temp("book/askzhangli"))
		{
			return "���ҷ��׷ǹʣ������أ�\n";
		}
		
		if (!me->query_temp("book/givegao"))
		{
			command("say �ҵ����岻̫�ã������������ҵ����߸࣬�Ҿ�ָ������εõ��Ȿ�飡\n");
			me->set_temp("book/askyusuo2");
			return "���߸���Ҫ�ڲ�ҩ�����в��ϰ��Ʒ������ɣ���ҩ�Ǹ��϶�������ϧ�ĺܣ�\n";
		}
        if (query("book_count") < 1)
                return "�������ˣ����¾��Ѿ�����ȡ���ˡ�";
		if (me->query("party/gongji")<1000)
		{
			return "������ɹ���ֵ����1000��ȥŬ������ȥ��\n";
		}
		me->add("party/gongji",-1000);
		command("say "+me->query("name")+",���Ѿ��۳�����1000�����ɹ���ֵ��\n");

        add("book_count", -1);
        ob = new(__DIR__"obj/daodejing-ii");
        ob->move(this_player());
        return "�ðɣ��Ȿ�����¾�������ȥ�ú��ж��������ĵط����������ҡ�";

}

string ask_yusuo2()
{
        mapping fam;
        object ob,me;
		me=this_player();
        if (! (fam = this_player()->query("family"))
           || fam["family_name"] != "ȫ���")
                return "�����뱾�̺��޹ϸ����⻰�ɽ���Ū�������ˡ�";
        if (!me->query("quest/qz/dichuan"))
                return "��Ǻ��ĵմ����ӣ�������������";
        if (query("yusuo_count") < 1)
                return "�������ˣ��������²��Ѿ�����ȡ���ˡ�";
		if (!me->query_temp("book/askzhangli"))
		{
			return "���ҷ��׷ǹʣ������أ�\n";
		}
		if (!me->query_temp("book/givegao"))
		{
			command("say �ҵ����岻̫�ã������������ҵ����߸࣬�Ҿ�ָ������εõ��Ȿ�飡\n");
			me->set_temp("book/askyusuo2",1);
			return "���߸���Ҫ�ڲ�ҩ�����в��ϰ��Ʒ������ɣ���ҩ�Ǹ��϶�������ϧ�ĺܣ�\n";
		}
		
		if (me->query("party/gongji")<1000)
		{
			return "������ɹ���ֵ����1000��ȥŬ������ȥ��\n";
		}
		
		me->add("party/gongji",-1000);
		command("say "+me->query("name")+",���Ѿ��۳�����1000�����ɹ���ֵ��\n");

        add("yusuo_count", -1);
        ob = new("/d/quanzhen/obj/yusuojue2");
        ob->move(this_player());
		me->delete_temp("book");
        return "�ðɣ��Ȿ�����������ʮ�ľ��²᡹����ȥ�ú��ж��������ĵط����������ҡ�";

}

int accept_object(object who, object ob)
{

	
	if (ob->query("id")=="guiling gao"
		&& who->query_temp("book/askyusuo2")
		&& ob->query("owner")==who->query("id"))
	{
		command("say "+who->query("name")+"�ã��ǳ����������õ�������߸��ˣ�\n");
		command("say �������գ���˳��������Ʒ��\n");
		command("say �����Т�����˼ң��Ҿ͸����Ȿ�ؼ����������ܣ�\n");
		//who->delete_temp("book");
		who->set_temp("book/givegao",1);
		destruct(ob);
		message_vision(HIY"$N���������������������õ���̵��������ؼ��Ļ��ᣡ\n"NOR,who);
		return 1;
	}
	
}