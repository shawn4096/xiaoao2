

#include "ansi.h"
inherit NPC;
inherit F_MASTER;


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
        map_skill("strike","hamagong");
		map_skill("cuff","lingshe-quanfa");
        map_skill("dodge","hamabu");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("force","hamagong");
        map_skill("staff","lingshe-zhangfa");
        prepare_skill("cuff","lingshe-quanfa");
		//prepare_skill("strike","hamagong");

        set("str", 35);
        set("int", 28);
        set("con", 30);
        set("dex", 28);

        set("max_qi", 55000);
        set("qi",55000);
        set("max_jing", 9000);
        set("jing",9000);
        set("neili", 56000);
        set("max_neili", 56000);
        set("jiali", 250);
        set("combat_exp", 15600000);

                  set("attitude", "peaceful");
                  set("shen_type", -1);

        create_family("����ɽ", 1 , "ׯ��");
        set("inquiry", ([
                "ŷ����" : "ŷ���桢ŷ���棬������������ͦ��ġ�����\n",
			                //"" : "ŷ���桢ŷ���棬������������ͦ��ġ�����\n",

         ]));

        setup();
        carry_object("/d/baituo/obj/gs-zhang")->wield();
        carry_object(ARMOR_D("cloth"))->wear();

}

int feng_say()
{
	command("angry ");
	command("say �Ͻл��㲻Ҫ��У���л���������ܺ�������������أ�");
	command("heng ");
	command("say �Զ��ӣ��������������޹�Ҳûʲô�˲���ģ��ҾͰ�Ϊ���������Ĺ��򴫸��㡣\n");
	command("say ����Ϊ�����������ת�������������ʾ�������������Ͻл�����Ҳ�Ŀ��\n");
	command("heng");
	command("heng");
	command("heng");
	command("heng");
}
