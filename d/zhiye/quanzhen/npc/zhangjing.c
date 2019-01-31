#include <ansi.h>
inherit NPC;

string ask_me();
string ask_read();

void create()
{
        set_name("�ƾ�����", ({ "zhangjing daozhang", "zhangjing", "daozhang" }));
        set("long", @LONG
��λ��ȫ������ƹܾ���ĵ���������ǰ�ǳ�
������һ��˽�ӵķ��ӣ���Ϊ��Ľ������Ű�
����ȫ�����¡������Ͼ���Ϊ������ˣ�����
�ĸ������ò��Σ���Ҳ�������⣬���԰�����
�ĵ��ж������ˡ�
LONG);

        set("gender", "����");
        set("age", 36);
        set("class", "taoist");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 28);
        set("int", 18);
        set("con", 20);
        set("dex", 26);

        set("qi", 25000);
        set("max_qi", 25000);
        set("jing", 3500);
        set("max_jing", 3500);
        set("neili", 15900);
        set("max_neili", 15900);
        set("jiali", 200);

        set("combat_exp", 9620000);
        set("score", 15000);

        set_skill("force", 450);
        set_skill("xiantian-gong", 450);
        set_skill("sword", 450);
        set_skill("quanzhen-jianfa",450);
        set_skill("dodge", 450);
        set_skill("jinyan-gong", 450);
        set_skill("parry", 450);
        set_skill("leg",450);
        set_skill("strike",450);
        set_skill("haotian-zhang", 450);
        set_skill("literate",200);
        set_skill("taoism",280);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
        prepare_skill("strike", "haotian-zhang");

        create_family("ȫ���", 4, "����");

        set("book_count",1);
        set("inquiry", ([
                "ȫ���" : "��ȫ��������µ����������ڡ�\n",
                "���¾�" : (: ask_me :),
				//"����" : (: ask_read :),
        ]) );
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                 (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.qixing" :),
                (: perform_action, "sword.ding" :),
				(: perform_action, "sword.jianqi" :),
                (: perform_action, "sword.lian" :),
				(: exert_function, "daojue" :),
				(: exert_function, "wuqi" :),
				(: exert_function, "yusuo" :),
               
        }));
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/grayrobe")->wear();

}

string ask_me()
{
        mapping fam;
        object ob,me;
		me=this_player();
        
		if (! (fam = this_player()->query("family"))
           || fam["family_name"] != "ȫ���")
                return "�����뱾�̺��޹ϸ����⻰�ɽ���Ū�������ˡ�";
		if (me->query("party/gongji")<500)
		{
			return "������ɹ���ֵ����500��ȥŬ������ȥ��\n";
		}
		me->add("party/gongji",-500);
		command("say "+me->query("name")+",���Ѿ��۳�����500�����ɹ���ֵ��\n");
        if (query("book_count") < 1)
                return "�������ˣ����¾��Ѿ�����ȡ���ˡ�";
        if (!me->query("quest/qz/dichuan") )
                return "��������еմ����ӣ�����������\n";

        add("book_count", -1);
        ob = new(__DIR__"obj/daodejing-i");
        ob->move(this_player());
        return "�ðɣ��Ȿ�����¾�������ȥ�ú��ж��������ĵط����������ҡ�";

}
