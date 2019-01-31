// gaozecheng.c (kunlun)
// ��һ���е���ʦ��
inherit NPC;
inherit F_MASTER;
#include <ansi.h>

void create()
{
	set_name("�����", ({ "gao zecheng", "gao" }));
	set("long",
		"������ɫ���ۣ�����б�峤������ʮ�˾�����͡�\n"
		"���ֺ�˪��һ��Ҫ�������ǵ�ģ����\n");
	set("gender", "����");
	set("age", 20);
	set("attitude", "heroism");
	set("shen_type", 1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);

	set("max_qi", 5600);
	set("max_jing", 3500);
	set("neili", 6500);
	set("max_neili", 6500);
	set("jiali", 130);
	set("combat_exp", 150000);
	set("score", 10000);

	set_skill("force", 180);
	set_skill("xuantian-wuji", 180);
	set_skill("dodge", 180);
	set_skill("taxue-wuhen", 180);
	set_skill("parry", 180);
	set_skill("sword", 180);
	set_skill("liangyi-jian",180);
	set_skill("cuff", 180);
	set_skill("zhentian-quan", 180);

	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("sword", "liangyi-jian");
	map_skill("cuff", "zhentian-quan");
	map_skill("parry", "xunlei-jian");
	set("chat_chance_combat", 25);
	set("chat_msg_combat", ({
  		(: perform_action, "cuff.zhentian" :),
  	}));

	prepare_skill("cuff", "zhentian-quan");

	create_family("������", 5, "����");
	setup();
   //     carry_object(BINGQI_D("changjian"))->wield();
        carry_object("/d/kunlun/obj/pao3")->wear();
}
void attempt_apprentice(object ob)
{
     if(ob->query("gender")=="Ů��"){
	    command("fear");
	    command("say "+RANK_D->query_respect(ob)+"ʦ����׼����Ů���ӣ���ȥ����ղ��ʦ械ɡ�");
   	    return;
	 }
	 if(ob->query("appren_hezudao", 1) == 1) {
	    command("say ǰ�����ҿ������Ц��������ɱ�������ˡ�");
	    return;
	 }
	 command("say ��Ȼ"+RANK_D->query_respect(ob)+"Ľ������֮����ǧ����������������Ե���������Ӣ��,�Ҿ�������ɡ�");
	 command("say ��Ȼ"+RANK_D->query_respect(ob)+"��������أ����˽����������ȥ��ղ��ʦ������£���������ʲô�¡�");
	 command("say �Ҵ����ؽ����������ɹ��ף�ǧ���ס����Ī����ǰ�̡�");

	 command("recruit " + ob->query("id"));
	// ob->set("title","�����ɵ���������");
	return;
}
