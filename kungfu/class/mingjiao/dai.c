// NPC dai.c ���˿
// Modify By River@sj 99.06
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
void create()
{
	object weapon;
        set_name("���˿",({"dai qisi","dai","qisi"}));
        set("title","���̻��̷���");
        set("nickname",MAG"��������"NOR);
        set("gender","Ů��");
        set("long",  "�������̵��Ĵ󻤷�֮һ������������\n"+
                     "������������ǵ������̵ĵ�һ��Ů��\n"+
                     "�������Ѹߣ��Բ���ɫ�Բ������ꡣ\n");
        set("age", 45);
        set("attitude", "peaceful");
        set("shen", -10000);
        set("str", 24);
        set("int", 40);
        set("con", 26);
        set("dex", 30);        
        set("max_qi", 28000);
        set("max_jing", 12200);
        set("eff_jingli", 12200);
        set("jiali", 170);
        set("combat_exp", 5600000);
        set("unique", 1);

        set_skill("throwing",400); 
        set_skill("dodge",400);
        set_skill("force", 400);
        set_skill("duoming-jinhua",450);
        set_skill("literate",230);
        set_skill("piaoyi-shenfa", 400);
        set_skill("shenghuo-shengong", 400);
        set_skill("parry", 400);
        set_skill("hand", 140);
        //set_skill("yingzhua-shou",120);
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("throwing", "duoming-jinhua");
        map_skill("parry", "duoming-jinhua");
        map_skill("hand", "yingzhua-shou");
        prepare_skill("hand","yingzhua-shou");

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "throwing.huayu":),
	}));

        create_family("����", 36, "����");
        setup();
        if(clonep()){
        	weapon = unew(BINGQI_D("shanhu-jin"));
        	if(!weapon) weapon = new(BINGQI_D("jinhua"));
        	weapon->move(this_object());
		carry_object("/d/mingjiao/obj/yel-cloth")->wear();
		carry_object("/d/mingjiao/obj/luopan");
		carry_object(BINGQI_D("jinhua"))->wield();
	}
}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping fam = ob->query("family");
        mapping my_fam = me->query("family");
        if(!fam || fam["family_name"] != "����"){
                command("say "+RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }
        if(ob->query("gender")!="Ů��"){
                command("say "+RANK_D->query_respect(ob)+"���ǻ�ȥ�ɣ�����ֻ��Ů���ӡ�");
                return;
        }
        if(fam["master_name"] == "���޼�"){
                command("haha");
                command("say "+RANK_D->query_respect(ob)+"���ǽ����״����ӣ�"+RANK_D->query_self(me)+"����������Ϊͽ��"); 
                return;
        }
        if (fam["generation"] == my_fam["generation"]){
                command("shake");
                command("say "+RANK_D->query_respect(ob)+"�Ѱݹ���ʹΪʦ��"+RANK_D->query_self(me)+"����������Ϊͽ��");
                return;
        }
        if ((int)ob->query_skill("shenghuo-shengong", 1) < 100) {
                command("say Ҫѧ��Ϊ������书�������и�����ڹ���Ϊ��"); 
                command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ����ʥ�����϶��µ㹦��");
                return;
        }
        if ((int)ob->query_int() < 28) {
                command("say ��ѧ�ҵĽ𻨰����������ܹ��۹��ķ��������˷���");
                command("say ���������Է��棬"+RANK_D->query_respect(ob)+"�Ƿ��Ӳ��˵㣿");
                return;
        }
        command("say �ţ����㻹�Ǹ�ѧ����ϣ������Ҿ�������ɣ�");
        command("say ��л������ӣ����������ֵ�һ���ģ�Ϊ�������壬�������̷�����ɡ�");
        command("recruit " + ob->query("id"));
        ob->set("title", MAG"���������������½���"NOR);
}
