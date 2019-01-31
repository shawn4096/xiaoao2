// /u/beyond/mr/npc/bao.c ����ͬ
// this is made by beyond
// update 1997.6.24
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int ask_yusui();

void create()
{
	
	set_name("����ͬ",({"bao butong","bao","butong"}));
        set("title","���ׯׯ��");
        set("nickname","��������");
  	set("long", 
              "������Ľ�ݸ��Ľ���ֵܹ���Ľ�ݽ��ׯ��ׯ����\n");
        set("age", 25);
	set("attitude", "friendly");
        set("unique", 1);
	set("shen_type", 1);
	set("str", 46);
	set("int", 26);
	set("con", 26);
	set("dex", 26);
	
	set("max_qi", 12500);
	set("max_jing", 5000);
	set("neili", 12500);
	set("max_neili", 12500);
	set("jiali", 200);
	set("combat_exp", 4850000);
	set("score", 85000);

       // set_skill("sword",350);
        set_skill("blade",350);
        set_skill("dodge",350);
        set_skill("force", 350);
		set_skill("shenyuan-gong", 350);
		set_skill("yanling-shenfa", 350);
        set_skill("parry", 350);
        set_skill("murong-daofa", 350);
        set_skill("literate", 130);
       // set_skill("finger", 130);
       // set_skill("canhe-zhi", 130);
        set_skill("strike", 350);
        set_skill("xingyi-zhang", 350);

		map_skill("force", "shenyuan-gong");
        map_skill("strike", "xingyi-zhang");
        //map_skill("finger", "canhe-zhi");
		map_skill("dodge", "yanling-shenfa");
		map_skill("parry", "murong-daofa");
		map_skill("blade", "murong-daofa");  
		//prepare_skill("finger", "canhe-zhi");
        prepare_skill("strike", "xingyi-zhang");
 
       setup();
        carry_object(__DIR__"obj/cloth2")->wear();
         carry_object(__DIR__"obj/blade")->wield();   
        create_family("����Ľ��",3,"����");
        set("inquiry", ([
            "name" : "��Ҳ����Ҳ���Ҿ��ǹ���Ľ�ݽ��ׯׯׯ������ͬ��\n",
            "here" : "�����Ǵ��������������룬�ѵ���û����˵����\n",
            "rumors" : "Ľ�ݹ��ӵ��Ա�֮������ʩ��������������\n",
            "����" : "����ס������ˮ鿣���Ľ�ݹ��ӵ�����Ѿ�ߣ�������������һͬ�̷�ӡ�\n",
            "����" : "���̹���ס������С��������Ҫ�ݼ�Ľ�ݹ��ӵ��˶�Ҫ�������ﾭ����\n",
            "������" : "��������Ľ�ݹ��ӵı��ã���֪��ʲôʱ�����ǳ��ס�\n",
            "�˰ٴ�" : "�˰ٴ����Ҵ�磬������������ׯ��ׯ����\n",
            "����Ǭ" : "����Ǭ���Ҷ��磬���������ϼׯ��ׯ����\n",
            "�粨��" : "�粨�������ĵܣ�����������˪ׯ��ׯ����������ϲ�������˴�ܡ�\n",
            "����ˮ�" : "����ˮ��ǰ������ס�ĵط��������ﲻԶ��\n",
            "����С��" : "����С���ǰ��̹���ס�ĵط�����С��������ˮ·�͵��ˡ�\n",
            "��٢��ɽׯ" : "��٢��ɽׯ�ǹ��ӵĹ���ס�ĵط���ƽʱ���Ҷ�����ȥ��\n",
            "��ʩˮ��" : "���������������֮���ڣ��ҿɲ������˵��\n",   
			"���鵶�����":   (: ask_yusui :),

       ]));
}

