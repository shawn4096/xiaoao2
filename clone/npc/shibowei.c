// shibowei.c ʷ����

inherit NPC;
int ask_gui();

void create()
{
        set_name("ʷ����", ({ "shi bowei","shi", "bowei" }));
        set("nickname", "�׶�ɽ��");
        set("long", 
        "��������ɽׯ���ֵܵĴ�磬��Ŀ��࣬��ɫ΢�ڡ�\n"
        "��˵һ�����ޱ�������뻯��\n");
        set("gender", "����");
        set("age", 38);
        set("attitude", "peaceful");
        set("shen", 4500);
        set("str", 25);
        set("int", 18);
        set("con", 25);
        set("dex", 20);
        
        set("max_qi", 18000);
        set("max_jing", 6000);
        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 150);
        set("combat_exp", 4500000);
         
    set_skill("force", 390);
    set_skill("hunyuan-yiqi", 390);
    set_skill("dodge", 390);
    set_skill("shaolin-shenfa", 380);
    set_skill("cuff", 390);
    set_skill("jingang-quan", 380);
    set_skill("parry", 390); 
    set_skill("literate", 120);

    map_skill("force", "hunyuan-yiqi");
    map_skill("dodge", "shaolin-shenfa");
    map_skill("cuff", "jingang-quan");
    map_skill("parry", "jingang-quan");
    prepare_skill("cuff", "jingang-quan");

    set("inquiry", ([
                "�����" : "���ܵĲ�ȫ�������˼Ҳŵ��Կ�����",
                "����" : "��Ҫ�����Ǹ�������һ��Ҫɱ������",
				"��ɽһ�߹�" : (: ask_gui :),
              	//"��Ȼ������"  : (: ask_anranzhang :),
                
    ]) );
        
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 50);
}

int ask_gui()
{
	command("say ����Ȼ��������������ģ������ŵù��ġ�\n");
	command("say ��ɽһ�߹��������߸����޶�����������������\n");
	command("say ������ʷ��յ��˾������Ǹ�����ɵģ���ɱ�����Ĳ�Ϊ�ˣ�\n");
	command("sigh ");
	command("consider");
	this_player()->set_temp("quest/shendiao/��ѩ�����/askgui",1);
	return 1;

}

int shi_say1()
{
	command("say ��Ȼ��������������ģ����ҾͲ������ˣ�����Ϊ���������ˡ�\n");
	command("say �������ܵ����ھ�������Ϊ���Σ���������֮������.\n");
	command("say ����Ҫ�о�β�����Ѫ��������.\n");
	command("sigh.\n");
	return 1;

}