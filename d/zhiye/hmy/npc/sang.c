// sang.c
#include <ansi.h>
inherit F_MASTER;
inherit NPC;

void create()
{
	set_name("ɣ����", ({ "sang sanniang", "sang", "sanniang"}));
	set("long", 
"һ����ò��������긾�ˣ���ɱ�������ĺ���������������\n");
	set("title",HIY"�������  "HIW"�׻�������"NOR);
  set("gender", "Ů��");
	set("age", 34);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 22);
	set("int", 25);
	set("con", 21);
	set("dex", 30);
                
  set("max_qi", 13000);
  set("max_jing", 4200);
	set("eff_jingli", 4200);
  set("jiali", 50);
  set("combat_exp", 4700000);
  set("shen", -5500);

	set_temp("apply/attack", 40);
	set_temp("apply/defence", 40);

    set_skill("tianmo-zhang",350);
    set_skill("tianmo-jue",200);
	set_skill("strike", 350);
	set_skill("literate", 100);
    set_skill("dodge",350);
	set_skill("huanmo-wubu", 350);
	set_skill("force", 350);
	set_skill("tianmo-gong", 350);
	set_skill("parry", 350);
	set_skill("hand", 350);
	set_skill("tianmo-shou", 200);

  map_skill("strike", "tianmo-zhang");
  map_skill("dodge", "huanmo-wubu");
  map_skill("force", "tianmo-gong");
	map_skill("parry", "tianmo-zhang");
	//map_skill("whip", "cihang-bian");
	prepare_skill("strike", "tianmo-zhang");
	create_family("�������",8,"����");
	
        setup();
        
  carry_object(BINGQI_D("changbian"))->wield();
	carry_object("/clone/misc/cloth")->wear();        
}
