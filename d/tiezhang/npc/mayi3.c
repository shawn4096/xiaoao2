//mayi3.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
void create()
{
       set_name("������", ({"huang lingtian","huang","lingtian"}));
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

		set_skill("force", 250);
		set_skill("guiyuan-tunafa", 250);
		set_skill("dodge", 250);
		set_skill("literate", 100);
		set_skill("shuishangpiao", 250);
		set_skill("strike", 250);
		set_skill("tiezhang-zhangfa", 250);
		set_skill("parry", 250);
		set_skill("blade", 250);
		set_skill("liuye-daofa", 250);
		set_skill("tiezhang-xinfa",150);

       map_skill("force", "guiyuan-tunafa");
       map_skill("dodge", "shuishangpiao");
       map_skill("strike", "tiezhang-zhangfa");
       map_skill("parry", "liye-daofa");
       map_skill("blade", "liuye-daofa");
       prepare_skill("strike", "tiezhang-zhangfa");
		
	   create_family("���ư�", 15, "����");
       setup();
       carry_object(__DIR__"obj/mayi")->wear();
       carry_object("clone/weapon/blade")->wield();       
}
void init()
{
       object me, ob;
       mapping fam;

       ::init();

       ob = this_player();
       me = this_object();
       
       if (interactive(ob) 
       && !environment(ob)->query("no_fight")
       && ( (fam = ob->query("family")) && fam["family_name"] != "���ư�" ) 
        && (int)ob->query("combat_exp", 1) >= 10000 ) 
       {
               if( !ob->query_temp("warned") ) {
        command("say վס���㲻�����ư���ӣ������ڴ˾�������");
        command("say �㻹�������뿪�˵ذɣ���Ȼ�����Ҫ���㲻�����ˣ���");
        command("hehe");
                       ob->set_temp("warned", 1);
               }
          else if( ob->query_temp("stay") < 3 ) ob->add_temp("stay", 1);
                else {
                       command("say ���ò��ͷ��ˣ����ҵ����ư�����Ұ������\n");
                       remove_call_out("hiting_ob");
                       call_out("hiting_ob", 1, ob);
               }
       }       

}
void attempt_apprentice(object ob)
{
      object me  = this_object();
      mapping fam = ob->query("family");

        if(!fam || fam["family_name"] != "���ư�"){
                command("say "+RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
                }
        if ((int)ob->query("shen") > -500000) {
                command("hehe");
                command("say ���ư�ɲ����Ĵ�������������ӣ�����500k����������ҡ�\n");
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
        if ((int)ob->query_skill("guiyuan-tunafa", 1) <= 150) {
                command("say Ҫѧ��Ϊ������书�������и�����ڹ���Ϊ,150��");
                command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ���ڹ�Ԫ���ɷ��϶��µ㹦��");
                return;
                }
                command("say �ðɣ��Ҿ��������ˡ�ϣ����������ư��񹦣���֮������\n");
                command("recruit " + ob->query("id"));
                ob->set("is/tiezhang",1);
                ob->set("class","brigand");
}