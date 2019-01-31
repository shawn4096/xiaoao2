

#include "ansi.h"
inherit NPC;


void create()
{
        set_name("ŷ����", ({ "ouyang feng", "ouyang", "feng" }));
        set("long","���߹���һ�������������ף�������ꪣ�һ��������̡����ƣ�\n"+
                "������ֱ��Ѿõ��常ŷ���档\n" );
        set("nickname","����");
        set("title", "����ɽׯׯ��");
        set("gender", "����");
        set("age", 65);
        set("attitude", "heroism");

        set_skill("cuff", 550);
        set_skill("strike", 500);
        set_skill("dodge", 550);
        set_skill("hamabu", 550);
        set_skill("parry", 550);
        set_skill("force", 550);
        set_skill("hamagong", 550);
        set_skill("lingshe-zhangfa",550);
		set_skill("lingshe-quanfa",550);

        set_skill("staff",550);
        set_skill("poison",300);
		set_skill("shentuo-zhang",550);

        map_skill("strike","shentuo-zhang");
		map_skill("cuff","lingshe-quanfa");
        map_skill("dodge","hamabu");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("force","hamagong");
        map_skill("staff","lingshe-zhangfa");
        prepare_skill("cuff","lingshe-quanfa");
		prepare_skill("strike","shentuo-zhang");

        set("str", 45);
        set("int", 28);
        set("con", 40);
        set("dex", 28);

        set("max_qi", 55000);
        set("qi",55000);
		set("eff_qi",55000);
        set("max_jing", 9000);
        set("jing",9000);
		set("eff_jing",9000);
        set("max_jingli", 9000);
        set("jingli",9000);
		set("eff_jingli",9000);

        set("neili", 56000);
        set("max_neili", 56000);
        set("jiali", 250);
        set("combat_exp", 15600000);

               //   set("attitude", "peaceful");
                  set("shen_type", -1);

        create_family("����ɽ", 1 , "ׯ��");
        set("inquiry", ([
              //  "ŷ����" : "ŷ���桢ŷ���棬������������ͦ��ġ�����\n",
			                //"" : "ŷ���桢ŷ���棬������������ͦ��ġ�����\n",

         ]));
		 set("chat_chance_combat", 100);
		 set("chat_msg_combat", ({
			(: perform_action, "cuff.wugu" :),
			(: perform_action, "cuff.lingshe" :),
			(: perform_action, "staff.baibian" :),
			(: perform_action, "staff.luoye" :),
			(: exert_function, "hama" :),
			(: exert_function, "nizhuan" :),
			(: perform_action, "staff.wanshe" :),
		}));
	//	call_out("check",5);

        setup();
        carry_object("/d/baituo/obj/gs-zhang")->wield();
        carry_object(ARMOR_D("cloth"))->wear();

}
int init()
{

	command("yun hama");
	command("yun nizhuan");
}

int feng_say()
{
	command("haha ");
	command("say �����������������µ�һ������ͨ������������ͷ��������һ���������̣�\n");
	command("heng ");
	command("say �����������ײ��У���������ô��\n");
	//command("say ��\n");
	command("heng");
	command("heng");
	command("heng");
	command("say ��֪�������ʿ�ǲ���������ˣ���Ҫ���ԣ���\n");
	
}
int check()
{
	object ob=this_object();
	if (ob->query_temp("weapon"))
	{
		command("yun hama");
		command("jifa parry lingshe-zhangfa");
		command("yun nizhuan");
		command("perform staff.shoot");
		command("perform staff.baibian");
		command("perform staff.luoye");
		command("perform staff.wanshe");
	}else{
		command("yun hama");
		command("jifa parry lingshe-quanfa");
		command("yun nizhuan");
		command("perform cuff.wugu");
		command("perform cuff.lingshe");
	
	}
	
}