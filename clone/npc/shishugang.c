// shishugang.cʷ���

inherit NPC;
void init();

void create()
{
        set_name("ʷ���", ({ "shi shugang","shi","shugang" }));
        set("nickname", "���ʨ��");
        set("long", 
        "��������ɽׯ���ֵܵ���������ɫ��΢���ƣ����Ǿò����������ӡ�\n"
        "��˵�������˴���һ����տ�Ĺ���\n");
        set("gender", "����");
        set("age", 29);
        set("attitude", "friendly");
        set("shen", 6500);
        set("str", 32);
        set("int", 20);
        set("con", 23);
        set("dex", 23);
        set("eff_jingli",2000);
        set("max_qi", 12000);
        set("max_jing", 1500);
        set("neili", 2600);
        set("max_neili", 5600);
        set("jiali", 120);
        set("combat_exp", 650000);
    
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "strike.tiangang" :)
            }));

         
        set_skill("strike", 140);
        set_skill("sword", 140);
        set_skill("dodge", 140);
        set_skill("parry", 140);
        set_skill("xiantian-gong", 160);
        set_skill("tiangang-zhang",150);
        set_skill("quanzhen-jianfa", 140);
        set_skill("jinyan-gong",140);             
        set_skill("literate", 140);
        set_skill("force",140);
        map_skill("force", "xiantian-gong");
        map_skill("dodge", "jinyan-gong");
        map_skill("strike","tiangang-zhang");
        map_skill("parry", "tiangang-zhang");
        map_skill("sword", "quanzhen-jianfa");
        prepare_skill("strike", "tiangang-zhang");

         set("inquiry", ([
                "�����" : "ȫ�������˼��ҵ����˲ŵ��Կ�����",
                "����" : "��Ҫ�����Ǹ�������һ��Ҫɱ������",
                "����": "�˼�Ϊ�����ֵ��洫֮�����书����С�ɣ�ѧϰ����Σ�ա�",
                
        ]) );
        
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("gold", 3+random(5));
}
void init()
{
	object me=this_player();
	/*if (me->query_temp("anran/ask1"))
	{
		this_object()->apply_condition("neishang",50);
	}*/
	if (interactive(me) && !is_fighting()&&me->query_temp("quest/shendiao/��ѩ�����/askanran")) {
		this_object()->apply_condition("neishang",150);
	}


}