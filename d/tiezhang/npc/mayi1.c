//mayi1.c ������

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
       set_name("������", ({"hong xiaotian","hong","xiaotian"}));
       set("title","���³���");
       set("nickname",HIY"������ӥ"NOR);
       set("long",
    "����һ����Լ��Ѯ�����ߣ���ͷ���������ް߰ס�\n"
    "�������̫��Ѩ�߸߹���΢�յ�˫Ŀ��ʱ�����������������ƺ���������\n"
       );

       set("gender", "����");
       set("attitude", "peaceful");
       set("unique", 1);
       set("age", 60);
       set("shen_type", -10);
       set("str", 28);
       set("int", 23);
       set("con", 23);
       set("dex", 28);
       set("per", 20);
       set("max_qi", 8000);
		set("max_jing", 3000);
		set("neili", 8000);
		set("max_neili", 8000);
		set("jiali", 150);
		set("combat_exp", 1600000);
		set("score", 10000);

		set_skill("force", 200);
		set_skill("guiyuan-tunafa", 200);
		set_skill("dodge", 200);
		set_skill("literate", 100);
		set_skill("shuishangpiao", 200);
		set_skill("strike", 200);
		set_skill("tiezhang-zhangfa", 200);
		set_skill("parry", 200);
		set_skill("blade", 250);
		set_skill("liuye-daofa", 250);
		set_skill("tiezhang-xinfa",150);

       map_skill("force", "guiyuan-tunafa");
       map_skill("dodge", "shuishangpiao");
       map_skill("strike", "tiezhang-zhangfa");
       map_skill("parry", "tiezhang-zhangfa");
       map_skill("blade", "liuye-daofa");
       prepare_skill("strike", "tiezhang-zhangfa");

       create_family("���ư�", 15, "����");

       setup();
       carry_object(__DIR__"obj/mayi")->wear();
       carry_object(BINGQI_D("blade"))->wield();
}
void attempt_apprentice(object ob)
{
      object me  = this_object();
      mapping fam = ob->query("family");

        if(!fam || fam["family_name"] != "���ư�"){
                command("say "+RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
                }
        if ((int)ob->query("shen") > -3000) {
                command("hehe");
                command("say ���ư�ɲ����Ĵ�������������ӡ�\n");
                return;
                }
        if(fam["master_name"] == "��ǧ��"){
                command("haha");
                command("say "+RANK_D->query_respect(ob)+"���ǰ����״����ӣ�"+RANK_D->query_self(me)+"����������Ϊͽ��");
                return;
                }
        if(fam["master_name"] == "�Ϲٽ���"){
                command("ah");
                command("say �Ϲٰ����������ѹ����������");
                command("say "+RANK_D->query_respect(ob)+"ԭ�����ϰ������ŵ��Ӱ���ʧ����"+RANK_D->query_self(me)+"����������Ϊͽ��");
                return;
                }
        if ((int)ob->query_skill("guiyuan-tunafa", 1) <= 30) {
                command("say Ҫѧ��Ϊ������书�������и�����ڹ���Ϊ��");
                command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ���ڹ�Ԫ���ɷ��϶��µ㹦��");
                return;
                }
                command("say �ðɣ��Ҿ��������ˡ�ϣ����������ư��񹦣���֮������\n");
                command("recruit " + ob->query("id"));
                ob->set("is/tiezhang",1);
                ob->set("class","brigand");


}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                add("apprentice_available", -1);
}