void attempt_apprentice(object ob)
{
    if (ob->query_skill("shenyuan-gong",1)<100)
    {
		command("say ��Ľ���������ڹ���Ϊ������Ԫ������100������Ŭ������ȥ�ɡ�\n");
    }
	command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");
	command("recruit " + ob->query("id"));
	ob->set("title","����Ľ�ݵ��Ĵ�����");
}
int ask_yusui()
{
	int i,j;
	object me=this_player();
	if (me->query("family/family_name")!="����Ľ��")
	{
		command("say �㲻���ҹ�����Ľ�ݵ��ˣ�����Ϲ����ʲô��\n");
		return 1;
	}
	if (me->query_skill("murong-daofa",1)<200)
	{
		command("say ���Ľ�ݵ�������200��˵����Ҳ������\n");
		return 1;
	}
	if (time()-me->query("quest/mr/mrdf/yusui/time")<86400)
	{
		command("say ������̫Ƶ���ˣ�\n");
		return 1;
	}
	if (me->query("quest/mr/mrdf/yusui/pass"))
	{
		command("say ���Ѿ��⿪�ˣ�\n");
		return 1;
	}

    j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	i= random(j);
	command("say ����Ľ�ݵ�Ľ�ݵ���������ʵս���ܽ�������似�����߹����ԣ�\n");
	command("say �뵱���Ҵ�����������֣�������ս���⵶�������º����ͣ�\n");
	message_vision(HIC"\t\t����ͬ˵����"HIY"����ǵ���׳־!\n"NOR,me);
	message_vision(HIC"\t\t����ͬ˵����"HIR"�䵶��ת��Ǭ��!\n"NOR,me);
	message_vision(HIC"\t\t����ͬ˵����"HIG"ң����ǧ��ѩ!\n"NOR,me);
	message_vision(HIC"\t\t����ͬ˵����"HIM"׳־����������!\n"NOR,me);
	command("say �������׸��������Ѫ�����ţ�\n");
	command("say �㶮�������׸����Ҫ��Ҳ�Ͷ��������ŵ��������壡\n");
	command("say ��Ȼ����ѧ���Ҿ�˵�����������ܷ�����Ϳ���������ˣ��������ˣ�\n");
	me->start_busy(2);
	if (i<7
		&&me->query("kar")>25)
	{
		message_vision(HIY"$N���Ű���ͬ�Ľ��⣬��������ǻ�����Ľ��⣬���Ȼ��������Ľ�ݵ������������壡\n"NOR,me);
		message_vision(HIG"�Ǿ���һ����ǰ��һ�����ƣ��̲�ס����������������������������������\n"NOR,me);
		message_vision(HIY"\t\t����ǵ���׳־!\n"NOR,me);
		message_vision(HIR"\t\t�䵶��ת��Ǭ��!\n"NOR,me);
		message_vision(HIG"\t\tң����ǧ��ѩ!\n"NOR,me);
		message_vision(HIM"\t\t׳־����������!\n"NOR,me);

		message_vision(HIY"$N������Խ��Խ����������������������������Ϊ���飬��Ϊ��ȫ����\n"NOR,me);
		message_vision(HIG"����ͬ����˵����仰����Ȼ�����쳤Х����\n"NOR,me,this_object());
		command("shout �Ҵ�Ľ��������һԱ�������γ���Ҵ��࣡\n");
		command("chat �������ƣ������Ƿ壬��Ľ�ݡ����Ҵ�Ľ�ݽ���ϲ�����ţ����ȸ�һ��ף�\n");
		command("chat* congra "+me->query("id"));

		command("chat* laught "+me->query("id"));
		me->set("quest/mr/mrdf/yusui/pass",1);
		log_file("quest/mrdfyusui",sprintf("%-18sʧ��%s�κ󣬳ɹ��Ӱ���ͬ���������鵶������ľ������ڣ�����%d����%d��\n",
			me->name(1)+"("+capitalize(getuid(me))+")",
			chinese_number(me->query("quest/mr/mrdf/yusui/fail")), 
			me->query("kar"), 
			me->query("int")), me);
		return 1;
	}else {

		command("sigh " + me->query("id"));
		command("poor "+ me->query("id"));
		command("disapp "+ me->query("id"));

		command("say �����㻹��δ���������а������ڵ�ʱ��,����������!");
		message_vision(HIG"\n\n$N����Ľ�ݵ��������鵶��ʧ�ܣ���\n"NOR,me,this_object());

		me->add("quest/mr/mrdf/yusui/fail", 1);
		me->set("quest/mr/mrdf/yusui/time", time());
		log_file("quest/mrdfyusui",
			sprintf("%-18s��Ӱ���ͬ���������鵶������ľ���ʧ�ܣ�ʧ��%s�Ρ�\n",
				me->name(1)+"("+capitalize(getuid(me))+")",
				chinese_number(me->query("quest/mr/mrdf/yusui/fail")) 
			), me);
	
		me->start_busy(1);
	}
	return 1;
/**/
}