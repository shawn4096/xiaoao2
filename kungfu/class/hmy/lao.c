// lao.c
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
      
	set_name("��ͷ��", ({ "lao touzi", "lao", "touzi",}));
	set("nickname", "�ƺ�����");    
	set("title", "ʥ������");
	set("long", "������ļ�֮���֣�Զ������һ������㣬����ȴ��֮���飬�����������Ѹ�١�\n");
	set("gender", "����");
	set("age", 50);
	set("attitude", "peaceful");
	set("shen", 10000);
	set("str", 22);
	set("int", 25);
	set("con", 21);
	set("dex", 40);
        
	set("max_qi", 5300);
	set("max_jing", 3400);
	set("eff_jingli", 3400);
	set("jiali", 150);
	set("combat_exp", 1000000);
	set("shen", -4000);

	set_temp("apply/attack", 150);
	set_temp("apply/defence", 140);

	set_skill("tianmo-dao",250);
	set_skill("blade", 250);
	set_skill("dodge",250);
	set_skill("huanmo-wubu", 250);
	set_skill("force", 250);
	set_skill("literate", 100);
	set_skill("tianmo-gong", 250);
	set_skill("parry", 250);
	//set_skill("tianmo-zhang", 250);
	//set_skill("strike", 250);
	
	map_skill("parry", "tianmo-dao");
	map_skill("blade", "tianmo-dao");
	 map_skill("dodge", "huanmo-wubu");
	 map_skill("force", "tianmo-gong");
	//map_skill("strike", "tianmo-zhang");
	//prepare_skill("strike", "tianmo-zhang");
	setup();
	create_family("�������",9,"����");
	carry_object(BINGQI_D("blade"))->wield();
	carry_object("/clone/misc/cloth")->wear();        
}
void attempt_apprentice(object ob)
{
     if(ob->query("int") < 25 ){
        command("say ��һ����ɵͷɵ�Եģ�������ô�ͣ���20���Զ���������������ã���");
        return;
        }
/*	 if(ob->query("gender") =="Ů��" ){
        command("say Ů���Ӻ����鷳���ҿ��㻹��ȥѰ��������˿�������˵����������Ů���ӣ���");
        return;
        }
	 	// if(!ob->query("family") || ob->query("family/family_name")!="�������" ){
	 if(ob->query("family/family_name")!="�������" ){
        command("say ��������ʦ�����˺θ�!��");
        return;
        }*/
	if(ob->query("gender") =="����" ){
        command("say �����ֲ��в�Ů�Ļ�ɫ������Ϊʦ����");
        return;
        }
     command("haha");
	 command("say �ðɣ�Ϊ�˹��������̣��Ҿ��������ˡ�");
     command("recruit " + ob->query("id"));
}