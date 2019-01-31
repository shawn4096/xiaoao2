// NPC :zhong_wanchou.c ����� 
// By River 98/12
#include <ansi.h>

inherit NPC;
string ask_duan();
string ask_eren();
string ask_manying();

void create()
{
        set_name("�����", ({ "zhong wanchou", "zhong", "wanchou"}));
        set("title",HIC"��ٹȹ���"NOR);
        set("nickname",HIR"������"NOR);
        set("gender", "����" );
        set("age", 42);
        set("str", 30);
        set("con", 23);
        set("dex", 22);
        set("int", 10);
        set("per", 5);
   		set("attitude", "heroism");

        set("max_qi", 28000);
        set("max_jing", 5000);
        set("eff_jingli", 5000);
        set("neili", 20000);
		set("qi", 18000);	
        set("max_neili", 20000);
        set("jiali", 140);
        set("unique", 1);
        
        set("long","ֻ�����ó�һ���������۾��������ߣ�һ��԰԰�Ĵ����ȴ����ͼ���һ�顣\n");
        set("combat_exp", 6400000);
        set("shen", -1000); 

        set_skill("parry", 400);
        set_skill("dodge", 400);
        set_skill("force", 400);
        set_skill("strike", 400);
        set_skill("yijin-jing", 400);        
        set_skill("shaolin-shenfa", 400);
        set_skill("zhongjia-zhang", 400);
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "zhongjia-zhang");
        map_skill("strike", "zhongjia-zhang");
        map_skill("force", "yijin-jing");
        prepare_skill("strike","zhongjia-zhang");

        set("inquiry", ([            
            "������" : (: ask_duan :),
			 "�Ĵ����" : (: ask_eren :),
			"�����ӯ" : (: ask_manying :),
        ]));

        setup();
        carry_object("/clone/armor/cloth")->wear();
}
string ask_duan()
{
	command("say �����������Ӿ��Ǹ�С������\n ");
	return "����������С������˭���Ҹ�˭����";

}
string ask_eren()
{
	command("say �Ĵ�������ڽ������������ϣ�\n");
	command("say ����Ϊ���׼���--���кף�\n");
	command("say ����Ϊ�Ϻ�����--��ĳ�ˣ�\n");
	command("say �϶�Ϊ�޶���--Ҷ���\n");
	command("say �ϴ��Ƕ����ӯ--�����죡\n");
	this_player()->set_temp("yanqing/askeren",1);
	return "˭�����Ĵ���ˣ�˭������������\n";
}
string ask_manying()
{
	object me=this_player();
	if (me->query("shen")>-200000)
	{
		command("say ��һ����ò��Ȼ��������ʿ��������(С��200k����)��\n");
		return "�ߣ�С������һ���Ͳ��Ǻö�����\n";
	}
	if (!me->query_temp("yanqing/askeren"))
	{
		command("say �����������Ĵ����֮�ף�\n");
		return "�ߣ�С������һ���Ͳ��Ǻö�����";
	}
	command("say ����������Ǵ���һ���ӣ����������䲻����\n");
	command("say ���Ϊ�ҵ���һֱ�ڱ�������˵�����黨��һ����û��\n");
	command("say ������ȥ���������ȥ�Ǳ߿�����\n");
	command("say �������ҿ������Ƣ������̫�ã���ҪС�ģ�\n");
	
	this_player()->set_temp("yanqing/askzhong",1);
	return "�Ĵ���ˣ�˭����˭����\n";
}