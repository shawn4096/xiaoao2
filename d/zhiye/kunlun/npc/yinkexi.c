// xiaoxiangzi.c
#include <ansi.h>
inherit NPC;

void create()
{
	object ob;
	set_name("������", ({ "yin kexi", "yin", "kexi"}));
        set("long", 
"�������ǲ�˹��֣�ר���鱦����ò�߱���Ŀ���������룬��Ȼ�Ǹ����ˣ�
���ϴ���ȴ�Ǻ������������飬���������ⱦ����������������������
������̫ԭ�ȵط����鱦�����Բ�ȡ�˸��й�����������������\n");
        set("title",HIY"�ɹ�����  "HIG"��˹���"NOR);
        set("gender", "����");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 23);
        set("int", 23);
        set("con", 24);
        set("dex", 28);
        set("shen",1000000);

        set("max_qi", 20000);
        set("max_jing", 5000);
	      set("eff_jingli", 6000);
        set("jiali", 200);
        set("combat_exp", 9800000);
		set("class","bonze");

        set_skill("dodge",450);
		set_skill("buddhism",200);
        set_skill("literate", 220);
        set_skill("huanmo-wubu",450);
        set_skill("tianmo-gong",450);
        set_skill("strike", 450);
        set_skill("tianmo-zhang",450);        
        set_skill("force",450);
        set_skill("parry",450);
	    set_skill("whip", 450);
		set_skill("poison", 150);
	    set_skill("cihang-bian", 450);
		set_skill("kurong-changong", 350);

        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
		map_skill("parry", "cihang-bian");
	    map_skill("whip", "cihang-bian");
	    map_skill("strike", "tianmo-zhang");
	    prepare_skill("strike", "tianmo-zhang"); 
	   // create_family("�������", 9, "����");
	   set("chat_chance_combat", 85);
		set("chat_msg_combat", ({
  		(: perform_action, "whip.cibei" :),
  		(: perform_action, "strike.kuaigong" :),
		(: perform_action, "strike.feiwu" :),
		(: exert_function, "tianmo" :),			
		(: exert_function, "jieti" :),
		}));
        setup();
	//weapon=new("/clone/weapon/club/kusangbang");
	//weapon->wield();
	if(clonep()) {
		ob = unew("/clone/weapon/whip/jinlong-bian");
		if(ob) {
		ob->move(this_object());
		ob->wield();
		}
	}
	//carry_object(BINGQI_D("club"))->wield();
	carry_object(MISC_D("cloth"))->wear();
}
