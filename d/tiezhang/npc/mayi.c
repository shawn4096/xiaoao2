// Npc: /u/zqb/tiezhang/npc/mayi.c
// Date: zqb 97/06/17

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
void create()
{
    set_name(HIY"���´���"NOR, ({
    "mayi zhanglao",
    "mayi",
    "zhanglao",
	}));
	set("long",
    "����һ����Լ��Ѯ�����ߣ���ͷ���������ް߰ס��������ư����\n"
    "�������̫��Ѩ�߸߹���΢�յ�˫Ŀ��ʱ����������������\n"
	"̫��Ѩ�߸߷����ƺ���������\n"
	);

	set("gender", "����");
	set("attitude", "peaceful");

	set("age", 60);
	set("shen_type", 1);
	set("str", 28);
	set("int", 23);
	set("con", 23);
	set("dex", 28);
	set("max_qi", 25000);
	set("max_jing", 4000);
	set("max_jingli", 6000);

	set("neili", 20000);
	set("max_neili", 20000);
	set("jiaji", 200);
	set("combat_exp", 4500000);
	set("score", 10000);

	set_skill("force", 350);
	set_skill("guiyuan-tunafa", 350);
	set_skill("dodge", 350);
	set_skill("shuishangpiao", 350);
	set_skill("strike", 350);
	set_skill("tiezhang-zhangfa", 350);
	set_skill("parry", 350);
	set_skill("axe", 350);
	set_skill("lietian-fu", 350);
	set_skill("liuye-daofa", 350);
	set_skill("blade", 350);

	map_skill("force", "guiyuan-tunafa");
	map_skill("dodge", "shuishangpiao");
	map_skill("strike", "tiezhang-zhangfa");
	map_skill("parry", "tiezhang-zhangfa");
	map_skill("blade", "liuye-daofa");
	map_skill("axe", "lietian-fu");
	prepare_skill("strike","tiezhang-zhangfa");
	
	create_family("���ư�", 15, "��ϯ����");
	
	setup();
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